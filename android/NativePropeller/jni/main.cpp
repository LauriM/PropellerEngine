#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/log.h>
#include <android/input.h>
#include <android_native_app_glue.h>

#include "engine/precompiled.h"
#include "AndroidLogger.h"

#include "engine/input/AndroidInputSystem.h"

#include "game/Propeller.h"
#include "engine/file/AndroidAssetManagerArchive.h"

#include "engine/input/KeyCodes.h"

/*
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
*/

struct engineState {
	struct android_app* app;

	PrimaryGameInstance *instance;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	int32_t width;
	int32_t height;

	bool focus;
};

static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	struct engineState* engine = (struct engineState*)app->userData;

	if (cmd == APP_CMD_INIT_WINDOW)
	{
		if (engine->app->window != NULL) {
			engine::sys::addLogger(new android::AndroidLogger());

			engine->instance = new PrimaryGameInstance();

			engine->instance->setAndroidApp(app);

			LOG_INFO("engine->app->window: " << (void*)engine->app->window);
			engine->instance->initializeRenderer((intptr_t)engine->app->window);
			engine->instance->init();

			engine->instance->getConsole()->execute("set dimensions 2");
			engine->instance->getConsole()->execute("axis TOUCH_MOVE_X cameraRotateX");
			engine->instance->getConsole()->execute("axis TOUCH_MOVE_Y cameraRotateY");
			engine->instance->getConsole()->execute("bind TOUCH playerTouch");

			engine->instance->getConsole()->execute("bind BUTTON_Y playerup");
			engine->instance->getConsole()->execute("bind BUTTON_A playerdown");
			engine->instance->getConsole()->execute("bind BUTTON_X playerleft");
			engine->instance->getConsole()->execute("bind BUTTON_B playerright");

			engine->instance->getConsole()->execute("scene phys");
		}

		return;
	}

	if (cmd == APP_CMD_WINDOW_REDRAW_NEEDED)
	{
		engine->instance->update();
	}

	if (cmd == APP_CMD_LOST_FOCUS)
	{
		engine->focus = false;
		LOG_INFO("[NativePropeller] Lost focus, not running the engine!");
	}

	if (cmd == APP_CMD_GAINED_FOCUS)
	{
		engine->focus = true;
		LOG_INFO("[NativePropeller] Gained focus!");
	}
}

enum {
	AXIS_LTHUMBSTICK = 0,
	AXIS_RTHUMBSTICK,
	AXIS_LTRIGGER,
	AXIS_RTRIGGER,
	AXIS_POVHAT,
	AXIS_COUNT
};

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) 
{
	struct engineState* engine = (struct engineState*)app->userData;

	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) 
	{

		int source = AInputEvent_getSource(event);

		if (source == AINPUT_SOURCE_TOUCHSCREEN)
		{
			float x = AMotionEvent_getX(event, 0);
			float y = AMotionEvent_getY(event, 0);

			engine->instance->getAndroidInputSystem()->handleTouchInput(x, y);

			return 1;
		}

		if (source == AINPUT_SOURCE_JOYSTICK)
		{
			float x = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_X, 0);
			float y = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Y, 0);

			int devId = AInputEvent_getDeviceId(event);

			LOG_INFO("dev: " << devId << " pos: " << x << ":" << y);
		}

		return 0;
	}

	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) 
	{
		int32_t source = AInputEvent_getSource(event);
		int32_t code = AKeyEvent_getKeyCode(event);
		int32_t action = AKeyEvent_getAction(event);

		LOG_INFO("Code: " << code << " Action: " << action);

		engine::input::KeyCode keycode = engine::input::KEY_VOID;

		switch (code)
		{
			case 96:
				keycode = engine::input::BUTTON_A;
				break;
			case 99:
				keycode = engine::input::BUTTON_X;
				break;
			case 100:
				keycode = engine::input::BUTTON_Y;
				break;
			case 97:
				keycode = engine::input::BUTTON_B;
				break;
		}

		if (action == 1)
			engine->instance->getInputSystem()->keyUp(keycode);
		else
			engine->instance->getInputSystem()->keyDown(keycode);

		return 1;
	}

	return 0;
}

void android_main(struct android_app* state) {
	struct engineState engine;
	engine.instance = NULL;

	app_dummy();

	memset(&engine, 0, sizeof(engine));
	engine.app = state;

	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.focus = true;

	while (1) {
		int ident;
		struct android_poll_source* source;

		while ((ident = ALooper_pollAll(0, NULL, NULL, (void**)&source)) >= 0) {

			if (source != NULL)
				source->process(state, source);

			// Check if we are exiting.
			if (state->destroyRequested != 0) {
				engine.instance->getConsole()->execute("stats");
				engine.instance->getConsole()->execute("quit");

				delete engine.instance; // should do cleanup and stuff
				return;
			}
		}

		if (engine.focus) // only run when context
		{
			if (engine.instance != NULL)
				engine.instance->update();
		}
	}
}
