#include "Wind.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>


bool newWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* res);

int main()
{
	wnd_proc new_proc; // create before window, please
	cv::Mat img = cv::imread("1.jpg");
	window_to_hell wndth(img);
	window_to_hell wndth1(img);
	window_to_hell wndth2(img);
	window_to_hell wndth3(img);
	//cv::imshow("asd", img);
	cv::waitKey(0);
	return 0;
}

bool newWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* res)
{
	switch(uMsg)
	{
	case WM_MOVE:
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		clientRect.top = HIWORD(lParam);
		clientRect.left = LOWORD(lParam);
		std::cout<<clientRect.top << " " << clientRect.left << std::endl;
	}
		break;
	}
	return false;
}