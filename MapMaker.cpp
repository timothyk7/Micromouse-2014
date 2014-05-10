#include "MapMaker.h"

///*Private*/
//void helpTop(int row)
//{
//    (void)printf("\t");
//    int col;
//    for(col = 0; col<MAX_SIZE; col++)
//    {
//       if(((mazeMap[row][col].wall>>2)&0x0001) == 0x0001)//if theres a top wall
//                (void)printf(" ____ ");
//       else
//                (void)printf("      ");//3 orig
//    }
//    (void)printf("\n");        
//}
//
//Info getMapInfo(int x, int y)
//{
//     return mazeMap[x][y];
//}
//
// /*
//     * Reads from a text file the positions to put the walls
//     * param 1: x coord
//     * param 2: y coord
//     * param 3: wall setup
//     */
// void initialize(const char *maze)
// {
//      FILE *inFile = 0; //file of maze
//      char buff[BUFSIZ]; //store string from file
//      char *endPtr; //for errors
//      inFile = fopen(maze, "r"); //open file
//      if(inFile == NULL) //if the file doesn't exist
//      {
//         (void)snprintf(buff, BUFSIZ,"%s", maze); //get error message
//         perror(buff); //print error message
//         exit(EXIT_FAILURE);
//      }
//      while(fgets(buff,BUFSIZ, inFile) !=NULL)
//      {
//        char *num; //num to read
//        char *endPtr; 
//        
//        num = strtok(buff,TOKEN_SEP);
//        int number; //data as int
//        int x =0; //counter of where to put data
//        Info data; //data holder
//        do
//        {
//            number = strtol(num,&endPtr,10);
//            if(x == 0)
//               data.x = number;
//            else if (x ==1)
//               data.y = number;
//            else
//            {
//                data.wall = number;
//                mazeMap[data.x][data.y] = data;
//            }
//            x++;
//            
//        }while((num = strtok(NULL,TOKEN_SEP)) != NULL);
//      }
// }
// 
///*
// * Display the map of the full maze
//   param: 
//          1 whether to display floodfill algorithm
//          2 current map of the bot (floodfill numbers)
//          3 current x location
//          4 current y location
//          5 direction
// */
//void displayMaze(int num, int number[MAX_SIZE][MAX_SIZE], int cX, int cY, char dir)
//      {
//        (void)printf("\t ");
//        int x = 0;
//        for (x=0; x<MAX_SIZE; x++)
//        {
//            (void)printf("%d",x%10);    
//            (void)printf("     "); //2 orig
//        }
//        (void)printf("\n");
//        
//        
//        int row = 0;
//        for (row = 0; row < MAX_SIZE; row++)
//        {
//          helpTop(row);
//          (void)printf("%d\t",row);
//          int col = 0;
//          for (col =0; col < MAX_SIZE; col++)
//          {
//              if(((mazeMap[row][col].wall>>1) & 0x0001) == 0x0001)//if theres a left wall
//                (void)printf("|");
//              else
//                (void)printf(" ");
//              if(cX == row && cY == col){
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
//                    (void)printf("_%c%c_",dir,dir);
//                else
//                    (void)printf("_%c%c_",dir,dir);
//              }else if(num){
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001){//if theres a bottom wall
//                    if(number[row][col]<10)
//                       (void)printf("_%d__",number[row][col]);
//                    else if(number[row][col]<100)
//                       (void)printf("_%d_", number[row][col]);
//                    else
//                       (void)printf("_%d", number[row][col]);
//                }
//                else{
//                    if(number[row][col]<10)
//                       (void)printf(" %d  ", number[row][col]);
//                    else if(number[row][col]<100)
//                       (void)printf(" %d ", number[row][col]);
//                    else
//                       (void)printf(" %d", number[row][col]);
//                }
//              }else{
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
//                    (void)printf("____");
//                else
//                    (void)printf("    ");
//              }
//                
//              if((mazeMap[row][col].wall&0x0001) == 0x0001)//if theres a rt wall
//                (void)printf("|");
//              else
//                (void)printf(" ");
//          }
//          (void)printf("\n");
//        }
//      }
//        
///*
// * Display the map of the current bot maze
//   param: 
//          1 whether to display floodfill algorithm
//          2 current map of the bot (floodfill numbers)
//          3 current map of bot
//          4 current x location
//          5 current y location
//          6 direction
// */
//void displayBotMaze(int num, int number[MAX_SIZE][MAX_SIZE], Info map[MAX_SIZE][MAX_SIZE], int cX, int cY, char dir)
//      {
//        (void)printf("\t ");
//        int x = 0;
//        for (x=0; x<MAX_SIZE; x++)
//        {
//            (void)printf("%d",x%10);    
//            (void)printf("     "); //2 orig
//        }
//        (void)printf("\n");
//        
//        
//        int row = 0;
//        for (row = 0; row < MAX_SIZE; row++)
//        {
//          helpTop(row);
//          (void)printf("%d\t",row);
//          int col = 0;
//          for (col =0; col < MAX_SIZE; col++)
//          {
//              if(((mazeMap[row][col].wall>>1) & 0x0001) == 0x0001)//if theres a left wall
//                (void)printf("|");
//              else
//                (void)printf(" ");
//              if(cX == row && cY == col){
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
//                    (void)printf("_%c%c_",dir,dir);
//                else
//                    (void)printf("_%c%c_",dir,dir);
//              }else if(num){
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001){//if theres a bottom wall
//                    if(number[row][col]<10)
//                       (void)printf("_%d__",number[row][col]);
//                    else if(number[row][col]<100)
//                       (void)printf("_%d_", number[row][col]);
//                    else
//                       (void)printf("_%d", number[row][col]);
//                }
//                else{
//                    if(number[row][col]<10)
//                       (void)printf(" %d  ", number[row][col]);
//                    else if(number[row][col]<100)
//                       (void)printf(" %d ", number[row][col]);
//                    else
//                       (void)printf(" %d", number[row][col]);
//                }
//              }else{
//                if(((mazeMap[row][col].wall>>3)&0x0001) == 0x0001)//if theres a bottom wall
//                    (void)printf("____");
//                else
//                    (void)printf("    ");
//              }
//                
//              if((mazeMap[row][col].wall&0x0001) == 0x0001)//if theres a rt wall
//                (void)printf("|");
//              else
//                (void)printf(" ");
//          }
//          (void)printf("\n");
//        }
//        
//}
