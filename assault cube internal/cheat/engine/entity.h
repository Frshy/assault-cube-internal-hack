#include <Windows.h>

#include "vectors.h"

class Entity {
public:
	uintptr_t object;
	bool Get(int index);

	int GetHealth();
	Vec3 GetHeadPos();
	Vec3 GetPos();
	Vec3 GetViewAngles();
};

class LocalPlayer : public Entity {
public:
	bool Get();

	void SetHealth(int amount);
	void SetPos(Vec3 pos);
	void SetViewAngles(Vec3 angles);
	void AimAt(Vec3 pos);
};