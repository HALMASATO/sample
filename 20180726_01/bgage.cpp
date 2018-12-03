//=============================================================================
//
// タイトル画面処理 [Bgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Bgage.h"
#include "bullet.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBgage(void);
void SetTextureBgage(void);
void SetVertexBgage(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBgage = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureBgageLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkBgage[NUM_VERTEX];			// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkBgageLogo[NUM_VERTEX];		// 頂点情報格納ワーク


BGAGE					bgageWk[BGAGE_MAX];			// プレイヤー構造体

//LOGO					logoWk[LOGO_MAX];				// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BGAGE *bgage = &bgageWk[0];


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BGAGE,				// ファイルの名前
								&g_pD3DTextureBgage);		// 読み込むメモリー

	for (int i = 0; i < BGAGE_MAX; i++, bgage++)
	{
		bgage->use = false;
	}

	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//							TEXTURE_BGAGE_LOGO,			// ファイルの名前
	//							&g_pD3DTextureBgageLogo);	// 読み込むメモリー
	//logo->use = false;

	// 頂点情報の作成
	MakeVertexBgage();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBgage(void)
{
	if(g_pD3DTextureBgage != NULL)
	{// テクスチャの開放
		g_pD3DTextureBgage->Release();
		g_pD3DTextureBgage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBgage(void)
{

	SetTextureBgage();
	SetVertexBgage();



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BGAGE *bgage = &bgageWk[0];

	if (bgage->use == false)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBgage);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBgage, sizeof(VERTEX_2D));
	}

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBgage(void)
{
	
	// 頂点座標の設定
	g_vertexWkBgage[0].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[1].vtx = D3DXVECTOR3(BGAGE_POS_X + BGAGE_SIZE_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[2].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);
	g_vertexWkBgage[3].vtx = D3DXVECTOR3(BGAGE_POS_X + BGAGE_SIZE_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkBgage[0].rhw =
	g_vertexWkBgage[1].rhw =
	g_vertexWkBgage[2].rhw =
	g_vertexWkBgage[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkBgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBgage(void)
{
	BULLET *bullet = GetBullet(0);


	// テクスチャ座標の設定
	g_vertexWkBgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBgage[1].tex = D3DXVECTOR2((float)bullet->reload/bullet->MAXreload, 0.0f);
	g_vertexWkBgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBgage[3].tex = D3DXVECTOR2((float)bullet->reload / bullet->MAXreload, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBgage(void)
{
	BULLET *bullet = GetBullet(0);


	// 頂点座標の設定
	g_vertexWkBgage[0].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[1].vtx = D3DXVECTOR3(BGAGE_POS_X + (float)bullet->counter, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[2].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);
	g_vertexWkBgage[3].vtx = D3DXVECTOR3(BGAGE_POS_X + (float)bullet->counter, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);


}


//=============================================================================
// エネミー取得関数
//=============================================================================
//LOGO *GetLogo(int no)
//{
//
//
//	return(&logoWk[no]);
//
//
//
//}
