//=============================================================================
//
// 背景処理 [bg.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// マクロ定義
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/yakei2.png")	// サンプル用画像
//#define TEXTURE_GAME_BG01_tuki		_T("data/TEXTURE/tuki.png")	// サンプル用画像
//#define TEXTURE_GAME_BG02_heart		_T("data/TEXTURE/heart.png")	// サンプル用画像

#define BG00_SIZE_X			(1000)							// テクスチャサイズ
#define BG00_SIZE_Y			(500)							// 同上
#define BG00_POS_X			(0)								// ポリゴンの初期位置X(左上)
#define BG00_POS_Y			(0)								// 同上

#define	BG01_POS_X			(400)							// タイトルロゴの表示位置
#define	BG01_POS_Y			(-50)							// タイトルロゴの表示位置
#define	BG01_SIZE_X			(350)							// タイトルロゴの幅
#define	BG01_SIZE_Y			(310)							// タイトルロゴの高さ

//#define	BG02_POS_X			(30)							// タイトルロゴの表示位置
//#define	BG02_POS_Y			(430)							// タイトルロゴの表示位置
//#define	BG02_SIZE_X			(50)							// タイトルロゴの幅
//#define	BG02_SIZE_Y			(50)							// タイトルロゴの高さ
//

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
//BG *GetBG(int no);

#endif
