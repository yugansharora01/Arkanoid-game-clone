#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <SDL_ttf.h>
#include <stdlib.h>


#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#endif // HEADERS_H_INCLUDED


struct gameobjects{
    int x;
    int y;
    int width;
    int height;
    int cent_x;
    int cent_y;
    int vel_x;
    int vel_y;
};

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
    int width;
    int height;
    int visibility;
}all_tiles[100];

