/*-----------------------------------------------------------*/
/*  radius_inside_circle.c                                   */
/*  This function will calculate the radius of a circle      */
/*  inscribed in a triangle.                                 */

#include <math.h>
#include "lab6.h"

double radius_inside_circle(double a, double b, double c)
{
    double s, radius;
    s = semi_perimeter(a, b, c);
    radius = sqrt( (s-a)*(s-b)*(s-c) ) / s ;
    return radius;
}
/*-----------------------------------------------------------*/
