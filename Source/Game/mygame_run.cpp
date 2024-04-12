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
}

void CGameStateRun::OnInit() // �C������Ȥιϧγ]�w
{
	load_background();

	for (int i = 0; i < box_amount; i++)
	{
		box[i].Init();
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

	for (int i = 0; i < 2; i++)
	{
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

	// question.ShowBitmap();
	// show_text_score();
	for (int i = 0; i < box_amount; i++)
	{
		if (box[i].box_count <= 0)
		{
			continue;
		}
		box[i].ShowImage();
		box[i].ShowText();
	}
	for (int i = 0; i < ball_count; i++)
	{
		ball[i].ShowBitmap();
	}
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
				ball[i].x = ball[i].GetLeft();

				ball[i].click_flag = 0;
			}
			// max min
			if (ball[i].GetLeft() + ball[i].dx <= 45)
			{
				currentL_ball_x = max(45, int(ball[i].GetLeft() + ball[i].dx));
				ball[i].SetTopLeft(currentL_ball_x, int(ball[i].GetTop() + ball[i].dy));
			}
			else if (ball[i].GetLeft() + ball[i].dx >= 395)
			{
				currentR_ball_x = min(395, int(ball[i].GetLeft() + ball[i].dx));
				ball[i].SetTopLeft(currentR_ball_x, int(ball[i].GetTop() + ball[i].dy));
			}
			else if (ball[i].GetTop() <= 164)
			{
				currentU_ball_y = max(164, int(ball[i].GetTop() + ball[i].dy));
				ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx), currentU_ball_y);
			}
			else if (ball[i].GetTop() >= 564)
			{
				currentD_ball_y = min(564, int(ball[i].GetTop() + ball[i].dy));
				ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx), currentD_ball_y);
			}
			// �|�]�o��
			else
			{
				ball[i].SetTopLeft(int(ball[i].x), int(ball[i].y));
			}
			// ball[i].ShowBitmap();
			// ball[i].RenewCoordinate(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
		}
	}
}

void CGameStateRun::checkBoxBallCollision()
{

	for (int i = 0; i < ball_count; i++)
	{
		for (int j = 0; j < box_count; j++)
		{
			if (ball[i].click_flag == 1)
			{
				if (box[j].box_count > 0)
				{

					IsOverlap_Direction(ball[i], box[j]);
					// show_text_score();
					if (CMovingBitmap::IsOverlap(box[j].image, ball[i].ball_image))
					{
						// show_text_score();
						if (ball[i].xDirectionChange_flag == 1)
						{
							ball[i].dx *= -1;
							ball[i].xDirectionChange_flag = 0;
							// show_text_score();
							box[j].box_count -= 1;
						}
						else if (ball[i].yDirectionChange_flag == 1)
						{
							ball[i].dy *= -1;
							ball[i].yDirectionChange_flag = 0;
							box[j].box_count -= 1;
							// show_text_score();
						}
					}
					ball[i].x += ball[i].dx;
					ball[i].y += ball[i].dy;
					ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
					ball[i].ShowBitmap();
					// ball[i].RenewCoordinate((int)(ball[i].x), (int)(ball[i].y));
				}
			}
		}
	}
}

void CGameStateRun::IsOverlap_Direction(Ball &ball, Box box)
{
	if ((ball.GetLeft() >= box.GetLeft() - ball.ballWidth) && (ball.GetLeft() <= box.GetLeft() + box.boxWidth))
	{
		if ((ball.GetTop()) == (box.GetTop() - ball.ballWidth + 1) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth))
		{
			ball.SetyDirectionChange_flag(1);
			question.ShowBitmap();
		}
		if ((ball.GetTop()) == (box.GetTop() + box.boxWidth + 1) || (ball.GetTop()) == (box.GetTop() + box.boxWidth + 2))
		{
			ball.SetyDirectionChange_flag(1);
			question.ShowBitmap();
		}
	}
	if ((ball.GetTop() >= box.GetTop() - ball.ballWidth) && (ball.GetTop() <= box.GetTop() + box.boxWidth))
	{
		question.ShowBitmap();
		if ((ball.GetLeft() + ball.ballWidth == box.GetLeft() + 1) || (ball.GetLeft() + ball.ballWidth == box.GetLeft()))
		{
			ball.SetxDirectionChange_flag(1);
			question.ShowBitmap();
		}
		if ((ball.GetLeft() == box.GetLeft() + box.boxWidth + 2) || (ball.GetLeft() == box.GetLeft() + box.boxWidth + 1))
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
	image.SetTopLeft(x, y);
}

void Box::ShowText()
{
	CDC *pDC = CDDraw::GetBackCDC();
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

	CDDraw::ReleaseBackCDC();
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
	dy = (mouse_y - y) / pow(pow((mouse_x - x), 2) + pow((mouse_y - y), 2), 0.5);
}
void Ball::SetyDirectionChange_flag(bool new_flag)
{
	yDirectionChange_flag = new_flag;
}
void Ball::SetxDirectionChange_flag(bool new_flag)
{
	xDirectionChange_flag = new_flag;
}
