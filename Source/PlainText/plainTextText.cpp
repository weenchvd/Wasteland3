
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"plainTextPath.hpp"
#include"plainTextText.hpp"
#include<assert.h>
#include<memory>
#include<stdlib.h>

namespace game {
namespace global {

using namespace std;

global::PlainTextBase                       PlainTextText::base_;
PlainTextTextCommon                         PlainTextText::common_;
bool                                        PlainTextText::initialized_{ false };

///************************************************************************************************

void PlainTextText::initialize()
{
    if (isInitialized()) return;
    base_.initialize();

    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(PLAINTEXT_TEXT_FB_BIN_FILE__NATIVE_REL_PATH, buffer,
                              PLAINTEXT_TEXT_FB_BIN_FILE__HASH);
    const fbPlainText::FB_PlainTextText* fb{
        fbPlainText::GetFB_PlainTextText(buffer.get())
    };

    assert(fb != nullptr);
    initCommon(fb->common());

    initialized_ = true;
}

void PlainTextText::initCommon(const fbPlainText::FB_PlainTextTextCommon* fb)
{
    assert(fb != nullptr);

    common::initLanguageBundle(fb->price(), common_.price_);
}

} // namespace global
} // namespace game
