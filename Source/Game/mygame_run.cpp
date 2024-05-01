#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState() // �]�w�C�������һݪ��ܼ�
{
}

void CGameStateRun::OnMove() // ���ʹC������
{
	checkCanvasCollision();
	checkBoxBallCollision();
	if (status == Status::READY) {
		for (int i = 0; i < level; i++) {
			for (int j = 0; j < boxTotalCountinLevel; j++) {
			
					box[i][j].SetTopLeft(47 + j * box[i][j].image.GetWidth(), 164 + (level - i - 1) * box[i][j].image.GetHeight());
				
				
			}
		}
	}
	
	int ball_return = 0;
	for (int i = 0; i < ball_count; i++) {
		if (status == Status::RUNNING && ball[i].click_flag == 0) {
			ball_return += 1;
		}
	}

	if (ball_return == ball_count && status == Status::RUNNING) {
		status = Status::READY;
		level += 1;
	}

	if (total_score == current_score) {
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit() // �C������Ȥιϧγ]�w
{
	load_background();

	for (int i = 0; i < boxTotalLevel; i++) {
		for (int j = 0; j < boxTotalCountinLevel; j++){
			box[i][j].Init();
		}
	}
	for (int i = 0; i < ball_count; i++)
	{
		ball[i].Init();
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	status = Status::RUNNING;
	//ball_status = Status::RUNNING;
	for (int i = 0; i < 2; i++)
	{
		ball[i].ball_status = Status::RUNNING;
		ball[i].mouse_x = point.x;
		ball[i].mouse_y = point.y;
		ball[i].Ball_shot(ball[i].x, ball[i].y, ball[i].mouse_x, ball[i].mouse_y);
		ball[i].click_flag = 1;
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	frame.ShowBitmap();

	 question.ShowBitmap();
	 show_text_score();
	for (int i = 0; i < level; i++) {
		for (int j = 0; j < boxTotalCountinLevel; j++) {
			if (box[i][j].box_count <= 0)
			{
				continue;
			}
			box[i][j].ShowImage();
			
		}
	}
	for (int i = 0; i < ball_count; i++)
	{
		ball[i].ShowBitmap();
	}

	CDC *pDC = CDDraw::GetBackCDC();
	for (int i = 0; i < level; i++) {
		for (int j = 0; j < boxTotalCountinLevel; j++) {
			box[i][j].ShowText(pDC);
		}
	}
	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::load_background()
{
	background.LoadBitmapByString({"resources/game_background.bmp"});
	background.SetTopLeft(0, 0);

	question.LoadBitmapByString({"resources/question.bmp"});
	question.SetTopLeft(0, 80);

	frame.LoadBitmapByString({"resources/frame.bmp"});
	frame.SetTopLeft(42, 160);
}

void CGameStateRun::checkCanvasCollision()
{

	for (int i = 0; i < ball_count; i++)
	{
		if (ball[i].click_flag == 1)
		{
			if (ball[i].GetLeft() <= 45 || ball[i].GetLeft() >= 395)
			{
				ball[i].dx *= -1;
			}
			if (ball[i].GetTop() <= 164)
			{
				ball[i].dy *= -1;
			}
			if (ball[i].GetTop() >= 564)
			{
				//status = Status::READY;
				ball[i].click_flag = 0;
				ball[i].ball_status = Status::READY;
				ball[i].x = ball[i].GetLeft();
				currentD_ball_y = min(560, int(ball[i].GetTop() + ball[i].dy));
				ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx+2), currentD_ball_y);
				
			}
			// max min
			//if (ball[i].GetLeft() + ball[i].dx <= 45)
			//{
			//	currentL_ball_x = max(45, int(ball[i].GetLeft() + ball[i].dx));
			//	//ball[i].SetTopLeft(currentL_ball_x, int(ball[i].GetTop() + ball[i].dy));
			//}
			//else if (ball[i].GetLeft() + ball[i].dx >= 395)
			//{
			//	currentR_ball_x = min(395, int(ball[i].GetLeft() + ball[i].dx));
			//	//ball[i].SetTopLeft(currentR_ball_x, int(ball[i].GetTop() + ball[i].dy));
			//}
			//else if (ball[i].GetTop() <= 164)
			//{
			//	currentU_ball_y = max(164, int(ball[i].GetTop() + ball[i].dy));
			//	//ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx), currentU_ball_y);
			//}
			//else if (ball[i].GetTop() >= 564)
			//{
			//	currentD_ball_y = min(564, int(ball[i].GetTop() + ball[i].dy));
			//	//ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx+2), currentD_ball_y);
			//}
			//// �|�]�o��
			//else
			//{
			//	//ball[i].SetTopLeft(int(ball[i].x), int(ball[i].y));
			//}
			// ball[i].ShowBitmap();
			// ball[i].RenewCoordinate(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
		}
	}
}

void CGameStateRun::checkBoxBallCollision()
{
	for (int i = 0; i < ball_count; i++){
		if (ball[i].ball_status == Status::RUNNING) {
			checkBallCollision(i);
			ballMove(i);
		}
		
	}
}

void CGameStateRun::checkBallCollision(int i) {
	for (int j = 0; j < level; j++) {
		for (int k = 0; k < boxTotalCountinLevel; k++) {
			if (ball[i].click_flag == 1){
				if (box[j][k].box_count > 0){
					IsOverlap_Direction(ball[i], box[j][k]);
					if (CMovingBitmap::IsOverlap(box[j][k].image, ball[i].ball_image))
					{
						if (ball[i].xDirectionChange_flag == 1)
						{
							ball[i].dx *= -1;
							ball[i].xDirectionChange_flag = 0;
							box[j][k].box_count -= 1;
							current_score += 1;
						}
						else if (ball[i].yDirectionChange_flag == 1)
						{
							ball[i].dy *= -1;
							ball[i].yDirectionChange_flag = 0;
							box[j][k].box_count -= 1;
							current_score += 1;
						}
					}
				}
			}
		}
	}
}


void CGameStateRun::ballMove(int i) {
	if (ball[i].ball_status == Status::RUNNING) {
		ball[i].x += 3 * ball[i].dx;
		ball[i].y += 3 * ball[i].dy;
		ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
	}
}

void CGameStateRun::IsOverlap_Direction(Ball &ball, Box box)
{
	if ((ball.GetLeft() >= box.GetLeft() - ball.ballWidth) && (ball.GetLeft() <= box.GetLeft() + box.boxWidth))
	{
		if ((ball.GetTop()) == (box.GetTop() - ball.ballWidth ) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth+1) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth+2) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth + 3))
		{
			ball.SetyDirectionChange_flag(1);
			question.ShowBitmap();
		}
		if ((ball.GetTop()) == (box.GetTop() + box.boxWidth) || (ball.GetTop()) == (box.GetTop() + box.boxWidth + 1) || (ball.GetTop()) == (box.GetTop() + box.boxWidth + 2) || (ball.GetTop()) == (box.GetTop() + box.boxWidth + 3))
		{
			ball.SetyDirectionChange_flag(1);
			question.ShowBitmap();
		}
	}
	if ((ball.GetTop() >= box.GetTop() - ball.ballWidth) && (ball.GetTop() <= box.GetTop() + box.boxWidth))
	{
		question.ShowBitmap();
		if ((ball.GetLeft() + ball.ballWidth == box.GetLeft() ) || (ball.GetLeft() + ball.ballWidth == box.GetLeft()+1) || (ball.GetLeft() + ball.ballWidth == box.GetLeft()+2) || (ball.GetLeft() + ball.ballWidth == box.GetLeft() + 3))
		{
			ball.SetxDirectionChange_flag(1);
			question.ShowBitmap();
		}
		if ((ball.GetLeft() == box.GetLeft() + box.boxWidth) || (ball.GetLeft() == box.GetLeft() + box.boxWidth + 1) || (ball.GetLeft() == box.GetLeft() + box.boxWidth + 2) || (ball.GetLeft() == box.GetLeft() + box.boxWidth + 3))
		{
			ball.SetxDirectionChange_flag(1);
			question.ShowBitmap();
		}
	}
}

