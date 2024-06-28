#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "Bush.h"
#include "GreenKoopas.h"
#include "SpawnPoint.h"
#include "Cloud.h"
#include "RedGoomba.h"
#include "Pipe.h"
#include "Piranha.h"
#include "Point.h"
#include "InGameUI.h"
#include "Box.h"
#include "P_Switch.h"
#include "PlaySceneBackground.h"

#include "KeyEventHandlerForMario.h"

using namespace std;

#define MAIN_CAMERA_HEIGHT -15
#define SECRET_ROOM_CAMERA_HEIGHT 950

CPlayScene::CPlayScene(int id, LPCWSTR filePath,DWORD timeLimit) :
	CScene(id, filePath)
{
	player = NULL;
	this->timeLimit = timeLimit;
	isLevelEnded = false;
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::AddObject(LPGAMEOBJECT object, int id)
{

	if (id == -1)
		objects.push_back(object);
	else
		objects.insert(objects.begin() + id, object);
}
/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() <= 2) return;
	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	CGameObject* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		obj = new CMario(x, y);
		if (player == NULL)
		{
			key_handler = new CSampleKeyHandler(this);
			player = (CMario*)obj;
		}
		break;
	case OBJECT_TYPE_REDGOOMBA:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CRedGoomba(x, y, level);
		break;
	}
	case OBJECT_TYPE_VENUS:
	{
		int type = 1;
		if (tokens.size() > 3)
			type = (int)atof(tokens[3].c_str());
		obj = new CVenus(x, y, type);
		break;
	}
	case OBJECT_TYPE_PIRANHA:
	{
		int type = 1;
		if (tokens.size() > 3)
			type = (int)atof(tokens[3].c_str());
		obj = new CPiranha(x, y, type);
		break;
	}
	case OBJECT_TYPE_P_SWITCH:
	{
		obj = new CPSwitch(x, y);
		break;
	}
	case OBJECT_TYPE_GOLD_BLOCK:
	{
		int type = (int)atof(tokens[3].c_str());
		CGoldBlock* block = new CGoldBlock(x, y, type);
		obj = block;
		if (tokens.size()>4)
		{
			int PWitch_Id = (int)atof(tokens[4].c_str());
			CPSwitch* _switch =(CPSwitch*) objects[PWitch_Id];
			_switch->GetBrick(block);
		}
		break;
	}
	case OBJECT_TYPE_GOOMBA:obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_MUSHROOM: obj = new CMushroom(x, y); break;
	case OBJECT_TYPE_BACKGROUND_CLOUD:	obj = new CCloud(x, y); break;
	case OBJECT_TYPE_SCENE_UI:	obj = new CInGameUI(); break;
	case OBJECT_TYPE_KOOPAS:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CBrownKoopas(x, y,level);
		break;
	}
	case OBJECT_TYPE_GREENKOOPAS:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CGreenKoopas(x, y, level);
		break;
	}
	case OBJECT_TYPE_QUESTIONBLOCK: 
	{
		int type = (int)atof(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, type); 
		break;
	}
	case OBJECT_TYPE_BUSH: 
	{
		int height = atoi(tokens[3].c_str());
		int sprite_begin = atoi(tokens[4].c_str());
		int sprite_middle = atoi(tokens[5].c_str());
		int sprite_end = atoi(tokens[6].c_str());
		obj = new CBush(x, y,height,sprite_begin,sprite_middle,sprite_end);
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		float scaleX = 1;
		float scaleY = 1;
		if (tokens.size() > 9)
		{
			scaleX = atof(tokens[9].c_str());
			scaleY = atof(tokens[10].c_str());
		}
		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,scaleX,scaleY
		);

		break;
	}
	case OBJECT_TYPE_PIPE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int height = atoi(tokens[9].c_str());
		int orientation = PIPE_ORIENTATION_UP;
		if(tokens.size()>10)
			orientation = atoi(tokens[10].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,1,1, height, orientation
		);

		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		float tele_x = atof(tokens[5].c_str());
		float tele_y = atof(tokens[6].c_str());
		obj = new CPortal(x, y, r, b,tele_x,tele_y);
	}
	break;
	case OBJECT_TYPE_SPAWNPOINT:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		string spawnObjectDetail = "";
		for (int i = 5; i < tokens.size(); i++)
		{
			spawnObjectDetail += tokens[i]+"	";
		}
		obj = new CSpawnPoint(x, y, r, b,spawnObjectDetail);
	}
	break;
	case OBJECT_TYPE_POINT:
	{
		float value = (float)atof(tokens[3].c_str());
		obj = new CPoint(x, y, value);
	}
	break;
	case OBJECT_TYPE_BOX:
	{
		float height = atof(tokens[3].c_str());
		float width = atof(tokens[4].c_str());
		int type = atoi(tokens[5].c_str());
		obj = new CBox(x, y, height, width, type);
	}
	break;
	case OBJECT_TYPE_BACKGROUND:
	{
		int spriteId = atoi(tokens[3].c_str());
		float scaleX = atof(tokens[4].c_str());
		float scaleY = atof(tokens[5].c_str());
		obj = new CPlaySceneBackground(x, y, spriteId, scaleX, scaleY);
	}
		break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT>& coObjects = objects; 
	if (!objects.empty()) {
		CMario* player = (CMario*)objects.front();

		for (size_t i = 0; i < objects.size(); i++) {
			objects[i]->Update(dt, &coObjects);
		}
		float cx, cy;
		player->GetPosition(cx, cy);

		if (cx > 3010&&!isLevelEnded)
			player->SetPosition(3010, cy);

		CGame* game = CGame::GetInstance();
		int screenHeight = game->GetBackBufferHeight();

		if (player->GetState() == MARIO_STATE_DIE)
			return;

		if ((cy > MAIN_CAMERA_HEIGHT + screenHeight)&&!player->IsUnderGround())
		{
			player->SetState(MARIO_STATE_DIE);
			player->StartUntouchable();
		}

		if (player->IsUnderGround())
			cy= SECRET_ROOM_CAMERA_HEIGHT;
		else
		{
			if (cy < MAIN_CAMERA_HEIGHT + screenHeight / 5 && player->GetLevel() == MARIO_LEVEL_RACOON) 
				cy -= screenHeight / 4;
			else 
				cy = MAIN_CAMERA_HEIGHT;
		}
		cx -= game->GetBackBufferWidth() / 2;
		if (cx < 0)
			cx = 0;
		else if (cx > 2715)
			cx = 2715;
		game->SetCamPos(cx, cy);

	}	
	timeLimit -= dt;

	PurgeDeletedObjects();
}


void CPlayScene::Render()
{
	if (player->GetState() != MARIO_STATE_TRAVELLING_DOWN && player->GetState() != MARIO_STATE_TRAVELLING_UP)
	{
		for (int i = objects.size() - 1; i >= 0; i--)
		{
			objects[i]->Render();
		}
	}
	else
	{
		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (i == 0)
				continue;
			if (!dynamic_cast<CPipe*>(objects[i])|| !dynamic_cast<CInGameUI*>(objects[i]))
				objects[i]->Render();
		}

		objects[0]->Render();

		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (i == 0)
				continue;
			if (dynamic_cast<CPipe*>(objects[i]) || dynamic_cast<CInGameUI*>(objects[i]))
				objects[i]->Render();
		}
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

bool CPlayScene::IsObjectStillThere(const LPGAMEOBJECT& o)
{
	return std::find(objects.begin(), objects.end(), o) != objects.end();
}

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}