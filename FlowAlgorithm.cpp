#include "FlowAlgorithm.h"

#include <stdio.h>
#include <string.h>

#define int MAP_SIZE = 16;


public:    // change it to private later
  int dist;
  int x;
  int y;
  int wall;

  int E = 0x0010;
  int W = 0x0001;
  int N = 0x0100;
  int S = 0x1000;

  int pos = 0;
  int DIR_SIZE = 4;
  char dir[] = {'N', 'E', 'S','W'};
  int cX = 0;
  int cY = 0;

  Node mazeMap[][] = new Node[MAP_SIZE][MAP_SIZE];
  bool once = true;

  int c_stack_size = 0;
  int n_stack_size = 0;
  int STACK_CAP = 256;

  Node node;
  Node c_stack[] = new Node[256];
  Node n_stack[] = new Node[256];



FlowAlgorithm::Node(0, 0, 0, 0) { //"default set 0s "
  Nodeinit (0, 0, 0, 0);
}

FlowAlgorithm::Node(int dist, int x, int y, int wall) { //"overloading"
  Nodeinit (dist, x, y, wall);
}

void FlowAlgorithm::Nodeinit(int dist, int x, int y, int wall) {
  this->dist = dist;
  this->x = x;
  this->y = y;
  this->wall = wall;
}

int FlowAlgorithm::getxC() { return cX; }
int FlowAlgorithm::getcY() { return cY; }
int FlowAlgorithm::getPos() { return pos; }

int[][] getDist() {
  int [][] dist = new int[MAP_SIZE][MAP_SIZE];
    for(int x=0; x<MAP_SIZE;x++) {
      for(int y =0; y<MAP_SIZE;y++) {
        dist[x][y] = mazeMap[x][y].dist;
      }
    }
  return dist;
} 

void push(bool next) {
  if(!next) {
    assert(c_stack_size+1<STACK_CAP);
    c_stack[c_stack_size] = node;
    c_stack_size++;
  }
  else {
    assert(n_stack_size+1<STACK_CAP);
    n_stack[n_stack_size] = node;
    n_stack_size++;
  }
}

void pop(bool next) {
  if(!next) {
    assert(c_stack_size-1>=0);
    node = c_stack[c_stack_size-1];
    c_stack_size--;
  }
  else {
    assert(n_stack_size-1>=0);
    node = n_stack[n_stack_size-1];
    n_stack_size--;
  }
}

int size(bool next) {
  if(next)
    return n_stack_size;
  else
    return c_stack_size;
}

FlowAlgorithm::FlowAlgorithm(int pos, int cX, int cY) {
  this->pos = pos;
  this->cX = cX;
  this->cY = cY;
  clear();
}
    
bool coordCheck(int coord) {
  return ((coord >= 0) && (coord < MAP_SIZE));
}
    
void clear() {
  for(int x= 0; x < MAP_SIZE;x++) {
    for(int y = 0; y < MAP_SIZE;y++) {
      mazeMap[x][y] = new Node(257,x,y,0);
    }
  }
}

void clearDist() {
  for(int x= 0; x < MAP_SIZE; x++) {
    for(int y = 0; y < MAP_SIZE;y++) {
      mazeMap[x][y]->dist = 257;
    }
  }
}
    
void updateLocation(int x, int y) {//update current location
  cX = x;
  cY = y;
}

void updateDir(int number) { //if turns, update direction its facing
  pos = number;
}

// 0 = no wall 1 = wall
//readData provided
void mapWall(int x, int y, int [] readData, int p) {
  if(dir[p] == 'N') {
       E = 0x0001;
       W = 0x0010;
       N = 0x0100;
       S = 0x1000;
  }
  else if (dir[p] == 'E') {
       E = 0x1000;
       W = 0x0100;
       N = 0x0001;
       S = 0x0010;
   }
   else if (dir[p] == 'S') {
       E = 0x0010;
       W = 0x0001;
       N = 0x1000;
       S = 0x0100;
   }
   else if (dir[p] == 'W') {
       E = 0x0100;
       W = 0x1000;
       N = 0x0010;
       S = 0x0001;
   }
   else
       assert(false);
    
  if (readData[0] < WALL) { //checking if wall on left
  
    mazeMap[x][y]->wall = mazeMap[x][y]->wall |W;
    
    //putting up wall on the other side
    if(dir[pos] == 'N' && coordCheck(y-1)) {
      mazeMap[x][y-1]->wall = mazeMap[x][y-1]->wall |E;
    }
    else if (dir[pos] =='E'&& coordCheck(x-1)) {
      mazeMap[x-1][y]->wall = mazeMap[x-1][y]->wall |E;
    }
    else if(dir[pos] == 'S' && coordCheck(y+1)) {
      mazeMap[x][y+1]->wall = mazeMap[x][y+1]->wall |E;
    }
    else if(dir[pos] =='W' && coordCheck(x+1)) {
      mazeMap[x+1][y]->wall = mazeMap[x+1][y]->wall |E;
    }
  }

  if (readData[4] < WALL) {//right
  
    mazeMap[x][y]->wall = mazeMap[x][y]->wall |E;
  
    if(dir[pos] == 'N' && coordCheck(y+1)) {
      mazeMap[x][y+1]->wall = mazeMap[x][y+1]->wall |W;
    }
    else if (dir[pos] =='E'&& coordCheck(x+1)) {
      mazeMap[x+1][y]->wall = mazeMap[x+1][y]->wall |W;
    }
    else if (dir[pos] == 'S' && coordCheck(y-1)) {
      mazeMap[x][y-1]->wall = mazeMap[x][y-1]->wall |W;
    }
    else if (dir[pos] =='W' && coordCheck(x-1)) {
        mazeMap[x-1][y]->wall = mazeMap[x-1][y]->wall |W;
    }
  }

  if ((readData[1] + readData[2] + readData[3])/3 < WALL) {//front
  
      mazeMap[x][y].wall = mazeMap[x][y].wall |N;
    
    if (dir[pos] == 'N' && coordCheck(x-1)) {
      mazeMap[x-1][y]->wall = mazeMap[x-1][y]->wall |S;
    }
    else if (dir[pos] =='E'&& coordCheck(y+1)) {
      mazeMap[x][y+1]->wall = mazeMap[x][y+1]->wall |S;
    }
    else if (dir[pos] == 'S' && coordCheck(x+1)) {
      mazeMap[x+1][y]->wall = mazeMap[x+1][y]->wall |S;
    }
    else if (dir[pos] =='W' && coordCheck(y-1)) {
        mazeMap[x][y-1]->wall = mazeMap[x][y-1]->wall |S;
    }
  }
  
}

