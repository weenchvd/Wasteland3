
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
#include"weaponReference.hpp"
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Global {
        class Factory;
    }

    namespace Object
    {
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
