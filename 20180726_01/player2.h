//=============================================================================
//
// プレイヤー処理 [player2.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_


// マクロ定義
#define	NUM_PLAYER2		(2)					// ポリゴン数

#define TEXTURE_GAME_PLAYER2	_T("data/TEXTURE/player2.png")	// 画像
#define TEXTURE_PLAYER2_SIZE_X	(40) // テクスチャサイズ
#define TEXTURE_PLAYER2_SIZE_Y	(40) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_PLAYER2	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYER2	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PLAYER2			(TEXTURE_PATTERN_DIVIDE_X_PLAYER2*TEXTURE_PATTERN_DIVIDE_Y_PLAYER2)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント

#define PLAYER2_MAX					(1) // プレイヤーの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				counter;
	int				HP;
	int				Bcounter;
	int				MAXHP;
	int				MAXcounter;					//
	int				MAXBcounter;
	int				Timecounter;
	int				Hitcounter;
	int				drawcounter;
	bool			drawflug;


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// プレイヤーの半径
	float			BaseAngle;					// プレイヤーの角度

} PLAYER2;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer2(int type);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
PLAYER2 *GetPlayer2(int no);


#endif
