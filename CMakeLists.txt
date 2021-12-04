# Copyright(c) 2017-2021 Federico Bolelli, Costantino Grana
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met :
# 
# *Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and / or other materials provided with the distribution.
# 
# * Neither the name of YACCLAB nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.6)

set(ProjectName "AdaptiveWienerFilter")
project(${ProjectName} LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install prefix" FORCE)
add_executable(${ProjectName})

set_target_properties(${ProjectName} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectName})
endif()

# Save libs and executables in the same place
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" CACHE PATH "Output directory for applications")

# --------------------
# OpenCV
# --------------------
find_package(OpenCV REQUIRED core imgcodecs imgproc)
if(OpenCV_VERSION VERSION_LESS 3)
    message(FATAL_ERROR "ERROR: Cannot find OpenCV 3.0+")
endif()
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

target_include_directories(${ProjectName} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${ProjectName} PUBLIC ${OpenCV_LIBS})


if(MSVC)
    if("${OpenCV_STATIC}" STREQUAL "ON" OR "${OpenCV_SHARED}" STREQUAL "OFF")
        message(STATUS "Setting static runtime for MSVC")
        foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO) 
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endforeach(flag_var)
    endif()
endif()

# --------------------
# Project
# --------------------
target_include_directories(${ProjectName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(${ProjectName} PRIVATE WienerFilter.h WienerFilter.cpp ExampleMain.cpp)

# Copy example image in the installation path folder
file(COPY "${CMAKE_SOURCE_DIR}/ExampleImage.jpg" DESTINATION ${CMAKE_INSTALL_PREFIX})