#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Platform.h"

#define PIPE_ORIENTATION_UP	1
#define PIPE_ORIENTATION_DOWN	3

#define PIPE_SCALEX 0.32
#define PIPE_SCALEY 0.32

class CPipe : public CPlatform {
protected:
	int orientation;
	int height;
public:
	CPipe(float x, float y, float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end,  float scaleX, float ScaleY,int height,int orientation) : CPlatform(x,y,
			cell_width, cell_height, length,
		 sprite_id_begin, sprite_id_middle,sprite_id_end,scaleX,ScaleY)
	{
		this->height = height;
		this->orientation = orientation;
	}
	int IsDirectionColliable(float nx, float ny) { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	void Render();
};

