
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include"common.hpp"
#include"slot.hpp"
#include"item.hpp"
#include"ammo.hpp"
#include"damage.hpp"
#include"weaponMod.hpp"
#include"weaponCommon.hpp"
#include<array>
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Global {
        class Factory;
    }

    namespace Object
    {
        constexpr unsigned int nWMSlots = 4; // number of weapon mod slots

        using Slot_WeaponModTypes = std::array<WeaponMod::Type, nWMSlots>;

        struct WeaponReference {
            explicit WeaponReference() noexcept
                :
                itemType_       { Item::Type::WEAPON },
                model_          { WeaponModel::INVALID },
                type_           { WeaponType::INVALID },
                weaponModTypes_ { WeaponMod::Type::INVALID,
                                  WeaponMod::Type::INVALID,
                                  WeaponMod::Type::INVALID,
                                  WeaponMod::Type::INVALID },
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
                tyAmmo_         { Ammo::Type::INVALID },
                tyDmg_          { Damage::Type::INVALID }
            {}

            WeaponReference(const WeaponReference&) = delete;
            WeaponReference& operator=(const WeaponReference&) = delete;
            WeaponReference(WeaponReference&&) = default;
            WeaponReference& operator=(WeaponReference&&) = default;

            void weaponModel(WeaponModel model) noexcept                { model_ = model; }
            void weaponType(WeaponType type) noexcept                   { type_ = type; }
            void slotWeaponModTypes(Slot_WeaponModTypes types) noexcept { weaponModTypes_ = types; }

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
            void ammoType(Ammo::Type type) noexcept                     { tyAmmo_ = type; }
            void damageType(Damage::Type type) noexcept                 { tyDmg_ = type; }

            ItemType                itemType_;      // item type
            WeaponModel             model_;         // weapon model
            WeaponType              type_;          // weapon type (kind)
            Slot_WeaponModTypes     weaponModTypes_;// list of slot types

            Common::Text            name_;          // weapon name
            Common::Text            descrip_;       // description
            Common::Damage          dmgMin_;        // min damage per hit
            Common::Damage          dmgMax_;        // max damage per hit
            Common::Price           price_;         // price
            Common::Range           rangeAttack_;   // attack range
            Common::Capacity        capAmmo_;       // ammo capacity
            Common::Multiplier      mulCritDmg_;    // critical damage multiplier
            Common::Chance          chaHit_;        // base hit chance
            Common::Chance          chaCritDmg_;    // base critical damage chance
            Common::Level           level_;         // weapon level
            Common::Level           levSkill_;      // min level of skill
            Common::Armor           armorPen_;      // penetration
            Common::ActionPoint     apAttack_;      // action points per attack
            Common::ActionPoint     apReload_;      // action points per reload
            Common::NumberShots     shoPerAttack_;  // number of shots per attack
            Ammo::Type              tyAmmo_;        // ammo type
            Damage::Type            tyDmg_;         // damage type
        };

        ///------------------------------------------------------------------------------------------------
        
        class Weapon : public Item {
        public:
            using Model     = WeaponModel;
            using Type      = WeaponType;

            friend Game::Global::Factory;

        protected:
            explicit Weapon(Weapon::Model model) noexcept;

        public:
            Weapon(const Weapon&) = delete;
            Weapon& operator=(const Weapon&) = delete;

            virtual ~Weapon() noexcept {}

            static void initializeReference() {
                if (ref_.size() == 0) initRef();
            }

            virtual void accept(ItemVisitor& visitor) noexcept override {
                visitor.visitWeapon(*this);
            }

            void apply() noexcept;

        private:
            void check() noexcept;

        /// weapon parameters
        public:
            virtual Item::Type itemType() const noexcept override {
                return base_.itemType_;
            }

            virtual Item::Model itemModel() const noexcept override {
                return static_cast<Item::Model>(base_.model_);
            }

            Weapon::Model model() const noexcept {
                return base_.model_;
            }

            Weapon::Type type() const noexcept {
                return base_.type_;
            }

            Common::Text name() const noexcept {
                return base_.name_;
            }

            Common::Text description() const noexcept {
                return base_.descrip_;
            }

            Common::Price price() const noexcept {
                return base_.price_;
            }

            Common::Level level() const noexcept {
                return base_.level_;
            }

            Common::Level levelSkill() const noexcept {
                return base_.levSkill_;
            }

            Common::Multiplier multiplierCritDamage() const noexcept {
                return mulCritDmg_;
            }

            void multiplierCritDamageAdd(Common::Multiplier shift) noexcept {
                mulCritDmg_ += shift;
            }

            Common::Damage damageMinimum() const noexcept {
                return dmgMin_;
            }

            void damageMinimumAdd(Common::Damage shift) noexcept {
                dmgMin_ += shift;
            }

            Common::Damage damageMaximum() const noexcept {
                return dmgMax_;
            }

            void damageMaximumAdd(Common::Damage shift) noexcept {
                dmgMax_ += shift;
            }

            Common::Chance chanceHit() const noexcept {
                return chaHit_;
            }

            void chanceHitAdd(Common::Chance shift) noexcept {
                chaHit_ += shift;
            }

            Common::Chance chanceCritDamage() const noexcept {
                return chaCritDmg_;
            }

            void chanceCritDamageAdd(Common::Chance shift) noexcept {
                chaCritDmg_ += shift;
            }

            Common::Armor armorPenetration() const noexcept {
                return armorPen_;
            }

            void armorPenetrationAdd(Common::Armor shift) noexcept {
                armorPen_ += shift;
            }

            Common::Range rangeAttack() const noexcept {
                return rangeAttack_;
            }

            void rangeAttackAdd(Common::Range shift) noexcept {
                rangeAttack_ += shift;
            }

            Common::NumberShots shotsPerAttack() const noexcept {
                return shoPerAttack_;
            }

            void shotsPerAttackAdd(Common::NumberShots shift) noexcept {
                shoPerAttack_ += shift;
            }

            Common::ActionPoint actionPointPerAttack() const noexcept {
                return apAttack_;
            }

            void actionPointPerAttackAdd(Common::ActionPoint shift) noexcept {
                apAttack_ += shift;
            }

            Common::ActionPoint actionPointPerReload() const noexcept {
                return apReload_;
            }

            void actionPointPerReloadAdd(Common::ActionPoint shift) noexcept {
                apReload_ += shift;
            }

            Common::Capacity capacityAmmo() const noexcept {
                return capAmmo_;
            }

            void capacityAmmoAdd(Common::Capacity shift) noexcept {
                capAmmo_ += shift;
            }

            Ammo::Type ammoType() const noexcept {
                return tyAmmo_;
            }

            void ammoType(Ammo::Type type) noexcept {
                tyAmmo_ = type;
            }

            Damage::Type damageType() const noexcept {
                return tyDmg_;
            }

            void damageType(Damage::Type type) noexcept {
                tyDmg_ = type;
            }

        /// slots
        public:
            const Common::Slot<WeaponMod, nWMSlots>& slotMod() const noexcept {
                return slotWeaponMod_;
            }

            Common::Slot<WeaponMod, nWMSlots>& slotMod() noexcept {
                return slotWeaponMod_;
            }

        private:
            static void initRef();

            static void add(WeaponReference common) {
                ref_[static_cast<std::underlying_type_t<Weapon::Model>>(common.model_)] = std::move(common);
            }

        private:
            const WeaponReference&      base_;          // reference, sample, template

            Common::Damage              dmgMin_;        // min damage per hit
            Common::Damage              dmgMax_;        // max damage per hit
            Common::Range               rangeAttack_;   // attack range
            Common::Capacity            capAmmo_;       // ammo capacity
            Common::Multiplier          mulCritDmg_;    // crit damage multiplier
            Common::Chance              chaHit_;        // base hit chance
            Common::Chance              chaCritDmg_;    // base critical damage chance
            Common::Armor               armorPen_;      // penetration
            Common::ActionPoint         apAttack_;      // action points per attack
            Common::ActionPoint         apReload_;      // action points per reload
            Common::NumberShots         shoPerAttack_;  // number of shots per attack
            Ammo::Type                  tyAmmo_;        // ammo type
            Damage::Type                tyDmg_;         // damage type

            Common::Slot<WeaponMod, nWMSlots>   slotWeaponMod_; // weapon mod slots

            static std::vector<WeaponReference> ref_;           // references
        };

    }
}

#endif // !WEAPON_HPP
