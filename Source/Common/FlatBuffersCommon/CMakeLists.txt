
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers schema file for FB_LanguageBundle
set(LANGUAGE_BUNDLE_FB_FILE_STEM "languageBundleFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${LANGUAGE_BUNDLE_FB_FILE_STEM}"
)

#**********************************************************************
set(LIBRARY_NAME "flatbuffersCommon")
set(HEADER_CXX_LIST "${LANGUAGE_BUNDLE_FB_FILE_STEM}_generated.h")

add_library(${LIBRARY_NAME} INTERFACE ${HEADER_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      INTERFACE flatbuffers
)
