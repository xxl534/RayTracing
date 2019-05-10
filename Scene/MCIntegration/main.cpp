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
#include "hitable/ConstantMedium.h"

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
		float pdf;
		if (depth < 50 && rec.material_ptr->Scatter(ray, rec, vAttenuation, scattered, pdf))
		{
			return vEmitted +  vAttenuation * Color(scattered, world, depth + 1) * rec.material_ptr->ScatterPdf(ray, rec, scattered) / pdf;
		}
		else
		{
			return vEmitted;
		}
	}
	return Vector3(0.f);
}

Hitable*  CornellScene()
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

	return new HitableList(list, i);
}

int main()
{
	LONG64 llCurrTick;
	QueryPerformanceCounter((LARGE_INTEGER*)&llCurrTick);
	int nx = 500;
	int ny = 500;
	int ns = 400;
	/*int y0 = 60, y1 = 70, x0 = 125, x1 = 150;*/
	int y0 = 0, y1 = ny, x0 = 0, x1 = nx; 
	std::cout << "P3\n" << x1 - x0<< " " << y1 - y0<< "\n255\n";
	Vector3 vEye( -0.0f, 0.f, -200.f);
	Vector3 vLookAt(0.f, 0.f, 0.0f);
	float fDistToFocus = (vLookAt - vEye).Length();
	float fAperture = 0.1f;
	fAperture = 0.f;
	Camera cam(vEye, vLookAt, Vector3(0.f, 1.f, 0.f), 40, float(nx) / float(ny), fAperture, fDistToFocus);
	Hitable* world = CornellScene();
	for (int j = y1 - 1; j >= y0; --j)
	{
		for (int i = x0; i < x1; ++i)
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