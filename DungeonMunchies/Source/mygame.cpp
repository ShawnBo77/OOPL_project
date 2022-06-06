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
		instructionsPage01.LoadBitmap(".\\res\\instructions01.bmp");
		instructionsPage02.LoadBitmap(".\\res\\instructions02.bmp");
		instructionsPageC.LoadBitmap(".\\res\\instructions_c01.bmp");
		whiteX.LoadBitmap(".\\res\\white_x.bmp", RGB(0, 0, 0));
		arrowL.LoadBitmap(".\\res\\arrow_left.bmp", RGB(0, 0, 0));
		arrowR.LoadBitmap(".\\res\\arrow_right.bmp", RGB(0, 0, 0));
		CAudio::Instance()->Load(AUDIO_STARTMENU, "sounds\\start_menu_audio.mp3");
		CAudio::Instance()->Load(AUDIO_CHOOSE, "sounds\\choose.mp3");
		CAudio::Instance()->Play(AUDIO_STARTMENU, true);
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
		lastChoice = 0;
		stage = stage_start_menu;
		instructionsPage = instructions_page01;
		record = 1;
		isArrowLShow = isArrowRShow = false;
		isMouseOnX = false;
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_SPACE)
		{
			CAudio::Instance()->Stop(AUDIO_STARTMENU);
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		}
		else if (nChar == KEY_ESC) // 關閉遊戲
		{  
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (stage == stage_start_menu)
		{
			if (choice == 1)
			{
				GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
				CAudio::Instance()->Stop(AUDIO_STARTMENU);
			}
			else if (choice == 2)
			{
				GotoGameState(GAME_STATE_OVER);
			}
			else if (choice == 3)
			{
				stage = stage_staff;
			}
			else if (choice == 4)
			{
				stage = stage_instructions;
			}
			if (point.x >= 0 && point.x <= 31 && point.y >= 735 && point.y <= 768)
			{
				ShellExecute(0, NULL, _T("https://www.facebook.com/dungeonmunchies/"), NULL, NULL, SW_NORMAL);
			}
			if (point.x > 31 && point.x <= 73 && point.y >= 735 && point.y <= 768)
			{
				ShellExecute(0, NULL, _T("https://twitter.com/dungeonmunchies"), NULL, NULL, SW_NORMAL);
			}
			if (point.x > 73 && point.x <= 98 && point.y >= 735 && point.y <= 768)
			{
				ShellExecute(0, NULL, _T("https://discord.com/invite/8NyCnxN"), NULL, NULL, SW_NORMAL);
			}
		}
		else if (stage == stage_staff)
		{
			if (point.x >= 1306 && point.y <= 60)
			{
				stage = stage_start_menu;
			}
		}
		else if (stage == stage_instructions)
		{
			if (instructionsPage == instructions_page01 && point.x >= 1278 && point.x <= 1336 && point.y >= 350 && point.y <= 418)
			{
				instructionsPage = instructions_page02;
				record = 2;
			}
			else if (instructionsPage == instructions_page02 && point.x >= 30 && point.x <= 88 && point.y >= 350 && point.y <= 418)
			{
				instructionsPage = instructions_page01;
				record = 1;
			}
			if (!(instructionsPage == instructions_page_cheat) && point.x >= 380 && point.x <= 980 && point.y >= 50 && point.y <= 120)
			{
				instructionsPage = instructions_page_cheat;
			}
			else if (instructionsPage == instructions_page_cheat && point.x >= 555 && point.x <= 815 && point.y >= 50 && point.y <= 120)
			{
				if (record == 1)
				{
					instructionsPage = instructions_page01;
				}
				else
				{
					instructionsPage = instructions_page02;
				}
			}
			if (point.x >= 1306 && point.y <= 60)
			{
				stage = stage_start_menu;
				instructionsPage = instructions_page01;
				record = 1;
			}
		}
	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (stage == stage_start_menu)
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
				else if (point.y > 635 && point.y < 701)
				{
					yChoice = 635;
					choice = 4;
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
		else if (stage == stage_staff)
		{
			if (point.x >= 1306 && point.y <= 60)
			{
				if (!isMouseOnX)
				{
					CAudio::Instance()->Play(AUDIO_CHOOSE, false);
				}
				isMouseOnX = true;
			}
			else
			{
				isMouseOnX = false;
			}
		}
		else if (stage == stage_instructions)
		{
			if (instructionsPage == instructions_page01 && point.x >= 1278 && point.x <= 1336 && point.y >= 350 && point.y <= 418)
			{
				if (!isArrowRShow)
				{
					CAudio::Instance()->Play(AUDIO_CHOOSE, false);
				}
				isArrowRShow = true;
			}
			else if (instructionsPage == instructions_page02 && point.x >= 30 && point.x <= 88 && point.y >= 350 && point.y <= 418)
			{
				if (!isArrowLShow)
				{
					CAudio::Instance()->Play(AUDIO_CHOOSE, false);
				}
				isArrowLShow = true;
			}
			else
			{
				isArrowLShow = false;
				isArrowRShow = false;
			}
			if (point.x >= 1306 && point.y <= 60)
			{
				if (!isMouseOnX)
				{
					CAudio::Instance()->Play(AUDIO_CHOOSE, false);
				}
				isMouseOnX = true;
			}
			else
			{
				isMouseOnX = false;
			}
		}
	}

	void CGameStateInit::isChoiceChange()
	{
		if (lastChoice != choice && choice != 0)
		{
			CAudio::Instance()->Play(AUDIO_CHOOSE, false);
			lastChoice = choice;
		}
	}

	void CGameStateInit::OnMove()
	{
		isChoiceChange();
	}

	void CGameStateInit::OnShow()
	{
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
		if (stage == stage_start_menu)
		{
			startMenu.SetTopLeft(0, 0);
			startMenu.ShowBitmap();
			if (onChoice)
			{
				startMenuChoice.SetTopLeft(603, yChoice);
				startMenuChoice.ShowBitmap();
			}
		}
		else if (stage == stage_staff)
		{
			staff.SetTopLeft(0, 0);
			staff.ShowBitmap();
			if (isMouseOnX)
			{
				whiteX.SetTopLeft(1306, 0);
				whiteX.ShowBitmap();
			}
		}
		else if (stage == stage_instructions)
		{
			instructionsPageShow();
			if (isArrowLShow)
			{
				arrowL.SetTopLeft(30, 350);
				arrowL.ShowBitmap();
			}
			if (isArrowRShow)
			{
				arrowR.SetTopLeft(1278, 350);
				arrowR.ShowBitmap();
			}
			if (isMouseOnX)
			{
				whiteX.SetTopLeft(1306, 0);
				whiteX.ShowBitmap();
			}
		}
	}

	void CGameStateInit::instructionsPageShow()
	{
		if (instructionsPage == instructions_page01)
		{
			instructionsPage01.SetTopLeft(0, 0);
			instructionsPage01.ShowBitmap();
		}
		else if (instructionsPage == instructions_page02)
		{
			instructionsPage02.SetTopLeft(0, 0);
			instructionsPage02.ShowBitmap();
		}
		else if (instructionsPage == instructions_page_cheat)
		{
			instructionsPageC.SetTopLeft(0, 0);
			instructionsPageC.ShowBitmap();
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
		//monsterS1.push_back(new MonsterShrimp(700, 500, &character));
		//monsterS1.push_back(new MonsterTree(1900, 400, &character));
		monsterS1.push_back(new MonsterCactus(1500, 500, &character));
		monsterS1.push_back(new MonsterBanana(800, 400, &character));

		monsterS2.push_back(new MonsterBanana(2650, 400, &character));

		monsterS3.push_back(new MonsterBanana(300, 400, &character));
		monsterS3.push_back(new MonsterShrimp(1000, 400, &character));
		monsterS3.push_back(new MonsterCactus(800, 400, &character));
		monsterS3.push_back(new MonsterTree(2000, 400, &character));

		//monsterS7.push_back(new MonsterTree(700, 400, &character));
		//monsterS7.push_back(new MonsterShrimp(600, 400, &character));
		//monsterS7.push_back(new MonsterShrimp(850, 400, &character));
		//monsterS7.push_back(new MonsterCactus(700, 500, &character));
		//monsterS7.push_back(new MonsterTree(400, 400, &character));
		//monsterS7.push_back(new MonsterBanana(1000, 400, &character));
		monsterS7.push_back(new MonsterBoss(900, 280, &character));
		//monsterS7.push_back(new MonsterCactus(700, 500, &character));
	}

	CGameStateRun::~CGameStateRun()
	{
		for (vector<Monster*>::iterator it_i = monsterS1.begin(); it_i != monsterS1.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS2.begin(); it_i != monsterS2.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS3.begin(); it_i != monsterS3.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS4.begin(); it_i != monsterS4.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS5.begin(); it_i != monsterS5.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS6.begin(); it_i != monsterS6.end(); ++it_i)
		{
			delete* it_i;
		}
		for (vector<Monster*>::iterator it_i = monsterS7.begin(); it_i != monsterS7.end(); ++it_i)
		{
			delete* it_i;
		}
	}

	void CGameStateRun::OnBeginState()
	{
		character.Initialize();
		mapS1.Initialize();
		mapS2.Initialize();
		mapS3.Initialize();
		//mapS4.Initialize();
		//mapS5.Initialize();
		//mapS6.Initialize();
		bossMap.Initialize();
		propsBook.Initialize(&character);
		characterStatus.Initialize(&character);
		characterStatusCall = false;
		haveCalledCharacterStatus = false;
		gamePause = false;
		gameCompleteFlag = false;
		messageShowFlag = false;

		currentStage = stage_1;
		lastStage = currentStage;
		monsterInitialize();

		isStageChanged = true;
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

		if (character.GetCurrentHp() <= 0)
		{
			GotoGameState(GAME_STATE_OVER);
		}
		for (int i = 0; i < (signed)monsterS7.size(); i++)
		{
			if (monsterS7[i]->GetBossDead())
			{
				gameCompleteFlag = true;
				currentStage = stage_game_complete;
			}
		}
		if (currentStage != stage_game_complete && gamePause == false)
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
			case stage_2:
				for (unsigned i = 0; i < monsterS2.size(); i++)
				{
					monsterS2[i]->OnMove(&mapS2);
				}
				character.OnMove(&mapS2, &monsterS2);
				break;
			case stage_3:
				for (unsigned i = 0; i < monsterS3.size(); i++)
				{
					monsterS3[i]->OnMove(&mapS3);
				}
				character.OnMove(&mapS3, &monsterS3);
				break;
				//case stage_4:
				//	for (unsigned i = 0; i < monsterS4.size(); i++)
				//	{
				//		monsterS4[i]->OnMove(&mapS4);
				//	}
				//	character.OnMove(&mapS2, &monsterS4);
				//	break;
				//case stage_5:
				//	for (unsigned i = 0; i < monsterS5.size(); i++)
				//	{
				//		monsterS5[i]->OnMove(&mapS5);
				//	}
				//	character.OnMove(&mapS5, &monsterS5);
				//	break;
				//case stage_6:
				//	for (unsigned i = 0; i < monsterS6.size(); i++)
				//	{
				//		monsterS6[i]->OnMove(&mapS6);
				//	}
				//	character.OnMove(&mapS6, &monsterS6);
				//	break;
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
		if (isStageChanged)
		{
			bgmPlayer();
			isStageChanged = false;
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
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
		mapS2.LoadBitmap();
		mapS3.LoadBitmap();
		//mapS4.LoadBitmap();
		//mapS5.LoadBitmap();
		//mapS6.LoadBitmap();
		bossMap.LoadBitmap();
		propsBook.LoadBitmap();
		characterStatus.LoadBitmap();
		lightBulb.LoadBitmap(".\\res\\light_bulb.bmp", RGB(0, 0, 0));
		gameComplete.LoadBitmap(".\\res\\game_complete.bmp");
		for (unsigned i = 0; i < monsterS1.size(); i++)
		{
			monsterS1[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS2.size(); i++)
		{
			monsterS2[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS3.size(); i++)
		{
			monsterS3[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS4.size(); i++)
		{
			monsterS4[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS5.size(); i++)
		{
			monsterS5[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS6.size(); i++)
		{
			monsterS6[i]->LoadBitmap();
		}
		for (unsigned i = 0; i < monsterS7.size(); i++)
		{
			monsterS7[i]->LoadBitmap();
		}

		CAudio::Instance()->Load(AUDIO_COOK, "sounds\\cook.mp3");
		CAudio::Instance()->Load(AUDIO_ATTACK_HU, "sounds\\attack_hu.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_01, "sounds\\music01.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_02, "sounds\\music02.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_03, "sounds\\music03.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_04, "sounds\\music04.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_05, "sounds\\music05.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_06, "sounds\\music06.mp3");
		CAudio::Instance()->Load(AUDIO_MUSIC_07, "sounds\\music07.mp3");
		CAudio::Instance()->Load(AUDIO_RECYCLE_CAN, "sounds\\recycle_can.mp3");
		CAudio::Instance()->Load(AUDIO_POT, "sounds\\pot.mp3");

		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (!gameCompleteFlag)
		{
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
				character.SetMovingDown();
				break;
			case KEY_CTRL:
				character.SetRolling(true);
				break;
			case KEY_E:
				if (character.GetCanGoToNextMap())
				{
					monsterInitialize();
					switch (currentStage)
					{
					case stage_1:
						mapS2.Initialize();
						character.SetXY(mapS2.getStartPosition(), 100);
						currentStage = stage_2;
						isStageChanged = true;
						character.SetCanGoToNextMap(false);
						break;
					case stage_2:
						mapS3.Initialize();
						character.SetXY(mapS3.getStartPosition(), 100);
						currentStage = stage_3;
						isStageChanged = true;
						character.SetCanGoToNextMap(false);
						break;
					case stage_3:
						bossMap.Initialize();
						character.SetXY(bossMap.getStartPosition(), 100);
						currentStage = stage_boss;
						isStageChanged = true;
						character.SetCanGoToNextMap(false);
						break;
					default:
						break;
					}
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
				else if (character.GetCanCraft())
				{
					lastStage = currentStage;
					currentStage = stage_props;
					haveCalledCharacterStatus = characterStatusCall;
					characterStatusCall = false;
					gamePause = true;
				}
				else if (GetCurrentMap()->getCanShowMessage() && !messageShowFlag)
				{
					gamePause = true;
					messageShowFlag = true;
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
						haveCalledCharacterStatus = true;
						gamePause = true;
					}
				}
				break;
			case KEY_R:
				character.restoreCurrentHp(50);
				break;
			case KEY_T:
				character.addAttackDamage(10);
				break;
			case KEY_Y:
				character.SetLightBulbNum(1000);
				break;
			case KEY_U:
				character.SetAllSourceNumToHundred();
				break;
			case KEY_H:
				currentStage = stage_boss;
				isStageChanged = true;
				for (int i = 0; i < (signed)monsterS7.size(); i++)
				{
					monsterS7[i]->SetCurrentHp(0);
				}
				break;
			case KEY_G:
				character.SetCurrentHp(0);
				break;
			case KEY_1:
				monsterInitialize();
				gamePause = false;
				characterStatusCall = false;
				mapS1.Initialize();
				character.SetXY(mapS1.getStartPosition(), 100);
				currentStage = stage_1;
				isStageChanged = true;
				break;
			case KEY_2:
				monsterInitialize();
				gamePause = false;
				characterStatusCall = false;
				mapS2.Initialize();
				character.SetXY(mapS2.getStartPosition(), 100);
				currentStage = stage_2;
				isStageChanged = true;
				break;
			case KEY_3:
				monsterInitialize();
				gamePause = false;
				characterStatusCall = false;
				mapS3.Initialize();
				character.SetXY(mapS3.getStartPosition(), 100);
				currentStage = stage_3;
				isStageChanged = true;
				break;
				//case KEY_4:
				//	monsterInitialize();
				//	gamePause = false;
				//	characterStatusCall = false;
				//	mapS2.Initialize();
				//	currentStage = stage_2;
				//	isStageChanged = true;
				//	break;
				//case KEY_5:
				//	monsterInitialize();
				//	gamePause = false;
				//	characterStatusCall = false;
				//	mapS2.Initialize();
				//	currentStage = stage_2;
				//	isStageChanged = true;
				//	break;
				//case KEY_6:
				//	monsterInitialize();
				//	gamePause = false;
				//	characterStatusCall = false;
				//	mapS2.Initialize();
				//	currentStage = stage_2;
				//	isStageChanged = true;
				//	break;
			case KEY_7:
				monsterInitialize();
				gamePause = false;
				characterStatusCall = false;
				bossMap.Initialize();
				character.SetXY(bossMap.getStartPosition(), 100);
				currentStage = stage_boss;
				isStageChanged = true;
				/*if (currentStage == stage_boss)
				{
					currentStage = lastStage;
				}
				else
				{
					if (currentStage != stage_props)
					{
						lastStage = currentStage;
					}
					bossMap.Initialize();
					currentStage = stage_boss;
				}*/
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
				else if (currentStage == stage_2)
				{
					character.attack(&monsterS2);
				}
				else if (currentStage == stage_3)
				{
					character.attack(&monsterS3);
				}
				else if (currentStage == stage_4)
				{
					character.attack(&monsterS4);
				}
				else if (currentStage == stage_5)
				{
					character.attack(&monsterS5);
				}
				else if (currentStage == stage_6)
				{
					character.attack(&monsterS6);
				}
				else if (currentStage == stage_boss)
				{
					character.attack(&monsterS7);
				}
			}
		}
		if (messageShowFlag && !GetCurrentMap()->getMessageEndFlag())
		{
			GetCurrentMap()->setMessageCounterToNext();
		}
		else if (messageShowFlag && GetCurrentMap()->getMessageEndFlag())
		{
			messageShowFlag = false;
			gamePause = false;
			GetCurrentMap()->InitializeMessage();
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
		if (!gamePause)
		{
			character.SetFacingDirection(point.x);					// 滑鼠位置改變角色方向
			mousePosition = point;
		}
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
		switch (currentStage)
		{
		case stage_1:
			mapS1.onShow();
			character.OnShow();
			for (unsigned i = 0; i < monsterS1.size(); i++)
			{
				monsterS1[i]->OnShow(&mapS1);
			}
			LightBulbOnShow();
			if (messageShowFlag)
			{
				mapS1.messageOnShow();
			}
			break;
		case stage_2:
			mapS2.onShow();
			character.OnShow();
			for (unsigned i = 0; i < monsterS2.size(); i++)
			{
				monsterS2[i]->OnShow(&mapS2);
			}
			LightBulbOnShow();
			break;
		case stage_3:
			mapS3.onShow();
			character.OnShow();
			for (unsigned i = 0; i < monsterS3.size(); i++)
			{
				monsterS3[i]->OnShow(&mapS3);
			}
			LightBulbOnShow();
			break;
			//case stage_4:
			//	mapS4.onShow();
			//	character.OnShow();
			//	for (unsigned i = 0; i < monsterS4.size(); i++)
			//	{
			//		monsterS4[i]->OnShow(&mapS4);
			//	}
			//	LightBulbOnShow();
			//	break;
			//case stage_5:
			//	mapS5.onShow();
			//	character.OnShow();
			//	for (unsigned i = 0; i < monsterS5.size(); i++)
			//	{
			//		monsterS5[i]->OnShow(&mapS5);
			//	}
			//	LightBulbOnShow();
			//	break;
			//case stage_6:
			//	mapS6.onShow();
			//	character.OnShow();
			//	for (unsigned i = 0; i < monsterS6.size(); i++)
			//	{
			//		monsterS6[i]->OnShow(&mapS6);
			//	}
			//	LightBulbOnShow();
			//	break;
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
			LightBulbOnShow();
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
		ShowData();
	}

	void CGameStateRun::LightBulbOnShow()
	{
		lightBulb.SetTopLeft(18, 80);
		lightBulb.ShowBitmap();
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(200, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		char position[100];								// Demo 數字對字串的轉換
		sprintf(position, "x %d", character.GetLightBulbNum());
		pDC->TextOut(57, 87, position);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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
		pDC->TextOut(665, 730, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void CGameStateRun::bgmPlayer()
	{
		if (currentStage == stage_1)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_01, true);
		}
		else if (currentStage == stage_2)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_02, true);
		}
		else if (currentStage == stage_3)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_03, true);
		}
		else if (currentStage == stage_4)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_04, true);
		}
		else if (currentStage == stage_5)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_05, true);
		}
		else if (currentStage == stage_6)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_06, true);
		}
		else if (currentStage == stage_boss)
		{
			stopAllBgm();
			CAudio::Instance()->Play(AUDIO_MUSIC_07, true);
		}
	}

	void CGameStateRun::stopAllBgm()
	{
		CAudio::Instance()->Stop(AUDIO_MUSIC_01);
		CAudio::Instance()->Stop(AUDIO_MUSIC_02);
		CAudio::Instance()->Stop(AUDIO_MUSIC_03);
		CAudio::Instance()->Stop(AUDIO_MUSIC_04);
		CAudio::Instance()->Stop(AUDIO_MUSIC_05);
		CAudio::Instance()->Stop(AUDIO_MUSIC_06);
		CAudio::Instance()->Stop(AUDIO_MUSIC_07);
	}

	Map* CGameStateRun::GetCurrentMap()
	{
		if (currentStage == stage_1)
		{
			return &mapS1;
		}
		else if (currentStage == stage_2)
		{
			return &mapS2;
		}
		else if (currentStage == stage_3)
		{
			return &mapS3;
		}
		else if (currentStage == stage_boss)
		{
			return &bossMap;
		}
		else
		{
			throw("GetCurrentMap() didn't have return");
		}
	}

	void CGameStateRun::monsterInitialize()
	{
		for (unsigned i = 0; i < monsterS1.size(); i++)
		{
			monsterS1[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS2.size(); i++)
		{
			monsterS2[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS3.size(); i++)
		{
			monsterS3[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS4.size(); i++)
		{
			monsterS4[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS5.size(); i++)
		{
			monsterS5[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS6.size(); i++)
		{
			monsterS6[i]->Initialize();
		}
		for (unsigned i = 0; i < monsterS7.size(); i++)
		{
			monsterS7[i]->Initialize();
		}
	}
}