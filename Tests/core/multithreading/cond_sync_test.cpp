#include <iostream>

#include <core/multithreading/thread.h>
#include <core/multithreading/mutex.h>
#include <core/multithreading/condition_variable.h>
#include <core/multithreading/synchronize.h>

#ifndef _MSC_VER
# 	define system(x)
#endif

class cond_sync
{
	core::multithreading::mutex					*m_mutex;
	core::multithreading::condition_variable	*m_cond_var;

public:
	cond_sync()
		: m_mutex(NULL), m_cond_var(NULL)
	{
		m_mutex = new core::multithreading::mutex;
		m_cond_var = new core::multithreading::condition_variable;
	}

	inline void lock()
	{
		m_mutex->lock();
	}

	inline void release()
	{
		m_mutex->release();
	}

	inline void wait()
	{
		m_cond_var->wait(m_mutex);
	}

	inline void signal()
	{
		m_cond_var->signal();
	}

	inline void broadcast()
	{
		m_cond_var->broadcast();
	}

	~cond_sync()
	{
		if(m_mutex)
			delete m_mutex;
		if(m_cond_var)
			delete m_cond_var;
	}
};

template<typename Type>
class Buffer
{
	Type m_value;
	bool m_full;

	Buffer(const Buffer&);
	Buffer& operator =(const Buffer<Type>&);
public:
	typedef Type elem_type_t;

	Buffer()
		: m_full(false)
	{
	}
	
	Buffer<Type>& push(const Type& value)
	{
		m_value = value;
		m_full = true;
		return *this;
	}

	Type pop()
	{
		m_full = false;
		return m_value;
	}

	bool isFull() const
	{
		return m_full;
	}
};

class Producer
{
public:
	typedef Buffer<int> buffer_t;
	typedef Buffer<int>* buffer_ptr_t;

	static const int QueueSize = 20;

private:
	buffer_t  m_buffer;

	Producer(const Producer&);
	Producer& operator=(const Producer&);
public:
	cond_sync CondSync;


	Producer()
		: m_buffer()
	{
	}
	
	void produce()
	{
		for(int i = 0; i < QueueSize; i++)
			synchronize(&CondSync) 
			{
				while(m_buffer.isFull())
					CondSync.wait();
				m_buffer.push(i);
				CondSync.broadcast();
			}
	}

	buffer_ptr_t buffer()
	{
		return &m_buffer;
	}


private:
};

class Consumer
{
	Producer* m_producer;

	Consumer();
	Consumer(const Consumer&);
	Consumer& operator=(const Consumer&);
public:
	Consumer(Producer& prod)
		: m_producer(&prod)
	{
	}
	void consume()
	{
		cond_sync* cs = &m_producer->CondSync;
		Producer::buffer_ptr_t buffer = m_producer->buffer();
		
		for(int i = 0; i < Producer::QueueSize; i++)
			synchronize(cs)
			{
				while(!buffer->isFull())
					cs->wait();
				std::cout << (buffer->pop()) << " ";
				cs->signal();
			}
	}
};

int main(void)
{
	using core::multithreading::thread;

	Producer producer;
	Consumer consumer(producer);

	thread *p_thread = thread::create<Producer, &Producer::produce>(producer);
	thread *c_thread = thread::create<Consumer, &Consumer::consume>(consumer);

	p_thread->join();
	c_thread->join();
	system("PAUSE");
	delete p_thread;
	delete c_thread;
}
