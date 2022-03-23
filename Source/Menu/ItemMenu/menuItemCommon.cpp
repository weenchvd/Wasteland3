
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"menuItemCommon.hpp"
#include<assert.h>
#include<sstream>

namespace game {
namespace menu {

using namespace std;

void printDamageEffect(
    std::ostream& os,
    const Indent indent,
    const object::DamageReference& reference,
    const bool isPositiveEffect)
{
    const auto sp  { ' ' };
    const auto p   { '%' };
    const auto& def{ object::Damage::damageReferenceContainer().damageReferenceDefault() };
    const auto& text{ object::Damage::damageText().common() };

    assert(def.isInitialized() == true);
    assert(reference.isInitialized() == true);
    if (isPositiveEffect == true) {
        if (reference.dmgRobots_ > def.dmgRobots_) {
            os << indent << text.damageVsRobots() << sp
                << common::getBonus(reference.dmgRobots_) << p << endl;
        }
        if (reference.dmgVehicles_ > def.dmgVehicles_) {
            os << indent << text.damageVsVehicles() << sp
                << common::getBonus(reference.dmgVehicles_) << p << endl;
        }
        if (reference.dmgHumans_ > def.dmgHumans_) {
            os << indent << text.damageVsHumans() << sp
                << common::getBonus(reference.dmgHumans_) << p << endl;
        }
        if (reference.dmgAnimals_ > def.dmgAnimals_) {
            os << indent << text.damageVsAnimals() << sp
                << common::getBonus(reference.dmgAnimals_) << p << endl;
        }
        if (reference.dmgMutants_ > def.dmgMutants_) {
            os << indent << text.damageVsMutants() << sp
                << common::getBonus(reference.dmgMutants_) << p << endl;
        }
    }
    else {
        if (reference.dmgRobots_ < def.dmgRobots_) {
            os << indent << text.damageVsRobots() << sp
                << common::getBonus(reference.dmgRobots_) << p << endl;
        }
        if (reference.dmgVehicles_ < def.dmgVehicles_) {
            os << indent << text.damageVsVehicles() << sp
                << common::getBonus(reference.dmgVehicles_) << p << endl;
        }
        if (reference.dmgHumans_ < def.dmgHumans_) {
            os << indent << text.damageVsHumans() << sp
                << common::getBonus(reference.dmgHumans_) << p << endl;
        }
        if (reference.dmgAnimals_ < def.dmgAnimals_) {
            os << indent << text.damageVsAnimals() << sp
                << common::getBonus(reference.dmgAnimals_) << p << endl;
        }
        if (reference.dmgMutants_ < def.dmgMutants_) {
            os << indent << text.damageVsMutants() << sp
                << common::getBonus(reference.dmgMutants_) << p << endl;
        }
    }
}

common::Text getDamageDescription(
    const Indent indent,
    const object::Damage::Type type)
{
    const auto& ref{ object::Damage::damageReferenceContainer().damageReference(type) };

    ostringstream oss;
    oss << showpos;
    printDamageEffect(oss, indent, ref, true);
    printDamageEffect(oss, indent, ref, false);
    return oss.str();
}

} // namespace menu
} // namespace game
