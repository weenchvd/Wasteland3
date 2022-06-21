
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
    squad.moneyAdd(game::common::Money{ initialMoney });
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
    static_cast<Weapon*>(weapon.get())->setMod(0, modBarrel, game::object::isCompatible);
    static_cast<Weapon*>(weapon.get())->setMod(3, modMag, game::object::isCompatible);
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
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_HAMMERFORGE_RIFLED), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_BROACH_RIFLED), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_COLUMBIUM));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_CUT_RIFLED), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_PHASE_SILENCER));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_SOUND_SUPRESSOR));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_BLAST_MUFFLER));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_ALLOY));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_OVERSIZED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_MAX_CAPACITY), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_EXTENDED));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_LONG));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_FARSIGHT), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_DEADEYE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_38MM));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_32MM));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_21MM));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_HOLOGRAPHIC), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_RED_DOT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::SCOPE_REFLEX));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_HE_FUSE_LINKAGE), true);
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_PLASMA_LINKAGE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_CRYOCELL_LINKAGE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_INCENDIARY_LINKAGE));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_SWAT_LIGHT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_TACTICAL_LIGHT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_UNDERBARREL_LIGHT));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_COMP_ASSISTED_LS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_ULTRAVIOLET_LS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_SPEC_OPS_LS));
    inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::UB_LASER_SIGHT));

    /// ammo
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 15), true);
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 90));
    inventory.insert(f.createAmmo(Ammo::Type::A_5_56, 10));
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

void initializeMembers(array<unique_ptr<game::object::Unit>,
                       game::object::Squad::nMembers_>& members)
{
    using game::object::Character;

    const game::global::Factory& f = game::global::Locator::getFactory();

    int i = 0;
    /// member 1
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_TEMPLATE);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("YURI");
    }
    /// member 2
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_TEMPLATE);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("ECHO");
    }
    /// member 3
    if (i < members.size()) {
        members[i] = f.createUnit<Character>(Character::Model::RANGER_TEMPLATE);
        auto& c = *static_cast<Character*>(members[i++].get());
        c.name("RUST");
    }
}

} // namespace init
