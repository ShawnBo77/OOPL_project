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

#include "Character.h"
#include "Map.h"
#include "MapForBoss.h"
#include "MapS1.h"
#include "MapS2.h"
#include "MapS3.h"
#include "MapS4.h"
#include "MapS5.h"
#include "MapS6.h"
#include "Util.h"
#include "PropsBook.h"
#include "CharacterStatus.h"
#include "Monster.h"
#include "MonsterCactus.h"
#include "MonsterCactusMutation.h"
#include "MonsterBanana.h"
#include "MonsterShrimp.h"
#include "MonsterTree.h"
#include "MonsterMosquito.h"
#include "MonsterBoss.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
	protected:
		void isChoiceChange();
		void OnMove();
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void instructionsPageShow();
	private:
		bool isMouseOnArrowR(CPoint point);
		bool isMouseOnArrowL(CPoint point);
		BeginningStage stage;
		InstructionsPage instructionsPage;
		int record; //1代表instructionsPage第一頁，2代表第二頁
		CMovingBitmap startMenu;
		CMovingBitmap startMenuChoice;
		CMovingBitmap staff;
		CMovingBitmap instructionsPage01;
		CMovingBitmap instructionsPage02;
		CMovingBitmap instructionsPage03;
		CMovingBitmap instructionsPageC;
		CMovingBitmap whiteX;
		CMovingBitmap arrowL;
		CMovingBitmap arrowR;
		int choice;
		int lastChoice;
		int yChoice;
		bool onChoice;
		bool isMouseOnX;
		bool isArrowLShow;
		bool isArrowRShow;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void LightBulbOnShow();
		void ShowData();
		void monsterInitialize();
	private:
		void gameCompleteNoteShow();
		void bgmPlayer();
		void stopAllBgm();
		Map* GetCurrentMap();
		//CMovingBitmap	monster;
		Character		character;
		MapForBoss		bossMap;
		MapS1 mapS1;
		MapS2 mapS2;
		MapS3 mapS3;
		MapS4 mapS4;
		MapS5 mapS5;
		MapS6 mapS6;
		PropsBook		propsBook;
		CharacterStatus characterStatus;
		Stage currentStage;
		Stage lastStage;
		bool characterStatusCall;
		bool haveCalledCharacterStatus;
		bool gamePause;
		vector<Monster*> monsterS1;
		vector<Monster*> monsterS2;
		vector<Monster*> monsterS3;
		vector<Monster*> monsterS4;
		vector<Monster*> monsterS5;
		vector<Monster*> monsterS6;
		vector<Monster*> monsterS7;

		bool messageShowFlag;


		CPoint mousePosition;
		CMovingBitmap lightBulb;
		CMovingBitmap gameComplete;
		bool gameCompleteFlag;
		bool isStageChanged; //for bmgPlayer
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
		bool isBgmPlayed;
		CMovingBitmap gameOver;
	};
}