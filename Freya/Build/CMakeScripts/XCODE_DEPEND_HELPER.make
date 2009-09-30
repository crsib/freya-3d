# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to, avoiding a bug in XCode 1.5
all.Debug: \
	/Developement/Projects/Freya/bin/Debug/ResourcesTest.app/Contents/MacOS/ResourcesTest\
	/Developement/Projects/Freya/bin/Debug/BumpMapping.app/Contents/MacOS/BumpMapping

all.Release: \
	/Developement/Projects/Freya/bin/Release/ResourcesTest.app/Contents/MacOS/ResourcesTest\
	/Developement/Projects/Freya/bin/Release/BumpMapping.app/Contents/MacOS/BumpMapping

all.MinSizeRel: \
	/Developement/Projects/Freya/bin/MinSizeRel/ResourcesTest.app/Contents/MacOS/ResourcesTest\
	/Developement/Projects/Freya/bin/MinSizeRel/BumpMapping.app/Contents/MacOS/BumpMapping

all.RelWithDebInfo: \
	/Developement/Projects/Freya/bin/RelWithDebInfo/ResourcesTest.app/Contents/MacOS/ResourcesTest\
	/Developement/Projects/Freya/bin/RelWithDebInfo/BumpMapping.app/Contents/MacOS/BumpMapping

# For each target create a dummy rule so the target does not have to exist
/usr/lib/libboost_filesystem.a:
/usr/lib/libboost_system.a:
/usr/lib/libboost_thread.a:
/usr/lib/libboost_date_time.a:
/usr/local/lib/libstlport.dylib:
/usr/lib/libSDLmain.a:
/usr/lib/libSDL.dylib:
/Developement/Projects/Freya/bin/static/Debug/libFreyaCore.a:
/Developement/Projects/Freya/bin/static/MinSizeRel/libFreyaCore.a:
/Developement/Projects/Freya/bin/static/RelWithDebInfo/libFreyaCore.a:
/Developement/Projects/Freya/bin/static/Release/libFreyaCore.a:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
/Developement/Projects/Freya/bin/Debug/ResourcesTest.app/Contents/MacOS/ResourcesTest:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/Debug/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/Debug/ResourcesTest.app/Contents/MacOS/ResourcesTest


/Developement/Projects/Freya/bin/Debug/BumpMapping.app/Contents/MacOS/BumpMapping:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/Debug/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/Debug/BumpMapping.app/Contents/MacOS/BumpMapping


/Developement/Projects/Freya/bin/Release/ResourcesTest.app/Contents/MacOS/ResourcesTest:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/Release/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/Release/ResourcesTest.app/Contents/MacOS/ResourcesTest


/Developement/Projects/Freya/bin/Release/BumpMapping.app/Contents/MacOS/BumpMapping:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/Release/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/Release/BumpMapping.app/Contents/MacOS/BumpMapping


/Developement/Projects/Freya/bin/MinSizeRel/ResourcesTest.app/Contents/MacOS/ResourcesTest:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/MinSizeRel/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/MinSizeRel/ResourcesTest.app/Contents/MacOS/ResourcesTest


/Developement/Projects/Freya/bin/MinSizeRel/BumpMapping.app/Contents/MacOS/BumpMapping:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/MinSizeRel/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/MinSizeRel/BumpMapping.app/Contents/MacOS/BumpMapping


/Developement/Projects/Freya/bin/RelWithDebInfo/ResourcesTest.app/Contents/MacOS/ResourcesTest:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/RelWithDebInfo/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/RelWithDebInfo/ResourcesTest.app/Contents/MacOS/ResourcesTest


/Developement/Projects/Freya/bin/RelWithDebInfo/BumpMapping.app/Contents/MacOS/BumpMapping:\
	/usr/lib/libboost_filesystem.a\
	/usr/lib/libboost_system.a\
	/usr/lib/libboost_thread.a\
	/usr/lib/libboost_date_time.a\
	/usr/local/lib/libstlport.dylib\
	/usr/lib/libSDLmain.a\
	/usr/lib/libSDL.dylib\
	/Developement/Projects/Freya/bin/static/RelWithDebInfo/libFreyaCore.a
	/bin/rm -f /Developement/Projects/Freya/bin/RelWithDebInfo/BumpMapping.app/Contents/MacOS/BumpMapping


