#include "../SonicMania.h"

ObjectSpecialClear *SpecialClear;

void SpecialClear_Update(void) {}

void SpecialClear_LateUpdate(void)
{
    RSDK_THIS(SpecialClear);
    if (entity->state)
        entity->state();
}

void SpecialClear_StaticUpdate(void) {}

void SpecialClear_Draw(void)
{
    Vector2 vertPos[4];
    Vector2 drawPos;

    RSDK_THIS(SpecialClear);

    int centerX  = RSDK_screens->centerX << 16;
    drawPos.x    = centerX - 0x600000;
    int *saveRAM = SaveGame->saveRAM;

    // Draw Emeralds
    int id = 1;
    for (int i = 0; i < 7; ++i) {
        int frame = 7;
        if ((id & saveRAM[28]) > 0)
            frame = id;
        entity->data4.frameID = frame;
        drawPos.y             = entity->positions[7 + i].y;
        RSDK.DrawSprite(&entity->data4, &drawPos, true);
        drawPos.x += 0x200000;
        id <<= 1;
    }

    drawPos.x    = entity->positions[1].x;
    drawPos.y    = entity->positions[1].y;
    drawPos.x    = centerX + 2 * drawPos.x;
    vertPos[0].x = drawPos.x - 7602176;
    vertPos[0].y = drawPos.y - 1310720;
    vertPos[1].x = 0x680000 + drawPos.x;
    vertPos[2].x = 0x780000 + drawPos.x;
    vertPos[3].x = drawPos.x - 6553600;
    vertPos[1].y = drawPos.y - 1310720;
    vertPos[2].y = drawPos.y - 0x40000;
    vertPos[3].y = drawPos.y - 0x40000;
    RSDK.DrawQuad(vertPos, 4, 0, 0, 0, 255, 0);

    if (entity->finishType > 0) {
        drawPos.x    = entity->positions[0].x;
        drawPos.y    = entity->positions[0].y;
        drawPos.x    = centerX + 2 * drawPos.x;
        vertPos[0].x = drawPos.x - 0x740000;
        vertPos[0].y = drawPos.y + 0x1C0000;
        vertPos[1].x = 0x680000 + drawPos.x;
        vertPos[2].x = 0x780000 + drawPos.x;
        vertPos[3].x = drawPos.x - 0x640000;
        vertPos[1].y = drawPos.y + 0x1C0000;
        vertPos[2].y = drawPos.y + 0x2C0000;
        vertPos[3].y = drawPos.y + 0x2C0000;
        RSDK.DrawQuad(vertPos, 4, 0, 0, 0, 255, 0);
    }

    drawPos.x = entity->positions[0].x;
    drawPos.y = entity->positions[0].y;
    drawPos.x += centerX;
    switch (entity->finishType) {
        case 0:
            entity->data1.frameID = 0;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);
            break;
        case 1:
            entity->data1.frameID = 1;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 2;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            drawPos.x = entity->positions[1].x;
            drawPos.y = entity->positions[1].y;
            drawPos.x += centerX;
            entity->data1.frameID = 3;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);
            break;
        case 2:
            entity->data1.frameID = 4;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 5;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            drawPos.x = entity->positions[1].x;
            drawPos.y = entity->positions[1].y;
            drawPos.x += centerX;
            entity->data1.frameID = 6;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);
            break;
        case 3:
            entity->data1.frameID = 7;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 8;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 9;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            drawPos.x = entity->positions[1].x;
            drawPos.y = entity->positions[1].y;
            drawPos.x += centerX;
            entity->data1.frameID = 10;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 11;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);

            entity->data1.frameID = 13;
            RSDK.DrawSprite(&entity->data1, &drawPos, true);
            break;
        default: break;
    }
    drawPos.x = entity->positions[2].x;
    drawPos.y = entity->positions[2].y;
    drawPos.x += centerX - 0x560000;
    entity->data2.frameID = 4;
    RSDK.DrawSprite(&entity->data2, &drawPos, true);

    entity->data2.frameID = 6;
    drawPos.x += 0x660000;
    RSDK.DrawSprite(&entity->data2, &drawPos, true);

    drawPos.x += 0x430000;
    SpecialClear_DrawNumbers(&drawPos, entity->score);

    drawPos.x = entity->positions[3].x;
    drawPos.y = entity->positions[3].y;
    drawPos.x += centerX - 0x560000;
    entity->data2.frameID = 0;
    RSDK.DrawSprite(&entity->data2, &drawPos, true);

    drawPos.x += 3276800;
    entity->data2.frameID = 3;
    RSDK.DrawSprite(&entity->data2, &drawPos, true);

    entity->data2.frameID = 6;
    drawPos.x += 3407872;
    RSDK.DrawSprite(&entity->data2, &drawPos, true);

    drawPos.x += 0x430000;
    SpecialClear_DrawNumbers(&drawPos, entity->ringBonus);

    if (entity->isBSS) {
        drawPos.x = entity->positions[4].x;
        drawPos.y = entity->positions[4].y;
        drawPos.x += centerX - 0x560000;
        entity->data2.frameID = 1;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        drawPos.x += 0x320000;
        entity->data2.frameID = 3;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        entity->data2.frameID = 6;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        drawPos.x += 0x430000;
        SpecialClear_DrawNumbers(&drawPos, entity->perfectBonus);
    }
    else {
        drawPos.x = entity->positions[5].x;
        drawPos.y = entity->positions[5].y;
        drawPos.x += centerX - 0x560000;
        entity->data2.frameID = 2;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        drawPos.x += 0x320000;
        entity->data2.frameID = 3;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        entity->data2.frameID = 6;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        drawPos.x += 0x430000;
        SpecialClear_DrawNumbers(&drawPos, entity->machBonus);
    }

    if (entity->continuesFlag) {
        drawPos.x = entity->positions[6].x;
        drawPos.y = entity->positions[6].y;
        drawPos.x += centerX - 0x560000;
        entity->data2.frameID = 5;
        RSDK.DrawSprite(&entity->data2, &drawPos, true);

        if (entity->field_6C == 1) {
            drawPos.x += 0xB00000;
            drawPos.y += 0xA0000;
            RSDK.DrawSprite(&entity->data5, &drawPos, true);
        }
    }

    if (entity->flag)
        RSDK.FillScreen(entity->fillColour, entity->timer, entity->timer - 128, entity->timer - 256);
}

