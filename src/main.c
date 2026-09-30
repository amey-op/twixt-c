/*
    Make File is made!
    make
    make run
    make clean
*/

#include<stdio.h>
#include"board.h"
#include"game.h"
#include<stdlib.h>
#include<string.h>

int main()
{
    Board b;
    Linkdata ldata;
    reset(&b,&ldata);
    Player current=RED;
    char command[20],command2[20];

    int r,c;
    printf("Welcome to Twixt!!!!\n");
    help();

    while(1)
    {
        printf("\n%s --> ",current==RED?"RED":"BLACK");
        scanf("%s",command);
        
        if(strcmp(command,"place")==0)
        {
            if(scanf("%d %d",&r,&c)!=2)
            {
                printf("Invalid command!! Please Try Again!\n");
                continue;
            }

            if(addpin(&b,&ldata,r,c,current))
            {
                print(&b);
                if(checkwin2(&b,&ldata,current))
                {
                    printf("%s Player Wins!! Congratulations!\n",current==RED?"RED":"BLACK");
                    reset(&b,&ldata);
                    continue;
                }
                playerswitch(&current);
            }
        }
        else if(strcmp(command,"view")==0)
        {
            scanf("%s",command2);

            if(strcmp(command2,"board")==0)
            {
                print(&b);
            }
            else if(strcmp(command2,"guide")==0)
            {
                help();
            }
            else if(strcmp(command2,"links")==0)
            {
                printf("------RED LINKS------\n");
                for(int i=0;i<ldata.redlinkcount;i++)
                {
                    Link l=ldata.redlinks[i];
                    printf("(%d,%d)<-->(%d,%d)\n",l.r1,l.c1,l.r2,l.c2);
                }
                printf("\n");
                printf("-----BLACK LINKS-----\n");
                for(int i=0;i<ldata.blacklinkcount;i++)
                {
                    Link l=ldata.blacklinks[i];
                    printf("(%d,%d)<-->(%d,%d)\n",l.r1,l.c1,l.r2,l.c2);
                }
                printf("\n");
            }
            else
            {
                printf("Invalid command!! Please Try Again!\n");
            }
        }
        else if(strcmp(command,"reset")==0)
        {
            reset(&b,&ldata);
            current=RED;
            printf("Game Restarted, Red Starts first!\n");
            print(&b);
        }
        else if(strcmp(command,"exit")==0)
        {
            printf("Thanks for playing twixst!! Have a nice day ahead!!\n");
            break;
        }
        else
        {
            printf("Invalid command!! Please Try Again!\n");
        }
    }

}