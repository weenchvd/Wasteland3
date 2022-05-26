
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"itemVisitorFullDescr.hpp"
#include"itemVisitorNameType.hpp"
#include"itemVisitorType.hpp"
#include"menuCommonText.hpp"
#include"menuItemCommon.hpp"
#include"menuItemText.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<assert.h>
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void printDamageEffect(
    ostream& os,
    const Indent indent,
    const object::DamageReference& reference,
    const bool isPositiveEffect)
{
    const auto sp  { ' ' };
    const auto p   { '%' };
    const auto& def{ object::Damage::damageReferenceContainer().damageReferenceDefault() };
    const auto& text{ object::Damage::damageText().common() };

    assert(def.isInitialized() == true);
    assert(reference.isInitialized() == true);
    if (isPositiveEffect == true) {
        if (reference.dmgRobots_ > def.dmgRobots_) {
            os << indent << text.damageVsRobots() << sp << reference.dmgRobots_ << p << endl;
        }
        if (reference.dmgVehicles_ > def.dmgVehicles_) {
            os << indent << text.damageVsVehicles() << sp << reference.dmgVehicles_ << p << endl;
        }
        if (reference.dmgHumans_ > def.dmgHumans_) {
            os << indent << text.damageVsHumans() << sp << reference.dmgHumans_ << p << endl;
        }
        if (reference.dmgAnimals_ > def.dmgAnimals_) {
            os << indent << text.damageVsAnimals() << sp << reference.dmgAnimals_ << p << endl;
        }
        if (reference.dmgMutants_ > def.dmgMutants_) {
            os << indent << text.damageVsMutants() << sp << reference.dmgMutants_ << p << endl;
        }
    }
    else {
        if (reference.dmgRobots_ < def.dmgRobots_) {
            os << indent << text.damageVsRobots() << sp << reference.dmgRobots_ << p << endl;
        }
        if (reference.dmgVehicles_ < def.dmgVehicles_) {
            os << indent << text.damageVsVehicles() << sp << reference.dmgVehicles_ << p << endl;
        }
        if (reference.dmgHumans_ < def.dmgHumans_) {
            os << indent << text.damageVsHumans() << sp << reference.dmgHumans_ << p << endl;
        }
        if (reference.dmgAnimals_ < def.dmgAnimals_) {
            os << indent << text.damageVsAnimals() << sp << reference.dmgAnimals_ << p << endl;
        }
        if (reference.dmgMutants_ < def.dmgMutants_) {
            os << indent << text.damageVsMutants() << sp << reference.dmgMutants_ << p << endl;
        }
    }
}

common::Text getDamageDescription(
    const Indent indent,
    const object::Damage::Type type)
{
    const auto& ref{ object::Damage::damageReferenceContainer().damageReference(type) };

    ostringstream oss;
    oss << showpos;
    printDamageEffect(oss, indent, ref, true);
    printDamageEffect(oss, indent, ref, false);
    return oss.str();
}

void printAttackDescription(
    ostream& os,
    const Indent indent,
    const object::Attack& attack,
    const bool printAttackType)
{
    const auto sp{ ' ' };
    const auto& text{ attack.attackText() };
    if (printAttackType && common::isValidEnum(attack.type())) {
        os << indent << text.common().attackType() << sp << text.type(attack.type()) << endl;
    }
    if (attack.rangeIsPresented()) {
        os << indent << text.common().attackRange() << sp;
        if (attack.range() != attack.pointBlank()) {
            os << attack.range();
        }
        else {
            os << text.common().pointBlank();
        }
        os << endl;
    }
    if (attack.rangeOfBouncesIsPresented()) {
        os << indent << text.common().rangeOfBounces() << sp
            << attack.rangeOfBounces() << endl;
    }
    if (attack.rangeOfConicalAreaIsPresented()) {
        os << indent << text.common().rangeOfConicalArea() << sp
            << attack.rangeOfConicalArea() << endl;
    }
    if (attack.radiusOfCircularAreaIsPresented()) {
        os << indent << text.common().radiusOfCircularArea() << sp
            << attack.radiusOfCircularArea() << endl;
    }
    if (attack.quantityOfBouncesIsPresented()) {
        os << indent << text.common().qtyOfBounces() << sp
            << attack.quantityOfBounces() << endl;
    }
    if (attack.angleOfConicalAreaIsPresented()) {
        os << indent << text.common().angleOfConicalArea() << sp
            << attack.angleOfConicalArea() << endl;
    }
}

