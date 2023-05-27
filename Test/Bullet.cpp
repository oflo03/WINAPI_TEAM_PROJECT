#include"Bullet.h"

void Bullet::SetImage(int type)
{
	switch (type)
	{
	case 1:
		this->animation.resource.Load(L"Bullet_Pistol.png");
		this->animation.frame = 4;
		this->animation.size = { 0,0,16,16 };
		break;
	case 2:
		this->animation.resource.Load(L"Bullet_Rifle.png");
		this->animation.frame = 4;
		this->animation.size = { 0,0,16,16 };
		break;
	case 3:
		this->animation.resource.Load(L"Bullet_Shotgun.png");
		this->animation.frame = 4;
		this->animation.size = { 0,0,16,16 };
		break;
	default:
		break;
	}
}

void Bullet::draw_bullet(HDC mDC)
{
	animation.resource.Draw(mDC, pos.x - animation.size.right, pos.y - (animation.size.bottom - 20) * 2 - animation.size.bottom, animation.size.right * 2, animation.size.bottom * 2,
		(int)frame * animation.size.right, 0, animation.size.right, animation.size.bottom
	);
}

void Bullet::update()
{
	pos += dir;
	frame = (frame + GetFrameTime() * 2 * animation.frame);
	if (frame >= animation.frame) frame = 0;
}