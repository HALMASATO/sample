//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include"boss2.h"
#include"Ebullet.h"
#include "input.h"
#include "bosseffect.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBoss2( int no);
void SetTextureBoss2( int no,int cntPattern );
void SetVertexBoss2( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS2 = NULL;		// テクスチャへのポリゴン


BOSS2					boss2Wk[BOSS2_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS2 *boss2 = boss2Wk;				// エネミーのポインターを初期化


	srand((unsigned)time(NULL));
	int j = 0;


	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BOSS2,				// ファイルの名前
			&g_pD3DTextureBOSS2);			// 読み込むメモリのポインタ


	}

		// エネミーの初期化処理
		for (int i = 0; i < BOSS2_MAX; i++, boss2++)
		{
			boss2->use = false;										// 使用
			boss2->effectflag = false;
			boss2->drawflug = false;
			boss2->pos = D3DXVECTOR3(i * 50 + 500.0f, 220.0f, 0.0f);	// 座標データを初期化
			boss2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			boss2->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
			boss2->CountAnim = 0;									// アニメカウントを初期化
			boss2->counter = 0;
			boss2->Popcounter = 0;
			boss2->Bcounter = 0;
			boss2->Bcounter_ORG = rand() % (60 * 3);
			boss2->Hitcounter = 0;
			boss2 ->Timecounter = 0;
			boss2->HP = 200;
			boss2->MAXHP = boss2->HP;


			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS2_SIZE_X, TEXTURE_BOSS2_SIZE_Y);
			boss2->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
			boss2->BaseAngle = atan2f(TEXTURE_BOSS2_SIZE_Y, TEXTURE_BOSS2_SIZE_X);	// エネミーの角度を初期化

			boss2->Texture = g_pD3DTextureBOSS2;					// テクスチャ情報
			MakeVertexBoss2(i);										// 頂点情報の作成
		}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss2(void)
{
	if (g_pD3DTextureBOSS2 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBOSS2->Release();
		g_pD3DTextureBOSS2 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss2(void)
{
	BOSS2 *boss2 = GetBoss2(0);				// エネミーのポインターを初期化


	if (boss2->Timecounter > 6)
	{
		boss2->Hitcounter = 0;
		boss2->Timecounter = 0;
		//player->Hitcounter = 0;

	}


	if (boss2->Popcounter > 13)
	{
		for (int i = 0; i < BOSS2_MAX; i++)
		{
			if (GetBoss2(i)->use == true)			// 使用している状態なら更新する
			{



					GetBoss2(i)->Bcounter++;
					if (GetBoss2(i)->Bcounter >= GetBoss2(i)->Bcounter_ORG)
					{
						GetBoss2(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetBoss2(i)->pos;
						SetEBullet(pos);


					}
					if (boss2->counter <= 3)
					{
						boss2->pos.y -= 1.0f;
					}
					if (boss2->counter >=3&&boss2->counter<=6 )
					{
						boss2->pos.y += 1.0f;
					}

					if (boss2->counter == 7)
					{

						boss2->counter = 0;

					}


					//アニメーション
					boss2->CountAnim++;
					if ((boss2->CountAnim % TIME_ANIMATION_BOSS2) == 0)
					{
						// パターンの切り替え
						boss2->PatternAnim = (boss2->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS2;

						// テクスチャ座標を設定
						SetTextureBoss2(i, boss2->PatternAnim);

					}

				}

			if (GetBoss2(i)->effectflag == true)
			{
				SetBossEffect(GetBoss2(i)->pos, i);

			}


				// 画面外まで進んだ？
				if (boss2->pos.y < -TEXTURE_BOSS2_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
				{
					boss2->use = false;
					boss2->pos.x = -100.0f;
				}


				SetVertexBoss2(i);	// 移動後の座標で頂点を設定
			}
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BOSS2 *boss2 = boss2Wk;				// エネミーのポインターを初期化

	//if (boss2->Popcounter > 13)
	//{
	//for (int i = 0; i < boss2->Timecounter; i++)
	//{

	//	switch (boss2->Timecounter)
	//	{
	//	case 1:
	//		boss2->drawflug = true;
	//		break;

	//	case 2:
	//		boss2->drawflug = false;
	//		break;

	//	case 3:
	//		boss2->drawflug = true;
	//		break;

	//	case 4:
	//		boss2->drawflug = false;
	//		break;

	//	case 5:
	//		boss2->drawflug = true;
	//		break;

	//	case 6:
	//		boss2->drawflug = false;
	//		break;

	//	default:
	//		break;
	//	}

	//}





		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < BOSS2_MAX; i++, boss2++)
		{
			if (boss2->use == true)			// 使用している状態なら描画する
			{
				//if (boss2->drawflug = false)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, boss2->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS2, boss2->vertexWk_boss2, sizeof(VERTEX_2D));
				//}
			}


		}

	}


//}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss2( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS2 *boss2 = &boss2Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexBoss2( no );

	// rhwの設定
	boss2->vertexWk_boss2[0].rhw =
	boss2->vertexWk_boss2[1].rhw =
	boss2->vertexWk_boss2[2].rhw =
	boss2->vertexWk_boss2[3].rhw = 1.0f;

	// 反射光の設定
	boss2->vertexWk_boss2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss2->vertexWk_boss2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss2->vertexWk_boss2[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS2, 0.0f);
	boss2->vertexWk_boss2[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS2);
	boss2->vertexWk_boss2[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS2);


	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss2( int no,int cntPattern )
{
	BOSS2 *boss2 = &boss2Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS2;
	
	boss2->vertexWk_boss2[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss2->vertexWk_boss2[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss2->vertexWk_boss2[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss2->vertexWk_boss2[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss2( int no )
{
	BOSS2 *boss2 = &boss2Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	boss2->vertexWk_boss2[0].vtx.x = boss2->pos.x - cosf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[0].vtx.y = boss2->pos.y - sinf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[0].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[1].vtx.x = boss2->pos.x + cosf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[1].vtx.y = boss2->pos.y - sinf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[1].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[2].vtx.x = boss2->pos.x - cosf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[2].vtx.y = boss2->pos.y + sinf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[2].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[3].vtx.x = boss2->pos.x + cosf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[3].vtx.y = boss2->pos.y + sinf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
BOSS2 *GetBoss2(int no)
{

	
	return(&boss2Wk[no]);



}


