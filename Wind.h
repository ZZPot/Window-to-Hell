#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <map>
#include "UniversalSubclassing.h"

#define DEFAULT_WND_WIDTH	300
#define DEFAULT_WND_HEIGHT	300
#define WND_PREFIX			"Hell"

/*
	Window class "Main HighGUI class"
	ChildWindow class "HighGUI class"
*/

#define HELL_WND_CLASS	"Main HighGUI class"
#define CHILD_WND_CLASS	"HighGUI class"
#define WND_WTH_PROP	"window_to_hell pointer"

class window_to_hell
{
public:
	window_to_hell(cv::Mat img, cv::Rect rect = cv::Rect());
	window_to_hell(std::string img_file, cv::Rect rect = cv::Rect());
	void SetImg(cv::Mat img);
	void SetImg(std::string img_file);
	void SetPos(cv::Point pos);
	void SetSize(cv::Size size);
	void SetPosAndSize(cv::Point pos, cv::Size size);
protected:
	void Init(cv::Mat img, cv::Rect rect, std::string name = "");
	void Refresh(bool refreshPos = true, bool refreshSize = true);
protected:
	cv::Point _pos;
	cv::Size _size;
	cv::Mat _img;
	std::string _name;
};

#define NAME_LEN			5

bool RelocHellWnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* res);
cv::Rect GetImgRect(HWND hWnd);
extern wnd_proc hell_proc_for_leather;