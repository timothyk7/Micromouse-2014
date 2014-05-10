/*
 @author Timothy Kua and Joe Kang
*/
#include "FloodAlgorithm.h"

/*DEBUGGING*/
int FloodAlgorithm::getDist(int x, int y)
{
    return mazeMap[x][y].dist;
}

int FloodAlgorithm::getWall(int x, int y)
{
    return mazeMap[x][y].wall;
}

/*Stack Methods*/
void FloodAlgorithm::push(bool next)
{
  if(!next)
  {
    //ASSERT(c_stack_size+1<STACK_CAP);
    c_stack[c_stack_size] = node;
    c_stack_size++;
  }
  else
  {
    //ASSERT(n_stack_size+1<STACK_CAP);
    n_stack[n_stack_size] = node;
    n_stack_size++;
  }
}


void FloodAlgorithm::pop(bool next)
{
  if(!next)
  {
    //ASSERT(c_stack_size-1>=0);
    node = c_stack[c_stack_size-1];
    c_stack_size--;
  }
  else
  {
    //ASSERT(n_stack_size-1>=0);
    node = n_stack[n_stack_size-1];
    n_stack_size--;
  }
}

int FloodAlgorithm::size(bool next)
{
  if(next)
    return n_stack_size;
  else
    return c_stack_size;
}

void FloodAlgorithm::copy()
{
  for(int x=0;x<STACK_CAP;x++)
  {
    c_stack[x] = n_stack[x];
  }
}

/*FloodAlgorithm - Basic*/
/*Private**********************************************************************/
bool FloodAlgorithm::coordCheck(int coord) {
  return ((coord >= 0) && (coord < MAP_SIZE));
}

void FloodAlgorithm::clearDist() {
  for(int x= 0; x < MAP_SIZE; x++) {
    for(int y = 0; y < MAP_SIZE;y++) {
      mazeMap[x][y].dist = 257;
    }
  }
}

void FloodAlgorithm::clear() {
  for(int mx= 0; mx < MAP_SIZE;mx++) {
    for(int my = 0; my < MAP_SIZE;my++) {
      mazeMap[mx][my].x = mx;
      mazeMap[mx][my].y = my;
      mazeMap[mx][my].wall = 0x0;
      mazeMap[mx][my].dist = 257;
    }
  }
}

/* Check if there is wall based on data
   CAN CHANGE
   
   return true if wall there
   return false if no wall nearby
*/
bool FloodAlgorithm::isWall(int readData[], int type)
{
     switch (type)
     {
            case 0: //front
               if((readData[0] + readData[5])/2 > WALL)
                  return true;
               break;
            case 1: //left
               if((readData[1] + readData[2])/2 > WALL)
                  return true;
               break;
            case 2: //right
               if((readData[3] + readData[4])/2 > WALL)
                  return true;
               break;
            default:
               return false;
     }
     return false;
}

