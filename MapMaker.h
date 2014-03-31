#ifndef MAPMAKER_HPP
#define MAPMAKER_HPP

#define MAP_SIZE  16
#define FALSE 0
#define TRUE 1
#define TOKEN_SEP " \t\n"
#define PROMPT "> "
#define DISPLAY_PROMPT ( (prompt != FALSE) ? (void) printf( PROMPT ) : (void)0 )


#define WALL_VALUES 0x0000, 0x0001,0x0010,0x0011,0x0100,0x0101,0x0110,0x0111, \
                    0x1000,0x1001,0x1010,0x1011,0x1100,0x1101,0x1110,0x1111

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//struct w/ coord and walls for bot
struct info{
              int x;
              int y;
              unsigned int wall;
};

typedef struct info Info;
      
//methods
//variables
Info mazeMap [MAP_SIZE][MAP_SIZE]; //map of maze
FILE *inFile = 0; //file of maze
char buff[BUFSIZ]; //store string from file
char *endPtr; //for errors

/*Private*/
void helpTop(int row)
{
    (void)printf("\t");
    int col;
    for(col = 0; col<MAP_SIZE; col++)
    {
       if(((mazeMap[row][col].wall>>2)&0x0001) == 0x0001)//if theres a top wall
                (void)printf(" ____ ");
       else
                (void)printf("      ");//3 orig
    }
    (void)printf("\n");        
}

Info getMapInfo(int x, int y)
{
     return mazeMap[x][y];
}

 /*
     * Reads from a text file the positions to put the walls
     * param 1: x coord
     * param 2: y coord
     * param 3: wall setup
     */
 void initialize(const char *maze)
 {
      inFile = fopen(maze, "r"); //open file
      if(inFile == NULL) //if the file doesn't exist
      {
         (void)snprintf(buff, BUFSIZ,"%s", maze); //get error message
         perror(buff); //print error message
         exit(EXIT_FAILURE);
      }
      while(fgets(buff,BUFSIZ, inFile) !=NULL)
      {
        char *num; //num to read
        char *endPtr; 
        
        num = strtok(buff,TOKEN_SEP);
        int number; //data as int
        int x =0; //counter of where to put data
        Info data; //data holder
        do
        {
            number = strtol(num,&endPtr,10);
            if(x == 0)
               data.x = number;
            else if (x ==1)
               data.y = number;
            else
            {
                data.wall = number;
                mazeMap[data.x][data.y] = data;
                //(void)printf("%d %d| %d", data.x, data.y, data.wall); /*DEBUG*/
                //(void)printf("\n");
                //(void)printf("data: %d %d| %d", mazeMap[data.x][data.y].x, mazeMap[data.x][data.y].y, mazeMap[data.x][data.y].wall); /*DEBUG*/
                //(void)printf("\n");
            }
            x++;
            
        }while((num = strtok(NULL,TOKEN_SEP)) != NULL);
          
        //(void)printf("%d", number);
      }
 }
 
void display(int num, int number[MAP_SIZE][MAP_SIZE], int cX, int cY, char dir)
      {
        (void)printf("\t ");
        int x = 0;
        for (x=0; x<MAP_SIZE; x++)
        {
            (void)printf("%d",x%10);    
            (void)printf("     "); //2 orig
        }
        (void)printf("\n");
        
        
        int row = 0;
        for (row = 0; row < MAP_SIZE; row++)
        {
          helpTop(row);
          (void)printf("%d\t",row);
          int col = 0;
          for (col =0; col < MAP_SIZE; col++)
          {
              //System.out.print(mazeMap[row][col] + "\t");
              //(void)printf("info: %d, %d",mazeMap[row][col].wall,mazeMap[row][col].wall & 0x0010 );
              if(((mazeMap[row][col].wall>>1) & 0x0001) == 0x0001)//if theres a left wall
                (void)printf("|");
              else
                (void)printf(" ");
              if(cX == row && cY == col){
                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
                    (void)printf("_%c%c_",dir,dir);
                else
                    (void)printf("_%c%c_",dir,dir);
              }else if(num){
                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001){//if theres a bottom wall
                    if(number[row][col]<10)
                       (void)printf("_%d__",number[row][col]);
                    else if(number[row][col]<100)
                       (void)printf("_%d_", number[row][col]);
                    else
                       (void)printf("_%d", number[row][col]);
                }
                else{
                    if(number[row][col]<10)
                       (void)printf(" %d  ", number[row][col]);
                    else if(number[row][col]<100)
                       (void)printf(" %d ", number[row][col]);
                    else
                       (void)printf(" %d", number[row][col]);
                }
              }else{
                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
                    (void)printf("____");
                else
                    (void)printf("    ");
              }
                
              if((mazeMap[row][col].wall&0x0001) == 0x0001)//if theres a rt wall
                (void)printf("|");
              else
                (void)printf(" ");
          }
          (void)printf("\n");
        }
}
      

#endif
