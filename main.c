#include <stdio.h>
#include "raylib.h"

enum mode_state { STORY, ENDLESS };
enum menu_state { OPENING, MAIN_MENU, GAME, ENDING };
enum main_levels { ONE, TWO, THREE, FOUR, FIVE };
enum floaty { UP, DOWN };

struct Entity {
        int x, y, radius;
        Color init_color;
        Color color;
        bool active;
};

#define NUM_OF_ENEMIES 1000

//all my draw calls which I'll instill in a function pointer
//opening sequence
void OPEN_GAME(Texture2D, int *, int *, struct Entity *, struct Entity *);
//main menu
void MAIN_MENU_GAME(void); 
//win or lose screen
void END_GAME(void);
//main game drawing stuff
void MAIN_GAME(int, int, int, struct Entity *, struct Entity *);

//the two modes
void MAIN_LEVEL_CHANGER(int, int *, int *);
void ENDLESS_LEVEL_CHANGER(int, int *, int *);

//initializing global variables
int screenHeight = 640;
int screenWidth = 480;
int score = 30;
int specialMove = 2;
int enemyCounter = 0;
unsigned int framesCounter = 0;
struct Entity player = { 0, 0, 25, RED, YELLOW, true};
struct Entity enemy[NUM_OF_ENEMIES] = { 0, 0, 40, GREEN, BLUE, false};
int frame_dividend = 14;
int frame_divisor = 7;

int bounce_counter = 0;

int game_banner_x = 100;
int game_banner_y = 100;
//the rainbow
Color rainbow[21] = { LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
        SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN };

int main(void) {
         
        //pointers i need
        struct Entity * pPlayer = &player;
        struct Entity * pEnemy = &enemy[0];
        int * pfdividend = &frame_dividend;
        int * pfdivisor = &frame_divisor;
      
        //game states
        enum mode_state mode = STORY;
        enum menu_state menu = OPENING;
        enum floaty bounce = UP;
        
        //spreading the enemies against the top of the screen
        for (int i = 0; i < NUM_OF_ENEMIES; i++) {
                enemy[i].x = GetRandomValue(0, screenHeight);
                enemy[i].y = 0;
                enemy[i].radius = 40;
                enemy[i].init_color = rainbow[GetRandomValue(0, 21)];
                enemy[i].color = enemy[i].init_color;
                enemy[i].active = false;
        }

        InitWindow(screenHeight, screenWidth, "falling balls");
        SetTargetFPS(60);

        Texture2D game_banner = LoadTexture("falling_circles_game_banner.png");
        Rectangle collision_of_the_vision = { 100, 100, game_banner.width, game_banner.height };
        const float original_height = game_banner.height;
        const float original_width = game_banner.width;
        const float half_height = original_height / 2;
        const float half_width = original_width / 2;

        // const float original_height = game_banner.height;
        // const float original_width = game_banner.width;
        // const float half_height = original_height / 2;
        // const float half_width = original_width / 2;
        while(!WindowShouldClose()) {

                //player position is the mouse position
                player.x = GetMouseX();
                player.y = GetMouseY();
                framesCounter++;

                switch(menu) {

                        case OPENING:

                                //go to next screen logic
                                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                        menu = GAME;
                                        }

                                if( bounce == DOWN ) {
                                       game_banner_y += 1;               
                                       bounce_counter++;
                                        if (bounce_counter == 64)
{                                               bounce_counter = 0;
                                                bounce = UP;
}                                } else if ( bounce == UP ) {
{                                       game_banner_y -= 1;
                                       bounce_counter++;
}                                        if (bounce_counter == 64)
{                                                bounce_counter = 0;
                                                bounce = DOWN;
}                                }

                                //old floaty squeezy
                                // if(CheckCollisionCircleRec((Vector2){player.x, player.y}, player.radius, collision_of_the_vision)) {
                                //                     game_banner.height += 1; game_banner.width += 1;    
                                //                     // game_banner_x += 1; game_banner_y += 1;    
                                //         } else if( game_banner.height != original_height) {
                                //                     game_banner.height -= 1; game_banner.width -= 1;    
                                //                     // game_banner_x -= 1; game_banner_y -= 1;    
                                //         }

                                //every we manipulate this with a switch statement
                                if (((framesCounter/frame_dividend)%frame_divisor) == 1) {
                                        enemy[enemyCounter].active = true;
                                        enemyCounter += 1;
                                        framesCounter = 0;
                                }

                                //make the circles fall in the OP
                                for(int i = 0; i < NUM_OF_ENEMIES; i++) {
                                        if (enemy[i].active == true) {
                                                enemy[i].y += 1;
                                                //if i is divisible by 2 change the dir of the falling circles in the intro
                                                if (i % 2 == 0) {
                                                        enemy[i].x -= 1;
                                                } else {
                                                        enemy[i].x += 1;
                                                }
                                        //if the player and the enemy collide
                                        if (CheckCollisionCircles((Vector2){player.x, player.y}, player.radius, (Vector2){enemy[i].x, enemy[i].y}, enemy[i].radius)) {
                                                enemy[i].color = BLUE;
                                                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                                        enemy[i].active = false;
                                                        score += 1;
                                                                }
                                        } else {
                                                enemy[i].color = enemy[i].init_color;
                                        }
                                        }
                                }

                                break;
                        case MAIN_MENU:
                                break;
                        case GAME:
                                MAIN_LEVEL_CHANGER(score, pfdividend, pfdivisor);

                                //every we manipulate this with a switch statement
                                if (((framesCounter/frame_dividend)%frame_divisor) == 1) {
                                        enemy[enemyCounter].active = true;
                                        enemyCounter += 1;
                                        framesCounter = 0;
                                }

                                for(int i = 0; i < NUM_OF_ENEMIES; i++) {
                                        if (enemy[i].active == true) {
                                                enemy[i].y += 1;
                                        //if the player and the enemy collide
                                        if (CheckCollisionCircles((Vector2){player.x, player.y}, player.radius, (Vector2){enemy[i].x, enemy[i].y}, enemy[i].radius)) {
                                                enemy[i].color = DARKPURPLE;
                                                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                                        enemy[i].active = false;
                                                        score += 1;
                                                                }
                                        }
                                        }
                                }
                        case ENDING:
                                break;
                }


                BeginDrawing();
                //draw state changes
                switch (menu) {
                        case OPENING:
                                OPEN_GAME(game_banner, &game_banner_x, &game_banner_y, &player, enemy);
                                break;
                        case MAIN_MENU:
                                break;
                        case GAME:
                                MAIN_GAME(score, frame_dividend, frame_divisor, &player, enemy);
                                break;
                        case ENDING:
                                break;
                };

                EndDrawing();
        }

        CloseWindow();

        printf("done\n");

}

