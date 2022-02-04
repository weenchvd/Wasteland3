// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SKILLTEXTFB_GAME_OBJECT_FBSKILL_H_
#define FLATBUFFERS_GENERATED_SKILLTEXTFB_GAME_OBJECT_FBSKILL_H_

#include "flatbuffers/flatbuffers.h"

namespace Game {
namespace Object {
namespace fbSkill {

struct FB_SkillTextType;
struct FB_SkillTextTypeBuilder;

struct FB_SkillTextGroup;
struct FB_SkillTextGroupBuilder;

struct FB_LanguageBundle;
struct FB_LanguageBundleBuilder;

struct FB_SkillText;
struct FB_SkillTextBuilder;

struct FB_SkillTextType FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_SkillTextTypeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_AUTOMATIC_WEAPONS = 4,
    VT_BIG_GUNS = 6,
    VT_BRAWLING = 8,
    VT_MELEE_COMBAT = 10,
    VT_SMALL_ARMS = 12,
    VT_SNIPER_RIFLES = 14,
    VT_ANIMAL_WHISPERER = 16,
    VT_EXPLOSIVES = 18,
    VT_FIRST_AID = 20,
    VT_SNEAKY_SHIT = 22,
    VT_WEIRD_SCIENCE = 24,
    VT_ARMOR_MODDING = 26,
    VT_LOCKPICKING = 28,
    VT_NERD_STUFF = 30,
    VT_MECHANICS = 32,
    VT_SURVIVAL = 34,
    VT_TOASTER_REPAIR = 36,
    VT_WEAPON_MODDING = 38,
    VT_BARTER = 40,
    VT_HARD_ASS = 42,
    VT_KISS_ASS = 44,
    VT_LEADERSHIP = 46
  };
  const flatbuffers::String *automatic_weapons() const {
    return GetPointer<const flatbuffers::String *>(VT_AUTOMATIC_WEAPONS);
  }
  const flatbuffers::String *big_guns() const {
    return GetPointer<const flatbuffers::String *>(VT_BIG_GUNS);
  }
  const flatbuffers::String *brawling() const {
    return GetPointer<const flatbuffers::String *>(VT_BRAWLING);
  }
  const flatbuffers::String *melee_combat() const {
    return GetPointer<const flatbuffers::String *>(VT_MELEE_COMBAT);
  }
  const flatbuffers::String *small_arms() const {
    return GetPointer<const flatbuffers::String *>(VT_SMALL_ARMS);
  }
  const flatbuffers::String *sniper_rifles() const {
    return GetPointer<const flatbuffers::String *>(VT_SNIPER_RIFLES);
  }
  const flatbuffers::String *animal_whisperer() const {
    return GetPointer<const flatbuffers::String *>(VT_ANIMAL_WHISPERER);
  }
  const flatbuffers::String *explosives() const {
    return GetPointer<const flatbuffers::String *>(VT_EXPLOSIVES);
  }
  const flatbuffers::String *first_aid() const {
    return GetPointer<const flatbuffers::String *>(VT_FIRST_AID);
  }
  const flatbuffers::String *sneaky_shit() const {
    return GetPointer<const flatbuffers::String *>(VT_SNEAKY_SHIT);
  }
  const flatbuffers::String *weird_science() const {
    return GetPointer<const flatbuffers::String *>(VT_WEIRD_SCIENCE);
  }
  const flatbuffers::String *armor_modding() const {
    return GetPointer<const flatbuffers::String *>(VT_ARMOR_MODDING);
  }
  const flatbuffers::String *lockpicking() const {
    return GetPointer<const flatbuffers::String *>(VT_LOCKPICKING);
  }
  const flatbuffers::String *nerd_stuff() const {
    return GetPointer<const flatbuffers::String *>(VT_NERD_STUFF);
  }
  const flatbuffers::String *mechanics() const {
    return GetPointer<const flatbuffers::String *>(VT_MECHANICS);
  }
  const flatbuffers::String *survival() const {
    return GetPointer<const flatbuffers::String *>(VT_SURVIVAL);
  }
  const flatbuffers::String *toaster_repair() const {
    return GetPointer<const flatbuffers::String *>(VT_TOASTER_REPAIR);
  }
  const flatbuffers::String *weapon_modding() const {
    return GetPointer<const flatbuffers::String *>(VT_WEAPON_MODDING);
  }
  const flatbuffers::String *barter() const {
    return GetPointer<const flatbuffers::String *>(VT_BARTER);
  }
  const flatbuffers::String *hard_ass() const {
    return GetPointer<const flatbuffers::String *>(VT_HARD_ASS);
  }
  const flatbuffers::String *kiss_ass() const {
    return GetPointer<const flatbuffers::String *>(VT_KISS_ASS);
  }
  const flatbuffers::String *leadership() const {
    return GetPointer<const flatbuffers::String *>(VT_LEADERSHIP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_AUTOMATIC_WEAPONS) &&
           verifier.VerifyString(automatic_weapons()) &&
           VerifyOffset(verifier, VT_BIG_GUNS) &&
           verifier.VerifyString(big_guns()) &&
           VerifyOffset(verifier, VT_BRAWLING) &&
           verifier.VerifyString(brawling()) &&
           VerifyOffset(verifier, VT_MELEE_COMBAT) &&
           verifier.VerifyString(melee_combat()) &&
           VerifyOffset(verifier, VT_SMALL_ARMS) &&
           verifier.VerifyString(small_arms()) &&
           VerifyOffset(verifier, VT_SNIPER_RIFLES) &&
           verifier.VerifyString(sniper_rifles()) &&
           VerifyOffset(verifier, VT_ANIMAL_WHISPERER) &&
           verifier.VerifyString(animal_whisperer()) &&
           VerifyOffset(verifier, VT_EXPLOSIVES) &&
           verifier.VerifyString(explosives()) &&
           VerifyOffset(verifier, VT_FIRST_AID) &&
           verifier.VerifyString(first_aid()) &&
           VerifyOffset(verifier, VT_SNEAKY_SHIT) &&
           verifier.VerifyString(sneaky_shit()) &&
           VerifyOffset(verifier, VT_WEIRD_SCIENCE) &&
           verifier.VerifyString(weird_science()) &&
           VerifyOffset(verifier, VT_ARMOR_MODDING) &&
           verifier.VerifyString(armor_modding()) &&
           VerifyOffset(verifier, VT_LOCKPICKING) &&
           verifier.VerifyString(lockpicking()) &&
           VerifyOffset(verifier, VT_NERD_STUFF) &&
           verifier.VerifyString(nerd_stuff()) &&
           VerifyOffset(verifier, VT_MECHANICS) &&
           verifier.VerifyString(mechanics()) &&
           VerifyOffset(verifier, VT_SURVIVAL) &&
           verifier.VerifyString(survival()) &&
           VerifyOffset(verifier, VT_TOASTER_REPAIR) &&
           verifier.VerifyString(toaster_repair()) &&
           VerifyOffset(verifier, VT_WEAPON_MODDING) &&
           verifier.VerifyString(weapon_modding()) &&
           VerifyOffset(verifier, VT_BARTER) &&
           verifier.VerifyString(barter()) &&
           VerifyOffset(verifier, VT_HARD_ASS) &&
           verifier.VerifyString(hard_ass()) &&
           VerifyOffset(verifier, VT_KISS_ASS) &&
           verifier.VerifyString(kiss_ass()) &&
           VerifyOffset(verifier, VT_LEADERSHIP) &&
           verifier.VerifyString(leadership()) &&
           verifier.EndTable();
  }
};

struct FB_SkillTextTypeBuilder {
  typedef FB_SkillTextType Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_automatic_weapons(flatbuffers::Offset<flatbuffers::String> automatic_weapons) {
    fbb_.AddOffset(FB_SkillTextType::VT_AUTOMATIC_WEAPONS, automatic_weapons);
  }
  void add_big_guns(flatbuffers::Offset<flatbuffers::String> big_guns) {
    fbb_.AddOffset(FB_SkillTextType::VT_BIG_GUNS, big_guns);
  }
  void add_brawling(flatbuffers::Offset<flatbuffers::String> brawling) {
    fbb_.AddOffset(FB_SkillTextType::VT_BRAWLING, brawling);
  }
  void add_melee_combat(flatbuffers::Offset<flatbuffers::String> melee_combat) {
    fbb_.AddOffset(FB_SkillTextType::VT_MELEE_COMBAT, melee_combat);
  }
  void add_small_arms(flatbuffers::Offset<flatbuffers::String> small_arms) {
    fbb_.AddOffset(FB_SkillTextType::VT_SMALL_ARMS, small_arms);
  }
  void add_sniper_rifles(flatbuffers::Offset<flatbuffers::String> sniper_rifles) {
    fbb_.AddOffset(FB_SkillTextType::VT_SNIPER_RIFLES, sniper_rifles);
  }
  void add_animal_whisperer(flatbuffers::Offset<flatbuffers::String> animal_whisperer) {
    fbb_.AddOffset(FB_SkillTextType::VT_ANIMAL_WHISPERER, animal_whisperer);
  }
  void add_explosives(flatbuffers::Offset<flatbuffers::String> explosives) {
    fbb_.AddOffset(FB_SkillTextType::VT_EXPLOSIVES, explosives);
  }
  void add_first_aid(flatbuffers::Offset<flatbuffers::String> first_aid) {
    fbb_.AddOffset(FB_SkillTextType::VT_FIRST_AID, first_aid);
  }
  void add_sneaky_shit(flatbuffers::Offset<flatbuffers::String> sneaky_shit) {
    fbb_.AddOffset(FB_SkillTextType::VT_SNEAKY_SHIT, sneaky_shit);
  }
  void add_weird_science(flatbuffers::Offset<flatbuffers::String> weird_science) {
    fbb_.AddOffset(FB_SkillTextType::VT_WEIRD_SCIENCE, weird_science);
  }
  void add_armor_modding(flatbuffers::Offset<flatbuffers::String> armor_modding) {
    fbb_.AddOffset(FB_SkillTextType::VT_ARMOR_MODDING, armor_modding);
  }
  void add_lockpicking(flatbuffers::Offset<flatbuffers::String> lockpicking) {
    fbb_.AddOffset(FB_SkillTextType::VT_LOCKPICKING, lockpicking);
  }
  void add_nerd_stuff(flatbuffers::Offset<flatbuffers::String> nerd_stuff) {
    fbb_.AddOffset(FB_SkillTextType::VT_NERD_STUFF, nerd_stuff);
  }
  void add_mechanics(flatbuffers::Offset<flatbuffers::String> mechanics) {
    fbb_.AddOffset(FB_SkillTextType::VT_MECHANICS, mechanics);
  }
  void add_survival(flatbuffers::Offset<flatbuffers::String> survival) {
    fbb_.AddOffset(FB_SkillTextType::VT_SURVIVAL, survival);
  }
  void add_toaster_repair(flatbuffers::Offset<flatbuffers::String> toaster_repair) {
    fbb_.AddOffset(FB_SkillTextType::VT_TOASTER_REPAIR, toaster_repair);
  }
  void add_weapon_modding(flatbuffers::Offset<flatbuffers::String> weapon_modding) {
    fbb_.AddOffset(FB_SkillTextType::VT_WEAPON_MODDING, weapon_modding);
  }
  void add_barter(flatbuffers::Offset<flatbuffers::String> barter) {
    fbb_.AddOffset(FB_SkillTextType::VT_BARTER, barter);
  }
  void add_hard_ass(flatbuffers::Offset<flatbuffers::String> hard_ass) {
    fbb_.AddOffset(FB_SkillTextType::VT_HARD_ASS, hard_ass);
  }
  void add_kiss_ass(flatbuffers::Offset<flatbuffers::String> kiss_ass) {
    fbb_.AddOffset(FB_SkillTextType::VT_KISS_ASS, kiss_ass);
  }
  void add_leadership(flatbuffers::Offset<flatbuffers::String> leadership) {
    fbb_.AddOffset(FB_SkillTextType::VT_LEADERSHIP, leadership);
  }
  explicit FB_SkillTextTypeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_SkillTextType> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_SkillTextType>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_SkillTextType> CreateFB_SkillTextType(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> automatic_weapons = 0,
    flatbuffers::Offset<flatbuffers::String> big_guns = 0,
    flatbuffers::Offset<flatbuffers::String> brawling = 0,
    flatbuffers::Offset<flatbuffers::String> melee_combat = 0,
    flatbuffers::Offset<flatbuffers::String> small_arms = 0,
    flatbuffers::Offset<flatbuffers::String> sniper_rifles = 0,
    flatbuffers::Offset<flatbuffers::String> animal_whisperer = 0,
    flatbuffers::Offset<flatbuffers::String> explosives = 0,
    flatbuffers::Offset<flatbuffers::String> first_aid = 0,
    flatbuffers::Offset<flatbuffers::String> sneaky_shit = 0,
    flatbuffers::Offset<flatbuffers::String> weird_science = 0,
    flatbuffers::Offset<flatbuffers::String> armor_modding = 0,
    flatbuffers::Offset<flatbuffers::String> lockpicking = 0,
    flatbuffers::Offset<flatbuffers::String> nerd_stuff = 0,
    flatbuffers::Offset<flatbuffers::String> mechanics = 0,
    flatbuffers::Offset<flatbuffers::String> survival = 0,
    flatbuffers::Offset<flatbuffers::String> toaster_repair = 0,
    flatbuffers::Offset<flatbuffers::String> weapon_modding = 0,
    flatbuffers::Offset<flatbuffers::String> barter = 0,
    flatbuffers::Offset<flatbuffers::String> hard_ass = 0,
    flatbuffers::Offset<flatbuffers::String> kiss_ass = 0,
    flatbuffers::Offset<flatbuffers::String> leadership = 0) {
  FB_SkillTextTypeBuilder builder_(_fbb);
  builder_.add_leadership(leadership);
  builder_.add_kiss_ass(kiss_ass);
  builder_.add_hard_ass(hard_ass);
  builder_.add_barter(barter);
  builder_.add_weapon_modding(weapon_modding);
  builder_.add_toaster_repair(toaster_repair);
  builder_.add_survival(survival);
  builder_.add_mechanics(mechanics);
  builder_.add_nerd_stuff(nerd_stuff);
  builder_.add_lockpicking(lockpicking);
  builder_.add_armor_modding(armor_modding);
  builder_.add_weird_science(weird_science);
  builder_.add_sneaky_shit(sneaky_shit);
  builder_.add_first_aid(first_aid);
  builder_.add_explosives(explosives);
  builder_.add_animal_whisperer(animal_whisperer);
  builder_.add_sniper_rifles(sniper_rifles);
  builder_.add_small_arms(small_arms);
  builder_.add_melee_combat(melee_combat);
  builder_.add_brawling(brawling);
  builder_.add_big_guns(big_guns);
  builder_.add_automatic_weapons(automatic_weapons);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_SkillTextType> CreateFB_SkillTextTypeDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *automatic_weapons = nullptr,
    const char *big_guns = nullptr,
    const char *brawling = nullptr,
    const char *melee_combat = nullptr,
    const char *small_arms = nullptr,
    const char *sniper_rifles = nullptr,
    const char *animal_whisperer = nullptr,
    const char *explosives = nullptr,
    const char *first_aid = nullptr,
    const char *sneaky_shit = nullptr,
    const char *weird_science = nullptr,
    const char *armor_modding = nullptr,
    const char *lockpicking = nullptr,
    const char *nerd_stuff = nullptr,
    const char *mechanics = nullptr,
    const char *survival = nullptr,
    const char *toaster_repair = nullptr,
    const char *weapon_modding = nullptr,
    const char *barter = nullptr,
    const char *hard_ass = nullptr,
    const char *kiss_ass = nullptr,
    const char *leadership = nullptr) {
  auto automatic_weapons__ = automatic_weapons ? _fbb.CreateString(automatic_weapons) : 0;
  auto big_guns__ = big_guns ? _fbb.CreateString(big_guns) : 0;
  auto brawling__ = brawling ? _fbb.CreateString(brawling) : 0;
  auto melee_combat__ = melee_combat ? _fbb.CreateString(melee_combat) : 0;
  auto small_arms__ = small_arms ? _fbb.CreateString(small_arms) : 0;
  auto sniper_rifles__ = sniper_rifles ? _fbb.CreateString(sniper_rifles) : 0;
  auto animal_whisperer__ = animal_whisperer ? _fbb.CreateString(animal_whisperer) : 0;
  auto explosives__ = explosives ? _fbb.CreateString(explosives) : 0;
  auto first_aid__ = first_aid ? _fbb.CreateString(first_aid) : 0;
  auto sneaky_shit__ = sneaky_shit ? _fbb.CreateString(sneaky_shit) : 0;
  auto weird_science__ = weird_science ? _fbb.CreateString(weird_science) : 0;
  auto armor_modding__ = armor_modding ? _fbb.CreateString(armor_modding) : 0;
  auto lockpicking__ = lockpicking ? _fbb.CreateString(lockpicking) : 0;
  auto nerd_stuff__ = nerd_stuff ? _fbb.CreateString(nerd_stuff) : 0;
  auto mechanics__ = mechanics ? _fbb.CreateString(mechanics) : 0;
  auto survival__ = survival ? _fbb.CreateString(survival) : 0;
  auto toaster_repair__ = toaster_repair ? _fbb.CreateString(toaster_repair) : 0;
  auto weapon_modding__ = weapon_modding ? _fbb.CreateString(weapon_modding) : 0;
  auto barter__ = barter ? _fbb.CreateString(barter) : 0;
  auto hard_ass__ = hard_ass ? _fbb.CreateString(hard_ass) : 0;
  auto kiss_ass__ = kiss_ass ? _fbb.CreateString(kiss_ass) : 0;
  auto leadership__ = leadership ? _fbb.CreateString(leadership) : 0;
  return Game::Object::fbSkill::CreateFB_SkillTextType(
      _fbb,
      automatic_weapons__,
      big_guns__,
      brawling__,
      melee_combat__,
      small_arms__,
      sniper_rifles__,
      animal_whisperer__,
      explosives__,
      first_aid__,
      sneaky_shit__,
      weird_science__,
      armor_modding__,
      lockpicking__,
      nerd_stuff__,
      mechanics__,
      survival__,
      toaster_repair__,
      weapon_modding__,
      barter__,
      hard_ass__,
      kiss_ass__,
      leadership__);
}

struct FB_SkillTextGroup FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_SkillTextGroupBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_COMBAT = 4,
    VT_GENERAL = 6,
    VT_EXPLORATION = 8,
    VT_SOCIAL = 10
  };
  const flatbuffers::String *combat() const {
    return GetPointer<const flatbuffers::String *>(VT_COMBAT);
  }
  const flatbuffers::String *general() const {
    return GetPointer<const flatbuffers::String *>(VT_GENERAL);
  }
  const flatbuffers::String *exploration() const {
    return GetPointer<const flatbuffers::String *>(VT_EXPLORATION);
  }
  const flatbuffers::String *social() const {
    return GetPointer<const flatbuffers::String *>(VT_SOCIAL);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_COMBAT) &&
           verifier.VerifyString(combat()) &&
           VerifyOffset(verifier, VT_GENERAL) &&
           verifier.VerifyString(general()) &&
           VerifyOffset(verifier, VT_EXPLORATION) &&
           verifier.VerifyString(exploration()) &&
           VerifyOffset(verifier, VT_SOCIAL) &&
           verifier.VerifyString(social()) &&
           verifier.EndTable();
  }
};

