//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// マクロ定義
#define	NUM_BULLET				(2)			// ポリゴン数

#define TEXTURE_GAME_BULLET		_T("data/TEXTURE/redtama.png")	// 画像
#define TEXTURE_BULLET_SIZE_X	(50/4)		// テクスチャサイズ
#define TEXTURE_BULLET_SIZE_Y	(50/8)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// アニメーションパターン数
#define TIME_ANIMATION_BULLET			(4)	// アニメーションの切り替わるカウント

#define BULLET_MAX						(8) // バレットの最大数

#define BULLET_SPEED			(6.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	bool			BBflag;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		dis;

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				BM;						//bulletの弾を入れておく変数
	int				reload;
	int				counter;				//弾を打ってからの秒数を数える
	int				MAXreload;				//
	float			SPPED_Y;
	float			SPPED_X;
	float			zet;						//絶対値


	float			posx1;
	float			posx2;
	float			posy1;
	float			posy2;


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度


} BULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
BULLET *GetBullet(int no);


#endif
