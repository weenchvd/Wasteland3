
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "effect")
set(SOURCE_CXX_LIST "${LIBRARY_NAME}.cpp"
                    "Attribute/effectAttribute.cpp"
                    "Skill/effectSkill.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Attribute"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Skill"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC unit
)
