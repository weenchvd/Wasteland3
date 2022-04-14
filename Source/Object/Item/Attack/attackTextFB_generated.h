// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ATTACKTEXTFB_FBATTACK_H_
#define FLATBUFFERS_GENERATED_ATTACKTEXTFB_FBATTACK_H_

#include "flatbuffers/flatbuffers.h"

#include "languageBundleFB_generated.h"

namespace fbAttack {

struct FB_AttackTextType;
struct FB_AttackTextTypeBuilder;

struct FB_AttackTextCommon;
struct FB_AttackTextCommonBuilder;

struct FB_AttackText;
struct FB_AttackTextBuilder;

struct FB_AttackTextType FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_AttackTextTypeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SINGLE_TARGET = 4,
    VT_CHAIN_OF_SINGLE_TARGETS = 6,
    VT_STRAIGHT_LINE = 8,
    VT_CONICAL_AREA_BEHIND_TARGET = 10,
    VT_CONICAL_AREA = 12,
    VT_REMOTE_CIRCULAR_AREA = 14,
    VT_CIRCULAR_AREA = 16
  };
  const fbCommon::FB_LanguageBundle *single_target() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_SINGLE_TARGET);
  }
  const fbCommon::FB_LanguageBundle *chain_of_single_targets() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CHAIN_OF_SINGLE_TARGETS);
  }
  const fbCommon::FB_LanguageBundle *straight_line() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_STRAIGHT_LINE);
  }
  const fbCommon::FB_LanguageBundle *conical_area_behind_target() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CONICAL_AREA_BEHIND_TARGET);
  }
  const fbCommon::FB_LanguageBundle *conical_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CONICAL_AREA);
  }
  const fbCommon::FB_LanguageBundle *remote_circular_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_REMOTE_CIRCULAR_AREA);
  }
  const fbCommon::FB_LanguageBundle *circular_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_CIRCULAR_AREA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_SINGLE_TARGET) &&
           verifier.VerifyTable(single_target()) &&
           VerifyOffset(verifier, VT_CHAIN_OF_SINGLE_TARGETS) &&
           verifier.VerifyTable(chain_of_single_targets()) &&
           VerifyOffset(verifier, VT_STRAIGHT_LINE) &&
           verifier.VerifyTable(straight_line()) &&
           VerifyOffset(verifier, VT_CONICAL_AREA_BEHIND_TARGET) &&
           verifier.VerifyTable(conical_area_behind_target()) &&
           VerifyOffset(verifier, VT_CONICAL_AREA) &&
           verifier.VerifyTable(conical_area()) &&
           VerifyOffset(verifier, VT_REMOTE_CIRCULAR_AREA) &&
           verifier.VerifyTable(remote_circular_area()) &&
           VerifyOffset(verifier, VT_CIRCULAR_AREA) &&
           verifier.VerifyTable(circular_area()) &&
           verifier.EndTable();
  }
};

struct FB_AttackTextTypeBuilder {
  typedef FB_AttackTextType Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_single_target(flatbuffers::Offset<fbCommon::FB_LanguageBundle> single_target) {
    fbb_.AddOffset(FB_AttackTextType::VT_SINGLE_TARGET, single_target);
  }
  void add_chain_of_single_targets(flatbuffers::Offset<fbCommon::FB_LanguageBundle> chain_of_single_targets) {
    fbb_.AddOffset(FB_AttackTextType::VT_CHAIN_OF_SINGLE_TARGETS, chain_of_single_targets);
  }
  void add_straight_line(flatbuffers::Offset<fbCommon::FB_LanguageBundle> straight_line) {
    fbb_.AddOffset(FB_AttackTextType::VT_STRAIGHT_LINE, straight_line);
  }
  void add_conical_area_behind_target(flatbuffers::Offset<fbCommon::FB_LanguageBundle> conical_area_behind_target) {
    fbb_.AddOffset(FB_AttackTextType::VT_CONICAL_AREA_BEHIND_TARGET, conical_area_behind_target);
  }
  void add_conical_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> conical_area) {
    fbb_.AddOffset(FB_AttackTextType::VT_CONICAL_AREA, conical_area);
  }
  void add_remote_circular_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> remote_circular_area) {
    fbb_.AddOffset(FB_AttackTextType::VT_REMOTE_CIRCULAR_AREA, remote_circular_area);
  }
  void add_circular_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> circular_area) {
    fbb_.AddOffset(FB_AttackTextType::VT_CIRCULAR_AREA, circular_area);
  }
  explicit FB_AttackTextTypeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_AttackTextType> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_AttackTextType>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_AttackTextType> CreateFB_AttackTextType(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> single_target = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> chain_of_single_targets = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> straight_line = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> conical_area_behind_target = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> conical_area = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> remote_circular_area = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> circular_area = 0) {
  FB_AttackTextTypeBuilder builder_(_fbb);
  builder_.add_circular_area(circular_area);
  builder_.add_remote_circular_area(remote_circular_area);
  builder_.add_conical_area(conical_area);
  builder_.add_conical_area_behind_target(conical_area_behind_target);
  builder_.add_straight_line(straight_line);
  builder_.add_chain_of_single_targets(chain_of_single_targets);
  builder_.add_single_target(single_target);
  return builder_.Finish();
}

