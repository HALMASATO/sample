//=============================================================================
//
// タイトル画面処理 [Tgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Tgage.h"
#include "boss.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTgage(void);
void SetTextureTgage(void);
void SetVertexTgage(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTgage = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureTgageLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTgage[NUM_VERTEX];			// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkTgageLogo[NUM_VERTEX];		// 頂点情報格納ワーク

TGAGE					tgageWk[TGAGE_MAX];			// プレイヤー構造体


//LOGO					logoWk[LOGO_MAX];				// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TGAGE *tgage = &tgageWk[0];

	for (int i = 0; i < TGAGE_MAX; i++, tgage++)
	{
		tgage->use = true;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TGAGE,				// ファイルの名前
								&g_pD3DTextureTgage);		// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexTgage();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTgage(void)
{
	if(g_pD3DTextureTgage != NULL)
	{// テクスチャの開放
		g_pD3DTextureTgage->Release();
		g_pD3DTextureTgage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTgage(void)
{
	TGAGE *tgage = &tgageWk[0];
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{
		tgage->use = false;

	}

	if (tgage->use == true)
	{
		SetTextureTgage();
		SetVertexTgage();
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TGAGE *tgage = &tgageWk[0];

	if (tgage->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureTgage);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTgage, sizeof(VERTEX_2D));
	}
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTgage(void)
{
	
	// 頂点座標の設定
	g_vertexWkTgage[0].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[1].vtx = D3DXVECTOR3(TGAGE_POS_X + TGAGE_SIZE_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[2].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
	g_vertexWkTgage[3].vtx = D3DXVECTOR3(TGAGE_POS_X + TGAGE_SIZE_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTgage[0].rhw =
	g_vertexWkTgage[1].rhw =
	g_vertexWkTgage[2].rhw =
	g_vertexWkTgage[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTgage(void)
{
	PLAYER *player = GetPlayer(0);


	// テクスチャ座標の設定
	g_vertexWkTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTgage[1].tex = D3DXVECTOR2((float)player->counter/player->MAXcounter, 0.0f);
	g_vertexWkTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTgage[3].tex = D3DXVECTOR2((float)player->counter / player->MAXcounter, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTgage(void)
{
	PLAYER *player = GetPlayer(0);

	// 頂点座標の設定
	g_vertexWkTgage[0].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[1].vtx = D3DXVECTOR3(TGAGE_POS_X + (float)player->counter, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[2].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
	g_vertexWkTgage[3].vtx = D3DXVECTOR3(TGAGE_POS_X + (float)player->counter, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
}
//=============================================================================
// エネミー取得関数
//=============================================================================
TGAGE *GetTgage(int no)
{
	return(&tgageWk[no]);
}