// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SKILLSERIALIZATIONFB_FBSKILL_H_
#define FLATBUFFERS_GENERATED_SKILLSERIALIZATIONFB_FBSKILL_H_

#include "flatbuffers/flatbuffers.h"

namespace fbSkill {

struct FB_Skill;
struct FB_SkillBuilder;

struct FB_Skill FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_SkillBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SKILL_POINTS = 4,
    VT_AUTOMATIC_LEVEL = 6,
    VT_BIG_GUNS_LEVEL = 8,
    VT_BRAWLING_LEVEL = 10,
    VT_MELEE_LEVEL = 12,
    VT_SMALL_ARMS_LEVEL = 14,
    VT_SNIPER_LEVEL = 16,
    VT_ANIMAL_WHISPERER_LEVEL = 18,
    VT_EXPLOSIVES_LEVEL = 20,
    VT_FIRST_AID_LEVEL = 22,
    VT_SNEAKY_SHIT_LEVEL = 24,
    VT_WEIRD_SCIENCE_LEVEL = 26,
    VT_MECHANICS_LEVEL = 28,
    VT_SURVIVAL_LEVEL = 30,
    VT_WEAPON_MODDING_LEVEL = 32,
    VT_BARTER_LEVEL = 34,
    VT_LEADERSHIP_LEVEL = 36
  };
  int16_t skill_points() const {
    return GetField<int16_t>(VT_SKILL_POINTS, 0);
  }
  int8_t automatic_level() const {
    return GetField<int8_t>(VT_AUTOMATIC_LEVEL, 0);
  }
  int8_t big_guns_level() const {
    return GetField<int8_t>(VT_BIG_GUNS_LEVEL, 0);
  }
  int8_t brawling_level() const {
    return GetField<int8_t>(VT_BRAWLING_LEVEL, 0);
  }
  int8_t melee_level() const {
    return GetField<int8_t>(VT_MELEE_LEVEL, 0);
  }
  int8_t small_arms_level() const {
    return GetField<int8_t>(VT_SMALL_ARMS_LEVEL, 0);
  }
  int8_t sniper_level() const {
    return GetField<int8_t>(VT_SNIPER_LEVEL, 0);
  }
  int8_t animal_whisperer_level() const {
    return GetField<int8_t>(VT_ANIMAL_WHISPERER_LEVEL, 0);
  }
  int8_t explosives_level() const {
    return GetField<int8_t>(VT_EXPLOSIVES_LEVEL, 0);
  }
  int8_t first_aid_level() const {
    return GetField<int8_t>(VT_FIRST_AID_LEVEL, 0);
  }
  int8_t sneaky_shit_level() const {
    return GetField<int8_t>(VT_SNEAKY_SHIT_LEVEL, 0);
  }
  int8_t weird_science_level() const {
    return GetField<int8_t>(VT_WEIRD_SCIENCE_LEVEL, 0);
  }
  int8_t mechanics_level() const {
    return GetField<int8_t>(VT_MECHANICS_LEVEL, 0);
  }
  int8_t survival_level() const {
    return GetField<int8_t>(VT_SURVIVAL_LEVEL, 0);
  }
  int8_t weapon_modding_level() const {
    return GetField<int8_t>(VT_WEAPON_MODDING_LEVEL, 0);
  }
  int8_t barter_level() const {
    return GetField<int8_t>(VT_BARTER_LEVEL, 0);
  }
  int8_t leadership_level() const {
    return GetField<int8_t>(VT_LEADERSHIP_LEVEL, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_SKILL_POINTS) &&
           VerifyField<int8_t>(verifier, VT_AUTOMATIC_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_BIG_GUNS_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_BRAWLING_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_MELEE_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_SMALL_ARMS_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_SNIPER_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_ANIMAL_WHISPERER_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_EXPLOSIVES_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_FIRST_AID_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_SNEAKY_SHIT_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_WEIRD_SCIENCE_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_MECHANICS_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_SURVIVAL_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_WEAPON_MODDING_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_BARTER_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_LEADERSHIP_LEVEL) &&
           verifier.EndTable();
  }
};

