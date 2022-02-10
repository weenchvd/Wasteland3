
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include"weaponPath.hpp"
#include"weaponReference.hpp"
#include<assert.h>
#include<memory>
#include<type_traits>
#include<vector>

namespace game {
namespace object {

using namespace std;
using common::Text;
using global::Locator;

common::ObserverDLL<void, WeaponReferenceContainer::language>
    WeaponReferenceContainer::langObs_;

std::vector<WeaponReference>    WeaponReferenceContainer::refs_;
WeaponReference                 WeaponReferenceContainer::refMinimal_;
unsigned char                   WeaponReferenceContainer::langIndex_    { 0 };
bool                            WeaponReferenceContainer::initialized_  { false };


const WeaponReference::text& WeaponReference::name() const noexcept
{
    return name_[WeaponReferenceContainer::languageIndex()];
}

const WeaponReference::text& WeaponReference::descr() const noexcept
{
    return descrip_[WeaponReferenceContainer::languageIndex()];
}


void WeaponReferenceContainer::initialize()
{
    if (isInitialized()) return;

    unique_ptr<char[]> buffer{
        common::getFlatBuffer(WEAPON_REF_FB_BIN_FILE__NATIVE_REL_PATH)
    };

    const fbWeapon::FB_WeaponReferenceContainer* container =
        fbWeapon::GetFB_WeaponReferenceContainer(buffer.get());
    assert(container != nullptr);

    initContainer(container);

    assert(Locator::isInitialized());
    setLanguage(Locator::getOption().getLanguage());
    langObs_.getDelegate().bind<&WeaponReferenceContainer::setLanguage>();
    Locator::getOption().languageSubject().addObserver(&langObs_);

    initialized_        = true;
}

void WeaponReferenceContainer::setLanguage(WeaponReferenceContainer::language lang)
{
    assert(common::isValidEnum(lang));
    assert(common::toUnderlying(lang) >= 0 && common::toUnderlying(lang) < sizeLang_);
    langIndex_ = common::toUnderlying(lang);
}

void WeaponReferenceContainer::initContainer(const fbWeapon::FB_WeaponReferenceContainer* container)
{
    assert(common::toUnderlying(Weapon__Model::NUMBER_OF) >= 0);
    refs_.resize(common::toUnderlying(Weapon__Model::NUMBER_OF));
    auto v = container->refs();
    assert(refs_.size() == v->size());
    for (size_t i = 0; i < v->size(); ++i) {
        WeaponReference ref = initWeaponReference(v->Get(i));
        size_t pos = common::toUnderlying(ref.model_);
        refs_[pos] = move(ref);
    }
    refMinimal_ = initWeaponReference(container->ref_minimal());
}

WeaponReference WeaponReferenceContainer::initWeaponReference(
    const fbWeapon::FB_WeaponReference* reference)
{
    assert(reference != nullptr);
    WeaponReference ref;
    ref.model_  = toWeaponModel(reference->weapon_model()->str());
    ref.type_   = toWeaponType(reference->weapon_type()->str());

    auto modTypes = reference->weapon_mod_types();
    assert(ref.weaponModTypes_.size() == modTypes->size());
    for (int i = 0; i < ref.weaponModTypes_.size(); ++i) {
        ref.weaponModTypes_[i] = toWeaponModType(modTypes->Get(i)->str());
    }

    initLanguageBundle(reference->name(), ref.name_);
    initLanguageBundle(reference->descrip(), ref.descrip_);

    ref.dmgMin_         = { reference->dmg_min() };
    ref.dmgMax_         = { reference->dmg_max() };
    ref.price_          = { reference->price() };
    ref.rangeAttack_    = { reference->range_attack() };
    ref.capAmmo_        = { reference->capacity_ammo() };
    ref.mulCritDmg_     = { reference->multiplier_crit_dmg() };
    ref.chaHit_         = { reference->chance_hit() };
    ref.chaCritDmg_     = { reference->chance_crit_dmg() };
    ref.level_          = { reference->weapon_level() };
    ref.levSkill_       = { reference->level_of_skill() };
    ref.armorPen_       = { reference->armor_penetration() };
    ref.apAttack_       = { reference->ap_per_attack() };
    ref.apReload_       = { reference->ap_per_reload() };
    ref.shoPerAttack_   = { reference->shots_per_attack() };
    ref.tyAmmo_         = toAmmoType(reference->ammo_type()->str());
    ref.tyDmg_          = toDamageType(reference->dmg_type()->str());

    ref.initialized_    = true;

    return ref;
}

void WeaponReferenceContainer::initLanguageBundle(
    const fbWeapon::FB_LanguageBundle* bundle,
    std::array<WeaponReferenceContainer::text, sizeLang_>& target
)
{
    using lang = WeaponReferenceContainer::language; // TODO delete?
    using text = WeaponReferenceContainer::text; // TODO delete?
    target[common::toUnderlying(lang::EN)] = move(text{ bundle->en()->c_str() });
    target[common::toUnderlying(lang::RU)] = move(text{ bundle->ru()->c_str() });
}

} // namespace object
} // namespace game
