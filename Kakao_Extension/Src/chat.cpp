#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>

bool FindKakaoTalk(HWND kako_hWnd);
void SendChat(HWND kako_hWnd, char* msg, int cnt);
void GetPersonList();

HWND kakao_hWnd, hEdit, hList, hScrl;

// 카카오톡 최대 입력글자 > 1000글자
char msg[1000];

int main()
{
	kakao_hWnd = FindWindow(TEXT("#32770"), 0);

	while (1)
	{
		std::cin.getline(msg, 1000);

		if (FindKakaoTalk(kakao_hWnd))
		{
			SetForegroundWindow(kakao_hWnd);

			SetForegroundWindow(hEdit);

			int number = 6;
			for (int idx = 1; idx <= number; idx++)
			{
				SendChat(hEdit, msg, idx);
			}

			Sleep(1000);

			// 엔터 키 누르기
			INPUT inputs[2];
			memset(inputs, 0, sizeof(inputs));

			inputs[0].type = INPUT_KEYBOARD;
			inputs[0].ki.wVk = VK_RETURN; // 엔터 키 코드
			inputs[0].ki.dwFlags = 0;

			inputs[1].type = INPUT_KEYBOARD;
			inputs[1].ki.wVk = VK_RETURN; // 엔터 키 코드
			inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(2, inputs, sizeof(INPUT));
		}
		else
		{
			kakao_hWnd = FindWindow(TEXT("#32770"), 0);
		}

		//break;
	}

	return 0;
}

bool FindKakaoTalk(HWND kako_hWnd)
{
	// 카카오톡 채팅창
	hEdit = FindWindowEx(kako_hWnd, NULL, L"RICHEDIT50W", NULL);

	// 카카오톡 채팅화면
	hList = FindWindowEx(kako_hWnd, NULL, L"EVA_VH_ListControl_Dblclk", NULL);

	// 카카오톡 채팅화면 -> 카카오톡 스크롤
	hScrl = FindWindowEx(hList, NULL, L"_EVA_CustomScrollCtrl", NULL);

	// 위와 같은형태이면 카카오톡으로 간주
	if ((hEdit != NULL) && (hList != NULL) && (hScrl != NULL))
	{
		std::cout << "SendMessage..\n";
		return true;
	}
	else
	{
		std::cout << "Unfined KakaoTalk..\n";
		return false;
	}

}

void GetPersonList()
{
	// 특정 키 조합을 눌러서 채팅방의 참가자 목록 열기
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('M', 0, 0, 0);
	keybd_event('M', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void SendChat(HWND hEdit, char* msg, int cnt)
{
	SetForegroundWindow(kakao_hWnd);

	SetForegroundWindow(hEdit);

	SendMessage(hEdit, EM_SETSEL, -1, -1);
	Sleep(300);

	SendMessageA(hEdit, EM_REPLACESEL, true, (LPARAM)"@");
	Sleep(300);

	PostMessage(hEdit, WM_KEYDOWN, VK_RIGHT, 0);
	Sleep(300);

	for (int idx = 0; idx < cnt; idx++)
	{
		// 아래키 누르기
		INPUT inputs[2];
		memset(inputs, 0, sizeof(inputs));

		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = VK_DOWN; // 아래 키 코드
		inputs[0].ki.dwFlags = 0;

		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = VK_DOWN; // 아래 키 코드
		inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

		SendInput(2, inputs, sizeof(INPUT));
		Sleep(300);
	}

	Sleep(500);

	// 엔터 키 누르기
	INPUT inputs[2];
	memset(inputs, 0, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_RETURN; // 엔터 키 코드
	inputs[0].ki.dwFlags = 0;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_RETURN; // 엔터 키 코드
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));
}
