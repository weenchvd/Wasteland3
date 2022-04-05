
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for PlainTextText
set(PLAINTEXT_TEXT_FB_FILE_STEM "plainTextTextFB")
set(PLAINTEXT_TEXT_FB_BIN_FILE_IDENTIFIER "PT_T")
set(PLAINTEXT_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(PLAINTEXT_TEXT_FB_BIN_FILE_NAME "${PLAINTEXT_TEXT_FB_FILE_STEM}.${PLAINTEXT_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${PLAINTEXT_TEXT_FB_BIN_FILE_NAME}" PLAINTEXT_TEXT_FB_BIN_FILE)
file(RELATIVE_PATH PLAINTEXT_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${PLAINTEXT_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH PLAINTEXT_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                PLAINTEXT_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT PLAINTEXT_TEXT_FB_BIN_FILE_NAME__OUT
  "${PLAINTEXT_TEXT_FB_FILE_STEM}_${PLAINTEXT_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${PLAINTEXT_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${PLAINTEXT_TEXT_FB_BIN_FILE_NAME__OUT}"
  PLAINTEXT_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${PLAINTEXT_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${PLAINTEXT_TEXT_FB_BIN_FILE_EXTENSION}"
  "${PLAINTEXT_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${PLAINTEXT_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${PLAINTEXT_TEXT_FB_BIN_FILE_NAME__OUT}"
)

#**********************************************************************
# create header file with paths
set(PLAINTEXT_PATH_FILE_NAME "plainTextPath.hpp")
cmake_language(CALL create_file "${PLAINTEXT_PATH_FILE_NAME}.in")
configure_file("${PLAINTEXT_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${PLAINTEXT_PATH_FILE_NAME}"
)

#**********************************************************************
set(LIBRARY_NAME "plainText")
set(SOURCE_CXX_LIST "plainText.cpp"
                    "plainTextBase.cpp"
                    "plainTextText.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC flatbuffersAux
                      PUBLIC flatbuffersCommon
                      PUBLIC locator
                      PUBLIC observer
)
