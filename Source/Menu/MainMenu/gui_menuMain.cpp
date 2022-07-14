
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
#include"menuCommonText.hpp"
#include"menuMain.hpp"
#include"menuMainAux.hpp"
#include"menuMainText.hpp"
#include<cstdlib>
#include<filesystem>
#include<regex>

namespace game {
namespace menu {

using namespace std;

void guiMenuMain(bool* open,
                 unique_ptr<game::object::Squad>& squad,
                 unique_ptr<game::object::Inventory>& shop)
{
    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    static bool showGuiMenuOption       { false };
    static bool showGuiMenuSaveGame     { false };
    static bool showGuiMenuLoadGame     { false };

    if (showGuiMenuOption)              guiMenuOptions(&showGuiMenuOption);
    if (showGuiMenuSaveGame)            guiMenuSaveGame(&showGuiMenuSaveGame, squad, shop);
    if (showGuiMenuLoadGame)            guiMenuLoadGame(&showGuiMenuLoadGame, squad, shop);

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.menuName().c_str() } + u8"###MenuMain";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        ImGui::Text(comT.actions().c_str());
        if (ImGui::Button(text.enterSquad().c_str())) {

        }
        if (ImGui::Button(text.enterInventory().c_str())) {

        }
        if (ImGui::Button(text.enterTrade().c_str())) {

        }
        s = string{ text.enterOptions().c_str() } + u8"###EnterOptions";
        if (ImGui::Button(s.c_str())) {
            showGuiMenuOption = true;
        }

        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        if (ImGui::Button(text.saveGame().c_str())) {
            showGuiMenuSaveGame = true;
        }
        if (ImGui::Button(text.loadGame().c_str())) {
            showGuiMenuLoadGame = true;
        }
        ImGui::NewLine();
        if (ImGui::Button(text.exit().c_str())) {
            *open = false;
        }

        ImGui::End();
    }
}

void guiMenuSaveGame(bool* open,
                     unique_ptr<object::Squad>& squad,
                     unique_ptr<object::Inventory>& shop)
{
    using namespace std::filesystem;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad != nullptr);
    assert(shop != nullptr);

    static bool showMessage{ false };

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.saveGame() } + u8"###MenuSaveGame";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        vector<string> filenames;
        auto filePath{ current_path() };
        filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC).make_preferred();
        auto fileExtension{ string{ sign::dot } + SAVE_FILE_EXTENSION };
        for (const auto& dir : directory_iterator{ filePath }) {
            if (dir.path().extension().u8string() == fileExtension) {
                filenames.push_back(dir.path().stem().u8string());
            }
        }

        s = string{ text.fileList() } + sign::colon;
        ImGui::Text(s.c_str());

        constexpr int invalidIndex{ -1 };
        static int curIndex{ invalidIndex };
        ImVec2 boxSize{ ImGui::GetContentRegionAvail() };
        boxSize.y *= 0.7f;
        if (ImGui::BeginListBox("###Filenames", boxSize)) {
            for (int i = 0; i < filenames.size(); ++i) {
                if (ImGui::Selectable(filenames[i].c_str(), false,
                    ImGuiSelectableFlags_AllowDoubleClick))
                {
                    constexpr int mouseButtonLeft{ 0 };
                    if (ImGui::IsMouseDoubleClicked(mouseButtonLeft)) {
                        curIndex = i;
                    }
                }
            }

            ImGui::EndListBox();
        }

        struct InputTextFilter {
            static int Filename(ImGuiInputTextCallbackData* data)
            {
                static wregex r{ fileStemRuleW };
                static wsmatch mr;
                wstring input{ data->EventChar };
                if (regex_match(input, mr, r)) return 0;
                return 1;
            }
        };

        ImGui::NewLine();
        s = string{ comT.enterFilenameNoExt() } + sign::colon;
        ImGui::Text(s.c_str());

        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
        constexpr int bufferSize{ 512 };
        static char buffer[bufferSize]{ "" };
        ImGui::InputText("###Filename", buffer, bufferSize, ImGuiInputTextFlags_CallbackCharFilter,
            InputTextFilter::Filename);
        ImGui::PopItemWidth();
        if (curIndex != invalidIndex) {
            if (filenames[curIndex].size() < bufferSize) {
                strcpy(buffer, filenames[curIndex].c_str());
            }
            curIndex = invalidIndex;
        }

        static string message;
        s = string{ text.saveGame() } + u8"###SaveGame";
        if (ImGui::Button(s.c_str())) {
            if (strlen(buffer) > 0) {
                string filename{ string{ buffer } + fileExtension };
                filePath.append(filename).make_preferred();
                buffer[0] = sign::nl;
                bool error{ false };
                try {
                    flatbuffers::FlatBufferBuilder fbb;

                    auto squadOffset{ squad->serialize(fbb) };
                    auto shopOffset{ shop->serialize(fbb) };

                    fbGame::FB_GameBuilder b{ fbb };
                    b.add_squad(squadOffset);
                    b.add_shop(shopOffset);
                    auto root{ b.Finish() };

                    fbb.Finish(root);

                    common::writeBinFlatBuffer(filePath.u8string().c_str(),
                        fbb.GetBufferPointer(), fbb.GetSize());

                    message = string{ text.gameSaved() } + sign::dot + sign::space
                        + comT.file() + sign::colon + sign::nl + filePath.u8string();
                }
                catch (...) {
                    error = true;
                }
                if (error) {
                    message = string{ comT.errorOccurred() } + sign::dot + sign::space
                        + text.gameNotSaved();
                }
            }
            else {
                message = text.filenameNotSpec();
            }
            showMessage = true;
        }

        ImGui::NewLine();
        if (ImGui::Button(comT.back().c_str())) {
            *open = false;
        }

        guiPopupMessage(&showMessage, u8"##Message", message.c_str());

        ImGui::End();
    }
}

