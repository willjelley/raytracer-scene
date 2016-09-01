// ========================================================================
// COSC 363  Computer Graphics  Assignment
// Raytracer
// Author: William Jelley wpj16
// Date: 02/06/16
// ========================================================================

#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.h"
#include "Sphere.h"
#include "Color.h"
#include "Object.h"
#include <GL/glut.h>
#include "Plane.h"
#include "Plane3.h"
#include "TextureBMP.h"
using namespace std;

const float WIDTH = 20.0;  
const float HEIGHT = 20.0;
const float EDIST = 40.0;
const int PPU = 30;     //Total 600x600 pixels
const int MAX_STEPS = 5;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;
bool anti_alias = true;
float sphere_text_size = 3;
float sphere_proc_size = 2;
Vector text_center = Vector(8., -4., -60.);
TextureBMP texture;
vector<Object*> sceneObjects;

Vector light;
Vector light2;
Color backgroundCol;
Color inOneShadow = Color(0.4, 0.4, 0.4);

//A useful struct
struct PointBundle   
{
	Vector point;
	int index;
	float dist;
};

/*
* This function compares the given ray with all objects in the scene
* and computes the closest point  of intersection.
*/
PointBundle closestPt(Vector pos, Vector dir)
{
    Vector  point(0, 0, 0);
	float min = 10000.0;

	PointBundle out = {point, -1, 0.0};

    for(unsigned int i = 0;  i < sceneObjects.size();  i++)
	{
        float t = sceneObjects[i]->intersect(pos, dir);
		if(t > 0)        //Intersects the object
		{
			point = pos + dir*t;
			if(t < min)
			{
				out.point = point;
				out.index = i;
				out.dist = t;
				min = t;
			}
		}
	}

	return out;
}




//Creates a checkered plane (of numChecks) given 4 vectors (that could create a rectangle plane with constant y) and the 2 desired colours
void checkered_plane(Color check_color1, Color check_color2, Vector vec1, Vector vec2, Vector vec3, Vector vec4, int numChecks)
{
	float xMax = vec2.x;
	float xMin = vec1.x;
	float zMax = vec4.z;
	float zMin = vec1.z;
	float yVal = vec1.y;
	
	float xDist = xMax - xMin;
	float zDist = zMax - zMin;
	
	float xStep = xDist / numChecks;
	float zStep = zDist / numChecks;
	
	for (int i=0; i<numChecks; i=i+2) {
		for (int j=0; j<numChecks; j=j+2) {
			Plane *plane1 = new Plane(Vector(xMin+j*xStep, yVal, zMin+i*zStep), Vector(xMin+(j+1)*xStep, yVal, zMin+i*zStep), Vector(xMin+(j+1)*xStep, yVal, zMin+(i+1)*zStep), Vector(xMin+j*xStep, yVal, zMin+(i+1)*zStep), check_color1);
			sceneObjects.push_back(plane1);
			Plane *plane2 = new Plane(Vector(xMin+(j+1)*xStep, yVal, zMin+(i+1)*zStep), Vector(xMin+(j+2)*xStep, yVal, zMin+(i+1)*zStep), Vector(xMin+(j+2)*xStep, yVal, zMin+(i+2)*zStep), Vector(xMin+(j+1)*xStep, yVal, zMin+(i+2)*zStep), check_color2);
			sceneObjects.push_back(plane2);		
		}
	}
	
}

void drawCube (Vector center, float size_cube, Color col)
{
	float dist = size_cube / 2;		//Dist to edge of cube
	Vector v1 = Vector(center.x-dist, center.y+dist, center.z+dist);
	Vector v2 = Vector(center.x+dist, center.y+dist, center.z+dist);
	Vector v3 = Vector(center.x+dist, center.y-dist, center.z+dist);
	Vector v4 = Vector(center.x-dist, center.y-dist, center.z+dist);
	Vector v5 = Vector(center.x-dist, center.y+dist, center.z-dist);
	Vector v6 = Vector(center.x+dist, center.y+dist, center.z-dist);
	Vector v7 = Vector(center.x+dist, center.y-dist, center.z-dist);
	Vector v8 = Vector(center.x-dist, center.y-dist, center.z-dist);
	
	
	Plane *plane1 = new Plane(v1, v4, v3, v2, col);
	sceneObjects.push_back(plane1);
	Plane *plane2 = new Plane(v2, v6, v7, v3, col);
	sceneObjects.push_back(plane2);
	Plane *plane3 = new Plane(v5, v6, v7, v8, col);
	sceneObjects.push_back(plane3);
	Plane *plane4 = new Plane(v5, v8, v4, v1, col);
	sceneObjects.push_back(plane4);
	Plane *plane5 = new Plane(v3, v4, v8, v7, col);
	sceneObjects.push_back(plane5);
	Plane *plane6 = new Plane(v6, v5, v1, v2, col);
	sceneObjects.push_back(plane6);
}

