#include "setup.h"

SDL_Texture* bluetexture = NULL;
SDL_Texture* redtexture = NULL;
SDL_Texture* pinktexture = NULL;
SDL_Texture* browntexture = NULL;
SDL_Texture* cyantexture = NULL;
SDL_Texture* greentexture = NULL;
SDL_Texture* limetexture = NULL;
SDL_Texture* orangetexture = NULL;
SDL_Texture* whitetexture = NULL;
SDL_Texture* yellowtexture = NULL;
SDL_Texture* notexture = NULL;
SDL_Texture* background = NULL;
SDL_Texture* balltex = NULL;
SDL_Texture* loadtexture(SDL_Renderer* renderer,char *filename);


void setup(SDL_Renderer *renderer){
    //the width and height of ball should be an add number
    paddle.width = 75;
    paddle.height = 15;
    paddle.x = WINDOW_WIDTH/2 - paddle.width/2;
    paddle.y = WINDOW_HEIGHT - 50;

    ball.width = 15;
    ball.height = 15;
    ball.x = paddle.x + paddle.width/2;
    ball.y = paddle.y - ball.height;
    //ball.x = 180;
    //ball.y = 0;
    ball.cent_x = ball.x + (ball.width+1)/2;
    ball.cent_y = ball.y + (ball.height+1)/2;
    ball.vel_x = 2;
    ball.vel_y = 2;

    tile_setup();

    for(int i=0;i<60;i++){
        all_tiles[i].height = 20;
        all_tiles[i].width = 70;
        all_tiles[i].cent_x = all_tiles[i].x + all_tiles[i].width;
        all_tiles[i].cent_y = all_tiles[i].y + all_tiles[i].height;
    }


    setup_tiletex(renderer);

}

void tile_setup(){
    int i=0,j,k=0;
    all_tiles[0].x = 20;
    all_tiles[0].y = 50;
    all_tiles[0].visibility = 0;
    for(j=0;j<10;j++){
        for(i=k;i<k+6;i++){
            all_tiles[i+1].y = all_tiles[i].y + 25;
            all_tiles[i+1].x = all_tiles[i].x;
            all_tiles[i+1].visibility = 0;
        }
        all_tiles[i].x = all_tiles[i-6].x +75;
        all_tiles[i].y = 50;
        k=k+6;
    }
}

void setup_tiletex(SDL_Renderer *renderer){
    bluetexture = loadtexture(renderer,"images/bluetile.png");
    redtexture = loadtexture(renderer,"images/redtile.png");
    pinktexture = loadtexture(renderer,"images/pinktile.png");
    browntexture = loadtexture(renderer,"images/browntile.png");
    cyantexture = loadtexture(renderer,"images/cyantile.png");
    greentexture = loadtexture(renderer,"images/greentile.png");
    limetexture = loadtexture(renderer,"images/limetile.png");
    orangetexture = loadtexture(renderer,"images/orangetile.png");
    whitetexture = loadtexture(renderer,"images/whitetile.png");
    yellowtexture = loadtexture(renderer,"images/yellowtile.png");
    notexture = loadtexture(renderer,"images/notile.png");
    background = loadtexture(renderer,"images/back1.png");
    balltex = loadtexture(renderer,"images/ball1.png");
}

SDL_Texture* ret_tiletex(int i,char *str){
    SDL_Texture* tex;
    int ch = i/6;
    if(all_tiles[i].visibility!=0){
        ch = 10;
    }
    if(strcmpi(str,"ball")==0){
        tex = balltex;
        return tex;
    }
    switch(ch){
        case 0:
            tex = bluetexture;
            break;
        case 1:
            tex = redtexture;
            break;
        case 2:
            tex = pinktexture;
            break;
        case 3:
            tex = cyantexture;
            break;
        case 4:
            tex = limetexture;
            break;
        case 5:
            tex = orangetexture;
            break;
        case 6:
            tex = greentexture;
            break;
        case 7:
            tex = whitetexture;
            break;
        case 8:
            tex = yellowtexture;
            break;
        case 9:
            tex = browntexture;
            break;
        case 10:
            tex = notexture;
            break;
        case 11:
            tex = background;
            break;
        default:
            tex = bluetexture;
            break;

    }
    return tex;
    SDL_DestroyTexture(tex);
}


void destroy_tiles(){
    SDL_DestroyTexture(bluetexture);
    SDL_DestroyTexture(pinktexture);
    SDL_DestroyTexture(redtexture);
    SDL_DestroyTexture(cyantexture);
    SDL_DestroyTexture(limetexture);
    SDL_DestroyTexture(greentexture);
    SDL_DestroyTexture(whitetexture);
    SDL_DestroyTexture(yellowtexture);
    SDL_DestroyTexture(browntexture);
    SDL_DestroyTexture(orangetexture);
    SDL_DestroyTexture(notexture);
}
