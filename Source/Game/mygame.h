/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 */

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////
	enum Status { READY, RUNNING, DEAD_Ball };
	enum AUDIO_ID
	{				// �w�q�U�ح��Ī��s��
		AUDIO_DING, // 0
		AUDIO_LAKE, // 1
		AUDIO_NTUT	// 2
	};
	class Bubble {
	public:
		Bubble(int IsBubble_flag = 0,int x = -100, int y = -100);
		CMovingBitmap image;
		void Init();
		void ShowImage();
		void SetTopLeft(int x, int y);
		int x;
		int y;
		int GetLeft();
		int GetTop();
		int IsBubble_flag = 0;
		int IsShow_flag = 1;

	};
	class Box
	{
	public:
		Box(int box_count, int Boxtype_flag=0, int x = -100, int y = -100);
		int box_count;
		int changeBall_flag;
		CMovingBitmap image;
		void Init();
		void ShowImage();
		void ShowText(CDC* pDC);
		void UnshowBitmap();
		void SetTopLeft(int x,int y);

		int x;
		int y;
		int GetLeft();
		int GetTop();
		// void IsOverlap_Direction(Ball ball);
		int boxWidth = 52;
		int box_count_Init=0;
		int Boxtype_flag;

	};

	//class Box_eat : public Box {
	//public:
	//	int box_count;
	//	int x;
	//	int y;
	//	int box_count_Init;
	//	bool Box_eat_flag;
	//	// Constructor
	//	Box_eat(int box_count, int x = -100, int y = -100, bool Box_eat_flag = 0);
	//};

	class Ball
	{
	public:
		Ball(int x, int y);
		CMovingBitmap ball_image;

		double x; // �y��
		double y;

		double dx = 0;
		double dy = 0;

		int mouse_x; // �y��
		int mouse_y;

		int ballWidth = 18;

		int GetLeft();
		int GetTop();

		bool xDirectionChange_flag = 0;
		bool yDirectionChange_flag = 0;
		bool ballUnShow_flag = 0;

		void Init();
		void ShowBitmap();
		void UnshowBitmap();
		void SetTopLeft(int set_x, int set_y);
		void RenewCoordinate(int set_x, int set_y);
		void Ball_shot(double x, double y, int mouse_x, int mouse_y);
		void SetxDirectionChange_flag(bool new_flag);
		void SetyDirectionChange_flag(bool new_flag);
		bool click_flag = 0;
		Status ball_status = Status::READY;
		
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame *g);
		void OnInit();								   // �C������Ȥιϧγ]�w
		void OnBeginState();						   // �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT);				   // �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point); // �B�z�ƹ����ʧ@
		static bool CGameStateInit::debug_flag;

	protected:
		void OnShow(); // ��ܳo�Ӫ��A���C���e��
	private:
		void show_text(int phase);
		void load_background();

		CMovingBitmap logo; // csie��logo
		CMovingBitmap background;
		CMovingBitmap character;
		CMovingBitmap ball;
		CMovingBitmap start;

		bool character_flag = 0;
		bool ball_flag = 0;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState(); // �]�w�C�������һݪ��ܼ�
		void OnInit();		 // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point); // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);   // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);   // �B�z�ƹ����ʧ@
		void OnRButtonDown(UINT nFlags, CPoint point); // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);   // �B�z�ƹ����ʧ@
		void ballMove(int i);
		void checkBallCollision(int i);
		int level = 1;
		bool click_flag = 0;
		int ball_return = 0;
		int canva_boxheight = 8;
		int canva_boxwidth = 7;
		bool touch_canva_lose_flag = 0;

		Status status = Status::READY;

		static int CGameStateRun::phase;
		static bool CGameStateRun::sub_phase;

	protected:
		void OnMove(); // ���ʹC������
		void OnShow(); // ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap background;
		CMovingBitmap frame;
		CMovingBitmap bbman;

		int boxTotalLevel = 15;
		int boxTotalCountinLevel = 7;
		int total_score_phase[2][6] = { {23,90,22,99,101,199},{7,17,7,19,18,31} };

		int ball_gotoRunning = 0;
		int ball_gotoRunning2 = 0;

		Box box[15][7] = {	{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) },
							{ Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0) } };

		Bubble bubble[15][7] = {	{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) },
									{ Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0),Bubble(0) } };


		int currentL_ball_x;
		int currentR_ball_x;
		int currentU_ball_y;
		int currentD_ball_y;

		int ball_count = 1;
		int ball_count_reset = 1;
		int ball_count_load = 10;


		Ball ball[10] = {Ball(223, 560),Ball(223, 560),Ball(223, 560),Ball(223, 560),Ball(223, 560), Ball(223, 560),Ball(223, 560), Ball(223, 560) ,Ball(223, 560),Ball(223, 560) };

		void load_background();
		void checkCanvasCollision();
		void checkBoxBallCollision();
		void checkBallAdd();
		void IsOverlap_Direction(Ball &ball, Box box);
		void show_text();
		void win_phase();
		void lose_phase();
		void ReadMap();
		void ReadBubble();
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point); // �B�z�ƹ����ʧ@
		void OnBeginState();						   // �]�w�C�������һݪ��ܼ�
		void OnInit();

	protected:
		void OnMove(); // ���ʹC������
		void OnShow(); // ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap background;
		int counter; // �˼Ƥ��p�ƾ�
		void show_text();
		void load_background();
	};
}
