
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammo.hpp"
#include"attribute.hpp"
#include"damage.hpp"
#include"itemVisitorFullDescr.hpp"
#include"menuItemCommon.hpp"
#include"plainText.hpp"
#include"skill.hpp"
#include"weapon.hpp"
#include"weaponMod.hpp"
#include<array>
#include<assert.h>
#include<sstream>

namespace game {
namespace menu {

using namespace std;

vector<WeaponList::list_t>          WeaponList::list_;
bool                                WeaponList::initialized_{ false };

///************************************************************************************************

void ItemVisitorWeaponCharacteristics::visitWeapon(const object::Weapon& weapon)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& x   { signX_ };
    const auto& p   { signPercent_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const object::Weapon& def{ object::Weapon::weaponDefault() };
    const auto& text{ weapon.weaponText() };
    ostringstream oss;
    bool firstLine{ true };
    name_ = weapon.name();

    oss.str("");
    oss << text.common().level() << sp << weapon.level() << sp
        << text.type(weapon.type());
    levelAndType_ = oss.str();

    oss.str("");
    oss << weapon.description();
    descr_ = oss.str();

    oss.str("");
    bool modsInstalled{ false };
    for (int i = 0; modsInstalled == false && i < weapon.slotMod().size(); ++i) {
        if (weapon.slotMod()[i] != nullptr) {
            modsInstalled = true;
        }
    }
    if (modsInstalled == true) {
        firstLine = true;
        oss << text.common().installedMods() << endl;
        for (int i = 0; i < weapon.slotMod().size(); ++i) {
            const auto& weaponMod{ weapon.slotMod()[i] };
            if (weaponMod != nullptr) {
                if (!firstLine) {
                    oss << endl;
                }
                oss << weaponMod->name();
                firstLine = false;
            }
        }
    }
    installedMods_ = oss.str();

    oss.str("");
    object::WeaponRequirements wReqDef;
    const auto skillReqDefaultType{ wReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weapon.requirements().skillRequirements() };
    firstLine = true;
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            if (!firstLine) {
                oss << endl;
            }
            oss << text.common().require() << sp << skillReq[i].second << sp
                << object::SkillText::name(skillReq[i].first);
            firstLine = false;
        }
    }
    const auto attrReqDefaultType{ wReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weapon.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            if (!firstLine) {
                oss << endl;
            }
            oss << text.common().require() << sp << attrReq[i].second << sp
                << object::AttributeText::name(attrReq[i].first);
            firstLine = false;
        }
    }
    weaponReq_ = oss.str();

    oss.str("");
    if (weapon.penalties().isPresented()) {
        oss << text.common().penalty();
        const object::WeaponPenalties& pen{ def.penalties() };
        if (weapon.penalties().mulCritDmg_ != pen.mulCritDmg_) {
            oss << endl << text.penalties().critDamage() << sp
                << weapon.penalties().mulCritDmg_ << p;
        }
        if (weapon.penalties().chaHit_ != pen.chaHit_) {
            oss << endl << text.penalties().hitChance() << sp
                << weapon.penalties().chaHit_ << p;
        }
        if (weapon.penalties().chaCritDmg_ != pen.chaCritDmg_) {
            oss << endl << text.penalties().critChance() << sp
                << weapon.penalties().chaCritDmg_ << p;
        }
        if (weapon.penalties().strike_ != pen.strike_) {
            oss << endl << text.penalties().strikeRate() << sp
                << weapon.penalties().strike_ << p;
        }
    }
    penalties_ = oss.str();

    oss.str("");
    oss << text.common().damage() << sp << weapon.damageMinimum() << '-'
        << weapon.damageMaximum() << sp << x
        << weapon.shotsPerAttack() << sp
        << object::Damage::damageReferenceContainer().damageReference(weapon.damageType()).name();
    dmgAndDmgType_ = oss.str();

    dmgDescr_ = getDamageDescription(Indent{}, weapon.damageType());

    oss.str("");
    printAttackDescription(oss, Indent{ 0 }, weapon.attack());
    attackDescr_ = oss.str();

    oss.str("");
    oss << text.common().ap() << sp << weapon.actionPointPerAttack();
    ap_ = oss.str();

    oss.str("");
    oss << text.common().apReload() << sp << weapon.actionPointPerReload();
    apReload_ = oss.str();

    if (weapon.capacityAmmo() != def.capacityAmmo()) {
        oss.str("");
        oss << text.common().ammoCapacity() << sp << weapon.capacityAmmo();
        ammoCapacity_ = oss.str();
    }
    if (weapon.ammoType() != def.ammoType()) {
        oss.str("");
        oss << text.common().ammoType() << sp
            << object::Ammo::ammoReferenceContainer().ammoReference(weapon.ammoType()).name();
        ammoType_ = oss.str();
    }
    if (weapon.bonusSneakAttackDamage() != def.bonusSneakAttackDamage()) {
        oss.str("");
        oss << text.common().bonSneakDamage() << sp << weapon.bonusSneakAttackDamage() << p;
        bonSneakAttackDmg_ = oss.str();
    }
    if (weapon.bonusNormalDamage() != def.bonusNormalDamage()) {
        oss.str("");
        oss << text.common().bonNormDamage() << sp << weapon.bonusNormalDamage() << p;
        bonNormalDmg_ = oss.str();
    }
    if (weapon.bonusMeleeDamage() != def.bonusMeleeDamage()) {
        oss.str("");
        oss << text.common().bonMeleeDamage() << sp << weapon.bonusMeleeDamage() << p;
        bonMeleeDmg_ = oss.str();
    }
    if (weapon.bonusRangedDamage() != def.bonusRangedDamage()) {
        oss.str("");
        oss << text.common().bonRangeDamage() << sp << weapon.bonusRangedDamage() << p;
        bonRangedDmg_ = oss.str();
    }
    oss.str("");
    oss << text.common().hitChance() << sp << weapon.chanceHit() << p;
    hitChance_ = oss.str();

    oss.str("");
    oss << text.common().critDamage() << sp << weapon.multiplierCritDamage() << x;
    critDamage_ = oss.str();

    oss.str("");
    oss << text.common().critChance() << sp << weapon.chanceCritDamage() << p;
    critChance_ = oss.str();

    oss.str("");
    oss << text.common().penetration() << sp << weapon.armorPenetration();
    penetration_ = oss.str();

    oss.str("");
    oss << global::PlainText::plainTextText().common().price() << sp << d << weapon.price();
    price_ = oss.str();
}

