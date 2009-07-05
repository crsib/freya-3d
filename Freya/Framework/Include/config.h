/*
 * config.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef CONFIG_H_
#define CONFIG_H_
//Multithreading

#define THREAD_IMPLEMENTATION_CLASS core::multithreading::implementations::boost_thread::ImplementationFactory

#define THREAD_IMPLEMENTATION_PREDEF namespace implementations\
{\
	namespace boost_thread\
	{\
	class ImplementationFactory;\
	}\
}

#define THREAD_IMPLEMENTATION core::multithreading::ImplementationFactory< THREAD_IMPLEMENTATION_CLASS >

#endif /* CONFIG_H_ */
