#ifndef OBJ_UFO_SPRINGBOARD_H
#define OBJ_UFO_SPRINGBOARD_H

#include "../SonicMania.hpp"

// Object Class
struct ObjectUFO_Springboard : Object {

};

// Entity Class
struct EntityUFO_Springboard : Entity {

};

// Object Struct
extern ObjectUFO_Springboard UFO_Springboard;

// Standard Entity Events
void UFO_Springboard_Update();
void UFO_Springboard_LateUpdate();
void UFO_Springboard_StaticUpdate();
void UFO_Springboard_Draw();
void UFO_Springboard_Create(void* data);
void UFO_Springboard_StageLoad();
void UFO_Springboard_EditorDraw();
void UFO_Springboard_EditorLoad();
void UFO_Springboard_Serialize();

// Extra Entity Functions


#endif //!OBJ_UFO_SPRINGBOARD_H