///************************************************************************************************

void ItemVisitorFullDescription::visitWeapon(const object::Weapon& weapon)
{
    reset();

    const auto& sep { separator_ };
    ItemVisitorWeaponCharacteristics vis;
    weapon.accept(vis);

    text_ =
        vis.name() + '\n' +
        vis.levelAndType() + '\n' +
        sep + '\n' +
        vis.description() + '\n';

    const auto& weaponReq{ vis.weaponRequirements() };
    if (weaponReq.size() > 0) {
        text_ += weaponReq + '\n';
    }

    const auto& penalties{ vis.penalties() };
    if (penalties.size() > 0) {
        text_ += penalties + '\n';
    }

    const auto& installedMods{ vis.installedMods() };
    if (installedMods.size() > 0) {
        text_ +=
            text_t{ sep } + '\n' +
            installedMods + '\n';
    }

    text_ +=
        text_t{ sep } + '\n' +
        vis.damageAndDamageType() + '\n';

    const auto& damageDescr{ vis.damageDescription() };
    if (damageDescr.size() > 0) {
        text_ += damageDescr;
    }

    text_ +=
        vis.attackDescription() +
        vis.actionPoints() + '\n' +
        vis.actionPointsReload() + '\n';

    const auto& ammoCapacity{ vis.ammoCapacity() };
    if (ammoCapacity.size() > 0) {
        text_ += ammoCapacity + '\n';
    }

    const auto& ammoType{ vis.ammoType() };
    if (ammoType.size() > 0) {
        text_ += ammoType + '\n';
    }

    const auto& bonusSneakAtt{ vis.bonusSneakAttackDamage() };
    if (bonusSneakAtt.size() > 0) {
        text_ += bonusSneakAtt + '\n';
    }

    const auto& bonusNormalDamage{ vis.bonusNormalDamage() };
    if (bonusNormalDamage.size() > 0) {
        text_ += bonusNormalDamage + '\n';
    }

    const auto& bonusMeleeDamage{ vis.bonusMeleeDamage() };
    if (bonusMeleeDamage.size() > 0) {
        text_ += bonusMeleeDamage + '\n';
    }

    const auto& bonusRangedDamage{ vis.bonusRangedDamage() };
    if (bonusRangedDamage.size() > 0) {
        text_ += bonusRangedDamage + '\n';
    }

    text_ +=
        vis.hitChance() + '\n' +
        vis.critDamage() + '\n' +
        vis.critChance() + '\n' +
        vis.penetration() + '\n' +
        vis.price();
}

