#include"Pistol.h"

void Pistol::update()
{

}
void Pistol::attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center)
{
	POINT mPos;
	GetCursorPos(&mPos);
	Vector2D<float> t = Vector2D<float>(mPos.x - center.x, mPos.y - center.y);
	t /= t.GetLenth();
	bullets.emplace_back(new Bullet(PISTOL, center, t * 10));
}