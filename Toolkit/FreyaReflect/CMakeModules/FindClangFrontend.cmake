# FindClangFrontend - Find the clang frontendincludes and library.
#
# This module defines
#  CLANGFRONTEND_INCLUDE_DIR, where to find LLVM/clang headers.
#  CLANGFRONTEND_LIBRARY_DIR, where to find LLVM/clang libraries.
#  CLANGFRONTEND_FOUND, If false, do not try to use LLVM/clang.
#  LLVM_<libname> path to each LLVM static library.
#  CLANG_<libname> path to each Clang static library.
#  CLANGFRONTEND_LIBRARIES all libraries to be used in build

if (NOT CLANGFRONTEND_INCLUDE_DIR)
  find_path(CLANGFRONTEND_INCLUDE_DIR llvm/LinkAllVMCore.h DOC "Path to LLVM headers")
else (NOT CLANGFRONTEND_INCLUDE_DIR)
  set(CLANGFRONTEND_INCLUDE_DIR ${CLANGFRONTEND_INCLUDE_DIR} CACHE PATH "Path to LLVM headers")
endif (NOT CLANGFRONTEND_INCLUDE_DIR)

# Look for the library dir
if (NOT CLANGFRONTEND_LIBRARY_DIR)
  find_library( LLVM_TMP LLVMSupport )
  get_filename_component(CLANGFRONTEND_LIBRARY_DIR ${LLVM_TMP} PATH)
  #set(CLANGFRONTEND_LIBRARY_DIR ${LLVM_LIB_DIR} CACHE PATH "Path to LLVM Libraries")
endif (NOT CLANGFRONTEND_LIBRARY_DIR)

# Lib macro
# Find a LLVM libraries
macro(find_llvm_library Name ReleaseLibName DebugLibName)
	find_library(LLVM_${Name} ${ReleaseLibName} PATHS ${CLANGFRONTEND_LIBRARY_DIR} NO_DEFAULT_PATH)
	find_library(LLVM_${Name}_DEBUG ${DebugLibName} PATHS ${CLANGFRONTEND_LIBRARY_DIR} NO_DEFAULT_PATH)
  
	if(NOT LLVM_${Name})
		message( SEND_ERROR "Failed to find ${ReleaseLibName}!" )
	endif()
	
	if(LLVM_${Name}_DEBUG)
		set( CLANGFRONTEND_LIBRARIES ${CLANGFRONTEND_LIBRARIES} optimized ${LLVM_${Name}} debug ${LLVM_${Name}_DEBUG})
	else()
		set( LLVM_${Name}_DEBUG ${LLVM_${Name}})
		set( CLANGFRONTEND_LIBRARIES ${CLANGFRONTEND_LIBRARIES} ${LLVM_${Name}} )
	endif()
	
	mark_as_advanced(LLVM_${Name})
	mark_as_advanced(LLVM_${Name}_DEBUG)
endmacro(find_llvm_library)

# Find clang libraries
macro(find_clang_library Name ReleaseLibName DebugLibName)
	find_library(CLANG_${Name} ${ReleaseLibName} PATHS ${CLANGFRONTEND_LIBRARY_DIR} NO_DEFAULT_PATH)
	find_library(CLANG_${Name}_DEBUG ${DebugLibName} PATHS ${CLANGFRONTEND_LIBRARY_DIR} NO_DEFAULT_PATH)
  
	if(NOT CLANG_${Name})
		message( SEND_ERROR "Failed to find ${ReleaseLibName}!" )
	endif()
	
	if(CLANG_${Name}_DEBUG)
		set( CLANGFRONTEND_LIBRARIES ${CLANGFRONTEND_LIBRARIES} optimized ${CLANG_${Name}} debug ${CLANG_${Name}_DEBUG})
	else()
		set( CLANG_${Name}_DEBUG ${CLANG_${Name}})
		set( CLANGFRONTEND_LIBRARIES ${CLANGFRONTEND_LIBRARIES} ${CLANG_${Name}} )
	endif()
	
	mark_as_advanced(CLANG_${Name})
	mark_as_advanced(CLANG_${Name}_DEBUG)
endmacro(find_clang_library)

find_llvm_library(CORE LLVMCore LLVMCored)
#find_llvm_library(SYSTEM LLVMSystem LLVMSystem_d)
find_llvm_library(SUPPORT LLVMSupport LLVMSupportd)
find_llvm_library(MC LLVMMC LLVMMCd)
find_llvm_library(BITREADER LLVMBitReader LLVMBitReaderd)
find_llvm_library(BITWRITER LLVMBitWriter LLVMBitWriterd)

find_clang_library(ANALYSIS clangAnalysis clangAnalysisd)
find_clang_library(AST clangAST clangASTd)
find_clang_library(BASIC clangBasic clangBasicd)
find_clang_library(DRIVER clangDriver clangDriverd)
find_clang_library(FRONTEND clangFrontend clangFrontendd)
find_clang_library(LEX clangLex clangLexd)
find_clang_library(PARSE clangParse clangParsed)
find_clang_library(SEMA clangSema clangSemad)

mark_as_advanced(CLANGFRONTEND_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set LLVM_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CLANGFRONTEND DEFAULT_MSG CLANGFRONTEND_INCLUDE_DIR CLANGFRONTEND_LIBRARY_DIR)
