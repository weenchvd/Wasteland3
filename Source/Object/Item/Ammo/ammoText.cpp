
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoPath.hpp"
#include"ammoText.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include<assert.h>
#include<memory>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, AmmoText::language> AmmoText::langObs_;

AmmoTextCommon AmmoText::common_;

underlying_type_t<AmmoText::language>       AmmoText::langIndex_   { 0 };
bool                                        AmmoText::initialized_ { false };

///************************************************************************************************

void AmmoText::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    assert(sizeLang_ > 0);
    unique_ptr<char[]> buffer{
        common::getFlatBuffer(AMMO_TEXT_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbAmmo::FB_AmmoText* fb{
        fbAmmo::GetFB_AmmoText(buffer.get())
    };
    assert(fb != nullptr);

    initCommon(fb->common());

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&AmmoText::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

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
