//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _PGAGE_H_
#define _PGAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PGAGE		_T("data/TEXTURE/gezi1.png")			// 読み込むテクスチャファイル名
//#define	TEXTURE_PGAGE_LOGO	_T("data/TEXTURE/start.png")		// 読み込むテクスチャファイル名
#define	PGAGE_POS_X			(30)								// タイトルの表示位置
#define	PGAGE_POS_Y			(30)								// タイトルの表示位置
#define	PGAGE_SIZE_X		(120)							// タイトルの幅
#define	PGAGE_SIZE_Y		(16)							// タイトルの高さ
//#define	PGAGELOGO_POS_X		(160)							// タイトルロゴの表示位置
//#define	PGAGELOGO_POS_Y		(300)							// タイトルロゴの表示位置
//#define	PGAGELOGO_SIZE_X	(380)							// タイトルロゴの幅
//#define	PGAGELOGO_SIZE_Y	(80)							// タイトルロゴの高さ
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
HRESULT InitPgage(void);
void UninitPgage(void);
void UpdatePgage(void);
void DrawPgage(void);
//LOGO*GetPgage(int no);

#endif
