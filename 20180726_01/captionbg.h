//=============================================================================
//
// 背景処理 [captionbg.h]
// Author : 
//
//=============================================================================
#ifndef _CAPTIONBG_H_
#define _CAPTIONBG_H_

// マクロ定義
#define TEXTURE_GAME_CAPTIONBG00		_T("data/TEXTURE/ps4kon_ver1.jpg")	// サンプル用画像
//#define TEXTURE_GAME_CAPTIONBG01_tuki		_T("data/TEXTURE/tuki.png")	// サンプル用画像
//#define TEXTURE_GAME_CAPTIONBG02_heart		_T("data/TEXTURE/heart.png")	// サンプル用画像

#define CAPTIONBG00_SIZE_X			(800)							// テクスチャサイズ
#define CAPTIONBG00_SIZE_Y			(450)							// 同上
#define CAPTIONBG00_POS_X			(0)								// ポリゴンの初期位置X(左上)
#define CAPTIONBG00_POS_Y			(0)								// 同上

//#define	CAPTIONBG01_POS_X			(400)							// タイトルロゴの表示位置
//#define	CAPTIONBG01_POS_Y			(-50)							// タイトルロゴの表示位置
//#define	CAPTIONBG01_SIZE_X			(350)							// タイトルロゴの幅
//#define	CAPTIONBG01_SIZE_Y			(310)							// タイトルロゴの高さ
//
//#define	CAPTIONBG02_POS_X			(30)							// タイトルロゴの表示位置
//#define	CAPTIONBG02_POS_Y			(430)							// タイトルロゴの表示位置
//#define	CAPTIONBG02_SIZE_X			(50)							// タイトルロゴの幅
//#define	CAPTIONBG02_SIZE_Y			(50)							// タイトルロゴの高さ
//

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCaptionBG(int type);
void UninitCaptionBG(void);
void UpdateCaptionBG(void);
void DrawCaptionBG(void);
//CAPTIONBG *GetCAPTIONBG(int no);

#endif
