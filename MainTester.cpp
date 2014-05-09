/*
 @author Timothy Kua
*/
#include "MapMaker.h" //not included in maple
//#include "FlowAlgorithm.h"

class MapMaker;

using namespace std; //testing

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

/*Parts of Code that will be included in the movements of the Bot*/

/*Done for testing purposes*/
void sensor(MapMaker map){
     int oR=0,oL=0,oF=0; // wall in dir facing
     if(dir[pos] == 'N'){
        oL=0x0010;
        oR=0x0001;
        oF=0x0100;
     }else if (dir[pos] == 'E'){
        oL=0x0100;
        oR=0x1000;
        oF=0x0001;
     }else if (dir[pos] == 'S'){
        oL=0x0001;
        oR=0x0010;
        oF=0x1000;
     }else if (dir[pos] == 'W'){
        oL=0x1000;
        oR=0x0100;
        oF=0x0010;
     }
     //System.out.println("Micro sensor: "+map.getMapInfo(cX,cY).wall+" "+oL+" "+dir[pos]);
     if((map.getMapInfo(cX,cY).wall&oL) == oL) //left
        readData[0] = 400;
     else
        readData[0] = 1200;
     if((map.getMapInfo(cX,cY).wall&oR) == oR) //right
        readData[4] = 400;
     else
        readData[4] = 1200;
     if((map.getMapInfo(cX,cY).wall&oF) == oF){ //front
            readData[1] = 400;
            readData[2] = 400;
            readData[3] = 400;
     }else{
            readData[1] = 1200;
            readData[2] = 1200;
            readData[3] = 1200;
     }
     
}
/***************************************************************************************/

int main (int argc, char *argv[]) {
    char buff[BUFSIZ]={0}; //store commands
    
    //used to store if the program should read from file or the user
    FILE *pFile;
    pFile = stdin; //initialize to stdin
    int prompt; //if should prompt the user or not
    prompt = TRUE; //should promt user
    
    initialize("maze4.txt");
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


