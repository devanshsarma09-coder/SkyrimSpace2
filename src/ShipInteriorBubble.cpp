// ShipInteriorBubble.cpp
#include "ShipInteriorBubble.h"

void ShipInteriorBubble::Update(float dt)
{
    auto shipHandle = shipRef.get();
    if (!shipHandle) {
        return;
    }

    auto ship = shipHandle.get();
    if (!ship) {
        return;
    }

    const auto currentPos = ship->GetPosition();
    const auto currentRot = ship->GetRotationQuaternion();

    const RE::NiPoint3 dPos = currentPos - lastShipPos;
    const RE::NiQuaternion dRot = currentRot * lastShipRot.Inverse();

    for (auto& handle : interiorRefs) {
        auto refHandle = handle.get();
        if (!refHandle) {
            continue;
        }

        auto ref = refHandle.get();
        if (!ref) {
            continue;
        }

        RE::NiPoint3 localPos = ref->GetPosition() - lastShipPos;
        RE::NiPoint3 rotatedLocalPos = dRot * localPos;
        RE::NiPoint3 newWorldPos = currentPos + rotatedLocalPos;

        ref->SetPosition(newWorldPos, true);

        if (auto actor = ref->As<RE::Actor>()) {
            if (auto ctrl = actor->GetCharController()) {
                ctrl->state.linearVelocity *= 0.05f;
                ctrl->context.characterSupported = true;
            }
        }

        if (auto node = ref->Get3D()) {
            RE::NiMatrix3 deltaRot(dRot);
            node->local.rotate = deltaRot * node->local.rotate;
            node->Update(0.0f);
        }
    }

    lastShipPos = currentPos;
    lastShipRot = currentRot;
}