
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
set(INTERFACE_LIBRARY_NAME "commonI")
set(HEADER_CXX_LIST "common.hpp"
                    "distribution.hpp"
                    "slot.hpp"
                    "specStorage.hpp"
)

add_library(${INTERFACE_LIBRARY_NAME} INTERFACE ${HEADER_CXX_LIST})

target_include_directories(${INTERFACE_LIBRARY_NAME}
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

#**********************************************************************
set(LIBRARY_NAME "common")
set(SOURCE_CXX_LIST "exception.cpp")

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      INTERFACE commonI
)

#**********************************************************************
add_subdirectory("FlatBuffersAux")
add_subdirectory("FlatBuffersCommon")
add_subdirectory("Observer")
