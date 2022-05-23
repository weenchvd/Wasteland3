
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "menu")
set(SOURCE_CXX_LIST "menuCommon.cpp"
                    "menuCommonText.cpp"
                    "AttributeMenu/menuAttribute.cpp"
                    "InventoryMenu/menuInventory.cpp"
                    "InventoryMenu/menuInventoryText.cpp"
                    "ItemMenu/itemVisitorExtendedName.cpp"
                    "ItemMenu/itemVisitorFullDescr.cpp"
                    "ItemMenu/itemVisitorNameType.cpp"
                    "ItemMenu/menuItem.cpp"
                    "ItemMenu/menuItemCommon.cpp"
                    "ItemMenu/menuItemModify.cpp"
                    "ItemMenu/menuItemText.cpp"
                    "MainMenu/menuMain.cpp"
                    "MainMenu/menuMainText.cpp"
                    "OptionMenu/menuOptions.cpp"
                    "OptionMenu/menuOptionsText.cpp"
                    "SkillMenu/menuSkill.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/AttributeMenu"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/InventoryMenu"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ItemMenu"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/MainMenu"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/OptionMenu"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SkillMenu"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC inventory
                      PUBLIC locator
                      PUBLIC plainText
                      PUBLIC squad
                      PUBLIC unit
)
