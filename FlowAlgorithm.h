#ifndef FlowAlgorithm_h
#define FlowAlgorithm_h

#define WALL = 600;

class FlowAlgorithm : public NAME {
  public:
  	Node(0, 0, 0, 0);
  	Node(int dist, int x, int y, int wall);
  	Nodeinit(int dist, int x, int y, int wall)
    int getcX();
    int getcY();
    int getPos();
    int [][] getDist();
    void push(bool next);
    void pop(bool next);
    int size(bool next);

    FlwAlgorithm(int pos, int cX, int cY);

    void clear();
    void clearDist();
    void updateLocation(int x, int y);
    void updateDir(int number);
    void mapWall(int x, int y, int readData[], int p);
    void mapMaze(int [] readData, int p, int iX, int iY, bool center);

};

#endif