
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for WeaponReference
set(WEAPON_REF_FB_FILE_STEM "weaponReferenceFB")
set(WEAPON_REF_FB_BIN_FILE_IDENTIFIER "WPNR")
set(WEAPON_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(WEAPON_REF_FB_BIN_FILE_NAME "${WEAPON_REF_FB_FILE_STEM}.${WEAPON_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${WEAPON_REF_FB_BIN_FILE_NAME}" WEAPON_REF_FB_BIN_FILE)
file(RELATIVE_PATH WEAPON_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${WEAPON_REF_FB_BIN_FILE}"
)
cmake_path(HASH WEAPON_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                WEAPON_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT WEAPON_REF_FB_BIN_FILE_NAME__OUT
  "${WEAPON_REF_FB_FILE_STEM}_${WEAPON_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${WEAPON_REF_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${WEAPON_REF_FB_BIN_FILE_NAME__OUT}"
  WEAPON_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${WEAPON_REF_FB_BIN_FILE_IDENTIFIER}"
  "${WEAPON_REF_FB_BIN_FILE_EXTENSION}"
  "${WEAPON_REF_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${WEAPON_REF_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${WEAPON_REF_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create Flatbuffers files for WeaponText
set(WEAPON_TEXT_FB_FILE_STEM "weaponTextFB")
set(WEAPON_TEXT_FB_BIN_FILE_IDENTIFIER "WPNT")
set(WEAPON_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(WEAPON_TEXT_FB_BIN_FILE_NAME "${WEAPON_TEXT_FB_FILE_STEM}.${WEAPON_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${WEAPON_TEXT_FB_BIN_FILE_NAME}" WEAPON_TEXT_FB_BIN_FILE)
file(RELATIVE_PATH WEAPON_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${WEAPON_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH WEAPON_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                WEAPON_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT WEAPON_TEXT_FB_BIN_FILE_NAME__OUT
  "${WEAPON_TEXT_FB_FILE_STEM}_${WEAPON_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${WEAPON_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${WEAPON_TEXT_FB_BIN_FILE_NAME__OUT}"
  WEAPON_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${WEAPON_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${WEAPON_TEXT_FB_BIN_FILE_EXTENSION}"
  "${WEAPON_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${WEAPON_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${WEAPON_TEXT_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create header file with paths
set(WEAPON_PATH_FILE_NAME "weaponPath.hpp")
cmake_language(CALL create_file "${WEAPON_PATH_FILE_NAME}.in")
configure_file("${WEAPON_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${WEAPON_PATH_FILE_NAME}"
)
