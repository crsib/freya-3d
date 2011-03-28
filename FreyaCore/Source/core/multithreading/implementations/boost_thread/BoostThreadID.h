/*
 * BoostThreadID.h
 *
 *  Created on: 06.07.2009
 *      Author: vedenko
 */

#ifndef BOOSTTHREADID_H_
#define BOOSTTHREADID_H_
#include <boost/thread/thread.hpp>
#include "core/multithreading/ThreadID.h"

namespace core
{

namespace multithreading
{
class ThreadID;
const ThreadID& getCurrentThreadID();
namespace implementations
{

namespace boost_thread
{

class BoostThreadID : public core::multithreading::ThreadID
{
	friend class BoostThread;
	friend class ImplementationFactory;
	friend const ThreadID& core::multithreading::getCurrentThreadID();
	BoostThreadID(const boost::thread::id& ID) : m_ID(ID){}
public:
	BoostThreadID() : m_ID(boost::thread::id()){}

	virtual bool operator==(const ThreadID& other) const
			{
				return m_ID == static_cast<const BoostThreadID&>(other).m_ID;
			}
	virtual bool operator!=(const ThreadID& other) const
			{
				return m_ID != static_cast<const BoostThreadID&>(other).m_ID;
			}
private:
			const boost::thread::id	m_ID;
};


}
}
}
}
#endif /* BOOSTTHREADID_H_ */
