#include "headers.h"

struct ball_points{
    int bottom_x;
    int bottom_y;
    int top_x;
    int top_y;
    int left_x;
    int left_y;
    int right_x;
    int right_y;
}ball_points;

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

void collision_with_tiles(){
    int ball_point,tile_centre,x1,y1,L,dist;
    ball.cent_x = ball.x + ball.width/2;
    ball.cent_y = ball.y + ball.height/2;
    ball_points.bottom_x = ball.x + ball.width/2;
    ball_points.bottom_y = ball.y + ball.height;
    ball_points.top_x = ball.x + ball.width/2;
    ball_points.top_y = ball.y;
    ball_points.left_x = ball.x;
    ball_points.left_y = ball.y + ball.height/2;
    ball_points.right_x = ball.x + ball.width;
    ball_points.right_y = ball.y + ball.height/2;
    for(int i=0;i<60;i++){
        if(all_tiles[i].visibility != 0){
            if(all_tiles[i].visibility <= 3){
                all_tiles[i].visibility++;
            }
        }else{
            if(ball_points.top_x >= all_tiles[i].x && ball_points.top_x <= all_tiles[i].x + all_tiles[i].width){//for bottom collision
                if(ball_points.top_y > all_tiles[i].y && ball_points.top_y <= all_tiles[i].y + all_tiles[i].height){
                    ball.vel_y = -ball.vel_y;
                    all_tiles[i].visibility = 1;
                }
            }else{
                if(ball_points.bottom_y >= all_tiles[i].y && ball_points.bottom_y < all_tiles[i].y + all_tiles[i].height){//for top collision
                    if(i==12)printf("kkkk");
                    if(ball_points.bottom_x <= all_tiles[i].x + all_tiles[i].width){
                        printf("\nball_points.bottom_x:%d,i:%d,all_tiles[i].x:%d,all_tiles[12].x:%d",ball_points.bottom_x,i,all_tiles[i].x,all_tiles[12].x);
                        printf("\nball_points.bottom_y:%d,%d",ball_points.bottom_y,all_tiles[12].y);
                        if(ball_points.bottom_x >= all_tiles[i].x){
                        ball.vel_y = -ball.vel_y;
                        all_tiles[i].visibility = 1;
                        printf("\n from up ");
                    }
                    }

                }else{
                    if(ball_points.left_x > all_tiles[i].x && ball_points.left_x <= all_tiles[i].x + all_tiles[i].width){//for right collision
                        if(ball_points.left_y >= all_tiles[i].y && ball_points.left_y <= all_tiles[i].y +all_tiles[i].height){
                            ball.vel_x = -ball.vel_x;
                            all_tiles[i].visibility = 1;
                        }
                    }else{
                        if(ball_points.right_x >= all_tiles[i].x && ball_points.right_x < all_tiles[i].x + all_tiles[i].width){//for left collision
                            if(ball_points.right_y >= all_tiles[i].y && ball_points.right_y <= all_tiles[i].y +all_tiles[i].height){
                                ball.vel_x = -ball.vel_x;
                                all_tiles[i].visibility = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}


void update(void){
    int time_to_wait = FRAME_TIME - (SDL_GetTicks() - last_frame_time);
    int collide_down = 0,collide_side = 0;
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
    collision_with_tiles();
    /*for(int i=0;i<60;i++){
        if(all_tiles[i].visibility != 0){
            if(all_tiles[i].visibility <= 3){
                all_tiles[i].visibility++;
            }
        }else{
            if(all_tiles[i].y + all_tiles[i].height >= ball.y && all_tiles[i].y <= ball.y){
                if(all_tiles[i].x + all_tiles[i].width >= ball.x && all_tiles[i].x + all_tiles[i].width <= ball.x + 3 || all_tiles[i].x <= ball.x + ball.width && all_tiles[i].x >= ball.x + ball.width - 3){
                    collide_side = 1;
                    all_tiles[i].visibility = 1;
                    break;
                }else{
                    if(all_tiles[i].x <= ball.x + ball.width && all_tiles[i].x + all_tiles[i].width >= ball.x){
                        collide_down = 1;
                        all_tiles[i].visibility = 1;
                        break;
                    }
                }
            }else{
                if(all_tiles[i].y <= ball.y + ball.height && all_tiles[i].y + all_tiles[i].height >= ball.y){
                    if(all_tiles[i].x <= ball.x + ball.width && all_tiles[i].x + all_tiles[i].width >= ball.x){
                        collide_down = 1;
                        all_tiles[i].visibility = 1;
                        break;
                    }
                }
            }
        }
    }*/
    if(collide_down == 1){
        ball.vel_y = -ball.vel_y;
    }
    if(collide_side == 1){
        ball.vel_x = -ball.vel_x;
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
    int score = 1,is_end = 0;
    is_end = startingnow(renderer);
    if(is_end){
        game_is_running = 0;
    }
    setup(renderer);
    while(game_is_running){
        process_input();
        update();
        render(window,renderer);
    }
    destroy_window();
    return 0;
}
