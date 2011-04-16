/* File		: core/memory/MemoryImpl.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "core/memory/MemoryArena.h"
#include "core/memory/MemoryPools.h"

#include <cassert>
#include <iostream>

#include <list>
#include <vector>

#include "atomic/atomic.h"
#include "integer.h"

#define YIELD() PAUSE ;

namespace core
{
namespace memory
{
/******************* Statics ********************************************************************
 ************************************************************************************************/
unsigned memory_allocated 		= 0;
unsigned allocation_count 		= 0;
unsigned deallocation_count 	= 0;
unsigned alloc_dealloc_dif 		= 0;
unsigned allocated_for_buffers	= 0;

namespace __internal
{
core::memory::MemoryArena		arena_inst;

const char*			pool_name_srings[] = {
		"default",
		"STL",
		"math",
		"generic",
		"class",
		"lua",

		"user"
};

}//namespace internal

/******************* Memory Pool implementation *************************************************
 ************************************************************************************************/

namespace __internal
{

#define FREE_BLOCK_MARK 0xDEADBEEF
#define ALLOCATED_BLOCK 0xFEEDFACE

typedef struct	__MemoryHeader
{
	__MemoryHeader*			prev;
	uint32_t				size;
	uint32_t				magic;
	__MemoryHeader*			next;

} MemoryHeader,*MemoryHeaderPtr;

class MemoryPool;

class MemoryBuffer
{
public:
	inline
	explicit MemoryBuffer(uint32_t size,uint32_t alignment,uint32_t pool) throw (): m_First(NULL),m_Last(NULL),m_Size(size + alignment + sizeof(__MemoryHeader)),
	m_Alignment(alignment),m_AllocCount(0), m_Allocated(0), m_ParentPool(pool),m_HeaderOffset(0),m_Mutex(0)
	{
		m_Buffer =  reinterpret_cast<uint8_t*>(malloc(m_Size));

		allocated_for_buffers += m_Size;
		if(m_Buffer)
		{
			if(m_Alignment == 0)
				m_Alignment  = 1;
			//Ok, we w managed to allocate buffer. Now, we should make the first address aligned
			if(sizeof(__MemoryHeader) % m_Alignment)
				m_HeaderOffset = m_Alignment - (sizeof(__MemoryHeader) % m_Alignment);
			uint32_t initial_offset = 0;
			if((reinterpret_cast<uint32_t>(m_Buffer + sizeof(__MemoryHeader))%m_Alignment))
				initial_offset = m_Alignment - (reinterpret_cast<uint32_t>(m_Buffer + sizeof(__MemoryHeader))%m_Alignment);
			//Setup memory header
			m_First = m_Last = reinterpret_cast<MemoryHeaderPtr>(m_Buffer + initial_offset);
			assert((reinterpret_cast<uint32_t>((m_First + sizeof(__MemoryHeader))) % m_Alignment) == 0 );
			m_Allocated = sizeof(__MemoryHeader) + (reinterpret_cast<uint8_t*>(m_First) - m_Buffer);

			m_First->prev  = m_First->next = NULL;
			m_First->magic = FREE_BLOCK_MARK;
			m_First->size  = m_Size - m_Allocated;

			//Write log
			std::clog << "Allocated memory buffer:\n\tSize: " << m_Size / (1024.0*1024.0)<< " MB\n\tAvailable: " << m_First->size / (1024.0*1024.0)
																																																			<< " MB\n\tAlignment: " << m_Alignment
																																																			<< " B\n\tPool: " << (pool < LAST_POOL ? pool_name_srings[pool] : pool_name_srings[LAST_POOL]) << std::endl;

		} // m_Buffer != NULL
		else
		{
#pragma  mark ("Implement error reporting")
			//throw MemoryException("Failed to allocate memory buffer");
		}

	}
	~MemoryBuffer()
	{
		if(m_Buffer == NULL)
			return;
		allocated_for_buffers -= m_Size;
		free( m_Buffer );
		m_Buffer = NULL;
		std::clog << "Deallocated memory buffer:\n\tSize: " << m_Size / (1024.0*1024.0)
																																																		<< " MB\n\tPool: " << (m_ParentPool < LAST_POOL ? pool_name_srings[m_ParentPool] : pool_name_srings[LAST_POOL]) << std::endl;
	}

	inline
	bool					isOk() const
	{
		return m_Buffer != NULL;
	}