struct FB_SkillTextGroupBuilder {
  typedef FB_SkillTextGroup Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_combat(flatbuffers::Offset<flatbuffers::String> combat) {
    fbb_.AddOffset(FB_SkillTextGroup::VT_COMBAT, combat);
  }
  void add_general(flatbuffers::Offset<flatbuffers::String> general) {
    fbb_.AddOffset(FB_SkillTextGroup::VT_GENERAL, general);
  }
  void add_exploration(flatbuffers::Offset<flatbuffers::String> exploration) {
    fbb_.AddOffset(FB_SkillTextGroup::VT_EXPLORATION, exploration);
  }
  void add_social(flatbuffers::Offset<flatbuffers::String> social) {
    fbb_.AddOffset(FB_SkillTextGroup::VT_SOCIAL, social);
  }
  explicit FB_SkillTextGroupBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_SkillTextGroup> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_SkillTextGroup>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_SkillTextGroup> CreateFB_SkillTextGroup(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> combat = 0,
    flatbuffers::Offset<flatbuffers::String> general = 0,
    flatbuffers::Offset<flatbuffers::String> exploration = 0,
    flatbuffers::Offset<flatbuffers::String> social = 0) {
  FB_SkillTextGroupBuilder builder_(_fbb);
  builder_.add_social(social);
  builder_.add_exploration(exploration);
  builder_.add_general(general);
  builder_.add_combat(combat);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_SkillTextGroup> CreateFB_SkillTextGroupDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *combat = nullptr,
    const char *general = nullptr,
    const char *exploration = nullptr,
    const char *social = nullptr) {
  auto combat__ = combat ? _fbb.CreateString(combat) : 0;
  auto general__ = general ? _fbb.CreateString(general) : 0;
  auto exploration__ = exploration ? _fbb.CreateString(exploration) : 0;
  auto social__ = social ? _fbb.CreateString(social) : 0;
  return Game::Object::fbSkill::CreateFB_SkillTextGroup(
      _fbb,
      combat__,
      general__,
      exploration__,
      social__);
}

struct FB_LanguageBundle FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_LanguageBundleBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_DESCR = 6,
    VT_GROUP = 8
  };
  const Game::Object::fbSkill::FB_SkillTextType *name() const {
    return GetPointer<const Game::Object::fbSkill::FB_SkillTextType *>(VT_NAME);
  }
  const Game::Object::fbSkill::FB_SkillTextType *descr() const {
    return GetPointer<const Game::Object::fbSkill::FB_SkillTextType *>(VT_DESCR);
  }
  const Game::Object::fbSkill::FB_SkillTextGroup *group() const {
    return GetPointer<const Game::Object::fbSkill::FB_SkillTextGroup *>(VT_GROUP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyTable(name()) &&
           VerifyOffset(verifier, VT_DESCR) &&
           verifier.VerifyTable(descr()) &&
           VerifyOffset(verifier, VT_GROUP) &&
           verifier.VerifyTable(group()) &&
           verifier.EndTable();
  }
};

