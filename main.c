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
        int enemyCounter = 0;
        unsigned int framesCounter = 0;
        struct entity Player = { 0, 0, 25, RED, true};
        struct entity Enemy[10] = { 0, 0, 40, GREEN, false};
        
        //spreading the enemies against the top of the screen
        for (int i = 0; i < 10; i++) {
                Enemy[i].x = GetRandomValue(0, screenHeight);
                printf("%d", Enemy[i].x);
        }

        InitWindow(screenHeight, screenWidth, "falling balls");
        SetTargetFPS(60);

        while(!WindowShouldClose()) {

                //player position is the mouse position
                Player.x = GetMouseX();
                Player.y = GetMouseY();
                framesCounter++;

                //every 5 seconds summon an enemy
                if (((framesCounter/300)%5) == 1) {
                        Enemy[enemyCounter].active = true;
                        enemyCounter += 1;
                        framesCounter = 0;
                }
                        

                for(int i = 0; i < 10; i++) {
                        if (Enemy[i].active == true) {
                                Enemy[i].y += 1;
                        //if the player and the enemy collide
                        if (CheckCollisionCircles((Vector2){Player.x, Player.y}, Player.radius, (Vector2){Enemy[i].x, Enemy[i].y}, Enemy[i].radius)) {
                                Enemy[i].color = DARKPURPLE;
                                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                        Enemy[i].active = false;
                                        score += 1;
                                }
                        }
                        }
                }


                BeginDrawing();
                        ClearBackground(RAYWHITE);
                        //text drawings
                        DrawFPS(10, 25);
                        DrawText(TextFormat("Score: %i", score), 10, 50, 15, BLACK); 
                        //entity drawings
                        DrawCircle(Player.x, Player.y, Player.radius, Player.color);
                        for(int i = 0; i < 10; i++) {
                                        if (Enemy[i].active == true) {
                                                DrawCircle(Enemy[i].x, Enemy[i].y, Enemy[i].radius, Enemy[i].color);
                                }
                        }
                EndDrawing();
        }

        CloseWindow();

        printf("done\n");

}

