
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "unit")
set(SOURCE_CXX_LIST "${LIBRARY_NAME}.cpp"
                    "Character/character.cpp"
                    "Character/characterCommon.cpp"
                    "Character/characterReference.cpp"
                    "Character/characterText.cpp"
                    "Character/Attribute/attribute.cpp"
                    "Character/Attribute/attributeAux.cpp"
                    "Character/Attribute/attributeCommon.cpp"
                    "Character/Attribute/attributeReference.cpp"
                    "Character/Attribute/attributeText.cpp"
                    "Character/Skill/skill.cpp"
                    "Character/Skill/skillCommon.cpp"
                    "Character/Skill/skillReference.cpp"
                    "Character/Skill/skillText.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Character"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Character/Attribute"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Character/Skill"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC effect
                      PUBLIC flatbuffersAux
                      PUBLIC flatbuffersCommon
                      PUBLIC inventory
                      PUBLIC item
                      PUBLIC locator
                      PUBLIC observer
)

add_subdirectory("Character")
add_subdirectory("Character/Attribute")
add_subdirectory("Character/Skill")
