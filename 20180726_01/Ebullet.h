//=============================================================================
//
// バレット処理 [Ebullet.h]
// Author : 
//
//=============================================================================
#ifndef _EBULLET_H_
#define _EBULLET_H_


// マクロ定義
#define	NUM_EBULLET				(2)			// ポリゴン数

#define TEXTURE_GAME_EBULLET		_T("data/TEXTURE/tama.png")	// 画像
#define TEXTURE_EBULLET_SIZE_X	(50/4)		// テクスチャサイズ
#define TEXTURE_EBULLET_SIZE_Y	(50/8)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EBULLET	(9)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EBULLET	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EBULLET			(TEXTURE_PATTERN_DIVIDE_X_EBULLET*TEXTURE_PATTERN_DIVIDE_Y_EBULLET)	// アニメーションパターン数
#define TIME_ANIMATION_EBULLET			(4)	// アニメーションの切り替わるカウント

#define EBULLET_MAX						(4) // バレットの最大数

#define EBULLET_SPEED			(-1.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		dis;

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				counter;					//バレットの制御
	int				Bcounter_ORG;				//
	float			SPPED_Y;
	float			SPPED_X;

	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} EBULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEBullet(int type);
void UninitEBullet(void);
void UpdateEBullet(void);
void DrawEBullet(void);
void SetEBullet(D3DXVECTOR3 pos);
EBULLET *GetEBullet(int no);


#endif
