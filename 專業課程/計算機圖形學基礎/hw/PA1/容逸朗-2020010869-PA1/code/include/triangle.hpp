#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle : public Object3D
{

public:
	Triangle() = delete;

	// a b c are three vertex positions of the triangle
	Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c, Material *m) : Object3D(m)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	bool intersect(const Ray &ray, Hit &hit, float tmin) override
	{
		Vector3f E1 = a - b;
		Vector3f E2 = a - c;
		Vector3f S = a - ray.getOrigin();
		Vector3f ans = Vector3f(Matrix3f(S, E1, E2).determinant(),
														Matrix3f(ray.getDirection(), S, E2).determinant(),
														Matrix3f(ray.getDirection(), E1, S).determinant());
		ans *= (1 / Matrix3f(ray.getDirection(), E1, E2).determinant());
		if (ans[0] > 0 && 0 <= ans[1] && 0 <= ans[2] && ans[1] + ans[2] <= 1)
		{
			// TODO: judge +- 1
			if (ans[0] < tmin || ans[0] > hit.getT())
				return false;
			hit.set(ans[0], material, normal);
			return true;
		}

		return false;
	}

	Vector3f normal;
	Vector3f vertices[3];

protected:
	Vector3f a, b, c;
};

#endif // TRIANGLE_H
