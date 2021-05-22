#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type), listener(listener)
{

}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}

bool Collider::NextToFromUp(const SDL_Rect& r) const
{
	return (rect.x == r.x &&
		rect.y + 16 == r.y);
}

bool Collider::NextToFromDown(const SDL_Rect& r) const
{
	return (rect.x == r.x &&
		rect.y == r.y + 16);
}

bool Collider::NextToFromLeft(const SDL_Rect& r) const
{
	return (rect.y == r.y &&
		rect.x + 16 ==r.x);
}

bool Collider::NextToFromRight(const SDL_Rect& r) const
{
	return (rect.y == r.y &&
		rect.x == r.x + 16);
}