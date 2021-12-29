
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"initialization.hpp"
#include"menuMain.hpp"
#include"squad.hpp"
#include"inventory.hpp"
#include<iostream>

#include<cstdio>
#include<string>
#include<Windows.h>


#define SHOW 0

#if SHOW
#include"unit.hpp"
#include"character.hpp"
#include"inventory.hpp"
#include"item.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include"initialization.hpp"
#include<array>
#include<iostream>
#include<memory>
#include<string>
#endif


int main()
{
    using namespace std;

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    cout << "\tmain.exe Start!" << endl;
    cout << "----Welcome to Wasteland 3!----" << endl;

    Game::Object::Squad squad;
    Init::initializeSquad(squad);

    Game::Object::Inventory shop;
    Init::initializeShop(shop);

    Game::Menu::menuMain(squad, shop);

    //sizeof(Game::Object::Character);
    //sizeof(Game::Common::Text);
    //sizeof(Game::Common::Slot<Game::Object::Weapon, Game::Object::nWSlots>);
    //sizeof(std::unique_ptr<Game::Object::Attribute>);

#if SHOW
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
    auto weapons = inv.roster(ItemType::WEAPON);
    auto weaponMods = inv.roster(ItemType::WEAPONMOD);
    auto armors = inv.roster(ItemType::ARMOR);

    unique_ptr<Unit> unit1 = Character::create(Character::Model::RANGER_COMMON);
    auto weapon = inv.extract(weapons.oldItems.beg);
    unique_ptr<Character> char1{ static_cast<Character*>(unit1.release()) };
    static_cast<Weapon*>(weapon.get())->slotMod().set(0, inv.extract(weaponMods.oldItems.beg));
    char1->slotWeapon().set(0, weapon);
    char1->slotWeapon().get(0)->slotMod().set(0, inv.extract(inv.roster(ItemType::WEAPONMOD).oldItems.beg));
    char1->slotWeapon().get(0)->slotMod().set(3, inv.extract(----inv.roster(ItemType::WEAPONMOD).oldItems.end));

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
#endif

    cout << "\tmain.exe Done!" << endl;
    return 0;
}
