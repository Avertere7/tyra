/*
# ______       ____   ___
#   |     \/   ____| |___|    
#   |     |   |   \  |   |       
#-----------------------------------------------------------------------
# Copyright 2020, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _FLOORS_
#define _FLOORS_

#include <tamtypes.h>
#include <game.hpp>
#include <engine.hpp>
#include "managers/floor_manager.hpp"
#include "managers/light_manager.hpp"
#include "modules/texture_repository.hpp"
#include "objects/player.hpp"
#include "./camera.hpp"

class Floors : public Game, AudioListener
{

public:
    Floors(Engine *t_engine);
    ~Floors();

    void onInit();
    void onUpdate();
    void onAudioTick();
    void onAudioFinish();

    Engine *engine;

private:
    u32 audioTicks;
    TextureRepository *texRepo;
    LightManager lightManager;
    FloorManager floorManager;
    Player player;
    Camera camera;
};

#endif
