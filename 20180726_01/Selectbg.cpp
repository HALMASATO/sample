//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Selectbg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSelBG(void);
void SetVertexSelBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_yakei = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_tuki = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_HP = NULL;		// テクスチャへのポインタ




VERTEX_2D				g_vertexWkSelBG_yakei[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkSelBG_tuki[NUM_VERTEX];		// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkSelBG_HP[NUM_VERTEX];		// 頂点情報格納ワーク



D3DXVECTOR2				g_posSelBG;					// 背景の位置

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSelBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAME_SelBG00,					// ファイルの名前
			&g_pD3DTextureSelBG_yakei);			// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_SelBG01_tuki,				// ファイルの名前
		//	&g_pD3DTextureSelBG_tuki);				// 読み込むメモリー

		//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		//	TEXTURE_GAME_SelBG02_heart,			// ファイルの名前
		//	&g_pD3DTextureSelBG_HP);			// 読み込むメモリー


	}

	g_posSelBG = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexSelBG();

	g_posSelBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexSelBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelBG(void)
{
	if(g_pD3DTextureSelBG_yakei != NULL)
	{// テクスチャの開放
		g_pD3DTextureSelBG_yakei->Release();
		g_pD3DTextureSelBG_yakei = NULL;
	}

	//if (g_pD3DTextureSelBG_tuki != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureSelBG_tuki->Release();
	//	g_pD3DTextureSelBG_tuki = NULL;
	//}

	//if (g_pD3DTextureSelBG_HP != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureSelBG_HP->Release();
	//	g_pD3DTextureSelBG_HP = NULL;
	//}



}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelBG(void)
{
	// 毎フレーム実行する処理

	// スクロール処理
	g_posSelBG.x = GetPlayer(0)->pos.x / 250.0f;
	//g_posSelBG.y = -GetPlayer(0)->pos.y / 250.0f;


	SetVertexSelBG();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSelBG(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/*yakei*/
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureSelBG_yakei);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_yakei, sizeof(VERTEX_2D));


	/*tuki*/

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureSelBG_tuki);

	//// ポリゴンの描画
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_tuki, sizeof(VERTEX_2D));


	/*heart*/
//
//// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, g_pD3DTextureSelBG_HP);
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_HP, sizeof(VERTEX_2D));
//




}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSelBG(void)
{

	/*ossan*/

	// 頂点座標の設定
	g_vertexWkSelBG_yakei[0].vtx = D3DXVECTOR3(SelBG00_POS_X, SelBG00_POS_Y, 0.0f);
	g_vertexWkSelBG_yakei[1].vtx = D3DXVECTOR3(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y, 0.0f);
	g_vertexWkSelBG_yakei[2].vtx = D3DXVECTOR3(SelBG00_POS_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f);
	g_vertexWkSelBG_yakei[3].vtx = D3DXVECTOR3(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f);

	// rhwの設定
	g_vertexWkSelBG_yakei[0].rhw =
	g_vertexWkSelBG_yakei[1].rhw =
	g_vertexWkSelBG_yakei[2].rhw =
	g_vertexWkSelBG_yakei[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkSelBG_yakei[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkSelBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	/*tuki*/

	// 頂点座標の設定
	g_vertexWkSelBG_tuki[0].vtx = D3DXVECTOR3(SelBG01_POS_X, SelBG01_POS_Y, 0.0f);
	g_vertexWkSelBG_tuki[1].vtx = D3DXVECTOR3(SelBG01_POS_X + SelBG01_SIZE_X, SelBG01_POS_Y, 0.0f);
	g_vertexWkSelBG_tuki[2].vtx = D3DXVECTOR3(SelBG01_POS_X, SelBG01_POS_Y + SelBG01_SIZE_Y, 0.0f);
	g_vertexWkSelBG_tuki[3].vtx = D3DXVECTOR3(SelBG01_POS_X + SelBG01_SIZE_X, SelBG01_POS_Y + SelBG01_SIZE_Y, 0.0f);
				 
	// rhwの設定 
	g_vertexWkSelBG_tuki[0].rhw =
	g_vertexWkSelBG_tuki[1].rhw =
	g_vertexWkSelBG_tuki[2].rhw =
	g_vertexWkSelBG_tuki[3].rhw = 1.0f;
				 
	// 反射光の設定
	g_vertexWkSelBG_tuki[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				 
	// テクスチャ座標の設定
	g_vertexWkSelBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	///*ossan*/

	//// 頂点座標の設定
	//g_vertexWkSelBG_HP[0].vtx = D3DXVECTOR3(SelBG02_POS_X, SelBG02_POS_Y, 0.0f);
	//g_vertexWkSelBG_HP[1].vtx = D3DXVECTOR3(SelBG02_POS_X + SelBG02_SIZE_X, SelBG02_POS_Y, 0.0f);
	//g_vertexWkSelBG_HP[2].vtx = D3DXVECTOR3(SelBG02_POS_X, SelBG02_POS_Y + SelBG02_SIZE_Y, 0.0f);
	//g_vertexWkSelBG_HP[3].vtx = D3DXVECTOR3(SelBG02_POS_X + SelBG02_SIZE_X, SelBG02_POS_Y + SelBG02_SIZE_Y, 0.0f);

	//// rhwの設定 
	//g_vertexWkSelBG_HP[0].rhw =
	//g_vertexWkSelBG_HP[1].rhw =
	//g_vertexWkSelBG_HP[2].rhw =
	//g_vertexWkSelBG_HP[3].rhw = 1.0f;

	//// 反射光の設定
	//g_vertexWkSelBG_HP[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// テクスチャ座標の設定
	//g_vertexWkSelBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkSelBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkSelBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkSelBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSelBG(void)
{
	//// 頂点座標の設定
	//g_vertexWkSelBG[0].vtx = D3DXVECTOR2(SelBG00_POS_X, SelBG00_POS_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[1].vtx = D3DXVECTOR2(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[2].vtx = D3DXVECTOR2(SelBG00_POS_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[3].vtx = D3DXVECTOR2(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f) + g_posSelBG;

	// テクスチャ座標の設定
	g_vertexWkSelBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f)+g_posSelBG;

	// テクスチャ座標の設定
	g_vertexWkSelBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// テクスチャ座標の設定
	//g_vertexWkSelBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkSelBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkSelBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkSelBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}


//=============================================================================
// エネミー取得関数
//=============================================================================
//SelBG *GetSelBG(int no)
//{
//	return(&SelBGWk[no]);
//}

