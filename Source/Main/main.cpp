
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"initialization.hpp"
#include"initializationAux.hpp"
#include"inventory.hpp"
#include"locator.hpp"
#include"menuMain.hpp"
#include"squad.hpp"
#include<iostream>
#include<memory>

#include<cstdio>
#include<string>
#include<Windows.h>

int main()
{
    using namespace std;

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    cout << "\twl3.exe Start!" << endl;
    cout << "----Welcome to Wasteland 3!----" << endl;

    try {
        game::global::initializeGame();

        auto squad{ make_unique<game::object::Squad>() };
        init::initializeSquad(*squad);

        auto shop{ make_unique<game::object::Inventory>() };
        init::initializeShop(*shop);

        game::menu::menuMain(cin, cout, squad, shop);
    }
    catch (const std::exception& e) {
        game::global::Locator::getErrorStream() << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch (...) {
        game::global::Locator::getErrorStream() << u8"[Unknown exception]" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "\twl3.exe Done!" << endl;
    return 0;
}
