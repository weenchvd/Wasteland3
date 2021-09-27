
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"weapon.hpp"
#include<string>

namespace Game
{
    namespace Object
    {
        using namespace std;

        Weapon::Weapon(WeaponModel model) noexcept
            : Item          { ItemType::Weapon, static_cast<ItemModel>(model) },
            base_           { ref_[static_cast<underlying_type_t<WeaponModel>>(model)] },
            dmgMin_         { base_.dmgMin_ },
            dmgMax_         { base_.dmgMax_ },
            rangeAttack_    { base_.rangeAttack_ },
            capAmmo_        { base_.capAmmo_ },
            mulCritDmg_     { base_.mulCritDmg_ },
            chaHit_         { base_.chaHit_ },
            chaCritDmg_     { base_.chaCritDmg_ },
            armorPen_       { base_.armorPen_ },
            apAttack_       { base_.apAttack_ },
            apReload_       { base_.apReload_ },
            shoPerAttack_   { base_.shoPerAttack_ },
            tyAmmo_         { base_.tyAmmo_ },
            tyDmg_          { base_.tyDmg_ },
            slotWeaponMod_  { base_.weaponModTypes_ }
        {}

        void Weapon::apply() noexcept
        {
            dmgMin_         = base_.dmgMin_;
            dmgMax_         = base_.dmgMax_;
            rangeAttack_    = base_.rangeAttack_;
            capAmmo_        = base_.capAmmo_;
            mulCritDmg_     = base_.mulCritDmg_;
            chaHit_         = base_.chaHit_;
            chaCritDmg_     = base_.chaCritDmg_;
            armorPen_       = base_.armorPen_;
            apAttack_       = base_.apAttack_;
            apReload_       = base_.apReload_;
            shoPerAttack_   = base_.shoPerAttack_;

            for (unsigned int i = 0; i < slotWeaponMod_.size(); ++i) {
                if (slotWeaponMod_[i]) {
                    slotWeaponMod_[i]->apply(*this);
                }
            }

            check();
        }

        void Weapon::check() noexcept
        {
            WeaponReference& refMin = ref_[static_cast<underlying_type_t<WeaponModel>>(WeaponModel::MINIMUM)];
            if (dmgMin_         < refMin.dmgMin_)           dmgMin_         = refMin.dmgMin_;
            if (dmgMax_         < refMin.dmgMax_)           dmgMax_         = refMin.dmgMax_;
            if (rangeAttack_    < refMin.rangeAttack_)      rangeAttack_    = refMin.rangeAttack_;
            if (capAmmo_        < refMin.capAmmo_)          capAmmo_        = refMin.capAmmo_;
            if (mulCritDmg_     < refMin.mulCritDmg_)       mulCritDmg_     = refMin.mulCritDmg_;
            if (chaHit_         < refMin.chaHit_)           chaHit_         = refMin.chaHit_;
            if (chaCritDmg_     < refMin.chaCritDmg_)       chaCritDmg_     = refMin.chaCritDmg_;
            if (armorPen_       < refMin.armorPen_)         armorPen_       = refMin.armorPen_;
            if (apAttack_       < refMin.apAttack_)         apAttack_       = refMin.apAttack_;
            if (apReload_       < refMin.apReload_)         apReload_       = refMin.apReload_;
            if (shoPerAttack_   < refMin.shoPerAttack_)     shoPerAttack_   = refMin.shoPerAttack_;
        }

        vector<WeaponReference> Weapon::ref_ = vector<WeaponReference>();

