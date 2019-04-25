#include <iostream>
#include <windows.h>
#include "ray.h"
#include "hitable/sphere.h"
#include <float.h>
#include "hitable/HitableList.h"
#include "Camera.h"
#include "material/Material.h"
#include "Random.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "Texture.h"
#include "hitable/Quad.h"
#include "material/Light.h"
#include "hitable/Box.h"
#include "hitable/Translate.h"
#include "hitable/Rotate.h"

extern RandomFloat random = RandomFloat();
extern float gShutterDuration = 0.1f;
extern float gElapsed = 0.f;

Vector3 Color(const Ray& ray, Hitable* world, int depth)
{
	HitRecord rec;
	if (world->Hit(ray, 0.001f, FLT_MAX, rec))
	{
		Ray scattered;
		Vector3 vEmitted = rec.material_ptr->Emitted(rec.u, rec.v, rec.point);
		if (depth == 0)
		{
			vEmitted = Vector3::Clamp(vEmitted, Vector3(0.f), Vector3(1.f));
		}
		Vector3 vAttenuation;
		if (depth < 50 && rec.material_ptr->Scatter(ray, rec, vAttenuation, scattered))
		{
			return vEmitted +  vAttenuation * Color(scattered, world, depth + 1);
		}
		else
		{
			return vEmitted;
		}
	}
	return Vector3(0.f);
	/*Vector3 vDirNormal = ray.NormalizedDirection();
	float t = 0.5f * (vDirNormal.y + 1.f);
	return Vector3(1.f) * (1.f - t) + Vector3(0.5f, 0.7f, 1.f) * t;*/
}

Hitable*  RandomScene()
{
	Hitable** list = new Hitable*[20];
	int i = 0;
	Material* red = new Lambertian(Vector3(0.65f, 0.05f, 0.05f));
	Material* green = new Lambertian(Vector3(0.12f, 0.45f, 0.15f));
	Material* blue = new Lambertian(Vector3(0.12f, 0.05f, 0.7f));
	Material* white = new Lambertian(Vector3(0.73f));
	Material* light = new DiffuseLight(new ConstantTexture(Vector3(15.f)));
	list[i++] = new Quad(Vector3( -50.f, 0.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f), 100.f, 100.f,green);
	list[i++] = new Quad(Vector3( 50.f, 0.f, 0.f), Vector3( -1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f), 100.f, 100.f, red);
	list[i++] = new Quad(Vector3(0.f, -50.f, 0.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, -1.f), 100.f, 100.f, white);
	list[i++] = new Quad(Vector3(0.f, 50.f, 0.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f), 100.f, 100.f, white);
	list[i++] = new Quad(Vector3(0.f, 49.99f, 0.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f), 20.f, 20.f, light);
	list[i++] = new Quad(Vector3(0.f, 0.f, 50.f), Vector3(0.f, 0.f, -1.f), Vector3(0.f, 1.f, 0.f), 100.f, 100.f, white);
	list[i++] = new Translate(new RotateY(new Box(Vector3(32.f, 64.f, 32.f), white), 18), Vector3(-15, -18.f, 20.f));
	list[i++] = new Translate(new RotateY(new Box(Vector3(32.f), white), -15), Vector3(15, -34.f, -20.f));

	//list[i++] = new Translate(new RotateY(new Box(Vector3(50.f), white), -30), Vector3(0, -25.f, 0.f));

	//list[i++] = new Translate(new RotateY(new Quad(Vector3(0.f, 0.f, -0.01f), Vector3(0.f, 0.f, -1.f), Vector3(0.f, 1.f, 0.f), 50.f, 50.f, blue), -30), Vector3(0, -25.f, -25.f));
	//list[i++] = new Translate(new RotateY(new Quad(Vector3(0.f, 0.f, 0.01f), Vector3(0.f, 0.f, 1.f), Vector3(0.f, 1.f, 0.f), 50.f, 50.f, blue), -30), Vector3(0, -25.f, -25.f));
	
	/*list[i++] = new Translate(new Box(Vector3(32.f, 64.f, 32.f), white), Vector3(-15, -18.f, 20.f));
	list[i++] = new Translate(new Box(Vector3(32.f), white), Vector3(15, -34.f, -20.f));
	list[i++] = new Quad(Vector3(0.f, 49.99f, -30.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f), 20.f, 20.f, light);
	list[i++] = new RotateY(new Box(Vector3(32.f), white), 30);*/
	return new HitableList(list, i);
}

int main()
{
	LONG64 llCurrTick;
	QueryPerformanceCounter((LARGE_INTEGER*)&llCurrTick);
	int nx = 400;
	int ny = 400;
	Vector3* colBuffer = new Vector3[nx*ny];
	memset(colBuffer, 0, nx * ny * sizeof(Vector3));
	int ns = 1000;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Vector3 vEye( -0.0f, 0.f, -200.f);
	Vector3 vLookAt(0.f, 0.f, 0.0f);
	float fDistToFocus = (vLookAt - vEye).Length();
	float fAperture = 0.1f;
	fAperture = 0.f;
	Camera cam(vEye, vLookAt, Vector3(0.f, 1.f, 0.f), 40, float(nx) / float(ny), fAperture, fDistToFocus);
	Hitable* world = RandomScene();
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			Vector3 vCol(0.f);
			for (int s = 0; s < ns; ++s)
			{
				float u = (float(i) + random.Gen()) / float(nx);
				float v = (float(j) + random.Gen()) / float(ny);
				Ray ray = cam.GetRay(u, v);
				gElapsed = gShutterDuration * random.Gen();
				vCol += Color(ray, world, 0);
			}
			vCol /= float(ns);
			vCol = Vector3(sqrtf(vCol.x), sqrtf(vCol.y), sqrtf(vCol.z));
			int ir = int(255.99* vCol.x);
			int ig = int(255.99* vCol.y);
			int ib = int(255.99* vCol.z);
			std::cout << MathClamp(ir,0,255) << " " << MathClamp(ig, 0, 255) << " " << MathClamp(ib, 0, 255) << " ";
		}
		std::cout << "\n";
	}
	LONG64 llEndTick;
	QueryPerformanceCounter((LARGE_INTEGER*)&llEndTick);
	//std::cout << llEndTick - llCurrTick;
}