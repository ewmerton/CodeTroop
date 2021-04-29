#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/particles.png");

	// Bomb particle
	bomb.anim.PushBack({ 47, 48, 16, 16 });
	bomb.anim.PushBack({ 63, 48, 16, 16 });
	bomb.anim.PushBack({ 80, 48, 16, 16 });
	bomb.lifetime = 300;
	bomb.anim.speed = 0.02f;
	

	// Explosion particle
	// Center
	explosionCenter.anim.PushBack({0, 0, 16, 16});
	explosionCenter.anim.PushBack({0, 16, 16, 16});
	explosionCenter.anim.PushBack({0, 32, 16, 16});
	explosionCenter.anim.loop = false;
	explosionCenter.anim.speed = 0.03f;
	// Horizontal
	exH.anim.PushBack({ 16, 0, 16, 16 });
	exH.anim.PushBack({ 16, 16, 16, 16 });
	exH.anim.PushBack({ 16, 32, 16, 16 });
	exH.anim.loop = false;
	exH.anim.speed = 0.03f;
	// Vertical
	exV.anim.PushBack({ 32, 48, 16, 16 });
	exV.anim.PushBack({ 16, 48, 16, 16 });
	exV.anim.PushBack({ 0, 48, 16, 16 });
	exV.anim.loop = false;
	exV.anim.speed = 0.03f;
	// Up
	exUp.anim.PushBack({ 0, 64, 16, 16 });
	exUp.anim.PushBack({ 16, 64, 16, 16 });
	exUp.anim.PushBack({ 32, 64, 16, 16 });
	exUp.anim.loop = false;
	exUp.anim.speed = 0.03f;
	// Down
	exDown.anim.PushBack({ 32, 80, 16, 16 });
	exDown.anim.PushBack({ 16, 80, 16, 16 });
	exDown.anim.PushBack({ 0, 80, 16, 16 });
	exDown.anim.loop = false;
	exDown.anim.speed = 0.03f;

	// Left
	exLeft.anim.PushBack({ 48, 32, 16, 16 });
	exLeft.anim.PushBack({ 48, 16, 16, 16 });
	exLeft.anim.PushBack({ 48, 0, 16, 16 });
	exLeft.anim.loop = false;
	exLeft.anim.speed = 0.03f;

	// Right
	exRight.anim.PushBack({ 32, 0, 16, 16 });
	exRight.anim.PushBack({ 32, 16, 16, 16 });
	exRight.anim.PushBack({ 32, 32, 16, 16 });
	exRight.anim.loop = false;
	exRight.anim.speed = 0.03f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}