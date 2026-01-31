#include<raylib.h>
#include<math.h>
#define MAP_W 10
#define MAP_H 10
#define tilte_size 64

int world_map[MAP_H][MAP_W]={
    // defualt map
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}

};
typedef struct{
    Vector2 pos;
    Vector2 dir;
}Player;

int main(){
    const int screenwidth=800;
    const int screenheight=700;
    
    InitWindow(screenwidth,screenheight,"Phase1-step0");
    SetTargetFPS(60);

    Player player;
    player.pos = (Vector2){3.5f,3.5f};
    player.dir = (Vector2){1.0f,0.0f};

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);


        for (int y=0;y<MAP_H;y++){

            for (int x=0;x<MAP_W;x++){
                int screenX = x * tilte_size;
                int screenY = y * tilte_size;

                if (world_map[y][x]==1){

                    DrawRectangle(screenX,screenY,tilte_size,tilte_size,GRAY);
                }
                else{
                    DrawRectangle(screenX,screenY,tilte_size,tilte_size,BLACK);
                }

                DrawRectangleLines(screenX,screenY,tilte_size,tilte_size,DARKGRAY);
            }
        }
        int px = (int) (player.pos.x * tilte_size);
        int py = (int )(player.pos.y * tilte_size);

        DrawCircle(px,py,tilte_size/4,RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}