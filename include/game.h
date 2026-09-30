#ifndef GAME_H
#define GAME_H
#include "board.h"

void help();
int orientation(int x1, int y1, int x2, int y2,int x3, int y3);
int segintersect(Link A,Link B);
int validlink(Board *b,Linkdata *ldata,int r1,int r2,int c1,int c2,Player p);
int linkexist(Linkdata *ldata,Player p,int r1,int c1,int r2,int c2);
void checkwin1(Board *b,Linkdata *ldata,int row,int col,Player p);
void playerswitch(Player *p);
int checkwin2(Board *b,Linkdata *ldata,Player p);

#endif