	inline
	bool 					empty() const
	{
		return				(m_AllocCount == 0);
	}

	inline
	bool					full() const
	{
		return				(m_Size == m_Allocated);
	}

	inline uint8_t*
	allocate(uint32_t size)
	{
		if(m_Buffer == NULL)
			return NULL;
		//Update the size
		uint32_t al = size % m_Alignment;
		if(al)
			size += m_Alignment - al;
		//Check the first block
		if( m_First->size >= size && (m_First->magic == FREE_BLOCK_MARK))
		{
			return sliceAndRemove(m_First,size);
		} //Check the last block
		else if( m_Last->size >= size && (m_Last->magic == FREE_BLOCK_MARK))
		{
			return sliceAndRemove(m_Last,size);
		}
		else //Find a block
		{
			for(MemoryHeaderPtr block = m_First; block; block = block->next)
				if((block->magic == FREE_BLOCK_MARK) &&block->size >= size)
					return sliceAndRemove (block,size);
		}
		return NULL;
	}

	inline
	bool					free(uint8_t* p)
	{
		if( (p < m_Buffer) || (p >= m_Buffer + m_Size) )
			return false;
		MemoryHeaderPtr	block = reinterpret_cast<MemoryHeaderPtr>((p - sizeof(__MemoryHeader)));

		if(block->magic == FREE_BLOCK_MARK) //It must be already deallocated
			return true;
		if(block->magic != ALLOCATED_BLOCK) //And it fucking must be allocated from arena at this point
			return false;

		insertAndConnect(block);

		return true;
	}

private:

	inline
	uint8_t *				sliceAndRemove(MemoryHeaderPtr  block,uint32_t size)
	{
		if(block->magic == FREE_BLOCK_MARK)
		{
			while(m_Mutex.bit_test_and_set(1))
			{
				YIELD();
			}

			{
				m_AllocCount++;
				m_Allocated += size;

				allocation_count++;
				alloc_dealloc_dif++;
				if((size + m_HeaderOffset + sizeof(__MemoryHeader) + m_Alignment) > block->size)
				{
					if(block->prev)
						block->prev->next = block->next;
					else if(block->next)
					{
						m_First = block->next;
						m_First->prev = NULL;
					}

					if(block->next)
						block->next->prev = block->prev;
					else if(block->prev)
					{
						m_Last = block->prev;
						m_Last->next = NULL;
					}
					memory_allocated += block->size;
				}
				else //Slicing needed
				{
					memory_allocated += size;
					//We need to calculate address of next memory block
					MemoryHeaderPtr slice = reinterpret_cast<MemoryHeaderPtr>(reinterpret_cast<uint8_t*>(block) + sizeof(__MemoryHeader) + size + m_HeaderOffset);
					assert((reinterpret_cast<uint32_t>((reinterpret_cast<uint8_t*>(slice) + sizeof(__MemoryHeader))) % m_Alignment) == 0 );
					slice->size = block->size - (sizeof(__MemoryHeader) + size + m_HeaderOffset);

					assert((reinterpret_cast<uint8_t*>(slice) - (reinterpret_cast<uint8_t*>(block) + sizeof(__MemoryHeader))) >= size );

					block->size = size;
					slice->next = block->next;
					slice->prev = block->prev;

					if(slice->prev)
						slice->prev->next = slice;
					else
						m_First = slice;

					if(slice->next)
						slice->next->prev = slice;
					else
						m_Last = slice;


					slice->magic = FREE_BLOCK_MARK;
					m_Allocated += m_HeaderOffset + sizeof(__MemoryHeader);
				}
			}
			m_Mutex = 0;
			block->magic = ALLOCATED_BLOCK;
			assert(m_Allocated <= m_Size);
			assert(reinterpret_cast<uint32_t>(reinterpret_cast<uint8_t*>(block) + sizeof(__MemoryHeader)) % m_Alignment == 0);
			return reinterpret_cast<uint8_t*>(block) + sizeof(__MemoryHeader);
		}
		return NULL;
	}

