
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"unit.hpp"
#include"character.hpp"
#include"inventory.hpp"
#include"item.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
//#include"armor.hpp"
//#include"destroyable.hpp"
#include<array>
#include<iostream>
#include<memory>
#include<string>


int main()
{
    using namespace std;
    using namespace Game;
    using namespace Game::Object;

    sizeof(ItemType);
    sizeof(ItemModel);
    sizeof(Item);
    sizeof(WeaponReference);
    sizeof(Common::Text);
    sizeof(WeaponModType);
    sizeof(array<WeaponModType, 4>);
    sizeof(array<unique_ptr<WeaponMod>, 4>);
    sizeof(Common::Slot<WeaponMod, 4>);
    sizeof(Weapon);

    unique_ptr<Item> socom1 = Weapon::create(WeaponModel::AR_SOCOM);
    TypeItemVisitor typeIV1;
    socom1->accept(typeIV1);
    cout << "socom1->accept(typeIV1)" << endl;
    cout << "  isWeapon:    " << boolalpha << typeIV1.isWeapon() << endl;
    cout << "  isWeaponMod: " << boolalpha << typeIV1.isWeaponMod() << endl;
    cout << "  isArmor:     " << boolalpha << typeIV1.isArmor() << endl;
    cout << "  isArmorMod:  " << boolalpha << typeIV1.isArmorMod() << endl;
    cout << "  isAmmo:      " << boolalpha << typeIV1.isAmmo() << endl;
    cout << "  isJunk:      " << boolalpha << typeIV1.isJunk() << endl << endl;

    unique_ptr<Item> quickMag1 = WeaponMod::create(WeaponModModel::MAG_QUICKFIRE);
    quickMag1->accept(typeIV1);
    cout << "quickMag1->accept(typeIV1)" << endl;
    cout << "  isWeapon:    " << boolalpha << typeIV1.isWeapon() << endl;
    cout << "  isWeaponMod: " << boolalpha << typeIV1.isWeaponMod() << endl;
    cout << "  isArmor:     " << boolalpha << typeIV1.isArmor() << endl;
    cout << "  isArmorMod:  " << boolalpha << typeIV1.isArmorMod() << endl;
    cout << "  isAmmo:      " << boolalpha << typeIV1.isAmmo() << endl;
    cout << "  isJunk:      " << boolalpha << typeIV1.isJunk() << endl << endl;

    
    unique_ptr<Item> arSocom1       = Weapon::create(WeaponModel::AR_SOCOM);
    unique_ptr<Item> arSocom2       = Weapon::create(WeaponModel::AR_SOCOM);
    unique_ptr<Item> arKalash97_1   = Weapon::create(WeaponModel::AR_KALASH97);
    unique_ptr<Item> smgRipper1     = Weapon::create(WeaponModel::SMG_RIPPER);

    
    unique_ptr<Item> barrelLight1   = WeaponMod::create(WeaponModModel::BARREL_LIGHTWEIGHT);
    unique_ptr<Item> barrelShort1   = WeaponMod::create(WeaponModModel::BARREL_SHORTENED);
    unique_ptr<Item> magAdvMat1     = WeaponMod::create(WeaponModModel::MAG_ADVANCED_MATERIALS);
    unique_ptr<Item> magOversized1  = WeaponMod::create(WeaponModModel::MAG_OVERSIZED);
    unique_ptr<Item> magQuickfire1  = WeaponMod::create(WeaponModModel::MAG_QUICKFIRE);

    Inventory inv;
    inv.insert(arSocom1, true);
    inv.insert(arKalash97_1, true);
    inv.insert(barrelLight1, true);
    inv.insert(barrelShort1, true);
    inv.insert(arSocom2);
    inv.insert(magAdvMat1);
    inv.insert(magOversized1);
    inv.insert(smgRipper1);
    inv.insert(magQuickfire1);
    //inv.sort();

    auto all = inv.roster();
    auto all2 = inv.roster();
    auto weapons = inv.roster(ItemType::Weapon);
    auto weaponMods = inv.roster(ItemType::WeaponMod);
    auto armors = inv.roster(ItemType::Armor);
    /*auto iter = inv.roster().oldItems.second;
    --iter;
    
    auto weapon1Iter = weapons.oldItems.first;
    auto& weapon1UP = *weapon1Iter;
    weapon1UP->accept(typeIV1);
    if (typeIV1.isWeapon()) {
        Weapon* weapon1 = static_cast<Weapon*>(weapon1UP.get());
        list<unique_ptr<Item>>::iterator weaponMod1Iter = weaponMods.oldItems.first;
        int slotNumber = weapon1->weaponModNumber((static_cast<WeaponMod*>(weaponMod1Iter->get()))->type());
        bool b1 = weapon1->weaponModSet(*weaponMod1Iter);
        list<unique_ptr<Item>>::iterator weaponMod2Iter = weaponMod1Iter;
        weaponMod2Iter++;
        if (!*weaponMod1Iter) {
            inv.erase(weaponMod1Iter);
        }
        if ((static_cast<WeaponMod*>(weaponMod2Iter->get()))->type() == weapon1->weaponModType(slotNumber)) {
            bool b2 = weapon1->weaponModSet(*weaponMod2Iter, slotNumber);
        }
        if (!*weaponMod2Iter) {
            inv.erase(weaponMod2Iter);
        }
        list<unique_ptr<Item>>::iterator weaponMod3Iter = weaponMod2Iter;
        weaponMod3Iter++;
        bool b3 = weapon1->weaponModSet(*weaponMod3Iter);
        if (!*weaponMod3Iter) {
            inv.erase(weaponMod3Iter);
        }

    }*/

    unique_ptr<Unit> unit1 = Character::create(Character::Model::RANGER_COMMON);
    auto weapon = inv.extract(weapons.oldItems.beg);
    unique_ptr<Character> char1{ static_cast<Character*>(unit1.release()) };
    static_cast<Weapon*>(weapon.get())->slotMod().set(0, inv.extract(weaponMods.oldItems.beg));
    char1->slotWeapon().set(0, weapon);
    char1->slotWeapon().get(0)->slotMod().set(0, inv.extract(inv.roster(ItemType::WeaponMod).oldItems.beg));
    char1->slotWeapon().get(0)->slotMod().set(3, inv.extract(----inv.roster(ItemType::WeaponMod).oldItems.end));

    const WeaponMod::Type ty1 = char1->slotWeapon().get(0)->slotMod().get(0)->type();
    const auto size1 = char1->slotWeapon().get(0)->slotMod().size();
    const auto sizeRaw1 = char1->slotWeapon().get(0)->slotMod().sizeRaw();
    const auto arSlotNum1 = char1->slotWeapon().slotNumber(Weapon::Type::AR);
    const auto magSlotNum1 = char1->slotWeapon().get(0)->slotMod().slotNumber(WeaponMod::Type::MAGAZINE);
    char1->slotWeapon().get(0)->slotMod().type(2) = WeaponMod::Type::WEIGHT;

    char1->slotWeapon().get(0)->apply();
    char1->slotWeapon().unset(0, weapon);
    unique_ptr<Item> mod;
    static_cast<Weapon*>(weapon.get())->slotMod().unset(0, mod);
    inv.insert(weapon);
    inv.insert(mod);

    cout << "\tmain.exe Done!" << endl;
    return 0;
}
