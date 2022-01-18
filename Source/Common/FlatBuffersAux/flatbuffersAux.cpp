
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include<iostream>
#include<fstream>
#include<stdlib.h>

namespace Game
{
    namespace Common
    {
        using namespace std;

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
