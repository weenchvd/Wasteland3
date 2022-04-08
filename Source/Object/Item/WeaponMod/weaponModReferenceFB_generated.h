// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WEAPONMODREFERENCEFB_FBWEAPONMOD_H_
#define FLATBUFFERS_GENERATED_WEAPONMODREFERENCEFB_FBWEAPONMOD_H_

#include "flatbuffers/flatbuffers.h"

#include "attributeTypeFB_generated.h"
#include "damageTypeFB_generated.h"
#include "weaponModTypeFB_generated.h"
#include "skillTypeFB_generated.h"
#include "languageBundleFB_generated.h"
#include "weaponModModelFB_generated.h"
#include "ammoTypeFB_generated.h"

namespace fbWeaponMod {

struct FB_SkillRequirement;

struct FB_AttributeRequirement;

struct FB_WeaponModRequirements;
struct FB_WeaponModRequirementsBuilder;

struct FB_WeaponModReference;
struct FB_WeaponModReferenceBuilder;

struct FB_WeaponModReferenceContainer;
struct FB_WeaponModReferenceContainerBuilder;

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

struct FB_WeaponModRequirements FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModRequirementsBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SKILL = 4,
    VT_ATTR = 6
  };
  const flatbuffers::Vector<const fbWeaponMod::FB_SkillRequirement *> *skill() const {
    return GetPointer<const flatbuffers::Vector<const fbWeaponMod::FB_SkillRequirement *> *>(VT_SKILL);
  }
  const flatbuffers::Vector<const fbWeaponMod::FB_AttributeRequirement *> *attr() const {
    return GetPointer<const flatbuffers::Vector<const fbWeaponMod::FB_AttributeRequirement *> *>(VT_ATTR);
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

struct FB_WeaponModRequirementsBuilder {
  typedef FB_WeaponModRequirements Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_skill(flatbuffers::Offset<flatbuffers::Vector<const fbWeaponMod::FB_SkillRequirement *>> skill) {
    fbb_.AddOffset(FB_WeaponModRequirements::VT_SKILL, skill);
  }
  void add_attr(flatbuffers::Offset<flatbuffers::Vector<const fbWeaponMod::FB_AttributeRequirement *>> attr) {
    fbb_.AddOffset(FB_WeaponModRequirements::VT_ATTR, attr);
  }
  explicit FB_WeaponModRequirementsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModRequirements> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModRequirements>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModRequirements> CreateFB_WeaponModRequirements(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<const fbWeaponMod::FB_SkillRequirement *>> skill = 0,
    flatbuffers::Offset<flatbuffers::Vector<const fbWeaponMod::FB_AttributeRequirement *>> attr = 0) {
  FB_WeaponModRequirementsBuilder builder_(_fbb);
  builder_.add_attr(attr);
  builder_.add_skill(skill);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponModRequirements> CreateFB_WeaponModRequirementsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<fbWeaponMod::FB_SkillRequirement> *skill = nullptr,
    const std::vector<fbWeaponMod::FB_AttributeRequirement> *attr = nullptr) {
  auto skill__ = skill ? _fbb.CreateVectorOfStructs<fbWeaponMod::FB_SkillRequirement>(*skill) : 0;
  auto attr__ = attr ? _fbb.CreateVectorOfStructs<fbWeaponMod::FB_AttributeRequirement>(*attr) : 0;
  return fbWeaponMod::CreateFB_WeaponModRequirements(
      _fbb,
      skill__,
      attr__);
}

struct FB_WeaponModReference FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModReferenceBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_WEAPON_MOD_MODEL = 4,
    VT_WEAPON_MOD_TYPE = 6,
    VT_WEAPON_MOD_REQUIREMENTS = 8,
    VT_NAME = 10,
    VT_DESCRIP = 12,
    VT_DMG_MIN = 14,
    VT_DMG_MAX = 16,
    VT_PRICE = 18,
    VT_RANGE_ATTACK = 20,
    VT_CAPACITY_AMMO = 22,
    VT_ANGLE_CONE = 24,
    VT_MULTIPLIER_CRIT_DMG = 26,
    VT_CHANCE_HIT = 28,
    VT_CHANCE_CRIT_DMG = 30,
    VT_BONUS_SNEAK_DMG = 32,
    VT_BONUS_NORMAL_DMG = 34,
    VT_BONUS_MELEE_DMG = 36,
    VT_BONUS_RANGE_DMG = 38,
    VT_ARMOR_PENETRATION = 40,
    VT_AP_PER_ATTACK = 42,
    VT_AP_PER_RELOAD = 44,
    VT_SHOTS_PER_ATTACK = 46,
    VT_AMMO_TYPE = 48,
    VT_DMG_TYPE = 50
  };
  fbWeaponMod::FB_WeaponModModel weapon_mod_model() const {
    return static_cast<fbWeaponMod::FB_WeaponModModel>(GetField<int16_t>(VT_WEAPON_MOD_MODEL, 0));
  }
  fbWeaponMod::FB_WeaponModType weapon_mod_type() const {
    return static_cast<fbWeaponMod::FB_WeaponModType>(GetField<int8_t>(VT_WEAPON_MOD_TYPE, 0));
  }
  const fbWeaponMod::FB_WeaponModRequirements *weapon_mod_requirements() const {
    return GetPointer<const fbWeaponMod::FB_WeaponModRequirements *>(VT_WEAPON_MOD_REQUIREMENTS);
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
  int16_t angle_cone() const {
    return GetField<int16_t>(VT_ANGLE_CONE, 0);
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
  int16_t bonus_sneak_dmg() const {
    return GetField<int16_t>(VT_BONUS_SNEAK_DMG, 0);
  }
  int16_t bonus_normal_dmg() const {
    return GetField<int16_t>(VT_BONUS_NORMAL_DMG, 0);
  }
  int16_t bonus_melee_dmg() const {
    return GetField<int16_t>(VT_BONUS_MELEE_DMG, 0);
  }
  int16_t bonus_range_dmg() const {
    return GetField<int16_t>(VT_BONUS_RANGE_DMG, 0);
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
           VerifyField<int16_t>(verifier, VT_WEAPON_MOD_MODEL) &&
           VerifyField<int8_t>(verifier, VT_WEAPON_MOD_TYPE) &&
           VerifyOffset(verifier, VT_WEAPON_MOD_REQUIREMENTS) &&
           verifier.VerifyTable(weapon_mod_requirements()) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyTable(name()) &&
           VerifyOffset(verifier, VT_DESCRIP) &&
           verifier.VerifyTable(descrip()) &&
           VerifyField<int16_t>(verifier, VT_DMG_MIN) &&
           VerifyField<int16_t>(verifier, VT_DMG_MAX) &&
           VerifyField<int16_t>(verifier, VT_PRICE) &&
           VerifyField<int16_t>(verifier, VT_RANGE_ATTACK) &&
           VerifyField<int16_t>(verifier, VT_CAPACITY_AMMO) &&
           VerifyField<int16_t>(verifier, VT_ANGLE_CONE) &&
           VerifyField<int16_t>(verifier, VT_MULTIPLIER_CRIT_DMG) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_HIT) &&
           VerifyField<int16_t>(verifier, VT_CHANCE_CRIT_DMG) &&
           VerifyField<int16_t>(verifier, VT_BONUS_SNEAK_DMG) &&
           VerifyField<int16_t>(verifier, VT_BONUS_NORMAL_DMG) &&
           VerifyField<int16_t>(verifier, VT_BONUS_MELEE_DMG) &&
           VerifyField<int16_t>(verifier, VT_BONUS_RANGE_DMG) &&
           VerifyField<int8_t>(verifier, VT_ARMOR_PENETRATION) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_ATTACK) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_RELOAD) &&
           VerifyField<int8_t>(verifier, VT_SHOTS_PER_ATTACK) &&
           VerifyField<int8_t>(verifier, VT_AMMO_TYPE) &&
           VerifyField<int8_t>(verifier, VT_DMG_TYPE) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModReferenceBuilder {
  typedef FB_WeaponModReference Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_weapon_mod_model(fbWeaponMod::FB_WeaponModModel weapon_mod_model) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_WEAPON_MOD_MODEL, static_cast<int16_t>(weapon_mod_model), 0);
  }
  void add_weapon_mod_type(fbWeaponMod::FB_WeaponModType weapon_mod_type) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_WEAPON_MOD_TYPE, static_cast<int8_t>(weapon_mod_type), 0);
  }
  void add_weapon_mod_requirements(flatbuffers::Offset<fbWeaponMod::FB_WeaponModRequirements> weapon_mod_requirements) {
    fbb_.AddOffset(FB_WeaponModReference::VT_WEAPON_MOD_REQUIREMENTS, weapon_mod_requirements);
  }
  void add_name(flatbuffers::Offset<fbCommon::FB_LanguageBundle> name) {
    fbb_.AddOffset(FB_WeaponModReference::VT_NAME, name);
  }
  void add_descrip(flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip) {
    fbb_.AddOffset(FB_WeaponModReference::VT_DESCRIP, descrip);
  }
  void add_dmg_min(int16_t dmg_min) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_DMG_MIN, dmg_min, 0);
  }
  void add_dmg_max(int16_t dmg_max) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_DMG_MAX, dmg_max, 0);
  }
  void add_price(int16_t price) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_PRICE, price, 0);
  }
  void add_range_attack(int16_t range_attack) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_RANGE_ATTACK, range_attack, 0);
  }
  void add_capacity_ammo(int16_t capacity_ammo) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_CAPACITY_AMMO, capacity_ammo, 0);
  }
  void add_angle_cone(int16_t angle_cone) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_ANGLE_CONE, angle_cone, 0);
  }
  void add_multiplier_crit_dmg(int16_t multiplier_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_MULTIPLIER_CRIT_DMG, multiplier_crit_dmg, 0);
  }
  void add_chance_hit(int16_t chance_hit) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_CHANCE_HIT, chance_hit, 0);
  }
  void add_chance_crit_dmg(int16_t chance_crit_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_CHANCE_CRIT_DMG, chance_crit_dmg, 0);
  }
  void add_bonus_sneak_dmg(int16_t bonus_sneak_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_BONUS_SNEAK_DMG, bonus_sneak_dmg, 0);
  }
  void add_bonus_normal_dmg(int16_t bonus_normal_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_BONUS_NORMAL_DMG, bonus_normal_dmg, 0);
  }
  void add_bonus_melee_dmg(int16_t bonus_melee_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_BONUS_MELEE_DMG, bonus_melee_dmg, 0);
  }
  void add_bonus_range_dmg(int16_t bonus_range_dmg) {
    fbb_.AddElement<int16_t>(FB_WeaponModReference::VT_BONUS_RANGE_DMG, bonus_range_dmg, 0);
  }
  void add_armor_penetration(int8_t armor_penetration) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_ARMOR_PENETRATION, armor_penetration, 0);
  }
  void add_ap_per_attack(int8_t ap_per_attack) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_AP_PER_ATTACK, ap_per_attack, 0);
  }
  void add_ap_per_reload(int8_t ap_per_reload) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_AP_PER_RELOAD, ap_per_reload, 0);
  }
  void add_shots_per_attack(int8_t shots_per_attack) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_SHOTS_PER_ATTACK, shots_per_attack, 0);
  }
  void add_ammo_type(fbAmmo::FB_AmmoType ammo_type) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_AMMO_TYPE, static_cast<int8_t>(ammo_type), 0);
  }
  void add_dmg_type(fbDamage::FB_DamageType dmg_type) {
    fbb_.AddElement<int8_t>(FB_WeaponModReference::VT_DMG_TYPE, static_cast<int8_t>(dmg_type), 0);
  }
  explicit FB_WeaponModReferenceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModReference> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModReference>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModReference> CreateFB_WeaponModReference(
    flatbuffers::FlatBufferBuilder &_fbb,
    fbWeaponMod::FB_WeaponModModel weapon_mod_model = fbWeaponMod::FB_WeaponModModel_INVALID,
    fbWeaponMod::FB_WeaponModType weapon_mod_type = fbWeaponMod::FB_WeaponModType_INVALID,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModRequirements> weapon_mod_requirements = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> name = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip = 0,
    int16_t dmg_min = 0,
    int16_t dmg_max = 0,
    int16_t price = 0,
    int16_t range_attack = 0,
    int16_t capacity_ammo = 0,
    int16_t angle_cone = 0,
    int16_t multiplier_crit_dmg = 0,
    int16_t chance_hit = 0,
    int16_t chance_crit_dmg = 0,
    int16_t bonus_sneak_dmg = 0,
    int16_t bonus_normal_dmg = 0,
    int16_t bonus_melee_dmg = 0,
    int16_t bonus_range_dmg = 0,
    int8_t armor_penetration = 0,
    int8_t ap_per_attack = 0,
    int8_t ap_per_reload = 0,
    int8_t shots_per_attack = 0,
    fbAmmo::FB_AmmoType ammo_type = fbAmmo::FB_AmmoType_INVALID,
    fbDamage::FB_DamageType dmg_type = fbDamage::FB_DamageType_INVALID) {
  FB_WeaponModReferenceBuilder builder_(_fbb);
  builder_.add_descrip(descrip);
  builder_.add_name(name);
  builder_.add_weapon_mod_requirements(weapon_mod_requirements);
  builder_.add_bonus_range_dmg(bonus_range_dmg);
  builder_.add_bonus_melee_dmg(bonus_melee_dmg);
  builder_.add_bonus_normal_dmg(bonus_normal_dmg);
  builder_.add_bonus_sneak_dmg(bonus_sneak_dmg);
  builder_.add_chance_crit_dmg(chance_crit_dmg);
  builder_.add_chance_hit(chance_hit);
  builder_.add_multiplier_crit_dmg(multiplier_crit_dmg);
  builder_.add_angle_cone(angle_cone);
  builder_.add_capacity_ammo(capacity_ammo);
  builder_.add_range_attack(range_attack);
  builder_.add_price(price);
  builder_.add_dmg_max(dmg_max);
  builder_.add_dmg_min(dmg_min);
  builder_.add_weapon_mod_model(weapon_mod_model);
  builder_.add_dmg_type(dmg_type);
  builder_.add_ammo_type(ammo_type);
  builder_.add_shots_per_attack(shots_per_attack);
  builder_.add_ap_per_reload(ap_per_reload);
  builder_.add_ap_per_attack(ap_per_attack);
  builder_.add_armor_penetration(armor_penetration);
  builder_.add_weapon_mod_type(weapon_mod_type);
  return builder_.Finish();
}

