#include "../SonicMania.h"

ObjectFlingRamp *FlingRamp;

void FlingRamp_Update(void)
{
    EntityFlingRamp *entity = (EntityFlingRamp *)RSDK_sceneInfo->entity;
    EntityPlayer *player    = NULL;
    while (RSDK.GetActiveEntities(Player->objectID, (Entity **)&player)) {
        if ((player->direction & FLIP_X) && player->velocity.x >= 0x40000) {
            if (Player_CheckCollisionTouch(player, entity, &FlingRamp->hitbox)) {
                player->velocity.x += 0x40000;
                player->velocity.y = -0x70000;
                player->onGround   = false;
                RSDK.SetSpriteAnimation(player->spriteIndex, ANI_SPRINGCS, &player->playerAnimData, true, 0);
            }
        }
        else if ((player->direction & FLIP_X) && player->velocity.x <= -0x40000) {
            if (Player_CheckCollisionTouch(player, entity, &FlingRamp->hitbox)) {
                player->velocity.x -= 0x40000;
                player->velocity.y = -0x70000;
                player->onGround   = false;
                RSDK.SetSpriteAnimation(player->spriteIndex, ANI_SPRINGCS, &player->playerAnimData, true, 0);
            }
        }
    }
}

void FlingRamp_LateUpdate(void)
{

}

void FlingRamp_StaticUpdate(void)
{

}

void FlingRamp_Draw(void)
{

}

void FlingRamp_Create(void* data)
{
    EntityFlingRamp *entity = (EntityFlingRamp *)RSDK_sceneInfo->entity;
    if (RSDK_sceneInfo->inEditor != 1) {
        entity->active  = ACTIVE_BOUNDS;
        entity->visible = false;
    }
}

void FlingRamp_StageLoad(void)
{
    FlingRamp->hitbox.left   = -16;
    FlingRamp->hitbox.top    = -16;
    FlingRamp->hitbox.right  = 16;
    FlingRamp->hitbox.bottom = 16;
}

void FlingRamp_EditorDraw(void)
{

}

void FlingRamp_EditorLoad(void)
{

}

void FlingRamp_Serialize(void) { RSDK_EDITABLE_VAR(FlingRamp, VAR_UINT8, direction); }
