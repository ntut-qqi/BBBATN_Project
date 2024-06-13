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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////
//bool CGameStateInit::debug_flag = 0;

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	
	load_background();
	
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x31) 
	{
		CGameStateRun::phase = 1;
		show_text(1);
	}
	else if (nChar == 0x32) {
		CGameStateRun::phase = 2;
		show_text(2);
	}
	else if (nChar == 0x33) {
		CGameStateRun::phase = 3;
		show_text(3);
	}
	else if (nChar == 0x34) {
		CGameStateRun::phase = 4;
		show_text(4);
	}
	else if (nChar == 0x35) {
		CGameStateRun::phase = 5;
		show_text(5);
	}
	else if (nChar == 0x36) {
		CGameStateRun::phase = 6;
		show_text(6);
	}
	else if (nChar == 0x44) {	//D 
		CGameStateRun::debug_flag = 1;
		
	}
	else if (nChar == 0x46) {	//F
		CGameStateRun::debug_flag = 0;

	}

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x >= 143 && point.x<=295) && (point.y >= 548 && point.y <= 618))
	{
		GotoGameState(GAME_STATE_RUN);  
	}
}


void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	character.ShowBitmap();
	ball.ShowBitmap();
	start.ShowBitmap();


	for (int i = 0; i < 2; i++) {
		if (character.GetLeft() == 300) {
			character_flag = 1;
		}
		else if (character.GetLeft() == 80) {
			character_flag = 0;
		}

		if (character_flag == 0) {
			character.SetTopLeft(character.GetLeft() + 1, character.GetTop());
		}
		if (character_flag == 1) {
			character.SetTopLeft(character.GetLeft() - 1, character.GetTop());
		}
	}

	for (int i = 0; i < 5; i++) {
		if (ball.GetTop() == 535) {
			ball_flag = 1;
		}
		else if (ball.GetTop() == 470) {
			ball_flag = 0;
		}

		// 模擬球的彈跳
		if (ball_flag == 0) {
			// 讓球向下移動
			ball.SetTopLeft(ball.GetLeft(), ball.GetTop() + 1);

		}
		else if (ball_flag == 1) {
			// 讓球向上移動
			ball.SetTopLeft(ball.GetLeft(), ball.GetTop() - 1);
		}
	}


}

void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "resources/start_background.bmp" });
	background.SetTopLeft(0, 0);

	character.LoadBitmapByString({ "resources/char_init.bmp"},RGB(0, 0, 0));
	character.SetTopLeft(130, 130); 

	ball.LoadBitmapByString({ "resources/ball.bmp" },RGB(0,0,0));
	ball.SetTopLeft(216, 531);

	start.LoadBitmapByString({ "resources/play-button.bmp" }, RGB(0, 0, 0));
	start.SetTopLeft(143, 548);
}

void CGameStateInit::show_text(int phase) {
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 400, 80, "Set phase to ");

	CDDraw::ReleaseBackCDC();
}