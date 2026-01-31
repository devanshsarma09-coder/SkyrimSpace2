// Hooks.h
#pragma once
#include <RE/Skyrim.h>

#include "MovementController.h"
#include "ShipInteriorBubble.h"

struct PlayerUpdateHook
{
    static void thunk(RE::PlayerCharacter* a_player, float a_delta)
    {
        MovementController::Update(a_delta);
        ShipInteriorBubble::Get()->Update(a_delta);
        func(a_player, a_delta);
    }

    static inline REL::Relocation<decltype(thunk)> func;
};
