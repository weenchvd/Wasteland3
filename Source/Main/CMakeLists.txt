
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

project("Main" VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(EXEC_NAME "main")
set(SOURCE_CXX_LIST "${EXEC_NAME}.cpp"
                    "initialization.cpp"
                    )

# Add source to this project's executable.
add_executable(${EXEC_NAME} ${SOURCE_CXX_LIST})

target_link_libraries(${EXEC_NAME} PRIVATE inventory locator menu squad unit)

# Add tests and install targets if needed.
install(TARGETS ${EXEC_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE} DESTINATION "${CMAKE_BUILD_TYPE}")
