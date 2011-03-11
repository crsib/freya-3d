/*
 * CubeDriver.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef CUBEDRIVER_H_
#define CUBEDRIVER_H_

/*
 *
 */
#include "resources/ResourceManagerDriver.h"

namespace resources {

namespace drivers {

class CubeDriver: public resources::ResourceManagerDriver {
public:
	CubeDriver();
	virtual ~CubeDriver();

	virtual bool	unique() const;
	virtual EString id() const;
	virtual Resource*	loadSynchronous(const EString& ID);
	virtual Resource*	loadAsynchronous(const EString& ID);
	virtual void 		destroy(Resource* res);
};

}

}

#endif /* CUBEDRIVER_H_ */
