#include <stdio.h>
#include "raylib.h"

enum stage_state { ONE, TWO, THREE };
enum mode_state { STORY, ENDLESS };
enum menu_state { OPENING, MAIN_MENU, ENDING };

struct Entity {
        int x, y, radius;
        Color color;
        bool active;
};

#define NUM_OF_ENEMIES 1000

void OPEN_GAME(void);
void MAIN_MENU_GAME(void); 
void END_GAME(void);

void MAIN_GAME(int, struct Entity *, struct Entity *);
void MAIN_LEVEL_CHANGER(int, int, int);

int main(void) {

        //initializing global variables
        int screenHeight = 640;
        int screenWidth = 480;
        int score = 0;
        int specialMove = 2;
        int enemyCounter = 0;
        unsigned int framesCounter = 0;
        struct Entity player = { 0, 0, 25, RED, true};
        struct Entity enemy[NUM_OF_ENEMIES] = { 0, 0, 40, GREEN, false};
        int frame_dividend = 120;
        int frame_divisor = 2;

        //pointers i need
        struct Entity * pPlayer = &player;
        struct Entity * pEnemy = &enemy[0];
      
        //game states
        enum stage_state stage = ONE;
        enum mode_state mode = STORY;
        enum menu_state menu = MAIN_MENU;
        
        //spreading the enemies against the top of the screen
        for (int i = 0; i < NUM_OF_ENEMIES; i++) {
                enemy[i].x = GetRandomValue(0, screenHeight);
                enemy[i].y = 0;
                enemy[i].radius = 40;
                enemy[i].color = GREEN;
                enemy[i].active = false;
        }

        InitWindow(screenHeight, screenWidth, "falling balls");
        SetTargetFPS(60);

        while(!WindowShouldClose()) {

                //player position is the mouse position
                player.x = GetMouseX();
                player.y = GetMouseY();
                framesCounter++;

                MAIN_LEVEL_CHANGER(score, frame_dividend, frame_divisor);

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


                BeginDrawing();
                //draw state changes
                MAIN_GAME(score, &player, enemy);
                EndDrawing();
        }

        CloseWindow();

        printf("done\n");

}

void MAIN_GAME(int score, struct Entity * pEntity, struct Entity * eEntity[]) {

        ClearBackground(RAYWHITE);
        //text drawings
        DrawFPS(10, 25);
        DrawText(TextFormat("Score: %i", score), 10, 50, 15, BLACK); 
        DrawText(TextFormat("Frame Dividend: %i", score), 10, 75, 15, BLACK); 
        DrawText(TextFormat("Frame Divisor: %i", score), 10, 100, 15, BLACK); 
        //entity drawings
        DrawCircle(pEntity->x, pEntity->y, pEntity->radius, pEntity->color);
        for(int i = 0; i < NUM_OF_ENEMIES; i++) {
                        if (eEntity[i]->active == true) {
                                DrawCircle(eEntity[i]->x, eEntity[i]->y, eEntity[i]->radius, eEntity[i]->color);
                }
        }

}

void OPEN_GAME() {}
void MAIN_MENU_GAME() {}
void END_GAME() {}

void MAIN_LEVEL_CHANGER(int score, int frame_dividend, int frame_divisor) {

        switch(score) {

                case 10:
                        frame_dividend = 360;
                        frame_divisor = 60;
                        break;
                case 20:
                        frame_dividend = 300;
                        frame_divisor = 60;
                        break;
                case 30:
                        frame_dividend = 240;
                        frame_divisor = 60;
                        break;
                case 40:
                        frame_dividend = 180;
                        frame_divisor = 60;
                        break;
                case 50:
                        frame_dividend = 120;
                        frame_divisor = 60;
                        break;
                case 60:
                        frame_dividend = 60;
                        frame_divisor = 30;
                        break;
                case 70:
                        frame_dividend = 30;
                        frame_divisor = 15;
                        break;
                case 80:
                        frame_dividend = 14;
                        frame_divisor = 7;
                        break;
                case 90:
                        frame_dividend = 6;
                        frame_divisor = 3;
                        break;
                case 100:
                        frame_dividend = 2;
                        frame_divisor = 1;
                        break;
                default:
                        break;
        };
}
