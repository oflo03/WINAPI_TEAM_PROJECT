#include"Bullet.h"
#include"EffectManager.h"
#include"Player.h"

extern double frame_time;
extern std::vector<Bullet*> Bullets;

Animation Bullet::animation[7];

void Bullet::init() {
	animation[BPISTOL].resource.Load(L"Bullet_Pistol.png");
	animation[BPISTOL].frame = 4;
	animation[BPISTOL].velocity = 3;
	animation[BRIFLE].resource.Load(L"Bullet_Rifle.png");
	animation[BRIFLE].frame = 4;
	animation[BRIFLE].velocity = 3;
	animation[BSHOTGUN].resource.Load(L"Bullet_Shotgun.png");
	animation[BSHOTGUN].frame = 4;
	animation[BSHOTGUN].velocity = 3;
	animation[BENEMY].resource.Load(L"enemy_bullet3.png");
	animation[BENEMY].frame = 4;
	animation[BENEMY].velocity = 3;
	animation[BBOUNCE].resource.Load(L"bounced_bullet.png");
	animation[BBOUNCE].frame = 4;
	animation[BBOUNCE].velocity = 3;
	animation[BOSSBULLET1].resource.Load(L"boss_bullet1.png");
	animation[BOSSBULLET1].frame = 4;
	animation[BOSSBULLET1].velocity = 3;
	animation[BOSSBULLET2].resource.Load(L"boss_bullet2.png");
	animation[BOSSBULLET2].frame = 1;
	animation[BOSSBULLET2].velocity = 0;
	for(int i=0;i<7;i++)
		animation[i].size = {0,0,animation[i].resource.GetWidth() / animation[i].frame, animation[i].resource.GetHeight()};
}

Bullet::Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir) :
	pos(pos), dir(dir), frame(0),type(type),side(side)
{
	col = new Collider(8);
	if (side == enemyBullet) {
		switch (this->type)
		{
		case BOSSBULLET1:
			col->size.x = col->size.y = 10;
			velocity = 2;
			break;
		case BOSSBULLET2:
			col->size.x = col->size.y = 10;
			velocity = 2;
			break;
		default:
			this->type = BENEMY;
			velocity = 0.5;
			break;
		}
	}
	else {
		velocity = 1;
	}
	col->layer = side;
	col->owner = this;
	col->damage = BulletDamage[type];
	col->pos = pos;
	COLL.emplace_back(col);
	angle = std::atan2(dir.y, dir.x) * (180.0f / M_PI) * -1;
}


Bullet::~Bullet() {
}


void Bullet::draw_bullet(HDC mDC){
	int width = animation[type].size.right;
	int height = animation[type].size.bottom;
	if(type != BOSSBULLET1){
		CImage temp;
		temp.Create(width, height, 32);
		CImage rotatedImage;
		rotatedImage.Create(width, height, 32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				BYTE* srcPixel = (BYTE*)animation[type].resource.GetPixelAddress((int)frame * width + x, y);
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
		rotatedImage.TransparentBlt(mDC, pos.x - animation[type].size.right / 2, pos.y - animation[type].size.bottom / 2, animation[type].size.right, animation[type].size.bottom,
			0, 0, animation[type].size.right, animation[type].size.bottom, RGB(0, 0, 0)
		);
		rotatedImage.Destroy();
		temp.Destroy();
	}
	else {
		animation[type].resource.Draw(mDC, pos.x - animation[type].size.right, pos.y - animation[type].size.bottom, animation[type].size.right*2, animation[type].size.bottom*2,
			animation[type].size.right*(int)frame, 0, animation[type].size.right, animation[type].size.bottom
		);
	}
}

void Bullet::update()
{
	if(type != BOSSBULLET1)
		pos += dir * velocity;
	else {

	}
	frame = (frame + frame_time * animation[type].velocity * animation[type].frame);
	if (frame >= animation[type].frame) frame = 0;
	col->pos = pos;
}

void Bullet::handle_collision(int otherLayer, int damage)
{
	if (type == BOSSBULLET1) return;
	switch (otherLayer)
	{
	case wall:
	case player:
	case enemy:
		switch (type)
		{
		case BPISTOL:
			EffectManager::getInstance()->set_effect(new Effect(CEffect::PISTOLBULLET, col->pos));
			break;
		case BRIFLE:
			EffectManager::getInstance()->set_effect(new Effect(CEffect::RIFLEBULLET, col->pos));
			break;
		case BSHOTGUN:
			EffectManager::getInstance()->set_effect(new Effect(CEffect::SHOTGUNBULLET, col->pos));
			break;
		case BOSSBULLET1:
		case BOSSBULLET2:
		case BENEMY:
			EffectManager::getInstance()->set_effect(new Effect(CEffect::ENEMYBULLET, col->pos));
			break;
		case BBOUNCE:
			EffectManager::getInstance()->set_effect(new Effect(CEffect::BOUNCEBULLET, col->pos));
			break;
		default:
			break;
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
	case playerMelee: {
		dir = Player::getInstance(1)->GetMouseVector()*10;
		angle = Player::getInstance(1)->GetAngle()*-1;
		col->layer = playerBullet;
		type = BBOUNCE;
	}
		break;
	default:
		break;
	}
}