#include"Bullet.h"

extern double frame_time;

Bullet::Bullet(int type, Vector2D<float> pos, Vector2D<float> dir) :
	type(type), pos(pos), dir(dir), damage(BulletDamage[type]), frame(0)
{
	SetImage(type);
	col = new Collider(animation.size.right);
	col->owner = this;
	col->layer = playerBullet;
	col->pos = pos;
	COLL.emplace_back(col);
}

void Bullet::SetImage(int type)
{
	switch (type)
	{
	case 1:
		this->animation.resource.Load(L"Bullet_Pistol.png");
		break;
	case 2:
		this->animation.resource.Load(L"Bullet_Rifle.png");
		break;
	case 3:
		this->animation.resource.Load(L"Bullet_Shotgun.png");
		break;
	default:
		break;
	}
	this->animation.frame = 4;
	this->animation.size = { 0,0,animation.resource.GetWidth() / animation.frame,animation.resource.GetHeight() };
}

void Bullet::draw_bullet(HDC mDC)
{
	animation.resource.Draw(mDC, pos.x - animation.size.right, pos.y  - animation.size.bottom, animation.size.right * 2, animation.size.bottom * 2,
		(int)frame * animation.size.right, 0, animation.size.right, animation.size.bottom
	);
}

void Bullet::update()
{
	pos += dir * 2;
	frame = (frame + frame_time * 2 * animation.frame);
	if (frame >= animation.frame) frame = 0;
	col->pos = pos;
}

void Bullet::handle_collision(Master* other)
{

}