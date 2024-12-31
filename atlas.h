#pragma once


#include <vector>
#include <graphics.h>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;


	void load(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);
		// 定义路径文件缓冲区
		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			// 格式化路径文件名
			_stprintf_s(path_file, path_template, i + 1);
			// 加载图像到列表中
			loadimage(&img_list[i], path_file);
		}
	}

	void clear() 
	{
		img_list.clear();
	}

	int get_size() const
	{
		return (int)img_list.size();
	}

	IMAGE* get_image(int idx)
	{
		// 检查索引是否有效
		if (idx < 0 || idx >= img_list.size())
			return nullptr;
		// 返回对应索引的图像指针
		return &img_list[idx];
	}

	void add_image(const IMAGE& img)
	{
		// 添加图像到列表中
		img_list.push_back(img);
	}


private:
	std::vector<IMAGE> img_list;
};
