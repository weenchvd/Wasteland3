
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FLATBUFFERS_AUX_HPP
#define FLATBUFFERS_AUX_HPP

#include<memory>
#include<vector>

namespace game {
namespace common {

// @brief Get std::vector<T> from flatbuffers::Array or flatbuffers::Vector.
// @param "a" - flatbuffers::Array or flatbuffers::Vector.
template<class T, class U>
std::vector<T> convertToVector(const U* a)
{
    std::vector<T> v;
    v.reserve(a->size());
    for (size_t i = 0; i < a->size(); ++i) {
        v.push_back(
            T{ a->Get(i) }
        );
    }
    return v;
}

void readBinFlatBuffer(const char* fileName,
                       std::unique_ptr<char[]>& receiver,
                       const char* fileHash = nullptr);

void writeBinFlatBuffer(const char* fileName,
                        const uint8_t* buffer,
                        const size_t bufferSize);

} // namespace common
} // namespace game

#endif // !FLATBUFFERS_AUX_HPP
