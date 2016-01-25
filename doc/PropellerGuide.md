PropellerGuide
==============

This document describes how you can actually do anything with the engine. This document is aimed for programmers.

Tip: if you open this file in Github, the markdown is formatted.

What is provided
================

.libs for the compiled engine is provided. The source code for the entrypoint&game is provided.

The engine contains references to code provided by SCE, because of this all the developers should be under the NDA by SCE.

**Nothing about the engine code should ever be released publicly. All the code should be kept in private repository.**

However, you should be extra careful to not modify the engine, or future patches might break it.

**If you need to modify the engine, contact the engine developer!**

Please note that the engine still has lots of functionality missing for the game developer.

How to compile the engine
=========================

1) Open PropellerGame.sln in the windows/ folder
2) Set configuration to GameDebug (usually it defaults to EditorDebug)
3) Set platform to Win32 (usually it defaults to Emscripten)
4) Set startup project to Standalone
5) F5 to compile

If required, you may need to change working directory to "../../bin" in debugging options.

State of the engine
===================

Engine is still highly work in progress. While stuff like integrated editor, rcc++ and 3D exists, they might not be at the state where you actually want to use it.

Following features can be considered to be working nicely

* Entity-Component-System
* 2D rendering (With dynamic lights)
* Box2D-Physics
* Flexible configuration system
* Flexible input system

Features I have planned to add

* Support for Tiled/integrated 2D map editor
* More platforms

What you can modify
===================

You should only modify the data under the game project (src/game/). 

