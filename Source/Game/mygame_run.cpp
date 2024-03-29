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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState() // 設定每次重玩所需的變數
{
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
	for (int i = 0; i < box_count; i++) {
		for (int j = 0; j < ball_count; j++) {
			if (CMovingBitmap::IsOverlap(box[i].image, ball[j].ball_image)) {
				overlap_flag = 1;
			}
		}
	}
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
	load_background();

	/*for (int j = 0; j < 3; j++)
	{
		ball[j].LoadBitmap({"resources/ball.bmp", "resources/ball.bmp", "resources/ball.bmp"}, RGB(0, 0, 0));
		ball[j].SetTopLeft(240, 540);
		ball[j].ShowBitmap();
	}*/
	for (int i = 0; i < box_count; i++) {
		box[i].Init();
	}
	for (int i = 0; i < ball_count; i++) {
		ball[i].Init();
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
	GotoGameState(GAME_STATE_OVER);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	frame.ShowBitmap();

	checkCanvasCollision();
	checkBoxBallCollision();

	question.ShowBitmap();
	show_text_score();
	for (int i = 0; i < box_count; i++) {
		box[i].ShowImage();
		box[i].ShowText();
	}
	for (int i = 0; i < ball_count; i++) {
		ball[i].ShowBitmap();
	}
}

void CGameStateRun::load_background()
{
	background.LoadBitmapByString({ "resources/game_background.bmp" });
	background.SetTopLeft(0, 0);

	question.LoadBitmapByString({ "resources/question.bmp" });
	question.SetTopLeft(0, 80);

	frame.LoadBitmapByString({ "resources/frame.bmp" });
	frame.SetTopLeft(42, 160);
}

void CGameStateRun::checkCanvasCollision()
{ // 外框碰撞
	//for (int speed = 0; speed < 3; speed++) {
	for (int i = 0; i < ball_count; i++) {

		if (ball[i].GetLeft() <= 45 || ball[i].GetLeft() >= 395)
		{
			ball[i].dx *= -1;
		}
		if (ball[i].GetTop() <= 164 || ball[i].GetTop() >= 564)
		{
			ball[i].dy *= -1;
		}
		//max min
		if (ball[i].GetLeft() + ball[i].dx <= 45) {
			currentL_ball_x = max(45, ball[i].GetLeft() + ball[i].dx);
			ball[i].SetTopLeft(currentL_ball_x, ball[i].GetTop() + ball[i].dy);
		}
		else if (ball[i].GetLeft() + ball[i].dx >= 395) {
			currentR_ball_x = min(395, ball[i].GetLeft() + ball[i].dx);
			ball[i].SetTopLeft(currentR_ball_x, ball[i].GetTop() + ball[i].dy);
		}
		else if (ball[i].GetTop() <= 164) {
			currentU_ball_y = max(164, ball[i].GetTop() + ball[i].dy);
			ball[i].SetTopLeft(ball[i].GetLeft() + ball[i].dx, currentU_ball_y);
		}
		else if (ball[i].GetTop() >= 564) {
			currentD_ball_y = min(564, ball[i].GetTop() + ball[i].dy);
			ball[i].SetTopLeft(ball[i].GetLeft() + ball[i].dx, currentD_ball_y);
		}
		//會跑這個
		else
		{
			ball[i].SetTopLeft(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
		}
		//ball[i].ShowBitmap();
		//ball[i].RenewCoordinate(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
	}
	//}
}

void CGameStateRun::checkBoxBallCollision() {
	for (int i = 0; i < ball_count; i++) {
		for (int j = 0; j < box_count; j++) {
			if (CMovingBitmap::IsOverlap(box[i].image, ball[i].ball_image))
			{
				box[i].IsOverlap_Direction(ball[i]);
				if (box[i].xDirectionChange_flag == 1)
				{
					ball[i].dx *= -1;
				}
				else if(box[i].yDirectionChange_flag == 1)
				{
					ball[i].dy *= -1;
				}
			}
			ball[i].SetTopLeft(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
			ball[i].ShowBitmap();
			ball[i].RenewCoordinate(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
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
		this->image.LoadBitmapByString({ "resources/box-blue.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 12 && box_count <= 16)
	{
		this->image.LoadBitmapByString({ "resources/box-purple.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 8 && box_count <= 12)
	{
		this->image.LoadBitmapByString({ "resources/box-red.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 4 && box_count <= 8)
	{
		this->image.LoadBitmapByString({ "resources/box-orange.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 1 && box_count <= 4)
	{
		this->image.LoadBitmapByString({ "resources/box-yellow.bmp" }, RGB(0, 0, 0));
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

void Box::IsOverlap_Direction(Ball ball)
{
	//新增穿模判斷
	//&& ball.GetTop()>=y && ball.GetTop() <= (y+52)
	//新增img width
	//flag寫在哪
	if (ball.GetLeft()>=x && ball.GetLeft()<=(x+53) && CMovingBitmap::IsOverlap(image, ball.ball_image)) {
		yDirectionChange_flag = 1;
	}
	else if (ball.GetTop() >= y && ball.GetTop() <= (y + 53)&& CMovingBitmap::IsOverlap(image, ball.ball_image))
	{
		xDirectionChange_flag = 1;
	}
}

Ball::Ball(int x, int y) {
	this->x = x;
	this->y = y;
}

void Ball::ShowBitmap()
{
	ball_image.ShowBitmap();
}

void Ball::Init()
{

	this->ball_image.LoadBitmapByString({ "resources/ball.bmp" }, RGB(255, 255, 255));

	ball_image.SetTopLeft(x, y);
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
	//return 0;
}

