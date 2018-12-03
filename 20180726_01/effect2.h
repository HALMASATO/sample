//=============================================================================
//
// 敵処理 [effect2.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT2_H_
#define _EFFECT2_H_


// マクロ定義
#define	NUM_EFFECT2				(2)			// ポリゴン数

#define TEXTURE_GAME_EFFECT2		_T("data/TEXTURE/bomb2.png")	// 画像
#define TEXTURE_EFFECT2_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_EFFECT2_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT2	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT2	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EFFECT2			(TEXTURE_PATTERN_DIVIDE_X_EFFECT2*TEXTURE_PATTERN_DIVIDE_Y_EFFECT2)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT2			(4)	// アニメーションの切り替わるカウント
#define EFFECT2_MAX						(1) // 敵の最大数





//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	//bool			effectflag2;
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			InitY=500.0f;				//初期Y値
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effect2counter;				//エフェクト管理
	


	float			effect2pos_x;
	float			effect2pos_y;
	//int				ENM = EFFECT2_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_effect2[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} EFFECT2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect2(int type);
void UninitEffect2(void);
void UpdateEffect2(void);
void DrawEffect2(void);
EFFECT2 *GetEffect2(int no);
void SetEffect2(D3DXVECTOR3 pos, int i);



#endif