/*MapWall - writes the wall configuration into the maze
  0 - no wall   1 - wall
*/
void FloodAlgorithm::mapWall(int x, int y, int readData[], int pos)
{
   char dir[] = {DIR}; //create dir array
   //wall location
   int E = 0x0; 
   int W = 0x0; 
   int N = 0x0; 
   int S = 0x0; 
  //formalize the wall hex to keep the same orientation
  if(dir[pos] == N_DIR) {
       E = 0x1; //0001;
       W = 0x2; //0010;
       N = 0x4; //0100;
       S = 0x8; //1000;
  }
  else if (dir[pos] == E_DIR) {
       E = 0x8; //1000;
       W = 0x4; //0100;
       N = 0x1; //0001;
       S = 0x2; //0010;
   }
   else if (dir[pos] == S_DIR) {
       E = 0x2; //0010;
       W = 0x1; //0001;
       N = 0x8; //1000;
       S = 0x4; //0100;
   }
   else if (dir[pos] == W_DIR) {
       E = 0x4; //0100;
       W = 0x8; //1000;
       N = 0x2; //0010;
       S = 0x1; //0001;
   }
   else{}
       //assert(false);
  if (isWall(readData, 1)) { //check if wall on left
    mazeMap[x][y].wall = mazeMap[x][y].wall |W;
    
    //putting up wall on the other side
    if(dir[pos] == N_DIR && coordCheck(y-1)) {
      mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |E;
    }
    else if (dir[pos] == E_DIR && coordCheck(x-1)) {
      mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |E;
    }
    else if(dir[pos] == S_DIR && coordCheck(y+1)) {
      mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |E;
    }
    else if(dir[pos] == W_DIR && coordCheck(x+1)) {
      mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |E;
    }
  }

  if (isWall(readData,2)) {//right
  
    mazeMap[x][y].wall = mazeMap[x][y].wall |E;
    
    //putting up wall on the other side
    if(dir[pos] == N_DIR && coordCheck(y+1)) {
      mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |W;
    }
    else if (dir[pos] == E_DIR && coordCheck(x+1)) {
      mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |W;
    }
    else if (dir[pos] == S_DIR && coordCheck(y-1)) {
      mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |W;
    }
    else if (dir[pos] == W_DIR && coordCheck(x-1)) {
        mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |W;
    }
  }

  if (isWall(readData,0)) {//front
  
    mazeMap[x][y].wall = mazeMap[x][y].wall |N;
    
    //putting up wall on the other side
    if (dir[pos] == N_DIR && coordCheck(x-1)) {
      mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |S;
    }
    else if (dir[pos] == E_DIR && coordCheck(y+1)) {
      mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |S;
    }
    else if (dir[pos] == S_DIR && coordCheck(x+1)) {
      mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |S;
    }
    else if (dir[pos] == W_DIR && coordCheck(y-1)) {
        mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |S;
    }
  }
}

