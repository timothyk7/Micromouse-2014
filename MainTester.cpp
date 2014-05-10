/*
 @author Timothy Kua
*/
#include "MapMaker.h" //not included in maple
#include "FloodAlgorithm.h"

/*In main Micromouse files*/
//Starting point
int cX = MAP_SIZE-1;
int cY = 0;
//Direction
int pos = 0;
char dir[DIR_SIZE] = {
  'N','E','S','W'};
//Sensor
int readData[5];

void turn(int degree)
{
  if(degree==-90) //left
  {
    pos--;
    if(pos<0)
      pos = DIR_SIZE-1;
  }
  else if(degree == 90 ) //right
  {
    pos++;
    if(pos>=DIR_SIZE)
      pos = 0;
  }
  else{ //turn around
    pos++;
    if(pos>=DIR_SIZE)
      pos = 0;
    pos++;
    if(pos>=DIR_SIZE)
      pos = 0;
  }
}
    
void forward()
{
  if(dir[pos] =='N'){
      --cX;
  }else if(dir[pos] == 'E'){
      ++cY;
  }else if(dir[pos] == 'S'){
      ++cX;
  }else if(dir[pos] == 'W'){
      --cY;
  }
}

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



