//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _BTGAGE_H_
#define _BTGAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BTGAGE		_T("data/TEXTURE/runa.png")			// 読み込むテクスチャファイル名
#define	BTGAGE_POS_X			(550)								// タイトルの表示位置
#define	BTGAGE_POS_Y			(-60)								// タイトルの表示位置
#define	BTGAGE_SIZE_X		(200)							// タイトルの幅
#define	BTGAGE_SIZE_Y		(200)							// タイトルの高さ
#define BTGAGE_MAX			(1)

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用

} BTGAGE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBTgage(void);
void UninitBTgage(void);
void UpdateBTgage(void);
void DrawBTgage(void);
BTGAGE *GetBTgage(int no);
#endif