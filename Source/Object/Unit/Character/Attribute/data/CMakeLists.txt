
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(PATH_TO_FILES "W3_Data/Assets")

configure_file("attribute.bundle"
               "${CMAKE_BINARY_DIR}/Source/Main/${PATH_TO_FILES}/attribute.bundle"
               COPYONLY
)

# Add tests and install targets if needed.
install(FILES "attribute.bundle" DESTINATION "${CMAKE_BUILD_TYPE}/${PATH_TO_FILES}")
