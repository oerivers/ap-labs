// Oscar Eduardo Rios Macriz - A01229111
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char ** argv)
{
    if(strtol(argv[2], NULL, 10) > 366){
        printf("Invalid Date and it is illegal!\n");
        return 0;
    }

    if (argc < 3) 
    {
    printf("./mont_day.o <year> <yearday>\n");
    return 1;
    }

    int pmonth = 0;
    int pday = 0;
    int year = atoi(argv[1]);
    int yearday = atoi(argv[2]);
    month_day(year, yearday, &pmonth, &pday);
    printf(" %d, %s\n", pday, argv[1]);
    return 0;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    static char dayt[2][13] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
    static char *months[13] = {"This month ILLEGAL","January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    int i, leap, prevS, currentS;
    i = leap = prevS = currentS = 0;
    leap = (year%4 == 0 && year%100 != 0) || year%400 ==0;

    for(; yearday > currentS; i++){
        prevS = currentS;
        currentS += dayt[leap][i];
    }
    *pday = yearday - prevS;
    *pmonth = i;

    printf("%s", months[i-1]);
}