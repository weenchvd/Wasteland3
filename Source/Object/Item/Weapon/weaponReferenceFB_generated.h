// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WEAPONREFERENCEFB_FBWEAPON_H_
#define FLATBUFFERS_GENERATED_WEAPONREFERENCEFB_FBWEAPON_H_

#include "flatbuffers/flatbuffers.h"

#include "ammoTypeFB_generated.h"
#include "weaponTypeFB_generated.h"
#include "attributeTypeFB_generated.h"
#include "damageTypeFB_generated.h"
#include "weaponModTypeFB_generated.h"
#include "skillTypeFB_generated.h"
#include "languageBundleFB_generated.h"
#include "weaponModelFB_generated.h"

namespace fbWeapon {

struct FB_SkillRequirement;

struct FB_AttributeRequirement;

struct FB_WeaponRequirements;
struct FB_WeaponRequirementsBuilder;

struct FB_WeaponPenalties;
struct FB_WeaponPenaltiesBuilder;

struct FB_WeaponReference;
struct FB_WeaponReferenceBuilder;

struct FB_WeaponReferenceContainer;
struct FB_WeaponReferenceContainerBuilder;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) FB_SkillRequirement FLATBUFFERS_FINAL_CLASS {
 private:
  int8_t type_;
  int8_t level_;

 public:
  FB_SkillRequirement()
      : type_(0),
        level_(0) {
  }
  FB_SkillRequirement(fbSkill::FB_SkillType _type, int8_t _level)
      : type_(flatbuffers::EndianScalar(static_cast<int8_t>(_type))),
        level_(flatbuffers::EndianScalar(_level)) {
  }
  fbSkill::FB_SkillType type() const {
    return static_cast<fbSkill::FB_SkillType>(flatbuffers::EndianScalar(type_));
  }
  int8_t level() const {
    return flatbuffers::EndianScalar(level_);
  }
};
FLATBUFFERS_STRUCT_END(FB_SkillRequirement, 2);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) FB_AttributeRequirement FLATBUFFERS_FINAL_CLASS {
 private:
  int8_t type_;
  int8_t level_;

 public:
  FB_AttributeRequirement()
      : type_(0),
        level_(0) {
  }
  FB_AttributeRequirement(fbAttribute::FB_AttributeType _type, int8_t _level)
      : type_(flatbuffers::EndianScalar(static_cast<int8_t>(_type))),
        level_(flatbuffers::EndianScalar(_level)) {
  }
  fbAttribute::FB_AttributeType type() const {
    return static_cast<fbAttribute::FB_AttributeType>(flatbuffers::EndianScalar(type_));
  }
  int8_t level() const {
    return flatbuffers::EndianScalar(level_);
  }
};
FLATBUFFERS_STRUCT_END(FB_AttributeRequirement, 2);

