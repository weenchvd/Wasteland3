
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"itemVisitorExtendedName.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void ItemVisitorExtendedName::visitWeapon(const object::Weapon& weapon)
{
    reset();

    ostringstream oss;
    oss << weapon.name();
    bool modsInstalled{ false };
    for (int i = 0; modsInstalled == false && i < weapon.slotMod().size(); ++i) {
        if (weapon.slotMod()[i] != nullptr) {
            modsInstalled = true;
        }
    }
    if (modsInstalled == true) {
        oss << " (";
        bool notFirst{ false };
        for (int i = 0; i < weapon.slotMod().size(); ++i) {
            const auto& weaponMod{ weapon.slotMod()[i] };
            if (weaponMod != nullptr) {
                if (notFirst == true) {
                    oss << ", ";
                }
                notFirst = true;
                oss << weaponMod->name();
            }
        }
        oss << ')';
    }

    text_ = oss.str();
}

void ItemVisitorExtendedName::visitWeaponMod(const object::WeaponMod& weaponMod)
{
    reset();

    ostringstream oss;
    oss << weaponMod.name();

    text_ = oss.str();
}

void ItemVisitorExtendedName::visitArmor(const object::Armor& armor)
{
    reset();
}

void ItemVisitorExtendedName::visitArmorMod(const object::ArmorMod& armorMod)
{
    reset();
}

void ItemVisitorExtendedName::visitAmmo(const object::Ammo& ammo)
{
    reset();

    ostringstream oss;
    oss << ammo.name() << " (" << ammo.quantity() << ')';

    text_ = oss.str();
}

void ItemVisitorExtendedName::visitJunk(const object::Junk& junk)
{
    reset();
}

} // namespace menu
} // namespace game
