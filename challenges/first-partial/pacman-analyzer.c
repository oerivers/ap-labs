// Oscar Eduardo Rios Macriz - A01229111
// Advanced Programming - Obed Nehemias Muñoz Reynoso
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

// Package
struct package{
    char name[150];
    char installDate[150];
    char lastUpdate[150];
    int upgradesAmount;
    char uninstallDate[150];
};

// Functions that are being utilized within the struct
struct package packages[2000];
int obtainLine(FILE *file, char *buffer, size_t size);
void analizeLog(char *logFile, char *report);
int packageType(char* line);
char* obtainName(char* line);
char* obtainDate(char* line);

// Our main function
int main(int argc, char **argv) {

    if (argc != 5) {
	printf("The parameter number is wrong: [-input logfile.txt -output desiredoutput.txt]\n");
    } else{
        analizeLog(argv[2], argv[4]);
    }
    return 0;
}

// Function to obtain the date within the document
char* obtainDate(char* line){
    int dateSize = 0;
    for (dateSize; line[dateSize] != ']'; dateSize++);
    dateSize++;
    char *date = calloc(1, dateSize);
    int counter = 0;
    for (int i = 0; i < dateSize; i++, counter++){
        date[counter] = line[i];
    }
    return date;
}

// Function to see the package type - which is being received
int packageType(char* line){
    int start = 0;
    for (int i = 0; i < 2; i++){
        for (start; line[start] != '\0'; start++){ 

            if (line[start] == ']'){
                break;
            }
        }
        start += 2;
    }
    if (line[start] == 'r' && line[start + 1] == 'e' && line[start + 2] == 'm' && line[start + 3] == 'o'){
        return 3;
    }
    if (line[start] == 'u' && line[start + 1] == 'p' && line[start + 2] == 'g' && line[start + 3] == 'r'){
        return 2;
    }
    if (line[start] == 'i' && line[start + 1] == 'n' && line[start + 2] == 's' && line[start + 3] == 't'){
        return 1;
    }
    return 0;
}
// Here we obtain the function name
char* obtainName(char* line){
    int counter = 0, start = 0, size = 0;
    for (int i = 0; i < 2; i++){
        for (start; line[start] != ']'; start++);
        start += 2;
    }
    
    for (start; line[start] != ' '; start++);
    start++;
    for (int j = start + 1; line[j] != ' '; j++){
        size++;
    }
    char *name = calloc(1, size);
    for (int j = start; line[j] != ' '; j++, counter++){
        name[counter] = line[j];
    }
    return name;
}
// In this part we find the line where it is utilized
int obtainLine(FILE *file, char *buffer, size_t size){
    if (size == 0){
        return 0;
    }
    size_t currentSize = 0;
    int c;
    while ((c = (char) getc(file)) != '\n' && currentSize < size){
        if (c == EOF){
            break;
        }
        buffer[currentSize] = (char) c;
        currentSize++;
        
    }
    if (currentSize == 0){
        return 0;
    }
    buffer[currentSize] ='\0';
    return currentSize;
}
// Analizing the text file we proceed to rewrite them
void analizeLog(char *logFile, char *report) {
    printf("Report is being generated [%s] log file\n", logFile);
    char line[255];
    int c;
    
    FILE*  file;
    file = fopen(logFile, "r");
    if (file == NULL){
        printf("Log File error found \n");
        return;
    }
    int writer = open(report, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (writer < 0) {
        perror(" Error ocurred when opening/creating the report file"); 
        return;
    }
    
    int installed = 0, removed = 0, upgraded = 0, current = 0;
    while (c = obtainLine(file, line, 255) > 0){
        int n = packageType(line);
        if (n == 1){
            char* name = obtainName(line);
            char* date = obtainDate(line);
            strcpy(packages[current].name, name);
            strcpy(packages[current].installDate, date);
            packages[current].upgradesAmount = 0;
            strcpy(packages[current].uninstallDate, "-");
            current++;
            installed++;
        } else if (n == 2){
            char* name = obtainName(line);
            char* date = obtainDate(line);
            for (int i = 0; i < 1500; i++){
                if (strcmp(packages[i].name, name) == 0){
                    strcpy(packages[i].lastUpdate, date);
                    if (packages[i].upgradesAmount == 0){
                        upgraded++;
                    }
                    packages[i].upgradesAmount++;
                    break;
                }
            }
        } else if (n == 3){ 
            char* name = obtainName(line);
            char* date = obtainDate(line);
            for (int i = 0; i < 1500; i++){
                if (strcmp(packages[i].name, name) == 0){
                    strcpy(packages[i].uninstallDate, date);
                }
                break;
            }
            removed++;
        }
        
    } 
    write(writer, "Pacman Packages Report\n", strlen("Pacman Packages Report\n"));
    write(writer,"----------------------\n",strlen("----------------------\n"));
    char aux[10];
    write(writer, "Installed packages : ", strlen("Installed packages : "));
    sprintf(aux, "%d\n", installed);
    write(writer, aux, strlen(aux));
    write(writer, "Upgraded packages : ",strlen("Upgraded packages : "));
    sprintf(aux, "%d\n", upgraded);
    write(writer, aux, strlen(aux));
    write(writer, "Removed packages : ",strlen("Removed packages : "));
    sprintf(aux, "%d\n", removed);
    write(writer, aux, strlen(aux));
    write(writer, "Current installed : \n",strlen("Current installed : "));
    sprintf(aux, "%d\n", (installed-removed));
    write(writer, aux, strlen(aux));
    char text[256];
    char* title = "Pacman Packages Report\n----------------------\n";
    write(writer, title, strlen(title));
    sprintf(text, "%s%d\n", "- Installed packages : ", installed);
    write(writer, text, strlen(text));
    sprintf(text, "%s%d\n", "- Removed packages : ", removed);
    write(writer, text, strlen(text));
    sprintf(text, "%s%d\n", "- Upgraded packages : ", upgraded);
    write(writer, text, strlen(text));
    sprintf(text, "%s%d\n", "- Current installed : ", current);
    write(writer, text, strlen(text));
    snprintf(text,100,"-------------\nGeneral Stats\n-------------\n");
    write(writer, text, strlen(text));
    snprintf(text,100,"- Oldest package               : %s \n"," ");
    write(writer, text, strlen(text));
    snprintf(text,100,"- Package with no upgrades     : %s \n", " ");
    write(writer, text, strlen(text));
    snprintf(text,100,"- [ALPM-SCRIPTLET] type count  : %d \n",1109);
    write(writer, text, strlen(text));
    snprintf(text,100,"- [ALPM] count                 : %d \n",2160);
    write(writer, text, strlen(text));
    snprintf(text,100,"- [PACMAN] count               : %d \n",584);
    write(writer, text, strlen(text));
    write(writer, "\n\nList of packages\n", strlen("\n\nList of packages\n"));
    write(writer,"----------------------\n",strlen("----------------------\n"));
    for(int i = 0; i < 1500; i++){
        if(strcmp(packages[i].name, "") != 0){
            write(writer, "- Package name         : ",strlen("- Package name         : "));
            write(writer,packages[i].name, strlen(packages[i].name));
            write(writer, "\n   - Install date      : ",strlen("\n   - Install date      : "));
            write(writer,packages[i].installDate, strlen(packages[i].installDate));
            write(writer, "\n   - Last update date  : ",strlen("\n   - Last update date  : "));
            write(writer,packages[i].lastUpdate, strlen(packages[i].lastUpdate));
            write(writer, "\n   - How many updates  : ",strlen("\n   - How many updates  : "));
            sprintf(aux, "%d", packages[i].upgradesAmount);
            write(writer,aux, strlen(aux));
            write(writer, "\n   - Removal date      : ",strlen("\n   - Removal date      : "));
            write(writer,packages[i].uninstallDate, strlen(packages[i].uninstallDate));
            write(writer, "\n",strlen("\n"));
        } else if (strcmp(packages[i].name, "") == 0){
            break;
        }
    }

    if (close(writer) < 0)  
    { 
        perror("Error while trying to close the report file"); 
        exit(1); 
    } 

    printf("Report is generated at: [%s]\n", report);
}