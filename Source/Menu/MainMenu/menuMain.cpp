
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"gameFB_generated.h"
#include"menuCharacter.hpp"
#include"menuCommonText.hpp"
#include"menuInventory.hpp"
#include"menuMain.hpp"
#include"menuMainAux.hpp"
#include"menuMainInit.hpp"
#include"menuMainText.hpp"
#include"menuOptions.hpp"
#include"menuSquad.hpp"
#include<filesystem>

namespace game {
namespace menu {

using namespace std;

void menuMain(
    istream& is,
    ostream& os,
    std::unique_ptr<object::Squad>& _squad,
    std::unique_ptr<object::Inventory>& _shop)
{
    initializeMenuText();

    Indent ind0{ Indent{} };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    while (true)
    {
        auto& squad{ *_squad };
        auto& shop{ *_shop };

        verticalIndent(os);
        os << ind0 << text.menuName() << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, text.exit()) << endl;
        printNumBar(os, ind1, actionMain::MENU_OPTION, text.enterOptions()) << endl;
        printNumBar(os, ind1, actionMain::MENU_SQUAD, text.enterSquad()) << endl;
        printNumBar(os, ind1, actionMain::MENU_INVENTORY, text.enterInventory()) << endl;
        printNumBar(os, ind1, actionMain::MENU_TRADE, text.enterTrade()) << endl;
        printNumBar(os, ind1, actionMain::SAVE_GAME, text.saveGame()) << endl;
        printNumBar(os, ind1, actionMain::LOAD_GAME, text.loadGame()) << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionMain::MENU_OPTION:
            menuOptions(is, os, ind1);
            break;
        case actionMain::MENU_SQUAD:
            menuSquad(is, os, squad, ind1);
            break;
        case actionMain::MENU_INVENTORY:
            menuInventory(is, os, squad, ind1);
            break;
        case actionMain::MENU_TRADE:
            menuTrade(is, os, squad, shop, ind1);
            break;
        case actionMain::SAVE_GAME:
            saveGame(is, os, _squad, _shop, ind1);
            break;
        case actionMain::LOAD_GAME:
            loadGame(is, os, _squad, _shop, ind1);
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

void menuTrade(
    istream& is,
    ostream& os,
    object::Squad& squad,
    object::Inventory& shop,
    const Indent indent)
{
    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };

    while (true)
    {
        verticalIndent(os);
        os << ind0 << "Trade menu" << endl;
        os << ind0 << comT.actions() << endl;
        printNumBar(os, ind1, actionCommon::EXIT, comT.exitMenu()) << endl;
        printNumBar(os, ind1, actionTrade::SHOW_ALL_ITEMS, "Show all items") << endl;
        printNumBar(os, ind1, actionTrade::BUY_ITEM, "Buy items") << endl;
        printNumBar(os, ind1, actionTrade::SELL_ITEM, "Sell items") << endl;
        os << ind0 << comT.enterAction() << endl;

        switch (getAction(is, os)) {
        case actionTrade::SHOW_ALL_ITEMS:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionTrade::BUY_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
            break;
        case actionTrade::SELL_ITEM:
            os << ind0 << comT.notImplemented() << endl;
            // TODO
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

void saveGame(
    istream& is,
    ostream& os,
    unique_ptr<object::Squad>& squad,
    unique_ptr<object::Inventory>& shop,
    const Indent indent)
{
    using namespace std::filesystem;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad.get() != nullptr);
    assert(shop.get() != nullptr);
    auto filenamePair{ getFilename(is, os, indent) };
    if (!filenamePair.second) {
        os << indent << text.gameNotSaved() << endl;
        return;
    }
    auto filename{ filenamePair.first + sign::dot + SAVE_FILE_EXTENSION };
    auto filePath{ current_path() };
    filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC);
    create_directory(filePath);
    filePath.append(filename);
    auto filePathStr{ filePath.u8string() };

    flatbuffers::FlatBufferBuilder fbb;

    auto squadOffset{ squad->serialize(fbb) };
    auto shopOffset{ shop->serialize(fbb) };

    fbGame::FB_GameBuilder b{ fbb };
    b.add_squad(squadOffset);
    b.add_shop(shopOffset);
    auto root{ b.Finish() };

    fbb.Finish(root);

    common::writeBinFlatBuffer(filePathStr.c_str(), fbb.GetBufferPointer(), fbb.GetSize());

    os << indent << text.gameSaved() << sign::dot << sign::space
        << comT.file() << sign::colon << sign::space << filePathStr << endl;
}

void loadGame(
    istream& is,
    ostream& os,
    unique_ptr<object::Squad>& squad,
    unique_ptr<object::Inventory>& shop,
    const Indent indent)
{
    using namespace std::filesystem;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad.get() != nullptr);
    assert(shop.get() != nullptr);
    auto filePath{ current_path() };
    filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC);
    auto fileExtension{ string{ sign::dot } + SAVE_FILE_EXTENSION };
    os << ind0 << text.fileList() << sign::colon << endl;
    for (const auto& dir : directory_iterator{ filePath }) {
        if (dir.path().extension().u8string() == fileExtension) {
            os << ind1 << dir.path().filename().u8string() << endl;
        }
    }

    auto filenamePair{ getFilename(is, os, ind0) };
    if (!filenamePair.second) {
        os << ind0 << text.gameNotLoaded() << endl;
        return;
    }
    auto filename{ filenamePair.first + sign::dot + SAVE_FILE_EXTENSION };
    filePath.append(filename);
    auto filePathStr{ filePath.u8string() };

    unique_ptr<char[]> buffer;
    common::readBinFlatBuffer(filePathStr.c_str(), buffer);
    const fbGame::FB_Game* fb{ fbGame::GetFB_Game(buffer.get()) };
    assert(fb != nullptr);

    auto loadedSquad{ object::Squad::deserialize(fb->squad()) };
    auto loadedShop{ object::Inventory::deserialize(fb->shop()) };

    squad.reset(loadedSquad.release());
    shop.reset(loadedShop.release());

    os << ind0 << text.gameLoaded() << sign::dot << sign::space
        << comT.file() << sign::colon << sign::space << filePathStr << endl;
}

} // namespace menu
} // namespace game
