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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	load_background();
	//
	//Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

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

		// �����y���u��
		if (ball_flag == 0) {
			// ���y�V�U����
			ball.SetTopLeft(ball.GetLeft(), ball.GetTop() + 1);

		}
		else if (ball_flag == 1) {
			// ���y�V�W����
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