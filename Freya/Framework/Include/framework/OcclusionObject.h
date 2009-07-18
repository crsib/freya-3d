/*
 * OcclusionObject.h
 *
 *  Created on: 14.07.2009
 *      Author: vedenko
 */

#ifndef OCCLUSIONOBJECT_H_
#define OCCLUSIONOBJECT_H_

/*
 *
 */
#include "EngineSubsystem.h"
//TODO: finish interface and documentation
namespace framework
{

class OcclusionObject: public virtual EngineSubsystem
{
public:
	virtual ~OcclusionObject() {}
};

}

#endif /* OCCLUSIONOBJECT_H_ */
