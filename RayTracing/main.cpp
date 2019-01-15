#include <iostream>
#include "ray.h"
#include "sphere.h"
#include <float.h>
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "Random.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

extern RandomFloat random = RandomFloat();
Vector3 Color(const Ray& ray, Hitable* world, int depth)
{
	HitRecord rec;
	if (world->Hit(ray, 0.001f, FLT_MAX, rec))
	{
		Ray scattered;
		Vector3 vAttenuation;
		if (depth < 50 && rec.material_ptr->scatter(ray, rec, vAttenuation, scattered))
		{
			return vAttenuation * Color(scattered, world, depth + 1);
		}
		else
		{
			return Vector3::Zero();
		}
	}
	Vector3 vDirNormal = ray.NormalizedDirection();
	float t = 0.5f * (vDirNormal.y + 1.f);
	return Vector3(1.f) * (1.f - t) + Vector3(0.5f, 0.7f, 1.f) * t;
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 10;
	float fs = 1.f / ns;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Camera cam(Vector3(-1.f, 1.f, -0.5f), Vector3(-0.f, 0.f, 1.f), Vector3(0.f, 1.f, 0.f), 90, float(nx) / float(ny));
	Hitable* list[5];
	list[0] = new Sphere(Vector3(0.f, 0.f, 1.f), 0.5f, new Lambertian(Vector3(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Vector3(0.f, -100.5f, 1.f), 100.f, new Lambertian(Vector3(0.8f, 0.8f, 0.f)));
	list[2] = new Sphere(Vector3(1.f, 0.f, 1.f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f)));
	list[3] = new Sphere(Vector3(-1.f, 0.f, 1.f), 0.5f, new Dielectric( 1.51f, Vector3(1.f, 1.f, 1.f)));
	list[4] = new Sphere(Vector3(-1.f, 0.f, 1.f), -0.49f, new Dielectric(1.51f, Vector3(1.f, 1.f, 1.f)));
	Hitable* world = new HitableList(list,4);
	/*Hitable* list[2];
	list[0] = new Sphere(Vector3(0.f, 0.f, 1.f), 0.5f, new Metal(Vector3(1.0f, 1.0f, 1.0f)));
	list[1] = new Sphere(Vector3(1.f, 0.f, 1.f), 0.5f, new Lambertian(Vector3(0.8f, 0.8f, 0.f)));
	Hitable* world = new HitableList(list, 2);*/
	for(int j = ny - 1; j >= 0; --j )
	{
		for (int i = 0; i < nx; ++i)
		{
			Vector3 vCol(0.f);
			for (int h = 0; h < ns; ++h)
			{
				for (int w = 0; w < ns; ++w)
				{
					float u = (float(i) + w * fs) / float(nx);
					float v = (float(j) + h * fs) / float(ny);
					Ray ray = cam.GetRay(u, v);
					vCol += Color(ray, world, 0);
				}
			}
			vCol /= float(ns*ns);
			/*for (int s = 0; s < ns; ++s)
			{
				float u = (float(i) + random.Gen()) / float(nx);
				float v = (float(j) + random.Gen()) / float(ny);
				Ray ray = cam.GetRay(u, v);
				vCol += Color(ray, world, 0);
			}
			vCol /= float(ns);*/
			vCol = Vector3(sqrtf(vCol.x), sqrtf(vCol.y), sqrtf(vCol.z));
			int ir = int(255.99* vCol.x);
			int ig = int(255.99* vCol.y);
			int ib = int(255.99* vCol.z);
			std::cout << ir << " " << ig << " " << ib << " ";
		}
		std::cout << "\n";
	}
}