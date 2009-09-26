/*
 * CubeDriver.cpp
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#include "CubeDriver.h"


namespace resources {

namespace drivers {

CubeDriver::CubeDriver() {
	// TODO Auto-generated constructor stub

}

CubeDriver::~CubeDriver() {
	// TODO Auto-generated destructor stub
}

bool	CubeDriver::unique() const
{
	return true;
}

EString CubeDriver::id() const
{
	return "cube";
}

Resource*	CubeDriver::loadSynchronous(const EString& ID)
{
	return NULL; 
}

Resource*	CubeDriver::loadAsynchronous(const EString& ID)
{
	return NULL;
}

void 		CubeDriver::destroy(Resource* res)
{

}


}

}
