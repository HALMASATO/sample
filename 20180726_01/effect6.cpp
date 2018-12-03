//=============================================================================
//
// 敵処理 [effect6.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect6.h"
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
HRESULT MakeVertexEffect6( int no);
void SetTextureEffect6( int no,int cntPattern );
void SetVertexEffect6( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect6 = NULL;		// テクスチャへのポリゴン


EFFECT6					effect6Wk[EFFECT6_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect6(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = effect6Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT6,				// ファイルの名前
			&g_pD3DTextureEffect6);			// 読み込むメモリのポインタ


	}
	 //エネミーの初期化処理
	for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
	{
		effect6->use = false;										// 使用
		effect6->pos = D3DXVECTOR3(i*50+effect6->InitY,50.0f, 0.0f);		// 座標データを初期化
		effect6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		effect6->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		effect6->CountAnim = 0;									// アニメカウントを初期化
		effect6->effectcounter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT6_SIZE_X, TEXTURE_EFFECT6_SIZE_Y);
		effect6->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		effect6->BaseAngle = atan2f(TEXTURE_EFFECT6_SIZE_Y, TEXTURE_EFFECT6_SIZE_X);	// エネミーの角度を初期化

		effect6->Texture = g_pD3DTextureEffect6;					// テクスチャ情報
		MakeVertexEffect6(i);										// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect6(void)
{
	if (g_pD3DTextureEffect6 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect6->Release();
		g_pD3DTextureEffect6 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect6(void)
{
	EFFECT6 *effect6 = effect6Wk;				// エネミーのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect6->use == true)			// 使用している状態なら更新する
			{

				//アニメーション
				effect6->CountAnim++;
				if ((effect6->CountAnim % TIME_ANIMATION_EFFECT6) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT6 -1> effect6->PatternAnim)
					{
						// パターンの切り替え
						effect6->PatternAnim = (effect6->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT6;


					}
					else
					{
						effect6->use = false;
						effect6->PatternAnim = 0;
						GetEnemy4(effect6->i)->effectflag4 = false;
					}

					
					// テクスチャ座標を設定
					SetTextureEffect6(0, effect6->PatternAnim);


					SetVertexEffect6(0);	// 移動後の座標で頂点を設定


				}

			}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = effect6Wk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
		//{
			if (effect6->use == true)			// 使用している状態なら描画する
			{
				//if (effect6->counter > 0)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, effect6->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT6, effect6->vertexWk_effect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect6( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = &effect6Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEffect6( no );

	// rhwの設定
	effect6->vertexWk_effect[0].rhw =
	effect6->vertexWk_effect[1].rhw =
	effect6->vertexWk_effect[2].rhw =
	effect6->vertexWk_effect[3].rhw = 1.0f;

	// 反射光の設定
	effect6->vertexWk_effect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect6->vertexWk_effect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect6->vertexWk_effect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT6, 0.0f);
	effect6->vertexWk_effect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT6);
	effect6->vertexWk_effect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT6, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT6);






	//effect6->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect6->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect6->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect6->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect6( int no,int cntPattern )
{
	EFFECT6 *effect6 = &effect6Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT6;
	
	effect6->vertexWk_effect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect6->vertexWk_effect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect6->vertexWk_effect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect6->vertexWk_effect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect6( int no )
{
	EFFECT6 *effect6 = &effect6Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	effect6->vertexWk_effect[0].vtx.x = effect6->pos.x - cosf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[0].vtx.y = effect6->pos.y - sinf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[0].vtx.z = 0.0f;

	effect6->vertexWk_effect[1].vtx.x = effect6->pos.x + cosf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[1].vtx.y = effect6->pos.y - sinf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[1].vtx.z = 0.0f;

	effect6->vertexWk_effect[2].vtx.x = effect6->pos.x - cosf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[2].vtx.y = effect6->pos.y + sinf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[2].vtx.z = 0.0f;

	effect6->vertexWk_effect[3].vtx.x = effect6->pos.x + cosf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[3].vtx.y = effect6->pos.y + sinf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetEffect6(D3DXVECTOR3 pos, int i)
{
	EFFECT6 *effect6 = &effect6Wk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
	//{
		if (effect6->use == false)			// 未使用状態のバレットを見つける
		{
			effect6->use = true;				// 使用状態へ変更する
			effect6->pos = pos;				// 座標をセット
			effect6->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}


//=============================================================================
// エネミー取得関数
//=============================================================================
EFFECT6 *GetEffect6(int no)
{

	
	return(&effect6Wk[no]);



}