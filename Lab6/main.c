/*-------------------------------------------------------*/
/* Ruthann Biel.                                         */
/* Lab 6 for CSC 60                       	         */
/* Given the sides of a triangle, find the radius of     */
/* circles, one inscribed in a triangle, and the other   */
/* circumscribed about a triangle.                       */

#include <stdio.h>
#include <stdlib.h>
#include "lab6.h"

#define IN_FILE "lab6.dat"
#define OUT_FILE "lab6.out"


/*-----------------------------------------------------------*/

int main(void)
{
    double a, b, c;	/* sides of the triangle */
    double radius_in;	/* radius of the inside circle */	
    double radius_out;	/* radius of the outside circle */

    FILE * data_in;      /* input file pointer */
    FILE * data_out;     /* output file pointer */


    /* Open the two required files */
    data_in = fopen(IN_FILE, "r");
    if (data_in == NULL)
    {
       printf("Error on fopen file %s \n", IN_FILE);
       exit(EXIT_FAILURE);
    }

    data_out = fopen(OUT_FILE, "w");
    if (data_out == NULL)
    {
       printf("Error on fopen file %s \n", OUT_FILE);
       exit(EXIT_FAILURE);
    }

    /* Print headers */
    fprintf(data_out, "\nYour name here.  Lab 6. \n\n");
    fprintf(data_out, "    Triangle Sides        Radius Of Circle    \n");
    fprintf(data_out, "    A      B      C       Inside   Outside    \n");
    fprintf(data_out, "-----------------------   ------   -------    \n");

    while ((fscanf(data_in, "%lf%lf%lf", &a, &b, &c))== 3)
    {
       radius_in  = radius_inside_circle(a, b, c);
       radius_out = radius_outside_circle(a, b, c);
       fprintf(data_out," %5.2f   %5.2f   %5.2lf %8.2f  %8.2f \n",
               a, b, c, radius_in, radius_out);
    }

    printf("\n");
    fclose(data_in);
    fclose(data_out);
    return EXIT_SUCCESS;
}
/*-----------------------------------------------------*/
