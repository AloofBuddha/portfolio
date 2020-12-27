w#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include "rayPointLight.h"
#include "rayScene.h"

Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){

	//calculate light intensity at object
	double d = (iInfo.iCoordinate - location).length(); //distance of light source to object
	double attenFactor = constAtten + d*linearAtten + d*d*quadAtten;
	Point3D intensity = color/attenFactor;
	
	//sanity-check light computation (rgb is [0,1])
	for (int i = 0; i < 3; i++) {
		if (intensity[i] > 1) intensity[i] = 1;
		if (intensity[i] < 0) intensity[i] = 0;
	}
	//compute diffuse with relation to surface
	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	if (lightDir.dot(iInfo.normal) < 0) //backfacing polygon
		return Point3D();
	Point3D diffuse = (iInfo.material -> diffuse) * intensity * (iInfo.normal).dot(lightDir);

	//sanity-check light computation (rgb is [0,1])
	for (int i = 0; i < 3; i++) {
		if (diffuse[i] > 1) diffuse[i] = 1;
		if (diffuse[i] < 0) diffuse[i] = 0;
	}
	return diffuse;
}

//Note: Reflective direction calculation via: 
// http://en.wikipedia.org/wiki/Phong_reflection_model
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	//calculate light intensity at object
	double d = (iInfo.iCoordinate - location).length(); //distance of light source to object
	double attenFactor = constAtten + d*linearAtten + d*d*quadAtten;
	Point3D intensity = color/attenFactor;
	
	//sanity-check light computation (rgb is [0,1])
	for (int i = 0; i < 3; i++) {
		if (intensity[i] > 1) intensity[i] = 1;
		if (intensity[i] < 0) intensity[i] = 0;
	}
	//compute specular with relation to surface
	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	Point3D viewerDir = (cameraPosition - iInfo.iCoordinate).unit();
	if (lightDir.dot(iInfo.normal) < 0) //backfacing polygon
		return Point3D();
	Point3D reflectDir = (iInfo.normal * 2 * lightDir.dot(iInfo.normal)) - lightDir;
	double highlightDegree = pow(viewerDir.dot(reflectDir), iInfo.material -> specularFallOff);
	Point3D specular = (iInfo.material -> specular) * intensity * highlightDegree;

	//sanity-check light computation (rgb is [0,1])
	for (int i = 0; i < 3; i++) {
		if (specular[i] > 1) specular[i] = 1;
		if (specular[i] < 0) specular[i] = 0;
	}
	return specular;
}

int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	RayIntersectionInfo tempInfo;

	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	double d = (iInfo.iCoordinate - location).length(); //distance of light source to object

	Point3D pointAdjust = lightDir*0.0001f; //to prevent self-intersection
	Ray3D ray(iInfo.iCoordinate + pointAdjust, lightDir);
	double t = shape -> intersect(ray, tempInfo, d);
	//note, shape in question will need to be group
	if (t > 0)
		return 1;
	else
		return 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo, RayShape* shape, Point3D cLimit) {
	RayIntersectionInfo tempInfo = iInfo;
	Point3D kTran;

	Point3D lightDir = (location - iInfo.iCoordinate).unit(); //dir from surface to light source
	double d = (iInfo.iCoordinate - location).length(); //distance of light source to object

	Point3D pointAdjust = lightDir*0.0001f; //to prevent self-intersection
	Ray3D ray(iInfo.iCoordinate + pointAdjust, lightDir);


	Point3D transVal(1,1,1);
    do {
    	//intersect closest shape
		double t = shape -> intersect(ray, tempInfo, d);
		kTran = tempInfo.material -> transparent; 
		
		if (t < 0) break;// hit the light

		//in case of intersection, update transVal
		transVal *= kTran;
		//iterate to next intersection
		ray.position = tempInfo.iCoordinate + pointAdjust;
		cLimit /= kTran;

	} while (kTran.length() > cLimit.length());

	return transVal;
}
