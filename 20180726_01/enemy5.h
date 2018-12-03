//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY5_H_
#define _ENEMY5_H_


// マクロ定義
#define	NUM_ENEMY5				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY5		_T("data/TEXTURE/tama.png")	// 画像
#define TEXTURE_ENEMY5_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_ENEMY5_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY5	(9)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY5	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY5			(TEXTURE_PATTERN_DIVIDE_X_ENEMY5*TEXTURE_PATTERN_DIVIDE_Y_ENEMY5)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY5			(4)	// アニメーションの切り替わるカウント
#define ENEMY5_MAX						(6) // 敵の最大数





//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			deadflag;					//true:死亡　false:生存
	bool			BBflag;						//バレットと当たったらtrue
	bool			comeback;					//再登場のflag
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				counter;
	int				Mcounter;					//動いているときのカウント
	//float			InitY;						//初期Y値
	int				i;
	int             pattern;
	int				Bcounter;
	int				Bcounter_ORG;
	int				flag;
	bool			effectflag;

	

	float			enemy5pos_x;
	float			enemy5pos_y;
	//int				ENM = ENEMY5_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_enemy5[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} ENEMY5;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy5(int type);
void UninitEnemy5(void);
void UpdateEnemy5(void);
void DrawEnemy5(void);
ENEMY5 *GetEnemy5(int no);



#endif
