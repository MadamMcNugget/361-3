#include "sphere.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;


/**********************************************************************
 * This function intersects a ray with a given sphere 'sph'. You should
 * use the parametric representation of a line and do the intersection.
 * The function should return the parameter value for the intersection, 
 * which will be compared with others to determine which intersection
 * is closest. The value -1.0 is returned if there is no intersection
 *
 * If there is an intersection, the point of intersection should be
 * stored in the "hit" variable
 **********************************************************************/
float intersect_sphere(Point o, Vector u, Spheres *sph, Point *hit, int type) 
{
  float a = pow(u.x,2) + pow(u.y,2) + pow(u.z,2);
  float b = 2 * ( u.x * (o.x - sph->center.x) + u.y * (o.y - sph->center.y) + u.z * (o.z - sph->center.z) );
  float c = pow(o.x - sph->center.x , 2) + pow(o.y - sph->center.y , 2) + pow(o.z - sph->center.z , 2) - pow(sph->radius, 2);

  float d = b*b - 4*a*c;
  if (d <0)
    return -1.0;
  else {
      float t1 = (-b - sqrt(b*b - 4*a*c))/(2*a);
      float t2 = (-b + sqrt(b*b - 4*a*c))/(2*a);
      if(type == 1){
        if(t1 > 0.001 || t2 > 0.001)
            return 1;
        return 0;
      }
      if (t1 >= 0) {   // if t1 is positive
          Point p;
          p.x = o.x + u.x*t1;
          p.y = o.y + u.y*t1;
          p.z = o.z + u.z*t1;
          hit->x=p.x;
          hit->y=p.y;
          hit->z=p.z;
      
        return t1;
    }

    else { 
        return -1.0;
    }

}}

// Also need intersect floor here!!!!!!!!!

/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
Spheres *intersect_scene(Point o, Vector u, Spheres *slist, Point *hit, int i) 
{
//
// do your thing here
//
// Does not return the closest point of contact!!!!!!!!!!! fix later  

    Spheres *sph=NULL;
    Spheres *cur=slist;
    Point curHit;


  if (slist == NULL) { // no spheres
    return NULL;
  } 
   if(i == 1){
    while(cur){
      if(intersect_sphere(o, u, cur, &curHit, i) == 1){
        return cur;
      }
      cur = cur->next;
    }
    return NULL;
  }
float t = 100000;

  
  while (cur!= NULL){
    float temp = intersect_sphere(o,u,cur,&curHit, i);
    if (temp != -1) {
      if(temp<t){
          sph = cur;
          t = temp;
          hit->x = curHit.x;
          hit->y = curHit.y;
          hit->z = curHit.z;
      }
    }
    cur = cur->next;
  }
  return sph;
/*
  while (cur!=NULL) {
    float temp = intersect_sphere(o, u, slist, hit);
    if (temp >= 0) {
      if (temp < t) {
        t = temp;
        sph = cur;
      }
    }
    cur = cur->next;
  }
  return sph;*/







  /*else if ( sizeof(slist) == 1) {
    //Spheres sph = slist;








    int num_sphere = 3;
  
    for (int i=0 ; i<num_sphere ; i++) {
      float f1 = intersect_sphere(o, u, slist, hit);
      if (f1 < 0) {

        return NULL;
      }
      else 
      {

        if (sph == NULL) {

          sph = slist;
          sph->next = NULL;
          slist = slist->next;
        }
        else {
          sph->next = slist;
          slist = slist->next;
          sph = sph->next;
          sph->next = NULL;
                    cout<<"test1"<<endl;
        }
      }
    }
  }
return sph;*/
/*
if (slist == NULL) { // first object
    slist = new_sphere;
  } else { // insert at the beginning
    new_sphere->next = slist;
    slist = new_sphere;
  }*/
         /*float f3 = intersect_sphere(o, u, slist->next->next, hit);
      if (f3 < 0)
        return NULL;
      else {
        return slist;*/

    
  /*
  else {
    Spheres sph;
    float f1 = intersect_sphere(o, u, slist, hit);
    if (f1 >= 0)
      sph = slist;

    while

  }*/


  /*
  else if (sizeof slist == 1) 
  {
    float f1 = intersect_sphere(o, u, slist, hit);
    if (f1 < 0)
  }
  else {
    {
    float f1 = intersect_sphere(o, u, slist, hit);
    if (f1 < 0)
      return NULL;
    else
      return slist;
    }

  }*/

}

/*****************************************************
 * This function adds a sphere into the sphere list
 *
 * You need not change this.
 *****************************************************/
Spheres *add_sphere(Spheres *slist, Point ctr, float rad, float amb[],
		    float dif[], float spe[], float shine, 
		    float refl, int sindex) {
  Spheres *new_sphere;

  new_sphere = (Spheres *)malloc(sizeof(Spheres));
  new_sphere->index = sindex;
  new_sphere->center = ctr;
  new_sphere->radius = rad;
  (new_sphere->mat_ambient)[0] = amb[0];
  (new_sphere->mat_ambient)[1] = amb[1];
  (new_sphere->mat_ambient)[2] = amb[2];
  (new_sphere->mat_diffuse)[0] = dif[0];
  (new_sphere->mat_diffuse)[1] = dif[1];
  (new_sphere->mat_diffuse)[2] = dif[2];
  (new_sphere->mat_specular)[0] = spe[0];
  (new_sphere->mat_specular)[1] = spe[1];
  (new_sphere->mat_specular)[2] = spe[2];
  new_sphere->mat_shineness = shine;
  new_sphere->reflectance = refl;
  new_sphere->next = NULL;

  if (slist == NULL) { // first object
    slist = new_sphere;
  } else { // insert at the beginning
    new_sphere->next = slist;
    slist = new_sphere;
  }

  return slist;
}

/******************************************
 * computes a sphere normal - done for you
 ******************************************/
Vector sphere_normal(Point q, Spheres *sph) {
  Vector rc;

  rc = get_vec(sph->center, q);
  normalize(&rc);
  return rc;
}
