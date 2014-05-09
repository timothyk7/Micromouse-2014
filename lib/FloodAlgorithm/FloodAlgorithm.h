/*
 @author Timothy Kua and Joe Kang
*/
#ifndef FlOODALGORITHM_HPP
#define FLOODALGORITHM_HPP

#include <stack>

#define MAP_SIZE  16
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
    
    
  /*Method*/
  //flood_algorithm 
    void clear(); //reset whole maze
    void clearDist();
  //stack methods

};

#endif
