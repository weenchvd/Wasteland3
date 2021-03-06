// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WEAPONMODFB_FBWEAPONMOD_H_
#define FLATBUFFERS_GENERATED_WEAPONMODFB_FBWEAPONMOD_H_

#include "flatbuffers/flatbuffers.h"

#include "weaponModModelFB_generated.h"

namespace fbWeaponMod {

struct FB_WeaponMod;
struct FB_WeaponModBuilder;

struct FB_WeaponMod FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_WeaponModBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MODEL = 4
  };
  fbWeaponMod::FB_WeaponModModel model() const {
    return static_cast<fbWeaponMod::FB_WeaponModModel>(GetField<int16_t>(VT_MODEL, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_MODEL) &&
           verifier.EndTable();
  }
};

struct FB_WeaponModBuilder {
  typedef FB_WeaponMod Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_model(fbWeaponMod::FB_WeaponModModel model) {
    fbb_.AddElement<int16_t>(FB_WeaponMod::VT_MODEL, static_cast<int16_t>(model), 0);
  }
  explicit FB_WeaponModBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_WeaponMod> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_WeaponMod>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_WeaponMod> CreateFB_WeaponMod(
    flatbuffers::FlatBufferBuilder &_fbb,
    fbWeaponMod::FB_WeaponModModel model = fbWeaponMod::FB_WeaponModModel_INVALID) {
  FB_WeaponModBuilder builder_(_fbb);
  builder_.add_model(model);
  return builder_.Finish();
}

}  // namespace fbWeaponMod

#endif  // FLATBUFFERS_GENERATED_WEAPONMODFB_FBWEAPONMOD_H_
