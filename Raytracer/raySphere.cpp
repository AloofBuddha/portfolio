#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include "rayScene.h"
#include "raySphere.h"
#include <iostream.h>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray, RayIntersectionInfo& iInfo, double mx){

	Point3D p0 = ray.position;
	Point3D V  = ray.direction;

	double a = 1;
	double b = (V * 2).dot(p0 - center);
	double c = (p0 - center).squareNorm() - pow(radius,2);
	double discriminant = b * b - 4 * a * c;
	//imaginary solutions means no intersection
	if (discriminant < 0)
		return -1;
	//an intersection exists, compute t values
	double t1 = (-b + sqrt(discriminant)) / (2 * a);
	double t2 = (-b - sqrt(discriminant)) / (2 * a);

	double t;
	// negative solutions mean the shape is BEHIND the camera
	if (t1 < 0 && t2 < 0) //both neg
		return -1;
	else if (t1 >= 0 && t2 >= 0) //both pos
		t = (t1 < t2) ? t1 : t2; //take nearest
	else //one must be negative
		t = (t1 < t2) ? t1 : t2; //take positive
	//this will only happen if the camera is inside the sphere or we are refracting a ray

	iInfo.material = material;
	iInfo.iCoordinate = ray(t);
	iInfo.normal = (iInfo.iCoordinate - center).unit();

	return t;
}

BoundingBox3D RaySphere::setBoundingBox(void){

	bBox.p[0] = center - Point3D(radius,radius,radius);
	bBox.p[1] = center + Point3D(radius,radius,radius);

	return bBox;
}
