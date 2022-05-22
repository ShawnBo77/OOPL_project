#ifndef __MAPS_H__
#define __MAPS_H__
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖構成
	/////////////////////////////////////////////////////////////////////////////
	class Map
	{
	public:
		Map(int x, int y);
		string getMapName();
		CMovingBitmap exitBitmap;
		CMovingBitmap pressEBitmap;
		int getStartPosition();
		virtual bool isEmpty(int x, int y) const = 0;
		virtual bool isPortal(int x, int y) const = 0;
		virtual bool isBridge(int x, int y) const = 0;
		void setSX(int x);
		void setSY(int y);
		int getSX();
		int getSY();
		bool mapScreenMoving();
		int getFloor();
		int getMonsterFloor();
		int getCeiling();
		int getEndBoundary();
		bool getPortalOpen();
		void setMapName(string name);
		void setStartPosition(int x);									//角色起始位置
		void setMonsterFloor(int y);

		virtual void addSX(int n);
		virtual void addSY(int n);
		virtual int screenX(int x) { return 0; };
		virtual int screenY(int y) { return 0; };
		virtual void setCharacterX(int x) {};
		virtual void setCharacterY(int y) {};
		virtual void monsterFloorChanging(int x) {};
		virtual void characterFloorChanging() {};
		void setFloor(int y);
		void setCeiling(int y);
		void setEndBoundary(int sx);
		void setScreenMoving(bool flag);
		void setPortalOpen(bool flag);
		

		virtual void setPos(int x, int y, int n) = 0;
		void setXY(int x, int y);
	private:
		int sx, sy; //screen 的座標
		int startX; //開始位置
		string mapName;
		int floor;
		int monsterFloor;
		int ceiling;
		int endBoundary;
		bool all_enemy_clear;
		bool screenMoving;
		bool portalOpen;
	};
}
#endif