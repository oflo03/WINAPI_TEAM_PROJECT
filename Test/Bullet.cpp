#include"Bullet.h"
#include"EffectManager.h"

extern double frame_time;
extern std::vector<Bullet*> Bullets;

Bullet::Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir) :
	pos(pos), dir(dir), frame(0),type(type)
{
	col = new Collider(8);
	col->layer = side;
	col->owner = this;
	if (side == enemyBullet) {
		velocity = 0.5;
	}
	else {
		velocity = 1;
	}
	col->damage = BulletDamage[type];
	col->pos = pos;
	COLL.emplace_back(col);
	SetImage(type);
	angle = std::atan2(dir.y, dir.x) * (180.0f / M_PI) * -1;
}


Bullet::~Bullet() {
	animation.resource.Destroy();
}

void Bullet::SetImage(int type)
{
	if (col->layer == playerBullet) {
		switch (type)
		{
		case PISTOL:
			this->animation.resource.Load(L"Bullet_Pistol.png");
			break;
		case RIFLE:
			this->animation.resource.Load(L"Bullet_Rifle.png");
			break;
		case SHOTGUN:
			this->animation.resource.Load(L"Bullet_Shotgun.png");
			break;
		default:
			break;
		}
	}
	else
		this->animation.resource.Load(L"enemy_bullet3.png");
	this->animation.frame = 4;
	this->animation.size = { 0,0,animation.resource.GetWidth() / 4, animation.resource.GetHeight() };
}

void Bullet::draw_bullet(HDC mDC)
{
	int width = animation.size.right;
	int height = animation.size.bottom;
	CImage temp;
	temp.Create(width, height, 32);
	CImage rotatedImage;
	rotatedImage.Create(width, height, 32);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			BYTE* srcPixel = (BYTE*)animation.resource.GetPixelAddress((int)frame * width + x, y);
			BYTE* destPixel = (BYTE*)temp.GetPixelAddress(x, y);
			memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Vector2D<float> rotatedPos = (Vector2D<float>(x - width / 2, y - height / 2)).Rotate(angle) + Vector2D<float>(width / 2, height / 2);
			if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
				BYTE* srcPixel = (BYTE*)temp.GetPixelAddress(rotatedPos.x, rotatedPos.y);
				BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
				memcpy(destPixel, srcPixel, sizeof(BYTE) * 4);
			}
		}
	}
	rotatedImage.TransparentBlt(mDC, pos.x - animation.size.right / 2, pos.y - animation.size.bottom / 2, animation.size.right, animation.size.bottom,
		0, 0, animation.size.right, animation.size.bottom, RGB(0, 0, 0)
	);
	rotatedImage.Destroy();
	temp.Destroy();
}

void Bullet::update()
{
	pos += dir * velocity;
	frame = (frame + frame_time * 3 * animation.frame);
	if (frame >= animation.frame) frame = 0;
	col->pos = pos;
}

void Bullet::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case wall:
	case player:
	case enemy:
		if (col->layer == enemyBullet)
			EffectManager::getInstance()->set_effect(new Effect(L"enemy_bullet_effect.png", col->pos + dir, 3, 5));
		else {
			switch (type)
			{
			case PISTOL:
				EffectManager::getInstance()->set_effect(new Effect(L"Bullet_Pistol_effect.png", col->pos + dir, 3, 4));
				break;
			case RIFLE:
				EffectManager::getInstance()->set_effect(new Effect(L"Bullet_Rifle_effect.png", col->pos + dir, 4, 6));
				break;
			case SHOTGUN:
				EffectManager::getInstance()->set_effect(new Effect(L"Bullet_shotgun_effect.png", col->pos + dir, 4, 6));
				break;
			default:
				break;
			}
		}
		for (auto i = COLL.begin(); i != COLL.end(); ++i)
			if (COLL[i - COLL.begin()] == this->col)
			{
				COLL.erase(i);
				break;
			}
		delete this->col;
		this->col = nullptr;
		for (auto i = Bullets.begin(); i != Bullets.end(); ++i)
			if (Bullets[i - Bullets.begin()] == this)
			{
				Bullets.erase(i);
				break;
			}
		deleteSet.insert(this);
		break;
	case playerMelee:
		dir *= -1;
		angle += 180;
		col->layer = playerBullet;
		animation.resource.Destroy();
		animation.resource.Load(L"bounced_bullet.png");
		break;
	default:
		break;
	}
}