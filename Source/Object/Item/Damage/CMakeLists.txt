
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for DamageReference
set(DAMAGE_REF_FB_FILE_STEM "damageReferenceFB")
set(DAMAGE_REF_FB_BIN_FILE_IDENTIFIER "DMGR")
set(DAMAGE_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(DAMAGE_REF_FB_BIN_FILE_NAME "${DAMAGE_REF_FB_FILE_STEM}.${DAMAGE_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${DAMAGE_REF_FB_BIN_FILE_NAME}" DAMAGE_REF_FB_BIN_FILE)
file(RELATIVE_PATH DAMAGE_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${DAMAGE_REF_FB_BIN_FILE}"
)
cmake_path(HASH DAMAGE_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                DAMAGE_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT DAMAGE_REF_FB_BIN_FILE_NAME__OUT
  "${DAMAGE_REF_FB_FILE_STEM}_${DAMAGE_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${DAMAGE_REF_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${DAMAGE_REF_FB_BIN_FILE_NAME__OUT}"
  DAMAGE_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${DAMAGE_REF_FB_BIN_FILE_IDENTIFIER}"
  "${DAMAGE_REF_FB_BIN_FILE_EXTENSION}"
  "${DAMAGE_REF_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${DAMAGE_REF_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${DAMAGE_REF_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create Flatbuffers files for DamageText
set(DAMAGE_TEXT_FB_FILE_STEM "damageTextFB")
set(DAMAGE_TEXT_FB_BIN_FILE_IDENTIFIER "DMGT")
set(DAMAGE_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(DAMAGE_TEXT_FB_BIN_FILE_NAME "${DAMAGE_TEXT_FB_FILE_STEM}.${DAMAGE_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${DAMAGE_TEXT_FB_BIN_FILE_NAME}" DAMAGE_TEXT_FB_BIN_FILE)
file(RELATIVE_PATH DAMAGE_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${DAMAGE_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH DAMAGE_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                DAMAGE_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT DAMAGE_TEXT_FB_BIN_FILE_NAME__OUT
  "${DAMAGE_TEXT_FB_FILE_STEM}_${DAMAGE_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${DAMAGE_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${DAMAGE_TEXT_FB_BIN_FILE_NAME__OUT}"
  DAMAGE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${DAMAGE_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${DAMAGE_TEXT_FB_BIN_FILE_EXTENSION}"
  "${DAMAGE_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${DAMAGE_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${DAMAGE_TEXT_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create header file with paths
set(DAMAGE_PATH_FILE_NAME "damagePath.hpp")
cmake_language(CALL create_file "${DAMAGE_PATH_FILE_NAME}.in")
configure_file("${DAMAGE_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${DAMAGE_PATH_FILE_NAME}"
)
