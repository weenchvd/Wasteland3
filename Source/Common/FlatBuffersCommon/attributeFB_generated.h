// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ATTRIBUTEFB_FBATTRIBUTE_H_
#define FLATBUFFERS_GENERATED_ATTRIBUTEFB_FBATTRIBUTE_H_

#include "flatbuffers/flatbuffers.h"

namespace fbAttribute {

struct FB_Attribute;
struct FB_AttributeBuilder;

struct FB_Attribute FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_AttributeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ATTR_POINTS = 4,
    VT_COORD_LEVEL = 6,
    VT_LUCK_LEVEL = 8,
    VT_AWARE_LEVEL = 10,
    VT_STR_LEVEL = 12,
    VT_SPEED_LEVEL = 14,
    VT_INT_LEVEL = 16,
    VT_CHA_LEVEL = 18
  };
  int8_t attr_points() const {
    return GetField<int8_t>(VT_ATTR_POINTS, 0);
  }
  int8_t coord_level() const {
    return GetField<int8_t>(VT_COORD_LEVEL, 0);
  }
  int8_t luck_level() const {
    return GetField<int8_t>(VT_LUCK_LEVEL, 0);
  }
  int8_t aware_level() const {
    return GetField<int8_t>(VT_AWARE_LEVEL, 0);
  }
  int8_t str_level() const {
    return GetField<int8_t>(VT_STR_LEVEL, 0);
  }
  int8_t speed_level() const {
    return GetField<int8_t>(VT_SPEED_LEVEL, 0);
  }
  int8_t int_level() const {
    return GetField<int8_t>(VT_INT_LEVEL, 0);
  }
  int8_t cha_level() const {
    return GetField<int8_t>(VT_CHA_LEVEL, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_ATTR_POINTS) &&
           VerifyField<int8_t>(verifier, VT_COORD_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_LUCK_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_AWARE_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_STR_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_SPEED_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_INT_LEVEL) &&
           VerifyField<int8_t>(verifier, VT_CHA_LEVEL) &&
           verifier.EndTable();
  }
};

struct FB_AttributeBuilder {
  typedef FB_Attribute Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_attr_points(int8_t attr_points) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_ATTR_POINTS, attr_points, 0);
  }
  void add_coord_level(int8_t coord_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_COORD_LEVEL, coord_level, 0);
  }
  void add_luck_level(int8_t luck_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_LUCK_LEVEL, luck_level, 0);
  }
  void add_aware_level(int8_t aware_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_AWARE_LEVEL, aware_level, 0);
  }
  void add_str_level(int8_t str_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_STR_LEVEL, str_level, 0);
  }
  void add_speed_level(int8_t speed_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_SPEED_LEVEL, speed_level, 0);
  }
  void add_int_level(int8_t int_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_INT_LEVEL, int_level, 0);
  }
  void add_cha_level(int8_t cha_level) {
    fbb_.AddElement<int8_t>(FB_Attribute::VT_CHA_LEVEL, cha_level, 0);
  }
  explicit FB_AttributeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_Attribute> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_Attribute>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_Attribute> CreateFB_Attribute(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t attr_points = 0,
    int8_t coord_level = 0,
    int8_t luck_level = 0,
    int8_t aware_level = 0,
    int8_t str_level = 0,
    int8_t speed_level = 0,
    int8_t int_level = 0,
    int8_t cha_level = 0) {
  FB_AttributeBuilder builder_(_fbb);
  builder_.add_cha_level(cha_level);
  builder_.add_int_level(int_level);
  builder_.add_speed_level(speed_level);
  builder_.add_str_level(str_level);
  builder_.add_aware_level(aware_level);
  builder_.add_luck_level(luck_level);
  builder_.add_coord_level(coord_level);
  builder_.add_attr_points(attr_points);
  return builder_.Finish();
}

}  // namespace fbAttribute

#endif  // FLATBUFFERS_GENERATED_ATTRIBUTEFB_FBATTRIBUTE_H_
