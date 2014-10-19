#include <stdio.h>
#include "answer06.h"

void * recursive(char * * maze, int w, int h, int x, int y)
{
if (maze[x + 1][y] = ' ' &&  x < w - 1 && x >= 0)
{
printf("S %d",1); 
recursive(maze, w, h, x + 1, y); 
printf("N %d",1);
}
else if (maze[x - 1][y] = ' ' && x < w - 1 && x >= 0)
{
printf("N %d",1);
recursive(maze, w, h, x - 1, y);
printf("S %d",1); 
}
else if (maze[x][y + 1] = ' ' && y < h - 1 && y >= 0)
{
printf("E %d",1);
recursive(maze, w, h, x, y + 1);
printf("W %d",1);
}
else (maze[x][y - 1] = ' ' && y < h - 1 && y >= 0)
{
printf("W %d",1);
recursive(maze, w, h, x, y - 1);
printf("E %d",1);
}
return; 
}
int entrancepoint(char * * maze, int w, int h) 
{
int i = 0;
int j;
while (maze[0][i] != '\0')
{
if (maze[0][i] == ' ')
{
return i;
}
i++;
}
}
void print_directions(char * * maze, int w, int h)
{
int y = entrancepoint(maze, w, h);
int x = 0;
recursive(maze, w, h, x, y);
}