struct FB_WeaponRequirements FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponRequirementsBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SKILL = 4,
    VT_ATTR = 6
  };
  const flatbuffers::Vector<const fbWeapon::FB_SkillRequirement *> *skill() const {
    return GetPointer<const flatbuffers::Vector<const fbWeapon::FB_SkillRequirement *> *>(VT_SKILL);
  }
  const flatbuffers::Vector<const fbWeapon::FB_AttributeRequirement *> *attr() const {
    return GetPointer<const flatbuffers::Vector<const fbWeapon::FB_AttributeRequirement *> *>(VT_ATTR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_SKILL) &&
           verifier.VerifyVector(skill()) &&
           VerifyOffset(verifier, VT_ATTR) &&
           verifier.VerifyVector(attr()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponRequirementsBuilder {
  typedef FB_WeaponRequirements Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_skill(flatbuffers::Offset<flatbuffers::Vector<const fbWeapon::FB_SkillRequirement *>> skill) {
    fbb_.AddOffset(FB_WeaponRequirements::VT_SKILL, skill);
  }
  void add_attr(flatbuffers::Offset<flatbuffers::Vector<const fbWeapon::FB_AttributeRequirement *>> attr) {
    fbb_.AddOffset(FB_WeaponRequirements::VT_ATTR, attr);
  }
  explicit FB_WeaponRequirementsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponRequirements> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponRequirements>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponRequirements> CreateFB_WeaponRequirements(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<const fbWeapon::FB_SkillRequirement *>> skill = 0,
    flatbuffers::Offset<flatbuffers::Vector<const fbWeapon::FB_AttributeRequirement *>> attr = 0) {
  FB_WeaponRequirementsBuilder builder_(_fbb);
  builder_.add_attr(attr);
  builder_.add_skill(skill);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponRequirements> CreateFB_WeaponRequirementsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<fbWeapon::FB_SkillRequirement> *skill = nullptr,
    const std::vector<fbWeapon::FB_AttributeRequirement> *attr = nullptr) {
  auto skill__ = skill ? _fbb.CreateVectorOfStructs<fbWeapon::FB_SkillRequirement>(*skill) : 0;
  auto attr__ = attr ? _fbb.CreateVectorOfStructs<fbWeapon::FB_AttributeRequirement>(*attr) : 0;
  return fbWeapon::CreateFB_WeaponRequirements(
      _fbb,
      skill__,
      attr__);
}

struct FB_WeaponPenalties FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponPenaltiesBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MULTIPLIER_CRIT_DMG = 4,
    VT_CHANCE_HIT = 6,
    VT_CHANCE_CRIT_DMG = 8,
    VT_STRIKE_RATE = 10
  };
  int16_t multiplier_crit_dmg() const {
    return GetField<int16_t>(VT_MULTIPLIER_CRIT_DMG, 0);
  }
  int16_t chance_hit() const {
    return GetField<int16_t>(VT_CHANCE_HIT, 0);
  }
  int16_t chance_crit_dmg() const {
    return GetField<int16_t>(VT_CHANCE_CRIT_DMG, 0);
  }
  int16_t strike_rate() const {
    return GetField<int16_t>(VT_STRIKE_RATE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_MULTIPLIER_CRIT_DMG) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_HIT) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_CRIT_DMG) &&
           VerifyField<int16_t>(verifier, VT_STRIKE_RATE) &&
           verifier.EndTable();
  }
};

struct FB_WeaponPenaltiesBuilder {
  typedef FB_WeaponPenalties Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_multiplier_crit_dmg(int16_t multiplier_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponPenalties::VT_MULTIPLIER_CRIT_DMG, multiplier_crit_dmg, 0);
  }
  void add_chance_hit(int16_t chance_hit) {
    fbb_.AddElement<int16_t>(FB_WeaponPenalties::VT_CHANCE_HIT, chance_hit, 0);
  }
  void add_chance_crit_dmg(int16_t chance_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponPenalties::VT_CHANCE_CRIT_DMG, chance_crit_dmg, 0);
  }
  void add_strike_rate(int16_t strike_rate) {
    fbb_.AddElement<int16_t>(FB_WeaponPenalties::VT_STRIKE_RATE, strike_rate, 0);
  }
  explicit FB_WeaponPenaltiesBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponPenalties> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponPenalties>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponPenalties> CreateFB_WeaponPenalties(
    flatbuffers::FlatBufferBuilder &_fbb,
    int16_t multiplier_crit_dmg = 0,
    int16_t chance_hit = 0,
    int16_t chance_crit_dmg = 0,
    int16_t strike_rate = 0) {
  FB_WeaponPenaltiesBuilder builder_(_fbb);
  builder_.add_strike_rate(strike_rate);
  builder_.add_chance_crit_dmg(chance_crit_dmg);
  builder_.add_chance_hit(chance_hit);
  builder_.add_multiplier_crit_dmg(multiplier_crit_dmg);
  return builder_.Finish();
}

