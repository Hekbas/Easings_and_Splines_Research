
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

SceneSplines::SceneSplines(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneSplines");
}

// Destructor
SceneSplines::~SceneSplines()
{
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

	spline = new Spline(8);

	// Get xml node
	pugi::xml_node configNode = app->GetNode();
	pugi::xml_node config = configNode.child(name.GetString());

	// Set var
	app->win->GetWindowSize(windowResolution.x, windowResolution.y);

	screenCenter.x = windowResolution.x / 2;
	screenCenter.y = windowResolution.y / 2;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	//Spline Nodes

	for (int i = 0; i < 10; i++)
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
	// Draw grid
	DrawGrid(0, 0, 100, 128, 128, 128, 48);


	// SPLINES ============================
	// Handle input
	double speed = 3 * (dt / 16);
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) { spline->points.At(spline->selectedPoint)->data.x -= speed; }
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) { spline->points.At(spline->selectedPoint)->data.x += speed; }
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) { spline->points.At(spline->selectedPoint)->data.y -= speed; }
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) { spline->points.At(spline->selectedPoint)->data.y += speed; }

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		if (++spline->selectedPoint == spline->points.Count())
			spline->selectedPoint = 0;

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		if (--spline->selectedPoint < 0)
			spline->selectedPoint = spline->points.Count() - 1;

	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) { cameraFollowSpline = !cameraFollowSpline; }

	
	// Calculate Spline point and set camera position
	if (cameraFollowSpline)
	{
		// TODO 2: Make the camera follow the spline
		// Remember tracktime, GetSplinePoint
		// tips: screenCenter, camera swapped (+/-)
		

	}	

	// Draw spline
	for (double t = 0.0f; t < spline->points.Count()-3; t += 0.01f)
	{
		iPoint point = spline->GetSplinePoint(t, false);
		app->render->DrawCircle(point.x, point.y, 1, 255, 255, 255, 128, true);
	}

	// Draw points + num
	for (size_t i = 0; spline->points.At(i) != NULL; i++)
	{
		int posX = spline->points.At(i)->data.x;
		int posY = spline->points.At(i)->data.y;

		app->render->DrawCircle(posX, posY, 6, 255, 0, 0, 255, true, true);
		app->fonts->BlitText(posX, posY, 0, std::to_string(i).c_str(), true);
	}

	//Highlight selectedPoint
	app->render->DrawCircle(spline->points.At(spline->selectedPoint)->data.x, spline->points.At(spline->selectedPoint)->data.y, 6, 255, 255, 0, 255, true, true);

	//======================================
	

	//Info
	std::string string = std::string("- SPLINES -");
	app->fonts->BlitText(800, 50, 0, string.c_str(), false);

	string = std::string("NODES: ") + std::to_string(spline->points.Count());
	app->fonts->BlitText(100, 50, 0, string.c_str(), false);

	string = std::string("") + std::to_string(spline->GetElapsedTime());
	app->fonts->BlitText(100, 100, 0, string.c_str(), false);

	// Limit FPS
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		app->render->limitFPS = !app->render->limitFPS;


	return true;
}

// Called each loop iteration
bool SceneSplines::PostUpdate()
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
		app->sceneUIAnimation->Enable();
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneSplines::CleanUp()
{
	LOG("Freeing scene");

	delete spline;

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