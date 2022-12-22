#include"Player.h"
#include"Bullet.h"
#include"Map.h"
Player::Player(const CVector2D& pos)
	:Base(eType_Player)
{
	m_img = COPY_RESOURCE("Player", CImage);
	//���S��ݒ�
	m_img.SetCenter(16, 16);
	//��`��ݒ�
	m_rect = CRect(-16, -16, 16, 16);
	
	//�v���C���[�̈ʒu���`�b�v�̒��S�ɂȂ�悤�ɒ���
	m_pos = pos + m_img.m_center;


	//�}�b�v�̎擾
	if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
		m->GetColRow(m_pos, &m_col, &m_row);
		m->GetColRow(m_pos, &m_old_col, &m_old_row);
	}
	//�ォ��i���������Ƃɂ���
	m_entry_dir = eUp;
}
void Player::Update()
{
	//�}�b�v�擾
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field));
	//�}�b�v��������Γ����Ȃ�
	if (!m) return;

	//�ړ����x
	const float speed = 1;

	
	//����Ă���`�b�v�̎��
	int t = m->GetTip(m_pos);

	//����Ă���`�b�v�ɂ���ē��������ς��
	switch (t) {
		//0:��
		//1:��E(�E��)�J�[�u
	case 1:

		if (m_entry_dir == eUp) {
			//�ォ�痈���Ȃ�A�E���ֈړ�
			m_pos.y += speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eRight) {
				//�E���痈���Ȃ獶��Ɉړ�
				m_pos.y -= speed;
				m_pos.x += speed;
			}
			else {
				//����ȊO�Ȃ�q����Ȃ�
			}
		break;
		//2:�㉺�X�g���[�g
	case 2:
		if (m_entry_dir == eUp) {
			//�ォ�痈���Ȃ�A���ֈړ�
			m_pos.y += speed;
		}
		else
			if (m_entry_dir == eDown) {
				//�����痈���Ȃ��Ɉړ�
				m_pos.y -= speed;
			}else{
				//����ȊO�Ȃ�q����Ȃ�
	}
		break;
		//3:���E�X�g���[�g
	case 3:
		if (m_entry_dir == eLeft) {
			//�����痈���Ȃ�A�E�ֈړ�
			m_pos.x += speed;
		}else 
		if (m_entry_dir == eRight) {
			//�E���痈���Ȃ�A���ֈړ�
			m_pos.x -= speed;
		} else {
			//����ȊO�Ȃ�q����Ȃ�
		}
		break;
		//4:���E(�E��)�J�[�u
	case 4:
		if (m_entry_dir == eRight) {
			//�E���痈���Ȃ�A�����ֈړ�
			m_pos.y += speed;
			m_pos.x -= speed;
		}
		else
			if (m_entry_dir == eDown) {
				//�����痈���Ȃ�A�E��ֈړ�
				m_pos.y -= speed;
				m_pos.x += speed;
			}
			else {
				//����ȊO�Ȃ�q����Ȃ�
			}
		break;
		//5:�㍶(����)�J�[�u
	case 5:
		if (m_entry_dir == eLeft) {
			//�����痈���Ȃ�A�E��ֈړ�
			m_pos.y -= speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eUp) {
				//�ォ�痈���Ȃ�A�����ֈړ�
				m_pos.y += speed;
				m_pos.x -= speed;
			}
			else {
				//����ȊO�Ȃ�q����Ȃ�
			}
		break;
		//6:����(����)�J�[�u
	case 6:
		if (m_entry_dir == eLeft) {
			//�����痈���Ȃ�A�E���ֈړ�
			m_pos.y += speed;
			m_pos.x += speed;
		}
		else
			if (m_entry_dir == eDown) {
				//�����痈���Ȃ�A����ֈړ�
				m_pos.y -= speed;
				m_pos.x -= speed;
			}
			else {
				//����ȊO�Ȃ�q����Ȃ�
			}
		break;
	}


	//���̍s����֐i�񂾂��`�F�b�N
	//���݂̈ʒu�ł̍s�Ɨ���擾
	m->GetColRow(m_pos, &m_col, &m_row);
	
	if (m_col < m_old_col) {
		//����̗�ɐi��
		//�E����i������
		m_entry_dir = eRight;
		m_old_col = m_col;
	}
	else if (m_col > m_old_col) {
		//��E�̗�ɐi��
		//������i������
		m_entry_dir = eLeft;
		m_old_col = m_col;
	}

	 if (m_row < m_old_row) {
		//���̍s�ɐi��
		//������i������
		m_entry_dir = eDown;
		m_old_row = m_row;
	}
	else if (m_row > m_old_row) {
		//����̍s�ɐi��
		//�ォ��i������
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