struct FB_WeaponReference FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponReferenceBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_WEAPON_MODEL = 4,
    VT_WEAPON_TYPE = 6,
    VT_WEAPON_MOD_TYPES = 8,
    VT_WEAPON_REQUIREMENTS = 10,
    VT_WEAPON_PENALTIES = 12,
    VT_NAME = 14,
    VT_DESCRIP = 16,
    VT_DMG_MIN = 18,
    VT_DMG_MAX = 20,
    VT_PRICE = 22,
    VT_RANGE_ATTACK = 24,
    VT_CAPACITY_AMMO = 26,
    VT_MULTIPLIER_CRIT_DMG = 28,
    VT_CHANCE_HIT = 30,
    VT_CHANCE_CRIT_DMG = 32,
    VT_WEAPON_LEVEL = 34,
    VT_ARMOR_PENETRATION = 36,
    VT_AP_PER_ATTACK = 38,
    VT_AP_PER_RELOAD = 40,
    VT_SHOTS_PER_ATTACK = 42,
    VT_AMMO_TYPE = 44,
    VT_DMG_TYPE = 46
  };
  fbWeapon::FB_WeaponModel weapon_model() const {
    return static_cast<fbWeapon::FB_WeaponModel>(GetField<int16_t>(VT_WEAPON_MODEL, 0));
  }
  fbWeapon::FB_WeaponType weapon_type() const {
    return static_cast<fbWeapon::FB_WeaponType>(GetField<int8_t>(VT_WEAPON_TYPE, 0));
  }
  const flatbuffers::Vector<int8_t> *weapon_mod_types() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_WEAPON_MOD_TYPES);
  }
  const fbWeapon::FB_WeaponRequirements *weapon_requirements() const {
    return GetPointer<const fbWeapon::FB_WeaponRequirements *>(VT_WEAPON_REQUIREMENTS);
  }
  const fbWeapon::FB_WeaponPenalties *weapon_penalties() const {
    return GetPointer<const fbWeapon::FB_WeaponPenalties *>(VT_WEAPON_PENALTIES);
  }
  const fbCommon::FB_LanguageBundle *name() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_NAME);
  }
  const fbCommon::FB_LanguageBundle *descrip() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_DESCRIP);
  }
  int16_t dmg_min() const {
    return GetField<int16_t>(VT_DMG_MIN, 0);
  }
  int16_t dmg_max() const {
    return GetField<int16_t>(VT_DMG_MAX, 0);
  }
  int16_t price() const {
    return GetField<int16_t>(VT_PRICE, 0);
  }
  int16_t range_attack() const {
    return GetField<int16_t>(VT_RANGE_ATTACK, 0);
  }
  int16_t capacity_ammo() const {
    return GetField<int16_t>(VT_CAPACITY_AMMO, 0);
  }
  int16_t multiplier_crit_dmg() const {
    return GetField<int16_t>(VT_MULTIPLIER_CRIT_DMG, 0);
  }
  int16_t chance_hit() const {
    return GetField<int16_t>(VT_CHANCE_HIT, 0);
  }
  int16_t chance_crit_dmg() const {
    return GetField<int16_t>(VT_CHANCE_CRIT_DMG, 0);
  }
  int8_t weapon_level() const {
    return GetField<int8_t>(VT_WEAPON_LEVEL, 0);
  }
  int8_t armor_penetration() const {
    return GetField<int8_t>(VT_ARMOR_PENETRATION, 0);
  }
  int8_t ap_per_attack() const {
    return GetField<int8_t>(VT_AP_PER_ATTACK, 0);
  }
  int8_t ap_per_reload() const {
    return GetField<int8_t>(VT_AP_PER_RELOAD, 0);
  }
  int8_t shots_per_attack() const {
    return GetField<int8_t>(VT_SHOTS_PER_ATTACK, 0);
  }
  fbAmmo::FB_AmmoType ammo_type() const {
    return static_cast<fbAmmo::FB_AmmoType>(GetField<int8_t>(VT_AMMO_TYPE, 0));
  }
  fbDamage::FB_DamageType dmg_type() const {
    return static_cast<fbDamage::FB_DamageType>(GetField<int8_t>(VT_DMG_TYPE, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_WEAPON_MODEL) &&
           VerifyField<int8_t>(verifier, VT_WEAPON_TYPE) &&
           VerifyOffset(verifier, VT_WEAPON_MOD_TYPES) &&
           verifier.VerifyVector(weapon_mod_types()) &&
           VerifyOffset(verifier, VT_WEAPON_REQUIREMENTS) &&
           verifier.VerifyTable(weapon_requirements()) &&
           VerifyOffset(verifier, VT_WEAPON_PENALTIES) &&
           verifier.VerifyTable(weapon_penalties()) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyTable(name()) &&
           VerifyOffset(verifier, VT_DESCRIP) &&
           verifier.VerifyTable(descrip()) &&
           VerifyField<int16_t>(verifier, VT_DMG_MIN) &&
           VerifyField<int16_t>(verifier, VT_DMG_MAX) &&
           VerifyField<int16_t>(verifier, VT_PRICE) &&
           VerifyField<int16_t>(verifier, VT_RANGE_ATTACK) &&
           VerifyField<int16_t>(verifier, VT_CAPACITY_AMMO) &&
           VerifyField<int16_t>(verifier, VT_MULTIPLIER_CRIT_DMG) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_HIT) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_CRIT_DMG) &&
           VerifyField<int8_t>(verifier, VT_WEAPON_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_ARMOR_PENETRATION) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_ATTACK) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_RELOAD) &&
           VerifyField<int8_t>(verifier, VT_SHOTS_PER_ATTACK) &&
           VerifyField<int8_t>(verifier, VT_AMMO_TYPE) &&
           VerifyField<int8_t>(verifier, VT_DMG_TYPE) &&
           verifier.EndTable();
  }
};

