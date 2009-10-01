# Locate SDL 1.3 library
# This module defines
# SDL_LIBRARY, the name of the library to link against
# SDL_FOUND, if false, do not try to link to SDL
# SDL_INCLUDE_DIR, where to find SDL.h
# If this is defined, then no SDL_main will be linked in because 
# only applications need main().
# Otherwise, it is assumed you are building an application and this
# module will attempt to locate and set the the proper link flags
# as part of the returned SDL_LIBRARY variable.
#
# Don't forget to include SDLmain.h and SDLmain.m your project for the 
# OS X framework based version. (Other versions link to -lSDLmain which
# this module will try to find on your behalf.) Also for OS X, this 
# module will automatically add the -framework Cocoa on your behalf.
#
#
# Additional Note: If you see an empty SDL_LIBRARY_TEMP in your configuration
# and no SDL_LIBRARY, it means CMake did not find your SDL library 
# (SDL.dll, libsdl.so, SDL.framework, etc). 
# Set SDL_LIBRARY_TEMP to point to your SDL library, and configure again. 
# Similarly, if you see an empty SDLMAIN_LIBRARY, you should set this value
# as appropriate. These values are used to generate the final SDL_LIBRARY
# variable, but when these values are unset, SDL_LIBRARY does not get created.
#
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
# l.e.galup  9-20-02
#
# Modified by Eric Wing. 
# Added code to assist with automated building by using environmental variables
# and providing a more controlled/consistent search behavior.
# Added new modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc). 
# Also corrected the header search path to follow "proper" SDL guidelines.
# Added a search for SDLmain which is needed by some platforms.
# Added a search for threads which is needed by some platforms.
# Added needed compile switches for MinGW.
#
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of 
# SDL_LIBRARY to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# Note that the header path has changed from SDL/SDL.h to just SDL.h
# This needed to change because "proper" SDL convention
# is #include "SDL.h", not <SDL/SDL.h>. This is done for portability
# reasons because not all systems place things in SDL/ (see FreeBSD).

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

# This file was higly modified by Dmitry crsib Vedenko to provide proper search for sdl 1.3.0+ library
IF( NOT WIN32 )
	SET(SDL_CONFIG_SEARCH_PATHS $ENV{SDLDIR}/bin /usr/local/bin /usr/bin /opt/bin /opt/local/bin)
	#MESSAGE("Searching for sdl-config in: ${SDL_CONFIG_SEARCH_PATHS}")
	FOREACH(CHECK_PATH ${SDL_CONFIG_SEARCH_PATHS})
		#MESSAGE("Checking ${CHECK_PATH}")
		FIND_PROGRAM(SDL_CONFIG sdl-config PATHS ${CHECK_PATH} NO_DEFAULT_PATH)
		#MESSAGE("Result: ${SDL_CONFIG}")
		IF(NOT SDL_CONFIG)
			#MESSAGE("sdl-config not found, continue searching")
		ELSE(NOT SDL_CONFIG)
			#MESSAGE("Checking found version")
			EXECUTE_PROCESS(COMMAND ${SDL_CONFIG} --version OUTPUT_VARIABLE SDL_VERSION)
			IF(SDL_VERSION VERSION_LESS 1.3)
				#MESSAGE("Wrong SDL version ${VERSION}")
				SET(SDL_CONFIG SDL_CONFIG-NOTFOUND)
			ELSE(SDL_VERSION VERSION_LESS 1.3)
				BREAK()
			ENDIF(SDL_VERSION VERSION_LESS 1.3)
		ENDIF(NOT SDL_CONFIG)
		
	ENDFOREACH(CHECK_PATH)
	IF(SDL_CONFIG)
		MESSAGE("Running sdl-config as ${SDL_CONFIG}")
		SET(SDL_FOUND YES)
		#Includes
		EXECUTE_PROCESS(COMMAND ${SDL_CONFIG} --cflags OUTPUT_VARIABLE SDL_OUTPUT)
		STRING(REGEX MATCHALL "-I[A-Za-z0-9/\\]+ " SDL_OUTPUT_1 ${SDL_OUTPUT})
		#MESSAGE("${SDL_OUTPUT_1}")
		STRING(REPLACE "-I" "" SDL_INCLUDE_DIR ${SDL_OUTPUT_1})
		#Libs
		EXECUTE_PROCESS(COMMAND ${SDL_CONFIG} --libs OUTPUT_VARIABLE SDL_OUTPUT)
		STRING(REGEX MATCHALL "-L[A-Za-z0-9/\\]+" SDL_OUTPUT_1 ${SDL_OUTPUT})
		#MESSAGE("${SDL_OUTPUT_1}")
		STRING(REPLACE "-L" "" SDL_OUTPUT ${SDL_OUTPUT_1})
		MESSAGE("${SDL_OUTPUT}")
		FIND_LIBRARY(SDL_LIBRARY NAMES SDL SDL-1.3 libSDL.so libSDL-1.3.so PATHS ${SDL_OUTPUT} NO_DEFAULT_PATH)
		IF(NOT SDL_LIBRARY)
			#hope for best
			IF(APPLE)
				SET(SDL_LIBRARY ${SDL_OUTPUT}/libSDL.dylib)
			ELSE()
				SET(SDL_LIBRARY ${SDL_OUTPUT}/libSDL.so)
			ENDIF()	
		ENDIF()
		UNSET(SDL_OUTPUT)
		UNSET(SDL_OUTPUT_1)
	ELSE(SDL_CONFIG)
		MESSAGE("SDL 1.3 is not found. Please install it. Alternatively set SDLDIR enviroment variable pointing to place where, you have installed SDL")
		SET(SDL_FOUND NO)
	ENDIF(SDL_CONFIG)
	
ELSE( )
	IF(DEFINED SDLDIR)
		
	ELSE(DEFINED SDLDIR )
		MESSAGE("Please, set SDLDIR in order to use SDL. ")
	ENDIF(DEFINED SDLDIR)
ENDIF(  )
