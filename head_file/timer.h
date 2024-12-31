#pragma once

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(float val)
	{
		wait_time = val;
	}

	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void set_on_timeout(std::function<void()> on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}


	void on_update(float delta)
	{
		// �����ʱ������ͣ����ֱ�ӷ���
		if (paused)	return;
		
		pass_time += delta;

		if (pass_time >= wait_time)
		{
			// ����Ƿ���Դ�����ʱ�¼�
			bool can_shot = (!one_shot || (one_shot && !shotted));
			// ����Ѿ�������
			shotted = true;
			// ������Դ������ҳ�ʱ�ص����������ã�����ûص�����
			if (can_shot && on_timeout)
			{
				on_timeout;
			}
			// ��ȥ�ȴ�ʱ�䣬������ܵĶ�δ���
			pass_time -= wait_time;
		}
	}


private:
	float pass_time = 0;
	float wait_time = 0;
	bool one_shot = false;
	bool paused = false;
	bool shotted = false;
	std::function<void()> on_timeout;
};

