#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Fonts.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneEasings.h"
#include "SceneSplines.h"
#include "SceneUIAnimation.h"
#include "Easing.h"

#include "Defs.h"
#include "Log.h"

SceneUIAnimation::SceneUIAnimation(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneUIAnimation");
}

// Destructor
SceneUIAnimation::~SceneUIAnimation()
{
}

// Called before render is available
bool SceneUIAnimation::Awake()
{
	LOG("Loading sceneUIAnimation");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneUIAnimation::Start()
{
	LOG("Starting sceneUIAnimation");
	bool ret = true;

	easingPause = new Easing(1);

	// Get xml node
	pugi::xml_node configNode = app->GetNode();
	pugi::xml_node config = configNode.child(name.GetString());

	// Set var
	app->win->GetWindowSize(windowResolution.x, windowResolution.y);

	screenCenter.x = windowResolution.x / 2;
	screenCenter.y = windowResolution.y / 2;

	app->render->camera.x = 0;
	app->render->camera.y = 0;


	return ret;
}

// Called each loop iteration
bool SceneUIAnimation::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneUIAnimation::Update(float dt)
{
	// Draw grid
	DrawGrid(0, 0, 100, 128, 128, 128, 48);


	// UI ANIMATION ==========================

	//Input
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		bPause = !bPause;
		easingPause->SetFinished(false);
	}

	if (!easingPause->GetFinished()) // Animation not finished? 
	{
		int a, b;
		EasingType easing;

		if (bPause)
		{
			a = 50;
			b = 150;
			easing = EasingType::EASE_OUT_ELASTIC;
		}
		else
		{
			a = 150;
			b = -50;
			easing = EasingType::EASE_IN_EXP;
		}

		double t = easingPause->TrackTime(dt);
		double easedY = easingPause->EasingAnimation(a, b, t, easing);

		SDL_Rect pauseBox = { 450, easedY, 300, 400 };
		app->render->DrawRectangle(pauseBox, 0, 255, 0, 255, false);
		app->render->DrawRectangle(pauseBox, 0, 255, 0, 64, true);
	}
	else if (bPause)
	{
		SDL_Rect pauseBox = { 450, 150, 300, 400 };
		app->render->DrawRectangle(pauseBox, 0, 255, 0, 255, false);
		app->render->DrawRectangle(pauseBox, 0, 255, 0, 64, true);
	}

	// =======================================
	
	//Info
	std::string string = std::string("- UI ANIMATION -");
	app->fonts->BlitText(800, 50, 0, string.c_str(), false);


	// Limit FPS
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		app->render->limitFPS = !app->render->limitFPS;


	return true;
}

// Called each loop iteration
bool SceneUIAnimation::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		this->Disable();
		app->sceneEasings->Enable();
	}
	else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		this->Disable();
		app->sceneSplines->Enable();
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneUIAnimation::CleanUp()
{
	LOG("Freeing sceneUIAnimation");


	return true;
}

void SceneUIAnimation::DrawGrid(int OX, int OY, int gridSpacing, uchar r, uchar g, uchar b, uchar a)
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