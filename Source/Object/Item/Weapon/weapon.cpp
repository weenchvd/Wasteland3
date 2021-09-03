
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weapon.hpp"
#include"item.hpp"
#include"itemCommon.hpp"
#include"itemVisitor.hpp"
#include<memory>
#include<string>
#include<vector>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace Common;

        Weapon::Weapon(WeaponModel model) noexcept
            : Item          { ItemType::Weapon, static_cast<ItemModel>(model) },
            base_           { ref_[static_cast<underlying_type_t<WeaponModel>>(model)] },
            critMul_        { base_.critMul_ },
            minDmg_         { base_.minDmg_ },
            maxDmg_         { base_.maxDmg_ },
            hitChance_      { base_.hitChance_ },
            critChance_     { base_.critChance_ },
            penet_          { base_.penet_ },
            range_          { base_.range_ },
            nAttacks_       { base_.nAttacks_ },
            ap_             { base_.ap_ },
            apReload_       { base_.apReload_ },
            ammoCap_        { base_.ammoCap_ },
            dmgTy_          { base_.dmgTy_ },
            mod_            { base_.modTypes_ }
        {}

        void Weapon::apply() noexcept
        {
            critMul_        = base_.critMul_;
            minDmg_         = base_.minDmg_;
            maxDmg_         = base_.maxDmg_;
            hitChance_      = base_.hitChance_;
            critChance_     = base_.critChance_;
            penet_          = base_.penet_;
            range_          = base_.range_;
            nAttacks_       = base_.nAttacks_;
            ap_             = base_.ap_;
            apReload_       = base_.apReload_;
            ammoCap_        = base_.ammoCap_;

            for (unsigned int i = 0; i < mod_.size(); ++i) {
                if (mod_[i]) {
                    mod_[i]->apply(*this);
                }
            }

            check();
        }

        void Weapon::check() noexcept
        {
            if (critMul_    < refMin_.critMul_)     critMul_    = refMin_.critMul_;
            if (minDmg_     < refMin_.minDmg_)      minDmg_     = refMin_.minDmg_;
            if (maxDmg_     < refMin_.maxDmg_)      maxDmg_     = refMin_.maxDmg_;
            if (hitChance_  < refMin_.hitChance_)   hitChance_  = refMin_.hitChance_;
            if (critChance_ < refMin_.critChance_)  critChance_ = refMin_.critChance_;
            if (penet_      < refMin_.penet_)       penet_      = refMin_.penet_;
            if (range_      < refMin_.range_)       range_      = refMin_.range_;
            if (nAttacks_   < refMin_.nAttacks_)    nAttacks_   = refMin_.nAttacks_;
            if (ap_         < refMin_.ap_)          ap_         = refMin_.ap_;
            if (apReload_   < refMin_.apReload_)    apReload_   = refMin_.apReload_;
            if (ammoCap_    < refMin_.ammoCap_)     ammoCap_    = refMin_.ammoCap_;
        }

        bool Weapon::setMod(unique_ptr<Item>& item) noexcept
        {
            if (!item) {
                return false;
            }
            TypeItemVisitor visitor;
            item->accept(visitor);
            if (visitor.isWeaponMod()) {
                WeaponMod* mod = static_cast<WeaponMod*>(item.get());
                auto slotNumber = mod_.slotNumber(mod->type());
                if (slotNumber != mod_.slotNotFound) {
                    swapUP(item, mod_[slotNumber]);
                    return true;
                }
            }
            return false;
        }

        bool Weapon::setMod(unique_ptr<Item>& item, unsigned int slotNumber) noexcept
        {
            if (!item || slotNumber >= mod_.size() || mod_.kind(slotNumber) == WeaponModType::INVALID) {
                return false;
            }
            TypeItemVisitor visitor;
            item->accept(visitor);
            if (visitor.isWeaponMod()) {
                WeaponMod* mod = static_cast<WeaponMod*>(item.get());
                if (mod_.kind(slotNumber) == mod->type()) {
                    swapUP(item, mod_[slotNumber]);
                    return true;
                }
            }
            return false;
        }

        bool Weapon::unsetMod(unique_ptr<Item>& item, unsigned int slotNumber) noexcept
        {
            if (item || slotNumber >= mod_.size() || !mod_[slotNumber]) {
                return false;
            }
            item.reset(mod_[slotNumber].release());
            return true;
        }

        vector<WeaponReference> Weapon::ref_ = vector<WeaponReference>();
        WeaponReference Weapon::refDef_;
        WeaponReference Weapon::refMin_;

        void Weapon::initializeRefMin()
        {
            refMin_.price(0);
            refMin_.minDamage(1);
            refMin_.maxDamage(1);
            refMin_.hitChance(0);
            refMin_.critChance(0);
            refMin_.critMultiplier(0.0);
            refMin_.penetration(0);
            refMin_.attackRange(1);
            refMin_.attackNumber(1);
            refMin_.actionPoints(1);
            refMin_.actionPointsReload(1);
            refMin_.level(0);
            refMin_.skillLevel(0);
            refMin_.ammoCapacity(1);
        }

        void Weapon::initialize()
        {
            initializeRefMin();
            
            ref_.resize(static_cast<underlying_type_t<WeaponModel>>(WeaponModel::NUMBER_OF_MODELS));

            ///// TEMPLATE
            //{
            //    WeaponReference ref;
            //    ref.weaponType();
            //    ref.weaponModel();
            //    ref.weaponModTypes(Weapon_ModTypes{ WeaponModType:,
            //                                        WeaponModType:,
            //                                        WeaponModType:,
            //                                        WeaponModType: });
            //    ref.price();
            //    ref.minDamage();
            //    ref.maxDamage();
            //    ref.hitChance();
            //    ref.critChance();
            //    ref.critMultiplier();
            //    ref.penetration();
            //    ref.attackRange();
            //    ref.attackNumber();
            //    ref.actionPoints();
            //    ref.actionPointsReload();
            //    ref.level();
            //    ref.skillLevel();
            //    ref.ammoCapacity();
            //    ref.ammoType();
            //    ref.damageType();
            //    ref.name();
            //    ref.description();

            //    add(move(ref));
            //}

            /// AR
            {
                /// KALASH 97
                {
                    WeaponReference ref;
                    ref.weaponType(WeaponType::AR);
                    ref.weaponModel(WeaponModel::AR_KALASH97);
                    ref.weaponModTypes(Weapon_ModTypes{ WeaponModType::BARREL,
                                                        WeaponModType::UNDERBARREL,
                                                        WeaponModType::SCOPE,
                                                        WeaponModType::MAGAZINE });
                    ref.price(1175);
                    ref.minDamage(26);
                    ref.maxDamage(32);
                    ref.hitChance(75);
                    ref.critChance(0);
                    ref.critMultiplier(1.5);
                    ref.penetration(18);
                    ref.attackRange(18);
                    ref.attackNumber(3);
                    ref.actionPoints(4);
                    ref.actionPointsReload(2);
                    ref.level(17);
                    ref.skillLevel(6);
                    ref.ammoCapacity(25);
                    ref.ammoType(AmmoType::A_7_62);
                    ref.damageType(DamageType::NORMAL);
                    ref.name("KALASH 97");
                    ref.description("Description");

                    add(move(ref));
                }

                /// SOCOM ASSAULT RIFLE
                {
                    WeaponReference ref;
                    ref.weaponType(WeaponType::AR);
                    ref.weaponModel(WeaponModel::AR_SOCOM);
                    ref.weaponModTypes(Weapon_ModTypes{ WeaponModType::BARREL,
                                                        WeaponModType::UNDERBARREL,
                                                        WeaponModType::SCOPE,
                                                        WeaponModType::MAGAZINE });
                    ref.price(1800);
                    ref.minDamage(40);
                    ref.maxDamage(48);
                    ref.hitChance(75);
                    ref.critChance(0);
                    ref.critMultiplier(1.5);
                    ref.penetration(22);
                    ref.attackRange(18);
                    ref.attackNumber(3);
                    ref.actionPoints(4);
                    ref.actionPointsReload(2);
                    ref.level(21);
                    ref.skillLevel(7);
                    ref.ammoCapacity(30);
                    ref.ammoType(AmmoType::A_5_56);
                    ref.damageType(DamageType::NORMAL);
                    ref.name("SOCOM ASSAULT RIFLE");
                    ref.description("Description");

                    add(move(ref));
                }
            }

            /// SMG
            {
                /// RIPPER
                {
                    WeaponReference ref; // TODO (stats from KALASH97)
                    ref.weaponType(WeaponType::SMG);
                    ref.weaponModel(WeaponModel::SMG_RIPPER);
                    ref.weaponModTypes(Weapon_ModTypes{ WeaponModType::BARREL,
                                                        WeaponModType::UNDERBARREL,
                                                        WeaponModType::SCOPE,
                                                        WeaponModType::MAGAZINE });
                    ref.price(1175);
                    ref.minDamage(26);
                    ref.maxDamage(32);
                    ref.hitChance(75);
                    ref.critChance(0);
                    ref.critMultiplier(1.5);
                    ref.penetration(18);
                    ref.attackRange(18);
                    ref.attackNumber(3);
                    ref.actionPoints(4);
                    ref.actionPointsReload(2);
                    ref.level(17);
                    ref.skillLevel(6);
                    ref.ammoCapacity(25);
                    ref.ammoType(AmmoType::A_7_62);
                    ref.damageType(DamageType::NORMAL);
                    ref.name("RIPPER");
                    ref.description("Description");

                    add(move(ref));
                }
            }

        }

    }
}