// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WEAPONMODTEXTFB_FBWEAPONMOD_H_
#define FLATBUFFERS_GENERATED_WEAPONMODTEXTFB_FBWEAPONMOD_H_

#include "flatbuffers/flatbuffers.h"

#include "languageBundleFB_generated.h"

namespace fbWeaponMod {

struct FB_WeaponModTextType;
struct FB_WeaponModTextTypeBuilder;

struct FB_WeaponModTextCommon;
struct FB_WeaponModTextCommonBuilder;

struct FB_WeaponModText;
struct FB_WeaponModTextBuilder;

struct FB_WeaponModTextType FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModTextTypeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CHOKE = 4,
    VT_BARREL = 6,
    VT_UNDERBARREL = 8,
    VT_SCOPE = 10,
    VT_MAGAZINE = 12,
    VT_WEIGHT = 14,
    VT_HANDLE = 16
  };
  const fbCommon::FB_LanguageBundle *choke() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CHOKE);
  }
  const fbCommon::FB_LanguageBundle *barrel() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BARREL);
  }
  const fbCommon::FB_LanguageBundle *underbarrel() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_UNDERBARREL);
  }
  const fbCommon::FB_LanguageBundle *scope() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_SCOPE);
  }
  const fbCommon::FB_LanguageBundle *magazine() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_MAGAZINE);
  }
  const fbCommon::FB_LanguageBundle *weight() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_WEIGHT);
  }
  const fbCommon::FB_LanguageBundle *handle() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_HANDLE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CHOKE) &&
           verifier.VerifyTable(choke()) &&
           VerifyOffset(verifier, VT_BARREL) &&
           verifier.VerifyTable(barrel()) &&
           VerifyOffset(verifier, VT_UNDERBARREL) &&
           verifier.VerifyTable(underbarrel()) &&
           VerifyOffset(verifier, VT_SCOPE) &&
           verifier.VerifyTable(scope()) &&
           VerifyOffset(verifier, VT_MAGAZINE) &&
           verifier.VerifyTable(magazine()) &&
           VerifyOffset(verifier, VT_WEIGHT) &&
           verifier.VerifyTable(weight()) &&
           VerifyOffset(verifier, VT_HANDLE) &&
           verifier.VerifyTable(handle()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModTextTypeBuilder {
  typedef FB_WeaponModTextType Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_choke(flatbuffers::Offset<fbCommon::FB_LanguageBundle> choke) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_CHOKE, choke);
  }
  void add_barrel(flatbuffers::Offset<fbCommon::FB_LanguageBundle> barrel) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_BARREL, barrel);
  }
  void add_underbarrel(flatbuffers::Offset<fbCommon::FB_LanguageBundle> underbarrel) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_UNDERBARREL, underbarrel);
  }
  void add_scope(flatbuffers::Offset<fbCommon::FB_LanguageBundle> scope) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_SCOPE, scope);
  }
  void add_magazine(flatbuffers::Offset<fbCommon::FB_LanguageBundle> magazine) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_MAGAZINE, magazine);
  }
  void add_weight(flatbuffers::Offset<fbCommon::FB_LanguageBundle> weight) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_WEIGHT, weight);
  }
  void add_handle(flatbuffers::Offset<fbCommon::FB_LanguageBundle> handle) {
    fbb_.AddOffset(FB_WeaponModTextType::VT_HANDLE, handle);
  }
  explicit FB_WeaponModTextTypeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModTextType> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModTextType>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModTextType> CreateFB_WeaponModTextType(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> choke = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> barrel = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> underbarrel = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> scope = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> magazine = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> weight = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> handle = 0) {
  FB_WeaponModTextTypeBuilder builder_(_fbb);
  builder_.add_handle(handle);
  builder_.add_weight(weight);
  builder_.add_magazine(magazine);
  builder_.add_scope(scope);
  builder_.add_underbarrel(underbarrel);
  builder_.add_barrel(barrel);
  builder_.add_choke(choke);
  return builder_.Finish();
}

