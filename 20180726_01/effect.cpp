//=============================================================================
//
// 敵処理 [effect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy.h"
#include "enemy2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect( int no);
void SetTextureEffect( int no,int cntPattern );
void SetVertexEffect( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// テクスチャへのポリゴン


EFFECT					effectWk[EFFECT_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = effectWk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EFFECT,				// ファイルの名前
			&g_pD3DTextureEffect);			// 読み込むメモリのポインタ


	}



	 //エネミーの初期化処理
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		effect->use = false;										// 使用
		effect->pos = D3DXVECTOR3(i*50+effect->InitY,50.0f, 0.0f);		// 座標データを初期化
		effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		effect->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		effect->CountAnim = 0;									// アニメカウントを初期化
		effect->effectcounter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT_SIZE_X, TEXTURE_EFFECT_SIZE_Y);
		effect->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		effect->BaseAngle = atan2f(TEXTURE_EFFECT_SIZE_Y, TEXTURE_EFFECT_SIZE_X);	// エネミーの角度を初期化

		effect->Texture = g_pD3DTextureEffect;					// テクスチャ情報
		MakeVertexEffect(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if (g_pD3DTextureEffect != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *effect = effectWk;				// エネミーのポインターを初期化
	//PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	//EBULLET *Ebullet = GetEBullet(0);	// バレットのポインターを初期化
	ENEMY*enemy = GetEnemy(0);
	ENEMY2*enemy2 = GetEnemy2(0);



	//if (effect->effectcounter == 1)
	//{
		//for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		//{

			//if (effect->effectcounter == 1)
			//{
				//if (effect->use == false)
				//{
				//	effect->pos.x = GetEnemy(j)->enemypos_x;
				//	effect->pos.y = GetEnemy(j)->enemypos_y;
				//}
			//}

			if (effect->use == true)			// 使用している状態なら更新する
			{

				//アニメーション
				effect->CountAnim++;
				if ((effect->CountAnim % TIME_ANIMATION_EFFECT) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT -1> effect->PatternAnim)
					{
						// パターンの切り替え
						effect->PatternAnim = (effect->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT;


					}
					else
					{
						effect->use = false;
						effect->PatternAnim = 0;
						GetEnemy(effect->i)->effectflag = false;
					}

					
					// テクスチャ座標を設定
					SetTextureEffect(0, effect->PatternAnim);


					SetVertexEffect(0);	// 移動後の座標で頂点を設定


				}

				//if(ANIM_PATTERN_NUM_EFFECT>effect->PatternAnim)


			//	effect->effectcounter = 0;								//エフェクトカウンター


			//}


	
	//}


	//if (effect->effectcounter == 2)
	//{
		//エネミーのエフェクト
		//for (int j = 0; j < ENEMY2_MAX; j++, enemy2++)
		//{

		//	//if (effect->effectcounter == 2)
		//	//{
		//		if (GetEnemy2(j)->use == false)
		//		{
		//			effect->pos.x = GetEnemy2(j)->enemy2pos_x;
		//			effect->pos.y = GetEnemy2(j)->enemy2pos_y;
		//		}
		//	//}



		//	if (effect->use == true)			// 使用している状態なら更新する
		//	{

		//		//アニメーション
		//		effect->CountAnim++;
		//		if ((effect->CountAnim % TIME_ANIMATION_EFFECT) == 0)
		//		{
		//			// パターンの切り替え
		//			effect->PatternAnim = (effect->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT;

		//			// テクスチャ座標を設定
		//			SetTextureEffect(0, effect->PatternAnim);

		//		}


		//		SetVertexEffect(0);	// 移動後の座標で頂点を設定

		//		effect->effectcounter = 0;								//エフェクトカウンター


		//	}


		//}

	}


		//if (effect->counter > 1)
		//{
		//	effect->use = false;
		//	effect->counter = 0;

			//effect->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
			//effect->CountAnim = 0;										// アニメカウントを初期化
		//}
}



			



//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = effectWk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
			if (effect->use == true)			// 使用している状態なら描画する
			{
				if (effect->counter > 0)
				{
					// テクスチャの設定
					pDevice->SetTexture(0, effect->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT, effect->vertexWk_effect, sizeof(VERTEX_2D));
				}
			}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = &effectWk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEffect( no );

	// rhwの設定
	effect->vertexWk_effect[0].rhw =
	effect->vertexWk_effect[1].rhw =
	effect->vertexWk_effect[2].rhw =
	effect->vertexWk_effect[3].rhw = 1.0f;

	// 反射光の設定
	effect->vertexWk_effect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk_effect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk_effect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk_effect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	effect->vertexWk_effect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk_effect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 0.0f);
	effect->vertexWk_effect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);
	effect->vertexWk_effect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT);


	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect( int no,int cntPattern )
{
	EFFECT *effect = &effectWk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;
	
	effect->vertexWk_effect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect->vertexWk_effect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect->vertexWk_effect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect->vertexWk_effect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect( int no )
{
	EFFECT *effect = &effectWk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	effect->vertexWk_effect[0].vtx.x = effect->pos.x - cosf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[0].vtx.y = effect->pos.y - sinf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[0].vtx.z = 0.0f;

	effect->vertexWk_effect[1].vtx.x = effect->pos.x + cosf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[1].vtx.y = effect->pos.y - sinf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[1].vtx.z = 0.0f;

	effect->vertexWk_effect[2].vtx.x = effect->pos.x - cosf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[2].vtx.y = effect->pos.y + sinf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[2].vtx.z = 0.0f;

	effect->vertexWk_effect[3].vtx.x = effect->pos.x + cosf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[3].vtx.y = effect->pos.y + sinf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk_effect[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, int i)
{
	EFFECT *effect = &effectWk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < EFFECT_MAX; i++, effect++)
	//{
		if (effect->use == false)			// 未使用状態のバレットを見つける
		{
			effect->use = true;				// 使用状態へ変更する
			effect->pos = pos;				// 座標をセット
			effect->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}




//=============================================================================
// エネミー取得関数
//=============================================================================
EFFECT *GetEffect(int no)
{

	
	return(&effectWk[no]);



}


