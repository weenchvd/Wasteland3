// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ATTRIBUTEREFERENCEFB_FBATTRIBUTE_H_
#define FLATBUFFERS_GENERATED_ATTRIBUTEREFERENCEFB_FBATTRIBUTE_H_

#include "flatbuffers/flatbuffers.h"

namespace fbAttribute {

struct FB_PointAttributeDistribution;

struct FB_CoordinationDistribution;

struct FB_LuckDistribution;

struct FB_AwarenessDistribution;

struct FB_StrengthDistribution;

struct FB_SpeedDistribution;

struct FB_IntelligenceDistribution;

struct FB_CharismaDistribution;

struct FB_AttributeReference;
struct FB_AttributeReferenceBuilder;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) FB_PointAttributeDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int8_t p_[2];

 public:
  FB_PointAttributeDistribution()
      : p_() {
  }
  FB_PointAttributeDistribution(flatbuffers::span<const int8_t, 2> _p) {
    flatbuffers::CastToArray(p_).CopyFromSpan(_p);
  }
  const flatbuffers::Array<int8_t, 2> *p() const {
    return &flatbuffers::CastToArray(p_);
  }
};
FLATBUFFERS_STRUCT_END(FB_PointAttributeDistribution, 2);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_CoordinationDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t status_effect_[11];
  int8_t ap_[11];
  int8_t ap_max_[11];

 public:
  FB_CoordinationDistribution()
      : status_effect_(),
        ap_(),
        ap_max_() {
  }
  FB_CoordinationDistribution(flatbuffers::span<const int16_t, 11> _status_effect, flatbuffers::span<const int8_t, 11> _ap, flatbuffers::span<const int8_t, 11> _ap_max) {
    flatbuffers::CastToArray(status_effect_).CopyFromSpan(_status_effect);
    flatbuffers::CastToArray(ap_).CopyFromSpan(_ap);
    flatbuffers::CastToArray(ap_max_).CopyFromSpan(_ap_max);
  }
  const flatbuffers::Array<int16_t, 11> *status_effect() const {
    return &flatbuffers::CastToArray(status_effect_);
  }
  const flatbuffers::Array<int8_t, 11> *ap() const {
    return &flatbuffers::CastToArray(ap_);
  }
  const flatbuffers::Array<int8_t, 11> *ap_max() const {
    return &flatbuffers::CastToArray(ap_max_);
  }
};
FLATBUFFERS_STRUCT_END(FB_CoordinationDistribution, 44);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_LuckDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int8_t penet_[11];
  int8_t padding0__;
  int16_t action_[11];
  int16_t crit_damage_[11];
  int16_t mega_crit_damage_[11];
  int16_t evade_[11];
  int16_t crit_resist_[11];
  int16_t double_healing_[11];
  int16_t double_money_[11];
  int16_t double_scrap_[11];

 public:
  FB_LuckDistribution()
      : penet_(),
        padding0__(0),
        action_(),
        crit_damage_(),
        mega_crit_damage_(),
        evade_(),
        crit_resist_(),
        double_healing_(),
        double_money_(),
        double_scrap_() {
    (void)padding0__;
  }
  FB_LuckDistribution(flatbuffers::span<const int8_t, 11> _penet, flatbuffers::span<const int16_t, 11> _action, flatbuffers::span<const int16_t, 11> _crit_damage, flatbuffers::span<const int16_t, 11> _mega_crit_damage, flatbuffers::span<const int16_t, 11> _evade, flatbuffers::span<const int16_t, 11> _crit_resist, flatbuffers::span<const int16_t, 11> _double_healing, flatbuffers::span<const int16_t, 11> _double_money, flatbuffers::span<const int16_t, 11> _double_scrap)
      : padding0__(0) {
    flatbuffers::CastToArray(penet_).CopyFromSpan(_penet);
    (void)padding0__;
    flatbuffers::CastToArray(action_).CopyFromSpan(_action);
    flatbuffers::CastToArray(crit_damage_).CopyFromSpan(_crit_damage);
    flatbuffers::CastToArray(mega_crit_damage_).CopyFromSpan(_mega_crit_damage);
    flatbuffers::CastToArray(evade_).CopyFromSpan(_evade);
    flatbuffers::CastToArray(crit_resist_).CopyFromSpan(_crit_resist);
    flatbuffers::CastToArray(double_healing_).CopyFromSpan(_double_healing);
    flatbuffers::CastToArray(double_money_).CopyFromSpan(_double_money);
    flatbuffers::CastToArray(double_scrap_).CopyFromSpan(_double_scrap);
  }
  const flatbuffers::Array<int8_t, 11> *penet() const {
    return &flatbuffers::CastToArray(penet_);
  }
  const flatbuffers::Array<int16_t, 11> *action() const {
    return &flatbuffers::CastToArray(action_);
  }
  const flatbuffers::Array<int16_t, 11> *crit_damage() const {
    return &flatbuffers::CastToArray(crit_damage_);
  }
  const flatbuffers::Array<int16_t, 11> *mega_crit_damage() const {
    return &flatbuffers::CastToArray(mega_crit_damage_);
  }
  const flatbuffers::Array<int16_t, 11> *evade() const {
    return &flatbuffers::CastToArray(evade_);
  }
  const flatbuffers::Array<int16_t, 11> *crit_resist() const {
    return &flatbuffers::CastToArray(crit_resist_);
  }
  const flatbuffers::Array<int16_t, 11> *double_healing() const {
    return &flatbuffers::CastToArray(double_healing_);
  }
  const flatbuffers::Array<int16_t, 11> *double_money() const {
    return &flatbuffers::CastToArray(double_money_);
  }
  const flatbuffers::Array<int16_t, 11> *double_scrap() const {
    return &flatbuffers::CastToArray(double_scrap_);
  }
};
FLATBUFFERS_STRUCT_END(FB_LuckDistribution, 188);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_AwarenessDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t hit_[11];
  int8_t percep_[11];
  int8_t padding0__;
  int16_t ranged_damage_[11];

 public:
  FB_AwarenessDistribution()
      : hit_(),
        percep_(),
        padding0__(0),
        ranged_damage_() {
    (void)padding0__;
  }
  FB_AwarenessDistribution(flatbuffers::span<const int16_t, 11> _hit, flatbuffers::span<const int8_t, 11> _percep, flatbuffers::span<const int16_t, 11> _ranged_damage)
      : padding0__(0) {
    flatbuffers::CastToArray(hit_).CopyFromSpan(_hit);
    flatbuffers::CastToArray(percep_).CopyFromSpan(_percep);
    (void)padding0__;
    flatbuffers::CastToArray(ranged_damage_).CopyFromSpan(_ranged_damage);
  }
  const flatbuffers::Array<int16_t, 11> *hit() const {
    return &flatbuffers::CastToArray(hit_);
  }
  const flatbuffers::Array<int8_t, 11> *percep() const {
    return &flatbuffers::CastToArray(percep_);
  }
  const flatbuffers::Array<int16_t, 11> *ranged_damage() const {
    return &flatbuffers::CastToArray(ranged_damage_);
  }
};
FLATBUFFERS_STRUCT_END(FB_AwarenessDistribution, 56);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_StrengthDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t con_max_[11];
  int16_t con_per_lvl_[11];
  int16_t melee_damage_[11];
  int16_t throwing_range_[11];

 public:
  FB_StrengthDistribution()
      : con_max_(),
        con_per_lvl_(),
        melee_damage_(),
        throwing_range_() {
  }
  FB_StrengthDistribution(flatbuffers::span<const int16_t, 11> _con_max, flatbuffers::span<const int16_t, 11> _con_per_lvl, flatbuffers::span<const int16_t, 11> _melee_damage, flatbuffers::span<const int16_t, 11> _throwing_range) {
    flatbuffers::CastToArray(con_max_).CopyFromSpan(_con_max);
    flatbuffers::CastToArray(con_per_lvl_).CopyFromSpan(_con_per_lvl);
    flatbuffers::CastToArray(melee_damage_).CopyFromSpan(_melee_damage);
    flatbuffers::CastToArray(throwing_range_).CopyFromSpan(_throwing_range);
  }
  const flatbuffers::Array<int16_t, 11> *con_max() const {
    return &flatbuffers::CastToArray(con_max_);
  }
  const flatbuffers::Array<int16_t, 11> *con_per_lvl() const {
    return &flatbuffers::CastToArray(con_per_lvl_);
  }
  const flatbuffers::Array<int16_t, 11> *melee_damage() const {
    return &flatbuffers::CastToArray(melee_damage_);
  }
  const flatbuffers::Array<int16_t, 11> *throwing_range() const {
    return &flatbuffers::CastToArray(throwing_range_);
  }
};
FLATBUFFERS_STRUCT_END(FB_StrengthDistribution, 88);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_SpeedDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t combat_speed_[11];
  int16_t evasion_[11];
  int16_t initiative_[11];

 public:
  FB_SpeedDistribution()
      : combat_speed_(),
        evasion_(),
        initiative_() {
  }
  FB_SpeedDistribution(flatbuffers::span<const int16_t, 11> _combat_speed, flatbuffers::span<const int16_t, 11> _evasion, flatbuffers::span<const int16_t, 11> _initiative) {
    flatbuffers::CastToArray(combat_speed_).CopyFromSpan(_combat_speed);
    flatbuffers::CastToArray(evasion_).CopyFromSpan(_evasion);
    flatbuffers::CastToArray(initiative_).CopyFromSpan(_initiative);
  }
  const flatbuffers::Array<int16_t, 11> *combat_speed() const {
    return &flatbuffers::CastToArray(combat_speed_);
  }
  const flatbuffers::Array<int16_t, 11> *evasion() const {
    return &flatbuffers::CastToArray(evasion_);
  }
  const flatbuffers::Array<int16_t, 11> *initiative() const {
    return &flatbuffers::CastToArray(initiative_);
  }
};
FLATBUFFERS_STRUCT_END(FB_SpeedDistribution, 66);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_IntelligenceDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t crit_damage_chance_[11];
  int16_t crit_damage_mult_[11];
  int16_t crit_healing_chance_[11];
  int16_t crit_healing_bonus_[11];
  int16_t skill_point_[11];

 public:
  FB_IntelligenceDistribution()
      : crit_damage_chance_(),
        crit_damage_mult_(),
        crit_healing_chance_(),
        crit_healing_bonus_(),
        skill_point_() {
  }
  FB_IntelligenceDistribution(flatbuffers::span<const int16_t, 11> _crit_damage_chance, flatbuffers::span<const int16_t, 11> _crit_damage_mult, flatbuffers::span<const int16_t, 11> _crit_healing_chance, flatbuffers::span<const int16_t, 11> _crit_healing_bonus, flatbuffers::span<const int16_t, 11> _skill_point) {
    flatbuffers::CastToArray(crit_damage_chance_).CopyFromSpan(_crit_damage_chance);
    flatbuffers::CastToArray(crit_damage_mult_).CopyFromSpan(_crit_damage_mult);
    flatbuffers::CastToArray(crit_healing_chance_).CopyFromSpan(_crit_healing_chance);
    flatbuffers::CastToArray(crit_healing_bonus_).CopyFromSpan(_crit_healing_bonus);
    flatbuffers::CastToArray(skill_point_).CopyFromSpan(_skill_point);
  }
  const flatbuffers::Array<int16_t, 11> *crit_damage_chance() const {
    return &flatbuffers::CastToArray(crit_damage_chance_);
  }
  const flatbuffers::Array<int16_t, 11> *crit_damage_mult() const {
    return &flatbuffers::CastToArray(crit_damage_mult_);
  }
  const flatbuffers::Array<int16_t, 11> *crit_healing_chance() const {
    return &flatbuffers::CastToArray(crit_healing_chance_);
  }
  const flatbuffers::Array<int16_t, 11> *crit_healing_bonus() const {
    return &flatbuffers::CastToArray(crit_healing_bonus_);
  }
  const flatbuffers::Array<int16_t, 11> *skill_point() const {
    return &flatbuffers::CastToArray(skill_point_);
  }
};
FLATBUFFERS_STRUCT_END(FB_IntelligenceDistribution, 110);