struct FB_SkillBuilder {
  typedef FB_Skill Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_skill_points(int16_t skill_points) {
    fbb_.AddElement<int16_t>(FB_Skill::VT_SKILL_POINTS, skill_points, 0);
  }
  void add_automatic_level(int8_t automatic_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_AUTOMATIC_LEVEL, automatic_level, 0);
  }
  void add_big_guns_level(int8_t big_guns_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_BIG_GUNS_LEVEL, big_guns_level, 0);
  }
  void add_brawling_level(int8_t brawling_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_BRAWLING_LEVEL, brawling_level, 0);
  }
  void add_melee_level(int8_t melee_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_MELEE_LEVEL, melee_level, 0);
  }
  void add_small_arms_level(int8_t small_arms_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_SMALL_ARMS_LEVEL, small_arms_level, 0);
  }
  void add_sniper_level(int8_t sniper_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_SNIPER_LEVEL, sniper_level, 0);
  }
  void add_animal_whisperer_level(int8_t animal_whisperer_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_ANIMAL_WHISPERER_LEVEL, animal_whisperer_level, 0);
  }
  void add_explosives_level(int8_t explosives_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_EXPLOSIVES_LEVEL, explosives_level, 0);
  }
  void add_first_aid_level(int8_t first_aid_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_FIRST_AID_LEVEL, first_aid_level, 0);
  }
  void add_sneaky_shit_level(int8_t sneaky_shit_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_SNEAKY_SHIT_LEVEL, sneaky_shit_level, 0);
  }
  void add_weird_science_level(int8_t weird_science_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_WEIRD_SCIENCE_LEVEL, weird_science_level, 0);
  }
  void add_mechanics_level(int8_t mechanics_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_MECHANICS_LEVEL, mechanics_level, 0);
  }
  void add_survival_level(int8_t survival_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_SURVIVAL_LEVEL, survival_level, 0);
  }
  void add_weapon_modding_level(int8_t weapon_modding_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_WEAPON_MODDING_LEVEL, weapon_modding_level, 0);
  }
  void add_barter_level(int8_t barter_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_BARTER_LEVEL, barter_level, 0);
  }
  void add_leadership_level(int8_t leadership_level) {
    fbb_.AddElement<int8_t>(FB_Skill::VT_LEADERSHIP_LEVEL, leadership_level, 0);
  }
  explicit FB_SkillBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_Skill> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_Skill>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_Skill> CreateFB_Skill(
    flatbuffers::FlatBufferBuilder &_fbb,
    int16_t skill_points = 0,
    int8_t automatic_level = 0,
    int8_t big_guns_level = 0,
    int8_t brawling_level = 0,
    int8_t melee_level = 0,
    int8_t small_arms_level = 0,
    int8_t sniper_level = 0,
    int8_t animal_whisperer_level = 0,
    int8_t explosives_level = 0,
    int8_t first_aid_level = 0,
    int8_t sneaky_shit_level = 0,
    int8_t weird_science_level = 0,
    int8_t mechanics_level = 0,
    int8_t survival_level = 0,
    int8_t weapon_modding_level = 0,
    int8_t barter_level = 0,
    int8_t leadership_level = 0) {
  FB_SkillBuilder builder_(_fbb);
  builder_.add_skill_points(skill_points);
  builder_.add_leadership_level(leadership_level);
  builder_.add_barter_level(barter_level);
  builder_.add_weapon_modding_level(weapon_modding_level);
  builder_.add_survival_level(survival_level);
  builder_.add_mechanics_level(mechanics_level);
  builder_.add_weird_science_level(weird_science_level);
  builder_.add_sneaky_shit_level(sneaky_shit_level);
  builder_.add_first_aid_level(first_aid_level);
  builder_.add_explosives_level(explosives_level);
  builder_.add_animal_whisperer_level(animal_whisperer_level);
  builder_.add_sniper_level(sniper_level);
  builder_.add_small_arms_level(small_arms_level);
  builder_.add_melee_level(melee_level);
  builder_.add_brawling_level(brawling_level);
  builder_.add_big_guns_level(big_guns_level);
  builder_.add_automatic_level(automatic_level);
  return builder_.Finish();
}

}  // namespace fbSkill

#endif  // FLATBUFFERS_GENERATED_SKILLSERIALIZATIONFB_FBSKILL_H_
