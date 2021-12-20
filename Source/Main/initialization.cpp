
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"initialization.hpp"
#include"factory.hpp"
#include"character.hpp"

namespace Init
{
	using namespace std;

	constexpr int initialMoney = 50'000;

	void initializeSquad(Game::Object::Squad& squad)
	{
		initializeInventory(squad.inventory());
		initializeMembers(squad.members());
		squad.moneyAdd(initialMoney);
	}

	void initializeInventory(Game::Object::Inventory& inventory)
	{
		using Game::Object::Weapon;
		using Game::Object::WeaponMod;
		
		Game::Global::Factory f;

		/// weapons
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));

		/// weapon mods
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));

	}

	void initializeShop(Game::Object::Inventory& inventory)
	{
		using Game::Object::Weapon;
		using Game::Object::WeaponMod;

		Game::Global::Factory f;

		/// weapons
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_SOCOM));
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));
		inventory.insert(f.createItem<Weapon>(Weapon::Model::AR_KALASH97));
		inventory.insert(f.createItem<Weapon>(Weapon::Model::SMG_RIPPER));

		/// weapon mods
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_LIGHTWEIGHT));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::BARREL_SHORTENED));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_ADVANCED_MATERIALS));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_OVERSIZED));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));
		inventory.insert(f.createItem<WeaponMod>(WeaponMod::Model::MAG_QUICKFIRE));

	}

	void initializeMembers(std::array<std::unique_ptr<Game::Object::Unit>, Game::Object::nMembers>& members)
	{
		using Game::Object::Character;

		Game::Global::Factory f;

		int i = 0;
		/// member 1
		if (i < members.size()) {
			members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
			auto& c = *static_cast<Character*>(members[i++].get());
			c.name("YURI");
		}
		/// member 2
		if (i < members.size()) {
			members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
			auto& c = *static_cast<Character*>(members[i++].get());
			c.name("ECHO");
		}
		/// member 3
		if (i < members.size()) {
			members[i] = f.createUnit<Character>(Character::Model::RANGER_COMMON);
			auto& c = *static_cast<Character*>(members[i++].get());
			c.name("RUST");
		}
	}

}
