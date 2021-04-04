#ifndef OBJ_DUST_H
#define OBJ_DUST_H

#include "../SonicMania.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    ushort spriteIndex;
} ObjectDust;

// Entity Class
typedef struct {
    RSDK_ENTITY
    void (*state)(void);
    int timer;
    Entity *parent;
    AnimationData data;
} EntityDust;

// Object Struct
extern ObjectDust *Dust;

// Standard Entity Events
void Dust_Update(void);
void Dust_LateUpdate(void);
void Dust_StaticUpdate(void);
void Dust_Draw(void);
void Dust_Create(void* data);
void Dust_StageLoad(void);
void Dust_EditorDraw(void);
void Dust_EditorLoad(void);
void Dust_Serialize(void);

// Extra Entity Functions
void Dust_State_DropDash(void);
void Dust_State_HammerDrop(void);
void Dust_State_GlideSlide(void);
void Dust_State_Skid(void);
void Dust_State_Spindash(void);
void Dust_State_EggLoco(void);

#endif //!OBJ_DUST_H