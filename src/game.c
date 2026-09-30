#include "board.h"
#include "game.h"
#include<stdlib.h>
#include<stdio.h>

void help()
{
    printf("--------------------------------Rules--------------------------------\n");
    printf("1. Two players Red and Black take turns to place pegs on a 24x24 board.\n");
    printf("2. The pegs can be connected using links when the pegs are at distance of a chess knight.\n");
    printf("3. The first player to reach the opposite side of the board using continuous linkage wins.\n");
    printf("4. You cannot make a link which crosses opponent's or your own existing linkage.\n");
    printf("5. Red connects top to bottom, and Black connects left to right.\n\n");

    printf("--------------------------------Commands--------------------------------\n");
    printf("1. To place a peg at (x,y) --> place x y\n");
    printf("2. To view the pin board --> view board\n");
    printf("3. To view the guide --> view guide\n");
    printf("4. To reset the board and play again --> reset\n");
    printf("5. To exit the game --> exit\n");
    printf("6. To view all the links present --> view links\n");
}


int orientation(int x1, int y1, int x2, int y2,int x3, int y3)
{
   long long val=(long long)x1*(y2-y3)+(long long)x2*(y3-y1)+(long long)x3*(y1-y2);
   if(val==0)
   {
    return 0;//collinear
   }
   return (val>0)?1:2;//1:Right,2:Left
}


int segintersect(Link A,Link B)
{
    int A_x1=A.c1,A_x2=A.c2,A_y1=A.r1,A_y2=A.r2;
    int B_x1=B.c1,B_x2=B.c2,B_y1=B.r1,B_y2=B.r2;

    int o1=orientation(A_x1,A_y1,A_x2,A_y2,B_x1,B_y1);//orientation of first B wrt line A
    int o2=orientation(A_x1,A_y1,A_x2,A_y2,B_x2,B_y2);//orientation of second B wrt line A
    int o3=orientation(B_x1,B_y1,B_x2,B_y2,A_x1,A_y1);//orientation of first A wrt line B
    int o4=orientation(B_x1,B_y1,B_x2,B_y2,A_x2,A_y2);//orientation of second A wrt line B

    return (o1!=o2 && o3!=o4);//check the the intersection by confirming both the cases
}


int validlink(Board *b,Linkdata *ldata,int r1,int r2,int c1,int c2,Player p)
{
    if(r2<0 || r2>=25 || c2<0 || c2>=25)//verify if linking is possible
    {
        return 0;
    }
    char peg=(p==RED)?'R':'B';

    if(b->pinboard[r2][c2]!=peg)
    {
        return 0;
    }

    int r=abs(r1-r2);
    int c=abs(c1-c2);
    if(((r==2 && c==1) || (r==1 && c==2))==0)//checking for knight move
    {
        return 0;
    }
    
    Link newlink={r1,r2,c1,c2};//store link that was added

    for(int i=0;i<ldata->redlinkcount;i++)//check for intersection with other linkages
    {
        Link L=ldata->redlinks[i];
        if ((L.r1 == r1 && L.c1 == c1) || (L.r2 == r1 && L.c2 == c1) ||
             (L.r1 == r2 && L.c1 == c2) || (L.r2 == r2 && L.c2 == c2))
        {
            continue;
        }
        if(segintersect(newlink,L))
        {
            return 0;
        }
    }

    for(int i=0;i<ldata->blacklinkcount;i++)//check for intersection with other linkages
    {
        Link L=ldata->blacklinks[i];
        if ((L.r1 == r1 && L.c1 == c1) || (L.r2 == r1 && L.c2 == c1) ||
             (L.r1 == r2 && L.c1 == c2) || (L.r2 == r2 && L.c2 == c2)) 
        {
            continue;
        }
        if(segintersect(newlink,L))
        {
            return 0;
        }
    }

    return 1;
}


int linkexist(Linkdata *ldata,Player p,int r1,int c1,int r2,int c2)
{
   Link *arr=(p==RED)?ldata->redlinks:ldata->blacklinks;
    int count=(p==RED)?ldata->redlinkcount:ldata->blacklinkcount;

    for(int i=0;i<count;i++)
    {
        if ((arr[i].r1 == r1 && arr[i].c1 == c1 && arr[i].r2 == r2 && arr[i].c2 == c2) ||
             (arr[i].r1 == r2 && arr[i].c1 == c2 && arr[i].r2 == r1 && arr[i].c2 == c1))
        {
            return 1;
        }
    }
    return 0;
}


int visited[25][25];
void checkwin1(Board *b,Linkdata *ldata,int row,int col,Player p)
{
   visited[row][col]=1;
   int moves[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
   char peg=(p==RED)?'R':'B';

    for(int i=0;i<8;i++)
    {
        int r2=row+moves[i][0];
        int c2=col+moves[i][1];

        if(r2<0 || r2>=25 || c2<0 || c2>=25)
        {
            continue;
        }
        if(b->pinboard[r2][c2]!=peg)
        {
            continue;
        }
        if(visited[r2][c2]==1)
        {
            continue;
        }
        if(linkexist(ldata,p,row,col,r2,c2)==0)
        {
            continue;
        }

        checkwin1(b,ldata,r2,c2,p);
    }
}


void playerswitch(Player *p)//for turns
{
    *p=(*p==RED)?BLACK:RED;
}


int checkwin2(Board *b,Linkdata *ldata,Player p)
{
   for(int i=0;i<25;i++)
   {
    for(int j=0;j<25;j++)
    {
        visited[i][j]=0;
    }
   }

   if(p==RED)//check for red win
   {
    for(int i=0;i<25;i++)//start with first row
    {
        if(b->pinboard[0][i]=='R')
        {
            checkwin1(b,ldata,0,i,RED);
        }
    }

    for(int i=0;i<25;i++)
    {
        if(b->pinboard[24][i]=='R' && visited[24][i]==1)
        {
            return 1;//won
        }
    }
   }
   else//check for black win
   {
    for(int j=0;j<25;j++)//start with first column
    {
        if(b->pinboard[j][0]=='B')
        {
            checkwin1(b,ldata,j,0,BLACK);
        }
    }

    for(int j=0;j<25;j++)//end check
    {
        if(b->pinboard[j][24]=='B' && visited[j][24]==1)
        {
            return 1;//won
        }
    }
   }
   return 0;
}
