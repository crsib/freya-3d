INCLUDE_DIRECTORIES( Framework/Include/math )

#
SET ( MATH_SOURCES 
${CMAKE_SOURCE_DIR}/Framework/Source/math/math.cpp 


${CMAKE_SOURCE_DIR}/Framework/Include/math/constants.h
${CMAKE_SOURCE_DIR}/Framework/Include/math/math_internal.h
${CMAKE_SOURCE_DIR}/Framework/Include/math/frustum.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/math.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/matrix2x2.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/matrix3x3.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/matrix4x4.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/plane.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/quaternion.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/vector2d.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/vector3d.hpp
${CMAKE_SOURCE_DIR}/Framework/Include/math/vector4d.hpp


${INTERMIDIATE_DIRECTORY}/math_lookup_tables.cpp
) 

SET_SOURCE_FILES_PROPERTIES("${INTERMIDIATE_DIRECTORY}/math_lookup_tables.cpp" PROPERTIES GENERATED YES)

MESSAGE(STATUS "Generating lookup tables. Writing to ${INTERMIDIATE_DIRECTORY}" )

ADD_CUSTOM_COMMAND(OUTPUT ${INTERMIDIATE_DIRECTORY}/math_lookup_tables.cpp ${INTERMIDIATE_DIRECTORY}/math_lookup_tables.h
                    COMMAND ${LUA_APP} ${GENERATORS_DIRECTORY}/generate_math_lookups.lua
                    DEPENDS ${GENERATORS_DIRECTORY}/generate_math_lookups.lua
                    WORKING_DIRECTORY ${INTERMIDIATE_DIRECTORY} 
                    VERBATIM)
#EXECUTE_PROCESS(COMMAND ${LUA_APP} ${GENERATORS_DIRECTORY}/generate_math_lookups.lua 
#                            WORKING_DIRECTORY ${INTERMIDIATE_DIRECTORY} 
#                            OUTPUT_VARIABLE LUA_OUT ERROR_VARIABLE LUA_ERROR)
MESSAGE(STATUS "Done generating math tables\n\tOutput: ${LUA_OUT}\n\tErrors: ${LUA_ERROR}" )

ADD_LIBRARY(FreyaMath_core STATIC ${MATH_SOURCES})
ADD_DEFINITIONS( -D_FREYA_SHARED_PLUGIN )
ADD_LIBRARY(FreyaMath_plugin STATIC ${MATH_SOURCES})
REMOVE_DEFINITIONS( -D_FREYA_SHARED_PLUGIN )