/*MapMaze - maps the maze based on flood fill
precondition: pos must be set the same way robot is facing
              must start in corner
              end of maze must be in center
readData provided
*/
void FloodAlgorithm::mapMaze
     (int readData[], int dir, int cX, int cY, bool center)
{
  //map the maze
  //assert(size(true) == 0 && size(false) == 0);
  mapWall(cX,cY,readData,dir);
  
  //flood the maze
  int x = 0; // store node value
  int y = 0;
  int level = 0; //shortest dist
  clearDist();

  if (center) { //doesn't work
    node = mazeMap[0][15];
    push(false);
  }
  else {
    node = mazeMap[MAP_SIZE/2-1][MAP_SIZE/2-1];
    push(false);
    node = mazeMap[MAP_SIZE/2-1][MAP_SIZE/2];
    push(false);
    node = mazeMap[MAP_SIZE/2][MAP_SIZE/2-1];
    push(false);
    node = mazeMap[MAP_SIZE/2][MAP_SIZE/2];
    push(false);
  }


  do {
    n_stack_size = 0;
    
    while (size(false) >0) {
      pop(false);
      
      x = node.x;
      y = node.y;
            
      if (mazeMap[x][y].dist ==257) {
    
        mazeMap[x][y].dist = level; //level manipulation 
        //left
        if (coordCheck(y-1) && !((mazeMap[x][y].wall & 0x2)==0x2) //0010
            && mazeMap[x][y-1].dist == 257) {//check whether to push onto the stack
          node = mazeMap[x][y-1];
          push(true);
        }
        //right
        if (coordCheck(y+1) && !((mazeMap[x][y].wall & 0x1) == 0x1) //0001
            && mazeMap[x][y+1].dist == 257 ) {
          node = mazeMap[x][y+1];
          push(true);
        }
        //up
        if (coordCheck(x-1) && !((mazeMap[x][y].wall & 0x4) == 0x4) //0100
            && mazeMap[x-1][y].dist == 257 ) {
          node = mazeMap[x-1][y];
          push(true);
        }
        //down
        if (coordCheck(x+1) && !((mazeMap[x][y].wall & 0x8) == 0x8) //1000
            && mazeMap[x+1][y].dist == 257 ) {
          node = mazeMap[x+1][y];
          push(true);
        }
        
        
      }
    }
     
    level++;
    copy();
    c_stack_size = n_stack_size;
  } while (size(true) > 0);
  n_stack_size = 0;
}
/*Public***********************************************************************/
/*movement - return an int value to tell bot which way to move
  0  -> forward
  1  -> left
  2  -> right
  3  -> turnaround
  -1 -> error
*/
int FloodAlgorithm::movement(int x, int y, int pos, int readData[])
{
    mapMaze(readData,pos,x,y,center);
    
    //if facing a wall
    if (isWall(readData,0)){
      return 3;
    }
    
    //determine valid locations to move
    Node values[4];
    //up
    if(coordCheck(x-1))
    {
      values[0].x = x-1;
      values[0].y = y;
      values[0].dist = mazeMap[x-1][y].dist;
    }else{
      values[0].x = 0;
      values[0].y = 0;
      values[0].dist = 256;
    }
    //down
    if(coordCheck(x+1))
    {
      values[1].x = x+1;
      values[1].y = y;
      values[1].dist = mazeMap[x+1][y].dist;
    }else{
      values[1].x = 0;
      values[1].y = 0;
      values[1].dist = 256;
    }
    //left
    if(coordCheck(y-1))
    {
      values[2].x = x;
      values[2].y = y-1;
      values[2].dist = mazeMap[x][y-1].dist;
    }else{
      values[2].x = 0;
      values[2].y = 0;
      values[2].dist = 256;
    }
    //rt
    if(coordCheck(y+1))
    {
      values[3].x = x;
      values[3].y = y+1;
      values[3].dist = mazeMap[x][y+1].dist;
    }else{
      values[3].x = 0;
      values[3].y = 0;
      values[3].dist = 256;
    }
    
    //sort best location to go
    for (int outer = 1; outer < DIR_SIZE ; outer++)
    {
      int position = outer;
      Node key = values[position];

      // Shift larger values to the right
      while (position > 0 && values[position - 1].dist>key.dist)
      {
        values[position] = values[position - 1];
        position--;
      }
      values[position] =  key;
    }
/**********************/
    //tell where bot to go
    char dir[] = {DIR}; //create dir array
    for(int i=0; i<DIR_SIZE;i++)
    {
      if(dir[pos]== N_DIR)
      {
        if(coordCheck(x-1) && !isWall(readData,0)
        && values[i].x == x-1 && values[i].y == y){     //up
          return 0;
        }
        else if(coordCheck(y+1) && !isWall(readData,2)
        && values[i].x == x && values[i].y == y+1){        //rt
          return 2;
        }
        else if(coordCheck(y-1) && !isWall(readData,1)
        && values[i].x == x && values[i].y == y-1){        //left
          return 1;
        }
      }
      else if (dir[pos] == S_DIR){
        if(coordCheck(x+1) && !isWall(readData,0)
        && values[i].x == x+1 && values[i].y == y){     //up
          return 0;
        }
        else if(coordCheck(y-1) && !isWall(readData,2) 
        && values[i].x == x && values[i].y == y-1){        //rt
          return 2;
        }
        else if(coordCheck(y+1) && !isWall(readData,1) 
        && values[i].x == x && values[i].y == y+1){        //left
          return 1;
        }
      }
      else if(dir[pos] == E_DIR){
        if(coordCheck(y+1) && !isWall(readData,0) 
        && values[i].x == x && values[i].y == y+1){     //up
          return 0;
        }
        else if(coordCheck(x+1) && !isWall(readData,2)
        && values[i].x == x+1 && values[i].y == y){        //rt
          return 2;
        }
        else if(coordCheck(x-1) && !isWall(readData,1) 
        && values[i].x == x-1 && values[i].y == y){        //left
          return 1;
        }
      }
      else if (dir[pos] == W_DIR){
        if(coordCheck(y-1) && !isWall(readData,0) 
        && values[i].x == x && values[i].y == y-1){     //up
          return 0;
        }
        else if(coordCheck(x-1) && !isWall(readData,2)
        && values[i].x == x-1 && values[i].y == y){        //rt
          return 2;
        }
        else if(coordCheck(x+1) && !isWall(readData,1)
        && values[i].x == x+1 && values[i].y == y){        //left
          return 1;
        }
      }
    }
    
    //check which part of algorithm to run  
    if(!center)
    {
      mapMaze(readData,pos,x,y,center);
      if((x==7 && y==7) || (x==7 && y==8) || (x==8 && y==7) || (x==8 && y==8)){
        center = !center;
      }
    }
    else{
      mapMaze(readData,pos,x,y,center);
      if(x == 0 && y == 15){
        center = !center;
      }
    }
    return -1;
}
