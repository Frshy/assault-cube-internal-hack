#include "modules.h"

#include "../engine/entity.h"
#include "../settings.h"
#include "../engine/helpers.h"
#include <iostream>

uintptr_t get_closest_enemy() {
	float distance = 9999999;
	Entity e;
	LocalPlayer local_player;
	uintptr_t closest_enemy;

	for (int i = 1; i < 4; i++) {
		if (e.Get(i) && e.GetHealth() > 0) {
			float actual_distance = helpers::GetDistance(local_player.GetPos(), e.GetPos());
			if (actual_distance < distance) {
				distance = actual_distance;
				closest_enemy = e.object;
			}
		}
	}

	return closest_enemy;
};

void modules::Aimbot() {
	if (C_Settings->Aimbot && GetAsyncKeyState(C_Settings->AimbotKey)) {
		LocalPlayer local_player;
		if (local_player.Get()) {
			Entity e;
			if (e.object = get_closest_enemy()) {
				local_player.AimAt(e.GetPos());
			}
		}
	}
}