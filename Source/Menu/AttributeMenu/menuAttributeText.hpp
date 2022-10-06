
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef MENU_ATTRIBUTE_TEXT_HPP
#define MENU_ATTRIBUTE_TEXT_HPP

#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace menu {

struct MenuAttributeTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuAttributeText;

private:
    MenuAttributeTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& attributes() const noexcept { return attributes_[li()]; }

    const text_t& attributesAccepted() const noexcept { return attributesAccepted_[li()]; }

    const text_t& attrPoints() const noexcept { return attrPoints_[li()]; }

    const text_t& attrPointsAccepted() const noexcept { return attrPointsAccepted_[li()]; }

    const text_t& selectAttribute() const noexcept { return selectAttribute_[li()]; }

    const text_t& enterNumOfLevels() const noexcept { return enterNumOfLevels_[li()]; }

    const text_t& invalidNumOfLevels() const noexcept { return invalidNumOfLevels_[li()]; }

    const text_t& undoChanges() const noexcept { return undoChanges_[li()]; }

    const text_t& questionUndoChanges() const noexcept { return questionUndoChanges_[li()]; }

    const text_t& confirmChanges() const noexcept { return confirmChanges_[li()]; }

    const text_t& questionConfirmChanges() const noexcept { return questionConfirmChanges_[li()]; }

private:
    language_bundle_t attributes_;
    language_bundle_t attributesAccepted_;
    language_bundle_t attrPoints_;
    language_bundle_t attrPointsAccepted_;
    language_bundle_t selectAttribute_;
    language_bundle_t enterNumOfLevels_;
    language_bundle_t invalidNumOfLevels_;
    language_bundle_t undoChanges_;
    language_bundle_t questionUndoChanges_;
    language_bundle_t confirmChanges_;
    language_bundle_t questionConfirmChanges_;
};

///************************************************************************************************

struct MenuAttributeTextMain {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuAttributeText;

private:
    MenuAttributeTextMain() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showAttributes() const noexcept { return showAttr_[li()]; }

    const text_t& showAttributesAccepted() const noexcept { return showAttrAccepted_[li()]; }

    const text_t& modify() const noexcept { return modify_[li()]; }

    const text_t& questionSaveChanges() const noexcept { return questionSaveChanges_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showAttr_;
    language_bundle_t showAttrAccepted_;
    language_bundle_t modify_;
    language_bundle_t questionSaveChanges_;
};

///************************************************************************************************

struct MenuAttributeTextModify {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class MenuAttributeText;

private:
    MenuAttributeTextModify() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& menuName() const noexcept { return menuName_[li()]; }

    const text_t& showDescription() const noexcept { return showDescription_[li()]; }

    const text_t& increaseLevel() const noexcept { return increaseLevel_[li()]; }

    const text_t& decreaseLevel() const noexcept { return decreaseLevel_[li()]; }

    const text_t& attribute() const noexcept { return attribute_[li()]; }

    const text_t& attributeAccepted() const noexcept { return attributeAccepted_[li()]; }

private:
    language_bundle_t menuName_;
    language_bundle_t showDescription_;
    language_bundle_t increaseLevel_;
    language_bundle_t decreaseLevel_;
    language_bundle_t attribute_;
    language_bundle_t attributeAccepted_;
};

///************************************************************************************************

class MenuAttributeText {
private:
    MenuAttributeText() noexcept {}

public:
    MenuAttributeText(const MenuAttributeText&) = delete;
    MenuAttributeText& operator=(const MenuAttributeText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const MenuAttributeTextCommon& common() noexcept { return common_; }

    static const MenuAttributeTextMain& main() noexcept { return main_; }

    static const MenuAttributeTextModify& modify() noexcept { return modify_; }

private:
    static void initCommon();

    static void initMain();

    static void initModify();

private:
    static global::PlainTextBase                    base_;
    static MenuAttributeTextCommon                  common_;
    static MenuAttributeTextMain                    main_;
    static MenuAttributeTextModify                  modify_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline MenuAttributeTextCommon::language_index_t MenuAttributeTextCommon::li() const noexcept
{
    return { MenuAttributeText::languageIndex() };
}

inline MenuAttributeTextMain::language_index_t MenuAttributeTextMain::li() const noexcept
{
    return { MenuAttributeText::languageIndex() };
}

inline MenuAttributeTextModify::language_index_t MenuAttributeTextModify::li() const noexcept
{
    return { MenuAttributeText::languageIndex() };
}

} // namespace menu
} // namespace game

#endif // !MENU_ATTRIBUTE_TEXT_HPP
