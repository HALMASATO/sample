//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET2_H_
#define _BULLET2_H_


// マクロ定義
#define	NUM_BULLET2				(2)			// ポリゴン数

#define TEXTURE_GAME_BULLET2		_T("data/TEXTURE/rifle.png")	// 画像
#define TEXTURE_BULLET2_SIZE_X	(50/4)		// テクスチャサイズ
#define TEXTURE_BULLET2_SIZE_Y	(50/8)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BULLET2	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BULLET2			(TEXTURE_PATTERN_DIVIDE_X_BULLET2*TEXTURE_PATTERN_DIVIDE_Y_BULLET2)	// アニメーションパターン数
#define TIME_ANIMATION_BULLET2			(4)	// アニメーションの切り替わるカウント

#define BULLET2_MAX						(3) // バレットの最大数

#define BULLET2_SPEED			(-6.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	bool			BBflag;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				BM =0;						//bulletの弾を入れておく変数
	int				reload=0;
	int				counter = 0;				//弾を打ってからの秒数を数える
	int				HP;
	float			posx1;
	float			posx2;
	float			posy1;
	float			posy2;

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度


} BULLET2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet2(int type);
void UninitBullet2(void);
void UpdateBullet2(void);
void DrawBullet2(void);
void SetBullet2(D3DXVECTOR3 pos);
BULLET2 *GetBullet2(int no);


#endif
