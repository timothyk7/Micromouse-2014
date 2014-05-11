/*
 @author Timothy Kua
*/

//not included in maple
#include <iostream>
#include <string>
#include "MapMaker.cpp" 
//include header in maple
#include "FloodAlgorithm.cpp"

using namespace std;

/*In main Micromouse files*/
//Starting point
int cX = MAP_SIZE-1;
int cY = 0;
//Direction
int pos = 0;
char dir[DIR_SIZE] = {
  'N','E','S','W'};
//Sensor
int readData[6];

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

/*
   small number = no wall there
   large number = wall
*/
void sensor(MapMaker map)
{
    unsigned int oR=0,oL=0,oF=0; // wall in dir facing
    if(dir[pos] == 'N'){
        oL=0x2; //0010
        oR=0x1; //0001
        oF=0x4; //0100
    }else if (dir[pos] == 'E'){
        oL=0x4; //0100
        oR=0x8; //1000
        oF=0x1; //0001
    }else if (dir[pos] == 'S'){
        oL=0x1; //0001
        oR=0x2; //0010
        oF=0x8; //1000
    }else if (dir[pos] == 'W'){
        oL=0x8; //1000
        oR=0x4; //0100
        oF=0x2; //0010
    }

    //printf("%d, %d= %x\n", cX,cY,map.getMapInfo(cX,cY).wall);
    if((map.getMapInfo(cX,cY).wall&oL) == oL) //left
    {
        readData[1] = 1200;
        readData[2] = 1200;
    }
    else
    {
        readData[1] = 400;
        readData[2] = 400;
    }
    
    if((map.getMapInfo(cX,cY).wall&oR) == oR) //right
    {
        readData[3] = 1200;
        readData[4] = 1200;
    }
    else
    {
        readData[3] = 400;
        readData[4] = 400;
    }
    
    if((map.getMapInfo(cX,cY).wall&oF) == oF){ //front
        readData[0] = 1200;
        readData[5] = 1200;
    }else{
        readData[0] = 400;
        readData[5] = 400;
    }
}

int main (int argc, char *argv[]) {
    //Testing
    FloodAlgorithm flow;
    MapMaker map;
    
    //char buff[BUFSIZ]={0}; //store commands
    
    //used to store if the program should read from file or the user
    FILE *pFile;
    pFile = stdin; //initialize to stdin
    int prompt; //if should prompt the user or not
    prompt = TRUE; //should promt user
    int count = -1; //number of moves
    
    map.initialize("maze5.txt");
    int dist [MAP_SIZE][MAP_SIZE]={0}; /*debug*/
    int wall [MAP_SIZE][MAP_SIZE]={0}; /*debug*/

    /* // Done to speed simulator*/
    //363 - finish maze5
    for(int x =0; x<363; x++)
    {
       sensor(map);
       int movement = flow.movementMap(cX,cY,pos,readData);
       for(int mx= 0; mx < MAP_SIZE;mx++) {
            for(int my = 0; my < MAP_SIZE;my++) {
              dist[mx][my] = flow.getDist(mx,my);
            }
        }
        for(int mx= 0; mx < MAP_SIZE;mx++) {
            for(int my = 0; my < MAP_SIZE;my++) {
              wall[mx][my] = flow.getWall(mx,my);
            }
        }
        switch (movement)
        {
              case 0:
                   forward();
              break;
              case 1:
                   turn(-90);
              break;
              case 2:
                   turn(90);
              break;
              case 3:
                   turn(180);
              break;
              case 4:
              break;
              default:
                 printf("ERROR\n");
                 return -1;
       }
        count++;
    }
    
    
    string str;
    do
    {
       cout<<">";
       getline(cin, str);  
       if(str.compare("quit") == 0)
          break;   
       sensor(map);
       //test
       int moveShort[256];
       flow.movementShort(cX,cY,pos,readData,moveShort);
       cout<<moveShort[0]<<endl;
       
       
        
       int movement = flow.movementMap(cX,cY,pos,readData);
       for(int mx= 0; mx < MAP_SIZE;mx++) {
            for(int my = 0; my < MAP_SIZE;my++) {
              dist[mx][my] = flow.getDist(mx,my);
            }
        }
        for(int mx= 0; mx < MAP_SIZE;mx++) {
            for(int my = 0; my < MAP_SIZE;my++) {
              wall[mx][my] = flow.getWall(mx,my);
            }
        }
       printf("\nShould be at %d,%d facing %c with count %d\n", cX , cY , dir[pos], count);
       map.displayMaze(TRUE,dist ,cX,cY,dir[pos]);
       map.displayBotMaze(TRUE,dist, wall,cX,cY,dir[pos]);
       printf("\n");
       switch (movement)
       {
              case 0:
                   forward();
              break;
              case 1:
                   turn(-90);
              break;
              case 2:
                   turn(90);
              break;
              case 3:
                   turn(180);
              break;
              case 4:
              break;
              default:
                 printf("ERROR\n");
                 return -1;
       }
       count++;
    }while(true);
    return 0;
}