void CGameStateRun::show_text_score()
{
	CDC *pDC = CDDraw::GetBackCDC();
	string phase_string = to_string(current_score);

	CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 400, 80, phase_string);

	CDDraw::ReleaseBackCDC();
}

Box::Box(int box_count, int x, int y)
{
	this->box_count = box_count;
	this->x = x;
	this->y = y;
}

void Box::ShowImage()
{
	image.ShowBitmap();
}

void Box::Init()
{
	if (box_count >= 16 && box_count <= 20)
	{
		this->image.LoadBitmapByString({"resources/box-blue.bmp"}, RGB(0, 0, 0));
	}
	else if (box_count >= 12 && box_count <= 16)
	{
		this->image.LoadBitmapByString({"resources/box-purple.bmp"}, RGB(0, 0, 0));
	}
	else if (box_count >= 8 && box_count <= 12)
	{
		this->image.LoadBitmapByString({"resources/box-red.bmp"}, RGB(0, 0, 0));
	}
	else if (box_count >= 4 && box_count <= 8)
	{
		this->image.LoadBitmapByString({"resources/box-orange.bmp"}, RGB(0, 0, 0));
	}
	else if (box_count >= 1 && box_count <= 4)
	{
		this->image.LoadBitmapByString({"resources/box-yellow.bmp"}, RGB(0, 0, 0));
	}
	else if (box_count ==0) {
		this->image.LoadBitmapByString({ "resources/box-black.bmp" }, RGB(0, 0, 0));
	}
	image.SetTopLeft(x, y);
}

