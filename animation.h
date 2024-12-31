#pragma once


#include "util.h"
#include "atlas.h"
#include "timer.h"
#include "vector2.h"

#include <functional>
#include <vector>

class Animation
{
public:
	enum class AnchorMode
	{
		Centered, //居中锚点
		BottomCentered //底部居中锚点
	};


	Animation()
	{
		
		timer.set_one_shot(false);
		
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				// 如果当前帧索引超出帧列表大小
				if (idx_frame >= frame_list.size())
				{
					// 如果是循环播放，则重置为第一帧，否则保持在最后一帧
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					// 如果不是循环播放且设置了播放完毕回调函数，则调用回调函数
					if (!is_loop && on_finished)
					{
						on_finished();
					}
				}
			}
		);
	}
	~Animation() = default;

	void reset()
	{
		idx_frame = 0;
		timer.restart();
	}

	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	void set_on_finished(const std::function<void()>& on_finished)
	{
		this->on_finished = on_finished;
	}

	void add_frame(IMAGE* image,int num_h)
	{
		int width = image->getwidth();
		int height = image->getheight();
		int width_frame = width / num_h;\

			for (int i = 0; i < num_h; i++)
			{
				Rect rect_src{};
				rect_src.x = i * width_frame, rect_src.y = 0;
				rect_src.w = width_frame, rect_src.h = height;
				frame_list.emplace_back(image, rect_src);
			}
	}

	void add_frame(Atlas* atlas)
	{
		
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			int width = image->getwidth();
			int height = image->getheight();

			Rect rect_src{};
			rect_src.x =0, rect_src.y = 0;
			rect_src.w = width, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}
	}

	void on_update(float delta)
	{
		timer.on_update(delta);
	}

	void on_render()
	{
		const Frame& frame = frame_list[idx_frame];

		Rect rect_dst{};
		rect_dst.x = (int)position.x - frame.rect_src.w / 2;
		rect_dst.y = (anchor_mode == AnchorMode::Centered)
			? (int)position.y - frame.rect_src.h / 2 : (int)position.y - frame.rect_src.h;
		rect_dst.w = frame.rect_src.w, rect_dst.h = frame.rect_src.h;

		putimage_ex(frame.image, &rect_dst, &frame.rect_src);
	}



private:
	struct Frame
	{
		Rect rect_src;
		IMAGE* image = nullptr;
		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src)
			: image(image), rect_src(rect_src){ }
		~Frame() = default;
	};

private:
	Timer timer; // 计时器，用于控制动画帧的切换时间
	Vector2 position;// 动画在窗口中渲染的位置
	bool is_loop = true;// 是否循环播放动画
	size_t idx_frame = 0;// 当前帧的索引
	std::vector<Frame> frame_list;// 动画帧的列表
	std::function<void()> on_finished;// 动画播放完毕时的回调函数
	AnchorMode anchor_mode = AnchorMode::Centered;// 锚点模式，默认为居中
};
