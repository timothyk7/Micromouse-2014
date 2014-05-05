#include "MapMaker.h" //not included in maple

int main (int argc, char *argv[]) {
    char buff[BUFSIZ]={0}; //store commands
    
    //used to store if the program should read from file or the user
    FILE *pFile;
    pFile = stdin; //initialize to stdin
    int prompt; //if should prompt the user or not
    prompt = TRUE; //should promt user
    
    initialize("maze4.txt");
    int dist [MAP_SIZE][MAP_SIZE]={0}; /*debug*/
    
    char *str;
    for(DISPLAY_PROMPT; fgets(buff,BUFSIZ, pFile) !=NULL;DISPLAY_PROMPT)
    {
       str = strtok(buff, TOKEN_SEP);
       if(strcmp(str, "exit") == 0)
          break;      
       displayMaze(TRUE, dist,0,0,'N');
          
    }
    return 0;
}
