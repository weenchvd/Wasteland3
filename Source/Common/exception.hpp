
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include<stdexcept>
#include<string>

namespace game {
namespace common {

enum class ErrorType : char {
    INVALID = -1,                   /// invalid, must be the first
    // vvv TYPES vvv
    UNKNOWN,
    IO_ERROR,
    CORRUPTED_FILE,
    // ^^^ TYPES ^^^
    NUMBER_OF                       /// must be the last
};

// @brief Convert an ErrorType to string
std::string toString(ErrorType type);

///************************************************************************************************

class Exception : public std::exception {
public:
    Exception(const char* message) { storage_ = message; }

    const char* what() const noexcept override { return storage_.c_str(); }

    virtual ErrorType errorType() const noexcept { return ErrorType::UNKNOWN; }

protected:
    static std::string storage_;
};

///************************************************************************************************

class IOError : public Exception {
public:
    IOError(const char* message);

    IOError(const char* fileName, const char* message);

    virtual ErrorType errorType() const noexcept override { return ErrorType::IO_ERROR; }
};

///************************************************************************************************

class CorruptedFile final : public IOError {
public:
    CorruptedFile(const char* fileName);

    virtual ErrorType errorType() const noexcept override { return ErrorType::CORRUPTED_FILE; }
};

} // namespace common
} // namespace game

#endif // !EXCEPTION_HPP
