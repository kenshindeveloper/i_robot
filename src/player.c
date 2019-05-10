#include <stdio.h>
#include "../header/player.h"

Player NewPlayer(Vector2 position) {
    Player player;
    player.position = position;
    player.animator = NewAnimator("resources/sprites/players.png", 2, 3.0f, (Vector2) {3.0f, 4.0f});
    player.isLeft = true;
    player.velocity = 5.0f;
    Vector2 size = ImageQuadAnimator(&player.animator);
    
    player.shape.position = (Vector2) {position.x + 64, position.y + 42};
    player.shape.size = (Vector2) {32 * 2, 32 * 3};
    player.shape.color = (Color) {0.0f, 150.f, 200.0f, 100.0f};

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

void EventPlayer(Player* player) {
    if (IsKeyDown(KEY_LEFT)) {
        player->isLeft = true;
        player->position.x -= player->velocity;
        player->shape.position = (Vector2) {player->position.x + 64, player->position.y + 42};
        SetAnimationAnimator(&player->animator, "run", player->isLeft);
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player->isLeft = false;
        player->position.x += player->velocity;
        player->shape.position = (Vector2) {player->position.x + 64, player->position.y + 42};
        SetAnimationAnimator(&player->animator, "run", player->isLeft);
    }
    else {
        SetAnimationAnimator(&player->animator, "idle", player->isLeft);
    }
}

void DrawPlayer(Player* player) {
    DrawAnimator(&player->animator, player->position);
    DrawShape(&player->shape);
}