	inline
	void					insertAndConnect(MemoryHeaderPtr block)
	{
		//Sync this section on mutex free basis
		while(m_Mutex.bit_test_and_set(1))
		{
			YIELD();
		}
		{
			//Special case discussed above
			m_AllocCount--;
			m_Allocated -= block->size;
			memory_allocated -= block->size;
			deallocation_count++;
			alloc_dealloc_dif--;

			if((m_First == m_Last) && (m_First == block))
			{
				block->magic = FREE_BLOCK_MARK;
			}
			else//!((m_First == m_Last) && (m_First == block))
			{
				block->magic = FREE_BLOCK_MARK;
				if(m_First > block)
				{
					block->prev = NULL;
					if((reinterpret_cast<uint8_t*>(block) + block->size + m_HeaderOffset + sizeof(__MemoryHeader)) == reinterpret_cast<uint8_t*>(m_First)) //Linkage needed
					{
						block->next = m_First->next;
						if(m_First->next)
							m_First->next->prev = block;
						else
							m_Last = block;

						block->size += m_HeaderOffset + sizeof(__MemoryHeader) + m_First->size;
						m_Allocated -= m_HeaderOffset + sizeof(__MemoryHeader);
						m_First = block;
					}
					else
					{
						block->next = m_First;
						m_First->prev = block;
						m_First = block;
					}
				}
				else if(m_Last < block)
				{
					block->next = NULL;
					if((reinterpret_cast<uint8_t*>(m_Last) + m_Last->size + m_HeaderOffset + sizeof(__MemoryHeader)) == reinterpret_cast<uint8_t*>(block))
					{
						m_Last->size += m_HeaderOffset + sizeof(__MemoryHeader) + block->size;
						m_Allocated -= m_HeaderOffset + sizeof(__MemoryHeader);
					}
					else
					{
						block->prev = m_Last;
						m_Last->next = block;
						m_Last = block;
					}
				}
				else //General variant m_First < block < m_Last
				{
					MemoryHeaderPtr prev_blc = m_Last;
					for( ; prev_blc > block; prev_blc = prev_blc->prev)
					{

					}
					assert(prev_blc);

					MemoryHeaderPtr next_blc = prev_blc->next;

					//Check if front linkage needed
					//Nothing bad could happen

					if((reinterpret_cast<uint8_t*>(prev_blc) + prev_blc->size + m_HeaderOffset + sizeof(__MemoryHeader)) == reinterpret_cast<uint8_t*>(block))
					{
						m_Allocated -= m_HeaderOffset + sizeof(__MemoryHeader);
						prev_blc->size += m_HeaderOffset + sizeof(__MemoryHeader) + block->size;
						block = prev_blc;
					}
					else
					{
						block->prev = prev_blc;
						block->next = next_blc;
						prev_blc->next = block;
						if(next_blc)
							next_blc->prev = block;
						else
							m_Last = block;
					}
					//Check for back linkage. We could possibly link to m_Last
					if((reinterpret_cast<uint8_t*>(block) + block->size + m_HeaderOffset + sizeof(__MemoryHeader)) == reinterpret_cast<uint8_t*>(next_blc))
					{
						m_Allocated -= m_HeaderOffset + sizeof(__MemoryHeader);
						block->size += m_HeaderOffset + sizeof(__MemoryHeader) + next_blc->size;
						block->next = next_blc->next;
						if(block->next == NULL)
							m_Last = block;
						else
							block->next->prev = block;
					}

				}
			} // Normal case
			assert(!(block->prev == NULL && block != m_First));
			assert(!(block->next == NULL && block != m_Last));
			assert(!(m_Last->next));
			assert(!(m_First->prev));
		} // End of sync
		m_Mutex = 0;
	}

	uint8_t*				m_Buffer;
	MemoryHeaderPtr			m_First;
	MemoryHeaderPtr			m_Last;
	uint32_t				m_Size;
	uint32_t				m_Alignment;
	uint32_t				m_AllocCount;
	uint32_t				m_Allocated;
	uint32_t				m_ParentPool;
	uint32_t				m_HeaderOffset;
	atomic::atomic<uint32_t>	m_Mutex;
};

/******************* Small block implementation *************************************************
 ************************************************************************************************/
//Code of rtAllocator is a slightly modified code from http://www.codeguru.com/cpp/misc/misc/memory/article.php/c13101/
class block;

class rtAllocator
{
public:
	friend class MemoryPool;
	rtAllocator(MemoryPool*	pool);
	void* alloc(long ls);
	bool free(void* p);

	static const int bdCount = 129;
private:
	MemoryPool*			m_Pool;
	// must be called before first alloc
	void init();
	~rtAllocator();
	int findBlockIndex(void* b);
	block* findBlockInArray(void* p);

