
// Copyright (c) 2021 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include"squad.hpp"

namespace game {
namespace object {

using namespace std;

flatbuffers::Offset<fbSquad::FB_Squad> Squad::serialize(
    flatbuffers::FlatBufferBuilder& fbb) const
{
    using sq_t  = fbSquad::FB_Squad;
    using usp_t = fbSquad::FB_UnitSlotPair;

    vector<flatbuffers::Offset<fbSquad::FB_UnitSlotPair>> unitSlotOffsets;
    auto i{ nMembers_ };
    for (i = 0; i < members_.size(); ++i) {
        if (members_[i] != nullptr) {
            auto unitOffset{ members_[i]->serialize(fbb) };
            fbSquad::FB_UnitSlotPairBuilder b{ fbb };
            b.add_unit(unitOffset);
            b.add_slot(common::checked<decltype(&usp_t::slot), usp_t>(i));
            auto unitSlotPairOffset{ b.Finish() };
            unitSlotOffsets.push_back(unitSlotPairOffset);
        }
    }
    auto unitSlotVectorOffset{ fbb.CreateVector(unitSlotOffsets) };
    auto inventoryOffset{ invent_->serialize(fbb) };

    fbSquad::FB_SquadBuilder b{ fbb };
    b.add_units(unitSlotVectorOffset);
    b.add_inventory(inventoryOffset);
    b.add_money(common::checkedEnum<decltype(&sq_t::money), sq_t>(money_));
    return b.Finish();
}

unique_ptr<Squad> Squad::deserialize(const fbSquad::FB_Squad* fb)
{
    assert(fb != nullptr);
    auto squad{ make_unique<Squad>() };
    const auto* units{ fb->units() };
    for (int i = 0; i < units->size(); ++i) {
        auto pair{ units->Get(i) };
        assert(pair != nullptr);
        auto index{ pair->slot() };
        auto unit{ Unit::deserialize(pair->unit()) };
        squad->members_[index].reset(unit.release());
    }
    auto inventory{ Inventory::deserialize(fb->inventory()) };
    squad->invent_.reset(inventory.release());
    squad->money_ = common::Money{ fb->money() };
    return squad;
}

} // namespace object
} // namespace game
