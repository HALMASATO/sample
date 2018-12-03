//=============================================================================
//
// 敵処理 [bosseffect.h]
// Author : 
//
//=============================================================================
#ifndef _BOSSEFFECT_H_
#define _BOSSEFFECT_H_


// マクロ定義
#define	NUM_BOSSEFFECT				(2)			// ポリゴン数

#define TEXTURE_GAME_BOSSEFFECT		_T("data/TEXTURE/bomb2.png")	// 画像
#define TEXTURE_BOSSEFFECT_SIZE_X	(100)		// テクスチャサイズ
#define TEXTURE_BOSSEFFECT_SIZE_Y	(100)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSSEFFECT			(TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT*TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT)	// アニメーションパターン数
#define TIME_ANIMATION_BOSSEFFECT			(4)	// アニメーションの切り替わるカウント
#define BOSSEFFECT_MAX						(1) // 敵の最大数





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
	int				bosseffectcounter;				//エフェクト管理
	


	float			bosseffectpos_x;
	float			bosseffectpos_y;
	//int				ENM = BOSSEFFECT_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk_bosseffect[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} BOSSEFFECT;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBossEffect(int type);
void UninitBossEffect(void);
void UpdateBossEffect(void);
void DrawBossEffect(void);
BOSSEFFECT *GetBossEffect(int no);
void SetBossEffect(D3DXVECTOR3 pos, int i);



#endif