void SpecialClear_Create(void *data)
{
    RSDK_THIS(SpecialClear);
    if (!RSDK_sceneInfo->inEditor) {
        entity->active     = ACTIVE_NORMAL;
        entity->visible    = true;
        entity->drawOrder  = 14;
        entity->timer      = 512;
        entity->fillColour = 0xF0F0F0;
        entity->flag       = true;
        entity->state      = SpecialClear_Unknown3;
        if (RSDK.CheckStageFolder("SpecialBS")) {
            entity->isBSS     = true;
            entity->ringBonus = 100 * BSS_Setup->rings;
            if (!BSS_Setup->ringCount)
                entity->perfectBonus = 50000;
            entity->finishType = 0;
        }
        else {
            RSDK.CopyPalette(7, 0, 0, 0, 128);
            entity->isBSS     = 0;
            entity->ringBonus = 100 * UFO_Setup->rings;
            entity->machBonus = 1000 * (UFO_Setup->machLevel + 10 * UFO_Setup->scoreBonus);
            if (globals->gameMode < MODE_TIMEATTACK && entity->machBonus + entity->ringBonus >= 10000)
                entity->continuesFlag = true;
            int *saveRAM     = SaveGame->saveRAM;
            entity->score    = saveRAM[26];
            entity->score1UP = saveRAM[27];
            entity->lives    = saveRAM[25];
            if (saveRAM[28] == 0x7F)
                entity->finishType = 2;
            else
                entity->finishType = UFO_Setup->timedOut == 0;
        }
        entity->positions[0].x = 0x1400000;
        entity->positions[0].y = 0x580000;
        entity->positions[1].x = -0x1400000;
        entity->positions[1].y = 0x700000;
        entity->positions[2].x = 0x1E80000;
        entity->positions[2].y = 0x8C0000;
        entity->positions[3].x = 0x3080000;
        entity->positions[3].y = 0xAC0000;
        entity->positions[5].x = 0x4280000;
        entity->positions[5].y = 0xBC0000;
        entity->positions[4].x = 0x4280000;
        entity->positions[4].y = 0xBC0000;
        entity->positions[6].x = 0x5480000;
        entity->positions[6].y = 0xCC0000;
        RSDK.CopyPalette(1, 0, 0, 128, 48);
        entity->positions[7].x  = 0x1100000;
        entity->positions[10].y = -0xA0000;
        entity->positions[7].y  = 0x1300000;
        entity->positions[11].x = -0xAA000;
        entity->positions[8].x  = 0x1500000;
        entity->positions[11].y = -0xB4000;
        entity->positions[8].y  = 0x1700000;
        entity->positions[12].x = -0xBE000;
        entity->positions[9].x  = 0x1900000;
        entity->positions[12].y = -0xC8000;
        entity->positions[9].y  = 0x1B00000;
        entity->positions[13].x = -0xD2000;
        entity->positions[10].x = 0x1D00000;
        entity->positions[13].y = -0xDC000;
        RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 5, &entity->data2, true, 0);
        RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 6, &entity->data3, true, 0);
        RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 7, &entity->data4, true, 0);
        switch (globals->playerID & 0xFF) {
            case ID_TAILS:
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 1, &entity->data1, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 8, &entity->data5, true, 1);
                break;
            case ID_KNUCKLES:
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 2, &entity->data1, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 8, &entity->data5, true, 2);
                break;
            case ID_MIGHTY:
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 3, &entity->data1, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 8, &entity->data5, true, 3);
                break;
            case ID_RAY:
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 4, &entity->data1, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 8, &entity->data5, true, 4);
                break;
            default:
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 0, &entity->data1, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->spriteIndex, 8, &entity->data5, true, 0);
                break;
        }
    }
}

