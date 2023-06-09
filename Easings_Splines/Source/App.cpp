#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "SceneEasings.h"
#include "SceneSplines.h"
#include "sceneUIAnimation.h"
#include "Fonts.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	win = new Window(true);
	input = new Input(true);
	tex = new Textures(true);
	fonts = new Fonts(true);
	audio = new Audio(true);
	sceneEasings = new SceneEasings(true);
	sceneSplines = new SceneSplines(false);
	sceneUIAnimation = new SceneUIAnimation(false);
	render = new Render(true);


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(fonts);
	AddModule(audio);
	AddModule(sceneEasings);
	AddModule(sceneSplines);
	AddModule(sceneUIAnimation);

	// Render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	// Measure the amount of ms that takes to execute the Awake and LOG the result
	timer = Timer();

	maxFrameDuration = 16;

	//Load config from XML
	bool ret = LoadConfig();

	if(ret == true)
	{
		//Read the title from the config file
		title = configNode.child("app").child("title").child_value();

		ListItem<Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			// Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			pugi::xml_node node = configNode.child(item->data->name.GetString());
			ret = item->data->Awake(node);
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{
	// Measure the amount of ms that takes to execute the App Start() and LOG the result
	timer.Start();
	startupTime.Start();
	lastSecFrameTime.Start();

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if (item->data->IsEnabled()) { ret = item->data->Start(); }
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
bool App::LoadConfig()
{
	bool ret = false;

	// Load config.xml file using load_file() method from the xml_document class
	pugi::xml_parse_result parseResult = configFile.load_file("config.xml");

	// Check result for loading errors
	if (parseResult) {
		ret = true;
		configNode = configFile.child("config");
	}
	else {
		LOG("Error in App::LoadConfig(): %s", parseResult.description());
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameTime.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// Amount of frames since startup
	frameCount++;

	// Amount of ms took the last update
	dt = frameTime.ReadMSec();

	// Amount of frames during the last second
	lastSecFrameCount++;

	if (lastSecFrameTime.ReadMSec() > 1000)
	{
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	//vsync
	if (app->render->limitFPS)
	{
		float delay = float(maxFrameDuration) - dt;

		if (maxFrameDuration > 0 && delay > 0) {
			SDL_Delay(delay);
			dt = maxFrameDuration;
		}
	}

	// Shows the time measurements in the window title
	static char title[256];
	sprintf_s(title, 256, "FPS: %i | dt: %.3f | V-Sync: %s",
		framesPerSecond, dt, app->render->limitFPS ? "ON" : "OFF");
	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->state == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;

	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->state == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->state == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		if (item->data->IsEnabled() == true) { ret = item->data->CleanUp(); }
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

pugi::xml_node App::GetNode()
{
	pugi::xml_node node;
	pugi::xml_parse_result parseResult = configFile.load_file("config.xml");

	if (parseResult)
		node = configFile.child("config");
	else
		LOG("Error in App::LoadConfig(): %s", parseResult.description());

	return node;
}