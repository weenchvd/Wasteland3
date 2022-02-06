
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"initializationAux.hpp"
#include"locator.hpp"
#include"character.hpp"

namespace init {

using namespace std;

constexpr int initialMoney = 50'000;

void initializeSquad(game::object::Squad& squad)
{
    initializeInventory(squad.inventory());
    initializeMembers(squad.members());
    squad.moneyAdd(initialMoney);
}

void initializeInventory(game::object::Inventory& inventory)
{
    using game::object::Weapon;
    using game::object::WeaponMod;
        
    const game::global::Factory& f = game::global::Locator::getFactory();

    /// weapons
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));

    /// weapon mods
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));

}

void initializeShop(game::object::Inventory& inventory)
{
    using game::object::Weapon;
    using game::object::WeaponMod;

    const game::global::Factory& f = game::global::Locator::getFactory();

    /// weapons
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::SMG_RIPPER));

    /// weapon mods
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_LIGHTWEIGHT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_SHORTENED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_OVERSIZED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));

}

void initializeMembers(array<unique_ptr<game::object::Unit>, game::object::nMembers>& members)
{
    using game::object::Character;

    const game::global::Factory& f = game::global::Locator::getFactory();

    int i = 0;
    /// member 1
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("YURI");
    }
    /// member 2
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("ECHO");
    }
    /// member 3
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("RUST");
    }
}

} // namespace init