struct FB_AttackTextCommon FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_AttackTextCommonBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ATTACK_TYPE = 4,
    VT_ATTACK_RANGE = 6,
    VT_RANGE_OF_BOUNCES = 8,
    VT_RANGE_OF_CONICAL_AREA = 10,
    VT_RADIUS_OF_CIRCULAR_AREA = 12,
    VT_QUANTITY_OF_BOUNCES = 14,
    VT_ANGLE_OF_CONICAL_AREA = 16,
    VT_POINT_BLANK = 18
  };
  const fbCommon::FB_LanguageBundle *attack_type() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_ATTACK_TYPE);
  }
  const fbCommon::FB_LanguageBundle *attack_range() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_ATTACK_RANGE);
  }
  const fbCommon::FB_LanguageBundle *range_of_bounces() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_RANGE_OF_BOUNCES);
  }
  const fbCommon::FB_LanguageBundle *range_of_conical_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_RANGE_OF_CONICAL_AREA);
  }
  const fbCommon::FB_LanguageBundle *radius_of_circular_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_RADIUS_OF_CIRCULAR_AREA);
  }
  const fbCommon::FB_LanguageBundle *quantity_of_bounces() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_QUANTITY_OF_BOUNCES);
  }
  const fbCommon::FB_LanguageBundle *angle_of_conical_area() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_ANGLE_OF_CONICAL_AREA);
  }
  const fbCommon::FB_LanguageBundle *point_blank() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_POINT_BLANK);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ATTACK_TYPE) &&
           verifier.VerifyTable(attack_type()) &&
           VerifyOffset(verifier, VT_ATTACK_RANGE) &&
           verifier.VerifyTable(attack_range()) &&
           VerifyOffset(verifier, VT_RANGE_OF_BOUNCES) &&
           verifier.VerifyTable(range_of_bounces()) &&
           VerifyOffset(verifier, VT_RANGE_OF_CONICAL_AREA) &&
           verifier.VerifyTable(range_of_conical_area()) &&
           VerifyOffset(verifier, VT_RADIUS_OF_CIRCULAR_AREA) &&
           verifier.VerifyTable(radius_of_circular_area()) &&
           VerifyOffset(verifier, VT_QUANTITY_OF_BOUNCES) &&
           verifier.VerifyTable(quantity_of_bounces()) &&
           VerifyOffset(verifier, VT_ANGLE_OF_CONICAL_AREA) &&
           verifier.VerifyTable(angle_of_conical_area()) &&
           VerifyOffset(verifier, VT_POINT_BLANK) &&
           verifier.VerifyTable(point_blank()) &&
           verifier.EndTable();
  }
};

