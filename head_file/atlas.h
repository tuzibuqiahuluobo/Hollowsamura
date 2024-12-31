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
		// ����·���ļ�������
		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			// ��ʽ��·���ļ���
			_stprintf_s(path_file, path_template, i + 1);
			// ����ͼ���б���
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
		// ��������Ƿ���Ч
		if (idx < 0 || idx >= img_list.size())
			return nullptr;
		// ���ض�Ӧ������ͼ��ָ��
		return &img_list[idx];
	}

	void add_image(const IMAGE& img)
	{
		// ���ͼ���б���
		img_list.push_back(img);
	}


private:
	std::vector<IMAGE> img_list;
};
