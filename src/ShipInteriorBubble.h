ShipInteriorBubble.h

#pragma once
#include <RE/Skyrim.h>
#include <vector>

class ShipInteriorBubble
{
public:
    static ShipInteriorBubble* Get()
    {
        static ShipInteriorBubble instance;
        return std::addressof(instance);
    }

    void SetShip(RE::TESObjectREFR* a_ship)
    {
        shipRef = a_ship->CreateRefHandle();
        lastShipPos = a_ship->GetPosition();
        lastShipRot = a_ship->GetRotationQuaternion();
    }

    void AddInteriorRef(RE::TESObjectREFR* a_ref)
    {
        interiorRefs.push_back(a_ref->CreateRefHandle());
    }

    void Update(float dt);
    