#include <stdio.h>
#include "../header/player.h"

Player NewPlayer(Vector2 position) {
    Player player;
    player.position = position;
    player.animator = NewAnimator("resources/sprites/players.png", 2, 3.0f, (Vector2) {3.0f, 4.0f});
    Vector2 size = ImageQuadAnimator(&player.animator);

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
    SetAnimation(&player->animator, "idle");
    
    if (IsKeyDown(KEY_LEFT))
        SetAnimation(&player->animator, "run");
    
    else if (IsKeyDown(KEY_RIGHT))
        SetAnimation(&player->animator, "run");
}

void DrawPlayer(Player* player) {
    DrawAnimator(&player->animator, player->position);
}