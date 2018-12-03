//=============================================================================
//
// 敵処理 [effect3.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT3_H_
#define _EFFECT3_H_


// マクロ定義
#define	NUM_EFFECT3				(2)			// ポリゴン数

#define TEXTURE_GAME_EFFECT3		_T("data/TEXTURE/bomb2.png")	// 画像
#define TEXTURE_EFFECT3_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_EFFECT3_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT3	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT3	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_EFFECT3			(TEXTURE_PATTERN_DIVIDE_X_EFFECT3*TEXTURE_PATTERN_DIVIDE_Y_EFFECT3)	// アニメーションパターン数
#define TIME_ANIMATION_EFFECT3			(4)	// アニメーションの切り替わるカウント
#define EFFECT3_MAX						(1) // 敵の最大数





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
	float			InitY=700.0f;				//初期Y値
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effect3counter;				//エフェクト管理
	


	float			effect3pos_x;
	float			effect3pos_y;
	//int				ENM = EFFECT3_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_effect3[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} EFFECT3;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect3(int type);
void UninitEffect3(void);
void UpdateEffect3(void);
void DrawEffect3(void);
EFFECT3 *GetEffect3(int no);
void SetEffect3(D3DXVECTOR3 pos, int i);



#endif
