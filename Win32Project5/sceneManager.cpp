#include "My_Include.h"

//////////////////////////////////////////////////////////////////////////
//
// cSceneManager() : ������(��������� �ʱ�ȭ)
//
// ���ڰ� : ����
//
// ��ȯ�� : ����
//
cSceneManager::cSceneManager()
{
	m_Scene					= NULL;				
	m_CurFrame				= NULL;				
	m_CurKey				= NULL;				
	m_bFrameOnceCompleted	= FALSE;
	m_FrameIdx				= 0;
	
	m_MaxImage				= 0;
	m_ImgList				= NULL;
}


//////////////////////////////////////////////////////////////////////////
//
// ~cSceneManager() : �Ҹ���(�����Ҵ�� ����� ����)
//
// ���ڰ� : ����
//
// ��ȯ�� : ����
//
cSceneManager::~cSceneManager()
{
	destroyFrameManager();
}


//////////////////////////////////////////////////////////////////////////
//
// void setDC : ����� ���� �޸� DC�� �����Ѵ�.
//
// ���ڰ� : HDC		memDC	- ����� �޸� DC
//
// ��ȯ�� : ����
//
void	cSceneManager::setDC(HDC memDC)
{
	m_backDC				= memDC;
}


//////////////////////////////////////////////////////////////////////////
//
// void setImageNum() : �ش� �����Ӹ޴������� ���� ��� �̹��� ���� ���� ��
//						�̹��� ������ ���� ��ü ����
//
// ���ڰ� : int		ImageNum	- ���� �̹��� ����
//
// ��ȯ�� : ����
//
void	cSceneManager::setImageNum(int ImageNum)
{
	m_MaxImage				= ImageNum;
	m_ImgList				= new cGdiImage[m_MaxImage];
}


//////////////////////////////////////////////////////////////////////////
//
// void setImage() : �̹��� ������ ���� ��ü�� �̹��� �ε��ϱ�
//					 (�̹��� ������ ���� ��ü�� �����Ǿ� �־�� ��)
//
// ���ڰ� : int		ImageIdx	- �̹��� ������ ���� ����� ��ü�� ����� �迭�� ���ؽ�
//			char*	ImgName		- �ε��� �̹����� ��� �� ���ϸ�
//
// ��ȯ�� : ����
//
void	cSceneManager::setImage(int ImageIdx, char* ImgName)
{
	m_ImgList[ImageIdx].setDC(m_backDC);
	m_ImgList[ImageIdx].Load(ImgName);
}


//////////////////////////////////////////////////////////////////////////
//
// void addScene() : ������ �޴����� ���� �����Ѵ�.
//
// ���ڰ� : string	sceneName	 - ���Ե� ���� �̸�(Ű)
//
// ��ȯ�� : ����
//
void	cSceneManager::addScene(char* sceneName)
{
	cScene*					pScene = new cScene();
	m_Scene					= pScene;
	m_SceneList[sceneName]	= pScene;
}


//////////////////////////////////////////////////////////////////////////
//
// void setMaxFrame() : ������ ���� �������� ���� �����ϰ� �̿� ���� ��� ��������� ũ�⸦ �Ҵ��Ѵ�.
//
// ���ڰ� : int		maxFrame		- �ش� ���� ��ü ������ ��
//          
// ��ȯ�� : ����
//
void	cSceneManager::setMaxFrame(int maxFrame)
{
	m_Scene->setMaxFrame(maxFrame);
	m_FrameIdx				= 0;
}


//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame() : ������ ���� �������� �������� �ʰ� ��ó������ 
//								 �������� �����ϴ� ����� �ִ� ������ �����Ѵ�.
//
// ���ڰ� : int		maxElement		- �ִ� ��� ��
//          DWORD	frameTime		- ������ �ð�
//          
// ��ȯ�� : ����
//
void	cSceneManager::setMaxElementOfFrame(DWORD frameTime)
{
	m_Scene->setMaxElementOfFrame(m_FrameIdx, frameTime);
	m_ElementOfFrameIdx = m_FrameIdx;
	m_FrameIdx++;
}


