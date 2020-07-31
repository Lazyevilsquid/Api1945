#pragma once

#include <Windows.h>

class cFrame
{
private:
	int 		m_ImgNum ;		//�̹����� ����� �迭�� �ε���
	int 		m_ImgWidth ;	//�̹��� ����
	int 		m_ImgHeight ;	//�̹��� ����
	int 		m_PosOffsetX ;	//X ��� offset 
	int 		m_PosOffsetY ;	//Y ��� offset
	int 		m_ImgOffsetX ;	//�����̹������� x ��ǥ
	int 		m_ImgOffsetY ;	//�����̹������� y ��ǥ

public:
	cFrame() ;
	~cFrame() ;

	void		setImgNum(int imgNum);
	void		setImgSize(int width, int height);
	void		setPosOffset(int xValue, int yValue);
	void		setImgOffset(int xValue, int yValue);

	int			getImgNum();
	int			getImgSizeX();
	int			getImgSizeY();
	int			getPosOffsetX();
	int			getPosOffsetY();
	int			getImgOffsetX();
	int			getImgOffsetY();
};