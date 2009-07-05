/*
 * MovementDrivenDevice.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef MOVEMENTDRIVENDEVICE_H_
#define MOVEMENTDRIVENDEVICE_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"

namespace drivermodel
{
class Driver;
}
namespace windowmanager
{
class Callback;
class WindowManagerDriver;
namespace input
{

class MovementDrivenDevice : public core::drivermodel::Driver
{
	friend class windowmanager::WindowManagerDriver;

public:
	virtual EString	id() const = 0;

	virtual bool 	isRelativeCaptureSupported() = 0;
	virtual void	relativeState(int* x,int* y) = 0;

	virtual bool	isAbsoluteCaptureSupported() = 0;
	virtual void	absoluteState(int* x,int* y) = 0;

	virtual void setMode(unsigned mode) = 0;//Set processing mode
	virtual void registerCallback(const windowmanager::Callback& callback) = 0;//For event-based mode

};

}
}

#endif /* MOVEMENTDRIVENDEVICE_H_ */
