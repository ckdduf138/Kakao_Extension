#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>

bool FindKakaoTalk(HWND kako_hWnd);
void SendChat(HWND kako_hWnd, char* msg, int cnt);
void GetPersonList();

HWND kakao_hWnd, hEdit, hList, hScrl;

// īī���� �ִ� �Է±��� > 1000����
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

			// ���� Ű ������
			INPUT inputs[2];
			memset(inputs, 0, sizeof(inputs));

			inputs[0].type = INPUT_KEYBOARD;
			inputs[0].ki.wVk = VK_RETURN; // ���� Ű �ڵ�
			inputs[0].ki.dwFlags = 0;

			inputs[1].type = INPUT_KEYBOARD;
			inputs[1].ki.wVk = VK_RETURN; // ���� Ű �ڵ�
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

void GetPersonList()
{
	// Ư�� Ű ������ ������ ä�ù��� ������ ��� ����
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
		// �Ʒ�Ű ������
		INPUT inputs[2];
		memset(inputs, 0, sizeof(inputs));

		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = VK_DOWN; // �Ʒ� Ű �ڵ�
		inputs[0].ki.dwFlags = 0;

		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = VK_DOWN; // �Ʒ� Ű �ڵ�
		inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

		SendInput(2, inputs, sizeof(INPUT));
		Sleep(300);
	}

	Sleep(500);

	// ���� Ű ������
	INPUT inputs[2];
	memset(inputs, 0, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_RETURN; // ���� Ű �ڵ�
	inputs[0].ki.dwFlags = 0;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_RETURN; // ���� Ű �ڵ�
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));
}
