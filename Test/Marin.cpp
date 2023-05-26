#include "Marin.h"
#include "IdleState.h"

Marin::Marin(float x, float y) : Player(x,y)
{
	state = new IdleState;
	SetImage(STATE_IDLE);
}

Marin::Marin() : Player()
{
	state = new IdleState;
	SetImage(STATE_IDLE);
}

Marin::~Marin()
{
	for (int j = 0; j < 6; j++)
		animation[j].resource.Destroy();
	delete state;
}

void Marin::draw_character(HDC mDC)
{
	float yDest = pos.y - 20 - (animation[direction].size.bottom - 20)*4;
	animation[direction].resource.Draw(mDC, pos.x- animation[direction].size.right, yDest, animation[direction].size.right*4, animation[direction].size.bottom*4,
		frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom
	);
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
	if (isFront && horizonDir == 0)
		direction = FRONT;
	else if(isFront && horizonDir == 1)
		direction = FRONT_RIGHT;
	else if (isFront && horizonDir == -1)
		direction = FRONT_LEFT;
	else if (!isFront && horizonDir == 0)
		direction = BACK;
	else if (!isFront && horizonDir == 1)
		direction = BACK_RIGHT;
	else if (!isFront && horizonDir == -1)
		direction = BACK_LEFT;
	state->update(*this);

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

void Marin::change_frame()
{
	frame = (frame + 1) % animation[direction].frame;
}
