#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	for (int i = 0; i < 2; i++) {
		box_list[i].LoadBitmap({ "resources/box-blue.bmp","resources/box-blue.bmp" }, RGB(0, 0, 0));
		box_list[i].SetTopLeft(46+52*i, 164);
	}
	for (int j = 0; j < 3; j++) {
		ball[j].LoadBitmap({ "resources/ball.bmp","resources/ball.bmp","resources/ball.bmp" }, RGB(0, 0, 0));
		ball[j].SetTopLeft(77 + 52 * j, 344);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//GotoGameState(GAME_STATE_OVER);

}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	frame.ShowBitmap();
	box.ShowBitmap();
	for (int i = 0; i < 2; i++) {
		box_list[i].ShowBitmap();
	};
	checkCanvasCollision();
}

void CGameStateRun::load_background() {
	background.LoadBitmapByString({ "resources/game_background.bmp" });
	background.SetTopLeft(0, 0);

	frame.LoadBitmapByString({ "resources/frame.bmp" });
	frame.SetTopLeft(42, 160);

	box.LoadBitmapByString({ "resources/box-blue.bmp"},RGB(0,0,0));
	box.SetTopLeft(46+52*6, 164+52*7);

	}

void CGameStateRun::checkCanvasCollision() {
	
	//ball[0].UnshowBitmap();
	if (ball[0].GetLeft() <= 54 || 400 < ball[0].GetLeft()) {
		dx *= -1;
		//dy *= -1;
	}
	else if (ball[0].GetTop() <= 164 || ball[0].GetTop() >= 560) {
		//dx *= -1;
		dy *= -1;
	}
	ball[0].SetTopLeft(ball[0].GetLeft() + dx, ball[0].GetTop() + dy);
	ball[0].ShowBitmap();
}