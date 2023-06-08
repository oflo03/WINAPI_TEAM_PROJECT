#include "IdleState.h"
#include"RollState.h"
#include "Marin.h"
#include"EffectManager.h"

extern double frame_time;

Marin::Marin(float x, float y) : Player(x, y)
{
	state = new IdleState;
	hand.Load(L"Marin_hand.png");
	shadow[0].Load(L"shadow.png");
	shadow[1].Load(L"shadow2.png");
	SetImage(STATE_IDLE);
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = player;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
	myWeapons.emplace_back(new Sword);
	myWeapons.emplace_back(new Pistol);
	myWeapons.emplace_back(new Rifle);
	myWeapons.emplace_back(new Shotgun);
	myWeapons.emplace_back(new Shotgun);
}

Marin::Marin() : Player()
{
	state = new IdleState;
	hand.Load(L"Marin_hand.png");
	shadow[0].Load(L"shadow.png");
	shadow[1].Load(L"shadow2.png");
	SetImage(STATE_IDLE);
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = player;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
	myWeapons.emplace_back(new Sword);
	myWeapons.emplace_back(new Pistol);
	myWeapons.emplace_back(new Rifle);
	myWeapons.emplace_back(new Shotgun);
	myWeapons.emplace_back(new Shotgun);
}

Marin::~Marin()
{
	for (int j = 0; j < 6; j++)
		animation[j].resource.Destroy();
	for (int i = 0; i < myWeapons.size(); i++)
		delete myWeapons[i];
	shadow[0].Destroy();
	shadow[1].Destroy();
	delete state;

}

void Marin::draw_character(HDC mDC)
{
	handPos = pos;
	if (abs(angle) < 90)
	{

		handPos.x += 18;
		handPos.y += 8;
	}
	else
	{
		handPos.x -= 17;
		handPos.y += 8;
	}
	bool isRolling = col->layer == rolled_player;
	float yDest = pos.y - (animation[direction].size.bottom - 20) * 2;
	shadow[isRolling].Draw(mDC, pos.x - shadow[isRolling].GetWidth(), pos.y + col->size.y - 2 - shadow[isRolling].GetHeight(), shadow[isRolling].GetWidth() * 2, shadow[isRolling].GetHeight() * 2);
	if (direction == FRONT || direction == FRONT_RIGHT || direction == FRONT_LEFT) {
		animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
			(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom
		);
		if (!isRolling) {
			myWeapons[selectedWeapon]->draw_weapon(mDC, handPos, mPos);
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		}
		else
		{
		}
	}
	else {
		if (!isRolling) {
			myWeapons[selectedWeapon]->draw_weapon(mDC, handPos, mPos);
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		}
		animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
			(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom
		);
	}
}

void Marin::handle_event()
{
	PlayerState* temp = this->state->handle_event(*this);
	if (temp != nullptr) {
		this->state->exit(*this);
		delete this->state;
		this->state = temp;
		this->state->enter(*this);
		frame = 0;
	}

}


void Marin::update()
{
	POINT temp;
	GetCursorPos(&temp);
	mPos.x = temp.x;
	mPos.y = temp.y;
	mPos -= monitorSize / 2;
	mPos /= 2;
	mPos += camPos;
	lastPos = pos;
	state->update(*this);
	if (col->layer == player)
		frame = (frame + frame_time * 1.5 * animation[direction].frame);
	else
		frame = (frame + frame_time * 2 * animation[direction].frame);
	if (frame >= animation[direction].frame) frame = 0;
	for (auto& W : myWeapons)
		W->update();
	if (myWeapons[selectedWeapon]->IsRunOut())
		SetWeapon(SWORD);
	col->pos = pos;
	camPos = pos + (mPos - pos) / 4;
	if (myWeapons[selectedWeapon]->IsReBound()) {
		Vector2D<float> t = mPos - pos;
		t.Normalize();
		t.Rotate(90);
		camPos += t * rebound[selectedWeapon] * (myWeapons[selectedWeapon]->GetCurTime() % 2 ? 1 : -1);
	}
}

void Marin::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation[FRONT].resource.Load(L"Marin_idle_front.png");
		animation[FRONT_RIGHT].resource.Load(L"Marin_idle_front_right.png");
		animation[FRONT_LEFT].resource.Load(L"Marin_idle_front_left.png");
		animation[BACK].resource.Load(L"Marin_idle_back.png");
		animation[BACK_RIGHT].resource.Load(L"Marin_idle_back_right.png");
		animation[BACK_LEFT].resource.Load(L"Marin_idle_back_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 4;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_RUN:
		animation[FRONT].resource.Load(L"Marin_run_front.png");
		animation[FRONT_RIGHT].resource.Load(L"Marin_run_front_right.png");
		animation[FRONT_LEFT].resource.Load(L"Marin_run_front_left.png");
		animation[BACK].resource.Load(L"Marin_run_back.png");
		animation[BACK_RIGHT].resource.Load(L"Marin_run_back_right.png");
		animation[BACK_LEFT].resource.Load(L"Marin_run_back_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 6;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_ROLL:
		animation[FRONT].resource.Load(L"Marin_roll_front.png");
		animation[FRONT_RIGHT].resource.Load(L"Marin_roll_front_right.png");
		animation[FRONT_LEFT].resource.Load(L"Marin_roll_front_left.png");
		animation[BACK].resource.Load(L"Marin_roll_back.png");
		animation[BACK_RIGHT].resource.Load(L"Marin_roll_back_right.png");
		animation[BACK_LEFT].resource.Load(L"Marin_roll_back_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 9;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	default:
		break;
	}
}

void Marin::SetDirection()
{
	angle = std::atan2(mPos.y - (pos.y), mPos.x - pos.x) * (180.0f / M_PI);
	if (angle >= -20 && angle <= 60) {
		direction = FRONT_RIGHT;
	}
	else if (angle > 60 && angle <= 120) {
		direction = FRONT;
	}
	else if (angle >= 120 && angle <= 180 || angle > -180 && angle < -160) {
		direction = FRONT_LEFT;
	}
	else if (angle >= -160 && angle <= -120) {
		direction = BACK_LEFT;
	}
	else if (angle >= -120 && angle <= -60) {
		direction = BACK;
	}
	else if (angle >= -60 && angle < -20) {
		direction = BACK_RIGHT;
	}
}

void Marin::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case wall:
		if (!isWallCollision(Vector2D<float>(pos.x, lastPos.y), col->size))
			pos.y = lastPos.y;
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y), col->size))
			pos.x = lastPos.x;
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case enemy:
		if(col->layer==player)
			pos -= dir * 5;
		else 
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case enemyBullet:
		EffectManager::getInstance()->set_effect(new Effect(L"player_damaged.png", col->pos = pos, 3, 5));
		break;
	default:
		break;
	}
}