/// ATTRIBUTE LEVEL:
/// 0     1     2     3     4     5     6     7     8     9    10
FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) FB_CharismaDistribution FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t strike_rate_[11];
  int16_t leadership_range_[11];
  int16_t experience_[11];
  int16_t mission_reward_[11];

 public:
  FB_CharismaDistribution()
      : strike_rate_(),
        leadership_range_(),
        experience_(),
        mission_reward_() {
  }
  FB_CharismaDistribution(flatbuffers::span<const int16_t, 11> _strike_rate, flatbuffers::span<const int16_t, 11> _leadership_range, flatbuffers::span<const int16_t, 11> _experience, flatbuffers::span<const int16_t, 11> _mission_reward) {
    flatbuffers::CastToArray(strike_rate_).CopyFromSpan(_strike_rate);
    flatbuffers::CastToArray(leadership_range_).CopyFromSpan(_leadership_range);
    flatbuffers::CastToArray(experience_).CopyFromSpan(_experience);
    flatbuffers::CastToArray(mission_reward_).CopyFromSpan(_mission_reward);
  }
  const flatbuffers::Array<int16_t, 11> *strike_rate() const {
    return &flatbuffers::CastToArray(strike_rate_);
  }
  const flatbuffers::Array<int16_t, 11> *leadership_range() const {
    return &flatbuffers::CastToArray(leadership_range_);
  }
  const flatbuffers::Array<int16_t, 11> *experience() const {
    return &flatbuffers::CastToArray(experience_);
  }
  const flatbuffers::Array<int16_t, 11> *mission_reward() const {
    return &flatbuffers::CastToArray(mission_reward_);
  }
};
FLATBUFFERS_STRUCT_END(FB_CharismaDistribution, 88);

