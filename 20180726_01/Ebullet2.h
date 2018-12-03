//=============================================================================
//
// バレット処理 [Ebullet2.h]
// Author : 
//
//=============================================================================
#ifndef _EBULLET2_H_
#define _EBULLET2_H_


// マクロ定義
#define	NUM_EBULLET2				(2)			// ポリゴン数

#define TEXTURE_GAME_EBULLET2		_T("data/TEXTURE/purple.png")	// 画像
#define TEXTURE_EBULLET2_SIZE_X	(50/4)		// テクスチャサイズ
#define TEXTURE_EBULLET2_SIZE_Y	(50/8)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EBULLET2	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EBULLET2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EBULLET2			(TEXTURE_PATTERN_DIVIDE_X_EBULLET2*TEXTURE_PATTERN_DIVIDE_Y_EBULLET2)	// アニメーションパターン数
#define TIME_ANIMATION_EBULLET2			(4)	// アニメーションの切り替わるカウント

#define EBULLET2_MAX						(6) // バレットの最大数

#define EBULLET2_SPEED			(-1.0f)		// バレットの移動スピード


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

} EBULLET2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEBullet2(int type);
void UninitEBullet2(void);
void UpdateEBullet2(void);
void DrawEBullet2(void);
void SetEBullet2(D3DXVECTOR3 pos);
EBULLET2 *GetEBullet2(int no);


#endif
