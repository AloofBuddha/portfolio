#include "rayScene.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include <math.h>
#include <iostream.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

//source for reflection equation is: 
// http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
Point3D RayScene::Reflect(Point3D v,Point3D n){
	//assumes v is normalized, no need to renormalize
	return v - n*2*v.dot(n);
}

Ray3D RayScene::GetRay(RayCamera* camera,int i, int j, int width, int height) {
	const double d = 1.0; //distance to viewing plane, arbitrary 

	//camera values
	Point3D camOrigin = camera -> position;
	Point3D towards = camera -> direction;
	Point3D up = camera -> up;
	Point3D right = camera -> right;
	double heigthAngle = (camera -> heightAngle)/2.0; //in radians
	double widthAngle = heigthAngle * (camera -> aspectRatio);

	//compute bot-left vector
	Point3D viewOrigin = camOrigin + towards*d; //center of view 
	viewOrigin -= up*d*tan(heigthAngle); //bot edge of view
	viewOrigin -= right*d*tan(widthAngle); //bot-left edge of view

	// compute up and right vector representing pixel [i, j]
	Point3D upComponent = up*d*tan(heigthAngle)*2*((j+0.5)/height);
	Point3D rightComponent = right*d*tan(widthAngle)*2*((i+0.5)/width);
	// pixelLoc is the linear composition of origin + up + right
	Point3D pixelLoc = viewOrigin + upComponent + rightComponent;

	// direction to point is the pixel location, minus the origin, normalized
	Point3D dir = (pixelLoc - camOrigin).unit(); 
	// reutrn a ray cast from origin in the specified direction
	return Ray3D(camOrigin, dir);
}

Point3D RayScene::GetColor(Ray3D ray, int rDepth, Point3D cLimit) {
	// for gathering info about the intersection
	RayIntersectionInfo iInfo;
	// 
	int t = group -> intersect(ray, iInfo);

	// case of no hit, return background color
	if (t < 0)
		return background;

	// calculate ambient light
	Point3D totalAmbient = ambient * iInfo.material -> ambient;
	// calculate emissive light
	Point3D emissive = iInfo.material -> emissive;

	Point3D totalDiffuse, totalSpecular; //initialized to <0,0,0>
	// total diffuse and specular will be the sum total from all lights in the scene
	for (int i = 0; i < lightNum; i++) {
		Point3D transFactor = lights[i] -> transparency(iInfo, group, cLimit);
		totalDiffuse += lights[i] -> getDiffuse(ray.position, iInfo);
		totalDiffuse *= transFactor;
		totalSpecular += lights[i] -> getSpecular(ray.position, iInfo);
		totalSpecular *= transFactor;
	}
	//total direct light at surface
	Point3D totalDirect = totalAmbient + emissive + totalDiffuse + totalSpecular;

	//Global illumination stuff
	Point3D reflectColor, refractColor; //initialized to <0,0,0>

	Point3D kSpec = iInfo.material -> specular; //transparency of material
	Point3D kTran = iInfo.material -> transparent; 
	
	// compute reflection
	if (rDepth > 0 && kSpec.length() > cLimit.length()) {
		Ray3D reflectRay;
		reflectRay.direction = Reflect(ray.direction, iInfo.normal);
		reflectRay.position = iInfo.iCoordinate + reflectRay.direction*0.0001f; //to prevent self-intersection

		// get the color from the relfection
		reflectColor = GetColor(reflectRay, rDepth-1, cLimit/kSpec);
		//don't add in a background reflection
		if (reflectColor[0] == background[0] && reflectColor[1] == background[1] && reflectColor[2] == background[2])
			reflectColor = Point3D(); //black

		reflectColor *= kSpec;
	}

	// compute refraction
	if (rDepth > 0 && kTran.length() > cLimit.length()) {
		Ray3D refractRay;
		refractRay.direction = ray.direction; //transparent follows same direction
		refractRay.position = iInfo.iCoordinate + refractRay.direction*0.0001f;
		refractColor = GetColor(refractRay, rDepth-1, cLimit/kTran);
		//stop when you hit the background
		if (refractColor[0] == background[0] && refractColor[1] == background[1] && refractColor[2] == background[2])
			refractColor = Point3D(); //black

		refractColor *= kTran;
	}

	//total global light at surface (reflect, refract)
	Point3D totalGlobal = reflectColor + refractColor;

	Point3D totalLight = totalDirect + totalGlobal;
	//check for overflow
	for (int i = 0; i < 3; i++)
		if (totalLight[i] > 1) totalLight[i] = 1;

	return totalLight;
}
