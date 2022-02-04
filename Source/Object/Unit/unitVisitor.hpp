
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef UNIT_VISITOR_HPP
#define UNIT_VISITOR_HPP

namespace Game {
namespace Object {

class Character;

class UnitVisitor {
public:
    UnitVisitor(const UnitVisitor&) = delete;
    UnitVisitor& operator=(const UnitVisitor&) = delete;

    virtual ~UnitVisitor() noexcept {}

    virtual void visitCharacter(Character& character) = 0;

protected:
    UnitVisitor() noexcept {}
};

class TypeUnitVisitor : public UnitVisitor {
public:
    TypeUnitVisitor() noexcept {}

    virtual ~TypeUnitVisitor() noexcept {}

    virtual void visitCharacter(Character& character) noexcept override {
        reset(); isChar_ = true;
    }

    bool isCharacter()     const noexcept { return isChar_; }

private:
    void reset() noexcept {
        isChar_ = false;
    }

private:
    bool isChar_        { false };
};

} // namespace Object
} // namespace Game

#endif // !UNIT_VISITOR_HPP
