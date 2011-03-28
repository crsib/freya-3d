/*
 * RederingAPIDriverID.h
 *
 *  Created on: Oct 12, 2009
 *      Author: crsib
 */

#ifndef REDERINGAPIDRIVERID_H_
#define REDERINGAPIDRIVERID_H_

#include "core/drivermodel/DriverID.h"

#include "renderer/RenderingAPIVersion.h"

namespace renderer
{

class RenderingAPIDriverID: public core::drivermodel::DriverID
{
public:
	virtual ~RenderingAPIDriverID(){}

	virtual core::drivermodel::Driver*		create()	const = 0;
	virtual EString							id()		const = 0;
	virtual renderer::RenderingAPIVersion*	version() 	const = 0;
};

}

#endif /* REDERINGAPIDRIVERID_H_ */
