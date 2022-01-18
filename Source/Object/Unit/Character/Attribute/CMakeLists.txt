
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(RELATIVE_PATH_TO_ASSETS "W3_Data/Assets")

#**********************************************************************
set(ATTRIBUTE_REF_FB_FILE_IDENTIFIER "ATTR")
set(ATTRIBUTE_REF_FB_FILE_STEM "attribute-ref")
set(ATTRIBUTE_REF_FB_FILE_EXTENSION "bundle")
set(ATTRIBUTE_REF_FB_FILENAME "${ATTRIBUTE_REF_FB_FILE_STEM}.${ATTRIBUTE_REF_FB_FILE_EXTENSION}")

file(TO_NATIVE_PATH
     "${RELATIVE_PATH_TO_ASSETS}/${ATTRIBUTE_REF_FB_FILENAME}"
     ATTRIBUTE_REF_FB_FILENAME_WITH_NATIVE_RELATIVE_PATH
)
configure_file(${ATTRIBUTE_REF_FB_FILE_STEM}.fbs.in
               "${CMAKE_CURRENT_SOURCE_DIR}/${ATTRIBUTE_REF_FB_FILE_STEM}.fbs")

#**********************************************************************
set(ATTRIBUTE_TEXT_FB_FILE_IDENTIFIER "ATTT")
set(ATTRIBUTE_TEXT_FB_FILE_STEM "attribute-text")
set(ATTRIBUTE_TEXT_FB_FILE_EXTENSION "bundle")
set(ATTRIBUTE_TEXT_FB_FILENAME "${ATTRIBUTE_TEXT_FB_FILE_STEM}.${ATTRIBUTE_TEXT_FB_FILE_EXTENSION}")

file(TO_NATIVE_PATH
     "${RELATIVE_PATH_TO_ASSETS}/${ATTRIBUTE_TEXT_FB_FILENAME}"
     ATTRIBUTE_TEXT_FB_FILENAME_WITH_NATIVE_RELATIVE_PATH
)
configure_file(${ATTRIBUTE_TEXT_FB_FILE_STEM}.fbs.in
               "${CMAKE_CURRENT_SOURCE_DIR}/${ATTRIBUTE_TEXT_FB_FILE_STEM}.fbs")

#**********************************************************************
configure_file(attributePath.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/attributePath.hpp")

add_subdirectory("data")
