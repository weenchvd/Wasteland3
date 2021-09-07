
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weaponMod.hpp"
#include"item.hpp"
#include"itemCommon.hpp"
#include"weapon.hpp"
#include<string>
#include<vector>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        WeaponMod::WeaponMod(WeaponModModel model) noexcept
            : Item          { ItemType::WeaponMod, static_cast<ItemModel>(model) },
            base_           { ref_[static_cast<underlying_type_t<WeaponModModel>>(model)] }
        {}

        void WeaponMod::apply(Weapon& weapon)
        {
            weapon.addCritMultiplier(base_.critMul_);
            weapon.addMinDamage(base_.minDmg_);
            weapon.addMaxDamage(base_.maxDmg_);
            weapon.addHitChance(base_.hitChance_);
            weapon.addCritChance(base_.critChance_);
            weapon.addPenetration(base_.penet_);
            weapon.addAttackRange(base_.range_);
            weapon.addAttackNumber(base_.nAttacks_);
            weapon.addActionPoints(base_.ap_);
            weapon.addActionPointsReload(base_.apReload_);
            weapon.addAmmoCapacity(base_.ammoCap_);
            if (base_.ammoTy_ != AmmoType::INVALID) weapon.ammoType(base_.ammoTy_);
            if (base_.dmgTy_ != DamageType::INVALID) weapon.damageType(base_.dmgTy_);
        }

        vector<WeaponModReference> WeaponMod::ref_ = vector<WeaponModReference>();
        WeaponModReference WeaponMod::refDef_;

        void WeaponMod::initialize()
        {
            ref_.resize(static_cast<underlying_type_t<WeaponModModel>>(WeaponModModel::NUMBER_OF_MODELS));
            
            ///// TEMPLATE
            //{
            //    WeaponModReference ref;
            //    ref.weaponModType();
            //    ref.weaponModModel();
            //    ref.skillLevel();
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
                    ref.weaponModType(WeaponModType::BARREL);
                    ref.weaponModModel(WeaponModModel::BARREL_SHORTENED);
                    ref.skillLevel(8);
                    ref.price(600);
                    ref.name("SHORTENED BARREL");
                    ref.description("This short barrel reduces Chance to Hit but increases "
                        "bullet velocity dramatically. Best for skilled marksmen.");
                    ref.minDamage(20);
                    ref.maxDamage(20);
                    ref.hitChance(-10);

                    add(move(ref));
                }

                /// LIGHTWEIGHT BARREL
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponModType::BARREL);
                    ref.weaponModModel(WeaponModModel::BARREL_LIGHTWEIGHT);
                    ref.skillLevel(8);
                    ref.price(600);
                    ref.name("LIGHTWEIGHT BARREL");
                    ref.description("Lighter materials in this barrel significantly reduce weight "
                        "at the cost of firepower.");
                    ref.minDamage(-12);
                    ref.maxDamage(-12);
                    ref.hitChance(12);
                    ref.penetration(1);

                    add(move(ref));
                }

            }

            /// MAGAZINE
            {
                /// QUICKFIRE MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponModType::MAGAZINE);
                    ref.weaponModModel(WeaponModModel::MAG_QUICKFIRE);
                    ref.skillLevel(10);
                    ref.price(450);
                    ref.name("QUICKFIRE MAG");
                    ref.description("This magazine has a built-in mechanism to slam bullets directry "
                        "into the chamber.");
                    ref.actionPoints(-1);

                    add(move(ref));
                }

                /// ADVANCED MATERIALS MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponModType::MAGAZINE);
                    ref.weaponModModel(WeaponModModel::MAG_ADVANCED_MATERIALS);
                    ref.skillLevel(8);
                    ref.price(350);
                    ref.name("ADVANCED MATERIALS MAG");
                    ref.description("A smaller, lightweight magazine can make reloads faster "
                        "when it counts.");
                    ref.actionPointsReload(-1);
                    ref.ammoCapacity(-1);

                    add(move(ref));
                }

                /// OVERSIZED MAG
                {
                    WeaponModReference ref;
                    ref.weaponModType(WeaponModType::MAGAZINE);
                    ref.weaponModModel(WeaponModModel::MAG_OVERSIZED);
                    ref.skillLevel(7);
                    ref.price(275);
                    ref.name("OVERSIZED MAG");
                    ref.description("A smaller, lightweight magazine can make reloads faster "
                        "when it counts.");
                    ref.actionPointsReload(1);
                    ref.ammoCapacity(8);

                    add(move(ref));
                }

            }
        }

    }
}
