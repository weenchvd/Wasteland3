
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for AmmoReference
set(AMMO_REF_FB_FILE_STEM "ammoReferenceFB")
set(AMMO_REF_FB_BIN_FILE_IDENTIFIER "AMMR")
set(AMMO_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(AMMO_REF_FB_BIN_FILE_NAME "${AMMO_REF_FB_FILE_STEM}.${AMMO_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${AMMO_REF_FB_BIN_FILE_NAME}" AMMO_REF_FB_BIN_FILE)
file(${DEFAULT_CMAKE_FILE_HASH_FUNC} "${AMMO_REF_FB_BIN_FILE}" AMMO_REF_FB_BIN_FILE__HASH)
file(RELATIVE_PATH AMMO_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${AMMO_REF_FB_BIN_FILE}"
)
cmake_path(HASH AMMO_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                AMMO_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT AMMO_REF_FB_BIN_FILE_NAME__OUT
  "${AMMO_REF_FB_FILE_STEM}_${AMMO_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${AMMO_REF_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${AMMO_REF_FB_BIN_FILE_NAME__OUT}"
  AMMO_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${AMMO_REF_FB_BIN_FILE_IDENTIFIER}"
  "${AMMO_REF_FB_BIN_FILE_EXTENSION}"
  "${AMMO_REF_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${AMMO_REF_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${AMMO_REF_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create Flatbuffers files for AmmoText
set(AMMO_TEXT_FB_FILE_STEM "ammoTextFB")
set(AMMO_TEXT_FB_BIN_FILE_IDENTIFIER "AMMT")
set(AMMO_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(AMMO_TEXT_FB_BIN_FILE_NAME "${AMMO_TEXT_FB_FILE_STEM}.${AMMO_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${AMMO_TEXT_FB_BIN_FILE_NAME}" AMMO_TEXT_FB_BIN_FILE)
file(${DEFAULT_CMAKE_FILE_HASH_FUNC} "${AMMO_TEXT_FB_BIN_FILE}" AMMO_TEXT_FB_BIN_FILE__HASH)
file(RELATIVE_PATH AMMO_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${AMMO_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH AMMO_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                AMMO_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT AMMO_TEXT_FB_BIN_FILE_NAME__OUT
  "${AMMO_TEXT_FB_FILE_STEM}_${AMMO_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${AMMO_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${AMMO_TEXT_FB_BIN_FILE_NAME__OUT}"
  AMMO_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${AMMO_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${AMMO_TEXT_FB_BIN_FILE_EXTENSION}"
  "${AMMO_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${AMMO_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${AMMO_TEXT_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create header file with paths
set(AMMO_PATH_FILE_NAME "ammoPath.hpp")
cmake_language(CALL create_file "${AMMO_PATH_FILE_NAME}.in")
configure_file("${AMMO_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${AMMO_PATH_FILE_NAME}"
)
