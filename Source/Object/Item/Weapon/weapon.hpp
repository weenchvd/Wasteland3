
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
#include"weaponMod.hpp"
#include"weaponCommon.hpp"
#include<array>
#include<memory>
#include<type_traits>
#include<vector>

namespace Game
{
    namespace Object
    {
        constexpr unsigned int nWMSlots = 4; // number of weapon mod slots

        using Slot_WeaponModTypes = std::array<WeaponModType, nWMSlots>;

        struct WeaponReference {
            explicit WeaponReference() noexcept
                :
                name_           {},
                descrip_        {},
                critMul_        { 0.0 },
                modTypes_       { WeaponModType::INVALID,
                                  WeaponModType::INVALID,
                                  WeaponModType::INVALID,
                                  WeaponModType::INVALID },
                price_          { 0 },
                model_          { WeaponModel::INVALID },
                minDmg_         { 0 },
                maxDmg_         { 0 },
                hitChance_      { 0 },
                critChance_     { 0 },
                penet_          { 0 },
                range_          { 0 },
                nAttacks_       { 0 },
                ap_             { 0 },
                apReload_       { 0 },
                weaponLvl_      { 0 },
                skillLvl_       { 0 },
                ammoCap_        { 0 },
                ammoTy_         { AmmoType::INVALID },
                dmgTy_          { DamageType::INVALID },
                type_           { WeaponType::INVALID }
            {}

            WeaponReference(const WeaponReference&) = delete;
            WeaponReference& operator=(const WeaponReference&) = delete;
            WeaponReference(WeaponReference&&) = default;
            WeaponReference& operator=(WeaponReference&&) = default;

            void name(Common::Name name) noexcept                       { name_ = name; }
            void description(Common::Description descr) noexcept        { descrip_ = descr; }
            void critMultiplier(CritMultiplier mult) noexcept           { critMul_ = mult; }
            void weaponModTypes(Slot_WeaponModTypes types) noexcept     { modTypes_ = types; }
            void price(Common::Price price) noexcept                    { price_ = price; }
            void weaponModel(WeaponModel model) noexcept                { model_ = model; }
            void minDamage(MinDamage damage) noexcept                   { minDmg_ = damage; }
            void maxDamage(MaxDamage damage) noexcept                   { maxDmg_ = damage; }
            void hitChance(HitChance chance) noexcept                   { hitChance_ = chance; }
            void critChance(CritChance chance) noexcept                 { critChance_ = chance; }
            void penetration(Penetration penet) noexcept                { penet_ = penet; }
            void attackRange(AttackRange range) noexcept                { range_ = range; }
            void attackNumber(AttackNumber number) noexcept             { nAttacks_ = number; }
            void actionPoints(ActionPoints ap) noexcept                 { ap_ = ap; }
            void actionPointsReload(ActionPointsReload ap) noexcept     { apReload_ = ap; }
            void level(Common::Level level) noexcept                    { weaponLvl_ = level; }
            void skillLevel(SkillLevel level) noexcept                  { skillLvl_ = level; }
            void ammoCapacity(AmmoCapacity capacity) noexcept           { ammoCap_ = capacity; }
            void ammoType(AmmoType type) noexcept                       { ammoTy_ = type; }
            void damageType(DamageType type) noexcept                   { dmgTy_ = type; }
            void weaponType(WeaponType type) noexcept                   { type_ = type; }

            Common::Name            name_;          // weapon name
            Common::Description     descrip_;       // description
            CritMultiplier          critMul_;       // crit damage multiplier
            Slot_WeaponModTypes     modTypes_;      // list of slot types
            Common::Price           price_;         // price
            WeaponModel             model_;         // weapon model
            MinDamage               minDmg_;        // min damage per hit
            MaxDamage               maxDmg_;        // max damage per hit
            HitChance               hitChance_;     // base hit chance
            CritChance              critChance_;    // crit chance
            Penetration             penet_;         // penetration
            AttackRange             range_;         // attack range
            AttackNumber            nAttacks_;      // number of attacks per turn
            ActionPoints            ap_;            // action points per attack
            ActionPointsReload      apReload_;      // action points per reload
            Common::Level           weaponLvl_;     // weapon level
            SkillLevel              skillLvl_;      // min level of skill
            AmmoCapacity            ammoCap_;       // ammo capacity
            AmmoType                ammoTy_;        // ammo type
            DamageType              dmgTy_;         // damage type
            WeaponType              type_;          // weapon type (kind)
        };

        ///------------------------------------------------------------------------------------------------
        
        class Weapon : public Item {
        public:
            using Model     = WeaponModel;
            using Type      = WeaponType;

        protected:
            explicit Weapon(WeaponModel model) noexcept;

        public:
            Weapon(const Weapon&) = delete;
            Weapon& operator=(const Weapon&) = delete;

            virtual ~Weapon() noexcept {}

            static std::unique_ptr<Item> create(WeaponModel model) {
                if (ref_.size() == 0) initialize();
                return std::unique_ptr<Item>(new Weapon(std::move(model)));
            }

