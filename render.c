#include "headers.h"

void render(SDL_Window* window,SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_Texture* backg;
    backg = ret_tiletex(70,"background");
    //blit(renderer,backg,0,0,WINDOW_WIDTH - 100,WINDOW_HEIGHT - 100);
    SDL_Rect ball_in_game = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    //SDL_RenderFillRect(renderer,&ball_in_game);
    SDL_Rect paddle_in_game = {
        (int)paddle.x,
        (int)paddle.y,
        (int)paddle.width,
        (int)paddle.height
    };
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&paddle_in_game);
    render_tiles(renderer);
    render_ball(renderer);
    score_board(window,renderer);
    SDL_RenderPresent(renderer);
}

void render_tiles(SDL_Renderer* renderer){
    SDL_Texture* texture;
    for(int i=0;i<60;i++){
        texture = ret_tiletex(i,"tiles");
        blit(renderer,texture,all_tiles[i].x,all_tiles[i].y,all_tiles[i].width,all_tiles[i].height);
    }
}


void render_ball(SDL_Renderer* renderer){
    SDL_Texture* ballexture = NULL;
    ballexture = ret_tiletex(0,"ball");
    blit(renderer,ballexture,ball.x,ball.y,ball.width,ball.height);
}

void score_board(SDL_Window* window,SDL_Renderer* renderer){
    int score = 0;
    char fullstr[50] = "SCORE - ";
    SDL_Color color = {255,255,255,255};
    SDL_Surface *text_surface;
    TTF_Font *font;
    font = TTF_OpenFont("fonts/ariblk.ttf",24 );
    for(int i=0;i<60;i++){
        if(all_tiles[i].visibility != 0){
            score++;
        }
    }
    int length = snprintf(NULL,0,"%d",score);
    char str[length+1];
    snprintf(str,length+1,"%d",score);
    strcat(fullstr,str);
    text_surface = TTF_RenderText_Solid(font,fullstr,color);
    if(!(text_surface)) {
        printf("%s",SDL_GetError());
    } else {
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer,text_surface);
        blit(renderer,text,0,0,50,50);
        SDL_FreeSurface(text_surface);
    }

}



