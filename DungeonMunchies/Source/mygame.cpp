/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ctime>
#include <ddraw.h>
#include <stdlib.h>
#include <stdio.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Util.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		startMenu.LoadBitmap(IDB_STARTMENU);
		startMenuChoice.LoadBitmap(".\\res\\start_menu_choice.bmp", RGB(0, 0, 0));
		staff.LoadBitmap(".\\res\\staff.bmp");
		//logo.LoadBitmap(IDB_BACKGROUND);
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
		onChoice = false;
		yChoice = 380;
		choice = 0;
		showStaff = false;
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		//const char KEY_ESC = 27;
		//const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (!showStaff)
		{
			if (choice == 1)
			{
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			}
			else if (choice == 2)
			{
				GotoGameState(GAME_STATE_OVER);
			}
			else if (choice == 3)
			{
				showStaff = true;
			}
		}
		else
		{
			if (point.x >= 1306 && point.y <= 60)
			{
				showStaff = false;
			}
		}
	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (!showStaff)
		{
			if (point.x > 603 && point.x < 770)
			{
				if (point.y > 380 && point.y < 446)
				{
					yChoice = 380;
					choice = 1;
					onChoice = true;
				}
				else if (point.y > 465 && point.y < 531)
				{
					yChoice = 465;
					choice = 2;
					onChoice = true;
				}
				else if (point.y > 550 && point.y < 616)
				{
					yChoice = 550;
					choice = 3;
					onChoice = true;
				}
				else
				{
					choice = 0;
				}
			}
			else
			{
				choice = 0;
			}
		}
	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
		//logo.ShowBitmap();
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		//CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		//CFont f,*fp;
		//f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
		//fp=pDC->SelectObject(&f);					// 選用 font f
		//pDC->SetBkColor(RGB(0,0,0));
		//pDC->SetTextColor(RGB(255,255,0));
		//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
		//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
		//if (ENABLE_GAME_PAUSE)
		//	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
		//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		startMenu.SetTopLeft(0, 0);
		startMenu.ShowBitmap();
		if (onChoice)
		{
			startMenuChoice.SetTopLeft(603, yChoice);
			startMenuChoice.ShowBitmap();
		}
		if (showStaff)
		{
			staff.SetTopLeft(0, 0);
			staff.ShowBitmap();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		//ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		gameOver.LoadBitmap(".\\res\\game_over.bmp");
		//
		// 開始載入資料
		//
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (point.x > 340 && point.x < 1085 && point.y > 275 && point.y < 410)
		{
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		}
		if (point.x > 440 && point.x < 975 && point.y > 410 && point.y < 500)
		{
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnShow()
	{
		gameOver.SetTopLeft(0, 0);
		gameOver.ShowBitmap();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Please click \"GAME OVER\" to close the game, or \"PLAY AGAIN\" to restart! (%d)", counter / 30);
		pDC->TextOut(680, 730, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		//ball = new CBall [NUMBALLS];
		//monsterS1.push_back(new MonsterCactus(700, 500, &character));
		monsterS1.push_back(new MonsterTree(1900, 400, &character));

		//monsterS7.push_back(new MonsterShrimp(300, 400, &character));
		//monsterS7.push_back(new MonsterShrimp(600, 400, &character));
		//monsterS7.push_back(new MonsterShrimp(900, 400, &character));
		//monsterS7.push_back(new MonsterCactus(700, 500, &character));
		monsterS7.push_back(new MonsterTree(400, 400, &character));
		//monsterS7.push_back(new MonsterBoss(650, 280, &character));
		//monsterS7.push_back(new MonsterCactus(700, 500, &character));

		monsterCactus.push_back(new MonsterCactus(700, 500, &character));
		monsterShrimp.push_back(new MonsterShrimp(300, 400, &character));
		monsterTree.push_back(new MonsterTree(400, 400, &character));
	}

	CGameStateRun::~CGameStateRun()
	{
		for (vector<Monster*>::iterator it_i = monsterS1.begin(); it_i != monsterS1.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS7.begin(); it_i != monsterS7.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterCactus.begin(); it_i != monsterCactus.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterShrimp.begin(); it_i != monsterShrimp.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterTree.begin(); it_i != monsterTree.end(); ++it_i)
		{
			delete* it_i;
		}
		//delete [] ball;
	}

	void CGameStateRun::OnBeginState()
	{
		//const int BALL_GAP = 90;
		//const int BALL_XY_OFFSET = 45;
		//const int BALL_PER_ROW = 7;
		//const int HITS_LEFT = 10;
		//const int HITS_LEFT_X = 590;
		//const int HITS_LEFT_Y = 0;
		//const int BACKGROUND_X = 60;
		//const int ANIMATION_SPEED = 15;
		//for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		//	int x_pos = i % BALL_PER_ROW;
		//	int y_pos = i / BALL_PER_ROW;
		//	ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		//	ball[i].SetDelay(x_pos);
		//	ball[i].SetIsAlive(true);
		//}

		//eraser.Initialize();
		character.Initialize();
		mapS1.Initialize();
		bossMap.Initialize();
		propsBook.Initialize(&character);
		characterStatus.Initialize(&character);
		characterStatusCall = false;
		haveCalledCharacterStatus = false;
		gamePause = false;
		gameCompleteFlag = false;
		//background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
		currentStage = stage_boss;
		lastStage = currentStage;
		for (unsigned i = 0; i < monsterS1.size(); i++)
		{
			monsterS1[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS7.size(); i++)
		{
			monsterS7[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterCactus.size(); i++)
		{
			monsterCactus[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterShrimp.size(); i++)
		{
			monsterShrimp[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterTree.size(); i++)
		{
			monsterTree[i]->Initialize();
		}
		//help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		//hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
		//hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//
		//if (background.Top() > SIZE_Y)
		//	background.SetTopLeft(60 ,-background.Height());
		//background.SetTopLeft(background.Left(),background.Top()+1);
		//
		// 移動球
		//
		//int i;
		//for (i=0; i < NUMBALLS; i++)
		//	ball[i].OnMove();
		//
		// 移動擦子
		//
		//eraser.OnMove();
		if (character.GetCurrentHp() <= 0)
		{
			GotoGameState(GAME_STATE_OVER);
		}
		if (monsterS7[0]->GetBossDead())
		{
			gameCompleteFlag = true;
			currentStage = stage_game_complete;
		}
		if (gamePause == false)
		{
			switch (currentStage)
			{
			case stage_1:
				for (unsigned i = 0; i < monsterS1.size(); i++)
				{
					monsterS1[i]->OnMove(&mapS1);
				}
				character.OnMove(&mapS1, &monsterS1);
				break;
			case stage_boss:
				for (unsigned i = 0; i < monsterS7.size(); i++)
				{
					monsterS7[i]->OnMove(&bossMap);
				}
				//for (unsigned i = 0; i < monsterCactus.size(); i++)
				//{
				//	monsterCactus[i]->OnMove();
				//}
				//for (unsigned i = 0; i < monsterShrimp.size(); i++)
				//{
				//	monsterShrimp[i]->OnMove();
				//}
				//for (unsigned i = 0; i < monsterTree.size(); i++)
				//{
				//	monsterTree[i]->OnMove();
				//}
				character.OnMove(&bossMap, &monsterS7);
				break;
			default:
				break;
			}
		}
		//
		// 判斷擦子是否碰到球
		//
		//for (i=0; i < NUMBALLS; i++)
		//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
		//		ball[i].SetIsAlive(false);
		//		CAudio::Instance()->Play(AUDIO_DING);
		//		hits_left.Add(-1);
		//		//
		//		// 若剩餘碰撞次數為0，則跳到Game Over狀態
		//		//
		//		if (hits_left.GetInteger() <= 0) {
		//			CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
		//			CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
		//			GotoGameState(GAME_STATE_OVER);
		//		}
		//	}
		//
		// 移動彈跳的球
		//
		//bball.OnMove();

		//monster.SetTopLeft(100, 50);
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		//int i;
		//for (i = 0; i < NUMBALLS; i++)	
		//	ball[i].LoadBitmap();								// 載入第i個球的圖形
		//eraser.LoadBitmap();
		//background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		character.LoadBitmap();
		//monster.LoadBitmap(IDB_MONSTER, RGB(255, 0, 255));
		mapS1.LoadBitmap();
		bossMap.LoadBitmap();
		propsBook.LoadBitmap();
		characterStatus.LoadBitmap();
		gameComplete.LoadBitmap(".\\res\\game_complete.bmp");
		for (unsigned i = 0; i < monsterS1.size(); i++)
		{
			monsterS1[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS7.size(); i++)
		{
			monsterS7[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterCactus.size(); i++)
		{
			monsterCactus[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterShrimp.size(); i++)
		{
			monsterShrimp[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterTree.size(); i++)
		{
			monsterTree[i]->LoadBitmap();
		}

		//help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
		//corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		//corner.ShowBitmap(background);							// 將corner貼到background
		//bball.LoadBitmap();										// 載入圖形
		//hits_left.LoadBitmap();									
		//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
		//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (!gameCompleteFlag) {
			switch (nChar)
			{
			case KEY_A:
				character.SetMovingLeft(true);
				break;
			case KEY_D:
				character.SetMovingRight(true);
				break;
			case KEY_W:
			case KEY_SPACE:
				character.SetMovingUp(true);
				break;
			case KEY_S:
				character.SetMovingDown(true);
				break;
			case KEY_CTRL:
				character.SetRolling(true);
				break;
			case KEY_E:
				if (character.GetCanGoToNextMap())
				{
					currentStage = stage_boss;
					character.SetCanGoToNextMap(false);
				}
				else if (currentStage == stage_props)
				{
					currentStage = lastStage;
					if (!haveCalledCharacterStatus)
					{
						gamePause = false;
					}
					else
					{
						characterStatusCall = true;
					}
				}
				else
				{
					lastStage = currentStage;
					currentStage = stage_props;
					haveCalledCharacterStatus = characterStatusCall;
					characterStatusCall = false;
					gamePause = true;
				}
				break;
			case KEY_TAB:
				if (characterStatusCall == true)
				{
					characterStatusCall = false;
					haveCalledCharacterStatus = false;
					gamePause = false;
				}
				else
				{
					if (currentStage != stage_props)
					{
						characterStatusCall = true;
						gamePause = true;
					}
				}
				break;
			case KEY_R:
				character.SetCurrentHp(50);
				break;
			case KEY_1:
				gamePause = false;
				characterStatusCall = false;
				if (currentStage == stage_1)
				{
					currentStage = lastStage;
				}
				else
				{
					if (currentStage != stage_props)
					{
						lastStage = currentStage;
					}
					currentStage = stage_1;
				}
				break;
			case KEY_7:
				gamePause = false;
				characterStatusCall = false;
				if (currentStage == stage_boss)
				{
					currentStage = lastStage;
				}
				else
				{
					if (currentStage != stage_props)
					{
						lastStage = currentStage;
					}
					currentStage = stage_boss;
				}
				break;
			case KEY_ESC:
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
				break;
			default:
				break;
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_A:
			character.SetMovingLeft(false);
			break;
		case KEY_D:
			character.SetMovingRight(false);
			break;
		case KEY_W:
		case KEY_SPACE:
			character.SetMovingUp(false);
			break;
		case KEY_S:
			character.SetMovingDown(false);
			break;
		default:
			break;
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(true);
		if (currentStage == stage_props)
		{
			if (point.x > 1253 && point.y > 57 && point.x < 1327 && point.y < 117)
			{
				currentStage = lastStage;
				if (!haveCalledCharacterStatus)
				{
					gamePause = false;
				}
				else
				{
					characterStatusCall = true;
				}
			}
			else
			{
				propsBook.setCase(point);
			}
		}
		else if (currentStage == stage_game_complete)
		{
			if (point.x > 80 && point.y > 170 && point.x < 700 && point.y < 610)
			{
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			}
			if (point.x > 840 && point.y > 215 && point.x < 1210 && point.y < 585)
			{
				GotoGameState(GAME_STATE_INIT);
			}
		}
		else
		{
			if (gamePause == false && !character.GetIsAttacking() && !character.GetIsRolling())
			{
				if (currentStage == stage_1)
				{
					character.attack(&monsterS1);
				}
				else if (currentStage == stage_boss)
				{
					character.attack(&monsterS7);
				}
			}
		}
		if (characterStatusCall == true && gameCompleteFlag == false)
		{
			if (point.x > 1030 && point.y > 133 && point.x < 1082 && point.y < 189)
			{
				characterStatusCall = false;
				gamePause = false;
			}
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//character.SetAttacking(false);
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		character.SetFacingDirection(point.x);					// 滑鼠位置改變角色方向
		mousePosition = point;
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		//background.ShowBitmap();			// 貼上背景圖
		//help.ShowBitmap();					// 貼上說明圖
		//hits_left.ShowBitmap();
		//for (int i=0; i < NUMBALLS; i++)
		//	ball[i].OnShow();				// 貼上第i號球
		//bball.OnShow();						// 貼上彈跳的球
		//eraser.OnShow();					// 貼上擦子
		//
		//  貼上左上及右下角落的圖
		//
		//corner.SetTopLeft(0,0);
		//corner.ShowBitmap();
		//corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
		//corner.ShowBitmap();

		//monster.ShowBitmap();
		switch (currentStage)
		{
		case stage_1:
			mapS1.onShow();
			character.OnShow();
			for (unsigned i = 0; i < monsterS1.size(); i++)
			{
				monsterS1[i]->OnShow(&mapS1);
			}
			break;
		case stage_boss:
			bossMap.onShow();
			character.OnShow();
			for (unsigned i = 0; i < monsterS7.size(); i++)
			{
				monsterS7[i]->OnShow(&bossMap);
			}
			//for (unsigned i = 0; i < monsterCactus.size(); i++)
			//{
			//	monsterCactus[i]->OnShow(&bossMap);
			//}
			//for (unsigned i = 0; i < monsterShrimp.size(); i++)
			//{
			//	monsterShrimp[i]->OnShow(&bossMap);
			//}
			//for (unsigned i = 0; i < monsterTree.size(); i++)
			//{
			//	monsterTree[i]->OnShow(&bossMap);
			//}
			ShowData();
			break;
		case stage_props:
			propsBook.onShow();
			break;
		case stage_game_complete:
			gameComplete.ShowBitmap();
			gameCompleteNoteShow();
			break;
		default:
			break;
		}
		if (characterStatusCall)
		{
			characterStatus.onShow();
		}
	}

	void CGameStateRun::ShowData()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(120, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(230, 220, 200));
		pDC->SetTextColor(RGB(0, 0, 0));
		char position[500];								// Demo 數字對字串的轉換
		sprintf(position, "mouseX:%d mouseY:%d", mousePosition.x, mousePosition.y);
		pDC->TextOut(200, 140, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void CGameStateRun::gameCompleteNoteShow()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Please click \"GAME COMPLETE\" to close the game, or \"PLAY AGAIN\" to restart!");
		pDC->TextOut(670, 730, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}