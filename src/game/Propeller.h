// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef PROPELLER_H
#define PROPELLER_H

/*
Configuration for the Propeller engine
*/

// What is the name of the game?
#define GAME_NAME "DummyPropellerGame"

// What version is the game?
#define GAME_VERSION_MAJOR 0
#define GAME_VERSION_MINOR 1

// Where to find the game instance?
#include "game/DummyGameInstance.h"

// What is the game instance class?
PROPELLER_REGISTER_PRIMARY_INSTANCE(game::DummyGameInstance);

#endif