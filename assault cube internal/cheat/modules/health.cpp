#include "modules.h"

#include "../engine/entity.h"
#include "../settings.h"

void modules::IniniteHealth() {
	if (C_Settings->InfiniteHealth) {
		LocalPlayer local_player;
		if (local_player.Get()) {
			local_player.SetHealth(1337 /*very cool hacking number ;--------DDDDDD*/);
		}
	}
}