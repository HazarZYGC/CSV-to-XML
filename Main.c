#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char Unix[] = "\n";
const char Windows[] = "\r\n";
const char Mac[] = "\r";
const char comma = ',';
const char tab = '/t';
const char semicolon = ';';



char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
struct row {
    char *email;
    char *phoneNumber;
    char *address;
    char *first;
    char *last;
};
typedef struct row row;

int fileOp(){
    row newRow;
    ////////opening xml file.
    FILE  *fp = fopen("Contacts.xml","w"); //open a stream with r, w, a modes
    if(fp == NULL)
    {
        puts("error opening file!");
        exit (1);
    }
    //
    char *tmp;
    FILE* stream = fopen("contacts.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        tmp = strdup(line);
        newRow.first = getfield(tmp,1);
        tmp = strdup(line);tmp = strdup(line);
        newRow.last = getfield(tmp,2);
        tmp = strdup(line);
        newRow.email = getfield(tmp,3);
        tmp = strdup(line);
        newRow.phoneNumber = getfield(tmp,4);
        tmp = strdup(line);
        newRow.address = getfield(tmp,5);
        fprintf(fp, "%s %s %s %s %s\n", newRow.first, newRow.last, newRow.email, newRow.phoneNumber, newRow.address); 
        puts("Record written...");//printf("writing was finished...\n");
        
        //printf("Field 3 would be %s\n", getfield(tmp, 5));
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(fp);
}
int main()
{
    opsys = 1;
   // fileOp()
   printf("aga be\tne");
                                            
}