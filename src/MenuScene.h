#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
private:
	Ranking ranking;

public:
	MenuScene();


	//Logica de la escena
	void Update(double dt, Inputs* input, Audio* audio);
	void Draw();

	~MenuScene();
};

