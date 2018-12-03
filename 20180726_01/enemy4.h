//=============================================================================
//
// 敵処理 [enemy4.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY4_H_
#define _ENEMY4_H_


// マクロ定義
#define	NUM_ENEMY4				(2)			// ポリゴン数

#define TEXTURE_GAME_ENEMY4		_T("data/TEXTURE/tama1.png")	// 画像
#define TEXTURE_ENEMY4_SIZE_X	(25)		// テクスチャサイズ
#define TEXTURE_ENEMY4_SIZE_Y	(25)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY4	(9)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY4	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY4			(TEXTURE_PATTERN_DIVIDE_X_ENEMY4*TEXTURE_PATTERN_DIVIDE_Y_ENEMY4)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY4			(4)	// アニメーションの切り替わるカウント
#define ENEMY4_MAX						(6) // 敵の最大数





//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			nextflag;					//true:死亡　false:生存
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
	bool			effectflag4;

	

	float			enemy4pos_x;
	float			enemy4pos_y;
	//int				ENM = ENEMY4_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_enemy4[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} ENEMY4;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy4(int type);
void UninitEnemy4(void);
void UpdateEnemy4(void);
void DrawEnemy4(void);
ENEMY4 *GetEnemy4(int no);



#endif
