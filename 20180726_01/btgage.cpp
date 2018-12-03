//=============================================================================
//
// タイトル画面処理 [BTgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "BTgage.h"
#include "player.h"
#include"boss.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBTgage(void);
void SetTextureBTgage(void);
void SetVertexBTgage(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBTgage = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureBTgageLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkBTgage[NUM_VERTEX];			// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkBTgageLogo[NUM_VERTEX];		// 頂点情報格納ワーク

BTGAGE					btgageWk[BTGAGE_MAX];			// プレイヤー構造体


//LOGO					logoWk[LOGO_MAX];				// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BTGAGE *btgage = &btgageWk[0];

	for (int i = 0; i < BTGAGE_MAX; i++, btgage++)
	{
		btgage->use = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BTGAGE,				// ファイルの名前
								&g_pD3DTextureBTgage);		// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexBTgage();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBTgage(void)
{
	if(g_pD3DTextureBTgage != NULL)
	{// テクスチャの開放
		g_pD3DTextureBTgage->Release();
		g_pD3DTextureBTgage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBTgage(void)
{
	BOSS*boss = GetBoss(0);
	BTGAGE *btgage = &btgageWk[0];
	PLAYER*player = GetPlayer(0);

	if (boss->use == true)
	{

		btgage->use = true;

	}

	if (btgage->use == true)
	{
		SetTextureBTgage();
		SetVertexBTgage();
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBTgage(void)
{
	BOSS*boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BTGAGE *btgage = &btgageWk[0];

	if (boss->use == true)
	{

		btgage->use = true;
		

	}


	if (btgage->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBTgage);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBTgage, sizeof(VERTEX_2D));
	}
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBTgage(void)
{
	
	// 頂点座標の設定
	g_vertexWkBTgage[0].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y, 0.0f);
	g_vertexWkBTgage[1].vtx = D3DXVECTOR3(BTGAGE_POS_X + BTGAGE_SIZE_X, BTGAGE_POS_Y, 0.0f);
	g_vertexWkBTgage[2].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
	g_vertexWkBTgage[3].vtx = D3DXVECTOR3(BTGAGE_POS_X + BTGAGE_SIZE_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkBTgage[0].rhw =
	g_vertexWkBTgage[1].rhw =
	g_vertexWkBTgage[2].rhw =
	g_vertexWkBTgage[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBTgage[0].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[1].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[2].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[3].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);

	// テクスチャ座標の設定
	g_vertexWkBTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBTgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBTgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBTgage(void)
{
	PLAYER *player = GetPlayer(0);
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{
		// テクスチャ座標の設定
		g_vertexWkBTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkBTgage[1].tex = D3DXVECTOR2((float)player->Bcounter / player->MAXBcounter, 0.0f);
		g_vertexWkBTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkBTgage[3].tex = D3DXVECTOR2((float)player->Bcounter / player->MAXBcounter, 1.0f);
	}

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBTgage(void)
{
	PLAYER *player = GetPlayer(0);
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{

		// 頂点座標の設定
		g_vertexWkBTgage[0].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y, 0.0f);
		g_vertexWkBTgage[1].vtx = D3DXVECTOR3(BTGAGE_POS_X + (float)player->Bcounter, BTGAGE_POS_Y, 0.0f);
		g_vertexWkBTgage[2].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
		g_vertexWkBTgage[3].vtx = D3DXVECTOR3(BTGAGE_POS_X + (float)player->Bcounter, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
	}

}
//=============================================================================
// エネミー取得関数
//=============================================================================
BTGAGE *GetBTgage(int no)
{
	return(&btgageWk[no]);
}