	void addBlockToArray(block* b);
	void removeBlockFromArray(block* b);

	block* mFreeBlocks[bdCount];
	long mBlockCount;
	long mBlockArraySize;
	block** mBlockArray;
	block** mBlockArrayEnd;
	bool mInited;
	block* mLastFoundBlock;
	char mBDIndexLookup[1025];
	atomic::atomic<uint32_t>	m_Lock;
};

typedef struct
{
	int fixedAllocSize;
	int chunks;
} blockDescriptor;

blockDescriptor bd[rtAllocator::bdCount];

class block
{
public:

	inline
	bool init(int fixedAllocSize, int bdIndex, int chunks)
	{
		mPrevFreeBlock = NULL;
		mNextFreeBlock = NULL;
		mAllocCount = 0;
		mFixedAllocSize = fixedAllocSize;
		mBDIndex = bdIndex;
		mChunks = chunks;

		mLastByte = (unsigned char*)this + getAllocSize(this->mFixedAllocSize, this->mChunks)-1;
		unsigned char* mDataStart = (unsigned char*)this + getHeaderSize(mChunks);
		uint32_t al = (reinterpret_cast<uint32_t>(mDataStart)%16);
		if(al)
			al = 16 - al;
		mDataStart = mDataStart + al; // 16 byte align
		assert(reinterpret_cast<uint32_t>(mDataStart)%16 == 0);

		mFreeChunk = NULL;
		mInitCursor = mDataStart;
		mTotalCount = mChunks * 16;
		return true;
	}

	inline bool isEmpty()
	{
		return (mAllocCount == 0);
	}

	inline bool isFull()
	{
		return mAllocCount == mTotalCount;
	}

	inline
	void* alloc()
	{
		void* result;

		if (mFreeChunk)
		{
			result = mFreeChunk;
			mFreeChunk = (void**)*mFreeChunk;
		}
		else
		{
			result = mInitCursor;
			mInitCursor += mFixedAllocSize;
		}

		mAllocCount++;
		return result;
	}

	inline void free(void* p)
	{
		void **pp = (void**)p;
		*pp = mFreeChunk;
		mFreeChunk = (void**)p;
		mAllocCount--;
	}

	static
	inline unsigned long getHeaderSize(int /*chunks*/)
	{
		return sizeof(block);
	}

	static
	unsigned long getAllocSize(int fixedAllocSize, int chunks)
	{
		return getHeaderSize(chunks) + (fixedAllocSize * 16 * chunks) + 16;
	}

	inline
	unsigned char* getLastByte()
	{
		return mLastByte;
	}

public:
	block* mNextFreeBlock;
	block* mPrevFreeBlock;
	void** mFreeChunk;
	unsigned long mTotalCount;
	unsigned long mAllocCount;
	unsigned char *mInitCursor;
	unsigned short mFixedAllocSize;
	unsigned short mChunks;
	unsigned char mBDIndex;
	unsigned char* mLastByte;
};

inline
void rtAllocator::init()
{
	if (mInited) return;

	// initialize the block descriptors for each heap.
	bd[0].fixedAllocSize = 4;
	bd[0].chunks = 3;
	// initialize for multiple of 8
	for (int i = 1; i < bdCount; i++)
	{
		int allocSize = i*8;
		int chunks = 11;

		bd[i].fixedAllocSize = allocSize;

		if (allocSize == 8) chunks = 3;
		else if (allocSize == 1008) chunks = 1;
		else if (allocSize == 1016) chunks = 1;
		else if (allocSize == 1024) chunks = 1;

		bd[i].chunks = chunks;
	}

	// initialize the free lists for each heap
	for (int i = 0; i < bdCount; i++)
	{
		mFreeBlocks[i] = NULL;
	}

	// lookup table used to quickly find out which heap the alloc request
	// should go to.
	for (int i = 0; i <= 1024; i++)
	{
		mBDIndexLookup[i] = -1;
		for (int j = 0; j < bdCount; j++)
		{
			if (i <= bd[j].fixedAllocSize)
			{
				mBDIndexLookup[i] = j;
				break;
			}
		}
	}

	mBlockArray = NULL;
	mInited = true;
}


inline
rtAllocator::rtAllocator(MemoryPool* pool)
{
	m_Pool = pool;
	mBlockCount = 0;
	mBlockCount = 0;
	mLastFoundBlock = NULL;
	mBlockArraySize = 10000;
	mBlockArray = NULL;
	mBlockArrayEnd = NULL;
	mInited = false;
}



/******************* Memory pool implementation *************************************************
 ************************************************************************************************/
class  MemoryPool
{
public:
	inline
	explicit MemoryPool(uint32_t poolId,uint32_t preallocSize, uint32_t alignment) :
	m_PoolId(poolId), m_PreallocSize(preallocSize),m_Alignment(alignment),m_Lock(0)
	{
		MemoryBuffer*	buf = new MemoryBuffer(preallocSize,alignment,poolId);
		assert(buf);
		if(buf->isOk())
		{
			m_Buffers.push_back(buf);
			m_SmallBlockPool = new rtAllocator(this);
			m_SmallBlockPool->init();
		}
	}

