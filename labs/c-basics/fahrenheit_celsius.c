#include <stdio.h>
#include <stdlib.h>

#define   LOWER  0       /* lower limit of table */
#define   UPPER  300     /* upper limit */
#define   STEP   20      /* step size */

int main(int argc, char **argv)
{
    int fahrenheit;

    if(argc < 2){
        for (fahrenheit = LOWER; fahrenheit <= UPPER; fahrenheit = fahrenheit + STEP)
	    printf("F: %3d, C: %6.1f\n", fahrenheit, (5.0/9.0)*(fahrenheit-32));
    }

    if(argc == 2){
        fahrenheit = atoi(argv[1]);
        printf("F: %3d, C: %6.1f\n", fahrenheit, (5.0/9.0)*(fahrenheit-32));
    }
    else{
        int str, end, inc, f;
        
        
         str = atoi(argv[1]);
         end = atoi(argv[2]);
         inc = atoi(argv[3]);

         for(f=str; f<= end; f= f+inc){
             printf("F: %3d, C: %6.1f\n", f, (5.0/9.0)*(f-32));
         }

    }

    return 0;
}