#include"Script.h"

using namespace std;

HHOOK kbdHOOK;

bool isDown = false;

Script script;

LRESULT __stdcall KeyboradProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code >= HC_ACTION)
	{
		if (wParam == WM_KEYDOWN && !isDown)
		{
			isDown = true;

			KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;

			if (kbdStruct->vkCode == VK_F2)
			{
				UnhookWindowsHookEx(kbdHOOK);
			}

			if (kbdStruct->vkCode == 'B')
			{
				POINT cursor;
				GetCursorPos(&cursor);
				std::cout << cursor.x << " " << cursor.y << "\n";
			}


			if (kbdStruct->vkCode == 'F')
			{
				script.start();
			}
		}
		else if (wParam == WM_KEYUP)
		{
			isDown = false;
		}
	}

	return CallNextHookEx(kbdHOOK, code, wParam, lParam);
}

int main()
{
	Color::hdc = GetDC(nullptr);
	kbdHOOK = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&KeyboradProc, GetModuleHandle(NULL), NULL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}