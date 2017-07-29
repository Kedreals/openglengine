cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(openglengine)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
  message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
  message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)
link_libraries(${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})
#########################################################
# Include Files
#########################################################

set( ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set( SRC_DIR ${ROOT_DIR}/src)

set( SOURCE
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/vec3.cpp
)

set( INCLUDE_DIR ${ROOT_DIR}/include usr/include)

IF(WIN32)
  
ELSE()
  set( CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11 -IGL -IGLEW")
ENDIF()

set(CMAKE_CXX_FLAGSE_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -02")

include_directories(${INCLUDE_DIR})
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(openglengine ${SOURCE})
#SET_TARGET_PROPERTIES(openglengine PROPERTIES LINKER_LANGUAGE CXX)
########################################################
# Linking & stuff
#########################################################
# create the program
target_link_libraries(openglengine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} )
