//=============================================================================
//
// 背景処理 [bg.h]
// Author : 
//
//=============================================================================
#ifndef _SelBG_H_
#define _SelBG_H_

// マクロ定義
#define TEXTURE_GAME_SelBG00		_T("data/TEXTURE/yakei2.png")	// サンプル用画像
//#define TEXTURE_GAME_SelBG01_tuki		_T("data/TEXTURE/tuki.png")	// サンプル用画像
//#define TEXTURE_GAME_SelBG02_heart		_T("data/TEXTURE/heart.png")	// サンプル用画像

#define SelBG00_SIZE_X			(1000)							// テクスチャサイズ
#define SelBG00_SIZE_Y			(500)							// 同上
#define SelBG00_POS_X			(0)								// ポリゴンの初期位置X(左上)
#define SelBG00_POS_Y			(0)								// 同上

#define	SelBG01_POS_X			(400)							// タイトルロゴの表示位置
#define	SelBG01_POS_Y			(-50)							// タイトルロゴの表示位置
#define	SelBG01_SIZE_X			(350)							// タイトルロゴの幅
#define	SelBG01_SIZE_Y			(310)							// タイトルロゴの高さ

//#define	SelBG02_POS_X			(30)							// タイトルロゴの表示位置
//#define	SelBG02_POS_Y			(430)							// タイトルロゴの表示位置
//#define	SelBG02_SIZE_X			(50)							// タイトルロゴの幅
//#define	SelBG02_SIZE_Y			(50)							// タイトルロゴの高さ
//

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSelBG(int type);
void UninitSelBG(void);
void UpdateSelBG(void);
void DrawSelBG(void);
//SelBG *GetSelBG(int no);

#endif
