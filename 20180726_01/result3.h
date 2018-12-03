//=============================================================================
//
//// リザルト画面処理 [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT3_H_
#define _RESULT3_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULT3		_T("data/TEXTURE/over.png")			// 読み込むテクスチャファイル名
//#define	TEXTURE_RESULT3_LOGO	_T("data/TEXTURE/result_logo.png")		// 読み込むテクスチャファイル名
#define	RESULT3_POS_X			(0)							// タイトルの表示位置
#define	RESULT3_POS_Y			(0)							// タイトルの表示位置
#define	RESULT3_SIZE_X			(800)						// タイトルの幅
#define	RESULT3_SIZE_Y			(450)						// タイトルの高さ
#define	RESULT3LOGO_POS_X		(160)						// タイトルロゴの表示位置
#define	RESULT3LOGO_POS_Y		(200)						// タイトルロゴの表示位置
#define	RESULT3LOGO_SIZE_X		(480)						// タイトルロゴの幅
#define	RESULT3LOGO_SIZE_Y		(80)						// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult3(void);
void UninitResult3(void);
void UpdateResult3(void);
void DrawResult3(void);

#endif
