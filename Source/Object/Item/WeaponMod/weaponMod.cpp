
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weapon.hpp"
#include"weaponMod.hpp"
#include<string>

namespace Game
{
    namespace Object
    {
        using namespace std;

        WeaponMod::WeaponMod(WeaponMod::Model model) noexcept
            :
            base_           { ref_[static_cast<underlying_type_t<WeaponMod::Model>>(model)] }
        {}

        void WeaponMod::apply(Weapon& weapon)
        {
            weapon.multiplierCritDamageAdd(base_.mulCritDmg_);
            weapon.damageMinimumAdd(base_.dmgMin_);
            weapon.damageMaximumAdd(base_.dmgMax_);
            weapon.chanceHitAdd(base_.chaHit_);
            weapon.chanceCritDamageAdd(base_.chaCritDmg_);
            weapon.armorPenetrationAdd(base_.armorPen_);
            weapon.rangeAttackAdd(base_.rangeAttack_);
            weapon.shotsPerAttackAdd(base_.shoPerAttack_);
            weapon.actionPointPerAttackAdd(base_.apAttack_);
            weapon.actionPointPerReloadAdd(base_.apReload_);
            weapon.capacityAmmoAdd(base_.capAmmo_);
            if (base_.tyAmmo_ != Ammo::Type::INVALID) weapon.ammoType(base_.tyAmmo_);
            if (base_.tyDmg_ != Damage::Type::INVALID) weapon.damageType(base_.tyDmg_);
        }

        vector<WeaponModReference> WeaponMod::ref_ = vector<WeaponModReference>();

        void WeaponMod::initRef()
        {
            ref_.resize(static_cast<underlying_type_t<WeaponMod::Model>>(WeaponMod::Model::NUMBER_OF));
            
            ///// TEMPLATE
            //{
            //    WeaponModReference ref;
            //    ref.weaponModType(WeaponMod::Type:);
            //    ref.weaponModModel(WeaponMod::Model:);
            //    ref.levelSkill();
            //    ref.price();
            //    ref.name();
            //    ref.description();

            //    add(move(ref));
            //}

            /// BARREL
            {
                /// SHORTENED BARREL
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponMod::Type::BARREL);
                    ref.weaponModModel(WeaponMod::Model::BARREL_SHORTENED);
                    ref.levelSkill(8);
                    ref.price(600);
                    ref.name("SHORTENED BARREL");
                    ref.description("This short barrel reduces Chance to Hit but increases "
                        "bullet velocity dramatically. Best for skilled marksmen.");
                    ref.damageMinimum(20);
                    ref.damageMaximum(20);
                    ref.chanceHit(-100);

                    add(move(ref));
                }

                /// LIGHTWEIGHT BARREL
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponMod::Type::BARREL);
                    ref.weaponModModel(WeaponMod::Model::BARREL_LIGHTWEIGHT);
                    ref.levelSkill(8);
                    ref.price(600);
                    ref.name("LIGHTWEIGHT BARREL");
                    ref.description("Lighter materials in this barrel significantly reduce weight "
                        "at the cost of firepower.");
                    ref.damageMinimum(-12);
                    ref.damageMaximum(-12);
                    ref.chanceHit(120);
                    ref.armorPenetration(1);

                    add(move(ref));
                }

            }

            /// MAGAZINE
            {
                /// QUICKFIRE MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponMod::Type::MAGAZINE);
                    ref.weaponModModel(WeaponMod::Model::MAG_QUICKFIRE);
                    ref.levelSkill(10);
                    ref.price(450);
                    ref.name("QUICKFIRE MAG");
                    ref.description("This magazine has a built-in mechanism to slam bullets directry "
                        "into the chamber.");
                    ref.actionPointPerAttack(-1);

                    add(move(ref));
                }

                /// ADVANCED MATERIALS MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponMod::Type::MAGAZINE);
                    ref.weaponModModel(WeaponMod::Model::MAG_ADVANCED_MATERIALS);
                    ref.levelSkill(8);
                    ref.price(350);
                    ref.name("ADVANCED MATERIALS MAG");
                    ref.description("A smaller, lightweight magazine can make reloads faster "
                        "when it counts.");
                    ref.actionPointPerReload(-1);
                    ref.capacityAmmo(-1);

                    add(move(ref));
                }

                /// OVERSIZED MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponMod::Type::MAGAZINE);
                    ref.weaponModModel(WeaponMod::Model::MAG_OVERSIZED);
                    ref.levelSkill(7);
                    ref.price(275);
                    ref.name("OVERSIZED MAG");
                    ref.description("A smaller, lightweight magazine can make reloads faster "
                        "when it counts.");
                    ref.actionPointPerReload(1);
                    ref.capacityAmmo(8);

                    add(move(ref));
                }

            }
        }

    }
}
