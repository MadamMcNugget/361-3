#include <chess.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/***************************************************
	Some Stuff to handle Chess Boards
	Since there exist only 1 Chess Board, 
	intersect chess includes only function 
	to see if it interect chess board or not. 
	If it does not, returns null, 
	If it does, return the */

//	RGB_float phong(Point q, Vector v, Vector surf_norm, Spheres *sph) // q = eyepos, v = ray


float intersect_chess(Point o, Vector u, Point *hit, int type)
{
	Point p = get_point(o, u);
	Vector a = (0,0,0);
	Vector b = (0,1,0);
	Vector c = (0,0,0);
	Vector d = (0,-2,0);
	Vector u = (a*o.x + b*o.y + c*o.z + d) / 
			( a*(o.x-p.x) + b*(o.y-p.y) + c*(o.z-p.z) );

	return u;
}
/*
bool linePlaneIntersection(Vector& contact, Vector ray, Vector rayOrigin, Vector normal, Vector coord) {

    // calculate plane
    float d = Dot(normal, coord);

    if (Dot(normal, ray)) {
        return false; // avoid divide by zero
    }

    // Compute the t value for the directed line ray intersecting the plane
    float t = (d - Dot(normal, rayOrigin)) / Dot(normal, ray);

    // scale the ray by t
    Vector newRay = ray * t;

    // calc contact point
    contact = rayOrigin + newRay;

    if (t >= 0.0f && t <= 1.0f) {
        return true; // line intersects plane
    }
    return false; // line does not
}
*/