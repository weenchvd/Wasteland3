
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(REL_PATH_TO_ASSETS "W3_Data/Assets")

configure_file(attributePath.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/attributePath.hpp")
