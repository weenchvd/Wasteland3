
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"plainText.hpp"

namespace Game
{
    namespace Global
    {
        using namespace std;

        PlainText::PlainText(PlainText::Language lang)
            : lang_{ lang }
        {
            initialize();
        }

        void PlainText::language(PlainText::Language lang)
        {
            if (lang_ == lang) return;
            lang_ = lang;
            initialize();
        }

        const Game::Common::Text& PlainText::common(PlainText::General id) const noexcept
        {
            if (Common::isValidEnum(id)) {
                return common_[Common::toUnderlying(id)];
            }
            return common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)];
        }

        const Game::Common::Text& PlainText::skill(PlainText::Skill id) const noexcept
        {
            if (Common::isValidEnum(id)) {
                return skill_[Common::toUnderlying(id)];
            }
            return common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)];
        }

        const Game::Common::Text& PlainText::skill(Object::Skill::Type id) const noexcept
        {
            if (Common::isValidEnum(id)) {
                return skillType_[Common::toUnderlying(id)];
            }
            return common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)];

        }

        void PlainText::initialize()
        {
            fill();
            switch (lang_) {
            case PlainText::Language::ENGLISH:
                initializeEN();
                break;
            case PlainText::Language::RUSSIAN:
                initializeRU();
                break;
            default:
                initializeEN();
                break;
            }
            common_[Common::toUnderlying(PlainText::General::INVALID_ENUM)]
                = invalidEnum;
        }

        void PlainText::initializeEN()
        {
            initCommonEN();
            initSkillEN();
        }

        void PlainText::initializeRU()
        {
            initCommonRU();
            initSkillRU();
        }

        void PlainText::fill()
        {
            fillAll(common_, getDefault());
            fillAll(skill_, getDefault());
            fillAll(skillType_, getDefault());
        }

        const Game::Common::Text& PlainText::getDefault() const noexcept
        {
            switch (lang_) {
            case PlainText::Language::ENGLISH:
                return eng_NoData;
            case PlainText::Language::RUSSIAN:
                return rus_NoData;
            default:
                return eng_NoData;
            }
        }

        void PlainText::initCommonEN()
        {
            common_[Common::toUnderlying(PlainText::General::NO_DATA)]
                = eng_NoData;
        }

        void PlainText::initSkillEN()
        {
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_COMBAT)]
                = Common::Text{ u8"Combat Skills" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_GENERAL)]
                = Common::Text{ u8"General Skills" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_EXPLORATION)]
                = Common::Text{ u8"Exploration Skills" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_SOCIAL)]
                = Common::Text{ u8"Social Skills" };



            skillType_[Common::toUnderlying(Object::Skill::Type::AUTOMATIC_WEAPONS)]
                = Common::Text{ u8"Automatic Weapons" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BIG_GUNS)]
                = Common::Text{ u8"Big Guns" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BRAWLING)]
                = Common::Text{ u8"Brawling" };
            skillType_[Common::toUnderlying(Object::Skill::Type::MELEE_COMBAT)]
                = Common::Text{ u8"Melee Combat" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SMALL_ARMS)]
                = Common::Text{ u8"Small Arms" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SNIPER_RIFLES)]
                = Common::Text{ u8"Sniper Rifles" };
            skillType_[Common::toUnderlying(Object::Skill::Type::ANIMAL_WHISPERER)]
                = Common::Text{ u8"Animal Whisperer" };
            skillType_[Common::toUnderlying(Object::Skill::Type::EXPLOSIVES)]
                = Common::Text{ u8"Explosives" };
            skillType_[Common::toUnderlying(Object::Skill::Type::FIRST_AID)]
                = Common::Text{ u8"First Aid" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SNEAKY_SHIT)]
                = Common::Text{ u8"Sneaky Shit" };
            skillType_[Common::toUnderlying(Object::Skill::Type::WEIRD_SCIENCE)]
                = Common::Text{ u8"Weird Science" };
            skillType_[Common::toUnderlying(Object::Skill::Type::ARMOR_MODDING)]
                = Common::Text{ u8"Armor Modding" };
            skillType_[Common::toUnderlying(Object::Skill::Type::LOCKPICKING)]
                = Common::Text{ u8"Lockpicking" };
            skillType_[Common::toUnderlying(Object::Skill::Type::NERD_STUFF)]
                = Common::Text{ u8"Nerd Stuff" };
            skillType_[Common::toUnderlying(Object::Skill::Type::MECHANICS)]
                = Common::Text{ u8"Mechanics" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SURVIVAL)]
                = Common::Text{ u8"Survival" };
            skillType_[Common::toUnderlying(Object::Skill::Type::TOASTER_REPAIR)]
                = Common::Text{ u8"Toaster Repair" };
            skillType_[Common::toUnderlying(Object::Skill::Type::WEAPON_MODDING)]
                = Common::Text{ u8"Weapon Modding" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BARTER)]
                = Common::Text{ u8"Barter" };
            skillType_[Common::toUnderlying(Object::Skill::Type::HARD_ASS)]
                = Common::Text{ u8"Hard Ass" };
            skillType_[Common::toUnderlying(Object::Skill::Type::KISS_ASS)]
                = Common::Text{ u8"Kiss Ass" };
            skillType_[Common::toUnderlying(Object::Skill::Type::LEADERSHIP)]
                = Common::Text{ u8"Leadership" };
        }

        void PlainText::initCommonRU()
        {
            common_[Common::toUnderlying(PlainText::General::NO_DATA)]
                = rus_NoData;
        }

        void PlainText::initSkillRU()
        {
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_COMBAT)]
                = Common::Text{ u8"������ ������" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_GENERAL)]
                = Common::Text{ u8"����� ������" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_EXPLORATION)]
                = Common::Text{ u8"����������������� ������" };
            skill_[Common::toUnderlying(PlainText::Skill::GROUP_SOCIAL)]
                = Common::Text{ u8"���������� ������" };



            skillType_[Common::toUnderlying(Object::Skill::Type::AUTOMATIC_WEAPONS)]
                = Common::Text{ u8"�������. ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BIG_GUNS)]
                = Common::Text{ u8"������� ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BRAWLING)]
                = Common::Text{ u8"����������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::MELEE_COMBAT)]
                = Common::Text{ u8"������� ���" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SMALL_ARMS)]
                = Common::Text{ u8"���������� ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SNIPER_RIFLES)]
                = Common::Text{ u8"����������� ��������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::ANIMAL_WHISPERER)]
                = Common::Text{ u8"������������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::EXPLOSIVES)]
                = Common::Text{ u8"����������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::FIRST_AID)]
                = Common::Text{ u8"������ ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SNEAKY_SHIT)]
                = Common::Text{ u8"����������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::WEIRD_SCIENCE)]
                = Common::Text{ u8"������ �����" };
            skillType_[Common::toUnderlying(Object::Skill::Type::ARMOR_MODDING)]
                = Common::Text{ u8"���. �����" };
            skillType_[Common::toUnderlying(Object::Skill::Type::LOCKPICKING)]
                = Common::Text{ u8"���������� ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::NERD_STUFF)]
                = Common::Text{ u8"���������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::MECHANICS)]
                = Common::Text{ u8"������ � ���������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::SURVIVAL)]
                = Common::Text{ u8"���������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::TOASTER_REPAIR)]
                = Common::Text{ u8"������ ��������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::WEAPON_MODDING)]
                = Common::Text{ u8"���. ������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::BARTER)]
                = Common::Text{ u8"������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::HARD_ASS)]
                = Common::Text{ u8"�������� �������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::KISS_ASS)]
                = Common::Text{ u8"�������" };
            skillType_[Common::toUnderlying(Object::Skill::Type::LEADERSHIP)]
                = Common::Text{ u8"���������" };
        }

    }
}
