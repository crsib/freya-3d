/*
 * WindowFormat.h
 *
 *  Created on: Oct 12, 2009
 *      Author: crsib
 */

#ifndef WINDOWFORMAT_H_
#define WINDOWFORMAT_H_

#include "core/EngineSubsystem.h"

namespace windowmanager
{
//!Window format descriptor
struct WindowFormat: public EngineSubsystem
{
	WindowFormat();
	virtual ~WindowFormat(){}

	//! Size of red component in bits. (default is 8)
	int				RedSize;
	//! Size of green component in bits. (default is 8)
	int				GreenSize;
	//! Size of blue component in bits. (default is 8)
	int				BlueSize;
	//! Size of alpha channel in bits. (default is 8)
	int 			AlphaSize;
	//! Size of color buffer in bits. Normally equals to sum of rgba components. (default is 32)
	int				BufferSize;
	//! Size of depth buffer in bits. (default is 24)
	int				DepthSize;
	//! Size of stencil size		  (default is 8)
	int				StencilSize;
	//! true if context must have 3D acceleration (default is true)
	bool			Accelerated;
	//! true if context is double buffered (default is true)
	bool			Doublebuffered;
	//! true if vsync is needed (this option does not garantee either enabling or disabling of vsync) (default is false)
	bool			VSync;
	//! true if window is multisampled (default is false)
	bool			Multisampled;
	//! number of samples for MSAA     (default is 1)
	int				MultisampleSamples;


};

//============== Implementation =============
inline WindowFormat::WindowFormat()
{
	RedSize = GreenSize = BlueSize = AlphaSize 	= 8;
	BufferSize 									= 32;
	DepthSize  									= 24;
	StencilSize 								= 8;
	Accelerated = Doublebuffered				= true;
	VSync       = Multisampled					= false;
	MultisampleSamples							= 1;
}
}

#endif /* WINDOWFORMAT_H_ */