	~MemoryPool()
	{
		delete m_SmallBlockPool;
		for(std::vector<MemoryBuffer*>::iterator it = m_Buffers.begin(); it != m_Buffers.end(); ++it)
		{
			delete (*it);
		}
	}

	inline
	void*
	alloc(size_t sz)
	{
		void* p;
		if((sz <= 1024) && (p = m_SmallBlockPool->alloc(sz)))
		{
			//m_Lock = 0;
			return p;
		}
		else
			return allocate(sz);
	}

	inline
	void*
	allocate(size_t sz)
	{
		void* p;
		while(m_Lock.bit_test_and_set(1))
		{
			YIELD();
		}

		for(size_t i = 0; i < m_Buffers.size(); i++)
			if((p = m_Buffers[i]->allocate(sz)) != NULL)
			{
				m_Lock = 0;
				return p;
			}

		uint32_t pr = (2 << m_Buffers.size())*m_PreallocSize;
		m_Buffers.push_back(new MemoryBuffer(pr > sz ? pr : sz,m_Alignment,m_PoolId));
		m_Lock = 0;
		return m_Buffers.back()->allocate(sz);
	}
	void 	free(void* p)
	{
		if(!m_SmallBlockPool->free(p))
			generic_free(p);
	}
	void	generic_free(void* p)
	{
		while(m_Lock.bit_test_and_set(1))
		{
			YIELD();
		}
		for(size_t i = 0; i < m_Buffers.size(); i++)
			if(m_Buffers[i]->free(reinterpret_cast<uint8_t*>(p)))
			{
				if(m_Buffers[i]->empty())
				{
					if(m_Buffers.size() > 1)
					{
						for(size_t j = 0; j < m_Buffers.size(); j++)
							if((j != i) && !m_Buffers[j]->full())
							{
								delete m_Buffers[i];
								m_Buffers.erase(m_Buffers.begin() + i);
								m_Lock = 0;
								return;
							}
					}
				}
				m_Lock = 0;
				return;
			}
		m_Lock = 0;
	}
private:
	std::vector<MemoryBuffer*>	m_Buffers;

