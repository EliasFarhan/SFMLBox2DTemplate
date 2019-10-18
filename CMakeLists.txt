cmake_minimum_required(VERSION 3.9)
project(PLATFORMER)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PLATFORMER_SRC src/*.cpp include/*.h)

include_directories(include/)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:RelWithDebInfo>:/MTd>
		$<$<CONFIG:Release>:/MT> #--|
    )
endif()

#SFML
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
set(BUILD_SHARED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_BUILD_EXAMPLES FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include)

LIST(APPEND PLATFORMER_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network)
#Box2D
set(BOX2D_DIR ${EXTERNAL_DIR}/Box2D)

SET(BOX2D_INSTALL ON CACHE INTERNAL "")
SET(BOX2D_BUILD_STATIC ON  CACHE INTERNAL "")

add_subdirectory(${BOX2D_DIR})
include_directories(${BOX2D_DIR}/)
LIST(APPEND PLATFORMER_LIBRARIES
	Box2D)
add_executable(PLATFORMER ${PLATFORMER_SRC})
target_link_libraries(PLATFORMER ${PLATFORMER_LIBRARIES})

if(MSVC)
if(NOT CMAKE_CL_64)
file(COPY ${SFML_DIR}/extlibs/bin/x86/openal32.dll DESTINATION ${CMAKE_BINARY_DIR}/)
else()
file(COPY ${SFML_DIR}/extlibs/bin/x64/openal32.dll DESTINATION ${CMAKE_BINARY_DIR}/)
endif()
endif()
