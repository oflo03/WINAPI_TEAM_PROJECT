#pragma once
#include"Animation.h"
#include"Master.h"

enum DROP
{
	DPISTOL,
	DRIFLE,
	DSHOTGUN,
	DROCKET
};

class DropItem : public Master
{
private:
	static CImage image[4];
	int type;
	Vector2D<float> pos;
	float xDir;
public:
	DropItem(int type, Vector2D<float> pos) : type(type), pos(pos), xDir(0) {
		col = new Collider(Vector2D<float>(image[type].GetWidth(), image[type].GetHeight()));
		col->layer = dropitem;
		col->owner = this;
		col->pos = pos;
		col->damage = type;
		COLL.emplace_back(col);
	}
	~DropItem() { }
	static void init();
	static void destroy();
	static void Clear();
	void update();
	void Draw(HDC mDC);
	virtual void handle_collision(int otherLayer, int damage);
};