struct FB_AttackTextCommonBuilder {
  typedef FB_AttackTextCommon Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_attack_type(flatbuffers::Offset<fbCommon::FB_LanguageBundle> attack_type) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_ATTACK_TYPE, attack_type);
  }
  void add_attack_range(flatbuffers::Offset<fbCommon::FB_LanguageBundle> attack_range) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_ATTACK_RANGE, attack_range);
  }
  void add_range_of_bounces(flatbuffers::Offset<fbCommon::FB_LanguageBundle> range_of_bounces) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_RANGE_OF_BOUNCES, range_of_bounces);
  }
  void add_range_of_conical_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> range_of_conical_area) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_RANGE_OF_CONICAL_AREA, range_of_conical_area);
  }
  void add_radius_of_circular_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> radius_of_circular_area) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_RADIUS_OF_CIRCULAR_AREA, radius_of_circular_area);
  }
  void add_quantity_of_bounces(flatbuffers::Offset<fbCommon::FB_LanguageBundle> quantity_of_bounces) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_QUANTITY_OF_BOUNCES, quantity_of_bounces);
  }
  void add_angle_of_conical_area(flatbuffers::Offset<fbCommon::FB_LanguageBundle> angle_of_conical_area) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_ANGLE_OF_CONICAL_AREA, angle_of_conical_area);
  }
  void add_point_blank(flatbuffers::Offset<fbCommon::FB_LanguageBundle> point_blank) {
    fbb_.AddOffset(FB_AttackTextCommon::VT_POINT_BLANK, point_blank);
  }
  explicit FB_AttackTextCommonBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_AttackTextCommon> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_AttackTextCommon>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_AttackTextCommon> CreateFB_AttackTextCommon(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> attack_type = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> attack_range = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> range_of_bounces = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> range_of_conical_area = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> radius_of_circular_area = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> quantity_of_bounces = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> angle_of_conical_area = 0,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> point_blank = 0) {
  FB_AttackTextCommonBuilder builder_(_fbb);
  builder_.add_point_blank(point_blank);
  builder_.add_angle_of_conical_area(angle_of_conical_area);
  builder_.add_quantity_of_bounces(quantity_of_bounces);
  builder_.add_radius_of_circular_area(radius_of_circular_area);
  builder_.add_range_of_conical_area(range_of_conical_area);
  builder_.add_range_of_bounces(range_of_bounces);
  builder_.add_attack_range(attack_range);
  builder_.add_attack_type(attack_type);
  return builder_.Finish();
}

struct FB_AttackText FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_AttackTextBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_COMMON = 6
  };
  const fbAttack::FB_AttackTextType *type() const {
    return GetPointer<const fbAttack::FB_AttackTextType *>(VT_TYPE);
  }
  const fbAttack::FB_AttackTextCommon *common() const {
    return GetPointer<const fbAttack::FB_AttackTextCommon *>(VT_COMMON);
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

struct FB_AttackTextBuilder {
  typedef FB_AttackText Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(flatbuffers::Offset<fbAttack::FB_AttackTextType> type) {
    fbb_.AddOffset(FB_AttackText::VT_TYPE, type);
  }
  void add_common(flatbuffers::Offset<fbAttack::FB_AttackTextCommon> common) {
    fbb_.AddOffset(FB_AttackText::VT_COMMON, common);
  }
  explicit FB_AttackTextBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_AttackText> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_AttackText>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_AttackText> CreateFB_AttackText(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbAttack::FB_AttackTextType> type = 0,
    flatbuffers::Offset<fbAttack::FB_AttackTextCommon> common = 0) {
  FB_AttackTextBuilder builder_(_fbb);
  builder_.add_common(common);
  builder_.add_type(type);
  return builder_.Finish();
}

inline const fbAttack::FB_AttackText *GetFB_AttackText(const void *buf) {
  return flatbuffers::GetRoot<fbAttack::FB_AttackText>(buf);
}

inline const fbAttack::FB_AttackText *GetSizePrefixedFB_AttackText(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbAttack::FB_AttackText>(buf);
}

inline const char *FB_AttackTextIdentifier() {
  return "ATKT";
}

inline bool FB_AttackTextBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_AttackTextIdentifier());
}

inline bool VerifyFB_AttackTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbAttack::FB_AttackText>(FB_AttackTextIdentifier());
}

inline bool VerifySizePrefixedFB_AttackTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbAttack::FB_AttackText>(FB_AttackTextIdentifier());
}

inline const char *FB_AttackTextExtension() {
  return "bundle";
}

inline void FinishFB_AttackTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbAttack::FB_AttackText> root) {
  fbb.Finish(root, FB_AttackTextIdentifier());
}

inline void FinishSizePrefixedFB_AttackTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbAttack::FB_AttackText> root) {
  fbb.FinishSizePrefixed(root, FB_AttackTextIdentifier());
}

}  // namespace fbAttack

#endif  // FLATBUFFERS_GENERATED_ATTACKTEXTFB_FBATTACK_H_
