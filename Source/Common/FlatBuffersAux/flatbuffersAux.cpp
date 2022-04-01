
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"flatbuffersAux.hpp"
#include<iostream>
#include<fstream>
#include<stdlib.h>

namespace game {
namespace common {

using namespace std;

bool readBinFlatBuffer(const char* fileName, unique_ptr<char[]>& receiver) noexcept
{
    constexpr int nAttempts{ 10 };
    if (fileName == nullptr) return false;

    try {
        ifstream ifs;
        bool opened{ false };
        for (int i = 0; !opened && i < nAttempts; ++i) {
            ifs.open(fileName, ios::binary | ios::in);
            opened = ifs.is_open();
        }
        if (!opened) return false;
        ifs.seekg(0, ios::end);
        auto length{ ifs.tellg() };
        if (length <= 0) return false;
        ifs.seekg(0, ios::beg);
        unique_ptr<char[]> temp{ new char[length] };
        ifs.read(temp.get(), length);
        if (!ifs.good()) return false;
        ifs.close();
        swap(receiver, temp);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool writeBinFlatBuffer(
    const char* fileName,
    const uint8_t* buffer,
    const size_t bufferSize) noexcept
{
    constexpr int nAttempts{ 10 };
    if (fileName == nullptr || buffer == nullptr || bufferSize == 0) return false;

    try {
        ofstream ofs;
        bool opened{ false };
        for (int i = 0; !opened && i < nAttempts; ++i) {
            ofs.open(fileName, ios::binary | ios::out);
            opened = ofs.is_open();
        }
        if (!opened) return false;
        ofs.write(reinterpret_cast<const char*>(buffer), bufferSize);
        if (!ofs.good()) return false;
        ofs.close();
        return true;
    }
    catch (...) {
        return false;
    }
}

} // namespace common
} // namespace game
