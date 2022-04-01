
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoPath.hpp"
#include"ammoText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace object {

using namespace std;

global::PlainTextBase                       AmmoText::base_;
AmmoTextCommon                              AmmoText::common_;
bool                                        AmmoText::initialized_{ false };

///************************************************************************************************

void AmmoText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    if (!common::readBinFlatBuffer(AMMO_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer)) {
        abort();
    }
    const fbAmmo::FB_AmmoText* fb{
        fbAmmo::GetFB_AmmoText(buffer.get())
    };

    assert(fb != nullptr);
    initCommon(fb->common());

    initialized_ = true;
}

void AmmoText::initCommon(const fbAmmo::FB_AmmoTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->item_type(), common_.itemType_);
    common::initLanguageBundle(fb->quantity(), common_.qty_);
}

} // namespace object
} // namespace game
