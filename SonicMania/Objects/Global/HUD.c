// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHUD *HUD;

void HUD_Update(void)
{
    RSDK_THIS(HUD);

    self->enableTimeFlash = false;
    self->enableRingFlash = false;

#if MANIA_USE_PLUS
    if (self->replayClapAnimator.animationID == 11)
        RSDK.ProcessAnimation(&self->replayClapAnimator);
#endif
}

void HUD_LateUpdate(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) {
        for (self->screenID = 0; self->screenID < RSDK.GetVideoSetting(VIDEOSETTING_SCREENCOUNT); ++self->screenID) {
            StateMachine_Run(self->vsStates[self->screenID]);
        }
    }
    else {
        StateMachine_Run(self->state);
    }
#else
    StateMachine_Run(self->state);
#endif

#if GAME_VERSION != VER_100
    if (globals->gameMode < MODE_TIMEATTACK) {
        EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        if (SceneInfo->timeEnabled && player->rings >= 50 && player->superState < SUPERSTATE_SUPER
            && SaveGame_GetSaveRAM()->collectedEmeralds >= 0b01111111) {
            if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV)
                HUD_GetActionButtonFrames();

            if (self->actionPromptPos < TO_FIXED(24))
                self->actionPromptPos += TO_FIXED(8);
        }
        else {
            if (self->actionPromptPos > -TO_FIXED(32))
                self->actionPromptPos -= TO_FIXED(8);
        }
    }
#if MANIA_USE_PLUS
    else if (globals->gameMode == MODE_TIMEATTACK) {
        if (HUD->showTAPrompt) {
            if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV) {
                HUD_GetButtonFrame(&self->superButtonAnimator, KEY_Y);
                HUD_GetButtonFrame(&self->saveReplayButtonAnimator, KEY_Y);
                HUD_GetButtonFrame(&self->thumbsUpButtonAnimator, KEY_START);
            }

            if (self->actionPromptPos < TO_FIXED(24))
                self->actionPromptPos += TO_FIXED(8);
        }
        else {
            if (self->actionPromptPos > -TO_FIXED(64))
                self->actionPromptPos -= TO_FIXED(8);
        }
    }
#endif
#endif
}

void HUD_StaticUpdate(void) {}

void HUD_Draw(void)
{
    RSDK_THIS(HUD);
    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    EntityPlayer *superSonic = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    Vector2 drawPos;
    Vector2 scorePos, timePos, ringPos, lifePos, inputPos, itemPos, bossBarPos, bossIconPos, bossNamePos;

    scorePos.x    = self->scorePos.x;
    scorePos.y    = self->scorePos.y;
    timePos.x     = self->timePos.x;
    timePos.y     = self->timePos.y;
    ringPos.x     = self->ringsPos.x;
    ringPos.y     = self->ringsPos.y;
    lifePos.x     = self->lifePos.x;
    lifePos.y     = self->lifePos.y;
    inputPos.x    = self->inputPos.x;
    inputPos.y    = self->inputPos.y;
    itemPos.x     = self->itemPos.x;
    itemPos.y     = self->itemPos.y;
    bossBarPos.x  = self->bossBarPos.x;
    bossBarPos.y  = self->bossBarPos.y;
    bossIconPos.x = self->bossIconPos.x;
    bossIconPos.y = self->bossIconPos.y;
    if (globals->gameMode == MODE_COMPETITION) {
#if MANIA_USE_PLUS
        scorePos.x = self->vsScorePos[SceneInfo->currentScreenID].x;
        scorePos.y = self->vsScorePos[SceneInfo->currentScreenID].y;
        timePos.x  = self->vsTimePos[SceneInfo->currentScreenID].x;
        timePos.y  = self->vsTimePos[SceneInfo->currentScreenID].y;
        ringPos.x  = self->vsRingsPos[SceneInfo->currentScreenID].x;
        ringPos.y  = self->vsRingsPos[SceneInfo->currentScreenID].y;
        lifePos.x  = self->vsLifePos[SceneInfo->currentScreenID].x;
        lifePos.y  = self->vsLifePos[SceneInfo->currentScreenID].y;
        inputPos.x = self->vsInputPos[SceneInfo->currentScreenID].x;
        inputPos.y = self->vsInputPos[SceneInfo->currentScreenID].y;
        itemPos.x  = self->vsItemPos[SceneInfo->currentScreenID].x;
        itemPos.y  = self->vsItemPos[SceneInfo->currentScreenID].y;
#endif

        foreach_active(Player, plr)
        {
            if (plr != player) {
                self->playerIDAnimator.frameID = plr->playerID;
                RSDK.DrawSprite(&self->playerIDAnimator, &plr->position, false);
            }
        }
    }
#if MANIA_USE_PLUS
    else {
        if (HUD->swapCooldown > 0) {
            RSDK.ProcessAnimation(&self->playerIDAnimator);
            RSDK.DrawSprite(&self->playerIDAnimator, &player->position, false);
            --HUD->swapCooldown;
        }
    }
#endif

    if (RSDK.CheckSceneFolder("ERZ") && superSonic->rings <= 10)
        self->ringFlashFrame = ((Zone->persistentTimer >> 3) & 1);
    else
        self->ringFlashFrame = player->rings ? 0 : ((Zone->persistentTimer >> 3) & 1);

#if GAME_VERSION != VER_100
#if MANIA_USE_PLUS
    self->timeFlashFrame = 0;
    if ((SceneInfo->minutes == 9 && isMainGameMode() && !(globals->medalMods & MEDAL_NOTIMEOVER)) && ActClear->disableTimeBonus)
        self->timeFlashFrame = (Zone->persistentTimer >> 3) & 1;
#else
    if (SceneInfo->minutes == 9 && globals->gameMode < MODE_TIMEATTACK)
        self->timeFlashFrame = (Zone->persistentTimer >> 3) & 1;
#endif
#endif

    // Draw "Score"
    self->hudElementsAnimator.frameID = 0;
    RSDK.DrawSprite(&self->hudElementsAnimator, &scorePos, true);

    // Draw Score
    drawPos.x = scorePos.x + TO_FIXED(97);
    drawPos.y = scorePos.y + TO_FIXED(14);
    HUD_DrawNumbersBase10(&drawPos, player->score, 0);

    // Draw "Time"
#if GAME_VERSION != VER_100
    self->hudElementsAnimator.frameID = self->timeFlashFrame + 1;
#else
    self->hudElementsAnimator.frameID = 1;
#endif
    RSDK.DrawSprite(&self->hudElementsAnimator, &timePos, true);

    if (!self->enableTimeFlash || Zone->persistentTimer & 8) {
        // Draw ":"
        drawPos.x                         = timePos.x + TO_FIXED(52);
        drawPos.y                         = timePos.y - TO_FIXED(2);
        self->hudElementsAnimator.frameID = 12;
        RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

        // Draw Milliseconds
        drawPos.x = timePos.x + TO_FIXED(97);
        drawPos.y = timePos.y + TO_FIXED(14);
        HUD_DrawNumbersBase10(&drawPos, SceneInfo->milliseconds, 2);

        // Draw Seconds
        drawPos.x -= TO_FIXED(9);
        HUD_DrawNumbersBase10(&drawPos, SceneInfo->seconds, 2);

        // Draw Minutes
        drawPos.x -= TO_FIXED(9);
#if MANIA_USE_PLUS
        if (SceneInfo->minutes > 9 && globals->medalMods & MEDAL_NOTIMEOVER)
            HUD_DrawNumbersBase10(&drawPos, SceneInfo->minutes, 2);
        else
#endif
            HUD_DrawNumbersBase10(&drawPos, SceneInfo->minutes, 1);
    }

    // Draw "Rings"
    self->hudElementsAnimator.frameID = self->ringFlashFrame + 3;
    RSDK.DrawSprite(&self->hudElementsAnimator, &ringPos, true);

    if (!self->enableRingFlash || Zone->persistentTimer & 8) {
        // Draw Rings
        drawPos.x = ringPos.x + TO_FIXED(97);
        drawPos.y = ringPos.y + TO_FIXED(14);
        if (player->hyperRing)
            HUD_DrawNumbersHyperRing(&drawPos, player->rings);
        else
            HUD_DrawNumbersBase10(&drawPos, player->rings, 0);
    }

    if (RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID == DebugMode->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = TO_FIXED(24);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += TO_FIXED(16);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.x));
        }
    }
