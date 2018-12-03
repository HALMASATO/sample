//=============================================================================
//
// 敵処理 [enemy6.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY6_H_
#define _ENEMY6_H_


// マクロ定義
#define	NUM_ENEMY6				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY6		_T("data/TEXTURE/enemy_green.png")	// 画像
#define TEXTURE_ENEMY6_SIZE_X	(40)		// テクスチャサイズ
#define TEXTURE_ENEMY6_SIZE_Y	(40)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY6	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY6	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY6			(TEXTURE_PATTERN_DIVIDE_X_ENEMY6*TEXTURE_PATTERN_DIVIDE_Y_ENEMY6)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY6			(4)	// アニメーションの切り替わるカウント
#define ENEMY6_MAX						(3) // 敵の最大数





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
	//float			InitY;						//初期Y値
	int				i;
	int             pattern;
	int				Bcounter;
	int				Bcounter_ORG;
	int				flag;
	bool			effectflag;

	

	float			enemy6pos_x;
	float			enemy6pos_y;
	//int				ENM = ENEMY6_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_enemy6[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} ENEMY6;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy6(int type);
void UninitEnemy6(void);
void UpdateEnemy6(void);
void DrawEnemy6(void);
ENEMY6 *GetEnemy6(int no);



#endif