	uint32_t					m_PoolId;
	uint32_t					m_PreallocSize;
	uint32_t					m_Alignment;
	atomic::atomic<uint32_t>		m_Lock;
	rtAllocator*				m_SmallBlockPool;
};

#define ALLOCJR_FULLBLOCK (block*)0xffffffff

rtAllocator::~rtAllocator()
{
	//m_Pool->generic_free(mBlockArray);
}

inline
void* rtAllocator::alloc(long ls)
{
	while(m_Lock.bit_test_and_set(1))
	{
		YIELD();
	}
	if (ls == 0) ls = 1;
	int bdIndex = -1;
	if (ls <= 1024) bdIndex = mBDIndexLookup[ls];
	if (bdIndex < 0)
	{
		// Not handling blocks of this size throw to blockalloc
		m_Lock = 0;
		return NULL;
	}
	else
	{
		void* result = NULL;

		if (!mFreeBlocks[bdIndex])
		{

			bd[bdIndex].chunks*=2;
			if (bd[bdIndex].chunks > 20) bd[bdIndex].chunks = 1;

			block* b = (block*)m_Pool->allocate(block::getAllocSize(bd[bdIndex].fixedAllocSize, bd[bdIndex].chunks));
			if (b)
			{
				b->init(bd[bdIndex].fixedAllocSize, bdIndex, bd[bdIndex].chunks);

				addBlockToArray(b);
				mFreeBlocks[bdIndex] = b;
			}
		}
		if (mFreeBlocks[bdIndex])
		{
			result = mFreeBlocks[bdIndex]->alloc();
			block *b = mFreeBlocks[bdIndex];

			if (b->mNextFreeBlock != ALLOCJR_FULLBLOCK && b->isFull())
			{
				// Unlink from free list
				if (b->mNextFreeBlock)
				{
					b->mNextFreeBlock->mPrevFreeBlock = b->mPrevFreeBlock;
				}
				if (b->mPrevFreeBlock)
				{
					b->mPrevFreeBlock->mNextFreeBlock = b->mNextFreeBlock;
				}
				mFreeBlocks[bdIndex] = b->mNextFreeBlock;
				b->mNextFreeBlock = ALLOCJR_FULLBLOCK; // special value means removed from free list
				b->mPrevFreeBlock = ALLOCJR_FULLBLOCK;
			}
		}
		m_Lock = 0;
		return result;
	}
	m_Lock = 0;
}

inline
bool rtAllocator::free(void* p)
{
	while(m_Lock.bit_test_and_set(1))
	{
		YIELD();
	}
	block* b = findBlockInArray(p);
	if (b)
	{
		b->free(p);
		if (b->isEmpty())
		{
			// Unlink from freelist and return to the system
			if (b->mNextFreeBlock)
			{
				b->mNextFreeBlock->mPrevFreeBlock = b->mPrevFreeBlock;
			}
			if (b->mPrevFreeBlock)
			{
				b->mPrevFreeBlock->mNextFreeBlock = b->mNextFreeBlock;
			}
			if (mFreeBlocks[b->mBDIndex] == b) mFreeBlocks[b->mBDIndex] = b->mNextFreeBlock;

			removeBlockFromArray(b);
			m_Pool->generic_free(b);
		}
		else
		{
			// need to see if block is not in free list if not add it back
			if (b->mNextFreeBlock == ALLOCJR_FULLBLOCK)
			{
				b->mPrevFreeBlock = NULL;
				b->mNextFreeBlock = mFreeBlocks[b->mBDIndex];
				if (mFreeBlocks[b->mBDIndex]) mFreeBlocks[b->mBDIndex]->mPrevFreeBlock = b;
				mFreeBlocks[b->mBDIndex] = b;
			}
		}
		m_Lock = 0;
		return true;
	}
	else
	{
		//must not be ours pass to blockfree
		m_Lock = 0;
		return false;
	}
}

inline
void rtAllocator::addBlockToArray(block* b)
{
	if (!mBlockArray)
	{
		mBlockArray = (block**)m_Pool->allocate(sizeof(block**)*mBlockArraySize);
		mBlockArrayEnd = mBlockArray+mBlockCount-1;
	}
	if (mBlockArraySize < mBlockCount+1)
	{
		mBlockArraySize += 10000;
		void* p = m_Pool->allocate(mBlockArraySize*sizeof(block**));
		::memcpy(p,mBlockArray,mBlockArraySize - 10000);
		m_Pool->generic_free(mBlockArray);
		mBlockArray= (block**)p;
		mBlockArrayEnd = mBlockArray+mBlockCount-1;
	}
	bool done = false;
	long s = 0;
	long e = mBlockCount-1;
	long m = s + ((e-s+1)/2);
	while (s < e)
	{
		if (b < mBlockArray[m])
		{
			e = m-1;
		}
		else if ((unsigned char*)b > mBlockArray[m]->getLastByte())
		{
			s = m+1;
		}
		m = s+ ((e-s+1)/2);
	}
	if (s<mBlockCount && (unsigned char*)b > (unsigned char*)mBlockArray[s]->getLastByte())
	{
		s++;
	}

	// We want to insert as s
	for (long i = mBlockCount-1; i >= s; i--)
	{
		mBlockArray[i+1] = mBlockArray[i];
	}

	mBlockArray[s] = b;
	mBlockCount++;
	mBlockArrayEnd = mBlockArray+mBlockCount-1;
}

inline
int rtAllocator::findBlockIndex(void* b)
{
	int result = -1;

	if (mBlockCount > 0)
	{
		block** s = mBlockArray;
		block** e = mBlockArrayEnd;
		block** m = s + ((e-s+1)>>1);

		while (s < m) // Given this condition alone we know that m-1 exists
		{
			if ((unsigned char*)b <  (unsigned char*)*m) e = m-1;
			else if ((unsigned char*)b >= (unsigned char*)*m) s = m;
			m = s + ((e-s+1)>>1);
		}

		if (m >= mBlockArray && m <= mBlockArrayEnd) // valid block
			if ((unsigned char*)b >= (unsigned char*)*m && (unsigned char*)b <= (*m)->getLastByte())
				result = m-mBlockArray;

	}

	return result;
}

inline
void rtAllocator::removeBlockFromArray(block* b)
{
	int m = findBlockIndex(b);

	if (m >=0)
	{
		if (mLastFoundBlock == mBlockArray[m]) mLastFoundBlock = NULL;
		for (long i = m+1; i < mBlockCount; i++)
		{
			mBlockArray[i-1] = mBlockArray[i];
		}
		mBlockCount--;
		mBlockArrayEnd = mBlockArray+mBlockCount-1;

		if (mBlockCount == 0)
		{
			m_Pool->generic_free(mBlockArray);
			mBlockArray = NULL;
			mBlockArrayEnd = NULL;
		}
	}
}

inline
block* rtAllocator::findBlockInArray(void* p)
{
	if (mLastFoundBlock)
	{
		if ((unsigned char*)mLastFoundBlock <= p && p <= mLastFoundBlock->getLastByte())
		{
			return mLastFoundBlock;
		}
	}

	// binary search code duped here to avoid function call penalty
	block* result = NULL;
	if (mBlockCount > 0)
	{

		block** s = mBlockArray;
		block** e = mBlockArrayEnd;
		block** m = s + ((e-s+1)>>1);
		while (s < m) // Given this condition alone we know that m-1 exists
		{
			if ((unsigned char*)p <  (unsigned char*)*m) e = m-1;
			else if ((unsigned char*)p >= (unsigned char*)*m) s = m;
			m = s + ((e-s+1)>>1);
		}
		if (m >= mBlockArray && m <= mBlockArrayEnd) // valid block
			if ((unsigned char*)p >= (unsigned char*)*m && (unsigned char*)p <= (*m)->getLastByte())
				result = mLastFoundBlock = *m;
	}
	return result;
}

} // __internal

