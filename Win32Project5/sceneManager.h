#pragma once

#include "scene.h"
#include "cGdiImage.h"
#include <string>
#include <map>
using namespace std;

class cSceneManager
{
	HDC						m_backDC;
	cGdiImage*				m_ImgList;				//���� �̹��� ����Ʈ
	int						m_MaxImage;				//���� �̹��� ����
	map<char*, cScene*>		m_SceneList;			//���� �����ϱ� ���� �����̳�
	cScene*					m_Scene;				//���� ��
	int						m_CurFrame;				//������ ���� Ȱ��ȭ�� ������
	char*					m_CurKey;				//���� ���� key ��
	BOOL					m_bFrameOnceCompleted;	//�� ���� ��� �������� ����Ͽ�����
	DWORD					m_OutFrameTime;			//���������� ��µǾ������� ī����

	int						m_FrameIdx;				//������ �߰��� �߰��Ǿ�� �� ���� ����Ų��.
	int						m_ElementOfFrameIdx;
public:
	cSceneManager();
	~cSceneManager();

	void		setDC(HDC memDC);
	void		setImageNum(int ImageNum);								//���� �̹����� ����
	void		setImage(int ImageIdx, char* ImgName);					//�̹��� �߰�
	void		addScene(char* sceneName);								//�� �߰�
	void		setMaxFrame(int maxFrame);								//���� �����Ӽ� ����
	void		setMaxElementOfFrame(DWORD frameTime);	//�ش� �������� �̹������� �����ӽð� ����
	void		addElementOfFrame(int imageIdx, 
		int frameIntervalX, int frameIntervalY, 
		int imageIntervalX,	int imageIntervalY,
		int w, int h);
	void		setFirstFrame();										//���� ���� ù���������� �̵�
	void		setLastFrame();											//���� ���� ������ ���������� �̵�
	void		nextFrame();											//���� ���� ������ �ѱ��
	void		setFrame(int frameIDX);

	void		setScene(char* sceneName);								//�� ����
	void		drawFrame(int x, int y);								//���� ���� ���� ������ ���(������ �ѱ�� ����)
	void		drawFrameRGB(int x, int y, UINT uRGB);
	void		drawFrameAuto(int x, int y);							//���� ���� ���� ������ ���(������ �ѱ�� �ڵ�)
	void		drawFrameAutoRGB(int x, int y, UINT uRGB);							//���� ���� ���� ������ ���(������ �ѱ�� �ڵ�)

	void		delAllScene();											//��� ������
	void		delScene(char* sceneName);								//Ư���� ����
	void		delSceneElement(cScene* pScene);						//Ư������ ������ ���� ����
	void		destroyFrameManager();									//��� ���� ����

	int			getMaxFrame();											//���� ���� �� �����Ӽ� ���ϱ�										
	int			getCurFrame();											//���� ���� ������ ��ȣ ���ϱ�
	BOOL		getFrameOnce();
	char*		getCurKey();

};