// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WEAPONREFERENCEFB_FBWEAPON_H_
#define FLATBUFFERS_GENERATED_WEAPONREFERENCEFB_FBWEAPON_H_

#include "flatbuffers/flatbuffers.h"

#include "languageBundleFB_generated.h"

namespace fbWeapon {

struct FB_WeaponReference;
struct FB_WeaponReferenceBuilder;

struct FB_WeaponReferenceContainer;
struct FB_WeaponReferenceContainerBuilder;

struct FB_WeaponReference FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponReferenceBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_WEAPON_MODEL = 4,
    VT_WEAPON_TYPE = 6,
    VT_WEAPON_MOD_TYPES = 8,
    VT_NAME = 10,
    VT_DESCRIP = 12,
    VT_DMG_MIN = 14,
    VT_DMG_MAX = 16,
    VT_PRICE = 18,
    VT_RANGE_ATTACK = 20,
    VT_CAPACITY_AMMO = 22,
    VT_MULTIPLIER_CRIT_DMG = 24,
    VT_CHANCE_HIT = 26,
    VT_CHANCE_CRIT_DMG = 28,
    VT_WEAPON_LEVEL = 30,
    VT_LEVEL_OF_SKILL = 32,
    VT_ARMOR_PENETRATION = 34,
    VT_AP_PER_ATTACK = 36,
    VT_AP_PER_RELOAD = 38,
    VT_SHOTS_PER_ATTACK = 40,
    VT_AMMO_TYPE = 42,
    VT_DMG_TYPE = 44
  };
  const flatbuffers::String *weapon_model() const {
    return GetPointer<const flatbuffers::String *>(VT_WEAPON_MODEL);
  }
  const flatbuffers::String *weapon_type() const {
    return GetPointer<const flatbuffers::String *>(VT_WEAPON_TYPE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *weapon_mod_types() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_WEAPON_MOD_TYPES);
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
  int8_t level_of_skill() const {
    return GetField<int8_t>(VT_LEVEL_OF_SKILL, 0);
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
  const flatbuffers::String *ammo_type() const {
    return GetPointer<const flatbuffers::String *>(VT_AMMO_TYPE);
  }
  const flatbuffers::String *dmg_type() const {
    return GetPointer<const flatbuffers::String *>(VT_DMG_TYPE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_WEAPON_MODEL) &&
           verifier.VerifyString(weapon_model()) &&
           VerifyOffset(verifier, VT_WEAPON_TYPE) &&
           verifier.VerifyString(weapon_type()) &&
           VerifyOffset(verifier, VT_WEAPON_MOD_TYPES) &&
           verifier.VerifyVector(weapon_mod_types()) &&
           verifier.VerifyVectorOfStrings(weapon_mod_types()) &&
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
           VerifyField<int8_t>(verifier, VT_LEVEL_OF_SKILL) &&
           VerifyField<int8_t>(verifier, VT_ARMOR_PENETRATION) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_ATTACK) &&
           VerifyField<int8_t>(verifier, VT_AP_PER_RELOAD) &&
           VerifyField<int8_t>(verifier, VT_SHOTS_PER_ATTACK) &&
           VerifyOffset(verifier, VT_AMMO_TYPE) &&
           verifier.VerifyString(ammo_type()) &&
           VerifyOffset(verifier, VT_DMG_TYPE) &&
           verifier.VerifyString(dmg_type()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponReferenceBuilder {
  typedef FB_WeaponReference Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_weapon_model(flatbuffers::Offset<flatbuffers::String> weapon_model) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_MODEL, weapon_model);
  }
  void add_weapon_type(flatbuffers::Offset<flatbuffers::String> weapon_type) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_TYPE, weapon_type);
  }
  void add_weapon_mod_types(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> weapon_mod_types) {
    fbb_.AddOffset(FB_WeaponReference::VT_WEAPON_MOD_TYPES, weapon_mod_types);
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
  void add_level_of_skill(int8_t level_of_skill) {
    fbb_.AddElement<int8_t>(FB_WeaponReference::VT_LEVEL_OF_SKILL, level_of_skill, 0);
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
  void add_ammo_type(flatbuffers::Offset<flatbuffers::String> ammo_type) {
    fbb_.AddOffset(FB_WeaponReference::VT_AMMO_TYPE, ammo_type);
  }
  void add_dmg_type(flatbuffers::Offset<flatbuffers::String> dmg_type) {
    fbb_.AddOffset(FB_WeaponReference::VT_DMG_TYPE, dmg_type);
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
    flatbuffers::Offset<flatbuffers::String> weapon_model = 0,
    flatbuffers::Offset<flatbuffers::String> weapon_type = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> weapon_mod_types = 0,
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
    int8_t level_of_skill = 0,
    int8_t armor_penetration = 0,
    int8_t ap_per_attack = 0,
    int8_t ap_per_reload = 0,
    int8_t shots_per_attack = 0,
    flatbuffers::Offset<flatbuffers::String> ammo_type = 0,
    flatbuffers::Offset<flatbuffers::String> dmg_type = 0) {
  FB_WeaponReferenceBuilder builder_(_fbb);
  builder_.add_dmg_type(dmg_type);
  builder_.add_ammo_type(ammo_type);
  builder_.add_descrip(descrip);
  builder_.add_name(name);
  builder_.add_weapon_mod_types(weapon_mod_types);
  builder_.add_weapon_type(weapon_type);
  builder_.add_weapon_model(weapon_model);
  builder_.add_chance_crit_dmg(chance_crit_dmg);
  builder_.add_chance_hit(chance_hit);
  builder_.add_multiplier_crit_dmg(multiplier_crit_dmg);
  builder_.add_capacity_ammo(capacity_ammo);
  builder_.add_range_attack(range_attack);
  builder_.add_price(price);
  builder_.add_dmg_max(dmg_max);
  builder_.add_dmg_min(dmg_min);
  builder_.add_shots_per_attack(shots_per_attack);
  builder_.add_ap_per_reload(ap_per_reload);
  builder_.add_ap_per_attack(ap_per_attack);
  builder_.add_armor_penetration(armor_penetration);
  builder_.add_level_of_skill(level_of_skill);
  builder_.add_weapon_level(weapon_level);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_WeaponReference> CreateFB_WeaponReferenceDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *weapon_model = nullptr,
    const char *weapon_type = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *weapon_mod_types = nullptr,
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
    int8_t level_of_skill = 0,
    int8_t armor_penetration = 0,
    int8_t ap_per_attack = 0,
    int8_t ap_per_reload = 0,
    int8_t shots_per_attack = 0,
    const char *ammo_type = nullptr,
    const char *dmg_type = nullptr) {
  auto weapon_model__ = weapon_model ? _fbb.CreateString(weapon_model) : 0;
  auto weapon_type__ = weapon_type ? _fbb.CreateString(weapon_type) : 0;
  auto weapon_mod_types__ = weapon_mod_types ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*weapon_mod_types) : 0;
  auto ammo_type__ = ammo_type ? _fbb.CreateString(ammo_type) : 0;
  auto dmg_type__ = dmg_type ? _fbb.CreateString(dmg_type) : 0;
  return fbWeapon::CreateFB_WeaponReference(
      _fbb,
      weapon_model__,
      weapon_type__,
      weapon_mod_types__,
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
      level_of_skill,
      armor_penetration,
      ap_per_attack,
      ap_per_reload,
      shots_per_attack,
      ammo_type__,
      dmg_type__);
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