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
    Vector2 plane;
}Player;

int Wall(int mapX, int mapY) {
    if (mapX < 0 || mapX >= MAP_W || mapY < 0 || mapY >= MAP_H)
        return 1;
    return world_map[mapY][mapX];
}

int main(){
    const int screenwidth=800;
    const int screenheight=700;

    const float move_speed = 3.0f;
    const float rot_speed = 3.0f;
    
    InitWindow(screenwidth,screenheight,"Phase1-step0");
    SetTargetFPS(60);

    Player player;
    player.pos = (Vector2){3.5f,3.5f};
    player.dir = (Vector2){1.0f,0.0f};

    while(!WindowShouldClose()){

        float dt = GetFrameTime();
        
        // ========== movemet ==========
        if (IsKeyDown(KEY_W)) {
            float targetpX = player.pos.x + player.dir.x * move_speed * dt;
            int mapX = (int)targetpX;
            int mapY = (int)player.pos.y;
            if (!Wall(mapX, mapY)) player.pos.x = targetpX;
            
            float targetpY = player.pos.y + player.dir.y * move_speed * dt;
            mapX = (int)player.pos.x;
            mapY = (int)targetpY;
            if (!Wall(mapX, mapY)) player.pos.y = targetpY;
        }
        
        if (IsKeyDown(KEY_S)) {
            float targetpX = player.pos.x - player.dir.x * move_speed * dt;
            int mapX = (int)targetpX;
            int mapY = (int)player.pos.y;
            if (!Wall(mapX, mapY)) player.pos.x = targetpX;
            
            float targetpY = player.pos.y - player.dir.y * move_speed * dt;
            mapX = (int)player.pos.x;
            mapY = (int)targetpY;
            if (!Wall(mapX, mapY)) player.pos.y = targetpY;
        }
        
        if (IsKeyDown(KEY_A)) {
            Vector2 perpdir = {player.dir.y, -player.dir.x};
            float targetpX = player.pos.x + perpdir.x * move_speed * dt;
            int mapX = (int)targetpX;
            int mapY = (int)player.pos.y;
            if (!Wall(mapX, mapY)) player.pos.x = targetpX;
            
            float targetpY = player.pos.y + perpdir.y * move_speed * dt;
            mapX = (int)player.pos.x;
            mapY = (int)targetpY;
            if (!Wall(mapX, mapY)) player.pos.y = targetpY;
        }
        
        if (IsKeyDown(KEY_D)) {
            Vector2 perpdir = {-player.dir.y, player.dir.x};
            float targetpX = player.pos.x + perpdir.x * move_speed * dt;
            int mapX = (int)targetpX;
            int mapY = (int)player.pos.y;
            if (!Wall(mapX, mapY)) player.pos.x = targetpX;
            
            float targetpY = player.pos.y + perpdir.y * move_speed * dt;
            mapX = (int)player.pos.x;
            mapY = (int)targetpY;
            if (!Wall(mapX, mapY)) player.pos.y = targetpY;
        }
        
        if (IsKeyDown(KEY_RIGHT)) {
            float rotstep = rot_speed * dt;
            float oldDirX = player.dir.x;
            player.dir.x = player.dir.x * cos(rotstep) - player.dir.y * sin(rotstep);
            player.dir.y = oldDirX * sin(rotstep) + player.dir.y * cos(rotstep);
            
            float oldPlaneX = player.plane.x;
            player.plane.x = player.plane.x * cos(rotstep) - player.plane.y * sin(rotstep);
            player.plane.y = oldPlaneX * sin(rotstep) + player.plane.y * cos(rotstep);
        }
        
        if (IsKeyDown(KEY_LEFT)) {
            float rotstep = -rot_speed * dt;
            float oldDirX = player.dir.x;
            player.dir.x = player.dir.x * cos(rotstep) - player.dir.y * sin(rotstep);
            player.dir.y = oldDirX * sin(rotstep) + player.dir.y * cos(rotstep);
            
            float oldPlaneX = player.plane.x;
            player.plane.x = player.plane.x * cos(rotstep) - player.plane.y * sin(rotstep);
            player.plane.y = oldPlaneX * sin(rotstep) + player.plane.y * cos(rotstep);
        }
        
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