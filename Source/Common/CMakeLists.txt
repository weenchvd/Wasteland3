
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "common")
set(HEADER_CXX_LIST "common.hpp"
                    "distribution.hpp"
                    "slot.hpp"
                    "specStorage.hpp"
)

add_library(${LIBRARY_NAME} INTERFACE ${HEADER_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory("FlatBuffersAux")
add_subdirectory("Observer")
