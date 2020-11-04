#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char *process(char*);

int main(int argc, char* argv[])
{
	
	/*
	* Check argc is more than one. 
	*/
    	char const* const fileName = argv[1]; 

	/*
	* Check Result. 
	*/
    	FILE* file = fopen(fileName, "r"); 
    	
	char *s;
	s = ReadLineFile(file);

	/*
	* Construct Buffer to have no Double Spaces. 
	*/
	char *text;

	text = process(s);	

	/*
	* File close
	*/

	char const* const fileName2 = argv[2];
	FILE* file2 = fopen(fileName2, "w+");
	fputs(text, file2);	
	//fwrite(text, 1, sizeof(text), file2);

	/*
	* Close File.
	*/
	fclose(file);
	//free(buffer);

    	return 0;
}

char *process(char *text) 
{
	int c;
	int d;
	c = d = 0;

   	int length = strlen(text);
   	char *start;
 
   	start = (char*)malloc(length+1);
 
   	if (start == NULL){
      		exit(EXIT_FAILURE);
	}
 
   	while (*(text+c) != '\0') {
      		if (*(text+c) == ' ') {
         		int temp = c + 1;
         		if (*(text+temp) != '\0') {
            			while (*(text+temp) == ' ' && *(text+temp) != '\0'){
               				if (*(text+temp) == ' '){
                  				c++;
               				}  
               				temp++;
            			}
         		}
      		}
      		*(start+d) = *(text+c);
      		c++;
      		d++;
   	}
	*(start+d)= '\0';

   	return start;
}