#if MANIA_USE_PLUS
    else if (self->actionPromptPos > -TO_FIXED(64) && globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
        drawPos.y = TO_FIXED(20);

        if (API.CheckDLC(DLC_PLUS)) {
            // Draw Replay Save Icon
            RSDK.DrawSprite(&self->replayClapAnimator, &drawPos, true);

            // Draw Replay Save Button
            drawPos.x -= TO_FIXED(28);
            if (HUD->replaySaveEnabled) {
                RSDK.DrawSprite(&self->saveReplayButtonAnimator, &drawPos, true);
            }
            else {
                self->inkEffect = INK_BLEND;
                RSDK.DrawSprite(&self->saveReplayButtonAnimator, &drawPos, true);

                self->inkEffect = INK_NONE;
            }

            drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
            drawPos.y += TO_FIXED(28);
        }
        // Draw Thumbs Up Icon
        RSDK.DrawSprite(&self->thumbsUpIconAnimator, &drawPos, true);

        // Draw Thumbs Up Button
        drawPos.x -= TO_FIXED(28);
        RSDK.DrawSprite(&self->thumbsUpButtonAnimator, &drawPos, true);
    }
#endif
#if GAME_VERSION != VER_100
    else if (self->actionPromptPos > -TO_FIXED(32)) {
        // Draw Super Icon
        drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
        drawPos.y = TO_FIXED(20);
        RSDK.DrawSprite(&self->superIconAnimator, &drawPos, true);

        drawPos.x -= TO_FIXED(20);
        bool32 canSuper = true;
#if MANIA_USE_PLUS
        if (Player->canSuperCB)
            canSuper = Player->canSuperCB(true);
#endif
        // Draw Super Button
        if (player->state == Player_State_Air && player->jumpAbilityState == 1 && canSuper) {
            RSDK.DrawSprite(&self->superButtonAnimator, &drawPos, true);
        }
        else {
            self->inkEffect = INK_BLEND;
            RSDK.DrawSprite(&self->superButtonAnimator, &drawPos, true);

            self->inkEffect = INK_NONE;
        }
    }
#endif

    // Draw Life Icon (aka the Leader Icon if in encore mode)
    drawPos.x = lifePos.x;
    drawPos.y = lifePos.y;
