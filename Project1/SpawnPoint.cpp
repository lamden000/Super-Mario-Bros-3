#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Luigi.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "Bush.h"
#include "Koopas.h"
#include "GreenKoopas.h"
#include "SpawnPoint.h"
#include "QuestionBlock.h"
#include "Cloud.h"
#include "RedGoomba.h"
#include "Pipe.h"
#include "Venus.h"
#include "Point.h"
#include "Box.h"
#include "Game.h"
#include "Textures.h"

CSpawnPoint::CSpawnPoint(float l, float t, float r, float b,string objectDetail)
{
	x = l;
	y = t;
	width = r - l;
	height = b - t;
	this->objectDetail = objectDetail;
}

void CSpawnPoint::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CSpawnPoint::Render()
{
	//RenderBoundingBox();
}


void CSpawnPoint::Spawn()
{
	_ParseSection_OBJECTS(objectDetail);
}


void CSpawnPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}

void CSpawnPoint::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_GOOMBA:obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_MUSHROOM: obj = new CMushroom(x, y); break;
	case OBJECT_TYPE_BACKGROUND_CLOUD:	obj = new CCloud(x, y); break;
	case OBJECT_TYPE_KOOPAS:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CBrownKoopas(x, y, level);
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
		obj = new CBush(x, y, height, sprite_begin, sprite_middle, sprite_end);
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
			sprite_begin, sprite_middle, sprite_end, scaleX, scaleY
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
		int orientation = atoi(tokens[9].c_str());
		int height = atoi(tokens[10].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end, 1, 1, orientation, height
		);

		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_SPAWNPOINT:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		string spawnObjectDetail = "";
		for (int i = 5; i < tokens.size(); i++)
		{
			spawnObjectDetail += tokens[i] + "	";
		}
		obj = new CSpawnPoint(x, y, r, b, spawnObjectDetail);
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
		float height = (float)atof(tokens[3].c_str());
		float width = (float)atof(tokens[4].c_str());
		int type = atoi(tokens[5].c_str());
		obj = new CBox(x, y, height, width, type);
	}
	break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(obj, 1);
}