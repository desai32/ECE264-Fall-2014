#include <stdio.h>
#include "answer06.h"
int entrancepoint(char * *, int, int);
void recursive(char * *, int, int, int, int);
void recursive(char * * maze, int w, int h, int x, int y)
{
int i;
for (i = 0; i < 4; i++)
{
if (x - 1 >= 0 && x < h -1 && maze[x + 1][y] == ' ' && i == 0)
{
maze[x][y] = '.';
printf("S 1\n"); 
recursive(maze, w, h, x + 1, y);
maze[x][y] = ' '; 
printf("N 1\n");
}
if (x - 1 >= 0 && x < h - 1 && maze[x - 1][y] == ' ' && i == 1)
{
maze[x][y] = '.';
printf("N 1\n");
recursive(maze, w, h, x - 1, y);
maze[x][y] = ' ';
printf("S 1\n"); 
}
if (y -1  >= 0 && y < w - 1 && maze[x][y + 1] == ' ' && i == 2)
{
maze[x][y] = '.';
printf("E 1\n");
recursive(maze, w, h, x, y + 1);
maze[x][y] = ' ';
printf("W 1\n");
}
if (y - 1 >= 0 && y < w - 1 && maze[x][y - 1] == ' ' && i == 3)
{
maze[x][y] = '.';
printf("W 1\n");
recursive(maze, w, h, x, y - 1);
maze[x][y] = ' ';
printf("E 1\n");
}
}
return; 
}
int entrancepoint(char * * maze, int w, int h) 
{
int i;
for (i = 0; i < h; i++)
{
if (maze[0][i] == ' ')
{
return i;
}
}
return 0;
}
void print_directions(char * * maze, int w, int h)
{
int y = entrancepoint(maze, w, h);
int x = 0;
recursive(maze, w, h, x, y);
return;
}
