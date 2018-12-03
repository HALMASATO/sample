//=============================================================================
//
// 敵処理 [effect4.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect4.h"
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
HRESULT MakeVertexEffect4( int no);
void SetTextureEffect4( int no,int cntPattern );
void SetVertexEffect4( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect4 = NULL;		// テクスチャへのポリゴン


EFFECT4					effect4Wk[EFFECT4_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect4(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = effect4Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT4,				// ファイルの名前
			&g_pD3DTextureEffect4);			// 読み込むメモリのポインタ


	}



	 //エネミーの初期化処理
	for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
	{
		effect4->use = false;										// 使用
		effect4->pos = D3DXVECTOR3(i*50+effect4->InitY,50.0f, 0.0f);		// 座標データを初期化
		effect4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		effect4->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		effect4->CountAnim = 0;									// アニメカウントを初期化
		effect4->effect4counter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT4_SIZE_X, TEXTURE_EFFECT4_SIZE_Y);
		effect4->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		effect4->BaseAngle = atan2f(TEXTURE_EFFECT4_SIZE_Y, TEXTURE_EFFECT4_SIZE_X);	// エネミーの角度を初期化

		effect4->Texture = g_pD3DTextureEffect4;					// テクスチャ情報
		MakeVertexEffect4(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect4(void)
{
	if (g_pD3DTextureEffect4 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect4->Release();
		g_pD3DTextureEffect4 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect4(void)
{
	EFFECT4 *effect4 = effect4Wk;				// エネミーのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect4->use == true)			// 使用している状態なら更新する
			{

				//アニメーション
				effect4->CountAnim++;
				if ((effect4->CountAnim % TIME_ANIMATION_EFFECT4) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT4 -1> effect4->PatternAnim)
					{
						// パターンの切り替え
						effect4->PatternAnim = (effect4->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT4;


					}
					else
					{
						effect4->use = false;
						effect4->PatternAnim = 0;
						GetEnemy4(effect4->i)->effectflag4 = false;
					}

					
					// テクスチャ座標を設定
					SetTextureEffect4(0, effect4->PatternAnim);


					SetVertexEffect4(0);	// 移動後の座標で頂点を設定


				}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = effect4Wk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
		//{
			if (effect4->use == true)			// 使用している状態なら描画する
			{
				//if (effect4->counter > 0)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, effect4->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT4, effect4->vertexWk_effect4, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect4( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = &effect4Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEffect4( no );

	// rhwの設定
	effect4->vertexWk_effect4[0].rhw =
	effect4->vertexWk_effect4[1].rhw =
	effect4->vertexWk_effect4[2].rhw =
	effect4->vertexWk_effect4[3].rhw = 1.0f;

	// 反射光の設定
	effect4->vertexWk_effect4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect4->vertexWk_effect4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect4->vertexWk_effect4[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT4, 0.0f);
	effect4->vertexWk_effect4[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT4);
	effect4->vertexWk_effect4[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT4, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT4);






	//effect4->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect4->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect4->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect4->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect4( int no,int cntPattern )
{
	EFFECT4 *effect4 = &effect4Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT4;
	
	effect4->vertexWk_effect4[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect4->vertexWk_effect4[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect4->vertexWk_effect4[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect4->vertexWk_effect4[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect4( int no )
{
	EFFECT4 *effect4 = &effect4Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	effect4->vertexWk_effect4[0].vtx.x = effect4->pos.x - cosf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[0].vtx.y = effect4->pos.y - sinf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[0].vtx.z = 0.0f;

	effect4->vertexWk_effect4[1].vtx.x = effect4->pos.x + cosf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[1].vtx.y = effect4->pos.y - sinf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[1].vtx.z = 0.0f;

	effect4->vertexWk_effect4[2].vtx.x = effect4->pos.x - cosf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[2].vtx.y = effect4->pos.y + sinf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[2].vtx.z = 0.0f;

	effect4->vertexWk_effect4[3].vtx.x = effect4->pos.x + cosf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[3].vtx.y = effect4->pos.y + sinf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetEffect4(D3DXVECTOR3 pos, int i)
{
	EFFECT4 *effect4 = &effect4Wk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
	//{
		if (effect4->use == false)			// 未使用状態のバレットを見つける
		{
			effect4->use = true;				// 使用状態へ変更する
			effect4->pos = pos;				// 座標をセット
			effect4->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}




//=============================================================================
// エネミー取得関数
//=============================================================================
EFFECT4 *GetEffect4(int no)
{

	
	return(&effect4Wk[no]);



}


