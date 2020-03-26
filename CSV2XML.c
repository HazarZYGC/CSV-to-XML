#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//CONSTANT CHAR VALUES.
char Unix[] = "\n";
char Windows[] = "\r\n";
char Mac[] = "\r";
char comma[] = ",";
char tab[] = "\t";
char semicolon[] = ";";


//SPLITTING STRING THROUGH DELIMETER (, ; \t)
char *xstrtok(char* line, char* delims);

//THE MAIN CODE FOR READIND FROM CSV AND WRITE TO XML.
int CSV2XML(char* source, char* destination, char* delimeter, char* endLine);


//MAIN
int main(int argc, char *argv[])
{
    if(argc == 2 && strcmp(argv[1],"-h")==0)
    {
        printf("enter arguments eg.\"./CSV2XML <inputfile> <outputfile> [-separator <P1>][-opsys <P2>]!!\"\n");
        return 0;
    }
    // Checking if number of argument 
    if (argc < 6 || argc > 7)  
    { 
        printf("You gave missing argument. You can type ./CSV2XML -h to more information.\n"); 
        return 0; 
    }

    //picking argv in order. 
    char* sourceDirectory = argv[1];
    char* destinationDirectory = argv[2];
    char* delimeterInteger = argv[4];
    char* opsysInteger = argv[6];
    //
    //DELIMETER THAT TOOK FROM USER (, ; \t)
    // 
    char* delimeter;
    if(strcmp(delimeterInteger,"1")==0)
    {
        delimeter = comma;
        printf("YOU CHOSE DELIMETER AS COMMA !!\n");
    }
        
    else if (strcmp(delimeterInteger,"2")==0)
    {
        delimeter = tab;
        printf("YOU CHOSE DELIMETER AS TAB !!\n");
    }
        
    else if(strcmp(delimeterInteger,"3")==0)
    {
        delimeter = semicolon;
        printf("YOU CHOSE DELIMETER AS SEMICOLON !!\n");
    }
    else
    {
        printf("\nYou entered wrong arg for delimeter number (1 = , | 2 = TAB | 3 = ;)\n");
        return 0;
    }
    /////
    /// END LINE CHAR TOOK FROM USER.
    //   
    char * endLine;
    if(strcmp(opsysInteger,"1")==0)
    {
        endLine = Windows;
        printf("YOU CHOSE END LINE CHARACTER THROUGH WINDOWS OS !!\n");
    }
        
    else if (strcmp(opsysInteger,"2")==0)
    {
        endLine = Unix;
        printf("YOU CHOSE END LINE CHARACTER THROUGH LINUX OS !!\n");
    }
        
    else if(strcmp(opsysInteger,"3")==0)
    {
        endLine = Mac;
        printf("YOU CHOSE END LINE CHARACTER THROUGH MAC OS !!\n");
    }
        
    else
    {
        printf("\nYou entered wrong arg for opsys number (1 = Windows | 2 = Unix | 3 = Mac )\n");
        return 0;
    }
    

    // calling CSV2XML (CSV to XML function)
    CSV2XML(sourceDirectory,destinationDirectory,delimeter,endLine);
    printf("CONVERTING PROCESS IS DONE.\n");
    printf("PLEASE CHECK THE XML FILE THAT YOU GAVE NAME.\n");
    return(1);

                                            
}



