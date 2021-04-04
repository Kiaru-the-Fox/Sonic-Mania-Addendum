#ifndef OBJ_HUD_H
#define OBJ_HUD_H

#include "../SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    ushort hudMappings;
    ushort superButtonMappings;
    ushort sfx_Click;
    ushort sfx_Starpost;
    int dwordC;
    int replaySaveEnabled;
    int compSession[4];
    int field_24;
    int field_28[PLAYER_MAX];
} ObjectHUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    void (*state)(void);
    Vector2 dword5C[4];
    int field_7C[4];
    int playerLives[PLAYER_MAX];
    int field_9C;
    int superButtonPos;
    void (*competitionStates[PLAYER_MAX])(void);
    Vector2 dwordB4[4];
    Vector2 dwordD4[4];
    Vector2 dwordF4[4];
    Vector2 dword114[4];
    int field_134[4];
    int screenID;
    int timeFlashFrame;
    int ringFlashFrame;
    int field_150;
    int field_154;
    AnimationData hudElementsData;
    AnimationData numbersData;
    AnimationData hyperNumbersData;
    AnimationData lifeIconsData;
    AnimationData playerIDData;
#if RETRO_GAMEVER != VER_100
    AnimationData superButtonsData;
    AnimationData superButtonData1;
#endif
    AnimationData taData1;
    AnimationData taData4;
    AnimationData taData2;
    AnimationData taData3;
} EntityHUD;

// Object Struct
extern ObjectHUD *HUD;

// Standard Entity Events
void HUD_Update(void);
void HUD_LateUpdate(void);
void HUD_StaticUpdate(void);
void HUD_Draw(void);
void HUD_Create(void* data);
void HUD_StageLoad(void);
void HUD_EditorDraw(void);
void HUD_EditorLoad(void);
void HUD_Serialize(void);

// Extra Entity Functions
void HUD_DrawNumbersBase10(Vector2 *drawPos, int value, signed int maxDigits);
void HUD_DrawNumbersBase16(Vector2 *drawPos, int value);
void HUD_DrawNumbersHyperRing(Vector2 *drawPos, int value);
void HUD_GetKeyFrame(AnimationData *data, int buttonID);
void HUD_GetSuperFrames(void);
void HUD_Unknown5(void);
void HUD_Unknown6(void);

#endif //!OBJ_HUD_H