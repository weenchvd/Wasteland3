
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ATTRIBUTE_FB_FILE_IDENTIFIER "ATTR")
set(ATTRIBUTE_FB_FILE_STEM "attribute")
set(ATTRIBUTE_FB_FILE_EXTENSION "bundle")
set(ATTRIBUTE_FB_FILENAME "${ATTRIBUTE_FB_FILE_STEM}.${ATTRIBUTE_FB_FILE_EXTENSION}")

set(RELATIVE_PATH_TO_ASSETS "W3_Data/Assets")

file(TO_NATIVE_PATH
     "${RELATIVE_PATH_TO_ASSETS}/${ATTRIBUTE_FB_FILENAME}"
     ATTRIBUTE_FB_FILENAME_WITH_NATIVE_RELATIVE_PATH
)

configure_file(attributePath.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/attributePath.hpp")
configure_file(attribute.fbs.in "${CMAKE_CURRENT_SOURCE_DIR}/attribute.fbs")

add_subdirectory("data")
