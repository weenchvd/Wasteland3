
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FLATBUFFERS_CONVERTER_HPP
#define FLATBUFFERS_CONVERTER_HPP

#include<vector>

namespace Game
{
    namespace Common
    {
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

    }
}

#endif // !FLATBUFFERS_CONVERTER_HPP
