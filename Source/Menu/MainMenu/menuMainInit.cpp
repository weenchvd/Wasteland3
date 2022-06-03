
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuAttributeText.hpp"
#include"menuCharacterText.hpp"
#include"menuCommonText.hpp"
#include"menuInventoryText.hpp"
#include"menuItemText.hpp"
#include"menuMainInit.hpp"
#include"menuMainText.hpp"
#include"menuOptionsText.hpp"
#include"menuSkillText.hpp"

namespace game {
namespace menu {

using namespace std;

void initializeMenuText()
{
    MenuCommonText::initialize();
    MenuMainText::initialize();
    MenuOptionsText::initialize();
    MenuInventoryText::initialize();
    MenuItemText::initialize();
    MenuAttributeText::initialize();
    MenuSkillText::initialize();
    MenuCharacterText::initialize();
}

} // namespace menu
} // namespace game
