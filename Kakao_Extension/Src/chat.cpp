#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>

bool FindKakaoTalk(HWND kako_hWnd);
void SendChat(HWND kako_hWnd, char* msg);

HWND hEdit, hList, hScrl;

// īī���� �ִ� �Է±��� > 1000����
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
	// īī���� ä��â
	hEdit = FindWindowEx(kako_hWnd, NULL, L"RICHEDIT50W", NULL);
	
	// īī���� ä��ȭ��
	hList = FindWindowEx(kako_hWnd, NULL, L"EVA_VH_ListControl_Dblclk", NULL);

	// īī���� ä��ȭ�� -> īī���� ��ũ��
	hScrl = FindWindowEx(hList, NULL, L"_EVA_CustomScrollCtrl", NULL);

	// ���� ���������̸� īī�������� ����
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

	// ����
	PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	PostMessage(hEdit, WM_KEYUP, VK_RETURN, 0);


	// ����
	//PostMessage(hEdit, WM_KEYDOWN, VK_RETURN, 0);
	//PostMessage(hEdit, WM_KEYUP, VK_RETURN, 0);
}
