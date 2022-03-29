
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef AMMO_TEXT_HPP
#define AMMO_TEXT_HPP

#include"ammoCommon.hpp"
#include"ammoTextFB_generated.h"
#include"common.hpp"
#include"plainTextBase.hpp"
#include<array>

namespace game {
namespace object {

class AmmoTextCommon {
public:
    using text_t = common::Text;

private:
    using language_bundle_t = std::array<text_t, global::PlainTextBase::sizeLang_>;
    using language_index_t  = decltype(global::PlainTextBase::languageIndex());

    friend class AmmoText;

private:
    AmmoTextCommon() noexcept {}

    language_index_t li() const noexcept;

public:
    const text_t& itemType() const noexcept { return itemType_[li()]; }

    const text_t& quantity() const noexcept { return qty_[li()]; }

private:
    language_bundle_t itemType_;
    language_bundle_t qty_;
};

///************************************************************************************************

class AmmoText {
private:
    friend class Ammo;

private:
    AmmoText() noexcept {}

public:
    AmmoText(const AmmoText&) = delete;
    AmmoText& operator=(const AmmoText&) = delete;

    static void initialize();

    static bool isInitialized() noexcept { return initialized_ && base_.isInitialized(); }

    static auto languageIndex() noexcept { return base_.languageIndex(); }

    static const AmmoTextCommon& common() noexcept { return common_; }

private:
    static void initCommon(const fbAmmo::FB_AmmoTextCommon* fb);

private:
    static global::PlainTextBase                    base_;
    static AmmoTextCommon                           common_;
    static bool                                     initialized_;
};

///************************************************************************************************

inline AmmoTextCommon::language_index_t AmmoTextCommon::li() const noexcept
{
    return { AmmoText::languageIndex() };
}

} // namespace object
} // namespace game

#endif // !AMMO_TEXT_HPP
