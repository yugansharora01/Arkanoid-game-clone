#include "headers.h"


SDL_Texture* loadtexture(SDL_Renderer* renderer,char *filename){
    SDL_Texture* imgtexture;
    imgtexture = IMG_LoadTexture(renderer,filename);
    return imgtexture;
}
void blit(SDL_Renderer* renderer,SDL_Texture* texture,int x,int y,int w,int h){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_QueryTexture(texture,NULL,NULL,&dest.w,&dest.h);
    SDL_RenderCopy(renderer,texture,NULL,&dest);
}
