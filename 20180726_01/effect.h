//=============================================================================
//
// 敵処理 [effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


// マクロ定義
#define	NUM_EFFECT				(2)			// ポリゴン数

#define TEXTURE_GAME_EFFECT		_T("data/TEXTURE/bomb2.png")	// 画像
#define TEXTURE_EFFECT_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_EFFECT_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT			(4)	// アニメーションの切り替わるカウント
#define EFFECT_MAX						(1) // 敵の最大数





//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			InitY=500.0f;				//初期Y値
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effectcounter;				//エフェクト管理
	


	float			effectpos_x;
	float			effectpos_y;
	//int				ENM = EFFECT_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_effect[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} EFFECT;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(int no);
void SetEffect(D3DXVECTOR3 pos, int i);



#endif