void guiMenuLoadGame(bool* open,
                     unique_ptr<object::Squad>& squad,
                     unique_ptr<object::Inventory>& shop)
{
    using namespace std::filesystem;

    const auto& comT{ MenuCommonText::common() };
    const auto& text{ MenuMainText::common() };

    assert(squad != nullptr);
    assert(shop != nullptr);

    static bool showMessage{ false };

    ImGuiWindowFlags window_flags{ 0 };
    guiCommonInitialization(window_flags);
    string s;

    s = string{ text.loadGame() } + u8"###MenuLoadGame";
    if (ImGui::Begin(s.c_str(), nullptr, window_flags)) {
        vector<string> filenames;
        auto filePath{ current_path() };
        filePath.append(SAVES__DIR__REL_PATH_FROM_W3EXEC).make_preferred();
        auto fileExtension{ string{ sign::dot } + SAVE_FILE_EXTENSION };
        for (const auto& dir : directory_iterator{ filePath }) {
            if (dir.path().extension().u8string() == fileExtension) {
                filenames.push_back(dir.path().stem().u8string());
            }
        }

        s = string{ text.fileList() } + sign::colon;
        ImGui::Text(s.c_str());

        constexpr int invalidIndex{ -1 };
        static int curIndex{ invalidIndex };
        ImVec2 boxSize{ ImGui::GetContentRegionAvail() };
        boxSize.y *= 0.7f;
        if (ImGui::BeginListBox("###Filenames", boxSize)) {
            for (int i = 0; i < filenames.size(); ++i) {
                const bool isSelected{ i == curIndex ? true : false };
                if (ImGui::Selectable(filenames[i].c_str(), isSelected)) {
                    curIndex = i;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndListBox();
        }

        ImGui::NewLine();
        static string message;
        s = string{ text.loadGame() } + u8"###LoadGame";
        if (ImGui::Button(s.c_str())) {
            if (curIndex >= 0 && curIndex < filenames.size()) {
                string filename{ filenames[curIndex] + fileExtension };
                filePath.append(filename).make_preferred();
                bool error{ false };
                try {
                    unique_ptr<char[]> buffer;
                    common::readBinFlatBuffer(filePath.u8string().c_str(), buffer);
                    const fbGame::FB_Game* fb{ fbGame::GetFB_Game(buffer.get()) };
                    assert(fb != nullptr);

                    auto loadedSquad{ object::Squad::deserialize(fb->squad()) };
                    auto loadedShop{ object::Inventory::deserialize(fb->shop()) };

                    squad.reset(loadedSquad.release());
                    shop.reset(loadedShop.release());

                    message = string{ text.gameLoaded() } + sign::dot + sign::space
                        + comT.file() + sign::colon + sign::nl + filePath.u8string();
                }
                catch (...) {
                    error = true;
                }
                if (error) {
                    message = string{ comT.errorOccurred() } + sign::dot + sign::space
                        + text.gameNotLoaded();
                }
            }
            else {
                message = text.fileNotSelected();
            }
            showMessage = true;
        }

        ImGui::NewLine();
        if (ImGui::Button(comT.back().c_str())) {
            *open = false;
            curIndex = invalidIndex;
        }

        guiPopupMessage(&showMessage, u8"##Message", message.c_str());

        ImGui::End();
    }
}

} // namespace menu
} // namespace game
