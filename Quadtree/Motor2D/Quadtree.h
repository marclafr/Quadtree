#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "SDL\include\SDL_rect.h"
#include "p2Point.h"

#define MAX_ENTITIES 3
#define CHILDS_NUM 4
#define QUAD_COLOR 0, 255, 0, 255	// R, G, B, ALPHA
#define POINTS_COLOR 255, 255, 255, 255 // R, G, B, ALPHA

class QuadtreeNode;

class Quadtree
{
public:

	Quadtree(SDL_Rect area);
	~Quadtree();

	bool PushBack(iPoint pos);
	void DrawQuadtree();

private:
	QuadtreeNode* origin = nullptr;	
};

	 //----------------||------------------||----------------\\
	//----------------||Quadtree Nodes Class||----------------\\
   //----------------||______________________||----------------\\

class QuadtreeNode
{
	friend Quadtree;

public:
	QuadtreeNode(SDL_Rect area, QuadtreeNode* parent);
	~QuadtreeNode();

	void DrawQuadtreeArea();
	bool IsInside(const iPoint pos);

private:
	QuadtreeNode* parent = nullptr;
	QuadtreeNode* childs[CHILDS_NUM];
	SDL_Rect area;
	iPoint entities[MAX_ENTITIES];

	void DrawEntity(iPoint entities);
	void AddEntity(iPoint entity);
	void PushToChild(iPoint entity);
	void SubDivide(iPoint entity);
};

//	\\----------------||______________________||----------------//
//	  \\----------------||__________________||----------------//
//		\\----------------||--------------||----------------//

#endif // __QUADTREE_H__