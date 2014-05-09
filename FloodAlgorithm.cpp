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
void FloodAlgorithm::mapWall(int x, int y, int readData[], int dir)
{
}
