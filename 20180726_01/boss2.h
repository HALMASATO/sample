//=============================================================================
//
// 敵処理 [BOSS2.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS2_H_
#define _BOSS2_H_


// マクロ定義
#define	NUM_BOSS2				(2)			// ポリゴン数

#define TEXTURE_GAME_BOSS2		_T("data/TEXTURE/boss3.png")	// 画像
#define TEXTURE_BOSS2_SIZE_X	(200)		// テクスチャサイズ
#define TEXTURE_BOSS2_SIZE_Y	(200)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSS2	(6)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSS2			(TEXTURE_PATTERN_DIVIDE_X_BOSS2*TEXTURE_PATTERN_DIVIDE_Y_BOSS2)	// アニメーションパターン数
#define TIME_ANIMATION_BOSS2			(4)	// アニメーションの切り替わるカウント

#define BOSS2_MAX						(1) // 敵の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			effectflag;
	bool			drawflug;
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				i;
	int				counter;
	int				Bcounter;
	int				Bcounter_ORG;
	int				Hitcounter;
	int				Timecounter;
	int				Popcounter;
	int				HP;
	int				MAXHP;


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_boss2[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} BOSS2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss2(int type);
void UninitBoss2(void);
void UpdateBoss2(void);
void DrawBoss2(void);
BOSS2 *GetBoss2(int no);


#endif
