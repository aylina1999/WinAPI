#include<Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "My Window Class";

LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����:
	 WNDCLASSEX wc;
	 ZeroMemory(&wc, sizeof(wc));

	 wc.cbSize = sizeof(WNDCLASSEX);
	 wc.cbClsExtra = 0;
	 wc.cbWndExtra = 0;
	 wc.style = 0; 
	 
	 wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION); //������, ������������ � ������ �����
	 wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);  //������, ������������ � ������ ���������
	 wc.hCursor = LoadCursor(hInstance, IDC_ARROW);      //��������� ���� ��� ��������� �� ����
	 wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);      //���� ���� ����

	 wc.hInstance = hInstance;                 //���������, ���������� ���������
	 wc.lpfnWndProc = WinProc;                 //��������� �� ��������� ����
	 wc.lpszMenuName = NULL;                   
	 wc.lpszClassName = g_sz_WINDOW_CLASS;     //��� ������ ����. ��������� ����� ����, ������� ����������� ������-�� ������
	                                           //�.�. ��������� ����� ���� ������-�� ���� (������, ��������� ����...)
	 if (!RegisterClassEx(&wc))
	 {
		 MessageBox(NULL, "Something went wrong", "Error", MB_OK | MB_ICONERROR);
		 return 0;
	 }

	//2) �������� ����:
	
	 HWND hwnd = CreateWindowEx
	 (
		 NULL,
		 g_sz_WINDOW_CLASS,   //��� ������ �����
		 g_sz_WINDOW_CLASS,   //��������� ����
		 WS_OVERLAPPEDWINDOW,       //������ ���� ���������, ��� ���������� TopLevelWindow
		
		 CW_USEDEFAULT, CW_USEDEFAULT,
		 CW_USEDEFAULT, CW_USEDEFAULT,
		
		 NULL,   //Parent
		 NULL,   //��� �������� ���� - ��� ID ����.
		         //��� �������� ���� - ��� ID_ ������� ����� ��������(IDC_EDIT, IDC_BOUTTON..)
		 hInstance,   //���� ��� ������� ������� � hInstance, �������� ������, ��� �� �� �������� ��� ��� ��������,
		              //�� ��� ������ ����� �������� ��� ������ ������� GetModuleHandle(NULL);
		 NULL
	 );
	 DWORD dwErrorMessageID = GetLastError();

	 if (hwnd == NULL)
	 {
		// MessageBox(NULL, "���� �� �����������, ������� ������� ���� �� ��������", "�������� ����������", MB_OK | MB_ICONINFORMATION);
		 
		 LPSTR messageBuffer = NULL;
		 DWORD dwSize =
			 FormatMessage
			 (
				 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_INSERTS
				 NULL,
				 dwErrorMessageID,
				 MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
				 (LPSTR)&lpszMessageBuffer,
				 0,
				 NULL
			 );
		 MessageBox(NULL, lpszMessageBuffer, "Error", MB_OK | MB_ICONERROR)
			 LocalFree(lpszMessageBuffer);
			 return 0;
	 }
	 ShowWindow(hwnd, nCmdShow);  //����� ����� ����������� ����
	 UpdateWindow(hwnd);          //��������� ���������� ����
	
	//3) ������ ����� ���������:

	 return 0;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}