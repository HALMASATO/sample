//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/title1.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/start.png")		// 読み込むテクスチャファイル名
#define	TITLE_POS_X			(0)								// タイトルの表示位置
#define	TITLE_POS_Y			(0)								// タイトルの表示位置
#define	TITLE_SIZE_X		(800)							// タイトルの幅
#define	TITLE_SIZE_Y		(450)							// タイトルの高さ
#define	TITLELOGO_POS_X		(160)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(300)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(380)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(80)							// タイトルロゴの高さ
#define	LOGO_MAX			(1)
////

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	int				logo_counter;

} LOGO;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
LOGO*GetLogo(int no);

#endif
