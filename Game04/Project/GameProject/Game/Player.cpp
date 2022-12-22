#include"Player.h"
#include"Bullet.h"
#include"Map.h"
Player::Player(const CVector2D& pos)
	:Base(eType_Player)
{
	m_img = COPY_RESOURCE("Player", CImage);
	//中心を設定
	m_img.SetCenter(16, 16);
	//矩形を設定
	m_rect = CRect(-16, -16, 16, 16);
	
	//プレイヤーの位置がチップの中心になるように調整
	m_pos = pos + m_img.m_center;


	//マップの取得
	if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
		m->GetColRow(m_pos, &m_col, &m_row);
		m->GetColRow(m_pos, &m_old_col, &m_old_row);
	}
	//上から進入したことにする
	m_entry_dir = eUp;
}
void Player::Update()
{
	//マップ取得
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field));
	//マップが無ければ動かない
	if (!m) return;

	//移動速度
	const float speed = 1;

	
	//乗っているチップの種類
	int t = m->GetTip(m_pos);

	//乗っているチップによって動き方が変わる
	switch (t) {
		//0:空白
		//1:上右(右上)カーブ
	case 1:

		if (m_entry_dir == eUp) {
			//上から来たなら、右下へ移動
			m_pos.y += speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eRight) {
				//右から来たなら左上に移動
				m_pos.y -= speed;
				m_pos.x += speed;
			}
			else {
				//それ以外なら繋がらない
			}
		break;
		//2:上下ストレート
	case 2:
		if (m_entry_dir == eUp) {
			//上から来たなら、下へ移動
			m_pos.y += speed;
		}
		else
			if (m_entry_dir == eDown) {
				//下から来たなら上に移動
				m_pos.y -= speed;
			}else{
				//それ以外なら繋がらない
	}
		break;
		//3:左右ストレート
	case 3:
		if (m_entry_dir == eLeft) {
			//左から来たなら、右へ移動
			m_pos.x += speed;
		}else 
		if (m_entry_dir == eRight) {
			//右から来たなら、左へ移動
			m_pos.x -= speed;
		} else {
			//それ以外なら繋がらない
		}
		break;
		//4:下右(右下)カーブ
	case 4:
		if (m_entry_dir == eRight) {
			//右から来たなら、左下へ移動
			m_pos.y += speed;
			m_pos.x -= speed;
		}
		else
			if (m_entry_dir == eDown) {
				//下から来たなら、右上へ移動
				m_pos.y -= speed;
				m_pos.x += speed;
			}
			else {
				//それ以外なら繋がらない
			}
		break;
		//5:上左(左上)カーブ
	case 5:
		if (m_entry_dir == eLeft) {
			//左から来たなら、右上へ移動
			m_pos.y -= speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eUp) {
				//上から来たなら、左下へ移動
				m_pos.y += speed;
				m_pos.x -= speed;
			}
			else {
				//それ以外なら繋がらない
			}
		break;
		//6:下左(左下)カーブ
	case 6:
		if (m_entry_dir == eLeft) {
			//左から来たなら、右下へ移動
			m_pos.y += speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eDown) {
				//下から来たなら、左上へ移動
				m_pos.y -= speed;
				m_pos.x -= speed;
			}
			else {
				//それ以外なら繋がらない
			}
		break;
	}


	//次の行か列へ進んだかチェック
	//現在の位置での行と列を取得
	m->GetColRow(m_pos, &m_col, &m_row);
	
	if (m_col < m_old_col) {
		//一つ左の列に進んだ
		//右から進入した
		m_entry_dir = eRight;
		m_old_col = m_col;
	}
	else if (m_col > m_old_col) {
		//一つ右の列に進んだ
		//左から進入した
		m_entry_dir = eLeft;
		m_old_col = m_col;
	}

	 if (m_row < m_old_row) {
		//一つ上の行に進んだ
		//下から進入した
		m_entry_dir = eDown;
		m_old_row = m_row;
	}
	else if (m_row > m_old_row) {
		//一つ下の行に進んだ
		//上から進入した
		m_entry_dir = eUp;
		m_old_row = m_row;
	}
	 if (m_pos.x > 1250)
		 m_pos.x = 1250;
	 if (m_pos.x < 15)
		 m_pos.x = 15;
	 if (m_pos.y > 700)
		 m_pos.y = 700;
	 if (m_pos.y < 20)
		 m_pos.y = 20;
	



}
void Player::Collision(Base* b)
{


}
void Player::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}