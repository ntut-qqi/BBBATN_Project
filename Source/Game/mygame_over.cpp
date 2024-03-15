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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	load_background();


}

void CGameStateOver::OnShow()
{
	if ( sub_phase == 0) {
		background.SetFrameIndexOfBitmap(0);
	}
	else if(phase != 6 && sub_phase==1)
	{
		background.SetFrameIndexOfBitmap(1);
	}
	else if (phase==6 && sub_phase==1)
	{
		background.SetFrameIndexOfBitmap(2);
	}
	background.ShowBitmap();

	show_text();

}

void CGameStateOver::show_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	
	if (phase==1 && sub_phase == 0)	{		// 第1關 輸
		CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 62, 376, "You LOSE ?!!");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 173, 450, " Level 1 ");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(55, 55, 55), 800);
		CTextDraw::Print(pDC, 103, 561-4, "  MAIN");
		CTextDraw::Print(pDC, 100, 585-4, "  MENU");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(55, 55, 55), 800);
		CTextDraw::Print(pDC, 260, 561-4, "  Play");
		CTextDraw::Print(pDC, 255, 585 - 4, "  AGAIN");
	}else if (phase == 1 && sub_phase == 1)				// 第1關 win
	{		
		CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 108, 376, "VICTORY !");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 173, 450, " Level 1 ");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(55, 55, 55), 800);
		CTextDraw::Print(pDC, 180+2, 561 - 6, "  NEXT");
		CTextDraw::Print(pDC, 175+2, 585 - 6, "  LEVEL");
	}else if (phase == 6 && sub_phase == 1)				
	{
		CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(55, 55, 55), 800);
		CTextDraw::Print(pDC, 108-45, 376, "ALL CLEAR !!");

		CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(55, 55, 55), 800);
		CTextDraw::Print(pDC, 40+22, 450, "YOU PASS ALL THE LEVEL !! ");

		
	}


	CDDraw::ReleaseBackCDC();

}

void CGameStateOver::load_background()
{

		background.LoadBitmap({ "resources/lose_background.bmp","resources/win_background.bmp", "resources/pass_background.bmp" });
		background.SetTopLeft(0, 0);
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (sub_phase == 0) 
	{
		if ((point.x >= 75 && point.x <= 213) && (point.y >= 547 && point.y <= 611))
		{
			GotoGameState(GAME_STATE_INIT);
		}
		else if ((point.x >= 235 && point.x <= 375) && (point.y >= 547 && point.y <= 611))
		{
			GotoGameState(GAME_STATE_RUN);
		}
	}
	else if(sub_phase ==1){
		if ((point.x >= 154 && point.x <= 294) && (point.y >= 544 && point.y <= 610))
		{
			GotoGameState(GAME_STATE_RUN);
		}
	}
		

}

