//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetVertexBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBG_yakei = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureBG_tuki = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureBG_HP = NULL;		// テクスチャへのポインタ




VERTEX_2D				g_vertexWkBG_yakei[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkBG_tuki[NUM_VERTEX];		// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkBG_HP[NUM_VERTEX];		// 頂点情報格納ワーク



D3DXVECTOR2				g_posBG;					// 背景の位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAME_BG00,					// ファイルの名前
			&g_pD3DTextureBG_yakei);			// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_BG01_tuki,				// ファイルの名前
		//	&g_pD3DTextureBG_tuki);				// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_BG02_heart,			// ファイルの名前
		//	&g_pD3DTextureBG_HP);			// 読み込むメモリー


	}

	g_posBG = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexBG();

	g_posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	if(g_pD3DTextureBG_yakei != NULL)
	{// テクスチャの開放
		g_pD3DTextureBG_yakei->Release();
		g_pD3DTextureBG_yakei = NULL;
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
void UpdateBG(void)
{
	// 毎フレーム実行する処理

	// スクロール処理
	g_posBG.x = GetPlayer(0)->pos.x / 250.0f;
	//g_posBG.y = -GetPlayer(0)->pos.y / 250.0f;


	SetVertexBG();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/*yakei*/
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureBG_yakei);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG_yakei, sizeof(VERTEX_2D));


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
HRESULT MakeVertexBG(void)
{

	/*ossan*/

	// 頂点座標の設定
	g_vertexWkBG_yakei[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	g_vertexWkBG_yakei[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	g_vertexWkBG_yakei[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	g_vertexWkBG_yakei[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhwの設定
	g_vertexWkBG_yakei[0].rhw =
	g_vertexWkBG_yakei[1].rhw =
	g_vertexWkBG_yakei[2].rhw =
	g_vertexWkBG_yakei[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBG_yakei[0].diffuse = D3DCOLOR_RGBA(250, 100, 100, 100);
	g_vertexWkBG_yakei[1].diffuse = D3DCOLOR_RGBA(250, 100, 100, 100);
	g_vertexWkBG_yakei[2].diffuse = D3DCOLOR_RGBA(250, 100, 100, 100);
	g_vertexWkBG_yakei[3].diffuse = D3DCOLOR_RGBA(250, 100, 100, 100);

	// テクスチャ座標の設定
	g_vertexWkBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	/*tuki*/

	// 頂点座標の設定
	g_vertexWkBG_tuki[0].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y, 0.0f);
	g_vertexWkBG_tuki[1].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y, 0.0f);
	g_vertexWkBG_tuki[2].vtx = D3DXVECTOR3(BG01_POS_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);
	g_vertexWkBG_tuki[3].vtx = D3DXVECTOR3(BG01_POS_X + BG01_SIZE_X, BG01_POS_Y + BG01_SIZE_Y, 0.0f);
				 
	// rhwの設定 
	g_vertexWkBG_tuki[0].rhw =
	g_vertexWkBG_tuki[1].rhw =
	g_vertexWkBG_tuki[2].rhw =
	g_vertexWkBG_tuki[3].rhw = 1.0f;
				 
	// 反射光の設定
	g_vertexWkBG_tuki[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG_tuki[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG_tuki[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG_tuki[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				 
	// テクスチャ座標の設定
	g_vertexWkBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);


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
void SetVertexBG(void)
{
	//// 頂点座標の設定
	//g_vertexWkBG[0].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[1].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[2].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[3].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;

	// テクスチャ座標の設定
	g_vertexWkBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f)+g_posBG;
	g_vertexWkBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f)+g_posBG;
	g_vertexWkBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f)+g_posBG;
	g_vertexWkBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f)+g_posBG;

	// テクスチャ座標の設定
	g_vertexWkBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

