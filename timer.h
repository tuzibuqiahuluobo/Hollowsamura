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
		// 如果计时器被暂停，则直接返回
		if (paused)	return;
		
		pass_time += delta;

		if (pass_time >= wait_time)
		{
			// 检查是否可以触发超时事件
			bool can_shot = (!one_shot || (one_shot && !shotted));
			// 标记已经触发过
			shotted = true;
			// 如果可以触发并且超时回调函数已设置，则调用回调函数
			if (can_shot && on_timeout)
			{
				on_timeout;
			}
			// 减去等待时间，处理可能的多次触发
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