void SpecialClear_StageLoad(void)
{
    SpecialClear->spriteIndex     = RSDK.LoadSpriteAnimation("Special/Results.bin", SCOPE_STAGE);
    SpecialClear->sfx_ScoreAdd    = RSDK.GetSFX("Global/ScoreAdd.wav");
    SpecialClear->sfx_ScoreTotal  = RSDK.GetSFX("Global/ScoreTotal.wav");
    SpecialClear->sfx_Event       = RSDK.GetSFX("Special/Event.wav");
    SpecialClear->sfx_SpecialWarp = RSDK.GetSFX("Global/SpecialWarp.wav");
    SpecialClear->sfx_Continue    = RSDK.GetSFX("Special/Continue.wav");
    SpecialClear->sfx_Emerald     = RSDK.GetSFX("Special/Emerald.wav");
}

void SpecialClear_DrawNumbers(Vector2 *pos, int value)
{
    RSDK_THIS(SpecialClear);
    int id  = 0;
    int cnt = value;
    if (value <= 0) {
        id = 1;
    }
    else {
        do {
            ++id;
            cnt /= 10;
        } while (cnt > 0);
    }
    if (id <= 0)
        return;

    int mult = 1;
    do {
        entity->data3.frameID = value / mult % 10;
        RSDK.DrawSprite(&entity->data3, pos, true);
        mult *= 10;
        pos->x -= 0x90000;
        --id;
    } while (id);
}

void SpecialClear_GiveScoreBonus(int score)
{
    RSDK_THIS(SpecialClear);
    entity->score += score;
    if (entity->score > 9999999)
        entity->score = 9999999;

    if (globals->gameMode == MODE_ENCORE)
        return;

    if (entity->score >= entity->score1UP) {
        if (entity->lives < 99)
            entity->lives++;
        Music_PlayMusicTrack(TRACK_1UP);
        Music->dword250 = -1;
        while (entity->score <= entity->score1UP) {
            entity->score1UP += 50000;
        }
    }
}

void SpecialClear_SaveCB(int success)
{
    RSDK_THIS(SpecialClear);
    UIWaitSpinner_WaitReplay();
    entity->field_120 = 0;
}

void SpecialClear_LoadScene(void)
{
    RSDK_THIS(SpecialClear);
    if (entity->fillColour) {
        entity->fillColour -= 0x80808;
    }
    else if (!entity->field_120) {
        if (((globals->menuParam[22] >> 8) & 0xFF) == 1) {
            RSDK.LoadScene("Presentation", "Menu");
            RSDK.InitSceneLoad();
        }
        else {
            int *saveRAM = SaveGame->saveRAM;
            if (globals->gameMode == MODE_ENCORE)
                RSDK.LoadScene("Encore Mode", "");
            else
                RSDK.LoadScene("Mania Mode", "");
            RSDK_sceneInfo->listPos = saveRAM[30];
            RSDK.InitSceneLoad();
        }
    }
}

