
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;
void fillBorad(int** board)
{
      int k=0;
        for(int i=9;i>=0;i--)
        {
            int* array=new int[10];//Creating each row
            if(i%2!=0)
            for(int j=0;j<=9;j++)
            {
                k++;
                array[j]=k; //filling each column
                
            }
            else
            for(int j=9;j>=0;j--)
            {
                k++;
                array[j]=k;  //filling each column
            }
            board[i]=array;
        }
}
void printBoard(int** board)
{
    cout<<"\n";
       cout<<"\t\tSnake Ladder Game!!!\n";
        int row=0,col=0;
        for(int i=1;i<=21;i++)
        {
           for(int j=1;j<=60;j++)
           {
               int k=j%6;
               if(i==1||i%2!=0||j==1||j%6==0)
                cout<<"#";
                else if(k%3==0)
                {
                    //Fethching value from array
                    int step=board[row][col];
                    col++;
                    if(col==10)
                    {
                        row++;
                        col=0;
                    }
                    if(step<10)
                    cout<<"0"<<step;//add 0 with single digit
                    else
                    cout<<step;
                }
                else if(k%4==0)
                {
                    //do nothing
                }
                else if(i==2&&j==2)
                {
                   //do nothing
                }
                else
                cout<<" ";
                
           }
            cout<<"\n";
            
        }
}
int** create9Snakes()
{
    int** snakes=new int*[9];
    int j=3;
     for(int i=0;i<=8;i++)
     {
            j++;
            int* snake=new int[4];
         
            int head_row=(j+(i*3))%9; 
            int head_col=(i+(j*3))%10;
            
            int margin=9-head_row;
            int snake_len=(j*(j+1))%margin;
            int tail_row=head_row+snake_len+1;
            int tail_col=(i*j+(j*3))%10;
            
            //filling snake
            snake[0]=head_row;
            snake[1]=head_col;
            snake[2]=tail_row;
            snake[3]=tail_col;
            //Add snake to snakes
            snakes[i]=snake;
            
            
      }

    return snakes;
}
int** create9Ladders()
{
    int** ladders=new int*[9];
    int j=3;
    int k=9;
     for(int i=0;i<=8;i++)
     {
            j=j+1;
            k=i;
            int* ladder=new int[4];
         
            int start_row=9-((j+(k*3))%9); 
            int start_col=(k+2+(j*3))%10;
            
            int margin=start_row;
            int ladder_len=(11*j+2*(j+4)/2)%margin;
            if(ladder_len==0)
            ladder_len=1;
            int end_row=start_row-ladder_len;
            int end_col=(k*j+3+(j*3))%10;
            
            //filling ladder
            ladder[0]=start_row;
            ladder[1]=start_col;
            ladder[2]=end_row;
            ladder[3]=end_col;
            //Add ladders to ladder
            ladders[i]=ladder;
            
            
      }
    


    return ladders;
}
bool removeConfilicts(int** snakes,int** ladders,int** board)
{
    
    
    for(int i=0;i<=8;i++)
    {
        int* snake=snakes[i];
           int s1=snake[0];//snake head row
           int s2=snake[1];//snake head column
           for(int j=0;j<=8;j++)
           {
               int snake_head=board[s1][s2];
           int* ladder=ladders[j];
           int l1=ladder[0];//ladder start row
           int l2=ladder[1];//ladder start column
               int ladder_start=board[l1][l2];
           if(snake_head==ladder_start)
              {
                   ladder[1]=(ladder[1]+1)%10;
                   removeConfilicts(snakes,ladders,board);//Call again to remove confilicts
              }
           }
           
            
       
    }
    
    return 1;  //if no confilicts
}
void printSnakesMsgs(int** snakes,int** board)
{
    cout<<"\n";
    cout<<"Be Aware!!!\n";
    cout<<"Snakes are as follows:\n";
    
    for(int i=0;i<=8;i++)
    {
        int* snake=snakes[i];//Getting each snake
        int h_r=snake[0];
        int h_c=snake[1];
        int t_r=snake[2];
        int t_c=snake[3];
        //printing msg
        cout<<"From "<<board[h_r][h_c]<<" to "<<board[t_r][t_c]<<"\n";
    }
    
    
}

void printLaddersMsgs(int** ladders,int** board)
{
    cout<<"\n";
    cout<<"Climbing Steps!!!\n";
    cout<<"Ladders are as follows:\n";
    
    for(int i=0;i<=8;i++)
    {
        int* ladder=ladders[i];//Getting each ladder
        int s_r=ladder[0];
        int s_c=ladder[1];
        int e_r=ladder[2];
        int e_c=ladder[3];
        //Printing msgs
        cout<<"From "<<board[s_r][s_c]<<" to "<<board[e_r][e_c]<<"\n";
    }
    
    
}



