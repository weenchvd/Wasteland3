// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PLAINTEXTTEXTFB_FBPLAINTEXT_H_
#define FLATBUFFERS_GENERATED_PLAINTEXTTEXTFB_FBPLAINTEXT_H_

#include "flatbuffers/flatbuffers.h"

#include "languageBundleFB_generated.h"

namespace fbPlainText {

struct FB_PlainTextTextCommon;
struct FB_PlainTextTextCommonBuilder;

struct FB_PlainTextText;
struct FB_PlainTextTextBuilder;

struct FB_PlainTextTextCommon FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_PlainTextTextCommonBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PRICE = 4
  };
  const fbCommon::FB_LanguageBundle *price() const {
    return GetPointer<const fbCommon::FB_LanguageBundle *>(VT_PRICE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_PRICE) &&
           verifier.VerifyTable(price()) &&
           verifier.EndTable();
  }
};

struct FB_PlainTextTextCommonBuilder {
  typedef FB_PlainTextTextCommon Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_price(flatbuffers::Offset<fbCommon::FB_LanguageBundle> price) {
    fbb_.AddOffset(FB_PlainTextTextCommon::VT_PRICE, price);
  }
  explicit FB_PlainTextTextCommonBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_PlainTextTextCommon> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_PlainTextTextCommon>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_PlainTextTextCommon> CreateFB_PlainTextTextCommon(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbCommon::FB_LanguageBundle> price = 0) {
  FB_PlainTextTextCommonBuilder builder_(_fbb);
  builder_.add_price(price);
  return builder_.Finish();
}

struct FB_PlainTextText FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FB_PlainTextTextBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_COMMON = 4
  };
  const fbPlainText::FB_PlainTextTextCommon *common() const {
    return GetPointer<const fbPlainText::FB_PlainTextTextCommon *>(VT_COMMON);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_COMMON) &&
           verifier.VerifyTable(common()) &&
           verifier.EndTable();
  }
};

struct FB_PlainTextTextBuilder {
  typedef FB_PlainTextText Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_common(flatbuffers::Offset<fbPlainText::FB_PlainTextTextCommon> common) {
    fbb_.AddOffset(FB_PlainTextText::VT_COMMON, common);
  }
  explicit FB_PlainTextTextBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FB_PlainTextText> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FB_PlainTextText>(end);
    return o;
  }
};

inline flatbuffers::Offset<FB_PlainTextText> CreateFB_PlainTextText(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<fbPlainText::FB_PlainTextTextCommon> common = 0) {
  FB_PlainTextTextBuilder builder_(_fbb);
  builder_.add_common(common);
  return builder_.Finish();
}

inline const fbPlainText::FB_PlainTextText *GetFB_PlainTextText(const void *buf) {
  return flatbuffers::GetRoot<fbPlainText::FB_PlainTextText>(buf);
}

inline const fbPlainText::FB_PlainTextText *GetSizePrefixedFB_PlainTextText(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<fbPlainText::FB_PlainTextText>(buf);
}

inline const char *FB_PlainTextTextIdentifier() {
  return "PT_T";
}

inline bool FB_PlainTextTextBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FB_PlainTextTextIdentifier());
}

inline bool VerifyFB_PlainTextTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<fbPlainText::FB_PlainTextText>(FB_PlainTextTextIdentifier());
}

inline bool VerifySizePrefixedFB_PlainTextTextBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<fbPlainText::FB_PlainTextText>(FB_PlainTextTextIdentifier());
}

inline const char *FB_PlainTextTextExtension() {
  return "bundle";
}

inline void FinishFB_PlainTextTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbPlainText::FB_PlainTextText> root) {
  fbb.Finish(root, FB_PlainTextTextIdentifier());
}

inline void FinishSizePrefixedFB_PlainTextTextBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<fbPlainText::FB_PlainTextText> root) {
  fbb.FinishSizePrefixed(root, FB_PlainTextTextIdentifier());
}

}  // namespace fbPlainText

#endif  // FLATBUFFERS_GENERATED_PLAINTEXTTEXTFB_FBPLAINTEXT_H_