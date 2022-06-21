
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create header file
set(MENU_MAIN_AUX_FILE_NAME "menuMainAux.hpp")
cmake_language(CALL create_file "${MENU_MAIN_AUX_FILE_NAME}.in")
configure_file("${MENU_MAIN_AUX_FILE_NAME}.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/${MENU_MAIN_AUX_FILE_NAME}"
)
