#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Window.h"
#include "Quadtree.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	quadtree = new Quadtree({ 0, 0, App->win->GetWindowWidth(), App->win->GetWindowHeight() });
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		iPoint mouse_pos;
		App->input->GetMousePosition(mouse_pos.x, mouse_pos.y);
		quadtree->PushBack(mouse_pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		Instert50Points();
	}

	quadtree->DrawQuadtree();
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

uint j1Scene::GetPointsInQuadtree()
{
	return quadtree->GetNumOfEntities();
}

uint j1Scene::GetQTDivisions()
{
	return qt_divisions;
}

void j1Scene::QTSubdivision()
{
	qt_divisions += 3;
}

void j1Scene::Instert50Points()
{
	for (int i = 0; i < 50; i++)
	{
		int rand_x = rand() % App->win->GetWindowWidth() - 1;
		int rand_y = rand() % App->win->GetWindowHeight() - 1;
		quadtree->PushBack({ rand_x, rand_y });
	}
}