//Oscar Eduardo Rios Macriz - A01229111
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int numcmp(char *first, char *second) {
    return atof(first)-atof(second);
}

void merge(char *lineptr[], int l, int m, int r, int (*comp)(void *,void *))
{
	int i = 0,
        j = 0,
        k = 0,
        first = m-l+1,
        second = r-m;

	void *left[first],
         *right[second];

	for (i=0; i<first; i++)
    {
		left[i] = lineptr[l+i];
	}
	for (i=0; i<second; i++)
    {
		right[i] = lineptr[m+i+1];
	}
	i = j = 0;
    k = l;
    while(i<first && j<second){
    	if(comp(left[i],right[j]) < 0)
        {
            lineptr[k++] = left[i++];
		}
        else
        {
            lineptr[k++] = right[j++];
		}
	}
	if (i == first)
    {
	    while(j < second)
        {
			lineptr[k++] = right[j++];
		}
	}
	else{
		while(i<first){
			lineptr[k++] = left[i++];
		}
	}
}

void mergeS(char *lineptr[], int start, int end, int (*comp)(void *,void *))
{
	int mid = start+(end-start)/2;
	if(end>start){
		mergeS(lineptr, start, mid, comp);
		mergeS(lineptr, mid+1, end, comp);
		merge(lineptr, start, mid, end, comp);
	}
}

void writeOut(char *file, int flag)
{
    int aSize = 100;
    char **aList = malloc(sizeof(char *) * aSize);

    printf("%s\n",file);
    FILE *fp = fopen(file, "r");
    if (!fp){
        printf("There was an error, file could not be opened \n");
    }

    char *linebuf = NULL;
    size_t linebufsize = 0;
    int linecount = 0;
    ssize_t linesize;

    linesize = getline(&linebuf, &linebufsize, fp);
    while (linesize >= 0)
    {
        aList[linecount] = malloc(sizeof(char) * linebufsize);
        sprintf(aList[linecount], "%s", linebuf);
        aList[linecount][strlen(linebuf) - 1] = 0;
        linecount++;
        linesize = getline(&linebuf, &linebufsize, fp);
    }

    free(linebuf);
    fclose(fp);

    if(flag == 0){
        mergeS(aList, 0, aSize - 1, (int (*)(void *, void *)) strcmp);
    }
    else if(flag ==1){
        mergeS(aList, 0, aSize - 1, (int (*)(void *, void *)) numcmp);
    }

    FILE *fpOut;
    fpOut = fopen((flag?"sorted_numbers.txt":"sorted_strings.txt"),"w");
    if (!fpOut){
        printf("There was an error, file could not be opened \n");
    }
    
    for(int i=0; i<100; i++)
    {
        fprintf(fpOut, "%s\n",aList[i]);
    }
    fclose(fpOut);
}

int main(int argc, char **argv)
{
    if (argc == 2 && strstr(argv[1],".txt")!=NULL)
    {
        writeOut(argv[1],0);
        printf("The results file is located at ./sorted_strings.txt\n");
        return 0;
    }
    else if(argc == 3 && strcmp(argv[1], "-n")==0 && strstr(argv[2],".txt")!=NULL)
    {
        writeOut(argv[2],1);
        printf("The results file is located at ./sorted_numbers.txt\n");
        return 0;
    }
    else 
    {
        return 0;
    }


}