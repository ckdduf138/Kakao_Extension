#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>

bool FindKakaoTalk(HWND kako_hWnd);
void SendChat(HWND kako_hWnd, char* msg);

HWND hEdit, hList, hScrl;

// 카카오톡 최대 입력글자 > 1000글자
char msg[1000];

int main()
{
	HWND kako_hWnd = FindWindow(TEXT("#32770"), 0);

	while (1) 
	{
		std::cin.getline(msg, 1000);

		if (FindKakaoTalk(kako_hWnd))
		{
			SendChat(hEdit, msg);
		}
		else
		{
			kako_hWnd = FindWindow(TEXT("#32770"), 0);
		}
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

void SendChat(HWND hEdit, char* msg)
{

	SendMessageA(hEdit, WM_SETTEXT, NULL, (LPARAM)msg);

	//int cnt = 3;
	//while (cnt > 0)
	//{
	//	PostMessage(hEdit, WM_KEYDOWN, VK_RIGHT, 0);
	//	cnt--;
	//}

	// 전송
	PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	PostMessage(hEdit, WM_KEYUP, VK_RETURN, 0);


	// 전송
	//PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	//PostMessage(hEdit, WM_KEYUP, VK_RETURN, 0);
}
