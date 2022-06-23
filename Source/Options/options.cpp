
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"common.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffers/idl.h"
#include"flatbuffers/util.h"
#include"options.hpp"
#include"optionsAux.hpp"
#include"optionsFBSchema.hpp"
#include<assert.h>
#include<fstream>

namespace game {
namespace global {

using namespace std;

OptionLanguage::OptionLanguage() noexcept
    :
    subj_           {},
    curLang_        { language_t::EN },
    prevLang_       { language_t::EN }
{}

bool OptionLanguage::accept() noexcept
{
    if (isModified()) {
        prevLang_ = curLang_;
        return true;
    }
    return false;
}

void OptionLanguage::reject() noexcept
{
    if (isModified()) {
        curLang_ = prevLang_;
        subj_.notify(curLang_);
    }
}

void OptionLanguage::setLanguage(language_t lang) noexcept
{
    assert(common::isValidEnum(lang));
    if (curLang_ != lang) {
        curLang_ = lang;
        subj_.notify(curLang_);
    }
}

///************************************************************************************************

Options::Options()
    :
    optLang_{}
{
    initialize();
    try {
        loadOptionsFromFiles();
        saveOptionsToFiles();
    }
    catch (...) {}
}

void Options::initialize()
{
    OptionLanguageBiMap::initialize();
}

bool Options::isModified() const noexcept
{
    return optLang_.isModified();
}

void Options::acceptAll() noexcept
{
    bool changed{
        optLang_.accept()
    };
    if (changed) {
        saveOptionsToFiles();
    }
}

void Options::rejectAll() noexcept
{
    optLang_.reject();
}

bool Options::saveOptionsToFiles()
{
    return saveOptionsToJSON() && saveOptionsToBin();
}

bool Options::loadOptionsFromFiles()
{
    return loadOptionsFromJSON() || loadOptionsFromBin();
}

bool Options::saveOptionsToJSON()
{
    flatbuffers::FlatBufferBuilder builder{ saveOptions() };
    string jsonText;
    flatbuffers::Parser parser;
    parser.opts.strict_json = true;
    parser.opts.output_default_scalars_in_json = true;
    if (!parser.Parse(optionsStuff::optionsFBSchema)) return false;
    if (!flatbuffers::GenerateText(parser, builder.GetBufferPointer(), &jsonText)) return false;
    return flatbuffers::SaveFile(optionsJSONFileName_, jsonText, false);
}

bool Options::saveOptionsToBin()
{
    flatbuffers::FlatBufferBuilder builder{ saveOptions() };
    common::writeBinFlatBuffer(optionsBinFileName_,
        builder.GetBufferPointer(), builder.GetSize());
    return true;
}

flatbuffers::FlatBufferBuilder Options::saveOptions()
{
    using namespace fbOptions;
    flatbuffers::FlatBufferBuilder builder{ 1024 };
    FB_OptionsBuilder optBuilder{ builder };

    FB_Options_Language lang{ OptionLanguageBiMap::toRightType(optLang_.getLanguage()) };
    assert(lang != FB_Options_Language::FB_Options_Language_INVALID);
    optBuilder.add_language(lang);

    builder.Finish(optBuilder.Finish());
    return builder;
}

bool Options::loadOptionsFromJSON()
{
    string jsonText;
    bool ok{ flatbuffers::LoadFile(optionsJSONFileName_, false, &jsonText) };
    if (!ok) return false;

    flatbuffers::Parser parser;
    parser.opts.strict_json = true;
    parser.opts.output_default_scalars_in_json = true;
    ok = parser.Parse(optionsStuff::optionsFBSchema) &&
         parser.Parse(jsonText.c_str());
    if (!ok) return false;

    return loadOptions(fbOptions::GetFB_Options(parser.builder_.GetBufferPointer()));
}

bool Options::loadOptionsFromBin()
{
    unique_ptr<char[]> buffer{};
    common::readBinFlatBuffer(optionsBinFileName_, buffer);
    return loadOptions(fbOptions::GetFB_Options(buffer.get()));
}

bool Options::loadOptions(const fbOptions::FB_Options* fb)
{
    struct OptionsSet {
        PlainTextBase::Language         lang_{ PlainTextBase::Language::__INVALID };
    };
    assert(fb != nullptr);

    OptionsSet set;
    set.lang_ = OptionLanguageBiMap::toLeftType(fb->language());
    if (set.lang_ == PlainTextBase::Language::__INVALID) {
        return false;
    }

    optLang_.setLanguage(set.lang_);
    acceptAll();
    return true;
}

} // namespace global
} // namespace game