struct FB_WeaponModTextCommon FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModTextCommonBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ITEM_TYPE = 4,
    VT_MIN_DAMAGE = 6,
    VT_MAX_DAMAGE = 8,
    VT_SHOTS = 10,
    VT_DAMAGE_TYPE = 12,
    VT_AP = 14,
    VT_AP_RELOAD = 16,
    VT_REQUIRE = 18,
    VT_AMMO_CAPACITY = 20,
    VT_AMMO_TYPE = 22,
    VT_RANGE = 24,
    VT_BASE_HIT_CHANCE = 26,
    VT_CRIT_DAMAGE = 28,
    VT_CRIT_CHANCE = 30,
    VT_CONE_ANGLE = 32,
    VT_BONUS_SNEAK_DAMAGE = 34,
    VT_BONUS_NORM_DAMAGE = 36,
    VT_BONUS_MELEE_DAMAGE = 38,
    VT_BONUS_RANGE_DAMAGE = 40,
    VT_PENETRATION = 42
  };
  const fbCommon::FB_LanguageBundle *item_type() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_ITEM_TYPE);
  }
  const fbCommon::FB_LanguageBundle *min_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_MIN_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *max_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_MAX_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *shots() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_SHOTS);
  }
  const fbCommon::FB_LanguageBundle *damage_type() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_DAMAGE_TYPE);
  }
  const fbCommon::FB_LanguageBundle *ap() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_AP);
  }
  const fbCommon::FB_LanguageBundle *ap_reload() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_AP_RELOAD);
  }
  const fbCommon::FB_LanguageBundle *require() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_REQUIRE);
  }
  const fbCommon::FB_LanguageBundle *ammo_capacity() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_AMMO_CAPACITY);
  }
  const fbCommon::FB_LanguageBundle *ammo_type() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_AMMO_TYPE);
  }
  const fbCommon::FB_LanguageBundle *range() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_RANGE);
  }
  const fbCommon::FB_LanguageBundle *base_hit_chance() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BASE_HIT_CHANCE);
  }
  const fbCommon::FB_LanguageBundle *crit_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CRIT_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *crit_chance() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CRIT_CHANCE);
  }
  const fbCommon::FB_LanguageBundle *cone_angle() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CONE_ANGLE);
  }
  const fbCommon::FB_LanguageBundle *bonus_sneak_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BONUS_SNEAK_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *bonus_norm_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BONUS_NORM_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *bonus_melee_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BONUS_MELEE_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *bonus_range_damage() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_BONUS_RANGE_DAMAGE);
  }
  const fbCommon::FB_LanguageBundle *penetration() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_PENETRATION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ITEM_TYPE) &&
           verifier.VerifyTable(item_type()) &&
           VerifyOffset(verifier, VT_MIN_DAMAGE) &&
           verifier.VerifyTable(min_damage()) &&
           VerifyOffset(verifier, VT_MAX_DAMAGE) &&
           verifier.VerifyTable(max_damage()) &&
           VerifyOffset(verifier, VT_SHOTS) &&
           verifier.VerifyTable(shots()) &&
           VerifyOffset(verifier, VT_DAMAGE_TYPE) &&
           verifier.VerifyTable(damage_type()) &&
           VerifyOffset(verifier, VT_AP) &&
           verifier.VerifyTable(ap()) &&
           VerifyOffset(verifier, VT_AP_RELOAD) &&
           verifier.VerifyTable(ap_reload()) &&
           VerifyOffset(verifier, VT_REQUIRE) &&
           verifier.VerifyTable(require()) &&
           VerifyOffset(verifier, VT_AMMO_CAPACITY) &&
           verifier.VerifyTable(ammo_capacity()) &&
           VerifyOffset(verifier, VT_AMMO_TYPE) &&
           verifier.VerifyTable(ammo_type()) &&
           VerifyOffset(verifier, VT_RANGE) &&
           verifier.VerifyTable(range()) &&
           VerifyOffset(verifier, VT_BASE_HIT_CHANCE) &&
           verifier.VerifyTable(base_hit_chance()) &&
           VerifyOffset(verifier, VT_CRIT_DAMAGE) &&
           verifier.VerifyTable(crit_damage()) &&
           VerifyOffset(verifier, VT_CRIT_CHANCE) &&
           verifier.VerifyTable(crit_chance()) &&
           VerifyOffset(verifier, VT_CONE_ANGLE) &&
           verifier.VerifyTable(cone_angle()) &&
           VerifyOffset(verifier, VT_BONUS_SNEAK_DAMAGE) &&
           verifier.VerifyTable(bonus_sneak_damage()) &&
           VerifyOffset(verifier, VT_BONUS_NORM_DAMAGE) &&
           verifier.VerifyTable(bonus_norm_damage()) &&
           VerifyOffset(verifier, VT_BONUS_MELEE_DAMAGE) &&
           verifier.VerifyTable(bonus_melee_damage()) &&
           VerifyOffset(verifier, VT_BONUS_RANGE_DAMAGE) &&
           verifier.VerifyTable(bonus_range_damage()) &&
           VerifyOffset(verifier, VT_PENETRATION) &&
           verifier.VerifyTable(penetration()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModTextCommonBuilder {
  typedef FB_WeaponModTextCommon Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_item_type(flatbuffers::Offset<fbCommon::FB_LanguageBundle> item_type) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_ITEM_TYPE, item_type);
  }
  void add_min_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> min_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_MIN_DAMAGE, min_damage);
  }
  void add_max_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> max_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_MAX_DAMAGE, max_damage);
  }
  void add_shots(flatbuffers::Offset<fbCommon::FB_LanguageBundle> shots) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_SHOTS, shots);
  }
  void add_damage_type(flatbuffers::Offset<fbCommon::FB_LanguageBundle> damage_type) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_DAMAGE_TYPE, damage_type);
  }
  void add_ap(flatbuffers::Offset<fbCommon::FB_LanguageBundle> ap) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_AP, ap);
  }
  void add_ap_reload(flatbuffers::Offset<fbCommon::FB_LanguageBundle> ap_reload) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_AP_RELOAD, ap_reload);
  }
  void add_require(flatbuffers::Offset<fbCommon::FB_LanguageBundle> require) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_REQUIRE, require);
  }
  void add_ammo_capacity(flatbuffers::Offset<fbCommon::FB_LanguageBundle> ammo_capacity) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_AMMO_CAPACITY, ammo_capacity);
  }
  void add_ammo_type(flatbuffers::Offset<fbCommon::FB_LanguageBundle> ammo_type) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_AMMO_TYPE, ammo_type);
  }
  void add_range(flatbuffers::Offset<fbCommon::FB_LanguageBundle> range) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_RANGE, range);
  }
  void add_base_hit_chance(flatbuffers::Offset<fbCommon::FB_LanguageBundle> base_hit_chance) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_BASE_HIT_CHANCE, base_hit_chance);
  }
  void add_crit_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> crit_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_CRIT_DAMAGE, crit_damage);
  }
  void add_crit_chance(flatbuffers::Offset<fbCommon::FB_LanguageBundle> crit_chance) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_CRIT_CHANCE, crit_chance);
  }
  void add_cone_angle(flatbuffers::Offset<fbCommon::FB_LanguageBundle> cone_angle) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_CONE_ANGLE, cone_angle);
  }
  void add_bonus_sneak_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_sneak_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_BONUS_SNEAK_DAMAGE, bonus_sneak_damage);
  }
  void add_bonus_norm_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_norm_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_BONUS_NORM_DAMAGE, bonus_norm_damage);
  }
  void add_bonus_melee_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_melee_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_BONUS_MELEE_DAMAGE, bonus_melee_damage);
  }
  void add_bonus_range_damage(flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_range_damage) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_BONUS_RANGE_DAMAGE, bonus_range_damage);
  }
  void add_penetration(flatbuffers::Offset<fbCommon::FB_LanguageBundle> penetration) {
    fbb_.AddOffset(FB_WeaponModTextCommon::VT_PENETRATION, penetration);
  }
  explicit FB_WeaponModTextCommonBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModTextCommon> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModTextCommon>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModTextCommon> CreateFB_WeaponModTextCommon(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> item_type = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> min_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> max_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> shots = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> damage_type = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> ap = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> ap_reload = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> require = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> ammo_capacity = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> ammo_type = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> range = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> base_hit_chance = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> crit_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> crit_chance = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> cone_angle = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_sneak_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_norm_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_melee_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> bonus_range_damage = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> penetration = 0) {
  FB_WeaponModTextCommonBuilder builder_(_fbb);
  builder_.add_penetration(penetration);
  builder_.add_bonus_range_damage(bonus_range_damage);
  builder_.add_bonus_melee_damage(bonus_melee_damage);
  builder_.add_bonus_norm_damage(bonus_norm_damage);
  builder_.add_bonus_sneak_damage(bonus_sneak_damage);
  builder_.add_cone_angle(cone_angle);
  builder_.add_crit_chance(crit_chance);
  builder_.add_crit_damage(crit_damage);
  builder_.add_base_hit_chance(base_hit_chance);
  builder_.add_range(range);
  builder_.add_ammo_type(ammo_type);
  builder_.add_ammo_capacity(ammo_capacity);
  builder_.add_require(require);
  builder_.add_ap_reload(ap_reload);
  builder_.add_ap(ap);
  builder_.add_damage_type(damage_type);
  builder_.add_shots(shots);
  builder_.add_max_damage(max_damage);
  builder_.add_min_damage(min_damage);
  builder_.add_item_type(item_type);
  return builder_.Finish();
}

