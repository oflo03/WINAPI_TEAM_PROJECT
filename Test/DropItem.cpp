#include "DropItem.h"

extern double frame_time;
extern std::vector<DropItem*> drops;

CImage DropItem::image[3];



void DropItem::init()
{
	image[DROP::DPISTOL].Load(L"drop_pistol.png");
	image[DROP::DRIFLE].Load(L"drop_rifle.png");
	image[DROP::DSHOTGUN].Load(L"drop_shotgun.png");
}

void DropItem::update()
{
	pos.y += std::sin(xDir / 3.14) / 3;
	xDir += 0.1;
	col->pos = pos;
}

void DropItem::Draw(HDC mDC)
{
	int width = image[type].GetWidth() * 2;
	int height = image[type].GetHeight() * 2;
	image[type].Draw(mDC, pos.x - width / 2, pos.y - height / 2, width, height);
}

void DropItem::handle_collision(int otherLayer, int damage)
{
	if (otherLayer == player || otherLayer == rolled_player) {
		for (auto i = COLL.begin(); i != COLL.end(); ++i)
			if (COLL[i - COLL.begin()] == this->col)
			{
				COLL.erase(i);
				break;
			}
		delete this->col;
		this->col = nullptr;
		for (auto i = drops.begin(); i != drops.end(); ++i)
			if (drops[i - drops.begin()] == this)
			{
				drops.erase(i);
				break;
			}
		deleteSet.insert(this);
	}
}
