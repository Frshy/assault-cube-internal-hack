#include "entity.h"

#include <Windows.h>
#include <math.h>
#include <iostream>

#include "helpers.h"
#include "../offsets.h"

#define PI 3.14

bool Entity::Get(int index) {
	uintptr_t game_module = (uintptr_t)GetModuleHandleA("ac_client.exe");
	uintptr_t entity_list = *(uintptr_t*)(game_module + m_entitylist);
	return this->object = *(uintptr_t*)(entity_list + index * 4);
}

int Entity::GetHealth() {
	return *(int*)(this->object + m_health);
}

Vec3 Entity::GetHeadPos() {
	return *(Vec3*)(this->object + m_headpos);
}

Vec3 Entity::GetPos() {
	return *(Vec3*)(this->object + m_pos);
}

Vec3 Entity::GetViewAngles() {
	return *(Vec3*)(this->object + m_viewangles);
}

bool LocalPlayer::Get() {
	uintptr_t game_module = (uintptr_t)GetModuleHandleA("ac_client.exe");
	return this->object = *(uintptr_t*)(game_module + m_localplayer);
}

void LocalPlayer::SetHealth(int amount) {
	*(int*)(this->object + m_health) = amount;
}

void LocalPlayer::SetPos(Vec3 pos) {
	*(Vec3*)(this->object + m_pos) = pos;
}

void LocalPlayer::SetViewAngles(Vec3 angles) {
	*(Vec3*)(this->object + m_viewangles) = angles;
}

void LocalPlayer::AimAt(Vec3 pos) {
	Vec3 actual_angles = this->GetPos();

	Vec3 new_angles;
	new_angles.x = -atan2f(pos.x - actual_angles.x, pos.y - actual_angles.y) / PI * 180.0f + 180.0f;
	new_angles.y = asinf((pos.z - actual_angles.z) / helpers::GetDistance(this->GetPos(), pos)) * 180.0f / PI;
	new_angles.z = 0.0f;

	this->SetViewAngles(new_angles);
}