struct FB_LanguageBundleBuilder {
  typedef FB_LanguageBundle Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextType> name) {
    fbb_.AddOffset(FB_LanguageBundle::VT_NAME, name);
  }
  void add_descr(flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextType> descr) {
    fbb_.AddOffset(FB_LanguageBundle::VT_DESCR, descr);
  }
  void add_group(flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextGroup> group) {
    fbb_.AddOffset(FB_LanguageBundle::VT_GROUP, group);
  }
  explicit FB_LanguageBundleBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_LanguageBundle> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_LanguageBundle>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_LanguageBundle> CreateFB_LanguageBundle(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextType> name = 0,
    flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextType> descr = 0,
    flatbuffers::Offset<Game::Object::fbSkill::FB_SkillTextGroup> group = 0) {
  FB_LanguageBundleBuilder builder_(_fbb);
  builder_.add_group(group);
  builder_.add_descr(descr);
  builder_.add_name(name);
  return builder_.Finish();
}

struct FB_SkillText FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_SkillTextBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_EN = 4,
    VT_RU = 6
  };
  const Game::Object::fbSkill::FB_LanguageBundle *en() const {
    return GetPointer<const Game::Object::fbSkill::FB_LanguageBundle *>(VT_EN);
  }
  const Game::Object::fbSkill::FB_LanguageBundle *ru() const {
    return GetPointer<const Game::Object::fbSkill::FB_LanguageBundle *>(VT_RU);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_EN) &&
           verifier.VerifyTable(en()) &&
           VerifyOffset(verifier, VT_RU) &&
           verifier.VerifyTable(ru()) &&
           verifier.EndTable();
  }
};

