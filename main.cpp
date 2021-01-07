#include "Wind.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <shlobj.h>
#include "common.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Comdlg32.lib")

int main()
{
	wnd_proc new_proc; // create before window, please
	cv::Mat img = cv::imread(ChooseFile(NULL, "Choose image"));
	window_to_hell wndth(img);
	window_to_hell wndth1(img);
	window_to_hell wndth2(img);
	window_to_hell wndth3(img);
	//cv::imshow("asd", img);
	cv::waitKey(0);
	return 0;
}