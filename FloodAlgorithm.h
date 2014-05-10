/*
 @author Timothy Kua
*/
#ifndef FlOODALGORITHM_HPP
#define FLOODALGORITHM_HPP

#include <stack>

#define MAP_SIZE  16
#define STACK_CAP 256
#define WALL  600
#define N_DIR 'N'
#define E_DIR 'E'
#define S_DIR 'S'
#define W_DIR 'W'
#define DIR N_DIR, E_DIR, S_DIR, W_DIR


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
  //FloodAlgorithm
     clear();  //make a clean map
  }
  
  ~FloodAlgorithm();
    
  //methods for movement
    int movement(int x, int y, int dir, int readData[]);
    
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
    void mapWall(int x, int y, int readData[], int pos/*dir*/);
    void mapMaze(int readData[], int dir, int cX, int cY, bool center);
  //stack methods
    void push (bool next);
    void pop (bool next);
    int size (bool next);
    void copy();

};

#endif