struct FB_SkillTextBuilder {
  typedef FB_SkillText Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_en(flatbuffers::Offset<Game::Object::fbSkill::FB_LanguageBundle> en) {
    fbb_.AddOffset(FB_SkillText::VT_EN, en);
  }
  void add_ru(flatbuffers::Offset<Game::Object::fbSkill::FB_LanguageBundle> ru) {
    fbb_.AddOffset(FB_SkillText::VT_RU, ru);
  }
  explicit FB_SkillTextBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_SkillText> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_SkillText>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_SkillText> CreateFB_SkillText(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Game::Object::fbSkill::FB_LanguageBundle> en = 0,
    flatbuffers::Offset<Game::Object::fbSkill::FB_LanguageBundle> ru = 0) {
  FB_SkillTextBuilder builder_(_fbb);
  builder_.add_ru(ru);
  builder_.add_en(en);
  return builder_.Finish();
}

inline const Game::Object::fbSkill::FB_SkillText *GetFB_SkillText(const void *buf) {
  return flatbuffers::GetRoot<Game::Object::fbSkill::FB_SkillText>(buf);
}

inline const Game::Object::fbSkill::FB_SkillText *GetSizePrefixedFB_SkillText(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Game::Object::fbSkill::FB_SkillText>(buf);
}

inline const char *FB_SkillTextIdentifier() {
  return "SKLT";
}

inline bool FB_SkillTextBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_SkillTextIdentifier());
}

inline bool VerifyFB_SkillTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Game::Object::fbSkill::FB_SkillText>(FB_SkillTextIdentifier());
}

inline bool VerifySizePrefixedFB_SkillTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Game::Object::fbSkill::FB_SkillText>(FB_SkillTextIdentifier());
}

inline const char *FB_SkillTextExtension() {
  return "bundle";
}

inline void FinishFB_SkillTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Game::Object::fbSkill::FB_SkillText> root) {
  fbb.Finish(root, FB_SkillTextIdentifier());
}

inline void FinishSizePrefixedFB_SkillTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Game::Object::fbSkill::FB_SkillText> root) {
  fbb.FinishSizePrefixed(root, FB_SkillTextIdentifier());
}

}  // namespace fbSkill
}  // namespace Object
}  // namespace Game

#endif  // FLATBUFFERS_GENERATED_SKILLTEXTFB_GAME_OBJECT_FBSKILL_H_
