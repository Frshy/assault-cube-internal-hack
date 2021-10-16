#include "helpers.h"

#include <math.h>

float helpers::GetDistance(Vec3 src, Vec3 dst) {
	float result = sqrtf( powf(dst.x - src.x, 2.0f) + powf(dst.y - src.y, 2.0f) + powf(dst.z - src.z, 2.0f) );
	return result;
}