//CSV2XML METHOD.
int CSV2XML(char* source, char* destination, char* delimeter, char* endLine)
{

    ///OPENING CSV AND XML FILES.
    //
    FILE *stream = fopen(source, "r");
    if(stream == NULL)
    {
        puts("ERROR OPENING THE CSV FILE !!");
        exit (1);
    }
    FILE  *fp = fopen(destination,"w"); 
    if(fp == NULL)
    {
        puts("ERROR OPENING THE XML FILE");
        exit (1);
    }
    ////
    //
    //CASTING DELIMETER AND END LINTE TO CHAR. WE WILL USE THEM INTO CODE IN CHAR FORM. FOR \r\n WE USE ! .
    char delimeterChar = strcmp(delimeter,"\t") == 0 ? '\t' : strcmp(delimeter,",") == 0 ? ',' : strcmp(delimeter,";") == 0 ? ';' : ' ';
    char endLineChar = strcmp(endLine,"\r\n") == 0 ? '!' : strcmp(endLine,"\n") == 0 ? '\n' : strcmp(endLine,"\r") == 0 ? '\r' : ' ';
   
    //FIRST LINE FROM CSV FILE TO DETERMINE TAGS.
    char firstLine[1024];
    fgets(firstLine, 1024, stream);
    //
    //VARIABLES
    char* root = strtok(source,"."); //ROOT TAG.
    int cursorTag = 0; //INDEX OF FIRST LINE.
    int cursurBackUp = 0; //STORING THE INDEX TO WRITE SAME TAG NAME AGAIN TO CLOSE THE TAG.
    int tagController = 0; //CONTROLLING EMPTY TAG OR NOT.
    char line[1024]; //TAKING FILE LINE BY LINE.
    char *tmp; //TEMP STRING.
    char* newRow; //NEWROW STRING FOR SPLITTED TMP.
    int start = 1; //CONTROLLING THE FIRST ELEMENT OF EVERY LINE TO CONTROL XSTRTOK FUNCTION
    int id = 1; //STARTING ELEMENT (ROW) ID FROM 1
    //
    //
    fprintf(fp,"<%s>\n", root); //WRITING ROOT TAG.
    printf("<%s>\n", root);
    while (fgets(line, 1024, stream)) 
    {
    //STARTING OF THE FILE. (WITHOUT FIRST LINE).
        
    fprintf(fp,"\t<row id=\"%d\">\n", id);//PRINTING ROW TAG WITH ID ATTRIBUTE.
    printf("\t<row id=\"%d\">\n", id);
       
       
    for (cursorTag; cursorTag <strlen(firstLine); ++cursorTag)  //FOR LOOP TO CONTROLLING LINE SIZE.
    {
        //IF WE FACE WITH FIRST ELEMENT. XSTRTOK WILL TAKE FROM US LINE  AND DELIMETER
        if(start == 1)
            newRow = xstrtok(line,delimeter);
        //ELSE TAKE NULL AND DELIMETER TO CONTINUE SPLITTING.
        else
        {
            newRow = xstrtok(NULL,delimeter);
        }
        //UPDATING START.
        start = 0;
       
           
        if(strcmp(newRow, "") !=0) //CONTROLLING THE EACH TAG EMPTY OR NOT.
        {
            cursurBackUp = cursorTag; //SAVING INDEX.
            fprintf(fp,"\t\t<");
            printf("\t\t<");
            //PRINTING FIRST LINE IN CONTROL WITH DELIMETER AND ENDLINE CHAR. END LINE CONTROLLING MUST BE MANUEL FOR THIS ONE.
            for (cursorTag; firstLine[cursorTag] != delimeterChar && firstLine[cursorTag] != endLineChar && firstLine[cursorTag] != 13  ; ++cursorTag) 
            {
                //PRINTING SPACES AS "_"

                if(firstLine[cursorTag]!=' ')
                {
                    fprintf(fp,"%c",tolower(firstLine[cursorTag]));
                    printf("%c",tolower(firstLine[cursorTag]));

                }
                else
                {
                    fprintf(fp,"_");
                    printf("_");

                }
            }
            //TAKING INDEX FROM BACKUP TO PRINT AGAIN.
            cursorTag = cursurBackUp;
            //CLOSE TAGE.
            fprintf(fp,">");
            printf(">");
            
            //
            //
            //PART OF THE CONTROLLING END LINE TO ARRANGE LINE ENDS (LAST COLUMN TAG).
            //FOR LINUX
            if(endLineChar == '\n')
            {
                if(newRow[strlen(newRow)-1] =='\n')
                    newRow[strlen(newRow)-1] = '\0';
            }
            //FOR MAC
            else if(endLineChar == '\r')
            {
                if(newRow[strlen(newRow)-1] =='\r')
                    newRow[strlen(newRow)-1] = '\0';
            }
            //FOR WINDOWS.
            else
            {
                if(newRow[strlen(newRow)-1] =='\n')
                    newRow[strlen(newRow)-1] = '\0';
                if(newRow[strlen(newRow)-1] =='\r')
                    newRow[strlen(newRow)-1] = '\0';
            }
            //
            //
        
            fprintf(fp,"%s",newRow); //PRINTING EACH STRING IN TAG.
            printf("%s",newRow);

            tagController = 1;       //TO ARRANGING PRETTY XML.
                     
           
        }
        //TO ARRANGING PRETTY XML.
        if(tagController == 1)
        {
            fprintf(fp,"</");
            printf("</");

        }
        else
        {
            fprintf(fp,"\t\t</");
            printf("\t\t</");
        }
        
        //PRINTING FIRST LINE IN CONTROL WITH DELIMETER AND ENDLINE CHAR. END LINE CONTROLLING MUST BE MANUEL FOR THIS ONE.
        for (cursorTag;firstLine[cursorTag] != delimeterChar && firstLine[cursorTag] != '\n' ; cursorTag++) 
        {
            //PRINTING SPACES AS "_"        
            if(firstLine[cursorTag]!=' ')
            {
                if(firstLine[cursorTag] != '\r')
                {
                    fprintf(fp,"%c",tolower(firstLine[cursorTag]));
                    printf("%c",tolower(firstLine[cursorTag]));
                }
            }
            else
            {
                fprintf(fp,"_");
                printf("_");

            }
            
        }
        //CONTINE TO CLOSING TAG.   
        fprintf(fp,">\n");
        printf(">\n");
        //AGAIN.
        tagController = 0;        
                
    }
    //BACK AGAIN TO STARTING VALUES.
    start=1;
    cursorTag = 0;
    //CLOSING ROW TAG.
    fprintf(fp,"\t</row>\n");
    printf("\t</row>\n");
    //INCREASING ID.
    id++; 
       
  }
    //CLOSING ROOT TAG.
    fprintf(fp,"</%s>", root);
    printf("</%s>\n", root);
    //CLOSING FILES.
    fclose(stream);
    fclose(fp);
    //
    

}


//XSTRTOK METHOD. SPLITTING METHOD.
char *xstrtok(char *line, char *delims)
{
    static char *saveline = NULL;
    char *p;
    int n;

    if(line != NULL)
        saveline = line;

    /*
    *see if we have reached the end of the line
    */
    if(saveline == NULL || *saveline == '\0')
        return(NULL);
    /*
    *return the number of characters that aren't delims
    */
    n = strcspn(saveline, delims);
    p = saveline; /*save start of this token*/

    saveline += n; /*bump past the delim*/

    if(*saveline != '\0') /*trash the delim if necessary*/
        *saveline++ = '\0';

    return(p);
}
