
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

///#include"ammo.hpp"
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
    using game::object::Item;
    using game::object::Ammo;
    using game::object::Weapon;
    using game::object::WeaponMod;
        
    const game::global::Factory& f = game::global::Locator::getFactory();

    /// add AR with installed mods
    auto weapon{ f.createItem<Weapon>(Weapon::Model::AR_SOCOM) };
    auto modBarrel{ f.createItem<WeaponMod>(WeaponMod::Model::BARREL_TITANIUM_COBALT) };
    auto modMag{ f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE) };
    static_cast<Weapon*>(weapon.get())->slotMod().set(0, modBarrel, game::object::isCompatible);
    static_cast<Weapon*>(weapon.get())->slotMod().set(3, modMag, game::object::isCompatible);
    inventory.insert(weapon, true);

    /// weapons
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::SMG_RIPPER));
    inventory.insert(f.createItem<Weapon>(Weapon::Model::SMG_RIPPER));

    /// weapon mods
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_SHORTENED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_LIGHTWEIGHT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_TITANIUM_COBALT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_OVERSIZED));

    /// ammo
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 15), true);
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 90));
    inventory.insert(f.createAmmo(Ammo::Type::FROZEN_FERRET, 6), true);
    inventory.insert(f.createAmmo(Ammo::Type::ENERGY_CELLS, 55));
    inventory.insert(f.createAmmo(Ammo::Type::ROCKET, 4));
}

void initializeShop(game::object::Inventory& inventory)
{
    using game::object::Ammo;
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
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_TITANIUM_COBALT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_TITANIUM_COBALT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_TITANIUM_COBALT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_OVERSIZED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));

    /// ammo
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 1500));
    inventory.insert(f.createAmmo(Ammo::Type::A_7_62, 2000));
    inventory.insert(f.createAmmo(Ammo::Type::A_D45, 1500));
    inventory.insert(f.createAmmo(Ammo::Type::A_D38, 1000));
    inventory.insert(f.createAmmo(Ammo::Type::ENERGY_CELLS, 1000));
    inventory.insert(f.createAmmo(Ammo::Type::ROCKET, 50));

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
