
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuMain.hpp"
#include"textUI.hpp"
#include<iostream>

#include<cstdio>
#include<string>
#include<Windows.h>


void textUI(
    std::unique_ptr<game::object::Squad>& squad,
    std::unique_ptr<game::object::Inventory>& shop)
{
    using namespace std;

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    cout << "\twl3.exe Start!" << endl;
    cout << "----Welcome to Wasteland 3!----" << endl;

    game::menu::menuMain(cin, cout, squad, shop);

    cout << "\twl3.exe Done!" << endl;
}
