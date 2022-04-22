#ifndef __COUNT__
#define __COUNT__

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
		clock_t GetTime();
	private:
		clock_t startTime;
		clock_t finishTime;
	};
}

#endif

