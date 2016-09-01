/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Plane class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Plane3.h"
#include "Vector.h"
#include <math.h>

//Function to test if an input point is within the triangle.
bool Plane3::isInside(Vector q)
{
	bool inQuad = false;
	Vector n = normal(q);
	Vector ua = b-a,  ub = c-b, uc = a-c;
	Vector va = q-a,  vb = q-b, vc = q-c;
	
	bool cond1 = (ua.cross(va)).dot(n) > 0;
	bool cond2 = (ub.cross(vb)).dot(n) > 0;
	bool cond3 = (uc.cross(vc)).dot(n) > 0;
	if( cond1 && cond2 && cond3 ) inQuad = true;
	return inQuad;
	
}

//Function to compute the paramter t at the point of intersection.
float Plane3::intersect(Vector pos, Vector dir)
{
	Vector n = normal(pos);
	Vector vdif = a-pos;
	float vdotn = dir.dot(n);
	if(fabs(vdotn) < 1.e-4) return -1;
    float t = vdif.dot(n)/vdotn;
	if(fabs(t) < 0.0001) return -1;
	Vector q = pos + dir*t;
	if(isInside(q)) return t;
    else return -1;
}

// Function to compute the unit normal vector
// Remember to output a normalised vector!
Vector Plane3::normal(Vector pos)
{
	Vector normal = (b-a).cross(c-a);
	normal.normalise();
	return normal;
	
}



