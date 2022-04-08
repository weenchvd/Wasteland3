
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"itemVisitorExtendedName.hpp"
#include"itemVisitorNameType.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void ItemVisitorNameType::visitWeapon(const object::Weapon& weapon)
{
    reset();

    const auto& text{ weapon.weaponText() };
    ItemVisitorExtendedName vis;
    weapon.accept(vis);
    ostringstream oss;
    oss << vis.getExtendedName() << " [" << text.type(weapon.type()) << ']';

    text_ = oss.str();
}

void ItemVisitorNameType::visitWeaponMod(const object::WeaponMod& weaponMod)
{
    reset();

    const auto& text{ weaponMod.weaponModText() };
    ItemVisitorExtendedName vis;
    weaponMod.accept(vis);
    ostringstream oss;
    oss << vis.getExtendedName() << " [" << text.type(weaponMod.type()) << ']';

    text_ = oss.str();
}

void ItemVisitorNameType::visitArmor(const object::Armor& armor)
{
    reset();
}

void ItemVisitorNameType::visitArmorMod(const object::ArmorMod& armorMod)
{
    reset();
}

void ItemVisitorNameType::visitAmmo(const object::Ammo& ammo)
{
    reset();

    ItemVisitorExtendedName vis;
    ammo.accept(vis);
    ostringstream oss;
    oss << vis.getExtendedName();

    text_ = oss.str();
}

void ItemVisitorNameType::visitJunk(const object::Junk& junk)
{
    reset();
}

} // namespace menu
} // namespace game
