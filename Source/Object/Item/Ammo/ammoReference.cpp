
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"ammoPath.hpp"
#include"ammoReference.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersLanguageBundle.hpp"
#include"locator.hpp"
#include<memory>
#include<type_traits>

namespace game {
namespace object {

using namespace std;

common::ObserverDLL<void, AmmoReferenceContainer::language>
                            AmmoReferenceContainer::langObs_;

vector<AmmoReference>       AmmoReferenceContainer::refs_;

underlying_type_t<AmmoReferenceContainer::language>
                            AmmoReferenceContainer::langIndex_  { 0 };
bool                        AmmoReferenceContainer::initialized_{ false };

///************************************************************************************************

AmmoReference::AmmoReference() noexcept
    :
    type_           { Ammo__Type::INVALID },
    price_          { 0 },
    name_           {},
    descrip_        {},
    initialized_    { false }
{}

///************************************************************************************************

void AmmoReferenceContainer::initialize()
{
    using global::Locator;

    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(AMMO_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };
    const fbAmmo::FB_AmmoReferenceContainer* fb{
        fbAmmo::GetFB_AmmoReferenceContainer(buffer.get())
    };

    initContainer(fb);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&AmmoReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_ = true;
}

void AmmoReferenceContainer::initContainer(
    const fbAmmo::FB_AmmoReferenceContainer* fb)
{
    assert(fb != nullptr);
    refs_.resize(common::numberOf<Ammo__Type>());
    auto v{ fb->refs() };
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        AmmoReference ref{ initAmmoReference(v->Get(i)) };
        auto pos{ common::toUnderlying(ref.type_) };
        refs_[pos] = move(ref);
    }
}

AmmoReference AmmoReferenceContainer::initAmmoReference(
    const fbAmmo::FB_AmmoReference* fb)
{
    assert(fb != nullptr);
    AmmoReference ref;

    ref.type_ = toAmmoType(fb->ammo_type());
    assert(common::isValidEnum(ref.type_));

    common::initLanguageBundle(fb->name(), ref.name_);
    common::initLanguageBundle(fb->descrip(), ref.descrip_);

    ref.price_          = { fb->price() };

    ref.initialized_    = true;

    return ref;
}

} // namespace object
} // namespace game
