
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAINTEXT_HPP
#define PLAINTEXT_HPP

#include"common.hpp"
#include"plainTextCommon.hpp"
#include<array>

namespace game {
namespace global {

template<class T, size_t size>
void fillAll(std::array<T, size> a, const T& filler) {
    for (auto& t : a) {
        t = filler;
    }
}

const common::Text invalidEnum{ u8"INVALID ENUM" };
const common::Text eng_NoData{ u8"NO DATA" };
const common::Text rus_NoData{ u8"НЕТ ДАННЫХ" };

///************************************************************************************************

class PlainText {
public:
    using Language      = PlainText__Language;
    using General       = PlainText__General;

    static constexpr unsigned char sizeLang_{ common::toUnderlying(PlainText::Language::NUMBER_OF) };

private:
    using text          = common::Text;

    friend class Factory;

    static constexpr unsigned int sizeCommon_{ common::toUnderlying(PlainText::General::NUMBER_OF) };

protected:
    PlainText(PlainText::Language lang);

public:
    PlainText(const PlainText&) = delete;
    PlainText& operator=(const PlainText&) = delete;

    ~PlainText() noexcept {}

    PlainText::Language getLanguage() const noexcept {
        return current_;
    }

    void setLanguage(PlainText::Language lang);

public:
    const text& language(PlainText::Language id) const noexcept;

    const text& common(PlainText::General id) const noexcept;

private:
    void initialize();
    void initializeEN();
    void initializeRU();

    void fill();

    const text& getDefault() const noexcept;

    void initCommonEN();

    void initCommonRU();

private:

protected:
    PlainText::Language                                 current_;
    std::array<text, sizeLang_>                         lang_;
    std::array<text, sizeCommon_>                       common_;

};

} // namespace global
} // namespace game

#endif // !PLAINTEXT_HPP
