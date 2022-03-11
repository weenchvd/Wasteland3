
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

void ItemVisitorExtendedName::visitWeapon(object::Weapon& weapon) noexcept
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

void ItemVisitorExtendedName::visitWeaponMod(object::WeaponMod& weaponMod) noexcept
{
    reset();

    ostringstream oss;
    oss << weaponMod.name();

    text_ = oss.str();
}

void ItemVisitorExtendedName::visitArmor(object::Armor& armor) noexcept
{
    reset();
}

void ItemVisitorExtendedName::visitArmorMod(object::ArmorMod& armorMod) noexcept
{
    reset();
}

void ItemVisitorExtendedName::visitAmmo(object::Ammo& ammo) noexcept
{
    reset();

    ostringstream oss;
    oss << ammo.name() << " (" << ammo.quantity() << ')';

    text_ = oss.str();
}

void ItemVisitorExtendedName::visitJunk(object::Junk& junk) noexcept
{
    reset();
}

} // namespace menu
} // namespace game
