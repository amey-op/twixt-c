#include "board.h"
#include "game.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
void reset(Board *b,Linkdata *ldata)
{

    for(int i=0;i<25;i++)
    {
        for(int j=0;j<25;j++)
        {
            b->pinboard[i][j]='.';
        }
    }
    ldata->blacklinkcount=0;
    ldata->redlinkcount=0;

    printf("Board reset successfull!\n");
}

int addpin(Board *b,Linkdata *ldata,int row,int col,Player p)
{
    if(p==RED && (col==0 || col==24))
    {
        printf("Red peg cannot be placed at the left and right edges!!\n");
        return 0;
    }
    else if(p==BLACK && (row==0 || row==24))
    {
        printf("Black peg cannot be placed at the top and bottom edges!!\n");
        return 0;
    }
    else if(validpin(b,row,col)==0)
    {
        printf("Invalid pin position!! Please try again!\n");
        return 0;
    }

    if(p==RED)
    {
        b->pinboard[row][col]='R';
    }
    else if(p==BLACK)
    {
        b->pinboard[row][col]='B';
    }
    printf("Pin %s placed successfully at (%d,%d) position\n",p==RED?"RED":"BLACK",row,col);

    int moves[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};


    for(int i=0;i<8;i++)
    {
        int row2=row+moves[i][0];
        int col2=col+moves[i][1];

        if(validlink(b,ldata,row,row2,col,col2,p)!=0)
        {
            addlink(b,ldata,row,row2,col,col2,p);
            printf("Linked (%d,%d)<--->(%d,%d)\n",row,col,row2,col2);
        }
    }

    return 1;
}

void addlink(Board *b,Linkdata *ldata,int r1,int r2,int c1,int c2,Player p)//add link
{
    Link newlink={r1,r2,c1,c2};
    if(p==RED)
    {
        ldata->redlinks[ldata->redlinkcount]=newlink;
        ldata->redlinkcount++;
    }
    else if(p==BLACK)
    {
        ldata->blacklinks[ldata->blacklinkcount]=newlink;
        ldata->blacklinkcount++;
    }
}

void print(Board *b)
{
    printf("\n    ");
    for(int j=0;j<25;j++)
    {
        if(j==1 || j==24)
        {
            printf(" ");
        }
        printf("%2d ",j);
    }
    printf("\n");
    
    for(int i=0;i<25;i++)
    {
        if(i==1 || i==24)
        {
            printf("--------------------------------------------------------------------------------\n");
        }
        printf("%2d ",i);
        for(int j=0;j<25;j++)
        {
            if((i==0 && j==0) || (i==24 && j==0))
            {
                printf("   |",b->pinboard[i][j]);
                continue;
            }
            else if((i==0 && j==24) || (i==24 && j==24))
            {
                printf("   ",b->pinboard[i][j]);
                continue;
            }
            else if(j==0 || j==23)
            {
                printf(" %2c|",b->pinboard[i][j]);
                continue;
            }
            printf(" %2c",b->pinboard[i][j]);
        }
        printf("\n");
    }
}

int validpin(Board *b,int row,int col)
{

    if(row<0 || row>=25 || col<0 || col>=25 || (row==0 && col==0) || (row==0 && col==24) || (row==24 && col==0) || (row==24 && col==24))
    {
       return 0; 
    }
    else if(b->pinboard[row][col]!='.')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



