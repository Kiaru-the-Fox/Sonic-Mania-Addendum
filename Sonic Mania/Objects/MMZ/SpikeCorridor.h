#ifndef OBJ_SPIKECORRIDOR_H
#define OBJ_SPIKECORRIDOR_H

#include "SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    ushort aniFrames;
    ushort sfxDrop;
    ushort sfxImpact;
    ushort sfxIndicator;
} ObjectSpikeCorridor;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Vector2 startPos;
    sbyte colWidth;
    sbyte rowHeight;
    int yOffset;
    int timer;
    sbyte rowID;
    sbyte field_75;
    sbyte storedRowID;
    sbyte field_77;
    int fallOffset;
    Hitbox hitbox;
    Hitbox hitboxes[4];
    Entity* parent;
} EntitySpikeCorridor;

// Object Struct
extern ObjectSpikeCorridor *SpikeCorridor;

// Standard Entity Events
void SpikeCorridor_Update(void);
void SpikeCorridor_LateUpdate(void);
void SpikeCorridor_StaticUpdate(void);
void SpikeCorridor_Draw(void);
void SpikeCorridor_Create(void* data);
void SpikeCorridor_StageLoad(void);
void SpikeCorridor_EditorDraw(void);
void SpikeCorridor_EditorLoad(void);
void SpikeCorridor_Serialize(void);

// Extra Entity Functions
void SpikeCorridor_SetupHitboxes(void);
void SpikeCorridor_HandleDrawing(Animator *animator, int offsetY, sbyte a3, bool32 animFlag);
void SpikeCorridor_Unknown3(void);
void SpikeCorridor_CheckPlayerCollisions(void);

void SpikeCorridor_StateDropper_Setup(void);
void SpikeCorridor_StateDropper_CheckForPlayer(void);
void SpikeCorridor_StateDropper_DropWarn(void);
void SpikeCorridor_StateDropper_SpawnSpikes(void);
void SpikeCorridor_StateDropper_DropWait(void);

void SpikeCorridor_StateSpikes_Setup(void);
void SpikeCorridor_StateSpikes_Fall(void);
void SpikeCorridor_StateSpikes_Land(void);

void SpikeCorridor_StateDraw_DropWarn(void);
void SpikeCorridor_StateDraw_Spikes(void);

#endif //!OBJ_SPIKECORRIDOR_H
