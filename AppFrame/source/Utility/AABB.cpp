#include "AABB.h"

	bool Intersect(const AABB& r1, const AABB& r2)
	{
		if (r1.max.x < r2.min.x) {
			return false;
		}
		if (r2.max.x < r1.min.x) {
			return false;
		}
		if (r1.max.y < r2.min.y) {
			return false;
		}
		if (r2.max.y < r1.min.y) {
			return false;
		}
		return true;
	}
	bool Within(const AABB& r1, const AABB& r2)
	{
		if (r1.max.x < r2.max.x) {
			return false;
		}
		if (r1.min.x > r2.min.x) {
			return false;
		}
		if (r1.max.y < r2.max.y) {
			return false;
		}
		if (r1.min.y > r2.min.y) {
			return false;
		}
		return true;
	}
	bool Within(const AABB& r1, const Vector2& r2)
	{
		if (r1.max.x < r2.x) {
			return false;
		}
		if (r1.min.x > r2.x) {
			return false;
		}
		if (r1.max.y < r2.y) {
			return false;
		}
		if (r1.min.y > r2.y) {
			return false;
		}
		return true;
	}

