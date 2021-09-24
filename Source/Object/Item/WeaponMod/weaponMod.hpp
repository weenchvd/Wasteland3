
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_MOD_HPP
#define WEAPON_MOD_HPP

#include"common.hpp"
#include"item.hpp"
#include"ammo.hpp"
#include"weaponModCommon.hpp"
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
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
                ammoTy_         { AmmoType::INVALID },
                dmgTy_          { DamageType::INVALID },
                type_           { WeaponModType::INVALID }
            {}

            WeaponModReference(const WeaponModReference&) = delete;
            WeaponModReference& operator=(const WeaponModReference&) = delete;
            WeaponModReference(WeaponModReference&&) = default;
            WeaponModReference& operator=(WeaponModReference&&) = default;

            void name(Common::Name name) noexcept                       { name_ = name; }
            void description(Common::Description descr) noexcept        { descrip_ = descr; }
            void critMultiplier(CritMultiplier mult) noexcept           { critMul_ = mult; }
            void price(Common::Price price) noexcept                    { price_ = price; }
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
            void level(Common::Level level) noexcept                    { modLvl_ = level; }
            void skillLevel(SkillLevel level) noexcept                  { skillLvl_ = level; }
            void ammoCapacity(AmmoCapacity capacity) noexcept           { ammoCap_ = capacity; }
            void ammoType(AmmoType type) noexcept                       { ammoTy_ = type; }
            void damageType(DamageType type) noexcept                   { dmgTy_ = type; }
            void weaponModType(WeaponModType type) noexcept             { type_ = type; }

            Common::Name                name_;          // weapon mod name
            Common::Description         descrip_;       // description
            CritMultiplier              critMul_;       // crit damage multiplier
            Common::Price               price_;         // price
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
            Common::Level               modLvl_;        // weapon mod level
            SkillLevel                  skillLvl_;      // min level of skill
            AmmoCapacity                ammoCap_;       // ammo capacity
            AmmoType                    ammoTy_;        // ammo type
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

            static std::unique_ptr<Item> create(WeaponModModel model) {
                if (ref_.size() == 0) initialize();
                return std::unique_ptr<Item>(new WeaponMod(std::move(model)));
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
                ref_[static_cast<std::underlying_type_t<WeaponModModel>>(ref.model_)] = std::move(ref);
            }

        private:
            const WeaponModReference&  base_;           // reference, sample, template

            static std::vector<WeaponModReference>  ref_;           // references
        };

    }
}

#endif // !WEAPON_MOD_HPP
