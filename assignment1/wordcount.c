#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
/*
 * Function: iWordCount(char *cFileName)
 *     Open file for read.
 * Parameter: char *fileName
 * Return: int
 *     Total count of words in file.
 */
int iWordCount(char *cFileName);
int iWordCount(char *cFileName)
{
    int iWordCount=0;
    char cWord;
    FILE *file;
    /*
    ** Open File for Read.
    ** Utilize while loop to find Character til' end of File.
    */
    file=fopen(cFileName,"r");
    while ((cWord = fgetc(file)) != EOF)
    {
        if (cWord=='\n'||cWord==' '||cWord=='\t')
        {
            iWordCount++;
        }
    }
    /*
    ** Close File.
    */
    fclose(file);
    /*
    ** Return Integer wordCount
    */
    return iWordCount;
}

/*
** Main Function.
*/
int main(int argc, char *argv[ ])
{
    
    int i;
    int iTotalFiles;
    char *cFileName[argc];
    pid_t childPpid = 0;
    long lPpid = getpid();
    
    /*
    ** Throw Error Show Usage.
    */
    if (argc<=1)
    {
        fprintf(stderr,"USAGE: ./wordcount file_1 file_2 file_3 ... File_n\n");
        exit(-1);
        
    }
    
    /*
    ** Get Number of Files and sort files.
    */
    iTotalFiles=argc-1;
    for (i=1;i<=iTotalFiles;i++)
    {
        cFileName[i-1] = argv[i];
        
    }
    
    /*
    ** Parent Process for Files.
    */
    for (i=0;i<iTotalFiles;i++)
    {
        int iCount;
        /*
        ** Fork Child Process for Count.
        */
        if ((childPpid=fork())<=0)
        {
            break;
        }
        
        /*
        ** Array of Files utilize iWordCount.
        */
        iCount=iWordCount(cFileName[i]);
        printf("Child Process for %s: number of words is %d\n",cFileName[i],iCount);
    }
    
    /*
    ** Wait for Child.
    */
    for (;;)
    {
        childPpid=wait(NULL);
        if (childPpid==-1&&errno!=EINTR)
        {
            break;
        }
    }
    /*
    ** Check Current Process for Parent.
    */
    if (lPpid==getpid())
    {
        printf("All %d files have been counted!\n",iTotalFiles);
        
    }
    fflush(stderr);
    return 0;
    
}
