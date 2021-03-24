//Oscar Eduardo Rios Macriz - A01229111
#include <stdio.h>
#include <stdlib.h>

int mystrlen(char *);
char *mystradd(char *,char *);
int mystrfind(char *,char *);

int main(int argc, char *argv[]) {
    char *string = (char *)malloc(sizeof(char *)),
         *string2 = (char *)malloc(sizeof(char *)),
         *r = (char *)malloc(sizeof(char *));
    string = argv[2];
    string2 = argv[3];
    if (mystrfind(argv[1],"-add")==0 && argc == 4)
    {
        printf("Initial Length\t: %d\n", mystrlen(string));
        mystradd(string,string2);
        printf("The new string\t: %s\n", string);
        printf("The new length\t: %d\n", mystrlen(string));
        return 0;
    }
    else if(mystrfind(argv[1],"-find")==0 && argc == 4)
    {
        printf("[%s] the string found was at [%d] position\n", string2,mystrfind(string,string2));
    }
    else
    {
        return 0;
    }
    
}