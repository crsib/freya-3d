/*
 * DisplayMode.h
 *
 *  Created on: Oct 12, 2009
 *      Author: crsib
 */

#ifndef DISPLAYMODE_H_
#define DISPLAYMODE_H_

#include "core/EngineSubsystem.h"

namespace windowmanager
{
//! Display mode. Contains driver specific info, thus must first be requested from the WindowManagerDriver
struct	DisplayMode : public ::EngineSubsystem
{
	DisplayMode() : width(0),height(0),refreshRate(0),id(-1)
		{}
	//! width of a display
	unsigned width;
	//! height of a display
	unsigned height;
	//! Refresh rate
	unsigned refreshRate;
	//! Driver specific ID
	unsigned id;
};

}

#endif /* DISPLAYMODE_H_ */