void printFullDescription(
    istream& is,
    ostream& os,
    const object::InventoryIterator& iterItem,
    const Indent indent)
{
    assert(iterItem.isValid() == true);
    assert(iterItem.getConst()->get() != nullptr);
    printFullDescription(is, os, *iterItem.getConst()->get(), indent);
}

void printFullDescription(
    istream& is,
    ostream& os,
    const object::Item& item,
    const Indent indent)
{
    ItemVisitorFullDescription vis;
    item.accept(vis);
    auto text{ vis.getFullDescription() };
    for (int i = 0; i < text.size(); ++i) {
        os << indent;
        while (i < text.size() && text[i] != '\n') {
            os << text[i++];
        }
        os << endl;
    }
    if (text.size() > 0) {
        os << endl;
    }
}

bool removeItem(
    istream& is,
    ostream& os,
    object::Inventory& inventory,
    object::InventoryIterator& iterItem,
    const Indent indent)
{
    assert(iterItem.isValid() == true);
    const auto& text{ MenuItemText::common() };
    os << indent << text.questionDeleteItem() << endl;
    switch (getYesNo(is, os, indent)) {
    case YesNo::YES:
        inventory.extract(iterItem);
        return true;
    case YesNo::NO:
    case YesNo::CANCEL:
    default:
        return false;
    }
}

void showSlotsAndMods(
    istream& is,
    ostream& os,
    const object::InventoryIterator& iterItem,
    const Indent indent)
{
    assert(iterItem.isValid() == true);
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    os << ind0 << text.mods() << endl;

    int i{ itemCounter::countFrom };
    object::ItemVisitorType vis;
    (*iterItem.getConst())->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterItem.getConst()->get()) };
        for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
            if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                printNumBar(os, ind1, i++,
                    object::WeaponMod::weaponModText().type(weapon->slotMod().type(j))
                );
                os << ": ";
                if (weapon->slotMod()[j] != nullptr) {
                    os << weapon->slotMod()[j]->name();
                }
                os << endl;
            }
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
}

pair<int, bool> pickSlotNumber(
    istream& is,
    ostream& os,
    object::Squad& squad,
    const object::InventoryIterator& iterItem,
    const Indent indent)
{
    assert(iterItem.isValid() == true);
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuItemText::modify() };

    os << indent << text.enterSlotNumber() << endl;

    int i{ itemCounter::countFrom };
    object::ItemVisitorType vis;
    (*iterItem.getConst())->accept(vis);

    switch (vis.type()) {
    case object::Item::Type::WEAPON: {
        const auto* weapon{ static_cast<object::Weapon*>(iterItem.getConst()->get()) };
        auto pair{ getNumber(is, os) };
        if (pair.second == true) {
            for (int j = 0; j < weapon->slotMod().sizeRaw(); ++j) {
                if (weapon->slotMod().type(j) != object::WeaponMod::Type::INVALID) {
                    if (pair.first == i) {
                        return { j, true };
                    }
                    ++i;
                }
            }
            os << comT.errorSymbol() << comT.invalidNumber() << endl;
        }
        break;
    }
    case object::Item::Type::WEAPON_MOD:
    case object::Item::Type::AMMO:
    default:
        break;
    }
    return { numeric_limits<int>::min(), false };
}

void showModsWithTypes(
    istream& is,
    ostream& os,
    const object::Roster& roster,
    const common::Text& title,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };

    os << ind0 << title << endl;

    ItemVisitorNameType vis;
    int i{ itemCounter::countFrom };
    for (auto iter{ roster.newItems().beg_.getConst() };
        iter != roster.newItems().end_.getConst();
        ++iter)
    {
        (*iter)->accept(vis);
        printNumBar(os, ind1, i++, '*' + vis.getNameType()) << endl;
    }
    for (auto iter{ roster.oldItems().beg_.getConst() };
        iter != roster.oldItems().end_.getConst();
        ++iter)
    {
        (*iter)->accept(vis);
        printNumBar(os, ind1, i++, vis.getNameType()) << endl;
    }
}

} // namespace menu
} // namespace game
