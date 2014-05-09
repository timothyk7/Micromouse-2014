/*
 @author Timothy Kua and Joe Kang
*/
#ifndef FlOODALGORITHM_HPP
#define FLOODALGORITHM_HPP

#include <stack>

#define MAP_SIZE  16
#define STACK_CAP 256
#define WALL  600


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
    Node map [MAP_SIZE][MAP_SIZE];
  //stack
  int c_stack_size;
  int n_stack_size;

  Node node;
  Node c_stack[STACK_CAP];
  Node n_stack[STACK_CAP];
    
    
  /*Method*/
  //flood_algorithm 
    void clear(); //reset whole maze
    void clearDist();
  //stack methods
    void push (bool next);
    void pop (bool next);
    int size (bool next);

};

#endif
