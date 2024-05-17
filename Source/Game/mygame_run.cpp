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

int CGameStateRun::phase=1;
bool CGameStateRun::sub_phase=0;


/////////////////////////////////////////////////////////////////////////////
// ï¿½oï¿½ï¿½classï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½ï¿½ï¿½æª«ï¿½ï¿½Aï¿½Dï¿½nï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½{ï¿½ï¿½ï¿½ï¿½ï¿½bï¿½oï¿½ï¿½
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState() // ï¿½]ï¿½wï¿½Cï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»Ýªï¿½ï¿½Ü¼ï¿½
{
	for (int i = 0; i < boxTotalLevel; i++)
	{
		for (int j = 0; j < boxTotalCountinLevel; j++)
		{
			box[CGameStateRun::phase-1][i][j].Init();
			bubble[i][j].Init();
		}
	}
	for (int i = 0; i < ball_count_load; i++)
	{
		ball[i].Init();
		ball[i].ball_status = Status::DEAD_Ball;
	}
}

void CGameStateRun::OnMove() // ï¿½ï¿½ï¿½Ê¹Cï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
{
	checkCanvasCollision();
	checkBallAdd();
	checkBoxBallCollision();
	if (status == Status::READY)
	{
		for (int i = 0; i < level; i++)
		{
			for (int j = 0; j < boxTotalCountinLevel; j++)
			{
				box[CGameStateRun::phase-1][i][j].SetTopLeft(47 + j * box[CGameStateRun::phase - 1][i][j].image.GetWidth(), 164 + (level - i - 1) * box[CGameStateRun::phase - 1][i][j].image.GetHeight());
				bubble[i][j].SetTopLeft(47 + j * 52, 164 + (level - i - 1) * 52);

			}
		}
	}


	int ball_return = 0;
	for (int i = 0; i < ball_count; i++)//
	{
		if (status == Status::RUNNING && ball[i].click_flag == 0)	//¨âÁû²y³£¸I¦a	//²y¸I©³ÅÜ0
		{
			ball_return += 1;
		}
	}
	//all ball dead
	if (ball_return == ball_count && status == Status::RUNNING)
	{
		status = Status::READY;
		level += 1;
		ball_gotoRunning = 0;
	}
	//³Ó§Q¶i¤JGAME_STATE_OVER

	//check if lose
	if (level >= canva_boxheight) {
		int check_boxlevel_index = 0;
		check_boxlevel_index = level - 8;
		for (int i = 0; i < 7; i++) {
			if (box[CGameStateRun::phase - 1][check_boxlevel_index][i].box_count > 0) {
				touch_canva_lose_flag = 1;
			}
		}
	}
	//if win
	for (int i = 1; i < 7; i++) {
		if ((current_score == total_score_phase[i-1]) && (phase == i)) {		//win phase
			win_phase();
		}	
	}
	//if lose
	for (int i = 1; i < 7; i++) {
		if ((touch_canva_lose_flag == 1) && (phase == i)) {		//win phase
			lose_phase();
		}
	}
	//check win lose & goto GAME_STATE_OVER
	
	//if (touch_canva_lose_flag == 1 ) {
	//}
	//lose
	
	//int checkBallStatus = 0;
	//for (int i = 0; i < ball_count; i++) {
	//	if (ball[i].ball_status == Status::READY) {//§PÂ_¨CÁû²y³£ready
	//		checkBallStatus += 1;
	//	}
	//}
	//if (checkBallStatus == ball_count) {//try again
	//	phase = 1;
	//	sub_phase = 0;
	//	current_score = 0;
	//	level = 0;
	//	status = Status::RUNNING;
	//	GotoGameState(GAME_STATE_OVER);
	//}


	//else if (current_score == total_score_phase2 && (phase==2)) {	//²Ä2Ãö win
	//	phase = 2;
	//	sub_phase = 1;
	//	GotoGameState(GAME_STATE_OVER);
	//}
	//else if (current_score == total_score_phase3 && (phase == 3)) {	//²Ä3Ãö win
	//	phase = 2;
	//	sub_phase = 1;
	//	GotoGameState(GAME_STATE_OVER);
	//}
	//else if (current_score == total_score_phase4 && (phase == 3)){	//²Ä4Ãö win
	//	phase = 2;
	//	sub_phase = 1;
	//	GotoGameState(GAME_STATE_OVER);
	//}
	//else if (current_score == total_score_phase5 && (phase == 4)) {	//²Ä5Ãö win
	//	phase = 2;
	//	sub_phase = 1;
	//	GotoGameState(GAME_STATE_OVER);
	//}
	//else if (current_score == total_score_phase6 && (phase == 5)) {	//²Ä6Ãö win
	//	phase = 2;
	//	sub_phase = 1;
	//	GotoGameState(GAME_STATE_OVER);
	//}

}

