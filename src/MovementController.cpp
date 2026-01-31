#include "MovementController.h"

void MovementController::Update(float dt)
{
    auto player = RE::PlayerCharacter::GetSingleton();
    if (!player) {
        return;
    }

    auto ctrl = player->GetCharController();
    if (!ctrl) {
        return;
    }

    auto input = RE::BSInputDeviceManager::GetSingleton();
    if (!input) {
        return;
    }

    RE::NiMatrix3 rot;
    player->GetRotationMatrix(rot);

    RE::NiPoint3 localThrust{ 0.f, 0.f, 0.f };

    if (input->IsKeyPressed(RE::DIK_W)) localThrust.y += 1.0f;
    if (input->IsKeyPressed(RE::DIK_S)) localThrust.y -= 1.0f;
    if (input->IsKeyPressed(RE::DIK_D)) localThrust.x += 1.0f;
    if (input->IsKeyPressed(RE::DIK_A)) localThrust.x -= 1.0f;
    if (input->IsKeyPressed(RE::DIK_SPACE)) localThrust.z += 1.0f;
    if (input->IsKeyPressed(RE::DIK_LCONTROL)) localThrust.z -= 1.0f;

    constexpr float thrustPower = 5000.0f;
    ctrl->state.linearVelocity += (rot * localThrust) * (thrustPower * dt);

    constexpr float maxSpeed = 6000.0f;
    if (ctrl->state.linearVelocity.Length() > maxSpeed) {
        ctrl->state.linearVelocity =
            ctrl->state.linearVelocity.Unit() * maxSpeed;
    }

    ctrl->state.linearVelocity *= 0.99f;

    constexpr float rSpd = 2.0f;

    player->SetAngleZ(player->GetAngleZ() + input->GetMouseX() * rSpd * dt);
    player->SetAngleX(player->GetAngleX() - input->GetMouseY() * rSpd * dt);

    if (input->IsKeyPressed(RE::DIK_Q))
        player->SetAngleY(player->GetAngleY() - rSpd * dt);

    if (input->IsKeyPressed(RE::DIK_E))
        player->SetAngleY(player->GetAngleY() + rSpd * dt);
}