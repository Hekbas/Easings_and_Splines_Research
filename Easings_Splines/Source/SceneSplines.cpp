
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Fonts.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneEasings.h"
#include "SceneSplines.h"
#include "Easing.h"

#include "Defs.h"
#include "Log.h"

SceneSplines::SceneSplines(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
	spline = new Spline();
}

// Destructor
SceneSplines::~SceneSplines()
{
	delete spline;
}

// Called before render is available
bool SceneSplines::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneSplines::Start()
{
	LOG("Starting Scene");
	bool ret = true;

	// Get xml node
	pugi::xml_node configNode = app->LoadConfigFileToVar();
	pugi::xml_node config = configNode.child(name.GetString());

	// Load font
	font_text = app->fonts->Load(config.child("texturepaths").attribute("font").as_string(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.,;:$#'! /?%&()@ -+=      ", 7);

	// Set var
	app->win->GetWindowSize(windowResolution.x, windowResolution.y);

	screenCenter.x = windowResolution.x / 2;
	screenCenter.y = windowResolution.y / 2;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	//Splines

	for (int i = 0; i < 5; i++)
	{
		spline->points.Add({100 + 100*i, 400});
	}

	return ret;
}

// Called each loop iteration
bool SceneSplines::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneSplines::Update(float dt)
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

	//Splines
	for (size_t i = 0; spline->points.At(i) != NULL; i++)
	{
		int posX = spline->points.At(i)->data.x;
		int posY = spline->points.At(i)->data.y;

		app->render->DrawCircle(posX, posY, 6, 255, 0, 0, 255, true);
		app->fonts->BlitText(posX, posY, 0, std::to_string(i).c_str(), false);
	}

	//Debug
	std::string string = std::string("EASING TYPE:  ") + std::to_string(20);
	app->fonts->BlitText(200, 50, 0, string.c_str(), false);

	string = std::string("ELAPSED TIME: ") + std::to_string(easingElapsedTime);
	app->fonts->BlitText(200, 100, 0, string.c_str(), false);


	return true;
}

// Called each loop iteration
bool SceneSplines::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		app->sceneSplines->Disable();
		app->sceneEasings->Enable();
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneSplines::CleanUp()
{
	LOG("Freeing scene");

	app->audio->PlayMusic("");

	return true;
}

void SceneSplines::DrawGrid(int OX, int OY, int gridSpacing, uchar r, uchar g, uchar b, uchar a)
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