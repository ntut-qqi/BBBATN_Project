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

void CGameStateRun::OnBeginState()						// 設定每次重玩所需的變數
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	load_background();
	
	for (int j = 0; j < 3; j++) {
		ball[j].LoadBitmap({ "resources/ball.bmp","resources/ball.bmp","resources/ball.bmp" }, RGB(0, 0, 0));
		ball[j].SetTopLeft(240,540);
		ball[j].ShowBitmap();
	}
	box.Init();

	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	GotoGameState(GAME_STATE_OVER);

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	GotoGameState(GAME_STATE_OVER);

}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	frame.ShowBitmap();



	checkCanvasCollision();
	
	box.ShowImage();
	box.ShowText();


}

void CGameStateRun::load_background() {
	background.LoadBitmapByString({ "resources/game_background.bmp" });
	background.SetTopLeft(0, 0);

	frame.LoadBitmapByString({ "resources/frame.bmp" });
	frame.SetTopLeft(42, 160);


	}

void CGameStateRun::checkCanvasCollision() {								//外框碰撞
	
	//ball[0].UnshowBitmap();
	if (ball[0].GetLeft() <= 54 || ball[0].GetLeft() >= 400) {
		dx *= -1;
		
	}
	else if (ball[0].GetTop() <= 164 || ball[0].GetTop() >= 560) {
		dy *= -1;
	}
	ball[0].SetTopLeft(ball[0].GetLeft() + dx, ball[0].GetTop() + dy);
	ball[0].ShowBitmap();
}


Box::Box(int box_count ,int x,int y){
	this->box_count = box_count;
	this->x = x;
	this->y= y;
}	

void Box::ShowImage(){
	image.ShowBitmap();
}

void Box::Init() {
	if (box_count >= 16 && box_count <= 20) {
		this->image.LoadBitmapByString({ "resources/box-blue.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 12 && box_count <= 16) {
		this->image.LoadBitmapByString({ "resources/box-purple.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 8 && box_count <= 12) {
		this->image.LoadBitmapByString({ "resources/box-red.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 4 && box_count <= 8) {
		this->image.LoadBitmapByString({ "resources/box-orange.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 1 && box_count <= 4) {
		this->image.LoadBitmapByString({ "resources/box-yellow.bmp" }, RGB(0, 0, 0));
	}
	image.SetTopLeft(x, y);

}

void Box::ShowText() {
	CDC *pDC = CDDraw::GetBackCDC();
	if (box_count == 1) {
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 22, image.GetTop() + 14, to_string(box_count));
	}
	else if(box_count >= 2 && box_count <= 9){
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 18, image.GetTop() + 14, to_string(box_count));
	}
	else if (box_count ==11) {
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 15, image.GetTop() + 14, "1 1");
	}
	else if (box_count == 10 || (box_count>=12&&box_count<=19)){
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 15, image.GetTop() + 14, to_string(box_count));
	}
	else if (box_count == 20) {
		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, image.GetLeft() + 11, image.GetTop() + 14, to_string(box_count));
	}


	CDDraw::ReleaseBackCDC();
}