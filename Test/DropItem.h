#pragma once
#include"Animation.h"
#include"Master.h"

class DropItem
{
private:
	int type;
	CImage image;
	Vector2D<float> pos;
	float xDir;
public:
	DropItem(int type, Vector2D<float> pos) : type(type),pos(pos),xDir(0)
	{
		/*switch (type)
		{
		case PISTOL:
			image.Load(L"drop_pistol.png");
			break;
		case RIFLE:
			image.Load(L"drop_rifle.png");
			break;
		case SHOTGUN:
			image.Load(L"drop_shotgun.png");
			break;
		default:
			break;
		}*/
	}
	~DropItem() { image.Destroy(); }
	void update();
	void Draw(HDC mDC);
	virtual void handle_collision(int otherLayer, int damage);
};