struct FB_AttributeReference FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_AttributeReferenceBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MIN_ATTR_POINTS = 4,
    VT_MAX_ATTR_POINTS = 6,
    VT_MIN_ATTR_LEVEL = 8,
    VT_MAX_ATTR_LEVEL = 10,
    VT_POINT_ATTR_DISTR = 12,
    VT_COORD_DISTR = 14,
    VT_LUCK_DISTR = 16,
    VT_AWARE_DISTR = 18,
    VT_STR_DISTR = 20,
    VT_SPEED_DISTR = 22,
    VT_INT_DISTR = 24,
    VT_CHA_DISTR = 26
  };
  int8_t min_attr_points() const {
    return GetField<int8_t>(VT_MIN_ATTR_POINTS, 0);
  }
  int8_t max_attr_points() const {
    return GetField<int8_t>(VT_MAX_ATTR_POINTS, 0);
  }
  int8_t min_attr_level() const {
    return GetField<int8_t>(VT_MIN_ATTR_LEVEL, 0);
  }
  int8_t max_attr_level() const {
    return GetField<int8_t>(VT_MAX_ATTR_LEVEL, 0);
  }
  const fbAttribute::FB_PointAttributeDistribution *point_attr_distr() const {
    return GetStruct<const fbAttribute::FB_PointAttributeDistribution *>(VT_POINT_ATTR_DISTR);
  }
  const fbAttribute::FB_CoordinationDistribution *coord_distr() const {
    return GetStruct<const fbAttribute::FB_CoordinationDistribution *>(VT_COORD_DISTR);
  }
  const fbAttribute::FB_LuckDistribution *luck_distr() const {
    return GetStruct<const fbAttribute::FB_LuckDistribution *>(VT_LUCK_DISTR);
  }
  const fbAttribute::FB_AwarenessDistribution *aware_distr() const {
    return GetStruct<const fbAttribute::FB_AwarenessDistribution *>(VT_AWARE_DISTR);
  }
  const fbAttribute::FB_StrengthDistribution *str_distr() const {
    return GetStruct<const fbAttribute::FB_StrengthDistribution *>(VT_STR_DISTR);
  }
  const fbAttribute::FB_SpeedDistribution *speed_distr() const {
    return GetStruct<const fbAttribute::FB_SpeedDistribution *>(VT_SPEED_DISTR);
  }
  const fbAttribute::FB_IntelligenceDistribution *int_distr() const {
    return GetStruct<const fbAttribute::FB_IntelligenceDistribution *>(VT_INT_DISTR);
  }
  const fbAttribute::FB_CharismaDistribution *cha_distr() const {
    return GetStruct<const fbAttribute::FB_CharismaDistribution *>(VT_CHA_DISTR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_MIN_ATTR_POINTS) &&
           VerifyField<int8_t>(verifier, VT_MAX_ATTR_POINTS) &&
           VerifyField<int8_t>(verifier, VT_MIN_ATTR_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_MAX_ATTR_LEVEL) &&
           VerifyField<fbAttribute::FB_PointAttributeDistribution>(verifier, VT_POINT_ATTR_DISTR) &&
           VerifyField<fbAttribute::FB_CoordinationDistribution>(verifier, VT_COORD_DISTR) &&
           VerifyField<fbAttribute::FB_LuckDistribution>(verifier, VT_LUCK_DISTR) &&
           VerifyField<fbAttribute::FB_AwarenessDistribution>(verifier, VT_AWARE_DISTR) &&
           VerifyField<fbAttribute::FB_StrengthDistribution>(verifier, VT_STR_DISTR) &&
           VerifyField<fbAttribute::FB_SpeedDistribution>(verifier, VT_SPEED_DISTR) &&
           VerifyField<fbAttribute::FB_IntelligenceDistribution>(verifier, VT_INT_DISTR) &&
           VerifyField<fbAttribute::FB_CharismaDistribution>(verifier, VT_CHA_DISTR) &&
           verifier.EndTable();
  }
};