struct FB_WeaponReferenceBuilder {
  typedef FB_WeaponReference Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_weapon_model(fbWeapon::FB_WeaponModel weapon_model) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_WEAPON_MODEL, static_cast<int16_t>(weapon_model), 0);
  }
  void add_weapon_type(fbWeapon::FB_WeaponType weapon_type) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_WEAPON_TYPE, static_cast<int8_t>(weapon_type), 0);
  }
  void add_weapon_mod_types(flatbuffers::Offset<flatbuffers::Vector<int8_t>> weapon_mod_types) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_MOD_TYPES, weapon_mod_types);
  }
  void add_weapon_requirements(flatbuffers::Offset<fbWeapon::FB_WeaponRequirements> weapon_requirements) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_REQUIREMENTS, weapon_requirements);
  }
  void add_weapon_penalties(flatbuffers::Offset<fbWeapon::FB_WeaponPenalties> weapon_penalties) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_PENALTIES, weapon_penalties);
  }
  void add_name(flatbuffers::Offset<fbCommon::FB_LanguageBundle> name) {
    fbb_.AddOffset(FB_WeaponReference::VT_NAME, name);
  }
  void add_descrip(flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip) {
    fbb_.AddOffset(FB_WeaponReference::VT_DESCRIP, descrip);
  }
  void add_dmg_min(int16_t dmg_min) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_DMG_MIN, dmg_min, 0);
  }
  void add_dmg_max(int16_t dmg_max) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_DMG_MAX, dmg_max, 0);
  }
  void add_price(int16_t price) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_PRICE, price, 0);
  }
  void add_range_attack(int16_t range_attack) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_RANGE_ATTACK, range_attack, 0);
  }
  void add_capacity_ammo(int16_t capacity_ammo) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_CAPACITY_AMMO, capacity_ammo, 0);
  }
  void add_multiplier_crit_dmg(int16_t multiplier_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_MULTIPLIER_CRIT_DMG, multiplier_crit_dmg, 0);
  }
  void add_chance_hit(int16_t chance_hit) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_CHANCE_HIT, chance_hit, 0);
  }
  void add_chance_crit_dmg(int16_t chance_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponReference::VT_CHANCE_CRIT_DMG, chance_crit_dmg, 0);
  }
  void add_weapon_level(int8_t weapon_level) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_WEAPON_LEVEL, weapon_level, 0);
  }
  void add_armor_penetration(int8_t armor_penetration) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_ARMOR_PENETRATION, armor_penetration, 0);
  }
  void add_ap_per_attack(int8_t ap_per_attack) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_AP_PER_ATTACK, ap_per_attack, 0);
  }
  void add_ap_per_reload(int8_t ap_per_reload) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_AP_PER_RELOAD, ap_per_reload, 0);
  }
  void add_shots_per_attack(int8_t shots_per_attack) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_SHOTS_PER_ATTACK, shots_per_attack, 0);
  }
  void add_ammo_type(fbAmmo::FB_AmmoType ammo_type) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_AMMO_TYPE, static_cast<int8_t>(ammo_type), 0);
  }
  void add_dmg_type(fbDamage::FB_DamageType dmg_type) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_DMG_TYPE, static_cast<int8_t>(dmg_type), 0);
  }
  explicit FB_WeaponReferenceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponReference> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponReference>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponReference> CreateFB_WeaponReference(
    flatbuffers::FlatBufferBuilder &_fbb,
    fbWeapon::FB_WeaponModel weapon_model = fbWeapon::FB_WeaponModel_INVALID,
    fbWeapon::FB_WeaponType weapon_type = fbWeapon::FB_WeaponType_INVALID,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> weapon_mod_types = 0,
    flatbuffers::Offset<fbWeapon::FB_WeaponRequirements> weapon_requirements = 0,
    flatbuffers::Offset<fbWeapon::FB_WeaponPenalties> weapon_penalties = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> name = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip = 0,
    int16_t dmg_min = 0,
    int16_t dmg_max = 0,
    int16_t price = 0,
    int16_t range_attack = 0,
    int16_t capacity_ammo = 0,
    int16_t multiplier_crit_dmg = 0,
    int16_t chance_hit = 0,
    int16_t chance_crit_dmg = 0,
    int8_t weapon_level = 0,
    int8_t armor_penetration = 0,
    int8_t ap_per_attack = 0,
    int8_t ap_per_reload = 0,
    int8_t shots_per_attack = 0,
    fbAmmo::FB_AmmoType ammo_type = fbAmmo::FB_AmmoType_INVALID,
    fbDamage::FB_DamageType dmg_type = fbDamage::FB_DamageType_INVALID) {
  FB_WeaponReferenceBuilder builder_(_fbb);
  builder_.add_descrip(descrip);
  builder_.add_name(name);
  builder_.add_weapon_penalties(weapon_penalties);
  builder_.add_weapon_requirements(weapon_requirements);
  builder_.add_weapon_mod_types(weapon_mod_types);
  builder_.add_chance_crit_dmg(chance_crit_dmg);
  builder_.add_chance_hit(chance_hit);
  builder_.add_multiplier_crit_dmg(multiplier_crit_dmg);
  builder_.add_capacity_ammo(capacity_ammo);
  builder_.add_range_attack(range_attack);
  builder_.add_price(price);
  builder_.add_dmg_max(dmg_max);
  builder_.add_dmg_min(dmg_min);
  builder_.add_weapon_model(weapon_model);
  builder_.add_dmg_type(dmg_type);
  builder_.add_ammo_type(ammo_type);
  builder_.add_shots_per_attack(shots_per_attack);
  builder_.add_ap_per_reload(ap_per_reload);
  builder_.add_ap_per_attack(ap_per_attack);
  builder_.add_armor_penetration(armor_penetration);
  builder_.add_weapon_level(weapon_level);
  builder_.add_weapon_type(weapon_type);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponReference> CreateFB_WeaponReferenceDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    fbWeapon::FB_WeaponModel weapon_model = fbWeapon::FB_WeaponModel_INVALID,
    fbWeapon::FB_WeaponType weapon_type = fbWeapon::FB_WeaponType_INVALID,
    const std::vector<int8_t> *weapon_mod_types = nullptr,
    flatbuffers::Offset<fbWeapon::FB_WeaponRequirements> weapon_requirements = 0,
    flatbuffers::Offset<fbWeapon::FB_WeaponPenalties> weapon_penalties = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> name = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip = 0,
    int16_t dmg_min = 0,
    int16_t dmg_max = 0,
    int16_t price = 0,
    int16_t range_attack = 0,
    int16_t capacity_ammo = 0,
    int16_t multiplier_crit_dmg = 0,
    int16_t chance_hit = 0,
    int16_t chance_crit_dmg = 0,
    int8_t weapon_level = 0,
    int8_t armor_penetration = 0,
    int8_t ap_per_attack = 0,
    int8_t ap_per_reload = 0,
    int8_t shots_per_attack = 0,
    fbAmmo::FB_AmmoType ammo_type = fbAmmo::FB_AmmoType_INVALID,
    fbDamage::FB_DamageType dmg_type = fbDamage::FB_DamageType_INVALID) {
  auto weapon_mod_types__ = weapon_mod_types ? _fbb.CreateVector<int8_t>(*weapon_mod_types) : 0;
  return fbWeapon::CreateFB_WeaponReference(
      _fbb,
      weapon_model,
      weapon_type,
      weapon_mod_types__,
      weapon_requirements,
      weapon_penalties,
      name,
      descrip,
      dmg_min,
      dmg_max,
      price,
      range_attack,
      capacity_ammo,
      multiplier_crit_dmg,
      chance_hit,
      chance_crit_dmg,
      weapon_level,
      armor_penetration,
      ap_per_attack,
      ap_per_reload,
      shots_per_attack,
      ammo_type,
      dmg_type);
}

