/*
 @author Timothy Kua and Joe Kang
*/
#include "FloodAlgorithm.h"

//destructor
 FloodAlgorithm::~FloodAlgorithm()
 { 
    
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

/*FloodAlgorithm - Basic*/
//private 
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
  for(int x= 0; x < MAP_SIZE;x++) {
    for(int y = 0; y < MAP_SIZE;y++) {
      mazeMap[x][y].x = x;
      mazeMap[x][y].y = y;
      mazeMap[x][y].wall = 0;
      mazeMap[x][y].dist = 257;
    }
  }
}

//public
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
       E = 0x0001;
       W = 0x0010;
       N = 0x0100;
       S = 0x1000;
  }
  else if (dir[pos] == E_DIR) {
       E = 0x1000;
       W = 0x0100;
       N = 0x0001;
       S = 0x0010;
   }
   else if (dir[pos] == S_DIR) {
       E = 0x0010;
       W = 0x0001;
       N = 0x1000;
       S = 0x0100;
   }
   else if (dir[pos] == W_DIR) {
       E = 0x0100;
       W = 0x1000;
       N = 0x0010;
       S = 0x0001;
   }
   else
       //assert(false);
    
  if (readData[0] < WALL) { //checking if wall on left
  
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

  if (readData[4] < WALL) {//right
  
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

  if ((readData[1] + readData[2] + readData[3])/3 < WALL) {//front
  
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
