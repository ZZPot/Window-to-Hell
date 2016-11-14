#include "Wind.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <shlobj.h>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Comdlg32.lib")

std::string ChooseFile(HWND hWndOwner, LPCSTR pCaption);

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

std::string ChooseFile(HWND hWndOwner, LPCSTR pCaption)
{
	std::string res = "";
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWndOwner;
	ofn.lpstrFilter = "All files\0*\0";
	ofn.lpstrFile = new TCHAR[MAX_PATH*2]; ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH*2-1;
	ofn.lpstrTitle = pCaption;
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	if(GetOpenFileName(&ofn))
		res = ofn.lpstrFile;
	delete [] ofn.lpstrFile;
	return res;
}