struct FB_AttributeReferenceBuilder {
  typedef FB_AttributeReference Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_min_attr_points(int8_t min_attr_points) {
    fbb_.AddElement<int8_t>(FB_AttributeReference::VT_MIN_ATTR_POINTS, min_attr_points, 0);
  }
  void add_max_attr_points(int8_t max_attr_points) {
    fbb_.AddElement<int8_t>(FB_AttributeReference::VT_MAX_ATTR_POINTS, max_attr_points, 0);
  }
  void add_min_attr_level(int8_t min_attr_level) {
    fbb_.AddElement<int8_t>(FB_AttributeReference::VT_MIN_ATTR_LEVEL, min_attr_level, 0);
  }
  void add_max_attr_level(int8_t max_attr_level) {
    fbb_.AddElement<int8_t>(FB_AttributeReference::VT_MAX_ATTR_LEVEL, max_attr_level, 0);
  }
  void add_point_attr_distr(const fbAttribute::FB_PointAttributeDistribution *point_attr_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_POINT_ATTR_DISTR, point_attr_distr);
  }
  void add_coord_distr(const fbAttribute::FB_CoordinationDistribution *coord_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_COORD_DISTR, coord_distr);
  }
  void add_luck_distr(const fbAttribute::FB_LuckDistribution *luck_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_LUCK_DISTR, luck_distr);
  }
  void add_aware_distr(const fbAttribute::FB_AwarenessDistribution *aware_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_AWARE_DISTR, aware_distr);
  }
  void add_str_distr(const fbAttribute::FB_StrengthDistribution *str_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_STR_DISTR, str_distr);
  }
  void add_speed_distr(const fbAttribute::FB_SpeedDistribution *speed_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_SPEED_DISTR, speed_distr);
  }
  void add_int_distr(const fbAttribute::FB_IntelligenceDistribution *int_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_INT_DISTR, int_distr);
  }
  void add_cha_distr(const fbAttribute::FB_CharismaDistribution *cha_distr) {
    fbb_.AddStruct(FB_AttributeReference::VT_CHA_DISTR, cha_distr);
  }
  explicit FB_AttributeReferenceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_AttributeReference> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_AttributeReference>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_AttributeReference> CreateFB_AttributeReference(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t min_attr_points = 0,
    int8_t max_attr_points = 0,
    int8_t min_attr_level = 0,
    int8_t max_attr_level = 0,
    const fbAttribute::FB_PointAttributeDistribution *point_attr_distr = 0,
    const fbAttribute::FB_CoordinationDistribution *coord_distr = 0,
    const fbAttribute::FB_LuckDistribution *luck_distr = 0,
    const fbAttribute::FB_AwarenessDistribution *aware_distr = 0,
    const fbAttribute::FB_StrengthDistribution *str_distr = 0,
    const fbAttribute::FB_SpeedDistribution *speed_distr = 0,
    const fbAttribute::FB_IntelligenceDistribution *int_distr = 0,
    const fbAttribute::FB_CharismaDistribution *cha_distr = 0) {
  FB_AttributeReferenceBuilder builder_(_fbb);
  builder_.add_cha_distr(cha_distr);
  builder_.add_int_distr(int_distr);
  builder_.add_speed_distr(speed_distr);
  builder_.add_str_distr(str_distr);
  builder_.add_aware_distr(aware_distr);
  builder_.add_luck_distr(luck_distr);
  builder_.add_coord_distr(coord_distr);
  builder_.add_point_attr_distr(point_attr_distr);
  builder_.add_max_attr_level(max_attr_level);
  builder_.add_min_attr_level(min_attr_level);
  builder_.add_max_attr_points(max_attr_points);
  builder_.add_min_attr_points(min_attr_points);
  return builder_.Finish();
}

