/*
 @author Timothy Kua
*/
#ifndef FLOODALGORITHM_H
#define FLOODALGORITHM_H

#include <stack>

#define MAP_SIZE  16
#define STACK_CAP 256
#define WALL  600
#define DIR_SIZE 4
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
     center = false;
  //clear
     for(int mx= 0; mx < MAP_SIZE;mx++) {
        for(int my = 0; my < MAP_SIZE;my++) {
           mazeMap[mx][my].x = mx;
           mazeMap[mx][my].y = my;
           mazeMap[mx][my].wall = 0;
           mazeMap[mx][my].dist = 257;
        }
     }
  }
  
  ~FloodAlgorithm()
  {
  }
    
  //methods for movement
    int movement(int x, int y, int dir, int readData[]);
    int getDist(int x, int y); //DEBUGGING
    int getWall(int x, int y); //DEBUGGING
    
  private:
  /*var*/
  //floodfill
  Node mazeMap [MAP_SIZE][MAP_SIZE];
  bool center;

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
    bool isWall(int readData[DIR_SIZE], int type);
    bool coordCheck(int coord); //check if x or y in bounds
    void mapWall(int x, int y, int readData[DIR_SIZE], int dir);
    void mapMaze(int readData[DIR_SIZE], int dir, int cX, int cY, bool center);
  //stack methods
    void push (bool next);
    void pop (bool next);
    int size (bool next);
    void copy();

};

#endif
