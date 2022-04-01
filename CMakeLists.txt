
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

project("Wasteland3"  VERSION 0.2.0)

option(GAME_ENABLE_TEST "Enable tests for game" OFF)



#set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/Install")

#**********************************************************************
set(W3EXEC__BIN_DIR "${CMAKE_BINARY_DIR}/Source/Main")
set(W3DATA__DIR__REL_PATH_FROM_W3EXEC "W3_data")
set(SYSTEM__DIR__REL_PATH_FROM_W3EXEC "${W3DATA__DIR__REL_PATH_FROM_W3EXEC}/System")
set(ASSETS__DIR__REL_PATH_FROM_W3EXEC "${W3DATA__DIR__REL_PATH_FROM_W3EXEC}/Assets")

set(FB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Source/Common/FlatBuffersCommon")
set(FB_DATA_DIR_NAME "data")
set(FB_BIN_FILE_EXTENSION "bundle")
set(FB_BATCH_FILE_EXTENSION "bat")
set(FB_SCHEMA_FILE_EXTENSION "fbs")

#**********************************************************************
set(TEMPLATE_FILES_DIR_NAME "Files")
set(FB_BATCH_FILE_STEM_SUFFIX_FBS_TO_CPP "build-fbs-to-cpp")
set(FB_BATCH_FILE_STEM_SUFFIX_JSON_TO_BIN "build-json-to-bin")
set(FB_BATCH_FILE_STEM_SUFFIX_BIN_TO_JSON "build-bin-to-json")

file(REAL_PATH "${TEMPLATE_FILES_DIR_NAME}/build-fbs-to-cpp.bat" BUILD_FBS_TO_CPP_REAL_PATH)
set(TEMPLATE_BUILD_FBS_TO_CPP_BATCH_FILE ${BUILD_FBS_TO_CPP_REAL_PATH})

file(REAL_PATH "${TEMPLATE_FILES_DIR_NAME}/build-json-to-bin.bat" BUILD_JSON_TO_BIN_REAL_PATH)
set(TEMPLATE_BUILD_JSON_TO_BIN_BATCH_FILE ${BUILD_JSON_TO_BIN_REAL_PATH})

file(REAL_PATH "${TEMPLATE_FILES_DIR_NAME}/build-bin-to-json.bat" BUILD_BIN_TO_JSON_REAL_PATH)
set(TEMPLATE_BUILD_BIN_TO_JSON_BATCH_FILE ${BUILD_BIN_TO_JSON_REAL_PATH})

#**********************************************************************
function(create_file _file_name)
  file(REAL_PATH "${_file_name}" file_)
  if (NOT EXISTS ${file_})
    file(WRITE ${file_} "")
  endif()
endfunction()

function(distribute_file _file _relative_path _new_file_name)
  if (EXISTS "${_file}")
    configure_file("${_file}"
                   "${W3EXEC__BIN_DIR}/${_relative_path}/${_new_file_name}"
                   COPYONLY
    )
    install(FILES "${_file}"
            DESTINATION "${CMAKE_BUILD_TYPE}/${_relative_path}"
            RENAME "${_new_file_name}"
    )
  endif()
endfunction()

function(create_batch_fbs_to_cpp _output_file _template_file _schema_files _include_dir _output_dir)
  set(VAR_INCLUDE_DIR "${_include_dir}")
  set(VAR_OUTPUT_DIR "${_output_dir}")
  set(VAR_SCHEMA_FILES "${_schema_files}")
  file(READ "${_template_file}" content_temp_)
  string(CONFIGURE "${content_temp_}" content_temp_)
  file(GENERATE OUTPUT "${_output_file}" CONTENT "${content_temp_}")
endfunction()

function(create_batch_json_to_bin _output_file _template_file _schema_files _include_dir _output_dir _json_file)
  set(VAR_INCLUDE_DIR "${_include_dir}")
  set(VAR_OUTPUT_DIR "${_output_dir}")
  set(VAR_SCHEMA_FILES "${_schema_files}")
  set(VAR_JSON_FILE "${_json_file}")
  file(READ "${_template_file}" content_temp_)
  string(CONFIGURE "${content_temp_}" content_temp_)
  file(GENERATE OUTPUT "${_output_file}" CONTENT "${content_temp_}")
endfunction()

function(create_batch_bin_to_json _output_file _template_file _schema_files _include_dir _output_dir _binary_file)
  set(VAR_INCLUDE_DIR "${_include_dir}")
  set(VAR_OUTPUT_DIR "${_output_dir}")
  set(VAR_SCHEMA_FILES "${_schema_files}")
  set(VAR_BIN_FILE "${_binary_file}")
  file(READ "${_template_file}" content_temp_)
  string(CONFIGURE "${content_temp_}" content_temp_)
  file(GENERATE OUTPUT "${_output_file}" CONTENT "${content_temp_}")
endfunction()

function(create_flatbuffers_data_files _bin_file_identifier _bin_file_extension _fb_file_stem)
  set(VAR_FB_BIN_FILE_IDENTIFIER "${_bin_file_identifier}")
  set(VAR_FB_BIN_FILE_EXTENSION "${_bin_file_extension}")

  set(fb_schema_file_name_ "${_fb_file_stem}.${FB_SCHEMA_FILE_EXTENSION}")
  set(fb_json_file_name_ "${_fb_file_stem}.json")
  set(fb_bin_file_name_ "${_fb_file_stem}.${_bin_file_extension}")

  file(REAL_PATH "${fb_schema_file_name_}" fb_schema_file_)
  file(REAL_PATH "${FB_INCLUDE_DIR}" fb_include_dir_)
  file(REAL_PATH "${FB_DATA_DIR_NAME}/${fb_json_file_name_}" fb_json_file_)
  file(REAL_PATH "${FB_DATA_DIR_NAME}/${fb_bin_file_name_}" fb_bin_file_)

  # create Flatbuffers Schema files
  cmake_language(CALL create_file "${fb_schema_file_name_}.in")
  configure_file("${fb_schema_file_name_}.in"
                 "${CMAKE_CURRENT_SOURCE_DIR}/${fb_schema_file_name_}"
  )
  # create json data file
  cmake_language(CALL create_file "${FB_DATA_DIR_NAME}/${fb_json_file_name_}")
  # create batch file Schema-to-CPP
  file(REAL_PATH "${_fb_file_stem}_${FB_BATCH_FILE_STEM_SUFFIX_FBS_TO_CPP}.${FB_BATCH_FILE_EXTENSION}"
                 fb_batch_fbs_to_cpp_file_
  )
  file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" fb_cpp_output_dir_)
  if(WIN32)
    cmake_language(CALL create_batch_fbs_to_cpp
      "${fb_batch_fbs_to_cpp_file_}"
      "${TEMPLATE_BUILD_FBS_TO_CPP_BATCH_FILE}"
      "${fb_schema_file_}"
      "${fb_include_dir_}"
      "${fb_cpp_output_dir_}"
    )
  endif()
  # create batch file JSON-to-binary
  file(REAL_PATH "${FB_DATA_DIR_NAME}/${_fb_file_stem}_${FB_BATCH_FILE_STEM_SUFFIX_JSON_TO_BIN}.${FB_BATCH_FILE_EXTENSION}"
                 fb_batch_json_to_bin_file_
  )
  file(REAL_PATH "${FB_DATA_DIR_NAME}" fb_bin_output_dir_)
  if(WIN32)
    cmake_language(CALL create_batch_json_to_bin
      "${fb_batch_json_to_bin_file_}"
      "${TEMPLATE_BUILD_JSON_TO_BIN_BATCH_FILE}"
      "${fb_schema_file_}"
      "${fb_include_dir_}"
      "${fb_bin_output_dir_}"
      "${fb_json_file_}"
    )
  endif()
  # create batch file Binary-to-JSON
  file(REAL_PATH "${FB_DATA_DIR_NAME}/${_fb_file_stem}_${FB_BATCH_FILE_STEM_SUFFIX_BIN_TO_JSON}.${FB_BATCH_FILE_EXTENSION}"
                 fb_batch_bin_to_json_file_
  )
  file(REAL_PATH "${FB_DATA_DIR_NAME}/${FB_BATCH_FILE_STEM_SUFFIX_BIN_TO_JSON}"
                 fb_json_output_dir_
  )
  if(WIN32)
    cmake_language(CALL create_batch_bin_to_json
      "${fb_batch_bin_to_json_file_}"
      "${TEMPLATE_BUILD_BIN_TO_JSON_BATCH_FILE}"
      "${fb_schema_file_}"
      "${fb_include_dir_}"
      "${fb_json_output_dir_}"
      "${fb_bin_file_}"
    )
  endif()
endfunction()

function(create_flatbuffers_schema_file _fb_file_stem)
  set(fb_schema_file_name_ "${_fb_file_stem}.${FB_SCHEMA_FILE_EXTENSION}")
  file(REAL_PATH "${fb_schema_file_name_}" fb_schema_file_)
  # create Flatbuffers Schema file
  cmake_language(CALL create_file "${fb_schema_file_name_}")
  # create batch file Schema-to-CPP
  file(REAL_PATH "${_fb_file_stem}_${FB_BATCH_FILE_STEM_SUFFIX_FBS_TO_CPP}.${FB_BATCH_FILE_EXTENSION}"
                 fb_batch_fbs_to_cpp_file_
  )
  file(REAL_PATH "${FB_INCLUDE_DIR}" fb_include_dir_)
  file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" fb_cpp_output_dir_)
  if(WIN32)
    cmake_language(CALL create_batch_fbs_to_cpp
      "${fb_batch_fbs_to_cpp_file_}"
      "${TEMPLATE_BUILD_FBS_TO_CPP_BATCH_FILE}"
      "${fb_schema_file_}"
      "${fb_include_dir_}"
      "${fb_cpp_output_dir_}"
    )
  endif()
endfunction()

#**********************************************************************
add_subdirectory("Source")

if(GAME_ENABLE_TEST)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.10.0
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/External/googletest/src
  )

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)

  enable_testing()

  add_subdirectory("Test")
endif()

include(FetchContent)
FetchContent_Declare(
  flatbuffers
  GIT_REPOSITORY  https://github.com/google/flatbuffers.git
  GIT_TAG         v2.0.0
  SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/External/flatbuffers
)
FetchContent_MakeAvailable(flatbuffers)
