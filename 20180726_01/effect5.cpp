//=============================================================================
//
// 敵処理 [effect5.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect5.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy4.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect5( int no);
void SetTextureEffect5( int no,int cntPattern );
void SetVertexEffect5( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect5 = NULL;		// テクスチャへのポリゴン


EFFECT5					effect5Wk[EFFECT5_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect5(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = effect5Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT5,				// ファイルの名前
			&g_pD3DTextureEffect5);			// 読み込むメモリのポインタ


	}



	 //エネミーの初期化処理
	for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
	{
		effect5->use = false;										// 使用
		effect5->pos = D3DXVECTOR3(i*50+effect5->InitY,50.0f, 0.0f);		// 座標データを初期化
		effect5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		effect5->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		effect5->CountAnim = 0;									// アニメカウントを初期化
		effect5->effectcounter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT5_SIZE_X, TEXTURE_EFFECT5_SIZE_Y);
		effect5->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		effect5->BaseAngle = atan2f(TEXTURE_EFFECT5_SIZE_Y, TEXTURE_EFFECT5_SIZE_X);	// エネミーの角度を初期化

		effect5->Texture = g_pD3DTextureEffect5;					// テクスチャ情報
		MakeVertexEffect5(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect5(void)
{
	if (g_pD3DTextureEffect5 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect5->Release();
		g_pD3DTextureEffect5 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect5(void)
{
	EFFECT5 *effect5 = effect5Wk;				// エネミーのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect5->use == true)			// 使用している状態なら更新する
			{

				//アニメーション
				effect5->CountAnim++;
				if ((effect5->CountAnim % TIME_ANIMATION_EFFECT5) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT5 -1> effect5->PatternAnim)
					{
						// パターンの切り替え
						effect5->PatternAnim = (effect5->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT5;


					}
					else
					{
						effect5->use = false;
						effect5->PatternAnim = 0;
						GetEnemy4(effect5->i)->effectflag4 = false;
					}

					
					// テクスチャ座標を設定
					SetTextureEffect5(0, effect5->PatternAnim);


					SetVertexEffect5(0);	// 移動後の座標で頂点を設定


				}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = effect5Wk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
		//{
			if (effect5->use == true)			// 使用している状態なら描画する
			{
				//if (effect5->counter > 0)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, effect5->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT5, effect5->vertexWk_effect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect5( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = &effect5Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEffect5( no );

	// rhwの設定
	effect5->vertexWk_effect[0].rhw =
	effect5->vertexWk_effect[1].rhw =
	effect5->vertexWk_effect[2].rhw =
	effect5->vertexWk_effect[3].rhw = 1.0f;

	// 反射光の設定
	effect5->vertexWk_effect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect5->vertexWk_effect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect5->vertexWk_effect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT5, 0.0f);
	effect5->vertexWk_effect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT5);
	effect5->vertexWk_effect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT5, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT5);






	//effect5->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect5->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect5->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect5->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect5( int no,int cntPattern )
{
	EFFECT5 *effect5 = &effect5Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT5;
	
	effect5->vertexWk_effect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect5->vertexWk_effect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect5->vertexWk_effect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect5->vertexWk_effect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect5( int no )
{
	EFFECT5 *effect5 = &effect5Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	effect5->vertexWk_effect[0].vtx.x = effect5->pos.x - cosf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[0].vtx.y = effect5->pos.y - sinf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[0].vtx.z = 0.0f;

	effect5->vertexWk_effect[1].vtx.x = effect5->pos.x + cosf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[1].vtx.y = effect5->pos.y - sinf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[1].vtx.z = 0.0f;

	effect5->vertexWk_effect[2].vtx.x = effect5->pos.x - cosf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[2].vtx.y = effect5->pos.y + sinf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[2].vtx.z = 0.0f;

	effect5->vertexWk_effect[3].vtx.x = effect5->pos.x + cosf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[3].vtx.y = effect5->pos.y + sinf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetEffect5(D3DXVECTOR3 pos, int i)
{
	EFFECT5 *effect5 = &effect5Wk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
	//{
		if (effect5->use == false)			// 未使用状態のバレットを見つける
		{
			effect5->use = true;				// 使用状態へ変更する
			effect5->pos = pos;				// 座標をセット
			effect5->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}




//=============================================================================
// エネミー取得関数
//=============================================================================
EFFECT5 *GetEffect5(int no)
{

	
	return(&effect5Wk[no]);



}


