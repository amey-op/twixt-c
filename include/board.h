#ifndef BOARD_H
#define BOARD_H


typedef enum{
    EMPTY,
    RED,BLACK
}Player;

typedef enum{
    PLACE,
    SHOW,
    QUIT
}Commands;

typedef struct{
    char pinboard[25][25];
}Board;

typedef struct{
    int r1,r2;
    int c1,c2;
}Link;

typedef struct
{
    Link redlinks[1000];
    Link blacklinks[1000];
    int redlinkcount;
    int blacklinkcount;
}Linkdata;
  

void reset(Board *b,Linkdata *ldata);
void addlink(Board *b,Linkdata *ldata,int r1,int r2,int c1,int c2,Player p);
int addpin(Board *b,Linkdata *ldata,int row,int col,Player p);
void print(Board *b);
int validpin(Board *b,int row,int col);


#endif