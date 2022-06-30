CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PA2 CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PATH(OPENGL_INCLUDE_SUBDIR
        NAMES gl.h
        PATHS ${OPENGL_INCLUDE_DIR}
        PATH_SUFFIXES GL OpenGL Headers
        NO_DEFAULT_PATH)

FIND_PACKAGE(GLUT REQUIRED)
FIND_PATH(GLUT_INCLUDE_SUBDIR
        NAMES glut.h
        PATHS ${GLUT_INCLUDE_DIR}
        PATH_SUFFIXES GL GLUT Headers
        NO_DEFAULT_PATH)

ADD_SUBDIRECTORY(deps/vecmath)

SET(PA2_SOURCES
        src/image.cpp
        src/main.cpp
        src/mesh.cpp
        src/scene_parser.cpp
        src/camera_controller.cpp)

SET(PA2_INCLUDES
        include/camera.hpp
        include/group.hpp
        include/hit.hpp
        include/image.hpp
        include/light.hpp
        include/material.hpp
        include/mesh.hpp
        include/object3d.hpp
        include/plane.hpp
        include/ray.hpp
        include/scene_parser.hpp
        include/sphere.hpp
        include/transform.hpp
        include/triangle.hpp
        include/camera_controller.hpp
        include/curve.hpp
        include/revsurface.hpp)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g -O3 -Wno-deprecated-declarations")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} ${PA2_SOURCES} ${PA2_INCLUDES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} vecmath ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE include ${OPENGL_INCLUDE_SUBDIR}  ${GLUT_INCLUDE_SUBDIR})
