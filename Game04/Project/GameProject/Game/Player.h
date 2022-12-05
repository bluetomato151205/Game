#pragma once
#include"../Base/Base.h"

class Player :public Base {
	CImage m_img;
	enum {
		eLeft,	//左から進入
		eRight,	//右から進入
		eUp,	//上から進入
		eDown,	//下から進入
	};
	//進入方向
	int	m_entry_dir;
	//現在の行と列
	int m_col, m_row;
	//一つ前の行と列
	int m_old_col, m_old_row;
public:
	Player(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};