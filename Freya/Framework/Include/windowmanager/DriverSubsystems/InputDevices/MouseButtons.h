/*
 * MouseKeys.h
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#ifndef MOUSEKEYS_H_
#define MOUSEKEYS_H_

namespace windowmanager
{
namespace input
{
extern const char* MouseButtonsNames [7];

enum MouseButtons
{
	BUTTON_LEFT = 1,
	BUTTON_MIDDLE,
	BUTTON_RIGT,
	BUTTON_WHEEL_UP,
	BUTTON_WHEEL_DOWN,
};

}
}


#endif /* MOUSEKEYS_H_ */