void drawCube2 (Vector center, float size_cube, Color col)
{
	float dist = size_cube / 2;		//Dist to edge of cube
	Vector v1 = Vector(center.x-dist, center.y+dist, center.z+dist);
	Vector v2 = Vector(center.x+dist, center.y+dist, center.z+dist);
	Vector v3 = Vector(center.x+dist, center.y-dist, center.z+dist);
	Vector v4 = Vector(center.x-dist, center.y-dist, center.z+dist);
	Vector v5 = Vector(center.x-dist, center.y+dist, center.z-dist);
	Vector v6 = Vector(center.x+dist, center.y+dist, center.z-dist);
	Vector v7 = Vector(center.x+dist, center.y-dist, center.z-dist);
	Vector v8 = Vector(center.x-dist, center.y-dist, center.z-dist);
	
	
	Plane *plane1 = new Plane(v1, v4, v3, v2, col);
	sceneObjects.push_back(plane1);
	Plane *plane2 = new Plane(v2, v6, v7, v3, col);
	sceneObjects.push_back(plane2);
	Plane *plane3 = new Plane(v5, v6, v7, v8, col);
	sceneObjects.push_back(plane3);
	Plane *plane4 = new Plane(v5, v8, v4, v1, col);
	sceneObjects.push_back(plane4);
	Plane *plane5 = new Plane(v3, v4, v8, v7, col);
	sceneObjects.push_back(plane5);
	Plane *plane6 = new Plane(v6, v5, v1, v2, col);
	sceneObjects.push_back(plane6);
}

////Functionthat draws a tetrahedral pyramid
void drawTetra(Vector center, float size, Color col)
{
	float dist = size / 2;		//Distance to the edge
	Vector v1 = Vector(center.x, center.y-dist, center.z+dist);
	Vector v2 = Vector(center.x+dist, center.y-dist, center.z-dist);
	Vector v3 = Vector(center.x-dist, center.y-dist, center.z-dist);
	Vector v4 = Vector(center.x, center.y+dist, center.z);
	
	Plane3 *plane1 = new Plane3(v1, v2, v3, col);
	sceneObjects.push_back(plane1);
	Plane3 *plane2 = new Plane3(v1, v2, v4, col);
	sceneObjects.push_back(plane2);
	Plane3 *plane3 = new Plane3(v2, v3, v4, col);
	sceneObjects.push_back(plane3);
	Plane3 *plane4 = new Plane3(v3, v1, v4, col);
	sceneObjects.push_back(plane4);
}
	
	
	
	

/*
* Computes the colour value obtained by tracing a ray.
* If reflections and refractions are to be included, then secondary rays will 
* have to be traced from the point, by converting this method to a recursive
* procedure.
*/

