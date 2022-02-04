
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef ARMOR_HPP
#define ARMOR_HPP

namespace Game {
namespace Object {

class Armor {
public:
    Armor(const signed char value)
        : val{ value } {}

    Armor(const Armor&) = delete;
    Armor& operator=(const Armor&) = delete;
    Armor(Armor&&) = delete;
    Armor& operator=(Armor&&) = delete;

    virtual ~Armor() noexcept {}

    int getArmorValue() const noexcept {
        return val;
    }

    void setArmorValue(const signed char value) noexcept {
        val = value;
    }

private:
    virtual void dummy() const noexcept = 0;

    signed char             val;            // armor value
};


class Head : public Armor {
public:
    Head(const signed char value)
        : Armor(value) {}

    Head(const Head&) = delete;
    Head& operator=(const Head&) = delete;
    Head(Head&&) = delete;
    Head& operator=(Head&&) = delete;

    ~Head() noexcept override {}

private:
    void dummy() const noexcept override {}

};


class Chest : public Armor {
public:
    Chest(const signed char value)
        : Armor(value) {}

    Chest(const Chest&) = delete;
    Chest& operator=(const Chest&) = delete;
    Chest(Chest&&) = delete;
    Chest& operator=(Chest&&) = delete;

    ~Chest() noexcept override {}

private:
    void dummy() const noexcept override {}

};


class Leg : public Armor {
public:
    Leg(const signed char value)
        : Armor(value) {}

    Leg(const Leg&) = delete;
    Leg& operator=(const Leg&) = delete;
    Leg(Leg&&) = delete;
    Leg& operator=(Leg&&) = delete;

    ~Leg() noexcept override {}

private:
    void dummy() const noexcept override {}

};

} // namespace Object
} // namespace Game

#endif // !ARMOR_HPP