#if MANIA_USE_PLUS
    int32 lives                    = self->lives[player->playerID];
    self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(player->characterID);

    if (player->characterID == ID_SONIC && player->superState == SUPERSTATE_SUPER) {
        if (player->miracleState)
            self->lifeIconAnimator.frameID = 7;
        else
            self->lifeIconAnimator.frameID = 6;
    }

    if (player->superState == SUPERSTATE_SUPER && player->miracleState) {
        switch (player->characterID) {
            default: break;
            case ID_SONIC: break;
            case ID_TAILS: self->lifeIconAnimator.frameID = 8; break;
            case ID_KNUCKLES: self->lifeIconAnimator.frameID = 9; break;
            case ID_MIGHTY: self->lifeIconAnimator.frameID = 10; break;
            case ID_RAY: self->lifeIconAnimator.frameID = 11; break;
            case ID_AMY: self->lifeIconAnimator.frameID = 12; break;
        }
    }

    if (self->lifeIconAnimator.frameID < 0) {
        self->lifeIconAnimator.frameID = self->lifeFrameIDs[player->playerID];
        lives--;
    }
    else {
        self->lifeFrameIDs[player->playerID] = self->lifeIconAnimator.frameID;
        self->lives[player->playerID]        = player->lives;
    }
#else
    switch (player->characterID) {
        default:
        case ID_SONIC: self->lifeIconAnimator.frameID = 0; break;
        case ID_TAILS: self->lifeIconAnimator.frameID = 1; break;
        case ID_KNUCKLES: self->lifeIconAnimator.frameID = 2; break;
    }
#endif
    if (player->miracleState) {
        for (int32 c = 0; c < 32; ++c) {
            Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
            RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
        }

        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

        for (int32 c = 0; c < 32; ++c) {
            RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
        }
    }
    else
        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_MANIA) {
        if (GET_CHARACTER_ID(2) > 0) {
            drawPos.x += TO_FIXED(20);
            EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
            // Draw Buddy Icon
            self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(sidekick->characterID);

            if (sidekick->characterID == ID_SONIC && sidekick->superState == SUPERSTATE_SUPER) {
                if (sidekick->miracleState)
                    self->lifeIconAnimator.frameID = 7;
                else
                    self->lifeIconAnimator.frameID = 6;
            }

            if (sidekick->superState == SUPERSTATE_SUPER && sidekick->miracleState) {
                switch (sidekick->characterID) {
                    default: break;
                    case ID_SONIC: break;
                    case ID_TAILS: self->lifeIconAnimator.frameID = 8; break;
                    case ID_KNUCKLES: self->lifeIconAnimator.frameID = 9; break;
                    case ID_MIGHTY: self->lifeIconAnimator.frameID = 10; break;
                    case ID_RAY: self->lifeIconAnimator.frameID = 11; break;
                    case ID_AMY: self->lifeIconAnimator.frameID = 12; break;
                }
            }

            if (self->lifeIconAnimator.frameID < 0) {
                self->lifeIconAnimator.frameID = self->lifeFrameIDs[player->playerID];
                lives--;
            }
            else {
                self->lifeFrameIDs[player->playerID] = self->lifeIconAnimator.frameID;
                self->lives[player->playerID]        = player->lives;
            }

            if (sidekick->miracleState) {
                for (int32 c = 0; c < 32; ++c) {
                    Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
                    RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
                }

                RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                for (int32 c = 0; c < 32; ++c) {
                    RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
                }
            }
            else
                RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);
        }
    }

    if (globals->gameMode == MODE_ENCORE) {
        for (int32 p = 0; p < PLAYER_COUNT + 1; ++p) {
            if (HUD->stockFlashTimers[p] > 0)
                HUD->stockFlashTimers[p]--;
        }

        drawPos.x += TO_FIXED(20);
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
        if (sidekick->classID) {
            // Draw Buddy Icon
            self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(sidekick->characterID);
            if (self->lifeIconAnimator.frameID >= 0 && !(HUD->stockFlashTimers[0] & 4)) {
                if ((sidekick->state != Player_State_Death && sidekick->state != Player_State_Drown && sidekick->state != Player_State_EncoreRespawn)
                    || !sidekick->abilityValues[0]) {

                    if (sidekick->characterID == ID_SONIC && sidekick->superState == SUPERSTATE_SUPER) {
                        if (sidekick->miracleState)
                            self->lifeIconAnimator.frameID = 7;
                        else
                            self->lifeIconAnimator.frameID = 6;
                    }
                    
                    if (sidekick->superState == SUPERSTATE_SUPER && sidekick->miracleState) {
                        switch (sidekick->characterID) {
                            default: break;
                            case ID_SONIC: break;
                            case ID_TAILS: self->lifeIconAnimator.frameID = 8; break;
                            case ID_KNUCKLES: self->lifeIconAnimator.frameID = 9; break;
                            case ID_MIGHTY: self->lifeIconAnimator.frameID = 10; break;
                            case ID_RAY: self->lifeIconAnimator.frameID = 11; break;
                            case ID_AMY: self->lifeIconAnimator.frameID = 12; break;
                        }
                    }

                    if (self->lifeIconAnimator.frameID < 0) {
                        self->lifeIconAnimator.frameID = self->lifeFrameIDs[player->playerID];
                        lives--;
                    }
                    else {
                        self->lifeFrameIDs[player->playerID] = self->lifeIconAnimator.frameID;
                        self->lives[player->playerID]        = player->lives;
                    }

                    if (sidekick->miracleState) {
                        for (int32 c = 0; c < 32; ++c) {
                            Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
                            RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
                        }

                        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                        for (int32 c = 0; c < 32; ++c) {
                            RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
                        }
                    }
                    else
                        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);
                }
            }

            // Draw Stock Icons
            drawPos.x += TO_FIXED(20);
            RSDK.SetSpriteAnimation(HUD->aniFrames, 12, &self->lifeIconAnimator, true, 0);
            for (int32 i = 1; i < 5; ++i) {
                self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(GET_STOCK_ID(i));
                if (self->lifeIconAnimator.frameID >= 0 && !(HUD->stockFlashTimers[i] & 4))
                    RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                drawPos.x += TO_FIXED(16);
            }

            RSDK.SetSpriteAnimation(HUD->aniFrames, 2, &self->lifeIconAnimator, true, 0);
        }
    }
    else {
        // Draw Life Icon "X"
        self->hudElementsAnimator.frameID = 14;
        RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

        // Draw Lives
        drawPos.x += TO_FIXED(48);
        if (player->lives < 10)
            drawPos.x -= TO_FIXED(8);
        if (player->lives > 99)
            drawPos.x += TO_FIXED(8);
        if (player->lives > 999)
            drawPos.x += TO_FIXED(8);
        if (player->lives > 9999)
            drawPos.x += TO_FIXED(8);
        // how anyone would ever be able to realistically surpass 9999 lives, i have no idea, so there isn't a hardcoded exception for it
        HUD_DrawNumbersBase10(&drawPos, lives, 0);
    }