Color trace(Vector pos, Vector dir, int step)
{
    PointBundle q = closestPt(pos, dir);

    if(q.index == -1) return Color(1.0, 0.6, 0.2);        //no intersection
    
	// Used for refractive stuff
    float n1 = 1.0;
	float n2 = 1.01;
   
    //Computing colour using Phongs illumination model:
    Vector n = sceneObjects[q.index]->normal(q.point);
    Vector l = light - q.point;	//Light source vector
    Vector l2 = light2 - q.point;	//Light2 source vector
    l.normalise();
    l2.normalise();
    float lDotn = l.dot(n);	//Note 'l' is letter el
    float l2Dotn = l2.dot(n);	//Note 'l2' is el 2
    Color col = sceneObjects[q.index]->getColor(); //Object's colour
    
    //Draw my checkered floor
    if (q.index == 5) {
		int x_point = int(abs(floor(q.point.x/2)));
		int z_point = int(abs(floor(q.point.z/2)));
		if ((x_point%2) == (z_point%2))
			col = Color(0.2, 0.8, 0);
	}
		
    Color colorSum;
    
	//Shadow ray intersection stuff:
    Vector lightVector = light - q.point;
    Vector lightVector2 = light2 - q.point;
    float lightDist = lightVector.length();	//Distance to light
    float lightDist2 = lightVector2.length();	//Distance to light2
    lightVector.normalise();
    lightVector2.normalise();
    
	
	//Texture image:
	if (q.index == 3 && step < MAX_STEPS) {
		float d = sphere_text_size*2;
		float u;
		float v;
		if (q.point.z > text_center.z) {
			u = (q.point.x - (text_center.x - sphere_text_size))/d;
		}
		else {
			u = 1 - (q.point.x - (text_center.x - sphere_text_size))/d;
		}	
		v = (q.point.y - (text_center.y - sphere_text_size))/d;
		if (q.point.z < text_center.z) {
			col = texture.getColorAt(u/2,v);
		}
		else {
			col = texture.getColorAt(0.5 + u/2,v);
		}	
		colorSum.combineColor(col);
	}	
    
    PointBundle s = closestPt(q.point, lightVector);
    PointBundle s2 = closestPt(q.point, lightVector2);

    if ((s.index > -1 && s.dist < lightDist) && (s2.index > -1 && s2.dist < lightDist2))
		colorSum =  col.phongLight(backgroundCol, 0.0, 0.0);
	else if ((s.index > -1 && s.dist < lightDist) || (s2.index > -1 && s2.dist < lightDist2))
		colorSum =  col.phongLight(inOneShadow, 0.0, 0.0);
		
    else if (lDotn <= 0.0 || l2Dotn <= 0.0) 
    {
		colorSum = col.phongLight(backgroundCol, 0.0, 0.0);
	}

	else
	{
		
		Vector r = ((n * 2) * lDotn) - l;	//r = 2(L.n)n - L
		r.normalise();
		Vector v(-dir.x, -dir.y, -dir.z);	//View vector
		float rDotv = r.dot(v);
		float spec;
		if (rDotv < 0) spec = 0.0;
		else spec = pow(rDotv, 10);		//Phong exponent = 10
		colorSum = col.phongLight(backgroundCol, lDotn, spec);
		colorSum.scaleColor(0.5);
		
		//Light 2 stuff
		Vector r2 = ((n * 2) * l2Dotn) - l2;	//r = 2(L.n)n - L
		r2.normalise();
		Vector v2(-dir.x, -dir.y, -dir.z);	//View vector
		float rDotv2 = r.dot(v);
		float spec2;
		if (rDotv2 < 0) spec2 = 0.0;
		else spec2 = pow(rDotv2, 10);		//Phong exponent = 10
		colorSum.combineColor(col.phongLight(backgroundCol, l2Dotn, spec2), 0.5);
	}
	float reflCoeff = 0.8;
	if (q.index == 0 && step < MAX_STEPS)
		{
			float dDotn = dir.dot(n);
			Vector re = dir -((n * 2) * dDotn);	//
			Color reflectionCol = trace(q.point, re, step+1);
			colorSum.combineColor(reflectionCol, reflCoeff);
		}	
		
	//OG transparent object!
	if (q.index == 1 && step < MAX_STEPS) {
		float transpCoeff = 0.9;
		Color transpCol = trace(q.point, dir, step+1);
		colorSum = Color(colorSum.r + transpCoeff*(transpCol.r-colorSum.r), colorSum.g + transpCoeff*(transpCol.g-colorSum.g),
						colorSum.b + transpCoeff*(transpCol.b-colorSum.b));
		//colorSum = transpCol;
	}
	
	//New refractive object:
	if (q.index == 2 && step < MAX_STEPS) {
		//float transpCoeff = 0.9;
		float dDotn = dir.dot(n);
		float cos_theta = sqrt(1-(n1/n2)*(n1/n2)*(1-(dDotn*dDotn)));
		//float cos_theta =45;
		Vector new_dir = dir*(n1/n2) - n*((n1/n2) * dDotn + cos_theta);
		new_dir.normalise();
		//Find exit point which will be "closest point":
		PointBundle q_next = closestPt(q.point, new_dir);
		float temp = n1;
		n1 = n2;
		n2 = temp;
		//Vector normal = Vector(-n.x, -n.y, -n.z);
		Vector normal = sceneObjects[q.index]->normal(q_next.point);
		normal = Vector(-normal.x, -normal.y, -normal.z);
		//normal.normalise();
		dDotn =new_dir.dot(normal);
		cos_theta = sqrt(1-(n1/n2)*(n1/n2)*(1-(dDotn*dDotn)));
		Vector final_dir = new_dir*(n1/n2) - normal*((n1/n2) * dDotn + cos_theta);	
		
		Color transpCol = trace(q_next.point, final_dir, step+1);
		colorSum.combineColor(transpCol, 1);
	}
	
		//Texture procedure sphere:
	if (q.index == 4 && step < MAX_STEPS) {
		int u = int(abs(q.point.x)/2);
		int v = int(abs(q.point.y)*2);
		if ((u%2) == (v%2)) {
			colorSum.combineColor(Color(1, 0, 0));
			}
	}
	
	return colorSum;
}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each pixel as quads.
//---------------------------------------------------------------------------------------
void display()
{
	int widthInPixels = (int)(WIDTH * PPU);
	int heightInPixels = (int)(HEIGHT * PPU);
	float pixelSize = 1.0/PPU;
	float halfPixelSize = pixelSize/2.0;
	float x1, y1, xc, yc;
	float xa, xb, ya, yb;
	Vector eye(0., 0., 0.);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);  //Each pixel is a quad.

	for(int i = 0; i < widthInPixels; i++)	//Scan every "pixel"
	{
		x1 = XMIN + i*pixelSize;
		xc = x1 + halfPixelSize;
		xa = xc - halfPixelSize / 2;
		xb = xc + halfPixelSize / 2;
		
		for(int j = 0; j < heightInPixels; j++)
		{
			y1 = YMIN + j*pixelSize;
			yc = y1 + halfPixelSize;
			ya = yc - halfPixelSize / 2;
			yb = yc + halfPixelSize / 2;
				
			Vector dir1(xa, ya, -EDIST);
			Vector dir2(xa, yb, -EDIST);
			Vector dir3(xb, ya, -EDIST);
			Vector dir4(xb, yb, -EDIST);
			
		    Vector dir(xc, yc, -EDIST);	//direction of the primary ray

		    dir.normalise();			//Normalise this direction
		    dir1.normalise();
		    dir2.normalise();
		    dir3.normalise();
		    dir4.normalise();
		    if (anti_alias == false) {
				Color col = trace (eye, dir, 1); //Trace the primary ray and get the colour value
				glColor3f(col.r, col.g, col.b);
			}
			else{
				Color col1 = trace (eye, dir1, 1);
				Color col2 = trace (eye, dir2, 1);
				Color col3 = trace (eye, dir3, 1);
				Color col4 = trace (eye, dir4, 1);
				glColor3f((col1.r+col2.r+col3.r+col4.r)/4, (col1.g+col2.g+col3.g+col4.g)/4, (col1.b+col2.b+col3.b+col4.b)/4);
			}
				
			glVertex2f(x1, y1);				//Draw each pixel with its color value
			glVertex2f(x1 + pixelSize, y1);
			glVertex2f(x1 + pixelSize, y1 + pixelSize);
			glVertex2f(x1, y1 + pixelSize);
        }
    }

    glEnd();
    glFlush();
}



