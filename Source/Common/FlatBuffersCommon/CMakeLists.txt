
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#**********************************************************************
# create Flatbuffers schema file for FB_AmmoType
set(AMMO_TYPE_FB_FILE_STEM "ammoTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${AMMO_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Ammo
set(AMMO_FB_FILE_STEM "ammoFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${AMMO_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Attack
set(ATTACK_FB_FILE_STEM "attackFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${ATTACK_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Attribute
set(ATTRIBUTE_FB_FILE_STEM "attributeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${ATTRIBUTE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_AttributeType
set(ATTRIBUTE_TYPE_FB_FILE_STEM "attributeTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${ATTRIBUTE_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Character
set(CHARACTER_FB_FILE_STEM "characterFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${CHARACTER_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_CharacterModel
set(CHARACTER_MODEL_FB_FILE_STEM "characterModelFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${CHARACTER_MODEL_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_CharacterType
set(CHARACTER_TYPE_FB_FILE_STEM "characterTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${CHARACTER_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_DamageType
set(DAMAGE_TYPE_FB_FILE_STEM "damageTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${DAMAGE_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Game
set(GAME_FB_FILE_STEM "gameFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${GAME_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Inventory
set(INVENTORY_FB_FILE_STEM "inventoryFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${INVENTORY_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Item
set(ITEM_FB_FILE_STEM "itemFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${ITEM_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_LanguageBundle
set(LANGUAGE_BUNDLE_FB_FILE_STEM "languageBundleFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${LANGUAGE_BUNDLE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Skill
set(SKILL_FB_FILE_STEM "skillFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${SKILL_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_SkillType
set(SKILL_TYPE_FB_FILE_STEM "skillTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${SKILL_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Squad
set(SQUAD_FB_FILE_STEM "squadFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${SQUAD_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Unit
set(UNIT_FB_FILE_STEM "unitFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${UNIT_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_Weapon
set(WEAPON_FB_FILE_STEM "weaponFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_WeaponModel
set(WEAPON_MODEL_FB_FILE_STEM "weaponModelFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_MODEL_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_WeaponMod
set(WEAPON_MOD_FB_FILE_STEM "weaponModFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_MOD_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_WeaponModModel
set(WEAPON_MOD_MODEL_FB_FILE_STEM "weaponModModelFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_MOD_MODEL_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_WeaponModType
set(WEAPON_MOD_TYPE_FB_FILE_STEM "weaponModTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_MOD_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
# create Flatbuffers schema file for FB_WeaponType
set(WEAPON_TYPE_FB_FILE_STEM "weaponTypeFB")

cmake_language(CALL create_flatbuffers_schema_file
  "${WEAPON_TYPE_FB_FILE_STEM}"
)

#**********************************************************************
set(LIBRARY_NAME "flatbuffersCommon")
set(HEADER_CXX_LIST "${AMMO_FB_FILE_STEM}_generated.h"
                    "${AMMO_TYPE_FB_FILE_STEM}_generated.h"
                    "${ATTACK_FB_FILE_STEM}_generated.h"
                    "${ATTRIBUTE_FB_FILE_STEM}_generated.h"
                    "${ATTRIBUTE_TYPE_FB_FILE_STEM}_generated.h"
                    "${CHARACTER_FB_FILE_STEM}_generated.h"
                    "${CHARACTER_MODEL_FB_FILE_STEM}_generated.h"
                    "${CHARACTER_TYPE_FB_FILE_STEM}_generated.h"
                    "${DAMAGE_TYPE_FB_FILE_STEM}_generated.h"
                    "${GAME_FB_FILE_STEM}_generated.h"
                    "${INVENTORY_FB_FILE_STEM}_generated.h"
                    "${ITEM_FB_FILE_STEM}_generated.h"
                    "${LANGUAGE_BUNDLE_FB_FILE_STEM}_generated.h"
                    "${SKILL_FB_FILE_STEM}_generated.h"
                    "${SKILL_TYPE_FB_FILE_STEM}_generated.h"
                    "${SQUAD_FB_FILE_STEM}_generated.h"
                    "${UNIT_FB_FILE_STEM}_generated.h"
                    "${WEAPON_FB_FILE_STEM}_generated.h"
                    "${WEAPON_MODEL_FB_FILE_STEM}_generated.h"
                    "${WEAPON_MOD_FB_FILE_STEM}_generated.h"
                    "${WEAPON_MOD_MODEL_FB_FILE_STEM}_generated.h"
                    "${WEAPON_MOD_TYPE_FB_FILE_STEM}_generated.h"
                    "${WEAPON_TYPE_FB_FILE_STEM}_generated.h"
)

add_library(${LIBRARY_NAME} INTERFACE ${HEADER_CXX_LIST})

target_include_directories(${LIBRARY_NAME}
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${LIBRARY_NAME}
                      INTERFACE flatbuffers
)
