#include <iostream>

#include <core/multithreading/thread.h>
#include <core/multithreading/mutex.h>
#include <core/multithreading/condition_variable.h>

template<typename Type>
class Buffer
{
	core::multithreading::mutex *m_mutex;
	core::multithreading::condition_variable *m_condition;

	Type m_value;
	bool m_full;

	Buffer(const Buffer&);
	Buffer& operator =(const Buffer&);
public:
	typedef Type elem_type_t;

	Buffer()
		: m_mutex(NULL), m_condition(NULL), m_full(false)
	{
		m_mutex = new core::multithreading::mutex;
		m_condition = new core::multithreading::condition_variable;
	}
	~Buffer()
	{
		if(m_mutex)
			delete m_mutex;
		if(m_condition)
			delete m_condition;
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

	core::multithreading::mutex* mutex()
	{
		return m_mutex;
	}
	core::multithreading::condition_variable* condition()
	{
		return m_condition;
	}
};

class Producer
{
public:
	typedef Buffer<int> buffer_t;
	typedef Buffer<int>* buffer_ptr_t;

	static const int QueueSize = 20;

private:
	Buffer<int> m_buffer;

	Producer(const Producer&);
	Producer& operator=(const Producer&);
public:

	Producer()
		: m_buffer()
	{
	}
	
	void produce()
	{
		core::multithreading::mutex *const mtx = m_buffer.mutex();
		core::multithreading::condition_variable *const cv = m_buffer.condition();
		for(int i = 0; i < QueueSize; i++)
		{
			mtx->lock();
			while(m_buffer.isFull())
				cv->wait(mtx);
			m_buffer.push(i);
			cv->broadcast();
			mtx->release();
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
		core::multithreading::mutex *const mtx = m_producer->buffer()->mutex();
		core::multithreading::condition_variable *const cv = m_producer->buffer()->condition();
		Producer::buffer_ptr_t buffer = m_producer->buffer();
		
		mtx->lock();
		for(int i = 0; i < Producer::QueueSize; i++)
		{
			mtx->lock();
			while(!buffer->isFull())
				cv->wait(mtx);
			std::cout << (buffer->pop()) << " ";
			cv->signal();
			mtx->release();
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