int checkLuck(int** snakes,int** ladders,int* position,int dice_num)
{          
               int c_r=position[0];
               int c_c=position[1];
               if(c_r%2!=0)
               {
                   //Row is Odd
                  if(c_c+dice_num>9)
                  {
                      int a=c_c+dice_num-9;
                      c_c=10-a;
                      c_r=c_r-1;
                      if(c_r<0)//No more row
                      return 0;
                      //update with new position
                    position[0]=c_r;
                    position[1]=c_c;
                   }
                  else
                  {
                    position[1]=c_c+dice_num;
               }
               }
               else
               {
                  //Row is even 
                   if(c_c-dice_num<0)
                  {
                      int a=c_c-dice_num;
                      c_c=-1-a;
                      c_r=c_r-1;
                      if(c_r<0)//No more row
                      return 0;
                      //update with new position
                    position[0]=c_r;
                    position[1]=c_c;
                   }
                  else
                  {
                     position[1]=c_c-dice_num;
                  }
                   
                   
                   
               }
               //Now Check new postions
        for(int i=0;i<=8;i++)
        {
            int c_r=position[0];
            int c_c=position[1];
          //get snake data
          int* snake=snakes[i];
           int sh_r=snake[0];
           int sh_c=snake[1];
           
           int st_r=snake[2];
           int st_c=snake[3];
          if(c_r==sh_r&&c_c==sh_c)
          {
              //Got snake 
              //update position with tail row and column
              position[0]=st_r;
              position[1]=st_c;
              return -1;
          }
          else
          {
              //get ladder data
           int* ladder=ladders[i];
           int ls_r=ladder[0];
           int ls_c=ladder[1];
           
           int le_r=ladder[2];
           int le_c=ladder[3];
              if(c_r==ls_r&&c_c==ls_c)
              {
              //Got Ladder 
              //update position with ladder's end  row and column
              position[0]=le_r;
              position[1]=le_c;
              return 1;
              }
            }
            
            
            
            
            
            
        }
        //Got No Ladder No Snake
        return 0;
}

int myrand()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
   return (ltm->tm_sec%ltm->tm_min)%6+1;
}


//Function Move
int move(int p_index,string players[2],int** positions,int* statuses,int** board,int** snakes,int** ladders)
{
    int dice_num=(rand()%6)+1;
    int* position=positions[p_index];
    int c_r=position[0];
    int c_c=position[1];
    cout<<players[p_index]<<" You got "<<dice_num<<" on Dice Roll...\n";
    if(statuses[p_index]==-1)
    {
        if(dice_num!=6)
        cout<<players[p_index]<<"! Please try to make 6 on dice to start on board...\n";
        else
        {
            cout<<"Congrates "<<players[p_index]<<"! You got 6 and start on board...\n";
            statuses[p_index]=1;
        }
        
    }
    else
    {
      int luck=checkLuck(snakes,ladders,position,dice_num);
             c_r=position[0];
             c_c=position[1];
        if(luck==1)
        {
            cout<<players[p_index]<<"! You got Lucky...\n";
            cout<<players[p_index]<<"! Now you are at "<<board[c_r][c_c]<<"...\n";
            
        }
        else if(luck==-1)
        {
            cout<<"Opps "<<players[p_index]<<"! You got snake...\n";
            cout<<players[p_index]<<"! Now you are at "<<board[c_r][c_c]<<"...\n";
        }
        else
        {
            cout<<players[p_index]<<"! Now you are at "<<board[c_r][c_c]<<"...\n";
        }
        
        
    }
    
    if(board[c_r][c_c]==100)
    {
        cout<<players[p_index]<<" is Winner!\n";
        cout<<"Congradulations to "<<players[p_index]<<"!\n";
        return -1;
    }
    return 0;
}
int main()
{
    //Creating Array 2D Array of snake board
    int** board=new int*[10];
    fillBorad(board);//Filling 2D Array
    int** snakes=create9Snakes();
    int** ladders=create9Ladders();
    //Removing confilicts from board
    removeConfilicts(snakes,ladders,board);
    //Print board on console
    printBoard(board);
    //print Snake palces
    printSnakesMsgs(snakes,board);
    //print Ladders palces
    printLaddersMsgs(ladders,board);
    
    //Array both Players names
    string players[2];
    //Taking input from user
    cout<<"Enter First Player's name!\n";
    getline(cin,players[0]);
    cout<<"Enter Second Player's name!\n";
    getline(cin,players[1]);
    
    //Setting postions of both players
    int** positions=new int*[2];
     int p1_pos[2]={9,0};
     int p2_pos[2]={9,0};
     positions[0]=p1_pos;
     positions[1]=p2_pos;
     //Status of both players
     int statuses[2]={-1,-1};
     
      int current_player=0;
      int game_status=0;
      int turn_num=1;
      while(game_status!=-1)
      {
        cout<<"\n";
        cout<<"Turn Number:"<<turn_num<<"\n";
        cout<<players[current_player]<<"! Press any key,then Enter to take your turn...\n";
         char c;
         cin>>c;
        game_status=move(current_player,players,positions,statuses,board,snakes,ladders);
        
        //Changing turns
        if(current_player==0)
        current_player=1;
        else if(current_player==1)
           current_player=0;
           
           turn_num++;
      }
    
    
    
    return 0;
}

