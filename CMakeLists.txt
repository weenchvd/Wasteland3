
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

project("Wasteland3"  VERSION 0.2.2)

option(GAME_ENABLE_TEST "Enable tests for game" OFF)



#set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
set(EXTERNAL_PROJECTS_DIR "${CMAKE_SOURCE_DIR}/External")
set(SRC_FILES_DIR "${CMAKE_SOURCE_DIR}/Files")
set(SRC_FONTS_DIR "${SRC_FILES_DIR}/Fonts")

#**********************************************************************
set(DEFAULT_CMAKE_FILE_HASH_FUNC "SHA3_256")
set(DEFAULT_BOTAN_FILE_HASH_FUNC "SHA-3(256)")

#**********************************************************************
set(W3EXEC__BIN_DIR "${CMAKE_BINARY_DIR}/Source/Main")
set(W3EXEC__INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/W3")
set(W3DATA__DIR__REL_PATH_FROM_W3EXEC "W3_data")
set(SYSTEM__DIR__REL_PATH_FROM_W3EXEC "${W3DATA__DIR__REL_PATH_FROM_W3EXEC}/System")
set(ASSETS__DIR__REL_PATH_FROM_W3EXEC "${W3DATA__DIR__REL_PATH_FROM_W3EXEC}/Assets")
set(FONTS__DIR__REL_PATH_FROM_W3EXEC "${W3DATA__DIR__REL_PATH_FROM_W3EXEC}/Fonts")

set(SAVES__DIR__REL_PATH_FROM_W3EXEC "Saves")
set(SAVE_FILE_EXTENSION "w3save")

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
            DESTINATION "${W3EXEC__INSTALL_DIR}/${_relative_path}"
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
include(FetchContent)

if(GAME_ENABLE_TEST)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         "release-1.10.0"
    SOURCE_DIR      "${EXTERNAL_PROJECTS_DIR}/googletest/src"
  )

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)

  enable_testing()

  add_subdirectory("Test")
endif()

FetchContent_Declare(
  flatbuffers
  GIT_REPOSITORY  https://github.com/google/flatbuffers.git
  GIT_TAG         "v2.0.0"
  SOURCE_DIR      "${EXTERNAL_PROJECTS_DIR}/flatbuffers"
)
FetchContent_MakeAvailable(flatbuffers)

