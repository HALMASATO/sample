//=============================================================================
//
// タイトル画面処理 [egage.h]
// Author : 
//
//=============================================================================
#ifndef _EGAGE_H_
#define _EGAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EGAGE		_T("data/TEXTURE/gazi2.png")			// 読み込むテクスチャファイル名
//#define	TEXTURE_EGAGE_LOGO	_T("data/TEXTURE/start.png")		// 読み込むテクスチャファイル名
#define	EGAGE_POS_X			(430)								// タイトルの表示位置
#define	EGAGE_POS_Y			(30)								// タイトルの表示位置
#define	EGAGE_SIZE_X		(120)							// タイトルの幅
#define	EGAGE_SIZE_Y		(16)							// タイトルの高さ
//#define	EGAGELOGO_POS_X		(160)							// タイトルロゴの表示位置
//#define	EGAGELOGO_POS_Y		(300)							// タイトルロゴの表示位置
//#define	EGAGELOGO_SIZE_X	(380)							// タイトルロゴの幅
//#define	EGAGELOGO_SIZE_Y	(80)							// タイトルロゴの高さ
//#define	LOGO_MAX			(1)
//

//typedef struct	// エネミー構造体
//{
//	bool			use;						// true:使用  false:未使用
//	int				logo_counter;
//
//} LOGO;
//

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEgage(void);
void UninitEgage(void);
void UpdateEgage(void);
void DrawEgage(void);
//LOGO*GetEgage(int no);

#endif
