#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <math.h>


#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#endif // HEADERS_H_INCLUDED
#define TRUE 1
#define FALSE 0
#define FPS 60
#define FRAME_TIME (1000/FPS)
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 680

struct ball{
    int x;
    int y;
    int width;
    int height;
    int cent_x;
    int cent_y;
    int vel_x;
    int vel_y;
}ball;

struct paddle{
    int x;
    int y;
    int width;
    int height;
    int vel_x;
    int vel_y;
}paddle;

struct Tile{
    int x;
    int y;
    int cent_x;
    int cent_y;
    int width;
    int height;
    int visibility;
}all_tiles[100];

