#pragma once
#include "Renderer.h"
#include "Inputs.h"
#include "Audio.h"
#include "Ranking.h"

class Scene
{
public:
	enum class SceneState {
		UPDATE,
		GOTO_PLAY, GOTO_MENU, RESTART,
		EXIT
	};

protected:
	SceneState sceneState;

public:
	Scene();
	virtual void Update(double dt, Inputs* input, Audio* audio) = 0;
	virtual void Draw() = 0;
	virtual SceneState GetState();
};

