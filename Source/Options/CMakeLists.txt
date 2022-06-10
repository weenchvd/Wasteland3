
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for Options
set(OPTIONS_FB_FILE_STEM "optionsFB")
set(OPTIONS_FB_BIN_FILE_IDENTIFIER "OPTS")
set(OPTIONS_FB_SCHEMA_FILE_EXTENSION "${FB_SCHEMA_FILE_EXTENSION}")
set(OPTIONS_FB_SCHEMA_FILE_NAME "${OPTIONS_FB_FILE_STEM}.${OPTIONS_FB_SCHEMA_FILE_EXTENSION}")
file(REAL_PATH "${OPTIONS_FB_SCHEMA_FILE_NAME}" OPTIONS_FB_SCHEMA_FILE)

cmake_language(CALL create_file "${OPTIONS_FB_SCHEMA_FILE_NAME}.in")
configure_file("${OPTIONS_FB_SCHEMA_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${OPTIONS_FB_SCHEMA_FILE_NAME}"
)
file(REAL_PATH "${OPTIONS_FB_FILE_STEM}_${FB_BATCH_FILE_STEM_SUFFIX_FBS_TO_CPP}.${FB_BATCH_FILE_EXTENSION}"
                OPTIONS_FB_BATCH_FBS_TO_CPP_FILE
)
file(REAL_PATH "${FB_INCLUDE_DIR}" OPTIONS_FB_INCLUDE_DIR)
file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" OPTIONS_FB_CPP_OUTPUT_DIR)
if(WIN32)
  cmake_language(CALL create_batch_fbs_to_cpp
    "${OPTIONS_FB_BATCH_FBS_TO_CPP_FILE}"
    "${TEMPLATE_BUILD_FBS_TO_CPP_BATCH_FILE}"
    "${OPTIONS_FB_SCHEMA_FILE}"
    "${OPTIONS_FB_INCLUDE_DIR}"
    "${OPTIONS_FB_CPP_OUTPUT_DIR}"
  )
endif()

#**********************************************************************
include(generateSchemaHeader.cmake)

#**********************************************************************
set(LIBRARY_NAME "options")
set(SOURCE_CXX_LIST "options.cpp"
                    "optionsAux.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC locator
                      PUBLIC observer
)

if(WIN32)
  target_include_directories(${LIBRARY_NAME} PUBLIC "${BOOST_LIB_INCLUDE_DIR}/boost-1_79")
  target_link_libraries(${LIBRARY_NAME} PUBLIC "${BOOST_LIB_LIST}")
endif()
