#include <stdio.h>
#include "raylib.h"

struct entity {
        int x, y, radius;
        Color color;
        bool active;
};

int main(void) {

        //initializing global variables
        int screenHeight = 640;
        int screenWidth = 480;
        int score = 0;
        int specialMove = 2;
        struct entity Player = { 0, 0, 25, RED, true };
        struct entity Enemy = { 0, 0, 40, GREEN, true};

        InitWindow(screenHeight, screenWidth, "falling balls");

        while(!WindowShouldClose()) {
                Player.x = GetMouseX();
                Player.y = GetMouseY();
                Enemy.x = 200;
                Enemy.y = 200;

                if (CheckCollisionCircles((Vector2){Player.x, Player.y}, Player.radius, (Vector2){Enemy.x, Enemy.y}, Enemy.radius)) {
                        Enemy.color = DARKPURPLE;
                        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                Enemy.active = false;
                                score += 1;
                        }
                }



                BeginDrawing();
                        ClearBackground(RAYWHITE);
                        DrawFPS(10, 25);
                        DrawText(TextFormat("Score: %i", score), 10, 50, 15, BLACK); 
                        DrawText("falling balls",
                                        190,
                                        200,
                                        20,
                                        BLACK);
                        DrawCircle(Player.x, Player.y, Player.radius, Player.color);
                        if (Enemy.active == true) {
                                DrawCircle(Enemy.x, Enemy.y, Enemy.radius, Enemy.color);
                }
                EndDrawing();
        }

        CloseWindow();

        printf("done\n");

}

