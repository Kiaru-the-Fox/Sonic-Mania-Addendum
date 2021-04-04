#ifndef OBJ_BSS_MESSAGE_H
#define OBJ_BSS_MESSAGE_H

#include "../SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    ushort spriteIndex;
} ObjectBSS_Message;

// Entity Class
typedef struct {
    RSDK_ENTITY
    void(*state)(void);
    int timer;
    int timer2;
    bool32 flag;
    int colour;
    int field_6C;
    AnimationData leftData;
    AnimationData rightData;
} EntityBSS_Message;

// Object Struct
extern ObjectBSS_Message *BSS_Message;

// Standard Entity Events
void BSS_Message_Update(void);
void BSS_Message_LateUpdate(void);
void BSS_Message_StaticUpdate(void);
void BSS_Message_Draw(void);
void BSS_Message_Create(void* data);
void BSS_Message_StageLoad(void);
void BSS_Message_EditorDraw(void);
void BSS_Message_EditorLoad(void);
void BSS_Message_Serialize(void);

// Extra Entity Functions
void BSS_Message_State_GetBS(void);
void BSS_Message_State_GetBSWait(void);
void BSS_Message_State_Unknown(void);
void BSS_Message_State_Perfect(void);
void BSS_Message_State_Idle(void);
void BSS_Message_State_Finish(void);
void BSS_Message_TrackProgress_CB(int success);
void BSS_Message_LoadPrevScene(void);
void BSS_Message_LoadGameState(void);

#endif //!OBJ_BSS_MESSAGE_H