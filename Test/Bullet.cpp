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
	animation.resource.Draw(mDC, x - (animation.size.right), y - (animation.size.bottom), animation.size.right * 2, animation.size.bottom * 2,
		frame * animation.size.right, 0, animation.size.right, animation.size.bottom
	);
}

void Bullet::update()
{
	x += dirX;
	y += dirY;
}

void Bullet::change_frame()
{
	frame = (frame + 1) % animation.frame;
}
