/*-----------------------------------------------------------*/
/* semi_perimeter.c                                          */
/* Function to compute the semi_perimeter of a triangle      */
/* for use in the radius functions                           */

#include "lab6.h"

double semi_perimeter(double a, double b, double c)
{
    double s;
    s = 0.5 * (a + b + c);
    return s;
}
/*-----------------------------------------------------------*/
