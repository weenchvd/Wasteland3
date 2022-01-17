
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

configure_file("${ATTRIBUTE_FB_FILENAME}"
               "${CMAKE_BINARY_DIR}/Source/Main/${RELATIVE_PATH_TO_ASSETS}/${ATTRIBUTE_FB_FILENAME}"
               COPYONLY
)

# Add tests and install targets if needed.
install(FILES "${ATTRIBUTE_FB_FILENAME}" DESTINATION "${CMAKE_BUILD_TYPE}/${RELATIVE_PATH_TO_ASSETS}")
