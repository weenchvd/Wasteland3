
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "flatbuffersAux")
set(SOURCE_CXX_LIST "flatbuffersAux.cpp"
                    "flatbuffersLanguageBundle.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC flatbuffersCommon
                      PUBLIC plainText
)

if(WIN32)
  target_include_directories(${LIBRARY_NAME} PUBLIC "${BOTAN_LIB_INCLUDE_DIR}/botan-2")
  target_link_libraries(${LIBRARY_NAME} PUBLIC "${BOTAN_LIB_LIB_DIR}/botan.lib")

  configure_file("${BOTAN_LIB_BIN_DIR}/botan.dll" "${W3EXEC__BIN_DIR}/botan.dll" COPYONLY)
  install(FILES "${BOTAN_LIB_BIN_DIR}/botan.dll" DESTINATION ${W3EXEC__INSTALL_DIR})

  install(FILES "${BOTAN_LIB_REPOS_DIR}/license.txt" DESTINATION ${W3EXEC__INSTALL_DIR} RENAME "botan_license.txt")
endif()


#**********************************************************************
# create header file with definitions
set(FLATBUFFERS_AUX_DEFINE_FILE_NAME "flatbuffersAuxDefine.hpp")
cmake_language(CALL create_file "${FLATBUFFERS_AUX_DEFINE_FILE_NAME}.in")
configure_file("${FLATBUFFERS_AUX_DEFINE_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${FLATBUFFERS_AUX_DEFINE_FILE_NAME}"
)
