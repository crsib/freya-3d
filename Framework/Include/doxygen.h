/*
 * doxygen.h
 *
 *  Created on: 12.02.2009
 *      Author: vedenko
 */

#ifndef DOXYGEN_H_
#define DOXYGEN_H_
//This file is provided only for doxygen and should be never included
/*!
 * \mainpage Freya 3D engine. Implementation specific notes.
 * \section home_sec Freya 3D engine home page
 * <A href="http://freya3d.co.cc/">Project home page</A>
 * \section source_sec Freya 3D engine source
 * The source code is available via svn from <br />
 * <A href="http://svn.freya3d.co.cc/freya/trunk/engine">http://svn.freya3d.co.cc/EnjoyInc/Framework</A>
 * \section depends_sec Dependencies
 * <OL>
 * <LI>boost.filesystem 1.37.0 (it depends on boost.system 1.37.0)</LI>
 * <LI>Lua 5.1.4 or LuaJIT 1.1.5 (note: to enable JIT engine usage define LUA_JIT_AVAILABLE) </LI>
 * <LI>xerces-c++ 3.0</LI>
 * <LI>OpenGL 2.1</LI>
 * <LI>SDL 1.3 (svn version)</LI>
 * </OL>
 * \section filesys_sec Filesystem notes
 * Currently implemented drivers:
 * <TABLE border="1">
 * <TR><TH>Driver ID:</TH><TH>Library used:</TH><TH>Writable:</TH><TH>Notes:</TH></TR>
 * <TR><TD>local</TD><TD>boost.filesytem 1.37.0</TD><TD>true</TD><TD>Possibly not all exception are intercepted, more testing needed</TD></TR>
 * <TR><TD>lzma</TD><TD>original 7zip sdk from official 7zip site</TD><TD>false</TD><TD>Requires legal lzma archive as mount point.</TD></TR>
 * <TR><TD>app-home</TD><TD>implemented over local driver</TD><TD>true</TD><TD>Mounts {current users home}/team-name/app-name directory. No mount point needed.<BR/> Probably not fully portable </TD></TR>
 * <TR><TD>pwd</TD><TD>implemented over local driver</TD><TD>true</TD><TD>Mounts pwd directory. No mount point needed. </TD></TR>
 * </TABLE>
 */

#endif /* DOXYGEN_H_ */
