#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Unix[] = "\n";
char Windows[] = "\r\n";
char Mac[] = "\r";
char comma[] = ",";
char tab[] = "\t";
char semicolon[] = ";";



char* getfield(char* line, int num, char* delimeter, char* delimeter2)
{
    printf(delimeter);
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


int fileOp(char* source, char* destination, char* delimeter1, char* delimeter2){
   
    /*
    FILE *fp = fopen(source, "r"); 
    char c;
    int rowCount = 0;
    // Check if file exists 
    if (fp == NULL) 
    { 
        printf("Could not open file %s", source); 
        return 0; 
    } 
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            rowCount = rowCount + 1; 
  
    // Close the file 
    fclose(fp); 
    */
    ////////opening xml file.
    FILE  *fp = fopen(destination,"w"); //open a stream with r, w, a modes
    if(fp == NULL)
    {
        puts("error opening file!");
        exit (1);
    }
    
    //
    char *tmp;
    FILE* stream = fopen(source, "r");
    char firstLine[1024];
    fgets(firstLine, 1024, stream);
    printf("%s", firstLine);
    int columnCount = 0;
    for (int i = 0; firstLine[i] != '\0'; ++i) {
       // if (',' == firstLine[i])
         //   ++columnCount;
         printf("%c",firstLine[i]);
    }
    columnCount++;
    //rowCount--;
    



    
    char line[1024];
    char* newRow;
    int start = 1;
    int id = 1;
    int cursorTag = 0;
    int cursurBackUp = 0;
    char* root = strtok(source,".");
    fprintf(fp,"<%s>\n", root);
    while (fgets(line, 1024, stream))
    {
        
        fprintf(fp,"<row id=\"%d\">\n", id);
        
       for (cursorTag; firstLine[cursorTag] != '\0'; ++cursorTag) {
           fprintf(fp,"<");
           cursurBackUp = cursorTag;
            for (cursorTag; firstLine[cursorTag] != ','; ++cursorTag) {
                    if(firstLine[cursorTag]!=' ')
                    fprintf(fp,"%c",firstLine[cursorTag]);
                    else
                    fprintf(fp,"_");

         //   
            }
            cursorTag = cursurBackUp;
            printf("%d",cursorTag);
            fprintf(fp,">");
                
                
                     tmp = strdup(line);
                     newRow = getfield(tmp,start,delimeter1,delimeter2);
                     fprintf(fp," %s ",newRow);
                     start = start +1;
            
            fprintf(fp,"</");
                for (cursorTag; firstLine[cursorTag] != ','; ++cursorTag) {

                    if(firstLine[cursorTag]!=' ')
                    fprintf(fp,"%c",firstLine[cursorTag]);
                    else
                    fprintf(fp,"_");
         //   
            }
            fprintf(fp,">\n");
            printf("%d",cursorTag);
                
                
       
                
       }
        start=1;
       // fprintf(fp, "%s %s %s %s %s\n", newRow.first, newRow.last, newRow.email, newRow.phoneNumber, newRow.address); 
        puts("Record written...");//printf("writing was finished...\n");
        
        //printf("Field 3 would be %s\n", getfield(tmp, 5));
        // NOTE strtok clobbers tmp
        free(tmp);
        fprintf(fp,"</row>\n");
        id++;
       
    }
    fprintf(fp,"</%s>", root);
    fclose(fp);

}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}




int main(int argc, char *argv[])
{

    // Checking if number of argument is 
    // equal to 4 or not. 
    if (argc < 6 || argc > 7)  
    { 
        printf("enter arguments only eg.\"CSV2XML <inputfile> <outputfile> [-separator <P1>][-opsys <P2>][-h]!!\""); 
        return 0; 
    } 
    char* sourceDirectory = argv[1];
    char* destinationDirectory = argv[2];
    char* delimeterInteger = argv[4];
    char* opsysInteger = argv[6];
    printf("%s %s %s %s",sourceDirectory,destinationDirectory,delimeterInteger,opsysInteger);
    char* delimeter1;
    if(strcmp(delimeterInteger,"1")==0)
        delimeter1 = comma;
    else if (strcmp(delimeterInteger,"2")==0)
        delimeter1 = tab;
    else if(strcmp(delimeterInteger,"3")==0)
        delimeter1 = semicolon;
    else
    {
        printf("\nYou entered wrong arg for delimeter number (1,2,3)\n");
        return 0;
    }
    char * delimeter2;
        if(strcmp(opsysInteger,"1")==0)
        delimeter2 = concat(delimeter1,Windows);
    else if (strcmp(opsysInteger,"2")==0)
        delimeter2 = concat(delimeter1,Unix);
    else if(strcmp(opsysInteger,"3")==0)
        delimeter2 = concat(delimeter1,Mac);
    else
    {
        printf("\nYou entered wrong arg for opsys number (1,2,3)\n");
        return 0;
    }
    fileOp(sourceDirectory,destinationDirectory,delimeter1,delimeter2);
    
    
    /*char input[500];
    char* temp;
    printf("Please enter a command:\n");
    fgets(input,499,stdin);
    printf("%s", input);
    temp = strdup(input);
    char* operation = getfield(temp,1," "," \n");
    temp = strdup(input);
    char* sourceDirectory = getfield(temp,2," "," \n");
    temp = strdup(input);
    char* destinationDirectory = getfield(temp,3," "," \n");
    temp = strdup(input);
    char* delimeterInteger = getfield(temp,5," "," \n");
    temp = strdup(input);
    char* opsysInteger = getfield(input,7," "," \n");
    printf("%s %s %s %s %s",operation,sourceDirectory,destinationDirectory,delimeterInteger,opsysInteger);
    */
    /*
    if(strcmp(string1,"CSV2XML")==0)
    {
        splitted = strtok(string5," ");
        printf("%s", splitted[2]);
        if(strcmp(&splitted[2],"1")==0)
        {
            printf("oldu");
        }
    }
    else
    {
        printf("Unavailable command. (Try to 'CSV2XML <inputfile> <outputfile> [-separator <P1>][-opsys <P2>][-h]'\n\n");
    }
    
  */
                                            
}