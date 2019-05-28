#include <stdio.h>
#include "../header/global.h"
#include "../header/player.h"

extern Global global;

Player NewPlayer(Vector2 position) {
    Player player;
    player.position = position;
    player.animator = NewAnimator("resources/sprites/players.png", 2, 3.0f, (Vector2) {3.0f, 4.0f});
    player.isLeft = true;
    player.velocity = 5.0f;
    Vector2 size = ImageQuadAnimator(&player.animator);
    
    player.shape.position = (Vector2) {position.x + 64, position.y + 42};
    player.shape.size = (Vector2) {32 * 2, 64};
    player.shape.color = (Color) {0.0f, 150.f, 200.0f, 100.0f};

    player.ground.position = (Vector2) {position.x + 69, position.y + 112};
    player.ground.size = (Vector2) {54, 24};
    player.ground.color = (Color) {150.f, 150.f, 0.0f, 200.0f};
    player.isGround = false;


    Animation idle = NewAnimation("idle", 2);
    PushFrameAnimation(&idle, (Rectangle) {0, 0, size.x, size.y});
    PushFrameAnimation(&idle, (Rectangle) {0, 0, size.x, size.y});
    PushAnimationAnimator(&player.animator, idle);

    Animation run = NewAnimation("run", 4);
    PushFrameAnimation(&run, (Rectangle) {size.x*2, 0, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {0, size.y, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {size.x*2, 0, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {0, size.y, size.x, size.y});
    PushAnimationAnimator(&player.animator, run);
    
    return player;
}

void DeletePlayer(Player* player) {
    DeleteAnimator(&player->animator);
}

bool CheckCollision(Shape* shape, Map* map) {
    TileMap* auxTileMap = map->tileMap;

    Rectangle rectPlayer = GetRectangle(shape);
    while (auxTileMap != NULL) {
        if (auxTileMap->fkTile->solid && CheckCollisionRecs(rectPlayer, (Rectangle) {auxTileMap->position.x, auxTileMap->position.y, map->quad, map->quad}))
            return true;
        
        auxTileMap = auxTileMap->prox;
    } 

    return false;
}

bool IsGround(Shape* shape, Map* map) {
    TileMap* auxTileMap = map->tileMap;

    Rectangle rectPlayer = GetRectangle(shape);
    Rectangle rectTile;
    while (auxTileMap != NULL) {
        rectTile = (Rectangle) {auxTileMap->position.x, auxTileMap->position.y, map->quad, map->quad};
        if (CheckCollisionRecs(rectPlayer, rectTile)) // && (rectPlayer.y+rectPlayer.height+30) >= rectTile.y
            return true;
        
        auxTileMap = auxTileMap->prox;
    }

    return false;
}

void EventPlayer(Player* player, Map* map) {
    if (IsKeyDown(KEY_LEFT)) {
        if(!player->isLeft ||  !CheckCollision(&(player->shape), map)) {
            player->position.x -= player->velocity;
            global.camera.offset.x += player->velocity;
            SetAnimationAnimator(&player->animator, "run", player->isLeft);
        }
        player->isLeft = true;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        if (player->isLeft || !CheckCollision(&(player->shape), map)) {
            player->position.x += player->velocity;
            global.camera.offset.x -= player->velocity;
            SetAnimationAnimator(&player->animator, "run", player->isLeft);
        }
        player->isLeft = false;
    }
    else {
        SetAnimationAnimator(&player->animator, "idle", player->isLeft);
    }

    player->isGround = IsGround(&(player->ground), map); 
    if (!player->isGround) {
        player->position.y += 9.8;
        global.camera.offset.y -= 9.8;
    }
    // else if (IsKeyDown(KEY_SPACE)) {
    //     player->position.y -= 225.8;
    //     global.camera.offset.y += 225.8;
    // }

    player->shape.position = (Vector2) {player->position.x + 64, player->position.y + 42};
    player->ground.position = (Vector2) {player->position.x + 69, player->position.y + 112};
    global.camera.target = player->position;
}

void DrawPlayer(Player* player) {
    DrawAnimator(&player->animator, player->position);
    if (global.isViewShape) {
        DrawShape(&player->shape);
        DrawShape(&player->ground);
    }
}