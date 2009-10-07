/*
 * config.h
 *
 *  Created on: 05.06.2009
 *      Author: vedenko
 */

#ifndef CONFIG_H_
#define CONFIG_H_
//Multithreading
#ifdef  USE_BOOST_THREADS
#define THREAD_IMPLEMENTATION_CLASS core::multithreading::implementations::boost_thread::ImplementationFactory

#define THREAD_IMPLEMENTATION_PREDEF namespace implementations\
{\
	namespace boost_thread\
	{\
	class ImplementationFactory;\
	}\
}

#define THREAD_IMPLEMENTATION core::multithreading::ImplementationFactory< THREAD_IMPLEMENTATION_CLASS >

#define THREAD_IMPLEMENTATION_INCLUDE "core/multithreading/implementations/boost_thread/ImplementationFactory.h"

#endif //USE_BOOST_THREADS

#endif /* CONFIG_H_ */
