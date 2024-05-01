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
	enum Status { READY, RUNNING };
	enum AUDIO_ID
	{				// �w�q�U�ح��Ī��s��
		AUDIO_DING, // 0
		AUDIO_LAKE, // 1
		AUDIO_NTUT	// 2
	};
	class Ball;

	class Box
	{
	public:
		Box(int box_count, int x=-100, int y=-100);
		int box_count;
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
	};

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

		void Init();
		void ShowBitmap();
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

	protected:
		void OnShow(); // ��ܳo�Ӫ��A���C���e��
	private:
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
		Status status = Status::READY;

	protected:
		void OnMove(); // ���ʹC������
		void OnShow(); // ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap background;
		CMovingBitmap frame;

		int boxTotalLevel = 8;
		int boxTotalCountinLevel = 7;
		int total_score = 14;
		//Box box_array[] = {		}
		Box box[8][7] = { {Box(1), Box(0),Box(1), Box(0), Box(0), Box(0),Box(0)},
						{Box(0), Box(2),Box(0), Box(2), Box(0), Box(0),Box(2)},
						{Box(0), Box(0),Box(0), Box(0), Box(3), Box(3),Box(0)},
						{Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0)},
						{Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0)},
						{Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0)},
						{Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0)},
						{Box(0), Box(0),Box(0), Box(0), Box(0), Box(0),Box(0)}
							
	};
		/*
		Box box[15][7] = {	{Box(1), Box(0),Box(1), Box(0), Box(0), Box(0),Box(0)},
							{Box(0), Box(2),Box(0), Box(2), Box(0), Box(0),Box(2)},
							{Box(3), Box(0),Box(0), Box(0), Box(3), Box(3),Box(0)},
							{Box(0), Box(4),Box(0), Box(0), Box(0), Box(4),Box(4)},
							{Box(0), Box(0),Box(5), Box(5), Box(0), Box(0),Box(0)},
							{Box(6), Box(6),Box(6), Box(0), Box(0), Box(0),Box(6)},
							{Box(0), Box(0),Box(0), Box(7), Box(7), Box(7),Box(0)},
							{Box(8), Box(8),Box(0), Box(0), Box(8), Box(0),Box(0)},
							{Box(0), Box(0),Box(9), Box(9), Box(9), Box(9),Box(0)},
							{Box(10), Box(10),Box(0), Box(0), Box(0), Box(10),Box(10)},
							{Box(0), Box(11),Box(11), Box(0), Box(0), Box(11),Box(11)},
							{Box(12), Box(0),Box(12), Box(12), Box(12), Box(12),Box(0)},
							{Box(13), Box(0),Box(0), Box(0), Box(0), Box(0),Box(13)},
							{Box(0), Box(14),Box(0), Box(0), Box(0), Box(0),Box(0)},
							{Box(15), Box(0),Box(0), Box(0), Box(0), Box(0),Box(15)}
						};
		*/
		//Box box[8] = {Box(1, 47 + 52 * 6, 164 + 52 * 7), Box(1, 47 + 52 * 6, 164 + 52 * 6), Box(10, 47 + 52 * 6, 164 + 52 * 5), Box(1, 47 + 52 * 5, 164 + 52 * 4), Box(10, 47 + 52 * 5, 164 + 52 * 3), Box(1, 47 + 52 * 5, 164 + 52 * 2), Box(10, 47 + 52 * 5, 164), Box(1, 47 + 52 * 5, 164 + 52)};

		int currentL_ball_x;
		int currentR_ball_x;
		int currentU_ball_y;
		int currentD_ball_y;

		int ball_count = 2;
		Ball ball[2] = {Ball(223, 540), Ball(203, 520)};

		CMovingBitmap question;
		void load_background();
		void checkCanvasCollision();
		void checkBoxBallCollision();
		void IsOverlap_Direction(Ball &ball, Box box);
		

		void show_text_score();
		void showBallMove();
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
