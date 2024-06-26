#pragma once

#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"

class CPlayScene : public CScene
{
protected:
	DWORD timeLimit;
	bool isLevelEnded;
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	virtual void _ParseSection_OBJECTS(string line);
	void _ParseSection_ASSETS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath, DWORD timeLimit = 300000);
	virtual void AddObject(LPGAMEOBJECT object, int id=-1);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	DWORD GetTimeLimit(){ return timeLimit; }
	virtual void SetTimeLimit(DWORD timeLimit) { this->timeLimit = timeLimit; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	bool IsObjectStillThere(const LPGAMEOBJECT& o);
	void EndLevel() { isLevelEnded = true; }
	bool IsLevelEnded() { return isLevelEnded; }
};

typedef CPlayScene* LPPLAYSCENE;


