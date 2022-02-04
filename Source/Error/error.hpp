
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ERROR_HPP
#define ERROR_HPP

#include<stdexcept>
#include<string>

namespace Game {
namespace Error {

enum class Level {
    EXCEPTION,
    ERROR,
    WARNING,
    NOTICE,
};

enum class Type {
    STD,
    RUNTIME,
    INFILE,
    OUTFILE
};

void errPrint(std::ostream& os, Level errLevel, const std::string& message);
void errPrint(std::ostream& os, Level errLevel, Type errType);
void errPrint(std::ostream& os, Level errLevel, Type errType, const std::string& message);

class RuntimeError : public std::exception {
public:
    using ExceptionBase = std::exception;

    explicit RuntimeError(const std::string& message) : ExceptionBase(message.c_str()) {}
    explicit RuntimeError(const char* message) : ExceptionBase(message) {}
};

class OutOfRangeError : public RuntimeError {
public:
    using ExceptionBase = RuntimeError;

    explicit OutOfRangeError(const std::string& message) : ExceptionBase(message.c_str()) {}
    explicit OutOfRangeError(const char* message) : ExceptionBase(message) {}
};

} // namespace Error
} // namespace Game

#endif // ERROR_HPP
