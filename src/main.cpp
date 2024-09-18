#include "raylib.h"
#include <iostream>
#include <cmath>

using namespace std;

Color Green = Color{38, 185, 154, 255}; // Not using Transparency so alpha is 255
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};

int PlayerScore = 0;
int CpuScore = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, yellow);
    }
    void Move()
    {
        static float delayTimer = 0.0f; // 1-second delay after reset
        static bool resetDone = false;

        if (resetDone)
        {
            delayTimer -= GetFrameTime();
            if (delayTimer <= 0.0f)
            {
                resetDone = false;
            }
        }
        else
        {

            x += speed_x;
            y += speed_y;

            if (y + radius >= GetScreenHeight() || y - radius <= 0)
            {
                speed_y *= -1;
            }
            if (x + radius >= GetScreenWidth()) // Computer wins
            {
                CpuScore++;
                speed_x *= -1;
                Reset();
                resetDone = true;
                delayTimer = 1.0f; // start delay timer
            }
            if (x - radius <= 0) // PlayerWins
            {
                PlayerScore++;
                speed_x *= -1;
                Reset();
                resetDone = true;
                delayTimer = 1.0f; // start delay timer
            }
        }
    }
    void Reset()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[] = {1, -1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    int speed;
    float width, height;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed; // To move the paddle up
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed; // To move the paddle down
        }

        LimitMovement();
    }
    void Move2()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= speed; // To move the paddle up
        }
        if (IsKeyDown(KEY_S))
        {
            y += speed; // To move the paddle down
        }

        LimitMovement();
    }
};

class CpuPaddle : public Paddle
{
public:
    void Move(int ball_y)
    {
        if (y + height / 2 < ball_y)
        {
            y += speed;
        }
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle player1;
Paddle player2;
CpuPaddle cpu;

int main()
{
    cout << "Starting the game" << endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player1.width = 25;
    player1.height = 120;
    player1.x = screenWidth - player1.width - 15;
    player1.y = screenHeight / 2 - player1.height / 2;
    player1.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 15;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;

    player2.width = 25;
    player2.height = 120;
    player2.x = 15;
    player2.y = screenHeight / 2 - player2.height / 2;
    player2.speed = 6;

    bool gameStarted = false;
    float delayTimer = 1.0f; // 1-second delay after pressing space
    bool spacePressed = false;
    bool cpuGame = false; // flag to indicate if it's a CPU game

    // Menu screen
    while (!gameStarted)
    {
        BeginDrawing();
        ClearBackground(DarkGreen);

        DrawText("Pong Game", screenWidth / 2 - 100, screenHeight / 2 - 100, 40, WHITE);
        DrawText("Select game mode:", screenWidth / 2 - 120, screenHeight / 2 - 60, 30, WHITE);
        DrawText("1. Player vs Player", screenWidth / 2 - 120, screenHeight / 2 - 20, 30, WHITE);
        DrawText("2. Player vs CPU", screenWidth / 2 - 120, screenHeight / 2 + 20, 30, WHITE);

        if (IsKeyPressed(KEY_ONE))
        {
            cpuGame = false;
            gameStarted = true;
        }
        if (IsKeyPressed(KEY_TWO))
        {
            cpuGame = true;
            gameStarted = true;
        }

        EndDrawing();
    }

    while (WindowShouldClose() == false)
    { 
        BeginDrawing();
        if (gameStarted)
        {
            ClearBackground(DarkGreen);

            // Animation for "Pong Game" text

            DrawText("Pong Game", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, WHITE);
            float textAlpha = (sin(GetTime() * 2) + 1) / 2; // oscillating alpha value
            DrawText("Press space to start", screenWidth / 2 - 120, screenHeight / 2 + 20, 30, Fade(WHITE, textAlpha));
            DrawText("[       Space       ]", screenWidth / 2 - 120, screenHeight / 2 + 50, 30, Fade(WHITE, textAlpha));

            if (IsKeyPressed(KEY_SPACE))
            {
                spacePressed = true;
            }

            if (spacePressed)
            {
                delayTimer -= GetFrameTime();
                if (delayTimer <= 0.0f)
                {
                    gameStarted = false;
                    delayTimer = 0.0f;
                }
            }
        }
        else
        {
        
        if (cpuGame)
        {
            // CPU game
            ball.Move();
            player1.Move();
            cpu.Move(ball.y);

            // Checking For Collision
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height}))
            {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.speed_x *= -1;
            }

            // Drawing
            ClearBackground(DarkGreen); // To fill the window with black color before drawing anything.. So that the previous frame is not visible
            DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
            DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            ball.Draw();
            cpu.Draw ();
            player1.Draw();

            DrawText(TextFormat("%i", CpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", PlayerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        }
        else
        {
            // Player vs Player game
            ball.Move();
            player1.Move();
            player2.Move2();

            // Checking For Collision
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height}))
            {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height}))
            {
                ball.speed_x *= -1;
            }

            // Drawing
            ClearBackground(DarkGreen); // To fill the window with black color before drawing anything.. So that the previous frame is not visible
            DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
            DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            ball.Draw();
            player2.Draw();
            player1.Draw();

            DrawText(TextFormat("%i", CpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", PlayerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}