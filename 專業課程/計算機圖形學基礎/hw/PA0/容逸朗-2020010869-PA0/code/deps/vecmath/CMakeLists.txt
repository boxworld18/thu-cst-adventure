CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(vecmath CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

SET(VECMATH_INCLUDES
        include/Matrix2f.h
        include/Matrix3f.h
        include/Matrix4f.h
        include/Quat4f.h
        include/vecmath.h
        include/Vector2f.h
        include/Vector3f.h
        include/Vector4f.h)

SET(VECMATH_SOURCES
        src/Matrix2f.cpp
        src/Matrix3f.cpp
        src/Matrix4f.cpp
        src/Quat4f.cpp
        src/Vector2f.cpp
        src/Vector3f.cpp
        src/Vector4f.cpp)

SET(CMAKE_CXX_STANDARD 11)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${VECMATH_INCLUDES} ${VECMATH_SOURCES})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC include)