void ItemVisitorFullDescription::visitWeaponMod(const object::WeaponMod& weaponMod)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& x   { signX_ };
    const auto& p   { signPercent_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const auto& text{ weaponMod.weaponModText() };
    ostringstream oss;
    oss << weaponMod.name() << endl;
    oss << text.common().itemType() << " (" << text.type(weaponMod.type()) << ')' << endl;
    oss << sep << endl;

    oss << weaponMod.description() << endl;

    object::WeaponModRequirements wmReqDef;
    const auto skillReqDefaultType{ wmReqDef.skillRequirements()[0].first };
    const auto& skillReq{ weaponMod.requirements().skillRequirements() };
    for (int i = 0; i < skillReq.size(); ++i) {
        if (skillReq[i].first != skillReqDefaultType) {
            oss << text.common().require() << sp << skillReq[i].second << sp
                << object::SkillText::name(skillReq[i].first) << endl;
        }
    }
    const auto attrReqDefaultType{ wmReqDef.attributeRequirements()[0].first };
    const auto& attrReq{ weaponMod.requirements().attributeRequirements() };
    for (int i = 0; i < attrReq.size(); ++i) {
        if (attrReq[i].first != attrReqDefaultType) {
            oss << text.common().require() << sp << attrReq[i].second << sp
                << object::AttributeText::name(attrReq[i].first) << endl;
        }
    }

    oss << text.common().require() << sp;
    const auto& list{ WeaponList::getList(weaponMod.type()) };
    for (int i = 0; i < list.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << object::WeaponText::type(list[i]);
    }
    oss << endl;
    oss << sep << endl;

    oss << std::showpos;
    const object::WeaponMod& def{ object::WeaponMod::weaponModDefault() };
    if (weaponMod.damageMinimum() != def.damageMinimum()) {
        oss << text.common().minDamage() << sp << weaponMod.damageMinimum() << endl;
    }
    if (weaponMod.damageMaximum() != def.damageMaximum()) {
        oss << text.common().maxDamage() << sp << weaponMod.damageMaximum() << endl;
    }
    if (weaponMod.shotsPerAttack() != def.shotsPerAttack()) {
        oss << text.common().shots() << sp << weaponMod.shotsPerAttack() << p << endl;
    }
    if (weaponMod.damageType() != def.damageType()) {
        oss << text.common().damageType() << sp
            << object::Damage::damageReferenceContainer().damageReference(
                weaponMod.damageType()).name() << endl;
        oss << getDamageDescription(Indent{}, weaponMod.damageType());
    }

    printAttackDescription(oss, Indent{ 0 }, weaponMod.attack(), false);

    if (weaponMod.actionPointPerAttack() != def.actionPointPerAttack()) {
        oss << text.common().ap() << sp << weaponMod.actionPointPerAttack() << endl;
    }
    if (weaponMod.actionPointPerReload() != def.actionPointPerReload()) {
        oss << text.common().apReload() << sp << weaponMod.actionPointPerReload() << endl;
    }
    if (weaponMod.capacityAmmo() != def.capacityAmmo()) {
        oss << text.common().ammoCapacity() << sp << weaponMod.capacityAmmo() << endl;
    }
    if (weaponMod.ammoType() != def.ammoType()) {
        oss << text.common().ammoType() << sp
            << object::Ammo::ammoReferenceContainer().ammoReference(weaponMod.ammoType()).name() << endl;
    }
    if (weaponMod.bonusSneakAttackDamage() != def.bonusSneakAttackDamage()) {
        oss << text.common().bonSneakDamage() << sp
            << weaponMod.bonusSneakAttackDamage() << p << endl;
    }
    if (weaponMod.bonusNormalDamage() != def.bonusNormalDamage()) {
        oss << text.common().bonNormDamage() << sp
            << weaponMod.bonusNormalDamage() << p << endl;
    }
    if (weaponMod.bonusMeleeDamage() != def.bonusMeleeDamage()) {
        oss << text.common().bonMeleeDamage() << sp
            << weaponMod.bonusMeleeDamage() << p << endl;
    }
    if (weaponMod.bonusRangedDamage() != def.bonusRangedDamage()) {
        oss << text.common().bonRangeDamage() << sp
            << weaponMod.bonusRangedDamage() << p << endl;
    }
    if (weaponMod.chanceHit() != def.chanceHit()) {
        oss << text.common().hitChance() << sp << weaponMod.chanceHit() << p << endl;
    }
    if (weaponMod.multiplierCritDamage() != def.multiplierCritDamage()) {
        oss << text.common().critDamage() << sp << weaponMod.multiplierCritDamage() << x << endl;
    }
    if (weaponMod.chanceCritDamage() != def.chanceCritDamage()) {
        oss << text.common().critChance() << sp << weaponMod.chanceCritDamage() << p << endl;
    }
    if (weaponMod.armorPenetration() != def.armorPenetration()) {
        oss << text.common().penetration() << sp
            << weaponMod.armorPenetration() << endl;
    }
    oss << std::noshowpos;

    oss << global::PlainText::plainTextText().common().price() << sp
        << d << weaponMod.price() << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitArmor(const object::Armor& armor)
{
    reset();
}

void ItemVisitorFullDescription::visitArmorMod(const object::ArmorMod& armorMod)
{
    reset();
}

void ItemVisitorFullDescription::visitAmmo(const object::Ammo& ammo)
{
    reset();

    const auto& sp  { signSpace_ };
    const auto& d   { signDollar_ };
    const auto& sep { separator_ };
    const auto& text{ ammo.ammoText() };
    ostringstream oss;
    oss << ammo.name() << endl;
    oss << text.common().itemType() << endl;
    oss << sep << endl;
    oss << ammo.description() << endl;
    oss << sep << endl;
    oss << text.common().quantity() << sp << ammo.quantity() << endl;

    oss << global::PlainText::plainTextText().common().price() << sp
        << d << ammo.price() << endl;

    text_ = oss.str();
}

void ItemVisitorFullDescription::visitJunk(const object::Junk& junk)
{
    reset();
}

///************************************************************************************************

void WeaponList::initialize()
{
    if (isInitialized()) return;

    assert(object::WeaponReferenceContainer::isInitialized());
    object::Weapon__Type last{ object::Weapon__Type::__INVALID };
    list_.resize(sizeWeaponModType_);

    for (size_t k = { common::toUnderlying(common::firstEnum<object::WeaponMod__Type>()) };
        k < list_.size(); ++k)
    {
        array<bool, sizeWeaponType_> a;
        a.fill(false);
        for (size_t i = { common::toUnderlying(common::firstEnum<object::Weapon__Model>()) };
            i <= common::toUnderlying(common::lastEnum<object::Weapon__Model>()); ++i)
        {
            const auto& ref{
                object::WeaponReferenceContainer::weaponReference(static_cast<object::Weapon__Model>(i))
            };
            if (last == ref.type_) continue;
            last = ref.type_;
            for (size_t j = 0; j < ref.weaponModTypes_.size(); ++j) {
                if (ref.weaponModTypes_[j] == static_cast<object::WeaponMod__Type>(k)) {
                    a[common::toUnderlying(ref.type_)] = true;
                    break;
                }
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] == true) {
                list_[k].emplace_back(static_cast<object::Weapon__Type>(i));
            }
        }
    }

    initialized_ = true;
}

} // namespace menu
} // namespace game
