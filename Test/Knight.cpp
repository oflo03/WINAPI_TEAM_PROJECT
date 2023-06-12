#include "IdleState.h"
#include"RollState.h"
#include "Knight.h"
#include"DeadState.h"
#include"EffectManager.h"
#include"SoundManager.h"

extern double frame_time;
extern bool beatable;

Animation Knight::animation[6][6];

void Knight::init() {
	animation[STATE_IDLE][FRONT].resource.Load(L"resources/knight_idle_front.png");
	animation[STATE_IDLE][FRONT_RIGHT].resource.Load(L"resources/knight_idle_front_right.png");
	animation[STATE_IDLE][FRONT_LEFT].resource.Load(L"resources/knight_idle_front_left.png");
	animation[STATE_IDLE][BACK].resource.Load(L"resources/knight_idle_back.png");
	animation[STATE_IDLE][BACK_RIGHT].resource.Load(L"resources/knight_idle_back_right.png");
	animation[STATE_IDLE][BACK_LEFT].resource.Load(L"resources/knight_idle_back_left.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_IDLE][i].frame = 4;
		animation[STATE_IDLE][i].size = { 0,0,animation[STATE_IDLE][i].resource.GetWidth() / animation[STATE_IDLE][i].frame,animation[STATE_IDLE][i].resource.GetHeight() };
		animation[STATE_IDLE][i].velocity = 1.5;
	}
	animation[STATE_RUN][FRONT].resource.Load(L"resources/knight_run_front.png");
	animation[STATE_RUN][FRONT_RIGHT].resource.Load(L"resources/knight_run_front_right.png");
	animation[STATE_RUN][FRONT_LEFT].resource.Load(L"resources/knight_run_front_left.png");
	animation[STATE_RUN][BACK].resource.Load(L"resources/knight_run_back.png");
	animation[STATE_RUN][BACK_RIGHT].resource.Load(L"resources/knight_run_back_right.png");
	animation[STATE_RUN][BACK_LEFT].resource.Load(L"resources/knight_run_back_left.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_RUN][i].frame = 6;
		animation[STATE_RUN][i].size = { 0,0,animation[STATE_RUN][i].resource.GetWidth() / animation[STATE_RUN][i].frame,animation[STATE_RUN][i].resource.GetHeight() };
		animation[STATE_RUN][i].velocity = 1.5;
	}
	animation[STATE_ROLL][FRONT].resource.Load(L"resources/knight_roll_front.png");
	animation[STATE_ROLL][FRONT_RIGHT].resource.Load(L"resources/knight_roll_front_right.png");
	animation[STATE_ROLL][FRONT_LEFT].resource.Load(L"resources/knight_roll_front_left.png");
	animation[STATE_ROLL][BACK].resource.Load(L"resources/knight_roll_back.png");
	animation[STATE_ROLL][BACK_RIGHT].resource.Load(L"resources/knight_roll_back_right.png");
	animation[STATE_ROLL][BACK_LEFT].resource.Load(L"resources/knight_roll_back_left.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_ROLL][i].frame = 9;
		animation[STATE_ROLL][i].size = { 0,0,animation[STATE_ROLL][i].resource.GetWidth() / animation[STATE_ROLL][i].frame,animation[STATE_ROLL][i].resource.GetHeight() };
		animation[STATE_ROLL][i].velocity = 2;
	}
	animation[STATE_DEAD][FRONT].resource.Load(L"resources/knight_dead.png");
	animation[STATE_DEAD][FRONT_RIGHT].resource.Load(L"resources/knight_dead.png");
	animation[STATE_DEAD][FRONT_LEFT].resource.Load(L"resources/knight_dead.png");
	animation[STATE_DEAD][BACK].resource.Load(L"resources/knight_dead.png");
	animation[STATE_DEAD][BACK_RIGHT].resource.Load(L"resources/knight_dead.png");
	animation[STATE_DEAD][BACK_LEFT].resource.Load(L"resources/knight_dead.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_DEAD][i].frame = 12;
		animation[STATE_DEAD][i].size = { 0,0,animation[STATE_DEAD][i].resource.GetWidth() / animation[STATE_DEAD][i].frame,animation[STATE_DEAD][i].resource.GetHeight() };
		animation[STATE_DEAD][i].velocity = 0.5;
	}
}

void Knight::destroy() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; ++j)
			animation[i][j].resource.Destroy();
}

Knight::Knight(float x, float y) : Player(x, y)
{
	state = new IdleState;
	hand.Load(L"resources/knight_hand.png");
	shadow[0].Load(L"resources/shadow.png");
	shadow[1].Load(L"resources/shadow2.png");
	col = new Collider(Vector2D<float>(animation[STATE_IDLE][FRONT].size.right, animation[STATE_IDLE][FRONT].size.bottom));
	col->owner = this;
	col->layer = player;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
	myWeapons.emplace_back(new Sword);
	myWeapons.emplace_back(new Pistol);
	myWeapons.emplace_back(new Rifle);
	myWeapons.emplace_back(new Shotgun);
	myWeapons.emplace_back(new Rocket);
}

