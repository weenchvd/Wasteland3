
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuCommon.hpp"
#include<string>

namespace Game {
namespace Menu {

using namespace std;


Indent operator+(const Indent& left, const Indent& right) {
    return Indent{ left.get() + right.get() };
}

ostream& operator<<(ostream& os, const Indent& indent) {
    for (unsigned int i = 0; i < indent.get(); ++i) {
        os.put(' ');
    }
    return os;
}

int getAction()
{
    cout << "> Enter an action: ";
    string input;
    getline(cin, input);
    try {
        return stoi(input);
    }
    catch (...) {
        return ActionCommon::INVALID;
    }
}

int getPosNumber()
{
    cout << "> Enter a number: ";
    string input;
    getline(cin, input);
    int n;
    try {
        n = stoi(input);
    }
    catch (...) {
        return -1;
    }
    if (n < 0) {
        return -1;
    }
    return n;
}

YesNo getYesNo()
{
    cout << "> 'Y' Yes | 'N' No: ";
    string input;
    getline(cin, input);
    if (input.size() != sizeof('Y')) {
        return YesNo::INVALID;
    }
    char ch = toupper(input[0]);
    if (ch == 'Y') {
        return YesNo::YES;
    }
    else if (ch == 'N') {
        return YesNo::NO;
    }
    else {
        return YesNo::INVALID;
    }
}

Common::Text statLevel(const Common::SpecStorage<Common::LevelStat>& level, bool accepted)
{
    Common::Text s;
    if (accepted) {
        for (Common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
            if (i <= level.getAccepted()) {
                s += '+';
            }
            else {
                s += '-';
            }
        }
    }
    else {
        for (Common::LevelStat i = level.getMinPossible() + 1; i <= level.getMaxPossible(); ++i) {
            if (i <= level.get()) {
                s += '+';
            }
            else {
                s += '-';
            }
        }
    }
    return s;
}

unsigned int utf8Size(const std::string& s)
{
    unsigned int size{ 0 };
    for (auto& ch : s) {
        if ((ch & 0xC0) != 0x80) {
            ++size;
        }
    }
    return size;
}

Game::Common::Text fillWithPlaseholders(
    const Game::Common::Text& source,
    unsigned char width,
    char placeholder)
{
    Game::Common::Text t{ source };
    for (int i = utf8Size(source); i < width; ++i) {
        t += placeholder;
    }
    return t;
}

} // namespace Menu
} // namespace Game
