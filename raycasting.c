#include<raylib.h>
#include<math.h>
#define MAP_W 10
#define MAP_H 10
#define TILE_SIZE 64

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

    InitWindow(screenwidth,screenheight,"Phase1-step0");
    SetTargetFPS(60);

    Player player;
    player.pos = (Vector2){3.5f,3.5f};
    player.dir = (Vector2){1.0f,0.0f};

    const float move_speed = 3.0f;
    const float rot_speed = 3.0f;

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
        // +++++++++ rendering ++++++++++++
        
        BeginDrawing();
        ClearBackground(BLUE);

        for (int x = 0; x < screenwidth; x++) {
            float cameraX = 2.0 * x / screenwidth - 1.0;
            
            Vector2 rayDir = {
                player.dir.x + player.plane.x * cameraX,
                player.dir.y + player.plane.y * cameraX
            };
            
            // +++ DDA +++
            int mapX = (int)player.pos.x;
            int mapY = (int)player.pos.y;
            
            double deltaDistX = (rayDir.x ==0) ? 1000000000000000000000000000000.0 : fabs(1/rayDir.x);
            double deltaDistY = (rayDir.y ==0) ? 1000000000000000000000000000000.0 : fabs(1/rayDir.y);
            
            double sideDistX, sideDistY;
            int stepX, stepY;
            
            if (rayDir.x < 0) {
                stepX = -1;
                sideDistX = (player.pos.x - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - player.pos.x) * deltaDistX;
            }
            
            if (rayDir.y < 0) {
                stepY = -1;
                sideDistY = (player.pos.y - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - player.pos.y) * deltaDistY;
            }
            
            int hit = 0;
            int side;
            
            while (hit == 0) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                
                if (mapX >= 0 && mapX < MAP_W && mapY >= 0 && mapY < MAP_H) {
                    if (world_map[mapY][mapX] > 0) {
                        hit = 1;
                    }
                } else {
                    hit = 1; 
                }
            }

            // +++ distance calculation and fish eye correction +++
            double perpWallDist;
            if (side == 0) {
                perpWallDist = sideDistX - deltaDistX;
            } else {
                perpWallDist = sideDistY - deltaDistY;
            }
            
            // ++++ wall ++++
            int lineHeight = (int)(screenheight / perpWallDist);
            int drawStart = -lineHeight / 2 + screenheight / 2;
            int drawEnd = lineHeight / 2 + screenheight / 2;
            
            if (drawStart < 0) drawStart = 0;
            if (drawEnd >= screenheight) drawEnd = screenheight - 1;
            
            Color wallColor = DARKGRAY;
            if (side == 1) {
                wallColor = GRAY; 
            }
            
            DrawLine(x, drawStart, x, drawEnd, wallColor);
        }


        

          

        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}