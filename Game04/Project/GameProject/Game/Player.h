#pragma once
#include"../Base/Base.h"

class Player :public Base {
	CImage m_img;
	enum {
		eLeft,	//������i��
		eRight,	//�E����i��
		eUp,	//�ォ��i��
		eDown,	//������i��
	};
	//�i������
	int	m_entry_dir;
	//���݂̍s�Ɨ�
	int m_col, m_row;
	//��O�̍s�Ɨ�
	int m_old_col, m_old_row;
public:
	Player(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};