struct FB_WeaponReferenceContainer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponReferenceContainerBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_REFS = 4,
    VT_REF_MINIMAL = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>> *refs() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>> *>(VT_REFS);
  }
  const fbWeapon::FB_WeaponReference *ref_minimal() const {
    return GetPointer<const fbWeapon::FB_WeaponReference *>(VT_REF_MINIMAL);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_REFS) &&
           verifier.VerifyVector(refs()) &&
           verifier.VerifyVectorOfTables(refs()) &&
           VerifyOffset(verifier, VT_REF_MINIMAL) &&
           verifier.VerifyTable(ref_minimal()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponReferenceContainerBuilder {
  typedef FB_WeaponReferenceContainer Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_refs(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>>> refs) {
    fbb_.AddOffset(FB_WeaponReferenceContainer::VT_REFS, refs);
  }
  void add_ref_minimal(flatbuffers::Offset<fbWeapon::FB_WeaponReference> ref_minimal) {
    fbb_.AddOffset(FB_WeaponReferenceContainer::VT_REF_MINIMAL, ref_minimal);
  }
  explicit FB_WeaponReferenceContainerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponReferenceContainer> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponReferenceContainer>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponReferenceContainer> CreateFB_WeaponReferenceContainer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>>> refs = 0,
    flatbuffers::Offset<fbWeapon::FB_WeaponReference> ref_minimal = 0) {
  FB_WeaponReferenceContainerBuilder builder_(_fbb);
  builder_.add_ref_minimal(ref_minimal);
  builder_.add_refs(refs);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponReferenceContainer> CreateFB_WeaponReferenceContainerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>> *refs = nullptr,
    flatbuffers::Offset<fbWeapon::FB_WeaponReference> ref_minimal = 0) {
  auto refs__ = refs ? _fbb.CreateVector<flatbuffers::Offset<fbWeapon::FB_WeaponReference>>(*refs) : 0;
  return fbWeapon::CreateFB_WeaponReferenceContainer(
      _fbb,
      refs__,
      ref_minimal);
}

inline const fbWeapon::FB_WeaponReferenceContainer *GetFB_WeaponReferenceContainer(const void *buf) {
  return flatbuffers::GetRoot<fbWeapon::FB_WeaponReferenceContainer>(buf);
}

inline const fbWeapon::FB_WeaponReferenceContainer *GetSizePrefixedFB_WeaponReferenceContainer(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbWeapon::FB_WeaponReferenceContainer>(buf);
}

inline const char *FB_WeaponReferenceContainerIdentifier() {
  return "WPNR";
}

inline bool FB_WeaponReferenceContainerBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_WeaponReferenceContainerIdentifier());
}

inline bool VerifyFB_WeaponReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbWeapon::FB_WeaponReferenceContainer>(FB_WeaponReferenceContainerIdentifier());
}

inline bool VerifySizePrefixedFB_WeaponReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbWeapon::FB_WeaponReferenceContainer>(FB_WeaponReferenceContainerIdentifier());
}

inline const char *FB_WeaponReferenceContainerExtension() {
  return "bundle";
}

inline void FinishFB_WeaponReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeapon::FB_WeaponReferenceContainer> root) {
  fbb.Finish(root, FB_WeaponReferenceContainerIdentifier());
}

inline void FinishSizePrefixedFB_WeaponReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeapon::FB_WeaponReferenceContainer> root) {
  fbb.FinishSizePrefixed(root, FB_WeaponReferenceContainerIdentifier());
}

}  // namespace fbWeapon

#endif  // FLATBUFFERS_GENERATED_WEAPONREFERENCEFB_FBWEAPON_H_
