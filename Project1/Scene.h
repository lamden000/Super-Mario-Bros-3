#pragma once
#include "KeyEventHandler.h"
#include <vector>
using namespace std;
/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual int GetId() { return id; };
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void SetTimeLimit(DWORD timeLimit) = 0;
};
typedef CScene* LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;
