
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for SkillReference
set(SKILL_REF_FB_FILE_STEM "skillReferenceFB")
set(SKILL_REF_FB_BIN_FILE_IDENTIFIER "SKLR")
set(SKILL_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(SKILL_REF_FB_BIN_FILE_NAME "${SKILL_REF_FB_FILE_STEM}.${SKILL_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${SKILL_REF_FB_BIN_FILE_NAME}" SKILL_REF_FB_BIN_FILE)
file(${DEFAULT_CMAKE_FILE_HASH_FUNC} "${SKILL_REF_FB_BIN_FILE}" SKILL_REF_FB_BIN_FILE__HASH)
file(RELATIVE_PATH SKILL_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${SKILL_REF_FB_BIN_FILE}"
)
cmake_path(HASH SKILL_REF_FB_BIN_FILE__REL_PATH_FROM_CSD
                SKILL_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT SKILL_REF_FB_BIN_FILE_NAME__OUT
  "${SKILL_REF_FB_FILE_STEM}_${SKILL_REF_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${SKILL_REF_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${SKILL_REF_FB_BIN_FILE_NAME__OUT}"
  SKILL_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${SKILL_REF_FB_BIN_FILE_IDENTIFIER}"
  "${SKILL_REF_FB_BIN_FILE_EXTENSION}"
  "${SKILL_REF_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${SKILL_REF_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${SKILL_REF_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create Flatbuffers files for SkillText
set(SKILL_TEXT_FB_FILE_STEM "skillTextFB")
set(SKILL_TEXT_FB_BIN_FILE_IDENTIFIER "SKLT")
set(SKILL_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(SKILL_TEXT_FB_BIN_FILE_NAME "${SKILL_TEXT_FB_FILE_STEM}.${SKILL_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_DIR_NAME}/${SKILL_TEXT_FB_BIN_FILE_NAME}" SKILL_TEXT_FB_BIN_FILE)
file(${DEFAULT_CMAKE_FILE_HASH_FUNC} "${SKILL_TEXT_FB_BIN_FILE}" SKILL_TEXT_FB_BIN_FILE__HASH)
file(RELATIVE_PATH SKILL_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                   "${CMAKE_SOURCE_DIR}"
                   "${SKILL_TEXT_FB_BIN_FILE}"
)
cmake_path(HASH SKILL_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD
                SKILL_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH
)
string(CONCAT SKILL_TEXT_FB_BIN_FILE_NAME__OUT
  "${SKILL_TEXT_FB_FILE_STEM}_${SKILL_TEXT_FB_BIN_FILE__REL_PATH_FROM_CSD__HASH}."
  "${SKILL_TEXT_FB_BIN_FILE_EXTENSION}"
)
file(TO_NATIVE_PATH
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}/${SKILL_TEXT_FB_BIN_FILE_NAME__OUT}"
  SKILL_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

cmake_language(CALL create_flatbuffers_data_files
  "${SKILL_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${SKILL_TEXT_FB_BIN_FILE_EXTENSION}"
  "${SKILL_TEXT_FB_FILE_STEM}"
)
cmake_language(CALL distribute_file
  "${SKILL_TEXT_FB_BIN_FILE}"
  "${ASSETS__DIR__REL_PATH_FROM_W3EXEC}"
  "${SKILL_TEXT_FB_BIN_FILE_NAME__OUT}"
)


#**********************************************************************
# create header file with paths
set(SKILL_PATH_FILE_NAME "skillPath.hpp")
cmake_language(CALL create_file "${SKILL_PATH_FILE_NAME}.in")
configure_file("${SKILL_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${SKILL_PATH_FILE_NAME}"
)
