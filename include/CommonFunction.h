#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H


#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <TextObj.h>

//biến xây dựng nên form window cho game
static SDL_Window* g_windows = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// Screen
const int FRAME_PER_SECOND = 60;  // fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;


#define BLANK_TILE 0

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_ITEM1 12
#define STATE_ITEM2 4
#define STATE_ITEM3 11
#define STATE_ITEM4 19

#define MIX_GAME 50

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};


namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); // xử lí va chạm bullet with threats
    int ShowMenu(SDL_Renderer* des, TTF_Font* font, Uint32 &time_menu);                       // Show
    int ShowExit(SDL_Renderer* des, TTF_Font* font, Uint32 scores_last, Uint32 high_scores);  // Show
    bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect & rect);     // Check hiệu ứng click
}

#endif // COMMONFUNCTION_H
