//��������� ����Ѵ�
#include <Windows.h>

//�������� ����Ѵ�
HINSTANCE _hInstance;
HWND _hWnd;

LPTSTR _lpszClass = TEXT("������������");

//�Լ� ������Ÿ�� ���ش�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
 MSG message;  //�ü������ �߻��ϴ� �޽��� ������ �����ϱ� ���� ����ü(����)
 WNDCLASS wndClass; //�������� ������ �����ϱ� ���� ����ü ����

 _hInstance = hInstance;  

 wndClass.cbClsExtra = 0;          //Ŭ���� ���� �޸�
 wndClass.cbWndExtra = 0;          //������ ���� �޸�
 wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������ ��׶��� ����
 wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);     //������ Ŀ��
 wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //������ ������
 wndClass.hInstance = hInstance;         //������ �ν��Ͻ�
 wndClass.lpfnWndProc = (WNDPROC)WndProc;      //���ν���
 wndClass.lpszClassName = _lpszClass;       //Ŭ���� �̸�
 wndClass.lpszMenuName = NULL;         //�޴��̸�
 wndClass.style = CS_HREDRAW | CS_VREDRAW;      //������ ������~

 //������ Ŭ���� ���
 RegisterClass(&wndClass);

 //������ ����
 _hWnd = CreateWindow(
  _lpszClass,    //������ Ŭ���� �̸�
  _lpszClass,    //������ Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
  WS_OVERLAPPEDWINDOW, //������ ��Ÿ��
  50,      //������ â ���� X��ǥ
  50,      //������ â ���� Y��ǥ
  800,     //������ ����ũ��
  600,     //������ ����ũ��
  NULL,     //�θ� ������ ����
  (HMENU)NULL,   //�޴��ڵ�
  hInstance,    //�ν��Ͻ� ������ ����
  NULL);

 //ȭ�鿡 ������ �����ش�
 ShowWindow(_hWnd, cmdShow);

 /*   ���ӿ�! ����Ǯ�� ���� (Ǯ��� �ϱ�������)
 while (true)
 {
  if (PeekMessage(&message, NULL, OU, OU, PM_REMOVE))
  {
   if (message.message == WM_QUIT) break;
   TranslateMessage(&message);
   DispatchMessage(&message);
  }
  else
  {
   Render();
  }

 }
 */

 //�޼��� ����
 while (GetMessage(&message, 0, 0, 0))
 {

  TranslateMessage(&message); //Ű���� �Է� �޽��� ó���� ���
  DispatchMessage(&message); //������ ������� ������ �ش�
 }

 return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
 //hWnd : ��� �����쿡�� �޽����� �߻��ߴ°�?
 //iMessage : �޽��� ���� ��ȣ
 //wParam : ���콺 ��ư ����, Ű���� ����
 //lParam : ���콺 ��ǥ��ġ ����


 switch (iMessage)
 {
  case WM_DESTROY:
   PostQuitMessage(0);
  break;

 }

 return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