Knight::~Knight()
{
	for (int i = 0; i < myWeapons.size(); i++)
		delete myWeapons[i];
	shadow[0].Destroy();
	shadow[1].Destroy();
	delete state;

}

void Knight::draw_character(HDC mDC)
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
	float yDest = pos.y - (animation[curstate][direction].size.bottom - 20) * 2;
	if (curstate != STATE_DEAD)
		shadow[isRolling].Draw(mDC, pos.x - shadow[isRolling].GetWidth(), pos.y + col->size.y - 2 - shadow[isRolling].GetHeight(), shadow[isRolling].GetWidth() * 2, shadow[isRolling].GetHeight() * 2);
	if (direction == FRONT || direction == FRONT_RIGHT || direction == FRONT_LEFT) {
		if (col->layer != damaged_player || (int)(damageCnt / 0.5) % 2)
			animation[curstate][direction].resource.Draw(mDC, pos.x - animation[curstate][direction].size.right, yDest - 20, animation[curstate][direction].size.right * 2, animation[curstate][direction].size.bottom * 2,
				(int)frame * animation[curstate][direction].size.right, 0, animation[curstate][direction].size.right, animation[curstate][direction].size.bottom
			);
		if (!isRolling && curstate != STATE_DEAD) {
			myWeapons[selectedWeapon]->draw_weapon(mDC, handPos, mPos);
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		}
		else
		{
		}
	}
	else {
		if (!isRolling && curstate != STATE_DEAD) {
			myWeapons[selectedWeapon]->draw_weapon(mDC, handPos, mPos);
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		}
		if (col->layer != damaged_player || (int)(damageCnt / 0.5) % 2)
			animation[curstate][direction].resource.Draw(mDC, pos.x - animation[curstate][direction].size.right, yDest - 20, animation[curstate][direction].size.right * 2, animation[curstate][direction].size.bottom * 2,
				(int)frame * animation[curstate][direction].size.right, 0, animation[curstate][direction].size.right, animation[curstate][direction].size.bottom
			);
	}
}

void Knight::handle_event()
{
	PlayerState* temp = this->state->handle_event(*this);
	if (temp != nullptr) {
		delete this->state;
		this->state = temp;
		this->state->enter(*this);
		frame = 0;
	}

}


void Knight::update()
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
	frame = (frame + frame_time * animation[curstate][direction].velocity * animation[curstate][direction].frame);
	if (frame >= animation[curstate][direction].frame && curstate != STATE_DEAD) frame = 0;
	else if (frame >= animation[curstate][direction].frame && curstate == STATE_DEAD) frame = 12;
	if (damageCnt > 0)damageCnt -= 0.1;
	if (col->layer == damaged_player && (int)damageCnt == 0) col->layer = player;
	myWeapons[selectedWeapon]->update();
	if (myWeapons[selectedWeapon]->GetShotTime() == 0 && myWeapons[selectedWeapon]->IsRunOut())
		SetWeapon(SWORD);
	col->pos = pos;
	if (curstate != STATE_DEAD)
		camPos = pos + (mPos - pos) / 4;
	if (myWeapons[selectedWeapon]->IsReBound()) {
		Vector2D<float> t = mPos - pos;
		t.Normalize();
		t.Rotate(180);
		camPos += t * rebound[selectedWeapon] * (myWeapons[selectedWeapon]->GetCurTime() % 2 ? 1 : -1);
	}
	if (damageCnt > 8) {
		Vector2D<float> t = mPos - pos;
		t.Normalize();
		t.Rotate(180);
		camPos += t * 10 * ((int)(damageCnt / 0.5) % 2 ? 1 : -1);
	}
}

void Knight::SetDirection()
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

void Knight::handle_collision(int otherLayer, int damage)
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
		if (col->layer == player && beatable)
		{
			--hp;
			if (hp > 0) {
				SoundManager::getInstance()->play(PLAYER_HURT);
				pos -= dir;
				col->layer = damaged_player;
				damageCnt = 10.0;
			}
			else {
				SoundManager::getInstance()->play(PLAYER_DEATH);
				delete this->state;
				this->state = new DeadState();
				this->state->enter(*this);
				frame = 0;
			}
		}
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case enemyBullet:
		EffectManager::getInstance()->set_effect(new Effect(CEffect::DAMAGED, col->pos));
		if (col->layer == player && beatable)
		{
			--hp;
			if (hp > 0) {
				SoundManager::getInstance()->play(PLAYER_HURT);
				pos -= dir;
				col->layer = damaged_player;
				damageCnt = 10.0;
			}
			else {
				SoundManager::getInstance()->play(PLAYER_DEATH);
				delete this->state;
				this->state = new DeadState();
				this->state->enter(*this);
				frame = 0;
			}
		}
		break;
	default:
		break;
	}
}