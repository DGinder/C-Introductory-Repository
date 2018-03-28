/*-----------------------------------------------------------*/
/*  radius_outside_circle.c                                  */
/*  This function will calculate the radius of a circle      */
/*  circumscribed about a triangle.                          */

#include <math.h>
#include "lab6.h"

double radius_outside_circle(double a, double b, double c)
{
    double s, radius;
    s = semi_perimeter(a, b, c);
    radius =  (a * b * c) / (4 * sqrt(s * (s-a) * (s-b) * (s-c) ) );
    return radius;
}
/*-----------------------------------------------------------*/
