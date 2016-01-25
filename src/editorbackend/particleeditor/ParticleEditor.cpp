// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/particleeditor/ParticleEditor.h"
#include "engine/GameInstance.h"

#include "game/Propeller.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(ParticleEditor);

	bool ParticleEditor::init()
	{
		// Create instance for the particle simulation
		instance = new PrimaryGameInstance();

		registerEvent("update", this, &ParticleEditor::update);
		registerEvent("initRender", this, &ParticleEditor::initRender);

		return true;
	}

	void ParticleEditor::uninit()
	{
		instance->uninit();
		delete instance;
	}

	void ParticleEditor::update()
	{
		instance->update();
	}

	void ParticleEditor::initRender(intptr_t hwnd)
	{
		instance->initializeRenderer(hwnd);
		instance->init();

		instance->getConsole()->execute("scene default");

		LOG_INFO("[ParticleEditor] init");
		// setup the particle here!
	}

}