void initialize()
{
	//Iniitialize background colour and light's position
	backgroundCol = Color(0.3, 0.3, 0.3);
	light = Vector(10.0, 40.0, -5.0);
	light2 = Vector(-10.0, 40.0, -5.0);
	
	//Initialise texture for texture mapping
	texture = TextureBMP("texture_mercury.bmp");


	//Add spheres to the list of scene objects here.
	Sphere *sphere2 = new Sphere(Vector(0, 4, -80), 12.6, Color::BLUE);
	sceneObjects.push_back(sphere2);
	Sphere *sphere_trans = new Sphere(Vector(5., -30, -45), 2.0, Color::RED);
	sceneObjects.push_back(sphere_trans);
	Sphere *sphere_refr = new Sphere(Vector(-1, -5, -50), 2.0, Color::GRAY);
	sceneObjects.push_back(sphere_refr);
	Sphere * sphere_textBMP = new Sphere(text_center, sphere_text_size, Color::RED);
	sceneObjects.push_back(sphere_textBMP);
	Sphere * sphere_proc = new Sphere(Vector(-11, -5, -70), sphere_proc_size, Color::GREEN);
	sceneObjects.push_back(sphere_proc);
	
	//Size parameters for plane:
	float p_y = -10.0;
	float p_x = 25;
	float p_z = 80;
	Plane *plane = new Plane(Vector(-p_x, p_y-0.01, -40), Vector(p_x, p_y-0.01, -40), 
						Vector(p_x, p_y-0.01, -40 - p_z), Vector(-p_x, p_y-0.01, -40 - p_z), Color(0.8, 0.2, 0));
	sceneObjects.push_back(plane);
	
	drawTetra(Vector(-5, 8, -63), 4.0, Color(0,0,1));
	drawCube(Vector(-8, -9, -50), 3.0, Color(0.6, 0., 0.6));
	

	//The following are OpenGL functions used only for drawing the pixels
	//of the ray-traced scene.
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
}


int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("William Jelley Raytracer");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
