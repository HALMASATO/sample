//=============================================================================
//
// タイトル画面処理 [pgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "pgage.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPgage(void);
void SetTexturePgage(void);
void SetVertexPgage(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePgage = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTexturePgageLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkPgage[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkPgageLogo[NUM_VERTEX];		// 頂点情報格納ワーク



//LOGO					logoWk[LOGO_MAX];				// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PGAGE,				// ファイルの名前
								&g_pD3DTexturePgage);		// 読み込むメモリー

	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//							TEXTURE_PGAGE_LOGO,			// ファイルの名前
	//							&g_pD3DTexturePgageLogo);	// 読み込むメモリー
	//logo->use = false;

	// 頂点情報の作成
	MakeVertexPgage();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPgage(void)
{
	if(g_pD3DTexturePgage != NULL)
	{// テクスチャの開放
		g_pD3DTexturePgage->Release();
		g_pD3DTexturePgage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePgage(void)
{

	SetTexturePgage();
	SetVertexPgage();



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexturePgage);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkPgage, sizeof(VERTEX_2D));

}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPgage(void)
{
	
	// 頂点座標の設定
	g_vertexWkPgage[0].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[1].vtx = D3DXVECTOR3(PGAGE_POS_X + PGAGE_SIZE_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[2].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);
	g_vertexWkPgage[3].vtx = D3DXVECTOR3(PGAGE_POS_X + PGAGE_SIZE_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkPgage[0].rhw =
	g_vertexWkPgage[1].rhw =
	g_vertexWkPgage[2].rhw =
	g_vertexWkPgage[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkPgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkPgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkPgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePgage(void)
{
	PLAYER *player = GetPlayer(0);


	// テクスチャ座標の設定
	g_vertexWkPgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPgage[1].tex = D3DXVECTOR2((float)player->HP/player->MAXHP, 0.0f);
	g_vertexWkPgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPgage[3].tex = D3DXVECTOR2((float)player->HP / player->MAXHP, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPgage(void)
{
	PLAYER *player = GetPlayer(0);


	// 頂点座標の設定
	g_vertexWkPgage[0].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[1].vtx = D3DXVECTOR3(PGAGE_POS_X + (float)player->HP, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[2].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);
	g_vertexWkPgage[3].vtx = D3DXVECTOR3(PGAGE_POS_X + (float)player->HP, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);


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
