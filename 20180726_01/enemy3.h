//=============================================================================
//
// 敵処理 [enemy3.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY3_H_
#define _ENEMY3_H_


// マクロ定義
#define	NUM_ENEMY3				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY3		_T("data/TEXTURE/tama1.png")	// 画像
#define TEXTURE_ENEMY3_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_ENEMY3_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY3	(9)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY3	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY3			(TEXTURE_PATTERN_DIVIDE_X_ENEMY3*TEXTURE_PATTERN_DIVIDE_Y_ENEMY3)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY3			(4)	// アニメーションの切り替わるカウント
#define ENEMY3_MAX						(6) // 敵の最大数





//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			deadflag;					//true:死亡　false:生存
	bool			BBflag;
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			InitY=500.0f;				//初期Y値
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	bool			effectflag3;

	

	float			enemy3pos_x;
	float			enemy3pos_y;
	//int				ENM = ENEMY3_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_enemy3[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} ENEMY3;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy3(int type);
void UninitEnemy3(void);
void UpdateEnemy3(void);
void DrawEnemy3(void);
ENEMY3 *GetEnemy3(int no);



#endif
