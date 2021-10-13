
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECT_VISITOR_HPP
#define EFFECT_VISITOR_HPP

namespace Game
{
    namespace Object
    {
        /*class Weapon;
        class WeaponMod;
        class Armor;
        class ArmorMod;
        class Ammo;
        class Junk;

        class EffectVisitor {
        public:
            ItemVisitor(const ItemVisitor&) = delete;
            ItemVisitor& operator=(const ItemVisitor&) = delete;

            virtual ~ItemVisitor() noexcept {}

            virtual void visitWeapon(Weapon& weapon) = 0;
            virtual void visitWeaponMod(WeaponMod& weaponMod) = 0;
            virtual void visitArmor(Armor& armor) = 0;
            virtual void visitArmorMod(ArmorMod& armorMod) = 0;
            virtual void visitAmmo(Ammo& ammo) = 0;
            virtual void visitJunk(Junk& junk) = 0;

        protected:
            ItemVisitor() noexcept {}
        };

        class TypeItemVisitor : public ItemVisitor {
        public:
            TypeItemVisitor() noexcept {}

            virtual ~TypeItemVisitor() noexcept {}

            virtual void visitWeapon(Weapon& weapon) noexcept override {
                reset(); isWeapon_ = true;
            }

            virtual void visitWeaponMod(WeaponMod& weaponMod) noexcept override {
                reset(); isWeaponMod_ = true;
            }

            virtual void visitArmor(Armor& armor) noexcept override {
                reset(); isArmor_ = true;
            }

            virtual void visitArmorMod(ArmorMod& armorMod) noexcept override {
                reset(); isArmorMod_ = true;
            }

            virtual void visitAmmo(Ammo& ammo) noexcept override {
                reset(); isAmmo_ = true;
            }

            virtual void visitJunk(Junk& junk) noexcept override {
                reset(); isJunk_ = true;
            }

            bool isWeapon()     const noexcept { return isWeapon_; }
            bool isWeaponMod()  const noexcept { return isWeaponMod_; }
            bool isArmor()      const noexcept { return isArmor_; }
            bool isArmorMod()   const noexcept { return isArmorMod_; }
            bool isAmmo()       const noexcept { return isAmmo_; }
            bool isJunk()       const noexcept { return isJunk_; }

        private:
            void reset() noexcept {
                isWeapon_       = false;
                isWeaponMod_    = false;
                isArmor_        = false;
                isArmorMod_     = false;
                isAmmo_         = false;
                isJunk_         = false;
            }

        private:
            bool isWeapon_      { false };
            bool isWeaponMod_   { false };
            bool isArmor_       { false };
            bool isArmorMod_    { false };
            bool isAmmo_        { false };
            bool isJunk_        { false };
        };*/

    }
}

#endif // !EFFECT_VISITOR_HPP
