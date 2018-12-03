//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_


// マクロ定義
#define	NUM_TARGET		(2)					// ポリゴン数

#define TEXTURE_GAME_TARGET	_T("data/TEXTURE/target.png")	// 画像
#define TEXTURE_TARGET_SIZE_X	(100/2) // テクスチャサイズ
#define TEXTURE_TARGET_SIZE_Y	(100/2) // 同上

#define TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント

#define TARGET_MAX					(1) // プレイヤーの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		pos1;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				enemy_x;
	int				enemy_y;
	int				HP;
	int				Timecounter;
	int				Hitcounter;
	int				drawcounter;
	bool			rockflug;

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// プレイヤーの半径
	float			BaseAngle;					// プレイヤーの角度

} TARGET;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTarget(int type);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
TARGET *GetTarget(int no);


#endif
