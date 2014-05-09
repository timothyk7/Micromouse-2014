/*
 @author Timothy Kua
*/
#include "MapMaker.h" //not included in maple
#include "FloodAlgorithm.h"

//Starting point
int iX = MAP_SIZE-1;
int iY = 0;
int cX = iX;
int cY = iY;
//Direction
int pos = 0;
int DIR_SIZE=4;
char dir[4] = {
  'N','E','S','W'};
//Sensor
int readData[5];

int main (int argc, char *argv[]) {
    char buff[BUFSIZ]={0}; //store commands
    
    //used to store if the program should read from file or the user
    FILE *pFile;
    pFile = stdin; //initialize to stdin
    int prompt; //if should prompt the user or not
    prompt = TRUE; //should promt user
    
    initialize("maze3.txt");
    int dist [MAP_SIZE][MAP_SIZE]={0}; /*debug*/
    
    char *str;
    for(DISPLAY_PROMPT; fgets(buff,BUFSIZ, pFile) !=NULL;DISPLAY_PROMPT)
    {
       str = strtok(buff, TOKEN_SEP);
       if(strcmp(str, "exit") == 0)
          break;      
       displayMaze(TRUE, dist,0,0,'N');
          
    }
    return 0;
}