void SpecialClear_TallyScore(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->ringBonus > 0) {
        entity->ringBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }
    if (entity->perfectBonus > 0) {
        entity->perfectBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }

    if (entity->machBonus > 0) {
        entity->machBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }
    if (RSDK_controller->keyA.press || RSDK_controller->keyStart.press) {
        SpecialClear_GiveScoreBonus(entity->machBonus + entity->ringBonus + entity->perfectBonus);
        entity->ringBonus    = 0;
        entity->perfectBonus = 0;
        entity->machBonus    = 0;
    }

    if (entity->machBonus + entity->ringBonus + entity->perfectBonus <= 0) {
        entity->timer = 0;
        if (entity->continuesFlag)
            entity->state = SpecialClear_Unknown9;
        else
            entity->state = SpecialClear_Unknown10;
        RSDK.PlaySFX(SpecialClear->sfx_ScoreTotal, 0, 255);
    }
    else if (++entity->timer == 2) {
        entity->timer = 0;
        RSDK.PlaySFX(SpecialClear->sfx_ScoreAdd, 0, 255);
    }
}

void SpecialClear_Unknown3(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->timer <= 0) {
        entity->timer = 0;
        entity->flag  = 0;
        entity->state = SpecialClear_Unknown4;
        Music_PlayTrack(TRACK_ACTCLEAR);
    }
    else {
        entity->timer -= 16;
    }
}

void SpecialClear_Unknown4(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->positions[0].x > 0)
        entity->positions[0].x -= 0x100000;

    if (entity->positions[1].x < 0) {
        entity->positions[1].x += 0x100000;
    }

    if (++entity->timer == 48) {
        entity->timer = 0;
        entity->state = SpecialClear_Unknown5;
    }
}

void SpecialClear_Unknown5(void)
{
    RSDK_THIS(SpecialClear);
    entity->positions[0].y -= 0x10000;
    entity->positions[1].y -= 0x10000;
    if (++entity->timer == 48) {
        entity->timer = 0;
        entity->state = SpecialClear_Unknown6;
    }
}

void SpecialClear_HandlePositions(void)
{
    RSDK_THIS(SpecialClear);
    int val = 0x700000;
    if (!entity->finishType)
        val = 0x680000;

    entity->positions[10].y += 0x4000;
    entity->positions[7].x += entity->positions[10].y;
    if (entity->positions[7].x > val && entity->positions[10].y >= 0) {
        entity->positions[7].x  = val;
        entity->positions[10].y = -(entity->positions[10].y >> 1);
    }

    entity->positions[11].x += 0x4000;
    entity->positions[7].y += entity->positions[11].x;
    if (entity->positions[7].y > val && entity->positions[11].x >= 0) {
        entity->positions[7].y  = val;
        entity->positions[11].x = -(entity->positions[11].x >> 1);
    }

    entity->positions[11].y += 0x4000;
    entity->positions[8].x += entity->positions[11].y;
    if (entity->positions[8].x > val && entity->positions[11].y >= 0) {
        entity->positions[8].x  = val;
        entity->positions[11].y = -(entity->positions[11].y >> 1);
    }

    entity->positions[12].x += 0x4000;
    entity->positions[8].y += entity->positions[12].x;
    if (entity->positions[8].y > val && entity->positions[12].x >= 0) {
        entity->positions[8].y  = val;
        entity->positions[12].x = -(entity->positions[12].x >> 1);
    }

    entity->positions[12].y += 0x4000;
    entity->positions[9].x += entity->positions[12].y;
    if (entity->positions[9].x > val && entity->positions[12].y >= 0) {
        entity->positions[9].x  = val;
        entity->positions[12].y = -(entity->positions[12].y >> 1);
    }

    entity->positions[13].x += 0x4000;
    entity->positions[9].y += entity->positions[13].x;
    if (entity->positions[9].y > val && entity->positions[13].x >= 0) {
        entity->positions[9].y  = val;
        entity->positions[13].x = -(entity->positions[13].x >> 1);
    }

    entity->positions[13].y += 0x4000;
    entity->positions[10].x += entity->positions[13].y;
    if (entity->positions[10].x > val && entity->positions[13].y >= 0) {
        entity->positions[10].x = val;
        entity->positions[13].y = -(entity->positions[13].y >> 1);
    }
}

