#include "start.h"

int last_frame_time_start = 0;
SDL_Rect outline;

int startingnow(SDL_Renderer* renderer){
    int start = 0,is_running = 0;
    while(!start){
        start_processinput(&start,&is_running);
        start_update();
        start_render(renderer);
    }
    return is_running;
}

void start_processinput(int *start,int *is_running){
    int x,y;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            *start = 1;
            *is_running = 1;
            //SDL_Quit();
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);;
            *start = mouse_key_pressed(x,y);
            break;
        case SDL_KEYDOWN:
            break;
        default:
            //printf("Unhandled Event!\n");
            break;
    }

}
int mouse_key_pressed(int x,int y){
    if(x<outline.x+outline.w&&x>outline.x&&y<outline.y+outline.h&&y>outline.y){
        return 1;
    }
    return 0;
}
void start_update(){
    int time_to_wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time_start);
    if(time_to_wait>0){
        SDL_Delay(time_to_wait);
    }
    last_frame_time_start = SDL_GetTicks();
}
void start_render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    outline.w = 150;
    outline.h = 75;
    outline.x = (WINDOW_WIDTH/2) - (outline.w/2);
    outline.y = (WINDOW_HEIGHT/2) - (outline.h/2);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer,&outline);
    SDL_Color color = {255,255,255,255};
    SDL_Surface *text_surface;
    TTF_Font *font;
    SDL_Rect start_button ={
        outline.x + 10,
        outline.y + 10,
        outline.w - 20,
        outline.h - 20
    };
    font = TTF_OpenFont("fonts/ariblk.ttf",34);
    text_surface = TTF_RenderText_Solid(font,"START",color);
    if(!(text_surface)) {
        printf("%s",SDL_GetError());
    } else {
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer,text_surface);
        blit(renderer,text,start_button.x,start_button.y,start_button.w,start_button.h);
        SDL_FreeSurface(text_surface);
    }

    SDL_RenderPresent(renderer);
}

