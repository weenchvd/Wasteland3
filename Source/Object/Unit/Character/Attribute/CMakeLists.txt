
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers files for AttributeReference
set(ATTRIBUTE_REF_FB_FILE_STEM "attributeReferenceFB")
set(ATTRIBUTE_REF_FB_BIN_FILE_IDENTIFIER "ATTR")
set(ATTRIBUTE_REF_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(ATTRIBUTE_REF_FB_BIN_FILE_NAME "${ATTRIBUTE_REF_FB_FILE_STEM}.${ATTRIBUTE_REF_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_FOLDER}/${ATTRIBUTE_REF_FB_BIN_FILE_NAME}" ATTRIBUTE_REF_FB_BIN_FILE)

cmake_language(CALL create_flatbuffers_data_files
  "${ATTRIBUTE_REF_FB_BIN_FILE_IDENTIFIER}"
  "${ATTRIBUTE_REF_FB_BIN_FILE_EXTENSION}"
  "${ATTRIBUTE_REF_FB_FILE_STEM}"
)
file(TO_NATIVE_PATH
  "${REL_PATH__ASSETS}/${ATTRIBUTE_REF_FB_BIN_FILE_NAME}"
  ATTRIBUTE_REF_FB_BIN_FILE__NATIVE_REL_PATH
)

if (EXISTS ${ATTRIBUTE_REF_FB_BIN_FILE})
  file(COPY "${ATTRIBUTE_REF_FB_BIN_FILE}"
       DESTINATION "${BIN_DIR__W3EXECUTABLE}/${REL_PATH__ASSETS}"
  )
  install(FILES "${ATTRIBUTE_REF_FB_BIN_FILE}"
          DESTINATION "${CMAKE_BUILD_TYPE}/${REL_PATH__ASSETS}"
  )
endif()


#**********************************************************************
# create Flatbuffers files for AttributeText
set(ATTRIBUTE_TEXT_FB_FILE_STEM "attributeTextFB")
set(ATTRIBUTE_TEXT_FB_BIN_FILE_IDENTIFIER "ATTT")
set(ATTRIBUTE_TEXT_FB_BIN_FILE_EXTENSION "${FB_BIN_FILE_EXTENSION}")
set(ATTRIBUTE_TEXT_FB_BIN_FILE_NAME "${ATTRIBUTE_TEXT_FB_FILE_STEM}.${ATTRIBUTE_TEXT_FB_BIN_FILE_EXTENSION}")
file(REAL_PATH "${FB_DATA_FOLDER}/${ATTRIBUTE_TEXT_FB_BIN_FILE_NAME}" ATTRIBUTE_TEXT_FB_BIN_FILE)

cmake_language(CALL create_flatbuffers_data_files
  "${ATTRIBUTE_TEXT_FB_BIN_FILE_IDENTIFIER}"
  "${ATTRIBUTE_TEXT_FB_BIN_FILE_EXTENSION}"
  "${ATTRIBUTE_TEXT_FB_FILE_STEM}"
)
file(TO_NATIVE_PATH
  "${REL_PATH__ASSETS}/${ATTRIBUTE_TEXT_FB_BIN_FILE_NAME}"
  ATTRIBUTE_TEXT_FB_BIN_FILE__NATIVE_REL_PATH
)

if (EXISTS ${ATTRIBUTE_TEXT_FB_BIN_FILE})
  file(COPY "${ATTRIBUTE_TEXT_FB_BIN_FILE}"
       DESTINATION "${BIN_DIR__W3EXECUTABLE}/${REL_PATH__ASSETS}"
  )
  install(FILES "${ATTRIBUTE_TEXT_FB_BIN_FILE}"
          DESTINATION "${CMAKE_BUILD_TYPE}/${REL_PATH__ASSETS}"
  )
endif()


#**********************************************************************
# create header file with paths
set(ATTRIBUTE_PATH_FILE_NAME "attributePath.hpp")
cmake_language(CALL create_file "${ATTRIBUTE_PATH_FILE_NAME}.in")
configure_file("${ATTRIBUTE_PATH_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${ATTRIBUTE_PATH_FILE_NAME}"
)
