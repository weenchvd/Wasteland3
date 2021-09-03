
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

set(ALL_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Common"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Error"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Destroyable"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Inventory"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Item"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Item/Ammo"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Item/Armor"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Item/Weapon"
                            "${CMAKE_CURRENT_SOURCE_DIR}/Object/Item/WeaponMod"
                            )


add_subdirectory("Error")
add_subdirectory("Object")
add_subdirectory("main")
