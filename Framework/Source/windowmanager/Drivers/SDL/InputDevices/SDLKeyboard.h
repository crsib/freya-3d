/*
 * SDLKeyboard.h
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#ifndef SDLKEYBOARD_H_
#define SDLKEYBOARD_H_

/*
 *
 */

#include "windowmanager/DriverSubsystems/InputDevices/KeyDrivenDevice.h"

#include <map>
#include <core/memory/MemoryAllocator.h>

namespace windowmanager
{
class SDLManagerDriver;
namespace input
{
namespace drivers
{
namespace sdl
{

class InputDeviceFactory;

namespace ids
{
class SDLKeyboardID;
}

class SDLKeyboard: public windowmanager::input::KeyDrivenDevice
{
	friend class windowmanager::input::drivers::sdl::ids::SDLKeyboardID;
	friend class windowmanager::SDLManagerDriver;
private:
	SDLKeyboard();
	virtual ~SDLKeyboard();
public:
	virtual EString id() const;
	virtual bool getKeyState(unsigned Key);
	virtual void updateState(); //Updates state


	//For normal mode
	//First argument is KeyAction, second - Key ID
	virtual void registerCallback(unsigned Key,const Callback& callback);
	virtual void dropCallback(unsigned Key);

	virtual void setMode(unsigned mode);//Set processing mode
	virtual void registerCallback(const Callback& callback);//For event-based mode
private:
	unsigned char 		m_KeyboardState[512];

	unsigned 			m_Mode;
	//The following data part is affect in event mode only
	Callback*			m_Callback;		   //Default callback
	unsigned			m_LastUpdateTime;  //Last update time (for simulate repeating)
	unsigned			m_SavedState[512]; //This state controls previous key state
	//These are callbacks for handling some keys in normal mode
	class KeyCallback : public EngineSubsystem
	{
		unsigned 		m_LastUpdate;
		Callback* 		m_Callback;
		unsigned		m_WasPressed;
	public:
		KeyCallback();
		virtual ~KeyCallback();


	};
	typedef	std::map<unsigned, Callback*, std::less<unsigned>, core::memory::MemoryAllocator<std::pair<const unsigned, Callback*> > > CallbackMap;
	CallbackMap			m_KeyCallbacks;

};

}
}
}
}
#endif /* SDLKEYBOARD_H_ */
