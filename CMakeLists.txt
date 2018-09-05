cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(openglengine)

find_package(OpenGL REQUIRED)
IF (WIN32)
  list(APPEND CMAKE_PREFIX_PATH "C:/Program Files (x86)/glew")
ENDIF()

find_package(GLEW REQUIRED)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${ROOT_DIR}/src)

add_subdirectory(${ROOT_DIR}/extern/glfw-3.2.1)

set(INCLUDE_DIRS
  ${ROOT_DIR}/include/
  ${ROOT_DIR}/extern/glm/
  ${GLEW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  /usr/include/
  )

include_directories(${INCLUDE_DIRS})

set(SRC
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/camera.cpp
  ${SRC_DIR}/baseGame.cpp
  ${SRC_DIR}/shader.cpp
  ${SRC_DIR}/model.cpp
  ${SRC_DIR}/debug.cpp
  ${SRC_DIR}/renderer.cpp
  ${SRC_DIR}/vertex.cpp
  ${SRC_DIR}/modelLoader.cpp
  ${SRC_DIR}/vertexBuffer.cpp
  ${SRC_DIR}/texture.cpp
  )

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  ${GLEW_LIBRARIES}
  glfw
  )

IF (WIN32)
  set( CMAKE_CXX_FLAGS "-std=c++11")
ELSE ()
  set( CMAKE_CXX_FLAGS "-g -W -Wall -std=c++11 -lGL -lGLU -lGLEW")
ENDIF()

add_executable(openglengine ${SRC})
target_link_libraries(openglengine ${ALL_LIBS})
