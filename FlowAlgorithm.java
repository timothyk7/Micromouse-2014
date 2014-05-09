
/**
 * FlowAlgorithm
 * 
 * @author Timothy Kua
 * @version 1.0
 */
public class FlowAlgorithm
{
    
    private final int WALL = 600;
    //mapping stuff
    private class Node {
        public int dist;
        public int x;
        public int y;
        public int wall;
        public Node(int dist, int x, int y, int wall)
        {
            this.dist = dist;
            this.x = x;
            this.y=y;
            this.wall=wall;
        }
    }
    //no wall bits (N)
    private int E = 0x0010;
    private int W = 0x0001;
    private int N = 0x0100;
    private int S = 0x1000;
    //dir bot faces | current loc
    private int pos = 0;
    private int DIR_SIZE=4;
    private char[] dir = {'N','E','S','W'};
    private int cX = 0;
    private int cY = 0;
    //maze in matrix
    private final int MAP_SIZE = 16;
    private Node [][]mazeMap = new Node[16][16];
    private boolean once = true;
    //array stack
    private int c_stack_size=0;
    private int n_stack_size=0;
    private int STACK_CAP = 256;
    private Node node;
    private Node []c_stack = new Node[256]; //locations that the bot could visit
    private Node []n_stack = new Node[256]; //new locations to go

    /*Keep track where bot is*/
    public int getcX()
    {
        return cX;
    }
    
    public int getcY()
    {
        return cY;
    }

    public int getPos()
    {
        return pos;
    }
    
    public int [][] getDist()
    {
        int [][] dist = new int[MAP_SIZE][MAP_SIZE];
        for(int x=0; x<MAP_SIZE;x++)
        {
          for(int y =0; y<MAP_SIZE;y++)
          {
            dist[x][y] = mazeMap[x][y].dist;
          }
        }
        return dist;
        
    }
    /*Stack Methods (use to access stack array)*/
    void push(boolean next)
    {
        if(!next)
        {
            assert(c_stack_size+1<STACK_CAP);
            c_stack[c_stack_size] = node;
            c_stack_size++;
        }
        else
        {
            assert(n_stack_size+1<STACK_CAP);
            n_stack[n_stack_size] = node;
            n_stack_size++;
        }
    }


    void pop(boolean next)
    {
        if(!next)
        {
            assert(c_stack_size-1>=0);
            node = c_stack[c_stack_size-1];
            c_stack_size--;
        }
        else
        {
            assert(n_stack_size-1>=0);
            node = n_stack[n_stack_size-1];
            n_stack_size--;
        }
    }

    int size(boolean next)
    {
        if(next)
            return n_stack_size;
        else
            return c_stack_size;
    }

    public FlowAlgorithm(int pos, int cX, int cY)
    {
        this.pos = pos;
        this.cX = cX;
        this.cY = cY;
        clear();
    }
    
    boolean coordCheck(int coord)
    {
        return coord >=0 && coord<MAP_SIZE;
    }
    
    public void clear()
    {
        for(int x=0; x<MAP_SIZE;x++)
        {
          for(int y =0; y<MAP_SIZE;y++)
          {
            mazeMap[x][y] = new Node(257,x,y,0);
          }
        }
    }
    
    public void clearDist()
    {
        for(int x=0; x<MAP_SIZE;x++)
        {
          for(int y =0; y<MAP_SIZE;y++)
          {
            mazeMap[x][y].dist = 257;
          }
        }
    }
    
    

    void updateLocation(int x, int y) //update current location
    {
        cX = x;
        cY = y;
    }

    void updateDir(int number) //if turns, update direction its facing
    {
        pos = number;
        //System.out.println("Flow dir: "+dir[pos]);
    }

