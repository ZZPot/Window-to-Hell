#define _CRT_RAND_S
#include <stdlib.h>
#include "Wind.h"
#include <iostream>
#pragma warning (disable: 4996)

window_to_hell::window_to_hell(cv::Mat img, cv::Rect rect)
{
	Init(img, rect);
}
window_to_hell::window_to_hell(std::string img_file, cv::Rect rect)
{
	Init(cv::imread(img_file), rect, img_file);
}
void window_to_hell::Init(cv::Mat img, cv::Rect rect, std::string name)
{
	if(!name.length())
		_name = CreateRandomName(NAME_LEN, WND_PREFIX "_");
	else
		_name = CreateRandomName(NAME_LEN, WND_PREFIX "_", name);
	_img = img; 
	_size.width = rect.width;
	_size.height = rect.height;
	if(!_size.width)
		_size.width = DEFAULT_WND_WIDTH;
	if(!_size.height)
		_size.height = DEFAULT_WND_HEIGHT;
	cv::namedWindow(_name, cv::WINDOW_FREERATIO);
	HWND hWnd = FindWindow(HELL_WND_CLASS, _name.c_str());
	if(hWnd == INVALID_HANDLE_VALUE)
		return;
	SetProp(hWnd, WND_WTH_PROP, (HANDLE)this);
	cv::Rect client_rect = GetImgRect(hWnd);
	_pos.x = client_rect.x;
	_pos.y = client_rect.y;
	// all windows has same window procedure, so _old_proc will be same
	hell_proc_for_leather.Subclass(hWnd, RelocHellWnd); 
	Refresh();
}
void window_to_hell::SetImg(cv::Mat img)
{
	_img = img;
	Refresh();
}
void window_to_hell::SetImg(std::string img_file)
{
	_img = cv::imread(img_file);
	Refresh();
}
void window_to_hell::SetPos(cv::Point pos)
{
	_pos = pos;
	Refresh();
}
void window_to_hell::SetSize(cv::Size size)
{
	_size = size;
}
void window_to_hell::Refresh()
{
	cv::Rect temp(_pos, _size);
	if(temp.width > _img.cols)
		temp.width = _img.cols;
	if(temp.height > _img.rows)
		temp.height = _img.rows;
	if(temp.width + temp.x >= _img.cols)
		temp.width = _img.cols - temp.x - 1;
	if(temp.height + temp.y >= _img.rows)
		temp.height = _img.rows - temp.y - 1;
	if(temp.x < 0)
	{
		temp.width = -temp.x;
		temp.x = 0;
	}
	if(temp.y < 0)
	{
		temp.height = -temp.y;
		temp.y = 0;
	}
	if(temp.width <= 0)
	{
		temp.width = 1;
		temp.x = _img.cols - 1;
	}
	if(temp.height <= 0)
	{
		temp.height = 1;
		temp.y = _img.rows - 1;
	}
	cv::imshow(_name, _img(temp));
	cv::resizeWindow(_name, temp.width, temp.height);
}
std::string CreateRandomName(unsigned num_chars, std::string prefix, std::string postfix)
{
	std::string new_name = prefix;
	if(num_chars > RANDOM_NAME_MAX_CHARS)
		num_chars = RANDOM_NAME_MAX_CHARS;
	unsigned u_rand;
	char rand_chunk[RANDOM_CHUNK_SIZE + 1];
	for(; num_chars; num_chars -= cv::min<unsigned>(num_chars, RANDOM_CHUNK_SIZE))
	{
		rand_s(&u_rand);
		itoa(u_rand % (unsigned)pow(10, cv::min<unsigned>(num_chars, RANDOM_CHUNK_SIZE)), rand_chunk, 10);
		new_name += rand_chunk;
	}
	new_name += postfix;
	return new_name;
}
bool RelocHellWnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* res)
{
	switch(uMsg)
	{
	case WM_MOVE:
	{
		cv::Rect rect = GetImgRect(hWnd);
		window_to_hell* wth = (window_to_hell*)GetProp(hWnd, WND_WTH_PROP);
		wth->SetPos(rect.tl());
	}
		break;
	case WM_SIZE:
	{
		cv::Rect rect = GetImgRect(hWnd);
		window_to_hell* wth = (window_to_hell*)GetProp(hWnd, WND_WTH_PROP);
		wth->SetSize(rect.size());
	}
		break;
	}
	return false;
}
cv::Rect GetImgRect(HWND hWnd)
{
	HWND childWnd = FindWindowEx(hWnd, NULL, CHILD_WND_CLASS, NULL);
	RECT clientRect;
	GetClientRect(childWnd, &clientRect);
	POINT tl{0, 0};
	ClientToScreen(childWnd, &tl);
	return cv::Rect(tl.x, tl.y, clientRect.right, clientRect.bottom);
}
wnd_proc hell_proc_for_leather;