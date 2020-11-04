#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>
#include "myio.h"

inline int ReadInteger(void){
	char *str = ReadLine();
	int iLength = getLength(str);
	int i = 0;
	int iFlag = 1;

	for(; i < iLength; i++){
		if(str[i] >= '9' || str[i] <= '0'){
			iFlag = 0;
		}
	}

	if(iFlag){
		return atoi(str);
	}
	else{
		printf("Throw - Only Integer. \n");
		int x = ReadInteger();
		return x;
	}

}

double ReadDouble(void)
{
	char *str = ReadLine();
	int iLength = getLength(str);
	int i = 0;
	int iFlag = 1;

	for(; i < iLength; i++){
			if((str[i] >= '9' || str[i] <= '0') && str[i] != '.'){
				iFlag = 0;
			}
	}

	if(iFlag && iLength < 17){
			return strtod(str, NULL);
	}
	else{
			printf("Throw - Only Double.\n");
			double x = ReadDouble();
			return x;
	}
}

char * ReadLine(void){
	int c;
	char * line = malloc(100);
	char * line2 = line;
	size_t lMax = 100;
	size_t len = lMax;

	if(line == NULL){
		return NULL;
	}

	for(;;){
		c = fgetc(stdin);

		if(c == EOF){
			break;
		}

		if(--len == 0) {

			len = lMax;
			char * line1 = realloc(line2, lMax *= 2);

			if(line1 == NULL) {
				free(line2);
				return NULL;
			}
			line = line1 + (line - line2);
			line2 = line1;
		}

		if((*line++ = c) == '\n'){
			break;
		}
	}
	*line = '\0';
	return line2;
}

int getLength(char *line){
	int c;
	int i = 0;
	char *temp = line;
	for(;;){
		c = *temp;

		if(c == EOF)
			break;
		
		if((*temp++ = c) == '\n'){
			break;
		}

		i++;
	}

	return i;
}

char *ReadLineFile(FILE *file){
	char *buffer;
        long lSize;

	/*
	* Find Size of File. 
	*/ 

        fseek(file, 0L, SEEK_END);
        lSize = ftell(file);
        rewind(file);

        /*
	* Create Memory utilized for file. 
	*/ 

        buffer = calloc(1, lSize+1);

	/*
	* Cp File into Buffer. 
	*/ 

        fread(buffer, lSize, 1, file);
	
	/*
	* Return Line. 
	*/ 
	return buffer;

}
