//=============================================================================
//
// リザルト画面処理 [result3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "result3.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult3(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult3 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResult3Logo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkResult3[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkResult3Logo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_RESULT3,				// ファイルの名前
								&g_pD3DTextureResult3);		// 読み込むメモリー

	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//							TEXTURE_RESULT3_LOGO,		// ファイルの名前
	//							&g_pD3DTextureResult3Logo);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexResult3();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult3(void)
{
	if(g_pD3DTextureResult3 != NULL)
	{// テクスチャの開放
		g_pD3DTextureResult3->Release();
		g_pD3DTextureResult3 = NULL;
	}

	if(g_pD3DTextureResult3Logo != NULL)
	{// テクスチャの開放
		g_pD3DTextureResult3Logo->Release();
		g_pD3DTextureResult3Logo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult3(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResult3);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult3, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureResult3Logo);

	//// ポリゴンの描画
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult3Logo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResult3(void)
{	
	// 頂点座標の設定
	g_vertexWkResult3[0].vtx = D3DXVECTOR3(RESULT3_POS_X, RESULT3_POS_Y, 0.0f);
	g_vertexWkResult3[1].vtx = D3DXVECTOR3(RESULT3_POS_X + RESULT3_SIZE_X, RESULT3_POS_Y, 0.0f);
	g_vertexWkResult3[2].vtx = D3DXVECTOR3(RESULT3_POS_X, RESULT3_POS_Y + RESULT3_SIZE_Y, 0.0f);
	g_vertexWkResult3[3].vtx = D3DXVECTOR3(RESULT3_POS_X + RESULT3_SIZE_X, RESULT3_POS_Y + RESULT3_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkResult3[0].rhw =
	g_vertexWkResult3[1].rhw =
	g_vertexWkResult3[2].rhw =
	g_vertexWkResult3[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkResult3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkResult3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult3[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult3[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult3[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkResult3Logo[0].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X, RESULT3LOGO_POS_Y, 0.0f);
	g_vertexWkResult3Logo[1].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X + RESULT3LOGO_SIZE_X, RESULT3LOGO_POS_Y, 0.0f);
	g_vertexWkResult3Logo[2].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X, RESULT3LOGO_POS_Y + RESULT3LOGO_SIZE_Y, 0.0f);
	g_vertexWkResult3Logo[3].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X + RESULT3LOGO_SIZE_X, RESULT3LOGO_POS_Y + RESULT3LOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkResult3Logo[0].rhw =
	g_vertexWkResult3Logo[1].rhw =
	g_vertexWkResult3Logo[2].rhw =
	g_vertexWkResult3Logo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkResult3Logo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkResult3Logo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult3Logo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult3Logo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult3Logo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

