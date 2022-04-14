
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for Attack
set(ATTACK_REF_FB_FILE_STEM "attackReferenceFB")
set(ATTACK_REF_FB_BIN_FILE_IDENTIFIER "ATKR")
set(ATTACK_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(ATTACK_REF_FB_BIN_FILE_NAME "${ATTACK_REF_FB_FILE_STEM}.${ATTACK_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${ATTACK_REF_FB_BIN_FILE_NAME}" ATTACK_REF_FB_BIN_FILE)
file(RELATIVE_PATH ATTACK_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${ATTACK_REF_FB_BIN_FILE}"
)
cmake_path(HASH ATTACK_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                ATTACK_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT ATTACK_REF_FB_BIN_FILE_NAME__OUT
  "${ATTACK_REF_FB_FILE_STEM}_${ATTACK_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${ATTACK_REF_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${ATTACK_REF_FB_BIN_FILE_NAME__OUT}"
  ATTACK_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${ATTACK_REF_FB_BIN_FILE_IDENTIFIER}"
  "${ATTACK_REF_FB_BIN_FILE_EXTENSION}"
  "${ATTACK_REF_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${ATTACK_REF_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${ATTACK_REF_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create Flatbuffers files for AttackText
set(ATTACK_TEXT_FB_FILE_STEM "attackTextFB")
set(ATTACK_TEXT_FB_BIN_FILE_IDENTIFIER "ATKT")
set(ATTACK_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(ATTACK_TEXT_FB_BIN_FILE_NAME "${ATTACK_TEXT_FB_FILE_STEM}.${ATTACK_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${ATTACK_TEXT_FB_BIN_FILE_NAME}" ATTACK_TEXT_FB_BIN_FILE)
file(RELATIVE_PATH ATTACK_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${ATTACK_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH ATTACK_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                ATTACK_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT ATTACK_TEXT_FB_BIN_FILE_NAME__OUT
  "${ATTACK_TEXT_FB_FILE_STEM}_${ATTACK_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${ATTACK_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${ATTACK_TEXT_FB_BIN_FILE_NAME__OUT}"
  ATTACK_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${ATTACK_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${ATTACK_TEXT_FB_BIN_FILE_EXTENSION}"
  "${ATTACK_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${ATTACK_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${ATTACK_TEXT_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create header file with paths
set(ATTACK_PATH_FILE_NAME "attackPath.hpp")
cmake_language(CALL create_file "${ATTACK_PATH_FILE_NAME}.in")
configure_file("${ATTACK_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${ATTACK_PATH_FILE_NAME}"
)
