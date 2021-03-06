#include "j1App.h"
#include "p2Defs.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Quadtree.h"

QuadtreeNode::QuadtreeNode(SDL_Rect area, QuadtreeNode* parent) : area(area), parent(parent)
{
	for (int i = 0; i < CHILDS_NUM; i++)
		childs[i] = nullptr;
	for (int i = 0; i < MAX_ENTITIES; i++)
		entities[i].SetToZero();

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
}

void QuadtreeNode::DrawQuadtreeArea()
{
	//Draws quad
	App->render->DrawQuad(area, QUAD_COLOR, false, false);
	//Draws Points
	for (int i = 0; i < MAX_ENTITIES; i++)
		DrawEntity(&entities[i]);

	//Calls children
	for (int i = 0; i < CHILDS_NUM; i++)
		if (childs[i] != nullptr)
			childs[i]->DrawQuadtreeArea();
}

bool QuadtreeNode::IsInside(const iPoint pos)
{
	if (area.x <= pos.x && pos.x <= (area.w + area.x) &&
		area.y <= pos.y && pos.y <= (area.h + area.y))
		return true;
	return false;
}

void QuadtreeNode::DrawEntity(const iPoint* entities)
{
	App->render->DrawCircle(entities->x, entities->y, 1, POINTS_COLOR, false);
}

void QuadtreeNode::AddEntity(const iPoint& entity)
{
	//If the quad is not subdivided
	if (childs[0] == nullptr)
	{
		if (!entities[MAX_ENTITIES - 1].IsZero())
		{
			SubDivide(entity);
		}

		else
		{
			for (int i = 0; i < MAX_ENTITIES; i++)
				if (entities[i].IsZero())
				{
					entities[i] = entity;
					break;
				}
		}
	}
	//If it is we search the correct child which is not
	else
		PushToChild(entity);
}

void QuadtreeNode::PushToChild(const iPoint& entity)
{
	for (int i = 0; i < CHILDS_NUM; i++)
		if (childs[i]->IsInside(entity))
			childs[i]->AddEntity(entity);
}

void QuadtreeNode::SubDivide(const iPoint entity)
{
	SDL_Rect top_left = { area.x,						  area.y,						 ceil(area.w / 2.0f),  ceil(area.h / 2.0f) };
	SDL_Rect top_right = { area.x + ceil(area.w / 2.0f),  area.y,						 ceil(area.w / 2.0f),  ceil(area.h / 2.0f) };
	SDL_Rect bot_left = { area.x,						  area.y + ceil(area.h / 2.0f),  ceil(area.w / 2.0f),  ceil(area.h / 2.0f) };
	SDL_Rect bot_right = { area.x + ceil(area.w / 2.0f),  area.y + ceil(area.h / 2.0f),	 ceil(area.w / 2.0f),  ceil(area.h / 2.0f) };

	childs[0] = new QuadtreeNode(top_left, this);
	childs[1] = new QuadtreeNode(top_right, this);
	childs[2] = new QuadtreeNode(bot_left, this);
	childs[3] = new QuadtreeNode(bot_right, this);
	App->scene->QTSubdivision();

	//Realocate all the points in the new quads
	for (int i = 0; i < MAX_ENTITIES; i++)
		PushToChild(entities[i]);

	//Allocate the new point
	PushToChild(entity);
}

Quadtree::Quadtree(SDL_Rect area)
{
	origin = new QuadtreeNode(area, nullptr);
}

Quadtree::~Quadtree()
{
	DELETE_PTR(origin);
}

bool Quadtree::PushBack(const iPoint pos)
{
	if (origin->IsInside(pos))
	{
		origin->AddEntity(pos);
		entities_num++;
		return true;
	}
	return false;
}

void Quadtree::DrawQuadtree()
{
	origin->DrawQuadtreeArea();
}

int Quadtree::GetNumOfEntities()
{
	return entities_num;
}

void Quadtree::ResetQuadtree(QuadtreeNode* node)
{
	for (int i = 0; i < CHILDS_NUM; i++)
	{
		if (node->childs[i] != nullptr)
		{
			ResetQuadtree(node->childs[i]);
			node->childs[i] = nullptr;
		}
	}

	DELETE_PTR(node);
}

QuadtreeNode * Quadtree::GetOrigin() const
{
	return origin;
}
