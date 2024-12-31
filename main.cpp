#include <graphics.h>
#include <chrono>
#include <thread>

#include "util.h"
#include "resources_manager.h"

static void draw_background()
{
	static IMAGE* img_background = ResourcesManager::instance()->find_image("background");
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}

int main(int argc, char** argv)
{
	using namespace std::chrono;

	HWND hwnd = initgraph(1280,720,EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollowsamura"));

	try
	{
		ResourcesManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("Failed to load: %s"), id);
		MessageBox(hwnd, err_msg, _T("Failed to load resource"), MB_OK | MB_ICONERROR);
		return -1;
	}

	const nanoseconds frame_duration(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit)
	{
		while (peekmessage(&msg))
		{
			//������Ϣ
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		//�������

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		//������Ⱦ
		draw_background();

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		//���֡���������ĵ�ʱ��С������������֡�ʱ�׼ʱ�䣬����sleep_for��������ʣ���ʱ��
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}

	EndBatchDraw();

	return 0;
}