#include "j1App.h"
#include "p2Defs.h"
#include "j1Render.h"
#include "Quadtree.h"

QuadtreeNode::QuadtreeNode(SDL_Rect area, QuadtreeNode* parent) : area(area), parent(parent)
{
	for (int i = 0; i < CHILDS_NUM; i++)
		childs[i] = nullptr;

	for (int i = 0; i < MAX_ENTITIES; i++)
		entities[i] = nullptr;
}

QuadtreeNode::~QuadtreeNode()
{
	for (int i = 0; i < CHILDS_NUM; i++)
	{
		if (childs[i] != nullptr)
		{
			DELETE_PTR(childs[i]);
		}
		else
			break;
	}

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] != nullptr)
		{
			DELETE_PTR(childs[i]);
		}
		else
			break;
	}
}

void QuadtreeNode::DrawQuadtreeArea()
{
	//Draws quad
	App->render->DrawQuad(area, QUAD_COLOR, false, false);

	//Calls children
	for (int i = 0; i < CHILDS_NUM; i++)
		if (childs[i] != nullptr)
			childs[i]->DrawQuadtreeArea();
}

Quadtree::Quadtree(SDL_Rect area)
{
	origin = new QuadtreeNode(area, nullptr);
}

Quadtree::~Quadtree()
{
	DELETE_PTR(origin);
}

void Quadtree::DrawQuadtree()
{
	origin->DrawQuadtreeArea();
}