
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"graphicUI.hpp"
#include"initialization.hpp"
#include"initializationAux.hpp"
#include"inventory.hpp"
#include"locator.hpp"
#include"squad.hpp"
#include"textUI.hpp"
#include<memory>


int main(int argc, char* argv[])
{
    using namespace std;

    bool isGUI{ true };
    if (argc > 1) {
        if (strcmp(argv[1], "--textUI") == 0) {
            isGUI = false;
        }
    }

    try {
        game::global::initializeGame();

        auto squad{ make_unique<game::object::Squad>() };
        init::initializeSquad(*squad);

        auto shop{ make_unique<game::object::Inventory>() };
        init::initializeShop(*shop);

        if (isGUI) {
            graphicUI(squad, shop);
        }
        else {
            textUI(squad, shop);
        }
    }
    catch (const std::exception& e) {
        game::global::Locator::getErrorStream() << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch (...) {
        game::global::Locator::getErrorStream() << u8"[Unknown exception]" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