void SpecialClear_Unknown6(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->positions[2].x > 0)
        entity->positions[2].x -= 0x100000;

    if (entity->positions[3].x > 0)
        entity->positions[3].x -= 0x100000;

    if (entity->positions[4].x > 0)
        entity->positions[4].x -= 0x100000;

    if (entity->positions[5].x > 0)
        entity->positions[5].x -= 0x100000;

    if (entity->positions[6].x <= 0) {
        if (entity->finishType == 2)
            User.UnlockAchievement("ACH_EMERALDS");
        entity->state = SpecialClear_Unknown7;
    }
    else {
        entity->positions[6].x -= 0x100000;
    }
    SpecialClear_HandlePositions();
}

void SpecialClear_Unknown7(void)
{
    RSDK_THIS(SpecialClear);
    if (++entity->timer == 120) {
        entity->timer = 0;
        entity->state = SpecialClear_TallyScore;
        if (entity->finishType)
            RSDK.PlaySFX(SpecialClear->sfx_Emerald, 0, 255);
    }
    SpecialClear_HandlePositions();
}

void SpecialClear_Unknown9(void)
{
    RSDK_THIS(SpecialClear);

    if (++entity->timer == 120) {
        RSDK.PlaySFX(SpecialClear->sfx_Continue, 0, 255);

        if (globals->continues < 25)
            globals->continues++;
    }
    else if (entity->timer > 120) {
        entity->field_6C = (entity->timer >> 3) & 1;
    }

    if (entity->timer == 360) {
        entity->timer         = 0;
        int *saveRAM          = SaveGame->saveRAM;
        saveRAM[26]           = entity->score;
        globals->restartScore = entity->score;
        saveRAM[27]           = entity->score1UP;
        saveRAM[25]           = entity->lives;
        saveRAM[29]           = globals->continues;
        saveRAM[66]           = globals->characterFlags;
        saveRAM[67]           = globals->stock;
        saveRAM[68]           = globals->playerID;

        if (saveRAM[28] == 0x7F) {
            entity->state = SpecialClear_Unknown11;
        }
        else {
            entity->timer = 0;
            entity->flag  = 1;
            RSDK.PlaySFX(SpecialClear->sfx_SpecialWarp, 0, 255);
            entity->state = SpecialClear_Unknown15;
        }
    }
}

void SpecialClear_Unknown10(void)
{
    RSDK_THIS(SpecialClear);
    if (++entity->timer == 120) {
        entity->timer         = 0;
        int *saveRAM          = SaveGame->saveRAM;
        saveRAM[26]           = entity->score;
        globals->restartScore = entity->score;
        if (saveRAM[28] == 127) {
            entity->state = SpecialClear_Unknown11;
        }
        else {
            entity->timer = 0;
            entity->flag  = 1;
            RSDK.PlaySFX(SpecialClear->sfx_SpecialWarp, 0, 255);
            entity->state = SpecialClear_Unknown15;
        }
    }
}

void SpecialClear_Unknown11(void)
{
    RSDK_THIS(SpecialClear);
    entity->positions[0].x += 0x180000;
    entity->positions[1].x -= 0x180000;
    if (++entity->timer == 30) {
        entity->timer      = 0;
        entity->finishType = 3;
        entity->state      = SpecialClear_Unknown12;
    }
}

void SpecialClear_Unknown12(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->positions[0].x > 0)
        entity->positions[0].x -= 0x180000;

    if (entity->positions[1].x >= 0) {
        RSDK.PlaySFX(SpecialClear->sfx_Event, 0, 255);
        entity->state = SpecialClear_Unknown13;
    }
    else {
        entity->positions[1].x += 0x180000;
    }
}

void SpecialClear_Unknown13(void)
{
    RSDK_THIS(SpecialClear);
    if (++entity->timer == 160) {
        entity->timer = 0;
        entity->flag  = true;
        RSDK.PlaySFX(SpecialClear->sfx_SpecialWarp, 0, 255);
        entity->state = SpecialClear_Unknown15;
    }
}

void SpecialClear_Unknown15(void)
{
    RSDK_THIS(SpecialClear);

    if (entity->timer >= 768) {
        entity->state = SpecialClear_LoadScene;
        if (globals->gameMode < MODE_TIMEATTACK && globals->saveSlotID != NO_SAVE_SLOT) {
            entity->field_120 = 1;
            UIWaitSpinner_Wait();
            SaveGame_TrackGameProgress(SpecialClear_SaveCB);
        }
    }
    else {
        entity->timer += 8;
    }
}

void SpecialClear_EditorDraw(void) {}

void SpecialClear_EditorLoad(void) {}

void SpecialClear_Serialize(void) {}