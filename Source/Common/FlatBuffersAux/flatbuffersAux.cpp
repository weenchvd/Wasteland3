
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"botan/hash.h"
#include"botan/hex.h"
#include"exception.hpp"
#include"flatbuffersAux.hpp"
#include"flatbuffersAuxDefine.hpp"
#include<iostream>
#include<fstream>
#include<stdlib.h>

namespace game {
namespace common {

using namespace std;

void readBinFlatBuffer(const char* fileName,
                       std::unique_ptr<char[]>& receiver,
                       const char* fileHash)
{
    constexpr int nAttempts{ 10 };
    if (fileName == nullptr) throw common::IOError{ u8"Filename is nullptr" };

    ifstream ifs;
    bool opened{ false };
    for (int i = 0; !opened && i < nAttempts; ++i) {
        ifs.open(fileName, ios::binary | ios::in);
        opened = ifs.is_open();
    }
    if (!opened) throw common::IOError{ fileName, u8"is not open" };
    ifs.seekg(0, ios::end);
    auto length{ ifs.tellg() };
    if (length <= 0) throw common::IOError{ fileName, u8"has zero length" };
    ifs.seekg(0, ios::beg);
    unique_ptr<char[]> temp{ new char[length] };
    ifs.read(temp.get(), length);
    if (!ifs.good()) throw common::IOError{ fileName, u8"not read" };
    ifs.close();
    if (fileHash != nullptr) {
        unique_ptr<Botan::HashFunction> hash{
            Botan::HashFunction::create(DEFAULT_BOTAN_FILE_HASH_FUNC)
        };
        hash->update(reinterpret_cast<uint8_t*>(temp.get()), length);
        if (string{ fileHash } != Botan::hex_encode(hash->final(), false)) {
            throw common::CorruptedFile{ fileName };
        }
    }
    swap(receiver, temp);
}

void writeBinFlatBuffer(const char* fileName,
                        const uint8_t* buffer,
                        const size_t bufferSize)
{
    constexpr int nAttempts{ 10 };
    if (fileName == nullptr) throw common::IOError{ u8"Filename is nullptr" };
    if (buffer == nullptr) throw common::IOError{ u8"Buffer is nullptr" };
    if (bufferSize == 0) throw common::IOError{ u8"Buffer size is 0" };

    ofstream ofs;
    bool opened{ false };
    for (int i = 0; !opened && i < nAttempts; ++i) {
        ofs.open(fileName, ios::binary | ios::out);
        opened = ofs.is_open();
    }
    if (!opened) throw common::IOError{ fileName, u8"is not open" };
    ofs.write(reinterpret_cast<const char*>(buffer), bufferSize);
    if (!ofs.good()) throw common::IOError{ fileName, u8"not written" };
    ofs.close();
}

} // namespace common
} // namespace game
