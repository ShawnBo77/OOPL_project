#ifndef __MAPS_H__
#define __MAPS_H__
#include "Util.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖構成
	/////////////////////////////////////////////////////////////////////////////
	class Map
	{
	public:
		Map(int x, int y);
		string getMapName();
		
		int getStartPosition();
		virtual bool isEmpty(int x, int y) const = 0;
		virtual bool isPortal(int x, int y) const = 0;
		virtual bool isBridge(int x, int y) const = 0;
		virtual bool isCraftTable(int x, int y) const = 0;
		virtual bool isTrashCan(int x, int y) const = 0;
		virtual bool isGetHurtPlace(int x, int y) const = 0;
		void setSX(int x);
		void setSY(int y);
		int getSX();
		int getSY();
		bool mapScreenMoving();
		int getFloor();
		int getMonsterFloor();
		int getCeiling();
		int getEndBoundary();
		void setMapName(string name);
		void setStartPosition(int x);									//角色起始位置
		void setMonsterFloor(int y);

		virtual void addSX(int n);
		virtual void addSY(int n);
		virtual int screenX(int x) { return 0; };
		virtual int screenY(int y) { return 0; };
		void setCharacterX(int x);
		void setCharacterY(int y);
		virtual void monsterFloorChanging(int x) {};
		virtual void characterFloorAndCeiling() {};
		void setFloor(int y);
		void setCeiling(int y);
		void setEndBoundary(int sx);
		void setScreenMoving(bool flag);


		bool getCraftTableOpen();
		void setCraftTableOpen(bool flag);
		bool getPortalOpen();
		void setPortalOpen(bool flag);
		bool getTrashCanOpen();
		void setTrashCanOpen(bool flag);
		

		virtual void setPos(int x, int y, int n) = 0;
		void setXY(int x, int y);
		void setInitialX(int x);
		int getInitialX();
		void setInitialY(int y);
		int getInitialY();
		void setInitialXY(int x, int y);
		int getXMovement();
		int getYMovement();

		/*訊息相關函式*/
		//放大鏡
		void loadMagnifierBitmap();
		void showMaginifier(int x, int y);
		void setShowMaginifierFlag(bool flag);
		bool getShowMaginifierFlag();
		//訊息圖示
		void loadMessageIconBitmap();
		void showMessageIcon(int x, int y);
		void setShowMessageIconFlag(bool flag);
		bool getShowMessageIconFlag();
		//訊息
		void setCanShowMessage(bool flag, int code);
		bool getCanShowMessage();
		//void setIsMessageShowing(bool flag);
		//bool getIsMessageShowing();
		void setMessageCounter(int n);
		int getMessageCounter();
		void setMessageCounterToNext();
		void setMessageEndFlag(bool flag);
		bool getMessageEndFlag();
		void InitializeMessage();
		virtual void messageOnShow();
	protected:
		CMovingBitmap exitBitmap;
		CMovingBitmap pressEBitmap;
		CMovingBitmap trashCanOpenBitmap, trashCanClosedBitmap;
		CMovingBitmap craftingBitmap;
		int sx, sy; //screen 的座標
		int characterX, characterY;
		int initialX, initialY; //初始X、Y
		int startX; //開始位置
		int cyRelativeMovement;
		string mapName;
		int floor;
		int monsterFloor;
		int ceiling;
		int endBoundary;
		bool screenMoving;
		bool portalOpen;
		bool craftTableOpen;
		bool trashCanOpen;

		CMovingBitmap magnifier;
		bool showMaginifierFlag;
		CMovingBitmap messageIcon;
		bool showMessageIconFlag;

		int messageCode;
		bool canShowMessage;
		//bool isMessageShowing;
		int messageCounter;
		int messageSize;
		bool messageEndFlag;
	};
}
#endif