#ifndef OBJ_UISHIFTER_H
#define OBJ_UISHIFTER_H

#include "../SonicMania.h"

#if RETRO_USE_PLUS
// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectUIShifter;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityUIShifter;

// Object Struct
extern ObjectUIShifter *UIShifter;

// Standard Entity Events
void UIShifter_Update(void);
void UIShifter_LateUpdate(void);
void UIShifter_StaticUpdate(void);
void UIShifter_Draw(void);
void UIShifter_Create(void* data);
void UIShifter_StageLoad(void);
void UIShifter_EditorDraw(void);
void UIShifter_EditorLoad(void);
void UIShifter_Serialize(void);

// Extra Entity Functions
#endif

#endif //!OBJ_UISHIFTER_H