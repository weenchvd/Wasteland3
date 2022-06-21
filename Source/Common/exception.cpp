
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"exception.hpp"

namespace game {
namespace common {

using namespace std;

string initExceptionStorage()
{
    constexpr int storageSize{ 4096 };
    string s;
    s.reserve(storageSize);
    return s;
}

string Exception::storage_{ initExceptionStorage() };

string toString(ErrorType type)
{
    switch (type) {
    case ErrorType::UNKNOWN:
        return u8"UNKNOWN";
    case ErrorType::IO_ERROR:
        return u8"IO_ERROR";
    case ErrorType::CORRUPTED_FILE:
        return u8"CORRUPTED_FILE";
    case ErrorType::SERIALIZATION:
        return u8"SERIALIZATION";
    default:
        return u8"Unrecognized error";
    }
}

///************************************************************************************************

IOError::IOError(const char* message)
    : Exception{ u8"[EXCEPTION] I/O error: " }
{
    storage_ += message;
}

IOError::IOError(const char* fileName, const char* message)
    : Exception{ u8"[EXCEPTION] I/O error: " }
{
    storage_ += u8"File '";
    storage_ += fileName;
    storage_ += u8"' ";
    storage_ += message;
}

///************************************************************************************************

CorruptedFile::CorruptedFile(const char* fileName)
    : IOError{ u8"File '" }
{
    storage_ += fileName;
    storage_ += u8"' is corrupted";
}

///************************************************************************************************

SerializationError::SerializationError(const char* message)
    : Exception{ u8"[EXCEPTION] Serialization error: " }
{
    storage_ += message;
}

} // namespace common
} // namespace game
