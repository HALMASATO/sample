//=============================================================================
//
// 敵処理 [effect3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect3.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy3.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect3( int no);
void SetTextureEffect3( int no,int cntPattern );
void SetVertexEffect3( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect3 = NULL;		// テクスチャへのポリゴン


EFFECT3					effect3Wk[EFFECT3_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect3(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = effect3Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT3,				// ファイルの名前
			&g_pD3DTextureEffect3);			// 読み込むメモリのポインタ
	}



	 //エネミーの初期化処理
	for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
	{
		effect3->use = false;										// 使用
		effect3->pos = D3DXVECTOR3(i*50+effect3->InitY,50.0f, 0.0f);		// 座標データを初期化
		effect3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		effect3->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		effect3->CountAnim = 0;									// アニメカウントを初期化
		effect3->effect3counter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT3_SIZE_X, TEXTURE_EFFECT3_SIZE_Y);
		effect3->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		effect3->BaseAngle = atan2f(TEXTURE_EFFECT3_SIZE_Y, TEXTURE_EFFECT3_SIZE_X);	// エネミーの角度を初期化

		effect3->Texture = g_pD3DTextureEffect3;					// テクスチャ情報
		MakeVertexEffect3(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect3(void)
{
	if (g_pD3DTextureEffect3 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect3->Release();
		g_pD3DTextureEffect3 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect3(void)
{
	EFFECT3 *effect3 = effect3Wk;				// エネミーのポインターを初期化
	ENEMY3*enemy3 = GetEnemy3(0);




			if (effect3->use == true)			// 使用している状態なら更新する
			{

				//アニメーション
				effect3->CountAnim++;
				if ((effect3->CountAnim % TIME_ANIMATION_EFFECT3) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT3 -1> effect3->PatternAnim)
					{
						// パターンの切り替え
						effect3->PatternAnim = (effect3->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT3;


					}
					else
					{
						effect3->use = false;
						effect3->PatternAnim = 0;
						GetEnemy3(effect3->i)->effectflag3 = false;
					}

					
					// テクスチャ座標を設定
					SetTextureEffect3(0, effect3->PatternAnim);


					SetVertexEffect3(0);	// 移動後の座標で頂点を設定


				}
	}

}



			



//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = effect3Wk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
		//{
			if (effect3->use == true)			// 使用している状態なら描画する
			{
				//if (effect3->counter > 0)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, effect3->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT3, effect3->vertexWk_effect3, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect3( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = &effect3Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEffect3( no );

	// rhwの設定
	effect3->vertexWk_effect3[0].rhw =
	effect3->vertexWk_effect3[1].rhw =
	effect3->vertexWk_effect3[2].rhw =
	effect3->vertexWk_effect3[3].rhw = 1.0f;

	// 反射光の設定
	effect3->vertexWk_effect3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect3->vertexWk_effect3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect3->vertexWk_effect3[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT3, 0.0f);
	effect3->vertexWk_effect3[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT3);
	effect3->vertexWk_effect3[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT3, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT3);






	//effect3->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect3->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect3->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect3->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect3( int no,int cntPattern )
{
	EFFECT3 *effect3 = &effect3Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT3;
	
	effect3->vertexWk_effect3[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect3->vertexWk_effect3[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect3->vertexWk_effect3[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect3->vertexWk_effect3[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect3( int no )
{
	EFFECT3 *effect3 = &effect3Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	effect3->vertexWk_effect3[0].vtx.x = effect3->pos.x - cosf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[0].vtx.y = effect3->pos.y - sinf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[0].vtx.z = 0.0f;

	effect3->vertexWk_effect3[1].vtx.x = effect3->pos.x + cosf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[1].vtx.y = effect3->pos.y - sinf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[1].vtx.z = 0.0f;

	effect3->vertexWk_effect3[2].vtx.x = effect3->pos.x - cosf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[2].vtx.y = effect3->pos.y + sinf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[2].vtx.z = 0.0f;

	effect3->vertexWk_effect3[3].vtx.x = effect3->pos.x + cosf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[3].vtx.y = effect3->pos.y + sinf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetEffect3(D3DXVECTOR3 pos, int i)
{
	EFFECT3 *effect3 = &effect3Wk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
	//{
		if (effect3->use == false)			// 未使用状態のバレットを見つける
		{
			effect3->use = true;				// 使用状態へ変更する
			effect3->pos = pos;				// 座標をセット
			effect3->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}




//=============================================================================
// エネミー取得関数
//=============================================================================
EFFECT3 *GetEffect3(int no)
{

	
	return(&effect3Wk[no]);



}


