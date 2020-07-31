#include "scene.h"

cScene::cScene()
{
	m_MaxFrame				= 0;
	m_FrameArr				= NULL;
	m_FrameTime				= NULL;
}

cScene::~cScene()
{
	destroyScene();
}

void	cScene::setMaxFrame(int maxFrame)
{
	if( maxFrame != 0 )
		destroyScene();

	m_MaxFrame				= maxFrame;
	m_FrameArr				= new cFrame[maxFrame];
	m_FrameTime				= new DWORD[maxFrame];
}

int		cScene::getMaxFrame()
{
	return m_MaxFrame;
}

void	cScene::setMaxElementOfFrame(int frameIdx, DWORD frameTime)
{
	m_FrameTime[frameIdx]	= frameTime;
}

//////////////////////////////////////////////////////////////////////////
//
// void addElementOfFrame() : �������� ��Ҹ� �߰��Ѵ�.
//
// ���ڰ� : int		frameIdx		- �߰��Ϸ��� ��Ҹ� ������ �����ӹ�ȣ
//			int		elementIdx		- �߰��Ϸ��� ����� ��ġ
//			int		imageIdx		- �̹��� ��ȣ
//			int		frameIntervalX	- ���������κ��� X������ �̵��Ͽ� ����� ��
//			int		frameIntervalY	- ���������κ��� Y������ �̵��Ͽ� ����� ��
//			int		imageIntervalX	- �̹����� X��
//			int		imageIntervalY	- �̹����� Y��
//			int		w				- �̹����� ����
//			int		h				- �̹����� ����
//			int		layer			- �������� ���̾�
//          
// ��ȯ�� : ����
//
void	cScene::addElementOfFrame(int frameIdx, int imageIdx,
								  int frameIntervalX, int frameIntervalY,
								  int imageIntervalX, int imageIntervalY,
								  int w, int h)
{
	m_FrameArr[frameIdx].setImgNum(imageIdx);
	m_FrameArr[frameIdx].setPosOffset(frameIntervalX, frameIntervalY);
	m_FrameArr[frameIdx].setImgOffset(imageIntervalX, imageIntervalY);
	m_FrameArr[frameIdx].setImgSize(w, h);
}

DWORD	cScene::getFrameTime(int frameIdx)
{
	return m_FrameTime[frameIdx];
}

void	cScene::destroyScene()
{
	m_MaxFrame				= 0;

	if( m_FrameArr != NULL )
	{
		delete []m_FrameArr;
		m_FrameArr			= NULL;
	}

	if( m_FrameTime != NULL )
	{
		delete []m_FrameTime;
		m_FrameTime			= NULL;
	}
}

int		cScene::getImgNum(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgNum();
}

int		cScene::getImgSizeX(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgSizeX();
}

int		cScene::getImgSizeY(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgSizeY();
}

int		cScene::getPosOffsetX(int frameIdx)
{
	return m_FrameArr[frameIdx].getPosOffsetX();
}

int		cScene::getPosOffsetY(int frameIdx)
{
	return m_FrameArr[frameIdx].getPosOffsetY();
}

int		cScene::getImgOffsetX(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgOffsetX();
}

int		cScene::getImgOffsetY(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgOffsetY();
}