#else
    // Draw Life Icon "X"
    self->hudElementsAnimator.frameID = 14;
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Lives
    drawPos.x += TO_FIXED(48);
    if (player->lives < 10)
        drawPos.x -= TO_FIXED(8);
    HUD_DrawNumbersBase10(&drawPos, player->lives, 0);
#endif

    if (globals->gameMode == MODE_COMPETITION) {
        // Draw Competition Borders
#if MANIA_USE_PLUS
        switch (HUD->screenBorderType[SceneInfo->currentScreenID]) {
            default:
            case VS_BORDER_NONE: break;

            case VS_BORDER_BOTTOMRIGHT:
                // Along right edge
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_BOTTOM:
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_BOTTOMLEFT:
                // Along left edge (on screen 2)
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOPRIGHT:
                // Along right edge
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along top edge (on screen 2 or 3)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOP:
                // Along top edge (on screen 2)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOPLEFT:
                // Along left edge (on screen 3 or 4)
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along top edge (on screen 3 or 4)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;
        }
#else
        switch (SceneInfo->currentScreenID) {
            case 0:
                // Along right edge (on screen 1)
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case 1:
                // Along left edge (on screen 2)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            default: break;
        }
#endif
    }

    if (SceneInfo->debugMode || globals->superSecret || globals->gameMode == MODE_TIMEATTACK) {
        Vector2 inputPos;
        inputPos.x = self->inputPos.x;
        inputPos.y = self->inputPos.y;

        // D-pad
        drawPos.x = inputPos.x;
        drawPos.y = inputPos.y - TO_FIXED(6);
        HUD_DrawInputViewer(&drawPos, player, 0);

        // ABC
        drawPos.x = inputPos.x + TO_FIXED(28);
        drawPos.y = inputPos.y - TO_FIXED(6);
        HUD_DrawInputViewer(&drawPos, player, 1);

        // XYZ
        drawPos.x = inputPos.x + TO_FIXED(28);
        drawPos.y = inputPos.y - TO_FIXED(18);
        HUD_DrawInputViewer(&drawPos, player, 2);

        // Bumpers
        drawPos.x = inputPos.x + TO_FIXED(28);
        drawPos.y = inputPos.y - TO_FIXED(28);
        HUD_DrawInputViewer(&drawPos, player, 3);
    }

    itemPos.x = self->itemPos.x;
    itemPos.y = self->itemPos.y;

    drawPos.x = itemPos.x;
    drawPos.y = itemPos.y;
    HUD_DrawItemsHUD(&drawPos, player, 0);

    if (self->invincibilityActive)
        drawPos.x = itemPos.x + TO_FIXED(18);
    else
        drawPos.x = itemPos.x;
    drawPos.y = itemPos.y;
    HUD_DrawItemsHUD(&drawPos, player, 1);

    if (self->invincibilityActive && !self->speedShoesActive)
        drawPos.x = itemPos.x + TO_FIXED(18);
    else if (self->speedShoesActive && !self->invincibilityActive)
        drawPos.x = itemPos.x + TO_FIXED(18);
    else if (self->invincibilityActive && self->speedShoesActive)
        drawPos.x = itemPos.x + TO_FIXED(36);
    else
        drawPos.x = itemPos.x;
    drawPos.y = itemPos.y;
    HUD_DrawItemsHUD(&drawPos, player, 2);
}

