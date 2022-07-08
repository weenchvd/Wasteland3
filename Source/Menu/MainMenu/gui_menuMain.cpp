
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"gameFB_generated.h"
#include"gui_menuCommon.hpp"
#include"gui_menuMain.hpp"
#include"gui_menuOptions.hpp"
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"menuCommonText.hpp"
#include"menuMainText.hpp"
#include<d3d11.h>
#include<filesystem>
#include<tchar.h>

namespace game {
namespace menu {

using namespace std;

void guiMenuMain(
    std::unique_ptr<game::object::Squad>& squad,
    std::unique_ptr<game::object::Inventory>& shop,
    bool* open)
{
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    static bool showGuiMenuOption{ false };

    if (showGuiMenuOption)              guiMenuOptions(&showGuiMenuOption);

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuMain";
    ImGui::Begin(s.c_str(), nullptr, window_flags);

    ImGui::Text(comT.actions().c_str());
    s = string{ text.enterOptions().c_str() } + u8"###EnterOptions";
    if (ImGui::Button(s.c_str())) {
        showGuiMenuOption = true;
    }
    if (ImGui::Button(text.enterSquad().c_str())) {

    }
    if (ImGui::Button(text.enterInventory().c_str())) {

    }
    if (ImGui::Button(text.enterTrade().c_str())) {

    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button(text.saveGame().c_str())) {

    }
    if (ImGui::Button(text.loadGame().c_str())) {

    }
    ImGui::NewLine();
    if (ImGui::Button(text.exit().c_str())) {
        *open = false;
    }

    ImGui::End();
}

///************************************************************************************************
/*
void saveGame(
    unique_ptr<object::Squad>& squad,
    unique_ptr<object::Inventory>& shop) noexcept
{
    using namespace std::filesystem;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad.get() != nullptr);
    assert(shop.get() != nullptr);

    try {
        regex regexFileStem{ fileStemRule };
        auto fileStemPair{ getFileStem(is, os, regexFileStem, ind0) };
        if (!fileStemPair.second) {
            os << ind0 << text.gameNotSaved() << endl;
            return;
        }
        auto filename{ fileStemPair.first + sign::dot + SAVE_FILE_EXTENSION };
        auto filePath{ current_path() };
        filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC).make_preferred();
        create_directories(filePath);
        filePath.append(filename).make_preferred();
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

        os << ind0 << text.gameSaved() << sign::dot << sign::space
            << comT.file() << sign::colon << sign::space << filePathStr << endl;
        return;
    }
    catch (exception& e) {
        os << comT.errorSymbol() << e.what() << endl;
    }
    catch (...) {}

    os << ind0 << comT.errorOccurred() << sign::dot << sign::space
        << text.gameNotSaved() << endl;
}

void loadGame(
    istream& is,
    ostream& os,
    unique_ptr<object::Squad>& squad,
    unique_ptr<object::Inventory>& shop,
    const Indent indent) noexcept
{
    using namespace std::filesystem;

    Indent ind0{ indent };
    Indent ind1{ ind0 + Indent{} };
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad.get() != nullptr);
    assert(shop.get() != nullptr);

    try {
        auto filePath{ current_path() };
        filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC).make_preferred();
        auto fileExtension{ string{ sign::dot } + SAVE_FILE_EXTENSION };
        os << ind0 << text.fileList() << sign::colon << endl;
        for (const auto& dir : directory_iterator{ filePath }) {
            if (dir.path().extension().u8string() == fileExtension) {
                os << ind1 << dir.path().filename().u8string() << endl;
            }
        }

        regex regexFileStem{ fileStemRule };
        auto fileStemPair{ getFileStem(is, os, regexFileStem, ind0) };
        if (!fileStemPair.second) {
            os << ind0 << text.gameNotLoaded() << endl;
            return;
        }
        auto filename{ fileStemPair.first + sign::dot + SAVE_FILE_EXTENSION };
        filePath.append(filename).make_preferred();
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
        return;
    }
    catch (exception& e) {
        os << comT.errorSymbol() << e.what() << endl;
    }
    catch (...) {}

    os << ind0 << comT.errorOccurred() << sign::dot << sign::space
        << text.gameNotLoaded() << endl;
}
*/
} // namespace menu
} // namespace game
