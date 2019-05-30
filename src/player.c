#include <stdio.h>
#include <string.h>
#include "../header/global.h"
#include "../header/player.h"

extern Global global;

Player NewPlayer(Vector2 position) {
    Player player;
    player.position = position;
    player.animator = NewAnimator("resources/sprites/players.png", 5, 3.0f, (Vector2) {3.0f, 4.0f});
    player.isLeft = false;
    player.isDown = false;
    player.velocity = 5.0f;
    player.contAnimaClose = 0.0f;

    Vector2 size = ImageQuadAnimator(&player.animator);
    
    player.shape.position = (Vector2) {position.x + 64, position.y + 42};
    player.shape.size = (Vector2) {32 * 2, 64};
    player.shape.color = (Color) {0.0f, 150.f, 200.0f, 100.0f};

    player.ground.position = (Vector2) {position.x + 69, position.y + 112};
    player.ground.size = (Vector2) {54, 27};
    player.ground.color = (Color) {150.f, 150.f, 0.0f, 200.0f};
    player.isGround = false;

    player.head.position = (Vector2) {position.x + 69, position.y + 42};
    player.head.size = (Vector2) {54, 27};
    player.head.color = (Color) {150.f, 150.f, 0.0f, 200.0f};

    player.trigger = NewTrigger((Rectangle) {position.x, position.y, 15, 15}, MAGENTA);

    player.smoke = NewSmoke("resources/sprites/smoke.png", 100);
    player.isUp = false;

    Animation idle = NewAnimation("idle", 2);
    PushFrameAnimation(&idle, (Rectangle) {size.x, size.y, size.x, size.y});
    PushFrameAnimation(&idle, (Rectangle) {size.x, size.y, size.x, size.y});
    PushAnimationAnimator(&player.animator, idle);

    Animation run = NewAnimation("run", 4);
    PushFrameAnimation(&run, (Rectangle) {0, size.y*2, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {size.x, size.y*2, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {0, size.y*2, size.x, size.y});
    PushFrameAnimation(&run, (Rectangle) {size.x, size.y*2, size.x, size.y});
    PushAnimationAnimator(&player.animator, run);

    Animation jump = NewAnimation("jump", 2);
    PushFrameAnimation(&jump, (Rectangle) {size.x, size.y*3, size.x, size.y});
    PushFrameAnimation(&jump, (Rectangle) {size.x, size.y*3, size.x, size.y});
    PushAnimationAnimator(&player.animator, jump);

    Animation down = NewAnimation("down", 2);
    PushFrameAnimation(&down, (Rectangle) {size.x*2, size.y*3, size.x, size.y});
    PushFrameAnimation(&down, (Rectangle) {size.x*2, size.y*3, size.x, size.y});
    PushAnimationAnimator(&player.animator, down);

    Animation close = NewAnimation("close", 3);
    PushFrameAnimation(&close, (Rectangle) {size.x, size.y, size.x, size.y});
    PushFrameAnimation(&close, (Rectangle) {size.x*2, size.y, size.x, size.y});
    PushFrameAnimation(&close, (Rectangle) {size.x, size.y, size.x, size.y});
    PushAnimationAnimator(&player.animator, close);
    
    return player;
}

void DeletePlayer(Player* player) {
    DeleteAnimator(&player->animator);
    DeleteSmoke(&player->smoke);
}

bool CheckCollision(Shape* shape, Map* map) {
    TileMap* auxTileMap = map->tileMap;

    Rectangle rectPlayer = GetRectangle(shape);
    while (auxTileMap != NULL) {
        if (auxTileMap->fkTile->solid && CheckCollisionRecs(rectPlayer, 
        (Rectangle) {auxTileMap->position.x+auxTileMap->fkTile->diff.x, 
        auxTileMap->position.y+auxTileMap->fkTile->diff.y, auxTileMap->fkTile->size.x, 
        auxTileMap->fkTile->size.y}))
            return true;
        
        auxTileMap = auxTileMap->prox;
    } 

    return false;
}

bool IsGround(Player* player, Map* map) {
    TileMap* auxTileMap = map->tileMap;

    Rectangle rectPlayer = GetRectangle(&player->ground);
    Rectangle rectTile;
    while (auxTileMap != NULL) {
        if (auxTileMap->fkTile->solid) {
            rectTile = (Rectangle) {auxTileMap->position.x+auxTileMap->fkTile->diff.x, 
            auxTileMap->position.y+auxTileMap->fkTile->diff.y, auxTileMap->fkTile->size.x, 
            auxTileMap->fkTile->size.y};
            if (CheckCollisionRecs(rectPlayer, rectTile)) {
                float height = GetCollisionRec(rectPlayer, rectTile).height;
                player->position.y -= height;
                global.camera.offset.y += height;
                return true;
            }
        }
        
        auxTileMap = auxTileMap->prox;
    }

    return false;
}

void EventPlayer(Player* player, Map* map) {
    bool isJumping = false;
    player->isUp = false;

    player->isGround = IsGround(player, map); 
    
    if (!player->isDown && IsKeyDown(KEY_LEFT)) {
        if(!player->isLeft || !CheckCollision(&(player->shape), map)) {
            player->position.x -= player->velocity;
            global.camera.offset.x += player->velocity;
            SetAnimationAnimator(&player->animator, "run", player->isLeft);
        }
        player->isLeft = true;
    }
    else if (!player->isDown && IsKeyDown(KEY_RIGHT)) {
        if (player->isLeft || !CheckCollision(&(player->shape), map)) {
            player->position.x += player->velocity;
            global.camera.offset.x -= player->velocity;
            SetAnimationAnimator(&player->animator, "run", player->isLeft);
        }
        player->isLeft = false;
    }
    else if (player->contAnimaClose < 2)
        SetAnimationAnimator(&player->animator, "idle", player->isLeft);
    
    if (global.power > 0 && IsKeyDown(KEY_UP) && !CheckCollision(&(player->head), map)) {
        global.contPower += GetFrameTime();
        if (global.contPower > 0.5) {
            global.power -= 3;
            global.contPower = 0.0f;
        } 
        isJumping = true;
        player->isDown = false;
        player->isUp = true;
        player->position.y -= 5.2;
        global.camera.offset.y += 5.2;
        SetAnimationAnimator(&player->animator, "jump", player->isLeft);
    }
    
    if (player->isGround) {
        if (IsKeyDown(KEY_DOWN)) {
            SetAnimationAnimator(&player->animator, "down", player->isLeft);
            player->isDown = true;
        }
        else
            player->isDown = false;
            
        
        if (strcmp(GetNameAnimator(&player->animator), "idle") == 0 || strcmp(GetNameAnimator(&player->animator), "close") == 0) {
            player->contAnimaClose += GetFrameTime();
            if (player->contAnimaClose > 2 && player->contAnimaClose < 2.5) {
                SetAnimationAnimator(&player->animator, "close", player->isLeft);
            }
            else if (player->contAnimaClose >= 2.5) {
                player->contAnimaClose = 0.0f;
            }
        }
        else
            player->contAnimaClose = 0.0f;
    }
    else if (!isJumping) {
        player->position.y += 9.8;
        global.camera.offset.y -= 9.8;
    }


    player->shape.position = (Vector2) {player->position.x + 64, player->position.y + 42};
    player->ground.position = (Vector2) {player->position.x + 69, player->position.y + 112};
    player->head.position = (Vector2) {player->position.x + 69, player->position.y + 42};
    global.camera.target = player->position;

    EventTrigger(&player->trigger, player->position, player->isLeft, isJumping);
    EventSmoke(&player->smoke, player->position, player->isLeft, player->isUp);
}

void DrawPlayer(Player* player) {
    DrawSmoke(&player->smoke);
    
    DrawAnimator(&player->animator, player->position);
    if (global.isViewShape) {
        DrawShape(&player->shape);
        DrawShape(&player->ground);
        DrawShape(&player->head);
        DrawTrigger(&player->trigger);
    }
}