/*
 * AIObject.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef AIOBJECT_H_
#define AIOBJECT_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
//TODO: finish interface and documentation
namespace framework
{

class AIObject: public EngineSubsystem {
public:
	virtual ~AIObject() {}
};

}

#endif /* AIOBJECT_H_ */
