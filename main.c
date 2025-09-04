#include <stdio.h>
#include "raylib.h"

/*
 *listen my people this is the design doc cause I am lazy

 we will have 3 difficulties, 3 menus, 5 soundtracks, some sprites or whatever

 Player moveset
 mouse movement
 2 attack buttons ( they can be binded maybe? )
 1 button for the slow down time move

 steps for how to get the results for the falling balls game
 we need a player
        Player characteristics
        a size 
        a color
        a special move that slows down time

        Enemy Balls
        a size
        a color
        possibly health

 Steps to make game
 1. make circle around cursor
 2. Spawn one enemy 
 3. make enemy collision change something
 4. when you click on the enemy it should disappear
 */

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 640
#define ENEMY_ARRAY_SIZE 10

struct Player {
        Vector2 pos;
        Color color;
        int special_counter, radius;
};

struct Enemy {
        Vector2 pos;
        Color color;
        int radius;
        bool is_active;
};

int main(void) {

        InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "falling balls, yah hear?");
        Vector2 enemyPos = { SCREEN_HEIGHT/2, SCREEN_WIDTH/2 };

        struct Player circle = {
                .pos = { 0, 0 } ,
                .color = GREEN,
                .special_counter = 0,
                .radius = 32
        };

        struct Enemy bad = {
                .pos = enemyPos,
                .color = RED,
                .radius = 64,
                .is_active = true
        };

        struct Enemy enemy_array[ENEMY_ARRAY_SIZE] = { 0 };
        for (int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
                enemy_array[i].pos.x =  0 ;
                enemy_array[i].pos.y =  0 ;
                enemy_array[i].color = DARKPURPLE;
                enemy_array[i].radius = 48;
                enemy_array[i].is_active = true;
        }

        while(!WindowShouldClose()) {
                int i = 0;

                for(i = 0; i < ENEMY_ARRAY_SIZE; i++) {
                        if (CheckCollisionCircles(circle.pos, circle.radius, enemy_array[i].pos, enemy_array[i].radius))  {
                                enemy_array[i].color = RED; 
                                enemy_array[i].is_active = false;
                        } else {
                                enemy_array[i].color = DARKPURPLE;
                        }
                }

                circle.pos = GetMousePosition();
                BeginDrawing();
                        DrawCircleV(circle.pos, 32, circle.color);
                        for(int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
                                if(enemy_array[i].is_active == true)
                                        DrawCircleV(bad.pos, 64, enemy_array[i].color);
                                }
                        ClearBackground(RAYWHITE);
                        DrawText("LET ME TELL YOU HOW YOU MUST CLICK!!!!", 190, 200, 20, BLACK);
                EndDrawing();
        }

        CloseWindow();

        printf("yah balls");

}

