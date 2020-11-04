
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myio.h"

void main(int argc, char *argv[]){
	/*
	* Check Arguments: x,y,z.
	*/

	if (argc > 4){
		perror("Too many args\n");
		exit(0);
	}

	if (argc < 4){
		perror("Not enough args\n");
		exit(0);
	}

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int z = atoi(argv[3]);

	/*
	* Construct Array for X to hold Values. 
	*/

	int xVal[x]; 
	int xLoc;
	int xLarge=0; 

	/*
	* Construct Array for Y to hold Values. 
	*/

	float yVal[y];
	float yLoc;
	float yLarge=0;
	
	/*
	* Construct Array for Z to hold Values. 
	*/
	
	char *zVal[z];
	int zLoc;
	int zLarge = 0;
	
	/*
	* Requests User to Enter X Amount of Integers.
	* For Loop through Integer Values. 
	*/

	int i;
	for(i = 0; i < x; i++){
		printf("Enter an integer for array x: ");
		xVal[i] = ReadInteger();			
		xLoc=xVal[i];

		if(xLarge < xLoc){
			xLarge=xLoc;
		}		
	}
	
	/*
	* Requests User to Enter Y Amount of Doubles.
	* For Loop through Double Values. 
	*/

	int iLocateDub=0;
	for(i = 0; i < y; i++){
                printf("Enter a double for array y: ");
                yVal[i]=ReadDouble();
		yLoc=yVal[i];

                if(yLarge < yLoc){
                        yLarge=yLoc;
			iLocateDub=i;
                }
        }

	/*
	* Requests User to Enter Z Amount of Lines.
	* For Loop through Double Values. 
	*/

	int iLocateLine=0;
        for(i = 0; i < z; i++){
                printf("Please enter a line of text for array z: ");
		zVal[i]=ReadLine();
		zLoc=getLength(zVal[i]);
		
		if(zLarge < zLoc){
			zLarge=zLoc;
			iLocateLine=i;	
		}
        }
	
	printf("The largest Integer: %d\n", xLarge);
	//printf("The largest Double: %f\n", yVal[iLocateDub]);
	printf("The longest Line: %s\n", zVal[iLocateLine]);
}
