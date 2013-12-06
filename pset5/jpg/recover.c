/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 *
 * Lucy Nam
 */

#include <stdio.h>
#include <stdlib.h>

void writerest(FILE* src, char* buffer, FILE* img);

int main(void)
{

    // open memory file
    FILE* src = fopen("card.raw", "r");

    // check null
    if (src == NULL)
    {
        printf("Could not open card.raw");
        return 1;
    }

    // declaration of variables
    char* title = malloc(sizeof(char) * 8);
    char buffer[520];
    int number = 0;
    int read = 0;
    
    // do-while loop to to find beginning of jpg
    do
    {
        // read 512 bytes into a buffer
        read = fread(&buffer, sizeof(char), 512, src);
            
        // if-loop to find beginning of jpg 
        if (buffer[0] == (char) 255 && buffer[1] == (char) 216 && buffer[2] == 
        (char) 255 && (buffer[3] == (char) 224 || buffer[3] == (char) 225))
        {
            number++;
                
            // print jpg into current directory
            sprintf(title, "%03d.jpg", number - 1);
                
            // open jpg file
            FILE* img = fopen(title, "w");
                
            // writes first 512 bytes into file
            fwrite(&buffer, sizeof(char) * 512, 1, img);
                
            // calls function writerest
            writerest(src, &buffer[0], img);
        }    
    }        
    while (read == 512);
    fclose(src);  
    free(title);          
} 


// function that writes until a new jpg is found
void writerest(FILE* src, char* buffer, FILE* img)
{
     // check for NULL
    if (src == NULL || buffer == NULL || img == NULL)
    {
        return;
    }
     
    // while-loop until new jpeg is found
    while (1 == 1)
    {  
         // write until new file found
        if (fread(buffer, sizeof(char), 512, src) == 512 && (buffer[0] != 
        (char) 255 || buffer[1] != (char) 216 || buffer[2] != (char) 255 || 
        (buffer[3] != (char) 224 && buffer[3] != (char) 225))) 
        {
            fwrite(buffer, sizeof(char) * 512, 1, img);
        }
        else         
        {
            // close image
            fclose(img); 
            
            // seeking back to the last 512 bytes
            fseek(src, -512, SEEK_CUR);         
            return;
        }    
     }   
}

     

     
  

     