void HUD_Create(void *data)
{
    RSDK_THIS(HUD);

    if (!SceneInfo->inEditor) {
#if MANIA_USE_PLUS
        ActClear->disableTimeBonus = false;
#endif

        self->active    = ACTIVE_NORMAL;
        self->visible   = true;
        self->drawGroup = Zone->hudDrawGroup;

        self->scorePos.x    = TO_FIXED(16);
        self->scorePos.y    = TO_FIXED(12);
        self->timePos.x     = TO_FIXED(16);
        self->timePos.y     = TO_FIXED(28);
        self->ringsPos.x    = TO_FIXED(16);
        self->ringsPos.y    = TO_FIXED(44);
        self->lifePos.x     = TO_FIXED(16);
        self->lifePos.y     = TO_FIXED(ScreenInfo->size.y - 12);
        self->inputPos.x    = TO_FIXED(16);
        self->inputPos.y    = TO_FIXED(ScreenInfo->size.y - 32);
        self->itemPos.x     = TO_FIXED(16);
        self->itemPos.y     = TO_FIXED(60);
        self->bossIconPos.x = TO_FIXED(16);
        self->bossIconPos.y = TO_FIXED(ScreenInfo->size.y - 52);
        self->bossBarPos.x  = TO_FIXED(18);
        self->bossBarPos.y  = TO_FIXED(ScreenInfo->size.y - 52);
#if GAME_VERSION != VER_100
        self->actionPromptPos = -TO_FIXED(32);
#endif

#if MANIA_USE_PLUS
        for (int32 i = 0; i < SCREEN_COUNT; ++i) {
            self->vsScorePos[i].x = self->scorePos.x;
            self->vsScorePos[i].y = self->scorePos.y;
            self->vsTimePos[i].x  = self->timePos.x;
            self->vsTimePos[i].y  = self->timePos.y;
            self->vsRingsPos[i].x = self->ringsPos.x;
            self->vsRingsPos[i].y = self->ringsPos.y;
            self->vsLifePos[i].x  = self->lifePos.x;
            self->vsLifePos[i].y  = self->lifePos.y;
            self->vsInputPos[i].x = self->inputPos.x;
            self->vsInputPos[i].y = self->inputPos.y;
            self->vsItemPos[i].x  = self->itemPos.x;
            self->vsItemPos[i].y  = self->itemPos.y;
        }
#endif

        RSDK.SetSpriteAnimation(HUD->aniFrames, 0, &self->hudElementsAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 1, &self->numbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 9, &self->hyperNumbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 2, &self->lifeIconAnimator, true, 0);
#if MANIA_USE_PLUS
        RSDK.SetSpriteAnimation(HUD->aniFrames, globals->gameMode == MODE_ENCORE ? 13 : 8, &self->playerIDAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 10, &self->thumbsUpIconAnimator, true, 2);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 10, &self->replayClapAnimator, true, 1);
#else
        RSDK.SetSpriteAnimation(HUD->aniFrames, 8, &self->playerIDAnimator, true, 0);
#endif
        RSDK.SetSpriteAnimation(HUD->aniFrames, 14, &self->readyUpIconAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBox1Animator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBox2Animator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBox3Animator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 15, &self->inputDpadAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputUpAnimator, true, 1);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputDownAnimator, true, 2);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputLeftAnimator, true, 3);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputRightAnimator, true, 4);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 17, &self->inputABCAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 18, &self->inputAAnimator, true, 1);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 18, &self->inputBAnimator, true, 2);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 18, &self->inputCAnimator, true, 3);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 19, &self->inputXYZAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 20, &self->inputXAnimator, true, 1);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 20, &self->inputYAnimator, true, 2);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 20, &self->inputZAnimator, true, 3);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 21, &self->inputBumperAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 22, &self->inputLBumperAnimator, true, 1);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 22, &self->inputRBumperAnimator, true, 2);

#if GAME_VERSION != VER_100
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, 0, &self->superIconAnimator, true, 0);
        HUD_GetActionButtonFrames();
#endif

#if MANIA_USE_PLUS
        RSDK.AddViewableVariable("Show HUD", &self->visible, VIEWVAR_UINT8, false, true);
#endif
    }
}

void HUD_StageLoad(void)
{
    HUD->aniFrames = RSDK.LoadSpriteAnimation("Global/HUD.bin", SCOPE_STAGE);
#if GAME_VERSION != VER_100
    HUD->superButtonFrames = RSDK.LoadSpriteAnimation("Global/SuperButtons.bin", SCOPE_STAGE);
#endif
#if MANIA_USE_PLUS
    HUD->bossFrames = RSDK.LoadSpriteAnimation("Global/BossBar.bin", SCOPE_STAGE);
#endif

#if MANIA_USE_PLUS
    HUD->sfxClick    = RSDK.GetSfx("Stage/Click.wav");
    HUD->sfxStarpost = RSDK.GetSfx("Global/StarPost.wav");

    HUD->showTAPrompt = false;

    EntityCompetitionSession *session = CompetitionSession_GetSession();
    if (globals->gameMode == MODE_COMPETITION) {
        HUD->screenBorderType[0] = session->screenBorderType[0];
        HUD->screenBorderType[1] = session->screenBorderType[1];
        HUD->screenBorderType[2] = session->screenBorderType[2];
        HUD->screenBorderType[3] = session->screenBorderType[3];
    }
#endif
}

void HUD_DrawNumbersBase10(Vector2 *drawPos, int32 value, int32 digitCount)
{
    RSDK_THIS(HUD);

    if (!digitCount && value > 0) {
        int32 v = value;
        while (v > 0) {
            ++digitCount;
            v /= 10;
        }
    }
    else {
        if (!digitCount && value <= 0)
            digitCount = 1;
    }

    int32 digit = 1;
    while (digitCount--) {
        self->numbersAnimator.frameID = value / digit % 10;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        digit *= 10;
        drawPos->x -= TO_FIXED(8);
    }
}

void HUD_DrawNumbersBase16(Vector2 *drawPos, int32 value)
{
    RSDK_THIS(HUD);

    int32 mult = 1;
    for (int32 i = 4; i; --i) {
        self->numbersAnimator.frameID = value / mult & 0xF;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        drawPos->x -= TO_FIXED(8);
        mult *= 16;
    }
}

