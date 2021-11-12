
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
                model_          { WeaponModModel::INVALID },
                type_           { WeaponModType::INVALID },
                name_           {},
                descrip_        {},
                dmgMin_         { 0 },
                dmgMax_         { 0 },
                price_          { 0 },
                rangeAttack_    { 0 },
                capAmmo_        { 0 },
                mulCritDmg_     { 0 },
                chaHit_         { 0 },
                chaCritDmg_     { 0 },
                level_          { 0 },
                levSkill_       { 0 },
                armorPen_       { 0 },
                apAttack_       { 0 },
                apReload_       { 0 },
                shoPerAttack_   { 0 },
                tyAmmo_         { AmmoType::INVALID },
                tyDmg_          { DamageType::INVALID }
            {}

            WeaponModReference(const WeaponModReference&) = delete;
            WeaponModReference& operator=(const WeaponModReference&) = delete;
            WeaponModReference(WeaponModReference&&) = default;
            WeaponModReference& operator=(WeaponModReference&&) = default;
            
            void weaponModModel(WeaponModModel model) noexcept          { model_ = model; }
            void weaponModType(WeaponModType type) noexcept             { type_ = type; }

            void name(Common::Text text) noexcept                       { name_ = text; }
            void description(Common::Text text) noexcept                { descrip_ = text; }
            void damageMinimum(Common::Damage dmg) noexcept             { dmgMin_ = dmg; }
            void damageMaximum(Common::Damage dmg) noexcept             { dmgMax_ = dmg; }
            void price(Common::Price price) noexcept                    { price_ = price; }
            void rangeAttack(Common::Range range) noexcept              { rangeAttack_ = range; }
            void capacityAmmo(Common::Capacity capacity) noexcept       { capAmmo_ = capacity; }
            void multiplierCritDamage(Common::Multiplier mul) noexcept  { mulCritDmg_ = mul; }
            void chanceHit(Common::Chance chance) noexcept              { chaHit_ = chance; }
            void chanceCritDamage(Common::Chance chance) noexcept       { chaCritDmg_ = chance; }
            void level(Common::Level level) noexcept                    { level_ = level; }
            void levelSkill(Common::Level level) noexcept               { levSkill_ = level; }
            void armorPenetration(Common::Armor ar) noexcept            { armorPen_ = ar; }
            void actionPointPerAttack(Common::ActionPoint ap) noexcept  { apAttack_ = ap; }
            void actionPointPerReload(Common::ActionPoint ap) noexcept  { apReload_ = ap; }
            void shotsPerAttack(Common::NumberShots num) noexcept       { shoPerAttack_ = num; }
            void ammoType(AmmoType type) noexcept                       { tyAmmo_ = type; }
            void damageType(DamageType type) noexcept                   { tyDmg_ = type; }

            WeaponModModel          model_;         // weapon mod model
            WeaponModType           type_;          // weapon mod type (kind)

            Common::Text            name_;          // weapon mod name
            Common::Text            descrip_;       // description
            Common::Damage          dmgMin_;        // min damage per hit
            Common::Damage          dmgMax_;        // max damage per hit
            Common::Price           price_;         // price
            Common::Range           rangeAttack_;   // attack range
            Common::Capacity        capAmmo_;       // ammo capacity
            Common::Multiplier      mulCritDmg_;    // critical damage multiplier
            Common::Chance          chaHit_;        // base hit chance
            Common::Chance          chaCritDmg_;    // base critical damage chance
            Common::Level           level_;         // weapon mod level
            Common::Level           levSkill_;      // min level of skill
            Common::Armor           armorPen_;      // penetration
            Common::ActionPoint     apAttack_;      // action points per attack
            Common::ActionPoint     apReload_;      // action points per reload
            Common::NumberShots     shoPerAttack_;  // number of shots per attack
            AmmoType                tyAmmo_;        // ammo type
            DamageType              tyDmg_;         // damage type
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
                if (ref_.size() == 0) initRef();
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
            static void initRef();

            static void add(WeaponModReference ref) {
                ref_[static_cast<std::underlying_type_t<WeaponModModel>>(ref.model_)] = std::move(ref);
            }

        /// weapon mod parameters
        public:
            Common::Text name() const noexcept {
                return base_.name_;
            }

        private:
            const WeaponModReference&  base_;           // reference, sample, template

            static std::vector<WeaponModReference>  ref_;           // references
        };

    }
}

#endif // !WEAPON_MOD_HPP
