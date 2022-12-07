#include"Map.h"

//チップ
//0:空白
//1:上右(右上)カーブ
//2:上下ストレート
//3:左右ストレート
//4:下右(右下)カーブ
//5:上左(左上)カーブ
//6:下左(左下)カーブ

static int stage1data[MAP_HEIGHT][MAP_WIDTH] = {
	{ 2,4,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{ 2,1,3,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{ 1,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() :Base(eType_Field)
{
	//画像複製
	m_img = COPY_RESOURCE("MapTip", CImage);
}
void Map::Draw()
{
	//マップチップによる表示の繰り返し
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//表示しない制御
			if (stage1data[i][j] == 0)continue;
			int t = stage1data[i][j];
			//画像切り抜き
			m_img.SetRect(32*t, 0, 32*t + 32, 32);
			//表示サイズ設定
			m_img.SetSize(MAP_TIP_SIZE, MAP_TIP_SIZE);
			//表示位置設定
			m_img.SetPos(MAP_TIP_SIZE * j, MAP_TIP_SIZE * i);
			//描画
			m_img.Draw();
		}
	}
}
int Map::GetTip(const CVector2D& pos)
{
	//列を計算
	int col = pos.x / MAP_TIP_SIZE;
	//列の制限(0～MAP_WIDTH-1)
	if (col < 0)col = 0;
	if (col > MAP_WIDTH - 1)col = MAP_WIDTH - 1;
	//行を計算
	int raw = pos.y / MAP_TIP_SIZE;
	//行の制限(0～MAP_HEIGHT-1)
	if (raw < 0)raw = 0;
	if (raw > MAP_HEIGHT - 1)raw = MAP_HEIGHT - 1;
	//チップデータを返却
	return GetTip(col, raw);
}
int Map::GetTip(int col, int raw)
{
	return stage1data[raw][col];
}
void Map::GetColRow(const CVector2D& pos, int* col, int* raw)
{
	//列を計算
	int c = pos.x / MAP_TIP_SIZE;
	//行を計算
	int r = pos.y / MAP_TIP_SIZE;
	if (col) *col = c;
	if (raw) *raw = r;
}
int Map::CollisionMap(const CVector2D& pos)
{
	//1点のみ検証
	int t = GetTip(pos);
	if (t != 0)return t;
	return 0;
}
int Map::CollisionMap(const CVector2D& pos, const CRect& rect)
{
	//左上
	int t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_top));
	if (t != 0) return t;
	//右上
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_top));
	if (t != 0) return t;
	//左下
	t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_bottom));
	if (t != 0) return t;
	//右下
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_bottom));
	if (t != 0) return t;
	return 0;
}
