#pragma once

#include "graphics/scene/Entity.h"
#include "mod/Objects.h"

class Object {
public:
    mod::Object & config;

    unsigned id;

    gfx::scene::Entity * entity;

    Object(mod::Object & config)
     : config(config)
    {
        // ...
    }
};