struct FB_WeaponModReferenceContainer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModReferenceContainerBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_REFS = 4,
    VT_REF_DEFAULT = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>> *refs() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>> *>(VT_REFS);
  }
  const fbWeaponMod::FB_WeaponModReference *ref_default() const {
    return GetPointer<const fbWeaponMod::FB_WeaponModReference *>(VT_REF_DEFAULT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_REFS) &&
           verifier.VerifyVector(refs()) &&
           verifier.VerifyVectorOfTables(refs()) &&
           VerifyOffset(verifier, VT_REF_DEFAULT) &&
           verifier.VerifyTable(ref_default()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModReferenceContainerBuilder {
  typedef FB_WeaponModReferenceContainer Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_refs(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>>> refs) {
    fbb_.AddOffset(FB_WeaponModReferenceContainer::VT_REFS, refs);
  }
  void add_ref_default(flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference> ref_default) {
    fbb_.AddOffset(FB_WeaponModReferenceContainer::VT_REF_DEFAULT, ref_default);
  }
  explicit FB_WeaponModReferenceContainerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModReferenceContainer> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModReferenceContainer>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModReferenceContainer> CreateFB_WeaponModReferenceContainer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>>> refs = 0,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference> ref_default = 0) {
  FB_WeaponModReferenceContainerBuilder builder_(_fbb);
  builder_.add_ref_default(ref_default);
  builder_.add_refs(refs);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponModReferenceContainer> CreateFB_WeaponModReferenceContainerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>> *refs = nullptr,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference> ref_default = 0) {
  auto refs__ = refs ? _fbb.CreateVector<flatbuffers::Offset<fbWeaponMod::FB_WeaponModReference>>(*refs) : 0;
  return fbWeaponMod::CreateFB_WeaponModReferenceContainer(
      _fbb,
      refs__,
      ref_default);
}

inline const fbWeaponMod::FB_WeaponModReferenceContainer *GetFB_WeaponModReferenceContainer(const void *buf) {
  return flatbuffers::GetRoot<fbWeaponMod::FB_WeaponModReferenceContainer>(buf);
}

inline const fbWeaponMod::FB_WeaponModReferenceContainer *GetSizePrefixedFB_WeaponModReferenceContainer(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbWeaponMod::FB_WeaponModReferenceContainer>(buf);
}

inline const char *FB_WeaponModReferenceContainerIdentifier() {
  return "WM_R";
}

inline bool FB_WeaponModReferenceContainerBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_WeaponModReferenceContainerIdentifier());
}

inline bool VerifyFB_WeaponModReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbWeaponMod::FB_WeaponModReferenceContainer>(FB_WeaponModReferenceContainerIdentifier());
}

inline bool VerifySizePrefixedFB_WeaponModReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbWeaponMod::FB_WeaponModReferenceContainer>(FB_WeaponModReferenceContainerIdentifier());
}

inline const char *FB_WeaponModReferenceContainerExtension() {
  return "bundle";
}

inline void FinishFB_WeaponModReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModReferenceContainer> root) {
  fbb.Finish(root, FB_WeaponModReferenceContainerIdentifier());
}

inline void FinishSizePrefixedFB_WeaponModReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModReferenceContainer> root) {
  fbb.FinishSizePrefixed(root, FB_WeaponModReferenceContainerIdentifier());
}

}  // namespace fbWeaponMod

#endif  // FLATBUFFERS_GENERATED_WEAPONMODREFERENCEFB_FBWEAPONMOD_H_