void Box::ShowText(CDC* pDC)
{
	
	if (box_count == 1)
	{
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 22, image.GetTop() + 14, to_string(box_count));
	}
	else if (box_count >= 2 && box_count <= 9)
	{
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 18, image.GetTop() + 14, to_string(box_count));
	}
	else if (box_count == 11)
	{
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 15, image.GetTop() + 14, "1 1");
	}
	else if (box_count == 10 || (box_count >= 12 && box_count <= 19))
	{
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 15, image.GetTop() + 14, to_string(box_count));
	}
	else if (box_count == 20)
	{
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 11, image.GetTop() + 14, to_string(box_count));
	}
}
int Box::GetLeft()
{
	return image.GetLeft();
}

int Box::GetTop()
{
	return image.GetTop();
}
void Box::UnshowBitmap()
{
	image.UnshowBitmap();
}

void Box::SetTopLeft(int x,int y) {
	return image.SetTopLeft(x, y);
}

Ball::Ball(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Ball::ShowBitmap()
{
	ball_image.ShowBitmap();
}

void Ball::Init()
{

	this->ball_image.LoadBitmapByString({"resources/ball.bmp"}, RGB(255, 255, 255));
	ball_image.SetTopLeft((int)x, (int)y);
}

int Ball::GetLeft()
{
	return ball_image.GetLeft();
}

int Ball::GetTop()
{
	return ball_image.GetTop();
}

void Ball::SetTopLeft(int set_x, int set_y)
{
	return ball_image.SetTopLeft(set_x, set_y);
}

void Ball::RenewCoordinate(int set_x, int set_y)
{
	x = set_x;
	y = set_y;
	// return 0;
}

void Ball::Ball_shot(double x, double y, int mouse_x, int mouse_y)
{
	// pow(pow((mouse_x - x),2)+ pow((mouse_y - y), 2),0.5)
	dx = (mouse_x - x) / pow(pow((mouse_x - x), 2) + pow((mouse_y - y), 2), 0.5);
	dy = abs((mouse_y - y) / pow(pow((mouse_x - x), 2) + pow((mouse_y - y), 2), 0.5))*-1;
}
void Ball::SetyDirectionChange_flag(bool new_flag)
{
	yDirectionChange_flag = new_flag;
}
void Ball::SetxDirectionChange_flag(bool new_flag)
{
	xDirectionChange_flag = new_flag;
}
