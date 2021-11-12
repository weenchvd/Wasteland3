
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include"character.hpp"
#include"common.hpp"
#include"inventory.hpp"
#include"squad.hpp"
#include<iostream>

namespace Game
{
    namespace Menu
    {
        class Indent {
        public:
            Indent()
                : indent_{ 2 } {}

            Indent(unsigned int indent)
                : indent_{ indent } {}

            unsigned int get() const {
                return indent_;
            }

        private:
            unsigned int indent_;
        };

        Indent operator+(const Indent& left, const Indent& right);

        std::ostream& operator<<(std::ostream& os, const Indent& indent);

        double secondTime(Common::Time time);

        double multiplier(Common::Multiplier mult);

        double percentChance(Common::Chance chance);

        double percentBonus(Common::Bonus bonus);

        double percentEvasion(Common::Evasion evasion);

        double percentResistance(Common::Resistance res);

        double percentInitiative(Common::Initiative init);

        double percentStrike(Common::Strike strike);

        int integer(char ch);

        int getAction();

        int getPosNumber();

        enum class YesNo {
            INVALID = -1,
            NO,
            YES
        };

        YesNo getYesNo();

        enum ActionCommon {
            INVALID = -1,
            EXIT,
            NEXT
        };

        enum ActionMain {
            MENUSQUAD = ActionCommon::NEXT,
            MENUINVENTORY
        };

        void menuMain(Object::Squad& squad, Object::Inventory& shop);

        enum ActionInventory {
            MONEY = ActionCommon::NEXT,
            ALLITEMS
        };

        void menuInventory(Object::Squad& squad, const Indent indent);

        enum ActionSquad {
            SHOWSQUAD = ActionCommon::NEXT,
            MENUCHARACTER
        };

        void menuSquad(Object::Squad& squad, const Indent indent);

        enum ActionCharacter {
            SHOWSTATS = ActionCommon::NEXT,
            SHOWGEAR,
            SHOWATTRIBUTES,
            MENUATTRIBUTE
        };

        void menuCharacter(Object::Character& character, const Indent indent);

        enum ActionAttribute {
            SHOWALL = ActionCommon::NEXT,
            SHOWALLACC,
            MODIFY
        };

        void menuAttribute(Object::Character& character, const Indent indent);

        enum ActionModifyAttribute {
            SHOWACC = ActionCommon::NEXT,
            INCREASELEVEL,
            DECREASELEVEL
        };

        void menuModifyAttribute(Object::Character& character, Object::Attribute::Type type, const Indent indent);



        Common::Text itemName(const std::unique_ptr<Object::Item>& item);

        void showAll(Object::Inventory& inventory, const Indent indent);

        Object::Character* pickCharacter(Object::Squad& squad, const Indent indent);

        void showSquad(const Object::Squad& squad, const Indent indent);

        void showStats(const Object::Character& character, const Indent indent);

        void showGear(const Object::Character& character, const Indent indent);

        Common::Text attLevel(const Common::SpecStorage<Common::LevelStat>& level, bool accepted = false);

        void showAllAttributes(const Object::Character& character, const Indent indent, bool accepted = false);

        void showAttribute(Object::Character& character, Object::Attribute::Type type,
            const Indent indent, bool accepted = false);

        void showAttPoints(const Object::Character& character, const Indent indent, bool accepted = false);

        Object::Attribute::Type pickAttribute(const Indent indent);

    }
}

#endif // !MAINMENU_HPP