void HUD_DrawNumbersHyperRing(Vector2 *drawPos, int32 value)
{
    RSDK_THIS(HUD);

    int32 cnt   = 0;
    int32 mult  = 1;
    int32 mult2 = 1;
    if (value <= 0) {
        cnt = 1;
    }
    else {
        int32 v = value;
        while (v) {
            ++cnt;
            v /= 10;
        }
    }

    if (cnt > 0) {
        while (cnt--) {
            self->hyperNumbersAnimator.frameID = value / mult % 10;
            RSDK.DrawSprite(&self->hyperNumbersAnimator, drawPos, true);
            drawPos->x -= TO_FIXED(8);
            mult = 10 * mult2;
            mult2 *= 10;
        }
    }

    self->hyperNumbersAnimator.frameID = 10;
    drawPos->x -= TO_FIXED(4);
    RSDK.DrawSprite(&self->hyperNumbersAnimator, drawPos, true);
}

#if GAME_VERSION != VER_100
void HUD_GetButtonFrame(Animator *animator, int32 buttonID)
{
    int32 gamepadType = UIButtonPrompt_GetGamepadType();
    if (API_GetConfirmButtonFlip() && buttonID <= 1)
        buttonID ^= 1;

    // Gamepad
    if (gamepadType != UIBUTTONPROMPT_KEYBOARD && (gamepadType < UIBUTTONPROMPT_KEYBOARD_FR || gamepadType > UIBUTTONPROMPT_KEYBOARD_SP)) {
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, gamepadType, animator, true, buttonID);
    }
    else {
        // Keyboard
        EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
#if MANIA_USE_PLUS
        int32 id = API_GetInputDeviceID(player->controllerID);
#else
        int32 id = INPUT_NONE;
#endif
        int32 contID = id == INPUT_UNASSIGNED ? CONT_P1 : player->controllerID;

        int32 map = 0;
        switch (buttonID) {
            default: break;
            case 0: map = ControllerInfo[contID].keyA.keyMap; break;
            case 1: map = ControllerInfo[contID].keyB.keyMap; break;
            case 2: map = ControllerInfo[contID].keyX.keyMap; break;
            case 3: map = ControllerInfo[contID].keyY.keyMap; break;
            case 4: map = ControllerInfo[contID].keyStart.keyMap; break;
        }

        int32 frame = UIButtonPrompt_MappingsToFrame(map);
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, 1, animator, true, frame);
    }
}
void HUD_GetActionButtonFrames(void)
{
    RSDK_THIS(HUD);

    HUD_GetButtonFrame(&self->superButtonAnimator, KEY_Y);
#if MANIA_USE_PLUS
    HUD_GetButtonFrame(&self->saveReplayButtonAnimator, KEY_Y);
    HUD_GetButtonFrame(&self->thumbsUpButtonAnimator, KEY_START);
    HUD_GetButtonFrame(&self->readyUpButtonAnimator, KEY_Y);
#endif
}
#endif

void HUD_State_MoveIn(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    StateMachine(*state) = NULL;
    Vector2 *scorePos = NULL, *timePos = NULL, *ringsPos = NULL, *lifePos = NULL, *inputPos = NULL, *itemPos = NULL;
    int32 *targetPos = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        state     = &self->vsStates[SceneInfo->currentScreenID];
        scorePos  = &self->vsScorePos[SceneInfo->currentScreenID];
        timePos   = &self->vsTimePos[SceneInfo->currentScreenID];
        ringsPos  = &self->vsRingsPos[SceneInfo->currentScreenID];
        lifePos   = &self->vsLifePos[SceneInfo->currentScreenID];
        inputPos  = &self->vsInputPos[SceneInfo->currentScreenID];
        itemPos   = &self->vsItemPos[SceneInfo->currentScreenID];
        targetPos = &self->vsTargetPos[SceneInfo->currentScreenID];
    }
    else {
        state     = &self->state;
        scorePos  = &self->scorePos;
        timePos   = &self->timePos;
        ringsPos  = &self->ringsPos;
        itemPos   = &self->itemPos;
        inputPos  = &self->inputPos;
        lifePos   = &self->lifePos;
        targetPos = &self->targetPos;
    }

    if (scorePos->x < *targetPos)
        scorePos->x += TO_FIXED(8);

    if (timePos->x < *targetPos)
        timePos->x += TO_FIXED(8);

    if (ringsPos->x < *targetPos)
        ringsPos->x += TO_FIXED(8);

    if (itemPos->x < *targetPos)
        itemPos->x += TO_FIXED(8);

    if (inputPos->x < *targetPos)
        inputPos->x += TO_FIXED(8);

    if (lifePos->x < *targetPos)
        lifePos->x += TO_FIXED(8);
    else
        *state = StateMachine_None;
#else
    if (self->scorePos.x < self->targetPos)
        self->scorePos.x += TO_FIXED(8);

    if (self->timePos.x < self->targetPos)
        self->timePos.x += TO_FIXED(8);

    if (self->ringsPos.x < self->targetPos)
        self->ringsPos.x += TO_FIXED(8);

    if (self->lifePos.x < self->targetPos)
        self->lifePos.x += TO_FIXED(8);
    else
        self->state = StateMachine_None;
#endif
}

