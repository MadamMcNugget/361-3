#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "global.h"
#include "sphere.h"

//
// Global variables
//
extern int win_width;
extern int win_height;

extern GLfloat frame[WIN_HEIGHT][WIN_WIDTH][3];  

extern float image_width;
extern float image_height;

extern Point eye_pos;
extern float image_plane;
extern RGB_float background_clr;
extern RGB_float null_clr;

extern Spheres *scene;

// light 1 position and color
extern Point light1;
extern float light1_ambient[3];
extern float light1_diffuse[3];
extern float light1_specular[3];

// global ambient term
extern float global_ambient[3];

// light decay parameters
extern float decay_a;
extern float decay_b;
extern float decay_c;

extern int shadow_on;
extern int step_max;

//sphere params
//extern float reflectance;
extern Spheres *slist;

/////////////////////////////////////////////////////////////////////

/*********************************************************************
 * Phong illumination - you need to implement this!
 *********************************************************************/
RGB_float phong(Point q, Vector v, Vector surf_norm, Spheres *sph) 
{
  //
  // do your thing here
  //
/*
  Point p;
  p.x = 0;
  p.y = 0;
  p.z = 0;

  float d = vec_minus(q, light1); 
  Vector r = vec_minus( ( vec_mult(surf_norm, 2*vec_dot(surf_norm, v)) ), v );
  Vector vv = get_vec(eye_pos, q);

  float col1;*/

	RGB_float color = {1,1,1 };
/*
  col1 = sph->reflectance*global_ambient[0] + light1_ambient[0]*sph->mat_ambient[0] + 
        ( 1 / (decay_a + decay_b*d + decay_c*d*d)) * 
        (light1_diffuse[0]*sph->mat_diffuse[0]*vec_dot(surf_norm, v) + 
         light1_specular[0]*sph->mat_specular[0]*pow(vec_dot(r, vv), sph->mat_shineness));

  color.r = col1;
  color.g = col1;
  color.b = col1;*/

	return color;
}

/************************************************************************
 * This is the recursive ray tracer - you need to implement this!
 * You should decide what arguments to use.
 ************************************************************************/
RGB_float recursive_ray_trace(Point p, Vector v, int step) {
//
// do your thing here
//
  RGB_float color;

  Point hit;
  Spheres *sph;
  sph = intersect_scene(p, v, scene, &hit, 0);

  if (sph==NULL)
    color = background_clr;
  else
    color = {1,1,1};
	return color;
}

/*********************************************************************
 * This function traverses all the pixels and cast rays. It calls the
 * recursive ray tracer and assign return color to frame
 *
 * You should not need to change it except for the call to the recursive
 * ray tracer. Feel free to change other parts of the function however,
 * if you must.
 *********************************************************************/
void ray_trace() {
  int i, j;
  float x_grid_size = image_width / float(win_width);
  float y_grid_size = image_height / float(win_height);
  float x_start = -0.5 * image_width;
  float y_start = -0.5 * image_height;
  RGB_float ret_color;
  Point cur_pixel_pos;
  Vector ray;
  //Spheres sph;

  //Point *p;
  /*p.x = 0;
  p.y = 0;
  p.z = 0;*/

  // ray is cast through center of pixel
  cur_pixel_pos.x = x_start + 0.5 * x_grid_size;
  cur_pixel_pos.y = y_start + 0.5 * y_grid_size;
  cur_pixel_pos.z = image_plane;

  for (i=0; i<win_height; i++) {
    for (j=0; j<win_width; j++) {
      ray = get_vec(eye_pos, cur_pixel_pos);
      //sph = intersect_scene(eye_pos, ray, slist, &p, 0);
      //Vector norm = sphere_normal(eye_pos, sph);
      //
      // You need to change this!!!
      //
      // ret_color = recursive_ray_trace();

      //int inters = intersect(eye_pos, ray, sph); 

      /*if (inters >= 0)
        ret_color = phong(eye_pos, ray, norm, sph);
      else */
      //ret_color = background_clr; // just background for now

      // Parallel rays can be cast instead using below
      //
      // ray.x = ray.y = 0;
      // ray.z = -1.0;
      ret_color = recursive_ray_trace(cur_pixel_pos, ray, 1);

      // Checkboard for testing
      //RGB_float clr = {float(i/32), 0, float(j/32)};
      //ret_color = clr;

      frame[i][j][0] = GLfloat(ret_color.r);
      frame[i][j][1] = GLfloat(ret_color.g);
      frame[i][j][2] = GLfloat(ret_color.b);

      cur_pixel_pos.x += x_grid_size;
    }

    cur_pixel_pos.y += y_grid_size;
    cur_pixel_pos.x = x_start;
  }
}
