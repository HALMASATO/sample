//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// マクロ定義
#define	NUM_PLAYER		(2)					// ポリゴン数

#define TEXTURE_GAME_PLAYER	_T("data/TEXTURE/player1.png")	// 画像
#define TEXTURE_PLAYER_SIZE_X	(35) // テクスチャサイズ
#define TEXTURE_PLAYER_SIZE_Y	(35) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_PLAYER	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYER	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PLAYER			(TEXTURE_PATTERN_DIVIDE_X_PLAYER*TEXTURE_PATTERN_DIVIDE_Y_PLAYER)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント
#define PLAYER_SPEED				(3.0f)//プレイヤーのスピード

#define PLAYER_MAX					(1) // プレイヤーの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			Xmuki;
	bool			Ymuki;
	bool			yoko;
	bool			tate;
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				counter;
	int				i;
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

} PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);


#endif
