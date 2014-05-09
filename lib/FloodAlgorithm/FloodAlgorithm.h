/*
 @author Timothy Kua and Joe Kang
*/
#ifndef FlOODALGORITHM_HPP
#define FLOODALGORITHM_HPP

#include <stack>

#define MAP_SIZE  16
#define STACK_CAP 256
#define WALL  600
#define E 0x0010
#define W 0x0001
#define N 0x0100
#define S 0x1000


struct Node{
     int dist;
     int x;
     int y;
     int wall;
};

class FloodAlgorithm{
  public:

  //(de)construtors
  explicit FloodAlgorithm() {
  //stack
     c_stack_size = 0;
     n_stack_size = 0;
  }
  
  ~FloodAlgorithm();
  
  //methods for flood_algorithm
    void mapWall(int x, int y, int readData[], int dir);
    void mapMaze(int readData[], int dir, int iX, int iY, bool center);
    
  //methods for movement
    
  private:
  /*var*/
  //floodfill
    Node mazeMap [MAP_SIZE][MAP_SIZE];
  //stack
  int c_stack_size;
  int n_stack_size;

  Node node;
  Node c_stack[STACK_CAP]; //locations that the bot could visit
  Node n_stack[STACK_CAP]; //new locations to go
    
    
  /*Method*/
  //flood_algorithm 
    void clear(); //reset whole maze
    void clearDist();
    bool coordCheck(int coord); //check if x or y in bounds
  //stack methods
    void push (bool next);
    void pop (bool next);
    int size (bool next);

};

#endif
