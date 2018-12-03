//=============================================================================
//
// 背景処理 [captionbg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "captionbg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCaptionBG(void);
void SetVertexCaptionBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCaptionBG = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureCaptionBG_tuki = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureBG_HP = NULL;		// テクスチャへのポインタ




VERTEX_2D				g_vertexWkCaptionBG[NUM_VERTEX];	// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkBG_tuki[NUM_VERTEX];		// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkBG_HP[NUM_VERTEX];		// 頂点情報格納ワーク



static D3DXVECTOR2				g_posBG;					// 背景の位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCaptionBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAME_CAPTIONBG00,					// ファイルの名前
			&g_pD3DTextureCaptionBG);			// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_BG01_tuki,				// ファイルの名前
		//	&g_pD3DTextureBG_tuki);				// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_BG02_heart,			// ファイルの名前
		//	&g_pD3DTextureBG_HP);			// 読み込むメモリー


	}

	g_posBG = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexCaptionBG();

	//g_posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexCaptionBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCaptionBG(void)
{
	if(g_pD3DTextureCaptionBG != NULL)
	{// テクスチャの開放
		g_pD3DTextureCaptionBG->Release();
		g_pD3DTextureCaptionBG = NULL;
	}

	//if (g_pD3DTextureBG_tuki != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureBG_tuki->Release();
	//	g_pD3DTextureBG_tuki = NULL;
	//}

	//if (g_pD3DTextureBG_HP != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureBG_HP->Release();
	//	g_pD3DTextureBG_HP = NULL;
	//}



}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCaptionBG(void)
{
	// 毎フレーム実行する処理

	// スクロール処理
	//g_posBG.x = GetPlayer(0)->pos.x / 250.0f;
	//g_posBG.y = -GetPlayer(0)->pos.y / 250.0f;


	SetVertexCaptionBG();


	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_GAME);
	}
	// ゲームパッドでで移動処理
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		SetStage(STAGE_GAME);
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_GAME);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCaptionBG(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/*yakei*/
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureCaptionBG);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkCaptionBG, sizeof(VERTEX_2D));


	/*tuki*/

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureBG_tuki);

	//// ポリゴンの描画
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG_tuki, sizeof(VERTEX_2D));


	/*heart*/
//
//// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, g_pD3DTextureBG_HP);
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG_HP, sizeof(VERTEX_2D));
//




}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCaptionBG(void)
{

	/*ossan*/

	// 頂点座標の設定
	g_vertexWkCaptionBG[0].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X, CAPTIONBG00_POS_Y, 0.0f);
	g_vertexWkCaptionBG[1].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X + CAPTIONBG00_SIZE_X, CAPTIONBG00_POS_Y, 0.0f);
	g_vertexWkCaptionBG[2].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X, CAPTIONBG00_POS_Y + CAPTIONBG00_SIZE_Y, 0.0f);
	g_vertexWkCaptionBG[3].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X + CAPTIONBG00_SIZE_X, CAPTIONBG00_POS_Y + CAPTIONBG00_SIZE_Y, 0.0f);

	// rhwの設定
	g_vertexWkCaptionBG[0].rhw =
	g_vertexWkCaptionBG[1].rhw =
	g_vertexWkCaptionBG[2].rhw =
	g_vertexWkCaptionBG[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkCaptionBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	/*tuki*/

	//// 頂点座標の設定
	//g_vertexWkCaptionBG[0].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X, CAPTIONBG01_POS_Y, 0.0f);
	//g_vertexWkCaptionBG[1].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X +CAPTIONBG01_SIZE_X, CAPTIONBG01_POS_Y, 0.0f);
	//g_vertexWkCaptionBG[2].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X, CAPTIONBG01_POS_Y + CAPTIONBG01_SIZE_Y, 0.0f);
	//g_vertexWkCaptionBG[3].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X +CAPTIONBG01_SIZE_X, CAPTIONBG01_POS_Y + CAPTIONBG01_SIZE_Y, 0.0f);
	//			 
	//// rhwの設定 
	//g_vertexWkCaptionBG[0].rhw =
	//g_vertexWkCaptionBG[1].rhw =
	//g_vertexWkCaptionBG[2].rhw =
	//g_vertexWkCaptionBG[3].rhw = 1.0f;
	//			 
	//// 反射光の設定
	//g_vertexWkCaptionBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//			 
	//// テクスチャ座標の設定
	//g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	///*ossan*/

	//// 頂点座標の設定
	//g_vertexWkBG_HP[0].vtx = D3DXVECTOR3(BG02_POS_X, BG02_POS_Y, 0.0f);
	//g_vertexWkBG_HP[1].vtx = D3DXVECTOR3(BG02_POS_X + BG02_SIZE_X, BG02_POS_Y, 0.0f);
	//g_vertexWkBG_HP[2].vtx = D3DXVECTOR3(BG02_POS_X, BG02_POS_Y + BG02_SIZE_Y, 0.0f);
	//g_vertexWkBG_HP[3].vtx = D3DXVECTOR3(BG02_POS_X + BG02_SIZE_X, BG02_POS_Y + BG02_SIZE_Y, 0.0f);

	//// rhwの設定 
	//g_vertexWkBG_HP[0].rhw =
	//g_vertexWkBG_HP[1].rhw =
	//g_vertexWkBG_HP[2].rhw =
	//g_vertexWkBG_HP[3].rhw = 1.0f;

	//// 反射光の設定
	//g_vertexWkBG_HP[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// テクスチャ座標の設定
	//g_vertexWkBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexCaptionBG(void)
{
	//// 頂点座標の設定
	//g_vertexWkBG[0].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[1].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[2].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[3].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;

	// テクスチャ座標の設定
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f)+g_posBG;
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f)+g_posBG;
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f)+g_posBG;
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f)+g_posBG;

	// テクスチャ座標の設定
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// テクスチャ座標の設定
	//g_vertexWkBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}


//=============================================================================
// エネミー取得関数
//=============================================================================
//BG *GetBG(int no)
//{
//	return(&BGWk[no]);
//}

