/*
 * KeyDrivenDevice.h
 *
 *  Created on: 27.08.2008
 *      Author: vedenko
 */

#ifndef KEYDRIVENDEVICE_H_
#define KEYDRIVENDEVICE_H_

/*
 *
 */
#include "core/drivermodel/Driver.h"

namespace windowmanager
{
class WindowManagerDriver;
class Callback;
namespace input
{
namespace KeyAction
{
enum
{
	PRESSED,
	DOWN,
	UP
};
}


class KeyDrivenDevice: public core::drivermodel::Driver
{
	friend class windowmanager::WindowManagerDriver;

public:
	virtual EString id() const = 0;
	virtual bool getKeyState(unsigned Key) = 0;
	virtual void updateState() = 0; //Updates state
};

}
}

#endif /* KEYDRIVENDEVICE_H_ */
