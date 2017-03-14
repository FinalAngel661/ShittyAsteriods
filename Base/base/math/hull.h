#pragma once

#include "aabb.h"


namespace base
{
//
//template<size_t S>
//struct hull
//{
//
//	vec2 points[S];
//	vec2 normals[S];
//
//	static constexpr size_t size() { return S; }
//
//
//	float min(const vec2 &axis) const
//	{
//		float ret = INFINITY;
//		for each(auto &pos in points)
//			ret = flops::min(ret, dot(pos, axis));
//
//		return ret;
//	}
//
//	float max(const vec2 &axis) const
//	{
//		float ret = -INFINITY;
//		for each(auto &pos in points)
//			ret = flops::max(ret, dot(pos, axis));
//
//		return ret;
//	}
//
//	aabb boundingBox() const
//	{
//		return aabb::fromMinMax(vec2{ min(vec2::right()), min(vec2::up()) },
//								vec2{ max(vec2::right()), max(vec2::up()) });
//	}
//
//	hull(const vec2 ccw[S])
//	{		
//		for (int i = 0; i < S; ++i)
//			points[i] = ccw[i];
//
//		calculateNormals();
//	}
//	hull(float radius = .5f)
//	{
//		float inc = 2*PI / S;
//		for (int i = 0; i < S; ++i)
//			points[i] = vec2::fromAngle(inc * i, radius);
//
//		calculateNormals();
//	}
//
//	void calculateNormals()
//	{
//		for (int i = 0; i < S; ++i)
//			normals[i] = -(points[(i + 1) % S] - points[i]).normal().perp();
//	}
//};
//
//
//template<size_t S>
//hull<S> operator*(const mat3 &M, hull<S> A)
//{
//	for each(auto &pos in A.points)
//		pos = (M * vec3(pos, 1)).xy;
//	return A;
//}





struct hull
{
	vec2 points[MAX_HULL_SIZE];
	vec2 normals[MAX_HULL_SIZE];
	size_t size;

	float min(const vec2 &axis) const
	{
		float ret = INFINITY;
		for(int i = 0; i < size; ++i)
			ret = flops::min(ret, dot(points[i], axis));

		return ret;
	}

	float max(const vec2 &axis) const
	{
		float ret = -INFINITY;
		for (int i = 0; i < size; ++i)
			ret = flops::max(ret, dot(points[i], axis));
		return ret;
	}

	aabb boundingBox() const
	{
		return aabb::fromMinMax(vec2{ min(vec2::right()), min(vec2::up()) },
								vec2{ max(vec2::right()), max(vec2::up()) });
	}

	hull(const vec2 *ccw, size_t a_size)
	{
		size = flops::min(a_size, MAX_HULL_SIZE);

		for (int i = 0; i < size; ++i)
			points[i] = ccw[i];

		calculateNormals();
	}
	hull(float radius = .5f) : size(MAX_HULL_SIZE)
	{
		float inc = 2 * PI / size;
		for (int i = 0; i < size; ++i)
			points[i] = vec2::fromAngle(inc * i, radius);

		calculateNormals();
	}

	void calculateNormals()
	{
		for (int i = 0; i < size; ++i)
			normals[i] = -(points[(i + 1) % size] - points[i]).normal().perp();
	}
};

hull operator*(const mat3 &M, hull A)
{
	for(int i = 0; i < A.size; ++i)
	{
		A.points[i]  = (M * vec3(A.points[i], 1)).xy;
		A.normals[i] = (M * vec3(A.normals[i], 0)).xy.normal();
	}
	return A;
}



}