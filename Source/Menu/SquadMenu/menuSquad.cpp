
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCharacter.hpp"
#include"menuCommonText.hpp"
#include"menuSquad.hpp"
#include"menuSquadText.hpp"
#include<limits>

namespace game {
namespace menu {

using namespace std;

void menuSquad(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuSquadText::main() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionSquad::SHOW_MEMBERS, text.showMembers()) << endl;
        printNumBar(os, ind1, actionSquad::MENU_CHARACTER, text.enterCharacter()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionSquad::SHOW_MEMBERS:
            showSquad(is, os, squad, ind1);
            break;
        case actionSquad::MENU_CHARACTER: {
            showSquad(is, os, squad, ind1);
            auto pairCharacter{ pickCharacter(is, os, squad, ind1) };
            if (!pairCharacter.second) break;
            object::Character& character{
                *static_cast<object::Character*>(squad.members()[pairCharacter.first].get())
            };
            menuCharacter(is, os, character, ind1);
            break;
        }
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

pair<int, bool> pickCharacter(istream& is, ostream& os, object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuSquadText::common() };

    os << ind0 << text.selectCharacter() << sign::colon << endl;

    auto pair{ getNumber(is, os) };
    if (pair.second == true) {
        pair.first -= squadCounter::countFrom;
        if (pair.first >= 0 && pair.first < squad.members().size()) {
            if (squad.members()[pair.first]) {
                return { pair.first, true };
            }
        }
        os << comT.errorSymbol() << comT.invalidNumber() << endl;
    }
    return { numeric_limits<int>::min(), false };
}

void showSquad(istream& is, ostream& os, const object::Squad& squad, const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& text{ MenuSquadText::common() };
    const auto& tCharCom{ object::Character::characterText().common() };

    os << ind0 << text.squad() << endl;
    for (int i = 0; i < squad.members().size(); ++i) {
        os << ind1 << text.member() << sign::space << sign::sharp
            << i + squadCounter::countFrom << sign::colon << sign::space;
        if (squad.members()[i] != nullptr) {
            auto& c{ *static_cast<object::Character*>(squad.members()[i].get()) };
            os << c.name() << sign::comma << sign::space << tCharCom.level() << sign::space
                << c.level() << sign::space << c.characterText().type(c.type());
        }
        else {
            os << sign::lp << text.emptySlot() << sign::rp;
        }
        os << endl;
    }
}

} // namespace menu
} // namespace game
