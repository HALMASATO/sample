//=============================================================================
//
// タイトル画面処理 [eage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "egage.h"
#include "input.h"
#include "boss.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEgage(void);
void SetTextureEgage(void);
void SetVertexEgage(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEgage = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkEgage[NUM_VERTEX];			// 頂点情報格納ワーク



//LOGO					logoWk[LOGO_MAX];				// エネミー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_EGAGE,				// ファイルの名前
								&g_pD3DTextureEgage);		// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexEgage();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEgage(void)
{
	if(g_pD3DTextureEgage != NULL)
	{// テクスチャの開放
		g_pD3DTextureEgage->Release();
		g_pD3DTextureEgage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEgage(void)
{

	SetTextureEgage();
	SetVertexEgage();



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = GetBoss(0);

	if (boss->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEgage);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkEgage, sizeof(VERTEX_2D));
	}

}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEgage(void)
{
	
	// 頂点座標の設定
	g_vertexWkEgage[0].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[1].vtx = D3DXVECTOR3(EGAGE_POS_X + EGAGE_SIZE_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[2].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);
	g_vertexWkEgage[3].vtx = D3DXVECTOR3(EGAGE_POS_X + EGAGE_SIZE_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkEgage[0].rhw =
	g_vertexWkEgage[1].rhw =
	g_vertexWkEgage[2].rhw =
	g_vertexWkEgage[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkEgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkEgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkEgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkEgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkEgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEgage(void)
{
	BOSS *boss = GetBoss(0);


	// テクスチャ座標の設定
	g_vertexWkEgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkEgage[1].tex = D3DXVECTOR2((float)boss->HP/boss->MAXHP, 0.0f);
	g_vertexWkEgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkEgage[3].tex = D3DXVECTOR2((float)boss->HP / boss->MAXHP, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEgage(void)
{
	BOSS *boss = GetBoss(0);


	// 頂点座標の設定
	g_vertexWkEgage[0].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[1].vtx = D3DXVECTOR3(EGAGE_POS_X + (float)boss->HP, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[2].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);
	g_vertexWkEgage[3].vtx = D3DXVECTOR3(EGAGE_POS_X + (float)boss->HP, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);


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
