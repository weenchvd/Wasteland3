
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_COMMON_TEXT_HPP
#define MENU_COMMON_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuCommonTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuCommonText;

private:
    MenuCommonTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& actions() const noexcept { return actions_[li()]; }

    const text_t& exitMenu() const noexcept { return exitMenu_[li()]; }

    const text_t& invalidInput() const noexcept { return invalidInput_[li()]; }

    const text_t& invalidType() const noexcept { return invalidType_[li()]; }

    const text_t& invalidNumber() const noexcept { return invalidNumber_[li()]; }

    const text_t& unknownAction() const noexcept { return unknownAct_[li()]; }

    const text_t& enterAction() const noexcept { return enterAct_[li()]; }

    const text_t& enterNumber() const noexcept { return enterNum_[li()]; }

    const text_t& enterFilenameNoExt() const noexcept { return enterFilenameNoExt_[li()]; }

    const text_t& file() const noexcept { return file_[li()]; }

    const text_t& selectType() const noexcept { return selectType_[li()]; }

    const text_t& remove() const noexcept { return remove_[li()]; }

    const text_t& yes() const noexcept { return yes_[li()]; }

    const text_t& no() const noexcept { return no_[li()]; }

    const text_t& cancel() const noexcept { return cancel_[li()]; }

    const text_t& close() const noexcept { return close_[li()]; }

    const text_t& back() const noexcept { return back_[li()]; }

    const text_t& description() const noexcept { return description_[li()]; }

    const text_t& all() const noexcept { return all_[li()]; }

    const text_t& promptSymbol() const noexcept { return promptSymbol_[li()]; }

    const text_t& errorSymbol() const noexcept { return errorSymbol_[li()]; }

    const text_t& notImplemented() const noexcept { return notImplemented_[li()]; }

    const text_t& saveChanges() const noexcept { return saveChanges_[li()]; }

    const text_t& cancelChanges() const noexcept { return cancelChanges_[li()]; }

    const text_t& changesSaved() const noexcept { return changesSaved_[li()]; }

    const text_t& changesCanceled() const noexcept { return changesCanceled_[li()]; }

    const text_t& actionFailed() const noexcept { return actionFailed_[li()]; }

    const text_t& errorOccurred() const noexcept { return errorOccurred_[li()]; }

private:
    language_bundle_t actions_;
    language_bundle_t exitMenu_;
    language_bundle_t invalidInput_;
    language_bundle_t invalidType_;
    language_bundle_t invalidNumber_;
    language_bundle_t unknownAct_;
    language_bundle_t enterAct_;
    language_bundle_t enterNum_;
    language_bundle_t enterFilenameNoExt_;
    language_bundle_t file_;
    language_bundle_t selectType_;
    language_bundle_t remove_;
    language_bundle_t yes_;
    language_bundle_t no_;
    language_bundle_t cancel_;
    language_bundle_t close_;
    language_bundle_t back_;
    language_bundle_t description_;
    language_bundle_t all_;
    language_bundle_t promptSymbol_;
    language_bundle_t errorSymbol_;
    language_bundle_t notImplemented_;
    language_bundle_t saveChanges_;
    language_bundle_t cancelChanges_;
    language_bundle_t changesSaved_;
    language_bundle_t changesCanceled_;
    language_bundle_t actionFailed_;
    language_bundle_t errorOccurred_;
};

///************************************************************************************************

class MenuCommonText {
private:
    MenuCommonText() noexcept {}

public:
    MenuCommonText(const MenuCommonText&) = delete;
    MenuCommonText& operator=(const MenuCommonText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuCommonTextCommon& common() noexcept { return common_; }

private:
    static void initCommon();

private:
    static global::PlainTextBase                    base_;
    static MenuCommonTextCommon                     common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuCommonTextCommon::language_index_t MenuCommonTextCommon::li() const noexcept
{
    return { MenuCommonText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_COMMON_TEXT_HPP
