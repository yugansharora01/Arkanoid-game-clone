#include "headers.h"

#define TRUE 1
#define FALSE 0
#define FPS 60
#define FRAME_TIME (1000/FPS)
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 680

int game_is_running = 0;
SDL_Window* window;
SDL_Renderer* renderer;
int last_frame_time = 0;

//struct gameobjects ball,paddle;


int initialise_game(){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        fprintf(stderr,"error in initialising SDL\n");
        return FALSE;
    }
    window = SDL_CreateWindow("new",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if(!window){
        fprintf(stderr,"error in creating window\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        fprintf(stderr,"error in creating renderer\n");
        return FALSE;
    }
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags)&imgFlags)){
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return FALSE;
    }
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    return TRUE;
}

void keydown(SDL_Event *event){
    switch(event->key.keysym.sym){
        case SDLK_RIGHT:
            paddle.vel_x = 0;
            paddle.vel_x += 20;
            break;
        case SDLK_LEFT:
            paddle.vel_x = 0;
            paddle.vel_x -= 20;
            break;
        case SDLK_UP:
            printf("lol, %d , %d \n",ball.x,ball.y);
            break;
        case SDLK_ESCAPE:
            game_is_running = 0;
            break;
    }
}

void process_input(void){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            game_is_running = 0;
        case SDL_MOUSEMOTION:
            break;
        case SDL_KEYDOWN:
            keydown(&event);
            break;
        default:
            //printf("Unhandled Event!\n");
            break;
    }
}

void update(void){
    int time_to_wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time);
    int collide = 0;
    //printf("%i   %i\n",SDL_GetTicks(),time_to_wait);
    if(time_to_wait>0){
        SDL_Delay(time_to_wait);
    }
    last_frame_time = SDL_GetTicks();
    //collision of ball with wall
    if(ball.x >= (WINDOW_WIDTH - ball.width)||ball.x <= 0){
        ball.vel_x = -ball.vel_x;
    }
    if(ball.y <= 0){
        ball.vel_y = -ball.vel_y;
    }
    //collision of ball with paddle
    if(ball.x + ball.width >= paddle.x && ball.x <= paddle.x + paddle.width){
        if(ball.y+ball.height==paddle.y||ball.y+ball.height+1==paddle.y){
            ball.vel_y = -ball.vel_y;
        }
    }
    //collision of paddle with wall
    if(paddle.x + paddle.width >= WINDOW_WIDTH||paddle.x <= 0){
        //for left side
        if(paddle.x <= 0){
            paddle.x++;
        }else //for right side
        paddle.x--;
        paddle.vel_x = 0;
    }
    //collision with tiles
    for(int i=0;i<60;i++){
        if(all_tiles[i].visibility != 0){
            if(all_tiles[i].visibility <= 3){
                all_tiles[i].visibility++;
            }
        }else{
            if(all_tiles[i].y + all_tiles[i].height >=ball.y && all_tiles[i].y <= ball.y){
                if(all_tiles[i].x <= ball.x + ball.width && all_tiles[i].x + all_tiles[i].width >= ball.x){
                    collide = 1;
                    all_tiles[i].visibility = 1;

                }
            }
        }
    }
    if(collide == 1){
        ball.vel_y = -ball.vel_y;
    }
    //After losing making y-cordinate 0
    if(ball.y >= WINDOW_HEIGHT - ball.height){
        printf("\nyou lost\ntry again");
        ball.y = 0;
    }
    //UPDATING THE COORDINATES
    ball.x += ball.vel_x;
    ball.y += ball.vel_y;
    ball.cent_x = ball.x + (ball.width+1)/2;
    ball.cent_y = ball.y + (ball.height+1)/2;
    if(paddle.vel_x > 0){
        paddle.x += 3;
        paddle.vel_x -= 2;
    }
    if(paddle.vel_x < 0){
        paddle.x -= 3;
        paddle.vel_x +=2;
    }

    //printf("ball.x:%i, ball.y\n",ball.x);
}



void destroy_window(void){
    destroy_tiles();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc,char* argv[]){
    game_is_running = initialise_game();
    int score = 1;
    setup(renderer);
    while(game_is_running){
        process_input();
        update();
        render(window,renderer);
    }
    destroy_window();
    return 0;
}