//////////////////////////////////////////////////////////////////////////
//
// void addElementOfFrame() : �������� ��Ҹ� �߰��Ѵ�.
//
// ���ڰ� : int		imageIdx		- �̹��� ��ȣ(�̹��� ID)
//          int		frameIntervalX  - ���������κ��� X������ �̵��Ͽ� ����� ��
//			int		frameIntervalY	- ���������κ��� Y������ �̵��Ͽ� ����� ��
//			int		imageIntervalX	- �̹����� X��
//			int		imageIntervalY	- �̹����� Y��
//			int		w				- �̹����� ����
//			int		h				- �̹����� ����
//			int		layer			- �������� ���̾�
//          
// ��ȯ�� : ����
//
void	cSceneManager::addElementOfFrame(int imageIdx,
										 int frameIntervalX, int frameIntervalY, 
										 int imageIntervalX, int imageIntervalY,
										 int w, int h)
{
	m_Scene->addElementOfFrame(m_ElementOfFrameIdx, 
		imageIdx, frameIntervalX, frameIntervalY, 
		imageIntervalX, imageIntervalY, w, h);
}


//////////////////////////////////////////////////////////////////////////
//
// void setFirstFrame() : ���� ���� ������������ ù���������� ����
//
// ���ڰ� : ����
//          
// ��ȯ�� : ����
//
void	cSceneManager::setFirstFrame()
{
	m_CurFrame				= 0;
	m_bFrameOnceCompleted	= FALSE;
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void setLastFrame() : ���� ���� ������������ ���������������� ����
//
// ���ڰ� : ����
//          
// ��ȯ�� : ����
//
void	cSceneManager::setLastFrame()
{
	m_CurFrame				= m_Scene->getMaxFrame() - 1;
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void nextFrame() : ���� ���� ������������ �������������� ����.
//					  ������ ��½ð����� ���� ��� return��.
//                    ������ ������ ������ ������ ���� Ŭ ��� ó������ �����ϸ�, ���� ���� �Ϸ� ���� TRUE�� ������
//
// ���ڰ� : ����
//          
// ��ȯ�� : ����
//
void	cSceneManager::nextFrame()
{
	if( GetTickCount() - m_OutFrameTime 
		< m_Scene->getFrameTime(m_CurFrame))
		return;

	m_CurFrame++;
	if( m_CurFrame >= m_Scene->getMaxFrame())
	{
		m_CurFrame				= 0;
		m_bFrameOnceCompleted	= TRUE;
	}
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void setScene() : ������� ����
//
// ���ڰ� : char*	sceneName	- �����ϰ��� �ϴ� ���� �̸�(Ű)
//								  �ʱ� addScene()�� ���� ��ϵ� �̸��� ��밡��
//          
// ��ȯ�� : ����
//
void	cSceneManager::setScene(char* sceneName)
{
	map<char*, cScene*>::iterator	it;
	it						= m_SceneList.find(sceneName);
	if( it == m_SceneList.end() )
		return;
	else
	{
		m_CurKey			= it->first;
		m_Scene				= it->second;
		setFirstFrame();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrame() : ���� ���� ���� �������� ����Ѵ�.
//
// ���ڰ� : int		x		 - ��µ� X��ǥ
//			int		y        - ��µ� Y��ǥ
//          
// ��ȯ�� : ����
//
void	cSceneManager::drawFrame(int x, int y)
{
	int						imgNum;
	int						sx, sy, iw, ih, ix, iy;

	imgNum				= m_Scene->getImgNum(m_CurFrame);
	sx					= m_Scene->getPosOffsetX(m_CurFrame) + x;
	sy					= m_Scene->getPosOffsetY(m_CurFrame) + y;
	iw					= m_Scene->getImgSizeX(m_CurFrame);
	ih					= m_Scene->getImgSizeY(m_CurFrame);
	ix					= m_Scene->getImgOffsetX(m_CurFrame);
	iy					= m_Scene->getImgOffsetY(m_CurFrame);

	m_ImgList[imgNum].Draw(sx, sy, ix, iy, iw, ih);
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameRGB() : ���� ���� ���� �������� ����Ѵ�.
//
// ���ڰ� : int		x		 - ��µ� X��ǥ
//			int		y        - ��µ� Y��ǥ
//			UING	uRGB	 - ����ó���� ����          
//
// ��ȯ�� : ����
//
void	cSceneManager::drawFrameRGB(int x, int y, UINT uRGB)
{
	int						imgNum;
	int						sx, sy, iw, ih, ix, iy;

	imgNum				= m_Scene->getImgNum(m_CurFrame);
	sx					= m_Scene->getPosOffsetX(m_CurFrame) + x;
	sy					= m_Scene->getPosOffsetY(m_CurFrame) + y;
	iw					= m_Scene->getImgSizeX(m_CurFrame);
	ih					= m_Scene->getImgSizeY(m_CurFrame);
	ix					= m_Scene->getImgOffsetX(m_CurFrame);
	iy					= m_Scene->getImgOffsetY(m_CurFrame);

	m_ImgList[imgNum].Draw(sx, sy, ix, iy, iw, ih, iw, ih, uRGB);
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameAuto() : ���� ���� ���� �������� ����ϰ� ������ ������ ���� ��Ų��.
//
// ���ڰ� : int		x		 - ��µ� X��ǥ
//			int		y        - ��µ� Y��ǥ
//          
// ��ȯ�� : ����
//
void	cSceneManager::drawFrameAuto(int x, int y)
{
	drawFrame(x, y);
	nextFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameAutoRGB() : ���� ���� ���� �������� ����ϰ� ������ ������ ���� ��Ų��.
//
// ���ڰ� : int		x		 - ��µ� X��ǥ
//			int		y        - ��µ� Y��ǥ
//			UINT	uRGB	 - ����ó���� ��������          
//
// ��ȯ�� : ����
//
void	cSceneManager::drawFrameAutoRGB(int x, int y, UINT uRGB)
{
	drawFrameRGB(x, y, uRGB);
	nextFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// void delAllScene() : ������ ���� �� ��� ��� �ʱ�ȭ
//
// ���ڰ� : ����
//          
// ��ȯ�� : ����
//
void	cSceneManager::delAllScene()
{
	destroyFrameManager();
}


//////////////////////////////////////////////////////////////////////////
//
// void delScene() : Ư�� ���� ����
//
// ���ڰ� : char*	sceneName	- ������ ���� �̸�(Ű)
//          
// ��ȯ�� : ����
//
void	cSceneManager::delScene(char* sceneName)
{
	map<char*, cScene*>::iterator	it;
	it						= m_SceneList.find(sceneName);
	if( it == m_SceneList.end() )
		return;
	else
	{	
		delete it->second;
		m_SceneList.erase(it->first);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// void delSceneElement() : Ư�� ���� ������ ���� ����
//
// ���ڰ� : cScene*		pScene	- ������ ������ ������ ���� ������
//          
// ��ȯ�� : ����
//
void	cSceneManager::delSceneElement(cScene* pScene)
{
	pScene->destroyScene();
}


//////////////////////////////////////////////////////////////////////////
//
// int getMaxFrame() : ���� ���� �ִ� �����Ӽ��� ��ȯ�Ѵ�.
//
// ���ڰ� : ����
//          
// ��ȯ�� : int					- ������� �ִ������Ӽ�
//
int		cSceneManager::getMaxFrame()
{
	return m_Scene->getMaxFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// int getCurFrame() : ���� ���� ���� �������� ������ ��ȯ
//				
// ���ڰ� : ����
//          
// ��ȯ�� : int					- ���� �����Ӱ�
//
int		cSceneManager::getCurFrame()
{
	return m_CurFrame;
}


//////////////////////////////////////////////////////////////////////////
//
// int destroyFrameManager() : �ش� �����Ӹ޴��� ��� ������ �޸� ����
//				
// ���ڰ� : ����
//          
// ��ȯ�� : ����
//
void	cSceneManager::destroyFrameManager()
{
	map<char*, cScene*>::iterator it;
	for( it = m_SceneList.begin() ; it != m_SceneList.end() ; it++ )
	{
		delete it->second;
		//m_SceneList.erase(it->first);
	}

	if( m_ImgList != NULL )
		delete []m_ImgList;

	m_Scene					= NULL;				
	m_CurFrame				= NULL;				
	m_CurKey				= NULL;				
	m_bFrameOnceCompleted	= FALSE;
	m_FrameIdx				= 0;
	m_ElementOfFrameIdx		= 0;
	m_MaxImage				= 0;
}

BOOL	cSceneManager::getFrameOnce()
{
	return m_bFrameOnceCompleted;
}

char*	cSceneManager::getCurKey()
{
	return m_CurKey;
}

void	cSceneManager::setFrame(int frameIDX)
{
	if( frameIDX < 0 || frameIDX > getMaxFrame()-1 )
		return;

	m_CurFrame = frameIDX;
}