    // 0 = no wall 1 = wall
    //readData provided
    void mapWall(int x, int y, int [] readData, int p)
    {
      //System.out.println("Flow mapWall: "+dir[p]);
      if(dir[p] == 'N'){
           E = 0x0001;
           W = 0x0010;
           N = 0x0100;
           S = 0x1000;
      }else if (dir[p] == 'E'){
           E = 0x1000;
           W = 0x0100;
           N = 0x0001;
           S = 0x0010;
       }else if (dir[p] == 'S'){
           E = 0x0010;
           W = 0x0001;
           N = 0x1000;
           S = 0x0100;
       }else if (dir[p] == 'W'){
           E = 0x0100;
           W = 0x1000;
           N = 0x0010;
           S = 0x0001;
       }else
           assert(false);
        
      if(readData[0] <WALL)  //checking if wall on left
      {
        mazeMap[x][y].wall = mazeMap[x][y].wall |W;
        
        //putting up wall on the other side
        if(dir[pos] == 'N' && coordCheck(y-1)){
            mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |E;
        }else if(dir[pos] =='E'&& coordCheck(x-1)){
            mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |E;
        }else if(dir[pos] == 'S' && coordCheck(y+1)){
            mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |E;
        }else if(dir[pos] =='W' && coordCheck(x+1)){
            mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |E;
        }
      }
      if(readData[4] <WALL) //right
      {
        mazeMap[x][y].wall = mazeMap[x][y].wall |E;
        if(dir[pos] == 'N' && coordCheck(y+1)){
            mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |W;
        }else if(dir[pos] =='E'&& coordCheck(x+1)){
            mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |W;
        }else if(dir[pos] == 'S' && coordCheck(y-1)){
            mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |W;
        }else if(dir[pos] =='W' && coordCheck(x-1)){
            mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |W;
        }
      }
      if((readData[1]+readData[2]+readData[3])/3 <WALL) //front
      {
            //System.out.println("mapwall front: "+N+" "+S+"..."+x+" "+y);
        mazeMap[x][y].wall = mazeMap[x][y].wall |N;
            //System.out.println("mapwall front wall: "+mazeMap[x][y].wall);
        if(dir[pos] == 'N' && coordCheck(x-1)){
            mazeMap[x-1][y].wall = mazeMap[x-1][y].wall |S;
        }else if(dir[pos] =='E'&& coordCheck(y+1)){
            mazeMap[x][y+1].wall = mazeMap[x][y+1].wall |S;
        }else if(dir[pos] == 'S' && coordCheck(x+1)){
            mazeMap[x+1][y].wall = mazeMap[x+1][y].wall |S;
        }else if(dir[pos] =='W' && coordCheck(y-1)){
            mazeMap[x][y-1].wall = mazeMap[x][y-1].wall |S;
        }
      }
      
    }
    
