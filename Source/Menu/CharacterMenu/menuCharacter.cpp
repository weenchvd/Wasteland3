
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttribute.hpp"
#include"menuCommonText.hpp"
#include"menuCharacter.hpp"
#include"menuCharacterText.hpp"
#include"menuSkill.hpp"
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void menuCharacter(istream& is, ostream& os, object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuCharacterText::main() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << sign::space
            << sign::lp << character.name() << sign::rp << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_STATS, text.showStats()) << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_GEAR, text.showGear()) << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_ATTRIBUTES, text.showAttributes()) << endl;
        printNumBar(os, ind1, actionCharacter::MENU_ATTRIBUTE, text.enterAttrMenu()) << endl;
        printNumBar(os, ind1, actionCharacter::SHOW_SKILLS, text.showSkills()) << endl;
        printNumBar(os, ind1, actionCharacter::MENU_SKILL, text.enterSkillMenu()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionCharacter::SHOW_STATS:
            showStats(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_GEAR:
            showGear(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_ATTRIBUTES:
            showAllAttributes(is, os, character, ind1);
            break;
        case actionCharacter::MENU_ATTRIBUTE:
            menuAttribute(is, os, character, ind1);
            break;
        case actionCharacter::SHOW_SKILLS:
            showAllSkills(is, os, character, ind1);
            break;
        case actionCharacter::MENU_SKILL:
            menuSkill(is, os, character, ind1);
            break;
        case actionCommon::EXIT:
            return;
        case actionCommon::INVALID:
            break;
        default:
            os << comT.errorSymbol() << comT.unknownAction() << endl;
            break;
        }
    }
}

///************************************************************************************************

void showStats(istream& is, ostream& os, const object::Character& character, const Indent indent)
{
    constexpr unsigned char statWidth{ 40 };
    constexpr auto sp{ sign::space };
    constexpr auto ph{ sign::dot };
    constexpr auto pc{ sign::percent };
    constexpr auto x { sign::x };
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& tCom{ character.characterText().common() };
    const auto& tSta{ character.characterText().stats() };
    ostringstream oss;

    os << ind0 << character.name() << endl;
    os << ind0 << tCom.level() << sp << character.level() << sp
        << character.characterText().type(character.type()) << endl;
    os << ind0 << tCom.stats() << endl;
    clearStream(oss) << character.constitutionCurrent() << sign::slash
        << character.constitutionMaximum();
    os << ind1 << fitInWidth(tSta.con(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.experience();
    os << ind1 << fitInWidth(tCom.xp(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.constitutionPerLevel();
    os << ind1 << fitInWidth(tSta.conPerLevel(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusHealing() << pc;
    os << ind1 << fitInWidth(tSta.healingBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.actionPointMaximum();
    os << ind1 << fitInWidth(tSta.actionPoints(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.chanceHit() << pc;
    os << ind1 << fitInWidth(tSta.hitChance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.chanceCritDamage() << pc;
    os << ind1 << fitInWidth(tSta.critChance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierCritDamage() << x;
    os << ind1 << fitInWidth(tSta.critDmg(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.armorPenetration();
    os << ind1 << fitInWidth(tSta.penetration(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusSneakAttackDamage() << pc;
    os << ind1 << fitInWidth(tSta.sneakAttackDmg(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.strikeRate() << pc;
    os << ind1 << fitInWidth(tSta.strikeRate(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.armor();
    os << ind1 << fitInWidth(tSta.armor(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.evasion() << pc;
    os << ind1 << fitInWidth(tSta.evasion(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceCritDamage() << pc;
    os << ind1 << fitInWidth(tSta.critResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceFireDamage() << pc;
    os << ind1 << fitInWidth(tSta.fireResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceColdDamage() << pc;
    os << ind1 << fitInWidth(tSta.coldResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceEnergyDamage() << pc;
    os << ind1 << fitInWidth(tSta.energyResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceExplosiveDamage() << pc;
    os << ind1 << fitInWidth(tSta.explosiveResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.resistanceStatusEffect() << pc;
    os << ind1 << fitInWidth(tSta.statusEffectResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << tCom.level() << sp << character.radiationResistance();
    os << ind1 << fitInWidth(tSta.radiationResistance(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.downedTime();
    os << ind1 << fitInWidth(tSta.downedTime(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusMeleeDamage() << pc;
    os << ind1 << fitInWidth(tSta.meleeDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusRangedDamage() << pc;
    os << ind1 << fitInWidth(tSta.rangedDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusNormalDamage() << pc;
    os << ind1 << fitInWidth(tSta.normalDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusFireDamage() << pc;
    os << ind1 << fitInWidth(tSta.fireDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusColdDamage() << pc;
    os << ind1 << fitInWidth(tSta.coldDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusEnergyDamage() << pc;
    os << ind1 << fitInWidth(tSta.energyDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.bonusExplosiveDamage() << pc;
    os << ind1 << fitInWidth(tSta.explosiveDmgBonus(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.perception();
    os << ind1 << fitInWidth(tSta.perception(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierThrowingRange() << x;
    os << ind1 << fitInWidth(tSta.throwingRange(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.initiative() << pc;
    os << ind1 << fitInWidth(tSta.initiative(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.timeDetection() << sp << tCom.sec();
    os << ind1 << fitInWidth(tSta.detectionTime(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.multiplierCombatSpeed() << x;
    os << ind1 << fitInWidth(tSta.combatSpeed(), oss.str(), statWidth, ph) << endl;
    //clearStream(oss) << character.();
    //os << ind1 << fitInWidth(tSta.quickSlots(), oss.str(), statWidth, ph) << endl;
    clearStream(oss) << character.rangeLeadership() << sp << tCom.m_meter();
    os << ind1 << fitInWidth(tSta.leadershipRange(), oss.str(), statWidth, ph) << endl;
}

void showGear(istream& is, ostream& os, const object::Character& character, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& text{ MenuCharacterText::common() };

    os << ind0 << text.gear() << endl;
    const auto& weapons{ character.slotWeapon() };
    for (int i = 0; i < weapons.size(); ++i) {
        os << ind1 << text.weapon() << sign::space << sign::sharp << i + 1
            << sign::colon << sign::space;
        if (weapons[i] != nullptr) {
            os << weapons[i]->name();
        }
        else {
            os << sign::lp << text.emptySlot() << sign::rp;
        }
        os << endl;
    }
    // TODO armor
    // TODO quick slots
}

} // namespace menu
} // namespace game
