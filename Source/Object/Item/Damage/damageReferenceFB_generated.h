// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DAMAGEREFERENCEFB_FBDAMAGE_H_
#define FLATBUFFERS_GENERATED_DAMAGEREFERENCEFB_FBDAMAGE_H_

#include "flatbuffers/flatbuffers.h"

#include "damageTypeFB_generated.h"
#include "languageBundleFB_generated.h"

namespace fbDamage {

struct FB_DamageReference;
struct FB_DamageReferenceBuilder;

struct FB_DamageReferenceContainer;
struct FB_DamageReferenceContainerBuilder;

struct FB_DamageReference FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_DamageReferenceBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_DMG_TYPE = 4,
    VT_NAME = 6,
    VT_DESCRIP = 8,
    VT_DAMAGE_VS_ROBOTS = 10,
    VT_DAMAGE_VS_VEHICLES = 12,
    VT_DAMAGE_VS_HUMANS = 14,
    VT_DAMAGE_VS_ANIMALS = 16,
    VT_DAMAGE_VS_MUTANTS = 18
  };
  fbDamage::FB_DamageType dmg_type() const {
    return static_cast<fbDamage::FB_DamageType>(GetField<int8_t>(VT_DMG_TYPE, 0));
  }
  const fbCommon::FB_LanguageBundle *name() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_NAME);
  }
  const fbCommon::FB_LanguageBundle *descrip() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_DESCRIP);
  }
  int16_t damage_vs_robots() const {
    return GetField<int16_t>(VT_DAMAGE_VS_ROBOTS, 0);
  }
  int16_t damage_vs_vehicles() const {
    return GetField<int16_t>(VT_DAMAGE_VS_VEHICLES, 0);
  }
  int16_t damage_vs_humans() const {
    return GetField<int16_t>(VT_DAMAGE_VS_HUMANS, 0);
  }
  int16_t damage_vs_animals() const {
    return GetField<int16_t>(VT_DAMAGE_VS_ANIMALS, 0);
  }
  int16_t damage_vs_mutants() const {
    return GetField<int16_t>(VT_DAMAGE_VS_MUTANTS, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_DMG_TYPE) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyTable(name()) &&
           VerifyOffset(verifier, VT_DESCRIP) &&
           verifier.VerifyTable(descrip()) &&
           VerifyField<int16_t>(verifier, VT_DAMAGE_VS_ROBOTS) &&
           VerifyField<int16_t>(verifier, VT_DAMAGE_VS_VEHICLES) &&
           VerifyField<int16_t>(verifier, VT_DAMAGE_VS_HUMANS) &&
           VerifyField<int16_t>(verifier, VT_DAMAGE_VS_ANIMALS) &&
           VerifyField<int16_t>(verifier, VT_DAMAGE_VS_MUTANTS) &&
           verifier.EndTable();
  }
};

