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

typedef enum{
    STATE_PLAY_MODE,
    STATE_EDIT_MODE
}GameState;

int main(){
    const int screenwidth=800;
    const int screenheight=700;

    InitWindow(screenwidth,screenheight,"Raycasting");
    SetTargetFPS(60);

    Player player;
    player.pos = (Vector2){3.5f,3.5f};
    player.dir = (Vector2){1.0f,0.0f};
    player.plane = (Vector2){0.0,0.66f};

    GameState gameState = STATE_PLAY_MODE;

    const float move_speed = 3.0f;
    const float rot_speed = 3.0f;

    while(!WindowShouldClose()){

        float dt = GetFrameTime();
        
        // ========== movemet ==========
        if (gameState == STATE_PLAY_MODE){

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
        }

        if (IsKeyPressed(KEY_M)) {
            if (gameState == STATE_PLAY_MODE) {
                gameState = STATE_EDIT_MODE;

            } else {
                gameState = STATE_PLAY_MODE;
    }
}
        // +++++++++ rendering ++++++++++++
        
        BeginDrawing();
        ClearBackground(BLUE);

        // ++++ floor and ceiling ++++
        if (gameState == STATE_PLAY_MODE){
            // floor and ceiling 
            DrawRectangle(0, 0, screenwidth, screenheight/2, SKYBLUE);
            DrawRectangle(0, screenheight/2, screenwidth, screenheight/2, DARKBROWN);

             // rays
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
            
            
                double perpWallDist;
                if (side == 0) {
                    perpWallDist = sideDistX - deltaDistX;
                } else {
                    perpWallDist = sideDistY - deltaDistY;
            }
            
            
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


        int miniMapSize = 150;
        int cellSize = miniMapSize / MAP_W > 10 ? miniMapSize / MAP_W : 10;


        int miniMapX = screenwidth - miniMapSize - 10;
        int miniMapY = 10;


        DrawRectangle(miniMapX, miniMapY, miniMapSize, miniMapSize,GRAY);

        DrawText("Camera view - Press M for map (ESC to exit)", 10, 10, 20, DARKGRAY);


        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                if (world_map[y][x] > 0) {
                    DrawRectangle(miniMapX + x * cellSize,miniMapY + y * cellSize,cellSize - 1,cellSize - 1, DARKGRAY );
        }
    }
}


        int playerMapX = miniMapX + (int)(player.pos.x * cellSize);
        int playerMapY = miniMapY + (int)(player.pos.y * cellSize);


        DrawCircle(playerMapX, playerMapY, 4, RED);


        float dirLength = 15.0f;
        DrawLine(playerMapX, playerMapY,playerMapX + (int)(player.dir.x * dirLength),playerMapY + (int)(player.dir.y * dirLength),GREEN);

        }else{
           
        
            DrawText("EDIT MODE (2D) - Press M for Play Mode", 10, 10, 20, WHITE);
            DrawText("Left Click: Add Wall (1) | Right Click: Remove Wall (0)", 10, 40, 18, YELLOW);
            DrawText("Press S to Save | L to Load", 10, 70, 18, SKYBLUE);
    
   
            int tileSize = 40; 
            int offsetX = (screenwidth - MAP_W * tileSize) / 2; 
            int offsetY = 100; 
    
    
            DrawRectangle(offsetX - 5, offsetY - 5, MAP_W * tileSize + 10, MAP_H * tileSize + 10, DARKGRAY);
    
    
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            
            int screenX = offsetX + x * tileSize;
            int screenY = offsetY + y * tileSize;
            
          
            Color cellColor;
            if (world_map[y][x] == 0) {
                cellColor = BLACK; 
            } else {
                cellColor = WHITE; 
            }
            
            // رسم خانه
            DrawRectangle(screenX, screenY, tileSize, tileSize, cellColor);
            DrawRectangleLines(screenX, screenY, tileSize, tileSize, GRAY);
        }
    }
        }
            
        if (gameState == STATE_EDIT_MODE) {
        int tileSize = 40; 
        int offsetX = (screenwidth - MAP_W * tileSize) / 2;
        int offsetY = 100;
        
        
        Vector2 mousePos = GetMousePosition();
        int mouseX = (int)mousePos.x;
        int mouseY = (int)mousePos.y;
        
        
        if (mouseX >= offsetX && mouseX < offsetX + MAP_W * tileSize && mouseY >= offsetY && mouseY < offsetY + MAP_H * tileSize) {
            
            
            int mapX = (mouseX - offsetX) / tileSize;
            int mapY = (mouseY - offsetY) / tileSize;
            
            // i used ai for calsulatin the pos of player on map
            DrawText(TextFormat("Mouse over: [%d,%d]", mapX, mapY),mouseX + 10, mouseY - 20, 15, GREEN); 
            
            
            DrawRectangleLines(offsetX + mapX * tileSize,offsetY + mapY * tileSize,tileSize, tileSize,YELLOW);

            if (gameState == STATE_EDIT_MODE) {
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), 5, RED);
            }
            
           
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
                if (mapX > 0 && mapX < MAP_W - 1 && mapY > 0 && mapY < MAP_H - 1) {
                    world_map[mapY][mapX] = 1;
                    printf("Added wall at [%d,%d]\n", mapX, mapY);
                }
            }
            
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            
                if (mapX > 0 && mapX < MAP_W - 1 && mapY > 0 && mapY < MAP_H - 1) {
                    world_map[mapY][mapX] = 0;
                    printf("Removed wall at [%d,%d]\n", mapX, mapY);
                }
            }
        }
    }
        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}