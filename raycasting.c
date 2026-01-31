#include<raylib.h>
#include<math.h>
int main(){
    const int screenwidth=800;
    const int screenheight=700;
    
    InitWindow(screenwidth,screenheight,"Phase1-step0");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}