            virtual void accept(ItemVisitor& visitor) noexcept override {
                visitor.visitWeapon(*this);
            }

            void apply() noexcept;

        private:
            void check() noexcept;

            static void initialize();

            static void initializeRefMin();

            static void add(WeaponReference common) {
                ref_[static_cast<std::underlying_type_t<WeaponModel>>(common.model_)] = std::move(common);
            }

        /// weapon parameters
        public:
            Common::Name name() const noexcept {
                return base_.name_;
            }

            Common::Description description() const noexcept {
                return base_.descrip_;
            }

            CritMultiplier critMultiplier() const noexcept {
                return critMul_;
            }

            void addCritMultiplier(CritMultiplier shift) noexcept {
                critMul_ += shift;
            }

            Common::Price price() const noexcept {
                return base_.price_;
            }

            WeaponModel model() const noexcept {
                return base_.model_;
            }

            MinDamage minDamage() const noexcept {
                return minDmg_;
            }

            void addMinDamage(MinDamage shift) noexcept {
                minDmg_ += shift;
            }

            MaxDamage maxDamage() const noexcept {
                return maxDmg_;
            }

            void addMaxDamage(MaxDamage shift) noexcept {
                maxDmg_ += shift;
            }

            HitChance hitChance() const noexcept {
                return hitChance_;
            }

            void addHitChance(HitChance shift) noexcept {
                hitChance_ += shift;
            }

            CritChance critChance() const noexcept {
                return critChance_;
            }

            void addCritChance(CritChance shift) noexcept {
                critChance_ += shift;
            }

            Penetration penetration() const noexcept {
                return penet_;
            }

            void addPenetration(Penetration shift) noexcept {
                penet_ += shift;
            }

            AttackRange attackRange() const noexcept {
                return range_;
            }

            void addAttackRange(AttackRange shift) noexcept {
                range_ += shift;
            }

            AttackNumber attackNumber() const noexcept {
                return nAttacks_;
            }

            void addAttackNumber(AttackNumber shift) noexcept {
                nAttacks_ += shift;
            }

            ActionPoints actionPoints() const noexcept {
                return ap_;
            }

            void addActionPoints(ActionPoints shift) noexcept {
                ap_ += shift;
            }

            ActionPointsReload actionPointsReload() const noexcept {
                return apReload_;
            }

            void addActionPointsReload(ActionPointsReload shift) noexcept {
                apReload_ += shift;
            }

            Common::Level level() const noexcept {
                return base_.weaponLvl_;
            }

            SkillLevel skillLevel() const noexcept {
                return base_.skillLvl_;
            }

            AmmoCapacity ammoCapacity() const noexcept {
                return ammoCap_;
            }

            void addAmmoCapacity(AmmoCapacity shift) noexcept {
                ammoCap_ += shift;
            }

            AmmoType ammoType() const noexcept {
                return ammoTy_;
            }

            void ammoType(AmmoType type) noexcept {
                ammoTy_ = type;
            }

            DamageType damageType() const noexcept {
                return dmgTy_;
            }

            void damageType(DamageType type) noexcept {
                dmgTy_ = type;
            }

            WeaponType type() const noexcept {
                return base_.type_;
            }

        /// mods
        public:
            unsigned int modSize() const noexcept;

            int modNumber(WeaponModType type) const noexcept {
                return mod_.slotNumber(type);
            }

            WeaponModType modType(unsigned int slotNumber) const noexcept {
                return mod_.type(slotNumber);
            }

            const std::unique_ptr<WeaponMod>& modGet(unsigned int slotNumber) const {
                return mod_[slotNumber];
            }

            //bool modSet(unique_ptr<Item>& source) noexcept;

            bool modSet(std::unique_ptr<Item>& source, unsigned int slotNumber) noexcept;

            bool modUnset(std::unique_ptr<Item>& receiver, unsigned int slotNumber) noexcept;

        private:
            const WeaponReference&      base_;          // reference, sample, template
            CritMultiplier              critMul_;       // crit damage multiplier
            MinDamage                   minDmg_;        // min damage per hit
            MaxDamage                   maxDmg_;        // max damage per hit
            HitChance                   hitChance_;     // base hit chance
            CritChance                  critChance_;    // crit chance
            Penetration                 penet_;         // penetration
            AttackRange                 range_;         // attack range
            AttackNumber                nAttacks_;      // number of attacks per turn
            ActionPoints                ap_;            // action points per attack
            ActionPointsReload          apReload_;      // action points per reload
            AmmoCapacity                ammoCap_;       // ammo capacity
            AmmoType                    ammoTy_;        // ammo type
            DamageType                  dmgTy_;         // damage type

            Common::Slot<WeaponMod, nWMSlots>   mod_;       // weapon mod slots

            static std::vector<WeaponReference> ref_;       // references
            static WeaponReference              refDef_;    // default reference
            static WeaponReference              refMin_;    // minimal valid stats
        };

    }
}

#endif // !WEAPON_HPP