void CGameStateRun::win_phase() {
	int checkBallStatus = 0;
	for (int i = 0; i < ball_count; i++) {
		if (ball[i].ball_status == Status::DEAD_Ball) {//§PÂ_¨CÁû²y³£ready
			checkBallStatus += 1;
		}
	}
	if (checkBallStatus == ball_count) {//try again
		sub_phase = 1;
		current_score = 0;
		level = 0;
		ball_gotoRunning = 0;
		status = Status::RUNNING;
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::lose_phase() {
	int checkBallStatus = 0;
	for (int i = 0; i < ball_count; i++) {
		if (ball[i].ball_status == Status::DEAD_Ball) {//§PÂ_¨CÁû²y³£ready
			checkBallStatus += 1;
		}
	}
	if (checkBallStatus == ball_count) {//try again
		sub_phase = 0;
		current_score = 0;
		level = 0;
		ball_gotoRunning = 0;
		touch_canva_lose_flag = 0;
		ball_count = ball_count_reset;
		for (int i = 0; i < ball_count; i++) {
			ball[i].ballUnShow_flag = 0;
			ball[i].SetTopLeft(223, currentD_ball_y);
			ball[i].RenewCoordinate(223, currentD_ball_y);
			ball[i].ball_status = Status::DEAD_Ball;
		}
		status = Status::RUNNING;
		GotoGameState(GAME_STATE_OVER);
	}
}


void CGameStateRun::OnInit() // ï¿½Cï¿½ï¿½ï¿½ï¿½ï¿½ï¿½?¤Î¹Ï§Î³]ï¿½w
{
	load_background();

	for (int i = 0; i < boxTotalLevel; i++)
	{
		for (int j = 0; j < boxTotalCountinLevel; j++)
		{
			box[CGameStateRun::phase - 1][i][j].Init();
			bubble[i][j].Init();
		}
	}
	for (int i = 0; i < ball_count_load; i++)
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // ï¿½Bï¿½zï¿½Æ¹ï¿½ï¿½ï¿½ï¿½Ê§@
{
	//if (status == Status::READY) {
		status = Status::RUNNING;
		// ball_status = Status::RUNNING;
		for (int i = 0; i < ball_count; i++)
		{
			ball[i].ball_status = Status::READY;
			ball[i].mouse_x = point.x;
			ball[i].mouse_y = point.y;
			ball[i].Ball_shot(ball[i].x, ball[i].y, ball[i].mouse_x, ball[i].mouse_y);
			ball[i].click_flag = 1;
		}
	//}
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // ï¿½Bï¿½zï¿½Æ¹ï¿½ï¿½ï¿½ï¿½Ê§@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // ï¿½Bï¿½zï¿½Æ¹ï¿½ï¿½ï¿½ï¿½Ê§@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // ï¿½Bï¿½zï¿½Æ¹ï¿½ï¿½ï¿½ï¿½Ê§@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // ï¿½Bï¿½zï¿½Æ¹ï¿½ï¿½ï¿½ï¿½Ê§@
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	frame.ShowBitmap();
	bbman.ShowBitmap();
	question.ShowBitmap();
	show_text();
	for (int i = 0; i < level; i++)
	{
		for (int j = 0; j < boxTotalCountinLevel; j++)
		{
			if (bubble[i][j].IsShow_flag == 1) {
				bubble[i][j].ShowImage();
			}

			if (box[CGameStateRun::phase - 1][i][j].box_count <= 0)
			{
				continue;
			}
			box[CGameStateRun::phase - 1][i][j].ShowImage();
		}
	}
	for (int i = 0; i < ball_count; i++)
	{
		//if (ball[i].ballUnShow_flag == 1) {
			//ball[i].ballUnShow_flag = 0;
			//ball[i].ball_status = Status::READY;
			//ball[i].SetTopLeft(223, currentD_ball_y);
			//ball[i].RenewCoordinate(223, currentD_ball_y);
		//	continue;
		//}
		ball[i].ShowBitmap();
	}
	
	CDC *pDC = CDDraw::GetBackCDC();
	for (int i = 0; i < level; i++)
	{
		for (int j = 0; j < boxTotalCountinLevel; j++)
		{
			box[CGameStateRun::phase - 1][i][j].ShowText(pDC);
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

	bbman.LoadBitmapByString({ "resources/bbman.bmp" }, RGB(0, 0, 0));
	bbman.SetTopLeft(220, 500);

}
void CGameStateRun::checkBallAdd() {
	

}

void CGameStateRun::checkCanvasCollision()
{

	for (int i = 0; i < ball_count; i++)
	{
		if (ball[i].click_flag == 1)
		{
			if (ball[i].GetLeft() <= 45)
			{
				ball[i].dx *= -1;
				//ball[i].x = max(46, int(ball[i].GetLeft()));
				//continue;
			}
			if (ball[i].GetLeft() >= 395) {
				ball[i].dx *= -1;
				//ball[i].x = min(394, int(ball[i].GetLeft()));
			}
			if (ball[i].GetTop() <= 164)
			{
				ball[i].dy *= -1;
				//continue;

			}
			//if (ball[i].GetLeft() == 395 || ball[i].GetLeft() == 396 || ball[i].GetLeft() == 397)
			//{
			//	ball[i].dx *= -1;
			//	break;
			//}
			//if (ball[i].GetLeft() == 45 || ball[i].GetLeft() == 46 || ball[i].GetLeft() == 47)
			//{
			//	ball[i].dx *= -1;
			//	break;
			//}
			//if (ball[i].GetTop() == 164 || ball[i].GetTop() == 165 || ball[i].GetTop() == 166)
			//{
			//	ball[i].dy *= -1;
			//	break;

			//}
			if (ball[i].GetTop() >= 564)
			{
				// status = Status::READY;
				ball[i].click_flag = 0;
				ball[i].ball_status = Status::DEAD_Ball;
				// ball[i].x = ball[i].GetLeft();
				currentD_ball_y = min(560, int(ball[i].GetTop() + ball[i].dy));
				//currentD_ball_y = 560;
				int a;
				a = abs(ball[i].GetLeft() - 223);
				if (a > 0) {
					for (int j = 0; j < a; j++) {
						if (ball[i].GetLeft() > 223) {
							ball[i].SetTopLeft(((ball[i].GetLeft()) - 1), currentD_ball_y);
							ball[i].RenewCoordinate(((ball[i].GetLeft()) - 1), currentD_ball_y);
						}
						else {
							ball[i].SetTopLeft(((ball[i].GetLeft()) + 1), currentD_ball_y);
							ball[i].RenewCoordinate(((ball[i].GetLeft()) + 1), currentD_ball_y);
						}
					}
				}
				else {
					ball[i].SetTopLeft(223, currentD_ball_y);
					ball[i].RenewCoordinate(223, currentD_ball_y);
				}
				
			}
			// max min
			// if (ball[i].GetLeft() + ball[i].dx <= 45)
			//{
			//	currentL_ball_x = max(45, int(ball[i].GetLeft() + ball[i].dx));
			//	//ball[i].SetTopLeft(currentL_ball_x, int(ball[i].GetTop() + ball[i].dy));
			//}
			// else if (ball[i].GetLeft() + ball[i].dx >= 395)
			//{
			//	currentR_ball_x = min(395, int(ball[i].GetLeft() + ball[i].dx));
			//	//ball[i].SetTopLeft(currentR_ball_x, int(ball[i].GetTop() + ball[i].dy));
			//}
			// else if (ball[i].GetTop() <= 164)
			//{
			//	currentU_ball_y = max(164, int(ball[i].GetTop() + ball[i].dy));
			//	//ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx), currentU_ball_y);
			//}
			// else if (ball[i].GetTop() >= 564)
			//{
			//	currentD_ball_y = min(564, int(ball[i].GetTop() + ball[i].dy));
			//	//ball[i].SetTopLeft(int(ball[i].GetLeft() + ball[i].dx+2), currentD_ball_y);
			//}
			//// ï¿½|ï¿½]ï¿½oï¿½ï¿½
			// else
			//{
			//	//ball[i].SetTopLeft(int(ball[i].x), int(ball[i].y));
			// }
			//  ball[i].ShowBitmap();
			//  ball[i].RenewCoordinate(ball[i].GetLeft() + ball[i].dx, ball[i].GetTop() + ball[i].dy);
		}
	}
}

void CGameStateRun::checkBoxBallCollision()
{
	for (int i = 0; i < ball_count; i++)
	{
		if (ball[i].ball_status == Status::RUNNING|| ball[i].ball_status == Status::READY)
		{
			checkBallCollision(i);
			//ballMove(i);
			if (ball[i].ball_status == Status::READY)
			{
				//ball[i].x += 20 * i * ball[i].dx;
				//ball[i].y += 20 * i * ball[i].dy;
				//ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
				//if (i == ball_gotoRunning) {
				//	ball[i].ball_status = Status::RUNNING;
				//	ball_gotoRunning += 1;
				//}
				ball[i].ball_status = Status::RUNNING;

			}
			if (ball[i].ball_status == Status::RUNNING)
			{
				
				ball[i].x += 3 * ball[i].dx;
				ball[i].y += 3 * ball[i].dy;
				ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
				//ball[i].RenewCoordinate((int)(ball[i].x), (int)(ball[i].y));
				
				//if (ball_gotoRunning == i ) {
				//	ball_gotoRunning += 1;
				//	break;
				//}
				if (ball_gotoRunning == i && (ball_gotoRunning2 < 10)) {
					//ball_gotoRunning += 1;
					ball_gotoRunning2 += 1;
					//if(ball_gotoRunning)
					if (ball_gotoRunning2 == 10) {
						ball_gotoRunning2 = 0;
						ball_gotoRunning += 1;
					}
					break;

				}
			}
		}
	}
}

void CGameStateRun::checkBallCollision(int i)
{
	for (int j = 0; j < level; j++)
	{
		for (int k = 0; k < boxTotalCountinLevel; k++)
		{
			if (ball[i].click_flag == 1)
			{
				if (CMovingBitmap::IsOverlap(bubble[j][k].image, ball[i].ball_image) && bubble[j][k].IsBubble_flag && bubble[j][k].IsShow_flag) {
					ball_count += 1;
					bubble[j][k].IsShow_flag = 0;
				}
				if (box[CGameStateRun::phase - 1][j][k].box_count > 0)
				{
					IsOverlap_Direction(ball[i], box[CGameStateRun::phase - 1][j][k]);
					if (CMovingBitmap::IsOverlap(box[CGameStateRun::phase - 1][j][k].image, ball[i].ball_image))
					{
						if (box[CGameStateRun::phase - 1][j][k].Boxtype_flag == 1) {
							if (box[CGameStateRun::phase - 1][j][k].box_count > 0 ) {
								//ball[i].ballUnShow_flag = 1;
								box[CGameStateRun::phase - 1][j][k].box_count -= 1;
								current_score += 1;
								ball[i].SetTopLeft(223, 560);
								ball[i].RenewCoordinate(223, 560);
								ball[i].ball_status = Status::DEAD_Ball;
								ball[i].click_flag = 0;
							}
						}
						//else if (box[j][k].Boxtype_flag == 2) {
						//	if (box[j][k].box_count > 0) {
						//		ball[i].ballUnShow_flag = 1;
						//		ball_count -= 1;
						//		box[j][k].box_count -= 1;
						//		current_score += 1;
						//		ball[i].ball_status = Status::DEAD_Ball;
						//		ball[i].click_flag = 0;
						//	}
						//}
						else{
							if (ball[i].xDirectionChange_flag == 1)
							{
								ball[i].dx *= -1;
								ball[i].xDirectionChange_flag = 0;
								box[CGameStateRun::phase - 1][j][k].box_count -= 1;
								current_score += 1;
							}
							else if (ball[i].yDirectionChange_flag == 1)
							{
								ball[i].dy *= -1;
								ball[i].yDirectionChange_flag = 0;
								if (box[CGameStateRun::phase - 1][j][k].Boxtype_flag!=2){
									box[CGameStateRun::phase - 1][j][k].box_count -= 1;
									current_score += 1;
								}
							}
						}
					}
				}
			}
		}
	}
}

void CGameStateRun::ballMove(int i)
{
	if (ball[i].ball_status == Status::READY)
	{
		//ball[i].x += 20 * i * ball[i].dx;
		//ball[i].y += 20 * i * ball[i].dy;
		//ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
		//if (i == ball_gotoRunning) {
		//	ball[i].ball_status = Status::RUNNING;
		//	ball_gotoRunning += 1;
		//}
		ball[i].ball_status = Status::RUNNING;
	}
	if (ball[i].ball_status == Status::RUNNING)
	{
		ball[i].x += 3 * ball[i].dx;
		ball[i].y += 3 * ball[i].dy;
		ball[i].SetTopLeft((int)(ball[i].x), (int)(ball[i].y));
		ball[i].RenewCoordinate((int)(ball[i].x), (int)(ball[i].y));
	}
}

void CGameStateRun::IsOverlap_Direction(Ball &ball, Box box)
{
	if ((ball.GetLeft() >= box.GetLeft() - ball.ballWidth) && (ball.GetLeft() <= box.GetLeft() + box.boxWidth))
	{
		if ((ball.GetTop()) == (box.GetTop() - ball.ballWidth) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth + 1) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth + 2) || (ball.GetTop()) == (box.GetTop() - ball.ballWidth + 3))
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
		if ((ball.GetLeft() + ball.ballWidth == box.GetLeft()) || (ball.GetLeft() + ball.ballWidth == box.GetLeft() + 1) || (ball.GetLeft() + ball.ballWidth == box.GetLeft() + 2) || (ball.GetLeft() + ball.ballWidth == box.GetLeft() + 3))
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

void CGameStateRun::show_text()
{
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 45, "SquareFont", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 400, 80, to_string(current_score));
	CTextDraw::ChangeFontLog(pDC, 20, "SquareFont", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 250, 550, "x"+to_string(ball_count));
	CTextDraw::ChangeFontLog(pDC, 35, "SquareFont", RGB(255, 255, 255), 500);
	CTextDraw::Print(pDC, 150, 85, "level "+to_string(phase));

	CDDraw::ReleaseBackCDC();
}

Box::Box(int box_count, int Boxtype_flag, int x, int y)
{
	this->box_count = box_count;
	this->Boxtype_flag = Boxtype_flag;
	this->x = x;
	this->y = y;
	this->box_count_Init = box_count;
}

void Box::ShowImage()
{
	image.ShowBitmap();
}

void Box::Init()
{
	box_count = box_count_Init;
	
	if (Boxtype_flag==1)
	{
	this->image.LoadBitmapByString({ "resources/box-eatBall.bmp" }, RGB(0, 0, 0));
	}
	else if (Boxtype_flag == 2)
	{
		this->image.LoadBitmapByString({ "resources/bottom.bmp" }, RGB(0, 0, 0));
	}
	else if (Boxtype_flag==2)
	{
		this->image.LoadBitmapByString({ "resources/hedgehog.bmp" }, RGB(0, 0, 0));
	}
	else if (box_count >= 16 && box_count <= 20)
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
	else if (box_count == 0)
	{
		this->image.LoadBitmapByString({"resources/box-black.bmp"}, RGB(0, 0, 0));
	}
	
	image.SetTopLeft(x, y);
}

void Box::ShowText(CDC *pDC)
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

void Box::SetTopLeft(int x, int y)
{
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

void Ball::UnshowBitmap()
{
	ball_image.UnshowBitmap();
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
	dy = abs((mouse_y - y) / pow(pow((mouse_x - x), 2) + pow((mouse_y - y), 2), 0.5)) * -1;
}
void Ball::SetyDirectionChange_flag(bool new_flag)
{
	yDirectionChange_flag = new_flag;
}
void Ball::SetxDirectionChange_flag(bool new_flag)
{
	xDirectionChange_flag = new_flag;
}   

//Box_eat::Box_eat(int box_count, int x, int y, bool Box_eat_flag) : Box(box_count, x, y) {
//	this->Box_eat_flag = Box_eat_flag;
//}

Bubble::Bubble(int IsBubble_flag, int x, int y) {
	this->IsBubble_flag = IsBubble_flag;
	this->x = x;
	this->y = y;
}

void Bubble::Init()
{
	if (IsBubble_flag == 1) {
		this->image.LoadBitmapByString({ "resources/power-add-ball.bmp" }, RGB(0, 0, 0));
	}
	else {
		this->image.LoadBitmapByString({ "resources/box-black.bmp" }, RGB(0, 0, 0));
	}
	image.SetTopLeft(x, y);
}

int Bubble::GetLeft()
{
	return image.GetLeft();
}

int Bubble::GetTop()
{
	return image.GetTop();
}

void Bubble::ShowImage()
{
	image.ShowBitmap();
}

void Bubble::SetTopLeft(int x, int y)
{
	image.SetTopLeft(x, y);
}