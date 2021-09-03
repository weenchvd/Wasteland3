
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_HPP
#define WEAPON_MOD_HPP

#include"common.hpp"
#include"item.hpp"
#include"itemCommon.hpp"
#include"itemVisitor.hpp"
#include"ammoCommon.hpp"
#include"weaponModCommon.hpp"
#include<memory>
#include<vector>
#include<type_traits>

namespace Game
{
    namespace Object
    {
        using namespace std;
        using namespace Common;

        struct WeaponModReference {
            explicit WeaponModReference() noexcept
                :
                name_           {},
                descrip_        {},
                critMul_        { 0.0 },
                price_          { 0 },
                model_          { WeaponModModel::INVALID },
                minDmg_         { 0 },
                maxDmg_         { 0 },
                hitChance_      { 0 },
                critChance_     { 0 },
                penet_          { 0 },
                range_          { 0 },
                nAttacks_       { 0 },
                ap_             { 0 },
                apReload_       { 0 },
                modLvl_         { 0 },
                skillLvl_       { 0 },
                ammoCap_        { 0 },
                //changeAmmoTy_   { false },
                ammoTy_         { AmmoType::INVALID },
                //changeDmgTy_    { false },
                dmgTy_          { DamageType::INVALID },
                type_           { WeaponModType::INVALID }
            {}

            WeaponModReference(const WeaponModReference&) = delete;
            WeaponModReference& operator=(const WeaponModReference&) = delete;
            WeaponModReference(WeaponModReference&&) = default;
            WeaponModReference& operator=(WeaponModReference&&) = default;

            void name(Name name) noexcept                               { name_ = name; }
            void description(Description descr) noexcept                { descrip_ = descr; }
            void critMultiplier(CritMultiplier mult) noexcept           { critMul_ = mult; }
            void price(Price price) noexcept                            { price_ = price; }
            void weaponModModel(WeaponModModel model) noexcept          { model_ = model; }
            void minDamage(MinDamage damage) noexcept                   { minDmg_ = damage; }
            void maxDamage(MaxDamage damage) noexcept                   { maxDmg_ = damage; }
            void hitChance(HitChance chance) noexcept                   { hitChance_ = chance; }
            void critChance(CritChance chance) noexcept                 { critChance_ = chance; }
            void penetration(Penetration penet) noexcept                { penet_ = penet; }
            void attackRange(AttackRange range) noexcept                { range_ = range; }
            void attackNumber(AttackNumber number) noexcept             { nAttacks_ = number; }
            void actionPoints(ActionPoints ap) noexcept                 { ap_ = ap; }
            void actionPointsReload(ActionPointsReload ap) noexcept     { apReload_ = ap; }
            void level(Level level) noexcept                            { modLvl_ = level; }
            void skillLevel(SkillLevel level) noexcept                  { skillLvl_ = level; }
            void ammoCapacity(AmmoCapacity capacity) noexcept           { ammoCap_ = capacity; }
            //void changeAmmoType(bool value) noexcept                    { changeAmmoTy_ = value; }
            void ammoType(AmmoType type) noexcept                       { ammoTy_ = type; }
            //void changeDamageType(bool value) noexcept                  { changeDmgTy_ = value; }
            void damageType(DamageType type) noexcept                   { dmgTy_ = type; }
            void weaponModType(WeaponModType type) noexcept             { type_ = type; }

            Name                        name_;          // weapon mod name
            Description                 descrip_;       // description
            CritMultiplier              critMul_;       // crit damage multiplier
            Price                       price_;         // price
            WeaponModModel              model_;         // weapon mod model
            MinDamage                   minDmg_;        // min damage per hit
            MaxDamage                   maxDmg_;        // max damage per hit
            HitChance                   hitChance_;     // base hit chance
            CritChance                  critChance_;    // crit chance
            Penetration                 penet_;         // penetration
            AttackRange                 range_;         // attack range
            AttackNumber                nAttacks_;      // number of attacks per turn
            ActionPoints                ap_;            // action points per attack
            ActionPointsReload          apReload_;      // action points per reload
            Level                       modLvl_;        // weapon mod level
            SkillLevel                  skillLvl_;      // min level of skill
            AmmoCapacity                ammoCap_;       // ammo capacity
            //bool                        changeAmmoTy_;  // change ammo type
            AmmoType                    ammoTy_;        // ammo type
            //bool                        changeDmgTy_;   // change damage type
            DamageType                  dmgTy_;         // damage type
            WeaponModType               type_;          // weapon mod type (kind)
        };

        ///------------------------------------------------------------------------------------------------

        class Weapon;

        class WeaponMod : public Item {
        public:
            using Model     = WeaponModModel;
            using Type      = WeaponModType;

        public:
            WeaponMod(const WeaponMod&) = delete;
            WeaponMod& operator=(const WeaponMod&) = delete;

            virtual ~WeaponMod() noexcept {}

            static unique_ptr<Item> create(WeaponModModel model) {
                if (ref_.size() == 0) initialize();
                return unique_ptr<Item>(new WeaponMod(move(model)));
            }

            virtual void accept(ItemVisitor& visitor) noexcept override {
                visitor.visitWeaponMod(*this);
            }

            void apply(Weapon& weapon);

        public:
            WeaponModType type() const noexcept {
                return base_.type_;
            }

        protected:
            explicit WeaponMod(WeaponModModel model) noexcept;

        private:
            static void initialize();

            static void add(WeaponModReference ref) {
                ref_[static_cast<underlying_type_t<WeaponModModel>>(ref.model_)] = move(ref);
            }

        private:
            const WeaponModReference&  base_;           // reference, sample, template

            static vector<WeaponModReference>   ref_;           // references
            static WeaponModReference           refDef_;        // default reference
        };

    }
}

#endif // !WEAPON_MOD_HPP
