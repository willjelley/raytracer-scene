
/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Plane class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_PLANE3
#define H_PLANE3

#include "Vector.h"
#include "Object.h"

class Plane3 : public Object
{
private:
    Vector a, b, c;      //The 3 vertices of a triangle

public:	
	Plane3(void);
	
    Plane3(Vector pa, Vector pb, Vector pc, Color col)
		: a(pa), b(pb), c(pc)
	{
		color = col;
	};

	bool isInside(Vector pos);
	
	float intersect(Vector pos, Vector dir);
	
	Vector normal(Vector pos);

};

#endif //!H_PLANE3
