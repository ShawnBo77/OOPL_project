
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供計時功能													   //
	/////////////////////////////////////////////////////////////////////////////
	class Counter
	{
	public:
		Counter();
		~Counter();
		void Start();
		void Finish();
		void Reset();
		clock_t GetTime();					//設定滿血的血量
	private:
		clock_t startTime;			//不同長度的血條
		clock_t finishTime;			//不同長度的血條
	};
}