        void Weapon::initRef()
        {
            ref_.resize(static_cast<underlying_type_t<WeaponModel>>(WeaponModel::NUMBER_OF_MODELS));

            ///// TEMPLATE
            //{
            //    WeaponReference ref;
            //    ref.weaponType();
            //    ref.weaponModel();
            //    ref.slotWeaponModTypes(Slot_WeaponModTypes{ WeaponModType::INVALID,
            //                                                WeaponModType::INVALID,
            //                                                WeaponModType::INVALID,
            //                                                WeaponModType::INVALID });
            //    ref.price();
            //    ref.damageMinimum();
            //    ref.damageMaximum();
            //    ref.chanceHit();
            //    ref.chanceCritDamage();
            //    ref.multiplierCritDamage();
            //    ref.armorPenetration();
            //    ref.rangeAttack();
            //    ref.shotsPerAttack();
            //    ref.actionPointPerAttack();
            //    ref.actionPointPerReload();
            //    ref.level();
            //    ref.levelSkill();
            //    ref.capacityAmmo();
            //    ref.ammoType();
            //    ref.damageType();
            //    ref.name();
            //    ref.description();

            //    add(move(ref));
            //}

            /// MINIMUM
            {
                WeaponReference refMin;
                refMin.weaponModel(WeaponModel::MINIMUM);
                refMin.price(0);
                refMin.damageMinimum(1);
                refMin.damageMaximum(1);
                refMin.chanceHit(0);
                refMin.chanceCritDamage(0);
                refMin.multiplierCritDamage(0);
                refMin.armorPenetration(0);
                refMin.rangeAttack(1);
                refMin.shotsPerAttack(1);
                refMin.actionPointPerAttack(1);
                refMin.actionPointPerReload(1);
                refMin.level(1);
                refMin.levelSkill(0);
                refMin.capacityAmmo(1);

                add(move(refMin));
            }

            /// AR
            {
                /// KALASH 97
                {
                    WeaponReference ref;
                    ref.weaponType(WeaponType::AR);
                    ref.weaponModel(WeaponModel::AR_KALASH97);
                    ref.slotWeaponModTypes(Slot_WeaponModTypes{ WeaponModType::BARREL,
                                                                WeaponModType::UNDERBARREL,
                                                                WeaponModType::SCOPE,
                                                                WeaponModType::MAGAZINE });
                    ref.price(1175);
                    ref.damageMinimum(26);
                    ref.damageMaximum(32);
                    ref.chanceHit(750);
                    ref.chanceCritDamage(0);
                    ref.multiplierCritDamage(150);
                    ref.armorPenetration(18);
                    ref.rangeAttack(18);
                    ref.shotsPerAttack(3);
                    ref.actionPointPerAttack(4);
                    ref.actionPointPerReload(2);
                    ref.level(17);
                    ref.levelSkill(6);
                    ref.capacityAmmo(25);
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
                    ref.slotWeaponModTypes(Slot_WeaponModTypes{ WeaponModType::BARREL,
                                                                WeaponModType::UNDERBARREL,
                                                                WeaponModType::SCOPE,
                                                                WeaponModType::MAGAZINE });
                    ref.price(1800);
                    ref.damageMinimum(40);
                    ref.damageMaximum(48);
                    ref.chanceHit(750);
                    ref.chanceCritDamage(0);
                    ref.multiplierCritDamage(150);
                    ref.armorPenetration(22);
                    ref.rangeAttack(18);
                    ref.shotsPerAttack(3);
                    ref.actionPointPerAttack(4);
                    ref.actionPointPerReload(2);
                    ref.level(21);
                    ref.levelSkill(7);
                    ref.capacityAmmo(30);
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
                    ref.slotWeaponModTypes(Slot_WeaponModTypes{ WeaponModType::BARREL,
                                                                WeaponModType::UNDERBARREL,
                                                                WeaponModType::SCOPE,
                                                                WeaponModType::MAGAZINE });
                    ref.price(1175);
                    ref.damageMinimum(26);
                    ref.damageMaximum(32);
                    ref.chanceHit(750);
                    ref.chanceCritDamage(0);
                    ref.multiplierCritDamage(150);
                    ref.armorPenetration(18);
                    ref.rangeAttack(18);
                    ref.shotsPerAttack(3);
                    ref.actionPointPerAttack(4);
                    ref.actionPointPerReload(2);
                    ref.level(17);
                    ref.levelSkill(6);
                    ref.capacityAmmo(25);
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