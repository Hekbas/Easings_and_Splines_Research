#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"
#include "Easing.h"

struct SDL_Texture;

class SceneEasings : public Module
{
public:

	SceneEasings(bool startEnabled);

	// Destructor
	virtual ~SceneEasings();

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

	const char* GetEasingTypeString(EasingType easingType);

public:

	uiPoint windowResolution;
	uiPoint screenCenter;

	int easingTypeCount = 0;
	double easingElapsedTime = 0;

	List<iPoint> functionPoints;

private:
	Easing* easing;
	int font_text;

};

#endif // __SCENE_H__