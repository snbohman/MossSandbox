#include <raylib.h>
#include <entt/entt.hpp>


int main() {
    InitWindow(500, 500, "softbody");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("hello", 250, 250, 50, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