//precondition: pos must be set the same way robot is facing
//              must start in corner
//              end of maze must be in center
//readData provided
public void mapMaze(int [] readData, int p, int iX, int iY, bool center) {
  //map the maze
  assert(size(true) == 0 && size(false) == 0);
  mapWall(cX,cY,readData,p);
    
  //flood the maze
  int x = 0
  int y = 0; // store node value
  int level = 0; //shortest dist
  clearDist();

  if (center) {
    node = mazeMap[iX][iY];
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
    n_stack = new Node[256];
    
    while (size(false) >0) {
      pop(false);
      
      x = node->x;
      y = node->y;
            
      if (mazeMap[x][y]->dist ==257) {
    
        mazeMap[x][y]->dist = level; //level manipulation 
        //left
        if (coordCheck(y-1) && !((mazeMap[x][y]->wall & 0x0010)==0x0010) 
            && mazeMap[x][y-1]->dist == 257) {//check whether to push onto the stack
          node = mazeMap[x][y-1];
          push(true);
        }
        //right
        if (coordCheck(y+1) && !((mazeMap[x][y]->wall & 0x0001) == 0x0001) 
            && mazeMap[x][y+1]->dist == 257 ) {
          node = mazeMap[x][y+1];
          push(true);
        }
        //up
        if (coordCheck(x-1) && !((mazeMap[x][y]->wall & 0x0100) == 0x0100)
            && mazeMap[x-1][y]->dist == 257 ) {
          node = mazeMap[x-1][y];
          push(true);
        }
        //down
        if (coordCheck(x+1) && !((mazeMap[x][y]->wall & 0x1000) == 0x1000) 
            && mazeMap[x+1][y]->dist == 257 ) {
          node = mazeMap[x+1][y];
          push(true);
        }
        
        node = null;
      }
    }
     
    level++;
    c_stack = n_stack;
    c_stack_size = n_stack_size;
  } while (size(true) > 0);
  n_stack_size = 0;
  once = false;
}
    /*
     * For help
     

public void display(bool num) {
  System.out.print("\t ");
  for (int x=0; x<MAP_SIZE; x++)
  {
      System.out.print(x%10);    
      System.out.print("     "); //2 orig
  }
  System.out.println();

  for (int row = 0; row < MAP_SIZE; row++)
  {
    helpTop(row);
    System.out.print((row) + "\t");
    for (int col =0; col < MAP_SIZE; col++)
    {
        if((mazeMap[row][col]->wall & 0x0010) == 0x0010)//if theres a left wall
          System.out.print("|");
        else
          System.out.print(" ");
        if(cX == row && cY == col){
          if((mazeMap[row][col]->wall&0x1000) == 0x1000)//if theres a bottom wall
              System.out.print("_"+dir[pos]+dir[pos]+"_");
          else
              System.out.print(" "+dir[pos]+dir[pos]+" ");
        }else if(num){
          if((mazeMap[row][col].wall&0x1000) == 0x1000){//if theres a bottom wall
              if(mazeMap[row][col].dist<10)
                 System.out.print("_" + mazeMap[row][col].dist +"__");
              else if(mazeMap[row][col].dist<100)
                 System.out.print("_" + mazeMap[row][col].dist +"_");
              else
                 System.out.print("_" + mazeMap[row][col].dist +""); 
          }
          else{
              if(mazeMap[row][col].dist<10)
                 System.out.print(" " + mazeMap[row][col].dist +"  ");
              else if(mazeMap[row][col].dist<100)
                 System.out.print(" " + mazeMap[row][col].dist +" ");
              else
                 System.out.print(" " + mazeMap[row][col].dist +""); 
          }
        }else{
          if((mazeMap[row][col].wall&0x1000) == 0x1000)//if theres a bottom wall
              System.out.print("____");
          else
              System.out.print("    ");
        }
          
        if((mazeMap[row][col].wall&0x0001) == 0x0001)//if theres a rt wall
          System.out.print("|");
        else
          System.out.print(" ");
    }
    System.out.println();
  }
}
    
     private void helpTop(int row)
     {
         System.out.print("\t");
         for(int col = 0; col<MAP_SIZE; col++)
         {
             if((mazeMap[row][col].wall&0x0100) == 0x0100)//if theres a top wall
                System.out.print(" ____ ");
             else
                System.out.print("      ");//3 orig
         }
         System.out.println();
     }

}  */