struct FB_DamageReferenceBuilder {
  typedef FB_DamageReference Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_dmg_type(fbDamage::FB_DamageType dmg_type) {
    fbb_.AddElement<int8_t>(FB_DamageReference::VT_DMG_TYPE, static_cast<int8_t>(dmg_type), 0);
  }
  void add_name(flatbuffers::Offset<fbCommon::FB_LanguageBundle> name) {
    fbb_.AddOffset(FB_DamageReference::VT_NAME, name);
  }
  void add_descrip(flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip) {
    fbb_.AddOffset(FB_DamageReference::VT_DESCRIP, descrip);
  }
  void add_damage_vs_robots(int16_t damage_vs_robots) {
    fbb_.AddElement<int16_t>(FB_DamageReference::VT_DAMAGE_VS_ROBOTS, damage_vs_robots, 0);
  }
  void add_damage_vs_vehicles(int16_t damage_vs_vehicles) {
    fbb_.AddElement<int16_t>(FB_DamageReference::VT_DAMAGE_VS_VEHICLES, damage_vs_vehicles, 0);
  }
  void add_damage_vs_humans(int16_t damage_vs_humans) {
    fbb_.AddElement<int16_t>(FB_DamageReference::VT_DAMAGE_VS_HUMANS, damage_vs_humans, 0);
  }
  void add_damage_vs_animals(int16_t damage_vs_animals) {
    fbb_.AddElement<int16_t>(FB_DamageReference::VT_DAMAGE_VS_ANIMALS, damage_vs_animals, 0);
  }
  void add_damage_vs_mutants(int16_t damage_vs_mutants) {
    fbb_.AddElement<int16_t>(FB_DamageReference::VT_DAMAGE_VS_MUTANTS, damage_vs_mutants, 0);
  }
  explicit FB_DamageReferenceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_DamageReference> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_DamageReference>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_DamageReference> CreateFB_DamageReference(
    flatbuffers::FlatBufferBuilder &_fbb,
    fbDamage::FB_DamageType dmg_type = fbDamage::FB_DamageType_INVALID,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> name = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> descrip = 0,
    int16_t damage_vs_robots = 0,
    int16_t damage_vs_vehicles = 0,
    int16_t damage_vs_humans = 0,
    int16_t damage_vs_animals = 0,
    int16_t damage_vs_mutants = 0) {
  FB_DamageReferenceBuilder builder_(_fbb);
  builder_.add_descrip(descrip);
  builder_.add_name(name);
  builder_.add_damage_vs_mutants(damage_vs_mutants);
  builder_.add_damage_vs_animals(damage_vs_animals);
  builder_.add_damage_vs_humans(damage_vs_humans);
  builder_.add_damage_vs_vehicles(damage_vs_vehicles);
  builder_.add_damage_vs_robots(damage_vs_robots);
  builder_.add_dmg_type(dmg_type);
  return builder_.Finish();
}

struct FB_DamageReferenceContainer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_DamageReferenceContainerBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_REFS = 4,
    VT_REF_DEFAULT = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<fbDamage::FB_DamageReference>> *refs() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<fbDamage::FB_DamageReference>> *>(VT_REFS);
  }
  const fbDamage::FB_DamageReference *ref_default() const {
    return GetPointer<const fbDamage::FB_DamageReference *>(VT_REF_DEFAULT);
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

struct FB_DamageReferenceContainerBuilder {
  typedef FB_DamageReferenceContainer Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_refs(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbDamage::FB_DamageReference>>> refs) {
    fbb_.AddOffset(FB_DamageReferenceContainer::VT_REFS, refs);
  }
  void add_ref_default(flatbuffers::Offset<fbDamage::FB_DamageReference> ref_default) {
    fbb_.AddOffset(FB_DamageReferenceContainer::VT_REF_DEFAULT, ref_default);
  }
  explicit FB_DamageReferenceContainerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_DamageReferenceContainer> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_DamageReferenceContainer>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_DamageReferenceContainer> CreateFB_DamageReferenceContainer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fbDamage::FB_DamageReference>>> refs = 0,
    flatbuffers::Offset<fbDamage::FB_DamageReference> ref_default = 0) {
  FB_DamageReferenceContainerBuilder builder_(_fbb);
  builder_.add_ref_default(ref_default);
  builder_.add_refs(refs);
  return builder_.Finish();
}

inline flatbuffers::Offset<FB_DamageReferenceContainer> CreateFB_DamageReferenceContainerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<fbDamage::FB_DamageReference>> *refs = nullptr,
    flatbuffers::Offset<fbDamage::FB_DamageReference> ref_default = 0) {
  auto refs__ = refs ? _fbb.CreateVector<flatbuffers::Offset<fbDamage::FB_DamageReference>>(*refs) : 0;
  return fbDamage::CreateFB_DamageReferenceContainer(
      _fbb,
      refs__,
      ref_default);
}

inline const fbDamage::FB_DamageReferenceContainer *GetFB_DamageReferenceContainer(const void *buf) {
  return flatbuffers::GetRoot<fbDamage::FB_DamageReferenceContainer>(buf);
}

inline const fbDamage::FB_DamageReferenceContainer *GetSizePrefixedFB_DamageReferenceContainer(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbDamage::FB_DamageReferenceContainer>(buf);
}

inline const char *FB_DamageReferenceContainerIdentifier() {
  return "DMGR";
}

inline bool FB_DamageReferenceContainerBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_DamageReferenceContainerIdentifier());
}

inline bool VerifyFB_DamageReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbDamage::FB_DamageReferenceContainer>(FB_DamageReferenceContainerIdentifier());
}

inline bool VerifySizePrefixedFB_DamageReferenceContainerBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbDamage::FB_DamageReferenceContainer>(FB_DamageReferenceContainerIdentifier());
}

inline const char *FB_DamageReferenceContainerExtension() {
  return "bundle";
}

inline void FinishFB_DamageReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbDamage::FB_DamageReferenceContainer> root) {
  fbb.Finish(root, FB_DamageReferenceContainerIdentifier());
}

inline void FinishSizePrefixedFB_DamageReferenceContainerBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbDamage::FB_DamageReferenceContainer> root) {
  fbb.FinishSizePrefixed(root, FB_DamageReferenceContainerIdentifier());
}

}  // namespace fbDamage

#endif  // FLATBUFFERS_GENERATED_DAMAGEREFERENCEFB_FBDAMAGE_H_