void HUD_State_MoveOut(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    Vector2 *scorePos = NULL, *timePos = NULL, *ringsPos = NULL, *lifePos = NULL, *inputPos = NULL, *itemPos = NULL;
    StateMachine(*state) = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        state    = &self->vsStates[self->screenID];
        scorePos = &self->vsScorePos[self->screenID];
        timePos  = &self->vsTimePos[self->screenID];
        ringsPos = &self->vsRingsPos[self->screenID];
        lifePos  = &self->vsLifePos[self->screenID];
        inputPos = &self->vsInputPos[self->screenID];
        itemPos  = &self->vsItemPos[self->screenID];
    }
    else {
        state    = &self->state;
        scorePos = &self->scorePos;
        timePos  = &self->timePos;
        ringsPos = &self->ringsPos;
        lifePos  = &self->lifePos;
        inputPos = &self->inputPos;
        itemPos  = &self->itemPos;
    }

    scorePos->x -= TO_FIXED(8);

    if (timePos->x - scorePos->x > TO_FIXED(16))
        timePos->x -= TO_FIXED(8);

    if (ringsPos->x - timePos->x > TO_FIXED(16))
        ringsPos->x -= TO_FIXED(8);

    if (itemPos->x - ringsPos->x > TO_FIXED(16))
        itemPos->x -= TO_FIXED(8);

    if (inputPos->x - itemPos->x > TO_FIXED(16))
        inputPos->x -= TO_FIXED(8);

    if (lifePos->x - inputPos->x > TO_FIXED(16))
        lifePos->x -= TO_FIXED(8);

    if (lifePos->x < -TO_FIXED(80)) {
        if (globals->gameMode == MODE_COMPETITION) {
            *state = StateMachine_None;
            CompSession_DeriveWinner(self->screenID, FINISHTYPE_GAMEOVER);
            EntityGameOver *gameOver   = RSDK_GET_ENTITY(self->screenID + Player->playerCount, GameOver);
            EntityCompetition *manager = Competition->sessionManager;

            if (!manager || manager->timer) {
                RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(false));
                gameOver->playerID = self->screenID;
            }
            else {
                RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(true));
                RSDK.SetEngineState(ENGINESTATE_FROZEN);
                SceneInfo->timeEnabled = false;
                gameOver->playerID     = self->screenID;
            }
        }
        else {
            destroyEntity(self);
        }
    }
#else
    self->scorePos.x -= TO_FIXED(8);

    if (self->timePos.x - self->scorePos.x > TO_FIXED(16))
        self->timePos.x -= TO_FIXED(8);

    if (self->ringsPos.x - self->timePos.x > TO_FIXED(16))
        self->ringsPos.x -= TO_FIXED(8);

    if (self->lifePos.x - self->ringsPos.x > TO_FIXED(16))
        self->lifePos.x -= TO_FIXED(8);

    if (self->lifePos.x < -TO_FIXED(64))
        destroyEntity(self);
#endif
}

void HUD_MoveIn(EntityHUD *hud)
{
    hud->targetPos = hud->scorePos.x;
    hud->scorePos.x -= TO_FIXED(0x100);
    hud->timePos.x -= TO_FIXED(0x110);
    hud->ringsPos.x -= TO_FIXED(0x120);
    hud->itemPos.x -= TO_FIXED(0x130);
    hud->inputPos.x -= TO_FIXED(0x140);
    hud->lifePos.x -= TO_FIXED(0x150);
    hud->state = HUD_State_MoveIn;
}

void HUD_MoveOut(void)
{
    foreach_active(HUD, hud) { hud->state = HUD_State_MoveOut; }
}

void HUD_EnableRingFlash(void)
{
    foreach_all(HUD, hud)
    {
        if (hud)
            hud->enableRingFlash = true;
        foreach_break;
    }
}

int32 HUD_CharacterIndexFromID(int32 characterID)
{
    int32 id = -1;
    for (int32 i = characterID; i > 0; ++id, i >>= 1)
        ;
    return id;
}

void HUD_DrawInputViewer(Vector2 *drawPos, EntityPlayer *player, int32 drawType)
{
    RSDK_THIS(HUD);
    RSDKControllerState *controller = &ControllerInfo[player->controllerID];
    RSDKTriggerState *Ltrigger      = &TriggerInfoL[player->controllerID];
    RSDKTriggerState *Rtrigger      = &TriggerInfoR[player->controllerID];

    if (drawType == 0) {
        RSDK.DrawSprite(&self->inputDpadAnimator, drawPos, true);
        if (controller->keyUp.press || controller->keyUp.down) {
            self->inputUpAnimator.frameID = 1;
        }
        else {
            self->inputUpAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputUpAnimator, drawPos, true);

        if (controller->keyDown.press || controller->keyDown.down) {
            self->inputDownAnimator.frameID = 2;
        }
        else {
            self->inputDownAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputDownAnimator, drawPos, true);

        if (controller->keyLeft.press || controller->keyLeft.down) {
            self->inputLeftAnimator.frameID = 3;
        }
        else {
            self->inputLeftAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputLeftAnimator, drawPos, true);

        if (controller->keyRight.press || controller->keyRight.down) {
            self->inputRightAnimator.frameID = 4;
        }
        else {
            self->inputRightAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputRightAnimator, drawPos, true);
    }

    if (drawType == 1) {
        RSDK.DrawSprite(&self->inputABCAnimator, drawPos, true);
        if (controller->keyA.press || controller->keyA.down) {
            self->inputAAnimator.frameID = 1;
        }
        else {
            self->inputAAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputAAnimator, drawPos, true);

        if (controller->keyB.press || controller->keyB.down) {
            self->inputBAnimator.frameID = 2;
        }
        else {
            self->inputBAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputBAnimator, drawPos, true);

        if (controller->keyC.press || controller->keyC.down) {
            self->inputCAnimator.frameID = 3;
        }
        else {
            self->inputCAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputCAnimator, drawPos, true);
    }

    if (drawType == 2) {
        RSDK.DrawSprite(&self->inputXYZAnimator, drawPos, true);
        if (controller->keyX.press || controller->keyX.down) {
            self->inputXAnimator.frameID = 1;
        }
        else {
            self->inputXAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputXAnimator, drawPos, true);

        if (controller->keyY.press || controller->keyY.down) {
            self->inputYAnimator.frameID = 2;
        }
        else {
            self->inputYAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputYAnimator, drawPos, true);

        if (controller->keyZ.press || controller->keyZ.down) {
            self->inputZAnimator.frameID = 3;
        }
        else {
            self->inputZAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputZAnimator, drawPos, true);
    }

    if (drawType == 3) {
        RSDK.DrawSprite(&self->inputBumperAnimator, drawPos, true);
        if (Ltrigger->keyBumper.press || Ltrigger->keyBumper.down) {
            self->inputLBumperAnimator.frameID = 1;
        }
        else {
            self->inputLBumperAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputLBumperAnimator, drawPos, true);

        if (Rtrigger->keyBumper.press || Rtrigger->keyBumper.down) {
            self->inputRBumperAnimator.frameID = 2;
        }
        else {
            self->inputRBumperAnimator.frameID = 0;
        }
        RSDK.DrawSprite(&self->inputRBumperAnimator, drawPos, true);
    }
}

