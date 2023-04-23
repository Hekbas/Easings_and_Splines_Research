#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneEasings.h"
#include "SceneSplines.h"
#include "Fonts.h"
#include "Easing.h"

#include "Defs.h"
#include "Log.h"

SceneEasings::SceneEasings(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
SceneEasings::~SceneEasings()
{}

// Called before render is available
bool SceneEasings::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneEasings::Start()
{
	LOG("Starting Scene");
	bool ret = true;

	easing = new Easing();

	// Set var
	app->win->GetWindowSize(windowResolution.x, windowResolution.y);

	screenCenter.x = windowResolution.x / 2;
	screenCenter.y = windowResolution.y / 2;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	easingTypeCount = 0;
	easingElapsedTime = 0;

	return ret;
}

// Called each loop iteration
bool SceneEasings::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneEasings::Update(float dt)
{
	//Camera movement
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) { app->render->camera.y++; }
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) { app->render->camera.y--; }
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) { app->render->camera.x++; }
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) { app->render->camera.x--; }

	// Limit FPS
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		app->render->limitFPS = !app->render->limitFPS;


	//Draw grid
	DrawGrid(0, 0, 100, 128, 128, 128, 48);


	//Easing
	double easingAnimationTime = 2;

	if (easingElapsedTime < easingAnimationTime)
	{
		easingElapsedTime += dt/1000;
	}
	else
	{
		easingElapsedTime = 0;
		easingTypeCount++;
		functionPoints.Clear();

		if (easingTypeCount == 30)
		{
			easingTypeCount = 0;
		}
	}
	double t = easingElapsedTime / easingAnimationTime;
	double easedT = easing->EasingAnimation(300, 900, t, (EasingType)easingTypeCount);
	app->render->DrawCircle(easedT, 300, 20, 255, 0, 0, 255, true);

	//Draw function points
	iPoint point = { (int)easedT, (int)(600 - (t * 300)) };
	functionPoints.Add(point);

	for (size_t i = 0; functionPoints.At(i) != NULL; i++)
	{
		app->render->DrawCircle(functionPoints.At(i)->data.x, functionPoints.At(i)->data.y, 1, 255, 255, 255, 128, true);
	}

	//Info
	std::string string = std::string("- EASINGS -");
	app->fonts->BlitText(800, 50, 0, string.c_str(), false);

	string = std::string("") + GetEasingTypeString((EasingType)easingTypeCount);
	app->fonts->BlitText(100, 50, 0, string.c_str(), false);

	string = std::string("") + std::to_string(easingElapsedTime);
	app->fonts->BlitText(100, 100, 0, string.c_str(), false);

	
	return true;
}

// Called each loop iteration
bool SceneEasings::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		app->sceneEasings->Disable();
		app->sceneSplines->Enable();
	}

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneEasings::CleanUp()
{
	LOG("Freeing scene");

	functionPoints.Clear();
	delete easing;

	return true;
}

void SceneEasings::DrawGrid(int OX, int OY, int gridSpacing, uchar r, uchar g, uchar b, uchar a)
{
	uint sizeX = 1;
	uint sizeY = 1;

	app->win->GetWindowSize(sizeX, sizeY);

	uint gridStepsX = sizeX / gridSpacing + 1;
	uint gridStepsY = sizeY / gridSpacing + 1;

	for (size_t i = 0; i < gridStepsX; i++)
	{
		app->render->DrawLine(OX + i * gridSpacing, 0, OX + i * gridSpacing, sizeY, r, g, b, a);
	}
	for (size_t i = 0; i < gridStepsY; i++)
	{
		app->render->DrawLine(0, OY + i * gridSpacing, sizeX, OY + i * gridSpacing, r, g, b, a);
	}
}

const char* SceneEasings::GetEasingTypeString(EasingType easingType)
{
	switch (easingType)
	{
	case EasingType::EASE_IN_SIN:			return "SIN (IN)";
	case EasingType::EASE_OUT_SIN:			return "SIN (OUT)";
	case EasingType::EASE_INOUT_SIN:		return "SIN (INOUT)";
	case EasingType::EASE_IN_QUAD:			return "QUAD (IN)";
	case EasingType::EASE_OUT_QUAD:			return "QUAD (OUT)";
	case EasingType::EASE_INOUT_QUAD:		return "QUAD (INOUT)";
	case EasingType::EASE_IN_CUBIC:			return "CUBIC (IN)";
	case EasingType::EASE_OUT_CUBIC:		return "CUBIC (OUT)";
	case EasingType::EASE_INOUT_CUBIC:		return "CUBIC (INOUT)";
	case EasingType::EASE_IN_QUART:			return "QUART (IN)";
	case EasingType::EASE_OUT_QUART:		return "QUART (OUT)";
	case EasingType::EASE_INOUT_QUART:		return "QUART (INOUT)";
	case EasingType::EASE_IN_QUINT:			return "QUINT (IN)";
	case EasingType::EASE_OUT_QUINT:		return "QUINT (OUT)";
	case EasingType::EASE_INOUT_QUINT:		return "QUINT (INOUT)";
	case EasingType::EASE_IN_EXP:			return "EXP (IN)";
	case EasingType::EASE_OUT_EXP:			return "EXP (OUT)";
	case EasingType::EASE_INOUT_EXP:		return "EXP (INOUT)";
	case EasingType::EASE_IN_CIRC:			return "CIRC (IN)";
	case EasingType::EASE_OUT_CIRC:			return "CIRC (OUT)";
	case EasingType::EASE_INOUT_CIRC:		return "CIRC (INOUT)";
	case EasingType::EASE_IN_BACK:			return "BACK (IN)";
	case EasingType::EASE_OUT_BACK:			return "BACK (OUT)";
	case EasingType::EASE_INOUT_BACK:		return "BACK (INOUT)";
	case EasingType::EASE_IN_ELASTIC:		return "ELASTIC (IN)";
	case EasingType::EASE_OUT_ELASTIC:		return "ELASTIC (OUT)";
	case EasingType::EASE_INOUT_ELASTIC:	return "ELASTIC (INOUT)";
	case EasingType::EASE_IN_BOUNCE:		return "BOUNCE (IN)";
	case EasingType::EASE_OUT_BOUNCE:		return "BOUNCE (OUT)";
	case EasingType::EASE_INOUT_BOUNCE:		return "BOUNCE (INOUT)";
	default: return "UKNOWN";
	}
}