//============================================================
// STUDENT NAME: Guo Xinying
// STUDENT NO.: A0226488R
// NUS EMAIL ADDRESS: e0634969@u.nus.edu
// COMMENTS TO GRADER: 
// 
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
	// shifts the ray to the frame of the sphere as the sphere isn't centered at the origin
	Vector3d newRay_Origin = r.origin() - center;

	double a = 1;
	double b = 2 * dot(r.direction(), newRay_Origin);
	double c = dot(newRay_Origin, newRay_Origin) - radius * radius;

	double disc = b * b - 4 * a * c;

	// means there's no intersection at all
	if (disc < 0)
		return false;

	//calculates the t value and checks if it lies within the threshold
	else {
		double t0 = (-b + pow(disc, 0.5)) / (a * 2);
		double t1 = (-b - pow(disc, 0.5)) / (a * 2);
		double t;

		if (t0 < tmin && t1 < tmin) {
			return false;
		}
		else if (t0 >= tmin && t1 <= tmin) {
			t = t0;
		}
		else if (t0 <= tmin && t1 >= tmin) {
			t = t1;
		}
		else {
			t = min(t0, t1);
		}

		if (t < tmin || t > tmax) {
			return false;
		}

		rec.t = t;
		rec.p = r.pointAtParam(t);
		Vector3d temp = rec.p - center;
		rec.normal = temp / temp.length();
		rec.mat_ptr = matp;

		return true;
	}
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

	Vector3d newRay_Origin = r.origin() - center;

	double a = 1;
	double b = 2 * dot(r.direction(), newRay_Origin);
	double c = dot(newRay_Origin, newRay_Origin) - radius * radius;

	double disc = b * b - 4 * a * c;

	if (disc < 0) {
		return false;
	}
	else {
		double t0 = (-b + pow(disc, 0.5)) / (a * 2);
		double t1 = (-b - pow(disc, 0.5)) / (a * 2);
		double t;
		if (t0 < tmin && t1 < tmin) {
			return false;
		}
		else if (t0 >= tmin && t1 <= tmin) {
			t = t0;
		}
		else if (t0 <= tmin && t1 >= tmin) {
			t = t1;
		}
		else {
			t = min(t0, t1);
		}

		return (t <= tmax);
	}
}
