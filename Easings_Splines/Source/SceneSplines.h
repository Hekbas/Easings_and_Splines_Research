#ifndef __SCENE_EASINGS_H__
#define __SCENE_EASINGS_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"
#include "Spline.h"

struct SDL_Texture;

class SceneSplines : public Module
{
public:

	SceneSplines(bool startEnabled);

	// Destructor
	virtual ~SceneSplines();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Draws grid based on window size
	void DrawGrid(int OX, int OY, int gridSpacing, uchar r = (255), uchar g = (255), uchar b = (255), uchar a = (255));

public:

	uiPoint windowResolution;
	uiPoint screenCenter;

	int easingTypeCount = 0;
	double easingElapsedTime = 0;


private:

	Spline* spline;
};

#endif // __SCENE_EASINGS_H__