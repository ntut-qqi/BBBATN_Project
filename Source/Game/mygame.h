/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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

	enum AUDIO_ID
	{				// 定義各種音效的編號
		AUDIO_DING, // 0
		AUDIO_LAKE, // 1
		AUDIO_NTUT	// 2
	};
	class Ball;

	class Box
	{
	public:
		Box(int box_count, int x, int y);
		int box_count;
		CMovingBitmap image;
		void Init();
		void ShowImage();
		void ShowText();
		int x;
		int y;
		int GetLeft();
		int GetTop();
		void IsOverlap_Direction(Ball ball);
		bool xDirectionChange_flag = 0;
		bool yDirectionChange_flag = 0;


	};

	class Ball
	{
	public:
		Ball(int x, int y);
		CMovingBitmap ball_image;
		
		int x;	//座標
		int y;

		double dx=1;
		double dy=1;

		int mouse_x;	//座標
		int mouse_y;

		int ballWidth = 18;
		
		int GetLeft();
		int GetTop();
		void Init();
		void ShowBitmap();
		void SetTopLeft(int set_x, int set_y);
		void RenewCoordinate(int set_x, int set_y);
		double Ball_shot(int x, int y, int mouse_x, int mouse_y);
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame *g);
		void OnInit();								   // 遊戲的初值及圖形設定
		void OnBeginState();						   // 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT);				   // 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作

	protected:
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		void load_background();

		CMovingBitmap logo; // csie的logo
		CMovingBitmap background;
		CMovingBitmap character;
		CMovingBitmap ball;
		CMovingBitmap start;

		bool character_flag = 0;
		bool ball_flag = 0;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState(); // 設定每次重玩所需的變數
		void OnInit();		 // 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);   // 處理滑鼠的動作
		void OnRButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作
	
		bool click_flag = 0;

	protected:
		void OnMove(); // 移動遊戲元素
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;
		CMovingBitmap frame;

		int box_count=2;
		Box box[2] = { Box(1, 250, 250), Box(10, 47+50, 320) };
		//Box box[2] = { Box(1, 47, 165), Box(10, 47 + 50, 165) };


		int currentL_ball_x;
		int currentR_ball_x;
		int currentU_ball_y;
		int currentD_ball_y;

		int ball_count = 2;
		Ball ball[2] = { Ball(240, 300), Ball(260, 350) };
		
		CMovingBitmap question;
		void load_background();
		void checkCanvasCollision();
		void checkBoxBallCollision();

		void show_text_score();

	
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
		void OnBeginState();						   // 設定每次重玩所需的變數
		void OnInit();

	protected:
		void OnMove(); // 移動遊戲元素
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;
		int counter; // 倒數之計數器
		void show_text();
		void load_background();
	};
}