inline const fbAttribute::FB_AttributeReference *GetFB_AttributeReference(const void *buf) {
  return flatbuffers::GetRoot<fbAttribute::FB_AttributeReference>(buf);
}

inline const fbAttribute::FB_AttributeReference *GetSizePrefixedFB_AttributeReference(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbAttribute::FB_AttributeReference>(buf);
}

inline const char *FB_AttributeReferenceIdentifier() {
  return "ATTR";
}

inline bool FB_AttributeReferenceBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_AttributeReferenceIdentifier());
}

inline bool VerifyFB_AttributeReferenceBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbAttribute::FB_AttributeReference>(FB_AttributeReferenceIdentifier());
}

inline bool VerifySizePrefixedFB_AttributeReferenceBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbAttribute::FB_AttributeReference>(FB_AttributeReferenceIdentifier());
}

inline const char *FB_AttributeReferenceExtension() {
  return "bundle";
}

inline void FinishFB_AttributeReferenceBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbAttribute::FB_AttributeReference> root) {
  fbb.Finish(root, FB_AttributeReferenceIdentifier());
}

inline void FinishSizePrefixedFB_AttributeReferenceBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbAttribute::FB_AttributeReference> root) {
  fbb.FinishSizePrefixed(root, FB_AttributeReferenceIdentifier());
}

}  // namespace fbAttribute

#endif  // FLATBUFFERS_GENERATED_ATTRIBUTEREFERENCEFB_FBATTRIBUTE_H_