struct FB_WeaponModText FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModTextBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_COMMON = 6
  };
  const fbWeaponMod::FB_WeaponModTextType *type() const {
    return GetPointer<const fbWeaponMod::FB_WeaponModTextType *>(VT_TYPE);
  }
  const fbWeaponMod::FB_WeaponModTextCommon *common() const {
    return GetPointer<const fbWeaponMod::FB_WeaponModTextCommon *>(VT_COMMON);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TYPE) &&
           verifier.VerifyTable(type()) &&
           VerifyOffset(verifier, VT_COMMON) &&
           verifier.VerifyTable(common()) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModTextBuilder {
  typedef FB_WeaponModText Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(flatbuffers::Offset<fbWeaponMod::FB_WeaponModTextType> type) {
    fbb_.AddOffset(FB_WeaponModText::VT_TYPE, type);
  }
  void add_common(flatbuffers::Offset<fbWeaponMod::FB_WeaponModTextCommon> common) {
    fbb_.AddOffset(FB_WeaponModText::VT_COMMON, common);
  }
  explicit FB_WeaponModTextBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponModText> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponModText>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponModText> CreateFB_WeaponModText(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModTextType> type = 0,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModTextCommon> common = 0) {
  FB_WeaponModTextBuilder builder_(_fbb);
  builder_.add_common(common);
  builder_.add_type(type);
  return builder_.Finish();
}

inline const fbWeaponMod::FB_WeaponModText *GetFB_WeaponModText(const void *buf) {
  return flatbuffers::GetRoot<fbWeaponMod::FB_WeaponModText>(buf);
}

inline const fbWeaponMod::FB_WeaponModText *GetSizePrefixedFB_WeaponModText(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbWeaponMod::FB_WeaponModText>(buf);
}

inline const char *FB_WeaponModTextIdentifier() {
  return "WM_T";
}

inline bool FB_WeaponModTextBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_WeaponModTextIdentifier());
}

inline bool VerifyFB_WeaponModTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbWeaponMod::FB_WeaponModText>(FB_WeaponModTextIdentifier());
}

inline bool VerifySizePrefixedFB_WeaponModTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbWeaponMod::FB_WeaponModText>(FB_WeaponModTextIdentifier());
}

inline const char *FB_WeaponModTextExtension() {
  return "bundle";
}

inline void FinishFB_WeaponModTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModText> root) {
  fbb.Finish(root, FB_WeaponModTextIdentifier());
}

inline void FinishSizePrefixedFB_WeaponModTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbWeaponMod::FB_WeaponModText> root) {
  fbb.FinishSizePrefixed(root, FB_WeaponModTextIdentifier());
}

}  // namespace fbWeaponMod

#endif  // FLATBUFFERS_GENERATED_WEAPONMODTEXTFB_FBWEAPONMOD_H_
