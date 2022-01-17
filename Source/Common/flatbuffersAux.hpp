
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef FLATBUFFERS_AUX_HPP
#define FLATBUFFERS_AUX_HPP

#include<iostream>
#include<fstream>
#include<memory>
#include<stdlib.h>
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

        std::unique_ptr<char[]> getFlatBuffer(const char* fileName)
        {
            constexpr int nAttempts{ 10 };

            std::ifstream infile;
            bool opened{ false };
            for (int i = 0; opened == false && i < nAttempts; ++i) {
                infile.open(fileName, std::ios::binary | std::ios::in);
                opened = infile.is_open();
            }
            if (opened == false) {
                abort();
            }
            infile.seekg(0, std::ios::end);
            int length = infile.tellg();
            infile.seekg(0, std::ios::beg);
            std::unique_ptr<char[]> buffer{ new char[length] };
            infile.read(buffer.get(), length);
            infile.close();
            return buffer;
        }

    }
}

#endif // !FLATBUFFERS_AUX_HPP
