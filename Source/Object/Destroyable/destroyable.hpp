
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DESTROYABLE_HPP
#define DESTROYABLE_HPP

namespace game {
namespace object {

using namespace std;

class Destroyable {
public:
    Destroyable(unsigned short int constitutionMax)
        : conMax{ constitutionMax }, con{ constitutionMax } {}

    Destroyable(const Destroyable&) = default;
    Destroyable& operator=(const Destroyable&) = default;
    Destroyable(Destroyable&&) = default;
    Destroyable& operator=(Destroyable&&) = default;

    virtual ~Destroyable() {}

    int getCon() const {
        return con;
    }

    virtual int takeDamage(unsigned short int damage) {
        return (con = (damage >= con) ? 0 : (con - damage));
    }
private:
    unsigned short int      conMax;         // constitution max value
    unsigned short int      con;            // constitution value
};

class Enviroment : public Destroyable {
public:

private:

};

class Unit : public Destroyable {
public:
    Unit(unsigned short int constitutionMax)
        : Destroyable(constitutionMax),
        critDam{ 1.0 },
        combatSpeed{ 0.5 },
        healBon{ 100 },
        apMax{ 0 },
        ap{ 0 },
        hitChance{ 0 },
        critChance{ 0 },
        penet{ 0 },
        armor{ 0 },
        evasion{ 0 },
        critRes{ 0 },
        fireRes{ 0 },
        coldRes{ 0 },
        enerRes{ 0 },
        explRes{ 0 },
        statEffRes{ 0 },
        radRes{ 0 },
        normDamBon{ 100 },
        init{ 0 },
        leadRange{ 0 } {}

    Unit(const Unit&) = default;
    Unit& operator=(const Unit&) = default;
    Unit(Unit&&) = default;
    Unit& operator=(Unit&&) = default;

    virtual ~Unit() {}
private:
    double                  critDam;        // critical damage, default: 1.0
    double                  combatSpeed;    // combat speed, default: 0.5?
    unsigned char           healBon;        // healing bonus, default: 100
    unsigned char           apMax;          // action points (max), default: 0
    unsigned char           ap;             // action points, default: 0
    unsigned char           hitChance;      // hit chance, default: 0
    unsigned char           critChance;     // critical chance, default: 0
    unsigned char           penet;          // penetration, default: 0
    unsigned char           armor;          // armor, default: 0
    char                    evasion;        // evasion, default: 0
    char                    critRes;        // critical resistance, default: 0
    char                    fireRes;        // fire resistance, default: 0
    char                    coldRes;        // cold resistance, default: 0
    char                    enerRes;        // energy resistance, default: 0
    char                    explRes;        // explosive resistance, default: 0
    char                    statEffRes;     // status effect resistance, default: 0
    unsigned char           radRes;         // radiation resistance, default: 0
    unsigned char           normDamBon;     // normal damage bonus, default: 100
    unsigned char           init;           // initiative, default: 0
    unsigned char           leadRange;      // leadership range, default: 0
};

class Flesh : public Unit {
public:

private:

};

class Mechanic : public Unit {
public:

private:

};

class Animal : public Flesh {
public:

private:

};

class Mutant : public Flesh {
public:

private:

};

class Human : public Flesh {
public:

private:
    unique_ptr<Armor>       head;           // head armor
    unique_ptr<Armor>       chest;          // chest armor
    unique_ptr<Armor>       leg;            // leg armor
    unique_ptr<Weapon>      fst;            // first weapon
    double                  throwRange;     // throwing range, default: 0.5?
    unsigned char           quickSlots;     // quick slots, default: 1
};

class Character : public Human {
public:

private:
    unique_ptr<Weapon>      sec;            // second weapon
    double                  detectTime;     // detection time, default: 1.0?
    unsigned int            xp;             // experience, default: 0
    unsigned short int      sneakAttDam;    // sneak attack damage, default: 100
    unsigned char           lvl;            // level, default: 1
    unsigned char           conPerLvl;      // CON per level, default: 20?
    unsigned char           strikeRate;     // strike rate, default: 0
    unsigned char           downTime;       // downed time, default: 3
    unsigned char           meleeDamBon;    // melee damage bonus, default: 100
    unsigned char           rangeDamBon;    // ranged damage bonus, default: 100
    unsigned char           fireDamBon;     // fire damage bonus, default: 100
    unsigned char           coldDamBon;     // cold damage bonus, default: 100
    unsigned char           enerDamBon;     // energy damage bonus, default: 100
    unsigned char           explDamBon;     // explosive damage bonus, default: 100
    unsigned char           percep;         // perception, default: 0
    char                    xpBon;          // experience bonus, default: 0
};

} // namespace object
} // namespace game

#endif // !DESTROYABLE_HPP
