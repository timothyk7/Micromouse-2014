#ifndef MAPMAKER_H
#define MAPMAKER_H

#define MAX_SIZE  16
#define FALSE 0
#define TRUE 1
#define TOKEN_SEP " \t\n"

#define PROMPT "> "
#define DISPLAY_PROMPT ( (prompt != FALSE) ? (void) printf( PROMPT ) : (void)0 )

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//struct w/ coord and walls for bot
struct info{
              unsigned int x;
              unsigned int y;
              unsigned int wall;
};

typedef struct info Info;

class MapMaker
{
public:    

   Info getMapInfo(int x, int y);
   void initialize(const char *maze);
   void displayMaze(int num, int number[MAX_SIZE][MAX_SIZE], int cX, int cY, char dir);
   void displayBotMaze(int num, int number[MAX_SIZE][MAX_SIZE], int map[MAX_SIZE][MAX_SIZE], int cX, int cY, char dir);

private:         
//variables
   Info mazeMap [MAX_SIZE][MAX_SIZE]; //map of maze from file

   void helpTop(int row);
   void helpTopBot(int row, int wall[MAX_SIZE][MAX_SIZE]);
};
      

#endif
