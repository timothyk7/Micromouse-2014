/*
 @author Timothy Kua
*/

//include header in maple...
#include "MapMaker.cpp" //not included in maple
#include "FloodAlgorithm.cpp"

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
    
    char buff[BUFSIZ]={0}; //store commands
    
    //used to store if the program should read from file or the user
    FILE *pFile;
    pFile = stdin; //initialize to stdin
    int prompt; //if should prompt the user or not
    prompt = TRUE; //should promt user
    int count = 0; //number of moves
    
    map.initialize("maze4.txt");
    int dist [MAP_SIZE][MAP_SIZE]={0}; /*debug*/
    int wall [MAP_SIZE][MAP_SIZE]={0}; /*debug*/

    char *str;
    for(DISPLAY_PROMPT; fgets(buff,BUFSIZ, pFile) !=NULL;DISPLAY_PROMPT)
    {
       str = strtok(buff, TOKEN_SEP);
       if(strcmp(str, "exit") == 0)
          break;    
       printf("Should be at %d,%d facing %c with count %d\n", cX , cY , dir[pos], count);
       map.displayMaze(TRUE,dist ,cX,cY,dir[pos]);
       map.displayBotMaze(TRUE,dist, wall,cX,cY,dir[pos]);
       printf("\n");  
       sensor(map);
       switch (flow.movement(cX,cY,pos,readData))
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
              default:
                 printf("ERROR\n");
                 return -1;
       }
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
       count++;
    }
    return 0;
}



