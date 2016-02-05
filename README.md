![Propeller](http://i.imgur.com/CyEu5EB.png)

![Screenshot](http://laurimakinen.net/img/propeller1.png)

This is the opensource/public version of the PropellerEngine. To understand more about the history of this project. The engine is result of almost 2 years of part-time development from one programmer.

**For more information about the engine, I recommend you to read the [postmortem](http://devblog.laurimakinen.net/2016/01/propellerengine-postmortem/).**

Main features that have been working

* Integrated editor written in C#
* Fully working entity/component/system
* Property system
* Full serialization support of game state
* Multiplatform input system with binds (Gamepad support, etc)
* Flexible cvar/command system
* RCC++ (Currently disabled due to some issues)
* 2D/3D Rendering with D3D11 and OpenGL
* Automated shader pipeline
* Custom archive formats
* 2D physics using Box2D
* 3D physics using Bullet
* And a lot of stuff you can expect from a game-engine

So far the engine has support for the following platforms:

* Windows
* Linux
* Mac
* HTML5
* Android
* PS4

Due to licensing, PS4 code is removed from the engine. Mac and HTML5 versions have not been fully maintained lately.

Thirdparty libraries used:

* Boost 1.55
* Box2D
* Bullet
* catch.h
* DirectXTK
* glew
* JsonCpp
* LodePNG
* stb_truetype.h
* xxhash
