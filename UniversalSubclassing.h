#pragma once
#include <windows.h>
#include <tchar.h>

typedef bool (*EXT_WNDPROC)(HWND, UINT, WPARAM, LPARAM, LRESULT*);
#define WND_PROC_PROP	_T("wnd_proc pointer")

class wnd_proc
{
public:
	wnd_proc();
	virtual ~wnd_proc(){};
	void Subclass(HWND hWnd, EXT_WNDPROC proc = nullptr);
	EXT_WNDPROC SetProc(EXT_WNDPROC proc);
	WNDPROC SetOld(WNDPROC old_proc);
	LRESULT operator()(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	EXT_WNDPROC _proc;
	WNDPROC _old_proc;
};


LRESULT CALLBACK UniversalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);