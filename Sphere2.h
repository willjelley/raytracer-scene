/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_SPHERE2
#define H_SPHERE2

#include "Object.h"

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class Sphere2 : public Object
{

private:
    Vector center;
    float radius;

public:	
	Sphere2()
		: center(Vector()), radius(1)  //Default constructor creates a unit sphere
	{
		color = Color::WHITE;
	};
	
    Sphere2(Vector c, float r, Color col)
		: center(c), radius(r)
	{
		color = col;
	};

	float intersect(Vector pos, Vector dir);

	Vector normal(Vector p);

};

#endif //!H_SPHERE2