void MAIN_GAME(int score, int frame_dividend, int frame_divisor, struct Entity * pEntity, struct Entity eEntity[]) {

        ClearBackground(RAYWHITE);
        //text drawings
        DrawFPS(10, 25);
        DrawText(TextFormat("Score: %i", score), 10, 50, 15, BLACK); 
        DrawText(TextFormat("Frame Dividend: %i", frame_dividend), 10, 75, 15, BLACK); 
        DrawText(TextFormat("Frame Divisor: %i", frame_divisor), 10, 100, 15, BLACK); 
        //entity drawings
        DrawCircle(pEntity->x, pEntity->y, pEntity->radius, pEntity->color);
        for(int i = 0; i < NUM_OF_ENEMIES; i++) {
                        if (eEntity[i].active == true) {
                                DrawCircle(eEntity[i].x, eEntity[i].y, eEntity[i].radius, eEntity[i].color);
                }
        }
}

void OPEN_GAME(Texture2D texture, int * textureX, int * textureY,  struct Entity * pEntity, struct Entity eEntity[]) {
        ClearBackground(BLACK);
        texture.height *= 2.0f;
        texture.width *= 2.0f;

        //entity drawings
        DrawCircle(pEntity->x, pEntity->y, pEntity->radius, pEntity->color);
        for(int i = 0; i < NUM_OF_ENEMIES; i++) {
                        if (eEntity[i].active == true) {
                                DrawCircle(eEntity[i].x, eEntity[i].y, eEntity[i].radius, eEntity[i].color);
                }
        }
        DrawRectangle(100, 100, 128, 60, GREEN); 
        DrawTexture(texture, *textureX, *textureY, WHITE);
}
void MAIN_MENU_GAME() {}
void END_GAME() {}

void MAIN_LEVEL_CHANGER(int score, int * frame_dividend, int * frame_divisor) {

        switch(score) {

                case 0:
                        *frame_dividend = 360;
                        *frame_divisor = 60;
                        break;
                case 10:
                        *frame_dividend = 300;
                        *frame_divisor = 60;
                        break;
                case 20:
                        *frame_dividend = 240;
                        *frame_divisor = 60;
                        break;
                case 30:
                        *frame_dividend = 180;
                        *frame_divisor = 60;
                        break;
                case 40:
                        *frame_dividend = 120;
                        *frame_divisor = 60;
                        break;
                case 50:
                        *frame_dividend = 60;
                        *frame_divisor = 30;
                        break;
                case 60:
                        *frame_dividend = 30;
                        *frame_divisor = 15;
                        break;
                case 70:
                        *frame_dividend = 14;
                        *frame_divisor = 7;
                        break;
                case 80:
                        *frame_dividend = 6;
                        *frame_divisor = 3;
                        break;
                case 90:
                        *frame_dividend = 2;
                        *frame_divisor = 1;
                        break;
                default:
                        break;
        };
}


