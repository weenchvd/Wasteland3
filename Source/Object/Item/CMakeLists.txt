
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(LIBRARY_NAME "item")
set(SOURCE_CXX_LIST "item.cpp"
                    "Ammo/ammo.cpp"
                    "Ammo/ammoCommon.cpp"
                    "Ammo/ammoReference.cpp"
                    "Ammo/ammoText.cpp"
                    "Attack/attack.cpp"
                    "Attack/attackCommon.cpp"
                    "Attack/attackText.cpp"
                    "Damage/damage.cpp"
                    "Damage/damageCommon.cpp"
                    "Damage/damageReference.cpp"
                    "Damage/damageText.cpp"
                    "Weapon/weapon.cpp"
                    "Weapon/weaponCommon.cpp"
                    "Weapon/weaponReference.cpp"
                    "Weapon/weaponText.cpp"
                    "WeaponMod/weaponMod.cpp"
                    "WeaponMod/weaponModCommon.cpp"
                    "WeaponMod/weaponModReference.cpp"
                    "WeaponMod/weaponModText.cpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Ammo"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Attack"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Damage"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Weapon"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/WeaponMod"
)

target_link_libraries(${LIBRARY_NAME}
                      PUBLIC common
                      PUBLIC flatbuffersAux
                      PUBLIC flatbuffersCommon
                      PUBLIC locator
                      PUBLIC plainText
                      PUBLIC unit
)

add_subdirectory("Ammo")
add_subdirectory("Attack")
add_subdirectory("Damage")
add_subdirectory("Weapon")
add_subdirectory("WeaponMod")