Your games assets goes into the data/ folder. The folder is mounted by the engine so you can reference the files by the name in the code. (Don't add the /data/)

Engines workflow
================

While you can create any kind of classes you desire in the game project, you have to create the following classes to get the engine to run your code. (Derive from this class)

* engine::component::Component
* engine::SystemBase
* engine::scene::ProgrammableSceneType

The engine uses entity-component-system pattern.

**Entity** can be simplified to a list that connects different components

**Component** has the actual data. For example TransformComponent has the location of the entity. SpriteComponent has the sprite reference and other information related to drawing it. Its good to note that SpriteComponent does not do any drawing, it just holds the data.

**System** system handles its components and the data on those components. For example RendererSystem loops trough the SpriteComponents and handles the drawing of the sprites.


## Example of the entity-component-system

Lets say you want the player to be able to pickup coins with different values. 

The coin entity would have following components:

* TransformComponent
* SpriteComponent ("coin.png")
* Box2DPhysicsComponent (to make the coin fly around because of explosions happening)
* CoinComponent (value of the coin)

Player has similar kind of stuff, but some game related components.

* TransformComponent
* SpriteComponent ("player.png")
* Box2DPhysicsComponent
* PlayerInfoComponent (Created by user) (contains coins owned, hp, etc fun stuff)
* PickupComponent (Created by user)

When the Box2DPhysicsComponents collide, they generate "onHit" events. Register the PickupComponent to listen to the hit events by the following code:

    rigidBody->setOnHitEvent(this, &PickupComponent::onHit);

After this the PickupComponent::onHit is going to receive hits. After this the Player entity should receive the hits. In that method, parse out if its the coin or not. (Try to find CoinComponent) If its coin, fetch the value, add the value to the PlayerInfoComponent and remove the coin from the game.

## Creating new objects

Do not ever create rtti-object manually by calling new.

Entities, components, etc are all under the PropellerEngine's RTTI system. You can use the static methods under the rtti::RTTI class feerly, but just to create object the easiest way is the following code:

    Entity *entity = rtti::generate<Entity>(instance->getContextData());

Just change the Entity to whatever type you want to create. This way the object you create is registered correctly to the rtti-system. Making sure all the required systems in the engine can handle the object.

For dynamic cast, you should not use the buildin dynamic_cast, as thats not supported well on all the existing platforms. You should instead use the rtti::dynamicCast<T>(obj) call.

## Removing objects

While you should not try to create objects using new, you should not try to remove with delete either.

Entities should be removed using the instance->getScene()->removeEntity(). This removes also all the components and releases references to the different systems used.

To remove components you should use the entity->removeComponent().

## Instance

PropellerEngine supports multiple instances of the same game running at the same time. This is used a lot in the editor.

This prevents completely the usage of singletons and other stuff that refers to a global state.

The whole "game" runs as a **instance**. The underlying instance is "GameInstance" on the engine side. To extent the functionality, you have your own game-specific instance on the Game project.

Instance holds the SceneManager and SystemManager. It will also contain references to all the different systems.

This is why you may see the instance passed around the code. With the pointer to instance you can access almost all the systems. (instance->getRendererSystem(), etc).

## Context

Context is a lightweight version of the instance, it only contains pointers to the different systems and doesn't have any other functionality.

The context is also created on engine side, but the suer can extend it by using the GameContext.h file.

Context is provided to the rtti system, to make sure the components are registered to the right system on the correct instance.

## SceneManager

SceneManager handles all the scenes in the engine. You can add new programable scenes with the addScene() method. SceneManager also loads .PropellerScene's in the data folders.

Adding your programmable scenes to the manager is best done in the games own GameInstance.

## SystemManager

SystemManager has all the systems in it and will run the "update" call every tick. It will provide the systems with the delta time.

If you have created new game related system, you should add it to the SystemManager. Using the weight parameter you can set the order when your system should run.

You can get list of systems using the "systemlist" console command, this also shows existing systems.

## Logging

For development purposes, the engine has the following macros for logging:

* LOG_INFO(p_msg)
* LOG_WARNING(p_msg)
* LOG_ERROR(p_msg)

These can be used anywhere in the code.

If you want to output some variables, you can do it via the following:

    float x, y;
	String name;

	LOG_INFO("Entity" << name << " at position: " << x << "," << y);

Logs are by default piped into the Visual Studios "output" window. On release builds they are send to engine.log file.

## Creating new source files

Check out the example files in the /doc/ folder. Those files contains comments about what you need to modify, etc.

Components and systems provided by the engine
=============================================

Following components are provided by the engine:

* Box2DRigidBodyComponent (Enable box2d physics)
* Box2DCharacterComponent (Box2d physics for 2d character)
* CameraComponent (Used to center the camera to the entity)
* MeshComponent (Used to render 3D-meshes)
* SpriteComponent (Used to render 2D-sprites)
* TransformComponent (Used to provide position and rotation data for the entity)
* LuaScriptComponent (Deprecated! Do not use!)
* LightComponent (Provides 2d-lighting) (Experimental, should be fixed soonish)
* RigidBodyComponent (3D-physics using bullet physics)

Following systems are provided by the engine:

* RawInputSystem      Weight: 0    (Provides raw input from Win32-API)
* XInputSystem        Weight: 0    (Xbox-controller support)
* AndroidInputSystem  Weight: 0    (Touch input for android)
* InputSystem         Weight: 3    (Main InputSystem (gets info from the device specific inputs))
* Box2DPhysicSystem   Weight: 10   (Box2D integration, handles Box2D..Components)
* PhysicSystem        Weight: 10   (Bullet integration, handles RigidBodyComponent)
* LuaSystem           Weight: 15   (Deprecated)
* CameraSystem        Weight: 30   (Handles camera positioning)
* RendererSystem      Weight: 40   (Renders the scene, handles Light/Sprite and MeshComponents)
* IngameConsoleSystem Weight: 60   (Renders the ingame console (WIP))

Configuration
=============

PropellerEngine provides configuration system for the engine. It can also be used to manage the games options and parameters.

Parameters are saved to .cfg files. The .cfg files contains the ingame commands to reapply the parameters.

The configuration system is similar to systems found in Quake or Source engines.

## Commands

Commands can be executed using the ingame-console, the editor or the config files.

The engine defines a set of commands already, adding your own commands is easily.

First, include "engine/console/Command.h" in the .cpp file you wish to use for the command. Its helpful to keep the command near the system or component its related to.

Following code snippet explains how to create a simple command:

    CREATE_COMMAND(version)
    {
        LOG_INFO("Version: " TO_STRING(ENGINE_VERSION_MAJOR) "." TO_STRING(ENGINE_VERSION_MINOR));
        return 0;
    }

The snippet above creates the command "version". When its executed, it logs the version of the engine and returns with error code 0. (All ok.)

##CVars

CVar system is similar to source-engines configuration system.

Creating new cvars is easy, you can use the "CVAR" macro. For example:

    namespace cvar {
        CVAR(int, developer, 0, false);
        CVAR(int, editor, 0, false);

	    EXTERN_CVAR(String, defaultScene);
	    EXTERN_CVAR(int, r_width);
	    EXTERN_CVAR(int, r_height);
    }

The following code implements cvars 'developer' and 'editor'. It uses extern cvars defined in other files.

Accessing cvars from code is simple:

    if(*cvar::developer == 1)
    {
        LOG_INFO("Developer mode enabled!");
    }

To list available commands, use the "listcvars" command.
* Basic usage of the engine "how components and systems work together"

#Propeller.h

Each game project should contain file "Propeller.h". This file is included in the runnable projects, and used to defined the default settings of the game. The file is self-documented and should be easy to use.

Following settings are available:

* GAME_NAME - Name of the game, appears in titles and logs.
* GAME_VERSION_MAJOR/MINOR - Version of the game, can be used to detect compatible savefiles.
* PROPELLER_REGISTER_PRIMARY_INSTANCE - What instance should be started when the engine is loaded. (Remember to include the instance in the Propeller.h file)


Data formats
============

Because of the lack of resources to develop the engine, it only supports very specific list of data types.

##Images

Images for textures, maps and sprites only supports standart png-files. They should be size thats power of two, some custom platforms may have issues with non-power-of-two textures, while DX11 builds should handle this without an issue.

Some other texture formats may work, but only png will be supported on all platform targets for now.

No conversion process required.

##3D-models

Engine itself only supports its own custom format, .PropellerModel. However, .obj format can be converted into the .PropellerModel format by using the editor.

When exporting the .obj format from Blender or 3ds Max, use the following settings:

* Triangles, not quads
* Scaling is optional, but can be helpful
* Export: coordinates, uw coordinates and normals

Materials in the .obj format are not supported. Materials should be created using the engines own material editor. (TBA)

Fbx-format is planned to be supported in the future.

Packaging the game contents
===========================

You can either use the DirectoryArchive, and leave the files as they are to the /data/ folder. However it is recommended to use the editor to package the files into a .pp format.

Currently subfolders are not supported, so all the files need to be in the same directory.

For platforms like Android the packaging is automatically done using the platforms specific  archive system.

##Patching and modding

.pp archives can be used to patch or mod the contents after the release.

For example, if the game contents are in packet "game.pp", user could create a packet for custom skin set, "superskin.pp". "Game.pp" is loaded first, and after that "superskin.pp" would overwrite the files that it wants to patch, for example textures in specific weapons.

This can also be used to patch the game. Instead of forcing to update one huge file when a small change occurs, developers can release the small file as its own .pp file that patches only the thing that needs updating.

Archive management tool is not yet developed, so while the engine supports this kind of behaviour, it is currently complicated to implement in practice.


Important tips to remember
==========================

###Adding files

To make sure all platform builds works, do not add source/header files directly from the visual studio. Instead go to the src/game/ folder and create a new file. Then drag&drop that file into the solution explorer. This way all the game code is under the src/game/ folder and doesn't go into the windows/ folder.

Alternatively you can try to remember to change the path when adding new path in visual studio.

###Folders for assets

Subfolders for assets are not fully tested and might break during release builds. This might be fixed by the time it could be an issue.

###C++11

C++11 is not supported, this is to ensure platform compatibility, and there isn't any real reason to use it.

###Globals and singletons

Do not use them, thats a bad idea in general and it will break the tools for the engine. If you want to keep state outside of components, place it to system. If you want to keep it outside of system, you are doing something wrong.

###Font rendering

Font rendering is currently missing and its coming back at some point. (?)

###Basics of building

* Right click the "standalone" project, set as default startup project
* Set solution configuration to "GameDebug/GameDevelopment" (top toolbar)
* Set platform to Win32 (top toolbar)
* Right click Standalone -> properties -> Debugging -> Working directory = "../../bin/"

After this press F5.

If there are errors about missing libs, the project dependencies are most likely broken. This can be easily fixed by manually building the libs that are failing.

For example if jsoncpp.lib is missing, right click jsoncpp project and build it. After that try to launch the project again. Repeat if necessary.