/******************* Memory Arena implementation ************************************************
 ************************************************************************************************/


MemoryArena::MemoryArena()
{
	m_Pools.reserve(LAST_POOL);

	m_Pools.push_back(new __internal::MemoryPool(DEFAULT_POOL,128,1));
	m_Pools.push_back(new __internal::MemoryPool(STL_POOL,1024*1024,1));
	m_Pools.push_back(new __internal::MemoryPool(MATH_POOL,1024*4096,16));
	m_Pools.push_back(new __internal::MemoryPool(GENERIC_POOL,1024*4024,16));
	m_Pools.push_back(new __internal::MemoryPool(CLASS_POOL,1024*4096,16));
	m_Pools.push_back(new __internal::MemoryPool(LUA_POOL,1024*1024,16));

	std::clog << "Memory arena created " << std::endl;
}

MemoryArena::~MemoryArena()
{
	for(size_t i = m_Pools.size() ; i > 0; --i)
		delete m_Pools[ i - 1 ];
	std::clog << "Memory arena destroyed " << std::endl;
}

MemoryArena*	MemoryArena::instance()
{
	return &__internal::arena_inst;
}

unsigned	MemoryArena::addPool(size_t size,size_t alligment)
{
	unsigned sz = m_Pools.size();
	m_Pools.push_back(new __internal::MemoryPool(sz,size,alligment));
	return sz;
}

void*		MemoryArena::allocate(size_t size, unsigned pool)
{
	return m_Pools[pool]->alloc(size);
}

void		MemoryArena::free(void* p,unsigned pool)
{
	if(p)
		m_Pools[pool]->free(p);
}

FREYA_SUPPORT_EXPORT void* alloc( size_t size, unsigned pool /*= GENERIC_POOL*/ ) throw()
{
	return MemoryArena::instance()->allocate(size,pool);
}


FREYA_SUPPORT_EXPORT void dealloc( void* p, unsigned pool /*= GENERIC_POOL*/ ) throw()
{
	MemoryArena::instance()->free(p,pool);
}

}//memory
}//core