    //precondition: pos must be set the same way robot is facing
    //              must start in corner
    //              end of maze must be in center
    //readData provided
    public void mapMaze(int [] readData, int p, int iX, int iY, boolean center)
    {
      //map the maze
      assert(size(true) ==0 && size(false) == 0);
      mapWall(cX,cY,readData,p);
        
      //flood the maze
      int x=0,y=0; // store node value
      int level = 0; //shortest dist
      clearDist();
      if(center)
      {
          node = mazeMap[iX][iY];
          push(false);
      }else{
          node = mazeMap[MAP_SIZE/2-1][MAP_SIZE/2-1];
          push(false);
          node = mazeMap[MAP_SIZE/2-1][MAP_SIZE/2];
          push(false);
          node = mazeMap[MAP_SIZE/2][MAP_SIZE/2-1];
          push(false);
          node = mazeMap[MAP_SIZE/2][MAP_SIZE/2];
          push(false);
      }
      do
      {
          n_stack_size = 0;
          n_stack = new Node[256];
          while(size(false) >0)
          {
              pop(false);
              x = node.x;
              y = node.y;
                    //System.out.println(x+" "+y);
              if(mazeMap[x][y].dist ==257)
              {
                            //System.out.println("ran "+n_stack_size);
                    mazeMap[x][y].dist = level; //level manipulation 
                    //left
                    if(coordCheck(y-1) && !((mazeMap[x][y].wall&0x0010)==0x0010) && mazeMap[x][y-1].dist ==257) //check whether to push onto the stack
                    {
                            //System.out.println("ranl"+x+" "+(y-1));
                        node = mazeMap[x][y-1];
                        push(true);
                    }
                    //right
                    if(coordCheck(y+1) && !((mazeMap[x][y].wall&0x0001) == 0x0001) && mazeMap[x][y+1].dist ==257 )
                    {
                             //System.out.println("ranr"+x+" "+(y+1));
                        node = mazeMap[x][y+1];
                        push(true);
                    }
                    //up
                    if(coordCheck(x-1) && !((mazeMap[x][y].wall&0x0100) == 0x0100)&& mazeMap[x-1][y].dist ==257 )
                    {
                              //System.out.println("ranu"+(x-1)+" "+y);
                        node = mazeMap[x-1][y];
                        push(true);
                    }
                    //down
                    if(coordCheck(x+1) && !((mazeMap[x][y].wall&0x1000) == 0x1000) && mazeMap[x+1][y].dist ==257 )
                    {
                               //System.out.println("rand"+(x+1)+" "+y);
                        node = mazeMap[x+1][y];
                        push(true);
                    }
                    node = null;
              }
          }
                //System.out.println(size(true));
          level++;
          c_stack = n_stack;
          c_stack_size = n_stack_size;
      }while(size(true)>0);
      n_stack_size = 0;
      once = false;
    }
    /*
     * For help
     */
    
     public void display(boolean num)
      {
        System.out.print("\t ");
        for (int x=0; x<MAP_SIZE; x++)
        {
            System.out.print(x%10);    
            System.out.print("     "); //2 orig
        }
        System.out.println();

        for (int row = 0; row < MAP_SIZE; row++)
        {
          helpTop(row);
          System.out.print((row) + "\t");
          for (int col =0; col < MAP_SIZE; col++)
          {
              if((mazeMap[row][col].wall & 0x0010) == 0x0010)//if theres a left wall
                System.out.print("|");
              else
                System.out.print(" ");
              if(cX == row && cY == col){
                if((mazeMap[row][col].wall&0x1000) == 0x1000)//if theres a bottom wall
                    System.out.print("_"+dir[pos]+dir[pos]+"_");
                else
                    System.out.print(" "+dir[pos]+dir[pos]+" ");
              }else if(num){
                if((mazeMap[row][col].wall&0x1000) == 0x1000){//if theres a bottom wall
                    if(mazeMap[row][col].dist<10)
                       System.out.print("_" + mazeMap[row][col].dist +"__");
                    else if(mazeMap[row][col].dist<100)
                       System.out.print("_" + mazeMap[row][col].dist +"_");
                    else
                       System.out.print("_" + mazeMap[row][col].dist +""); 
                }
                else{
                    if(mazeMap[row][col].dist<10)
                       System.out.print(" " + mazeMap[row][col].dist +"  ");
                    else if(mazeMap[row][col].dist<100)
                       System.out.print(" " + mazeMap[row][col].dist +" ");
                    else
                       System.out.print(" " + mazeMap[row][col].dist +""); 
                }
              }else{
                if((mazeMap[row][col].wall&0x1000) == 0x1000)//if theres a bottom wall
                    System.out.print("____");
                else
                    System.out.print("    ");
              }
                
              if((mazeMap[row][col].wall&0x0001) == 0x0001)//if theres a rt wall
                System.out.print("|");
              else
                System.out.print(" ");
          }
          System.out.println();
        }
      }
    
     private void helpTop(int row)
     {
         System.out.print("\t");
         for(int col = 0; col<MAP_SIZE; col++)
         {
             if((mazeMap[row][col].wall&0x0100) == 0x0100)//if theres a top wall
                System.out.print(" ____ ");
             else
                System.out.print("      ");//3 orig
         }
         System.out.println();
     }

}