void HUD_DrawItemsHUD(Vector2 *drawPos, EntityPlayer *player, int32 drawType)
{
    RSDK_THIS(HUD);

    if (drawType == 0) {
        if (player->state != Player_State_Transform && player->superState != SUPERSTATE_SUPER) {
            if (player->invincibleTimer > 0) {
                self->invincibilityActive = true;
                if (player->invincibleTimer > 180) {
                    self->itemBox1Animator.frameID = 5;
                }
                else {
                    if (player->invincibleTimer & 4)
                        self->itemBox1Animator.frameID = 0;
                    if (player->invincibleTimer & 8)
                        self->itemBox1Animator.frameID = 5;
                }
            }
            else {
                self->itemBox1Animator.frameID = 0;
                self->invincibilityActive      = false;
            }
        }
        else {
            if (player->rings > 0) {
                self->invincibilityActive = true;
                if (player->rings > 3) {
                    if (player->miracleState)
                        self->itemBox1Animator.frameID = 13;
                    else
                        self->itemBox1Animator.frameID = 12;
                }
                else {
                    if (player->superRingLossTimer & 8)
                        self->itemBox1Animator.frameID = 0;
                    else {
                        if (player->miracleState)
                            self->itemBox1Animator.frameID = 13;
                        else
                            self->itemBox1Animator.frameID = 12;
                    }
                }
            }
            else {
                self->itemBox1Animator.frameID = 0;
                self->invincibilityActive      = false;
            }
        }

        RSDK.DrawSprite(&self->itemBox1Animator, drawPos, true);
    }

    if (drawType == 1) {
        if (player->speedShoesTimer > 0) {
            self->speedShoesActive = true;
            if (player->speedShoesTimer > 180) {
                switch (player->characterID) {
                    default:
                    case ID_SONIC: self->itemBox2Animator.frameID = 6; break;
                    case ID_TAILS: self->itemBox2Animator.frameID = 7; break;
                    case ID_KNUCKLES: self->itemBox2Animator.frameID = 8; break;
                    case ID_MIGHTY: self->itemBox2Animator.frameID = 9; break;
                    case ID_RAY: self->itemBox2Animator.frameID = 10; break;
                    case ID_AMY: self->itemBox2Animator.frameID = 11; break;
                }
            }
            else {
                switch (player->characterID) {
                    default:
                    case ID_SONIC:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 6;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                    case ID_TAILS:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 7;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                    case ID_KNUCKLES:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 8;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                    case ID_MIGHTY:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 9;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                    case ID_RAY:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 10;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                    case ID_AMY:
                        if (player->speedShoesTimer & 4)
                            self->itemBox2Animator.frameID = 11;
                        if (player->speedShoesTimer & 8)
                            self->itemBox2Animator.frameID = 0;
                        break;
                }
            }
        }
        else {
            self->itemBox2Animator.frameID = 0;
            self->speedShoesActive         = false;
        }

        RSDK.DrawSprite(&self->itemBox2Animator, drawPos, true);
    }

    if (drawType == 2) {
        if (player->shield > SHIELD_NONE) {
            self->shieldActive = true;
            switch (player->shield) {
                default:
                case SHIELD_BLUE: self->itemBox3Animator.frameID = 1; break;
                case SHIELD_BUBBLE: self->itemBox3Animator.frameID = 2; break;
                case SHIELD_FIRE: self->itemBox3Animator.frameID = 3; break;
                case SHIELD_LIGHTNING: self->itemBox3Animator.frameID = 4; break;
            }
        }
        else {
            self->itemBox3Animator.frameID = 0;
            self->shieldActive             = false;
        }

        RSDK.DrawSprite(&self->itemBox3Animator, drawPos, true);
    }
}

#if GAME_INCLUDE_EDITOR
void HUD_EditorDraw(void)
{
    RSDK_THIS(HUD);
    RSDK.SetSpriteAnimation(HUD->aniFrames, 0, &self->hudElementsAnimator, true, 0);
    RSDK.DrawSprite(&self->hudElementsAnimator, NULL, false);
}

void HUD_EditorLoad(void) { HUD->aniFrames = RSDK.LoadSpriteAnimation("Editor/EditorIcons.bin", SCOPE_STAGE); }
#endif

void HUD_Serialize(void) {}