if(WIN32)
  cmake_path(GET CMAKE_BINARY_DIR FILENAME CONFIG_NAME)

  # set paths
  set(BOTAN_LIB_ROOT_DIR    "${EXTERNAL_PROJECTS_DIR}/botan")
  set(BOTAN_LIB_REPOS_DIR   "${BOTAN_LIB_ROOT_DIR}/repos")
  set(BOTAN_LIB_FCSTUFF_DIR "${BOTAN_LIB_ROOT_DIR}/cmake-fetchcontent-stuff")
  if (CONFIG_NAME)
    set(BOTAN_LIB_INSTALL_DIR "${BOTAN_LIB_ROOT_DIR}-install/${CONFIG_NAME}")
  else()
    set(BOTAN_LIB_INSTALL_DIR "${BOTAN_LIB_ROOT_DIR}-install")
  endif()

  set(BOTAN_LIB_INCLUDE_DIR "${BOTAN_LIB_INSTALL_DIR}/include")
  set(BOTAN_LIB_BIN_DIR     "${BOTAN_LIB_INSTALL_DIR}/bin")
  set(BOTAN_LIB_LIB_DIR     "${BOTAN_LIB_INSTALL_DIR}/lib")

  # set script options and commands for the build
  set(BOTAN_LIB_CONFIGURE_PY_ARGS         "--prefix=${BOTAN_LIB_INSTALL_DIR}")
  list(APPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--includedir=${BOTAN_LIB_INCLUDE_DIR}")
  list(APPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--bindir=${BOTAN_LIB_BIN_DIR}")
  list(APPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--libdir=${BOTAN_LIB_LIB_DIR}")
  list(PREPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--disable-static-library")

  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    list(PREPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--debug-mode")
  endif()
  if(MSVC)
    list(PREPEND BOTAN_LIB_CONFIGURE_PY_ARGS "--cc=msvc;--os=windows")
    set(BOTAN_LIB_MAKE_COMMAND    "nmake")
    set(BOTAN_LIB_TEST_COMMAND    "nmake;check")
    set(BOTAN_LIB_INSTALL_COMMAND "nmake;install")
  else()
    set(BOTAN_LIB_MAKE_COMMAND    " ")
    set(BOTAN_LIB_TEST_COMMAND    " ")
    set(BOTAN_LIB_INSTALL_COMMAND " ")
  endif()

  # download and unpack Botan library
  FetchContent_Declare(
    botan
    GIT_REPOSITORY  https://github.com/randombit/botan.git
    GIT_TAG         "2.19.1"
    PREFIX          ${BOTAN_LIB_FCSTUFF_DIR}
    SOURCE_DIR      ${BOTAN_LIB_REPOS_DIR}
  )
  set(FETCHCONTENT_QUIET OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(botan)

  # find Python3 Interpreter and run build, testing and installation
  if(${botan_POPULATED} AND NOT EXISTS "${BOTAN_LIB_LIB_DIR}/botan.lib")
    find_package(Python3 COMPONENTS Interpreter)
    if(NOT ${Python3_Interpreter_FOUND})
      message(FATAL_ERROR "Python3 Interpreter NOT FOUND")
    endif()

    execute_process(
      COMMAND           ${Python3_EXECUTABLE} configure.py ${BOTAN_LIB_CONFIGURE_PY_ARGS}
      WORKING_DIRECTORY ${BOTAN_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
    execute_process(
      COMMAND           ${BOTAN_LIB_MAKE_COMMAND}
      WORKING_DIRECTORY ${BOTAN_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
    execute_process(
      COMMAND           ${BOTAN_LIB_TEST_COMMAND}
      WORKING_DIRECTORY ${BOTAN_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
    execute_process(
      COMMAND           ${BOTAN_LIB_INSTALL_COMMAND}
      WORKING_DIRECTORY ${BOTAN_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
  endif()
endif()

if(WIN32)
  cmake_path(GET CMAKE_BINARY_DIR FILENAME CONFIG_NAME)

  # set paths
  set(BOOST_LIB_ROOT_DIR    "${EXTERNAL_PROJECTS_DIR}/boost")
  set(BOOST_LIB_REPOS_DIR   "${BOOST_LIB_ROOT_DIR}/repos")
  set(BOOST_LIB_BUILD_DIR   "${BOOST_LIB_ROOT_DIR}/build")
  set(BOOST_LIB_FCSTUFF_DIR "${BOOST_LIB_ROOT_DIR}/cmake-fetchcontent-stuff")
  if (CONFIG_NAME)
    set(BOOST_LIB_INSTALL_DIR "${BOOST_LIB_ROOT_DIR}-install/${CONFIG_NAME}")
  else()
    set(BOOST_LIB_INSTALL_DIR "${BOOST_LIB_ROOT_DIR}-install")
  endif()

  set(BOOST_LIB_INCLUDE_DIR "${BOOST_LIB_INSTALL_DIR}/include")
  set(BOOST_LIB_LIB_DIR     "${BOOST_LIB_INSTALL_DIR}/lib")

  # set script options and commands for the build
  set(BOOST_LIB_BUILD_OPTIONS         "--includedir=${BOOST_LIB_INCLUDE_DIR}")
  list(APPEND BOOST_LIB_BUILD_OPTIONS "--libdir=${BOOST_LIB_LIB_DIR}")
  list(APPEND BOOST_LIB_BUILD_OPTIONS "--build-dir=${BOOST_LIB_BUILD_DIR}")
  list(APPEND BOOST_LIB_BUILD_OPTIONS "--build-type=minimal")
  list(APPEND BOOST_LIB_BUILD_OPTIONS "--no-cmake-config")

  set(BOOST_LIB_BUILD_PROPERTIES            "address-model=64")
  list(APPEND BOOST_LIB_BUILD_PROPERTIES    "link=static")
  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    list(APPEND BOOST_LIB_BUILD_PROPERTIES  "variant=debug")
  else()
    list(APPEND BOOST_LIB_BUILD_PROPERTIES  "variant=release")
  endif()
  
  file(GLOB BOOST_LIB_LIST "${BOOST_LIB_LIB_DIR}/*boost*.lib")
  list(LENGTH BOOST_LIB_LIST BOOST_LIB_LIST_LENGTH)

  # download and unpack BOOST library
  include(FetchContent)
  FetchContent_Declare(
    boost
    GIT_REPOSITORY  https://github.com/boostorg/boost.git
    GIT_TAG         "boost-1.79.0"
    PREFIX          ${BOOST_LIB_FCSTUFF_DIR}
    SOURCE_DIR      ${BOOST_LIB_REPOS_DIR}
  )
  set(FETCHCONTENT_QUIET OFF CACHE BOOL "" FORCE)

  FetchContent_GetProperties(boost)
  if(NOT boost_POPULATED)
    FetchContent_Populate(boost)
  endif()

  # run build and installation
  if(${boost_POPULATED} AND NOT ${BOOST_LIB_LIST_LENGTH})
    execute_process(
      COMMAND           "bootstrap.bat"
      WORKING_DIRECTORY ${BOOST_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
    execute_process(
      COMMAND           "./b2" ${BOOST_LIB_BUILD_OPTIONS} ${BOOST_LIB_BUILD_PROPERTIES} "install"
      WORKING_DIRECTORY ${BOOST_LIB_REPOS_DIR}
      COMMAND_ECHO      STDOUT
    )
  endif()
endif()

if(WIN32)
  # set paths
  set(IMGUI_LIB_ROOT_DIR      "${EXTERNAL_PROJECTS_DIR}/imgui")
  set(IMGUI_LIB_REPOS_DIR     "${IMGUI_LIB_ROOT_DIR}/repos")
  set(IMGUI_LIB_FCSTUFF_DIR   "${IMGUI_LIB_ROOT_DIR}/cmake-fetchcontent-stuff")
  set(IMGUI_LIB_BACKENDS_DIR  "${IMGUI_LIB_REPOS_DIR}/backends")

  # download and unpack IMGUI library
  include(FetchContent)
  FetchContent_Declare(
    imgui
    GIT_REPOSITORY  https://github.com/ocornut/imgui.git
    GIT_TAG         "5d0deebba46a69aa89e7b666c753251c6e2103bf"
    PREFIX          ${IMGUI_LIB_FCSTUFF_DIR}
    SOURCE_DIR      ${IMGUI_LIB_REPOS_DIR}
  )
  set(FETCHCONTENT_QUIET OFF CACHE BOOL "" FORCE)

  FetchContent_GetProperties(imgui)
  if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
  endif()
endif()

#**********************************************************************
add_subdirectory("Source")
