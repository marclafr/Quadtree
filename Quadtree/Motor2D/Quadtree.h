#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "SDL\include\SDL_rect.h"
#include "p2Point.h"

#define MAX_ENTITIES 3
#define CHILDS_NUM 4
#define QUAD_COLOR 255, 0, 0, 255

class QuadtreeNode
{
public:
	QuadtreeNode(SDL_Rect area, QuadtreeNode* parent);
	~QuadtreeNode();

	void DrawQuadtreeArea();
	
private:
	QuadtreeNode* parent = nullptr;
	QuadtreeNode* childs[CHILDS_NUM];
	SDL_Rect area;
	iPoint* entities[MAX_ENTITIES];
};

class Quadtree
{
public:

	Quadtree(SDL_Rect area);
	~Quadtree();

	void DrawQuadtree();

private:
	QuadtreeNode* origin = nullptr;
	
};

#endif // __QUADTREE_H__