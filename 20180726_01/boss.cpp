//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include"boss.h"
#include"Ebullet.h"
#include "input.h"
#include "bosseffect.h"
#include "btgage.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBoss( int no);
void SetTextureBoss( int no,int cntPattern );
void SetVertexBoss( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS = NULL;		// テクスチャへのポリゴン


BOSS					bossWk[BOSS_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = bossWk;				// エネミーのポインターを初期化


	srand((unsigned)time(NULL));
	int j = 0;


	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BOSS,				// ファイルの名前
			&g_pD3DTextureBOSS);			// 読み込むメモリのポインタ


	}

		// エネミーの初期化処理
		for (int i = 0; i < BOSS_MAX; i++, boss++)
		{
			boss->use = false;										// 使用
			boss->effectflag = false;
			boss->drawflug = false;
			boss->endflug = false;
			boss->pos = D3DXVECTOR3(i * 50 + 700.0f, 220.0f, 0.0f);	// 座標データを初期化
			boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			boss->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
			boss->CountAnim = 0;									// アニメカウントを初期化
			boss->counter = 0;
			boss->Popcounter = 0;
			boss->Bcounter = 0;
			boss->Bcounter_ORG = rand() % (60 * 3);
			boss->Hitcounter = 0;
			boss ->Timecounter = 0;
			boss->HP = 100;
			boss->MAXHP = boss->HP;


			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y);
			boss->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
			boss->BaseAngle = atan2f(TEXTURE_BOSS_SIZE_Y, TEXTURE_BOSS_SIZE_X);	// エネミーの角度を初期化

			boss->Texture = g_pD3DTextureBOSS;					// テクスチャ情報
			MakeVertexBoss(i);										// 頂点情報の作成
		}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss(void)
{
	if (g_pD3DTextureBOSS != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBOSS->Release();
		g_pD3DTextureBOSS = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss(void)
{
	BOSS *boss = GetBoss(0);				// エネミーのポインターを初期化

	if (GetBoss(0)->Popcounter > 13)
	{
		GetBoss(0)->use = true;

	}


	if (boss->Timecounter > 6)
	{
		boss->Hitcounter = 0;
		boss->Timecounter = 0;

	}


	if (boss->Popcounter > 13)
	{


		for (int i = 0; i < BOSS_MAX; i++)
		{
			if (GetBoss(i)->use == true)			// 使用している状態なら更新する
			{



					GetBoss(i)->Bcounter++;
					if (GetBoss(i)->Bcounter >= GetBoss(i)->Bcounter_ORG)
					{
						GetBoss(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetBoss(i)->pos;
						SetEBullet(pos);


					}
					if (boss->counter <= 3)
					{
						boss->pos.y -= 1.0f;
					}
					if (boss->counter >=3&&boss->counter<=6 )
					{
						boss->pos.y += 1.0f;
					}

					if (boss->counter == 7)
					{

						boss->counter = 0;

					}


					//アニメーション
					boss->CountAnim++;
					if ((boss->CountAnim % TIME_ANIMATION_BOSS) == 0)
					{
						// パターンの切り替え
						boss->PatternAnim = (boss->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS;

						// テクスチャ座標を設定
						SetTextureBoss(i, boss->PatternAnim);

					}

			}

			if (GetBoss(i)->effectflag == true)
			{
				SetBossEffect(GetBoss(i)->pos, i);

			}


				// 画面外まで進んだ？
				if (boss->pos.y < -TEXTURE_BOSS_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
				{
					boss->use = false;
					boss->pos.x = -100.0f;
				}

				if (boss->HP <= 0)
				{
					boss->endflug = true;
				}

				SetVertexBoss(i);	// 移動後の座標で頂点を設定
			}
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BOSS *boss = bossWk;				// エネミーのポインターを初期化

	//if (boss->Popcounter > 13)
	//{
	//for (int i = 0; i < boss->Timecounter; i++)
	//{

	//	switch (boss->Timecounter)
	//	{
	//	case 1:
	//		boss->drawflug = true;
	//		break;

	//	case 2:
	//		boss->drawflug = false;
	//		break;

	//	case 3:
	//		boss->drawflug = true;
	//		break;

	//	case 4:
	//		boss->drawflug = false;
	//		break;

	//	case 5:
	//		boss->drawflug = true;
	//		break;

	//	case 6:
	//		boss->drawflug = false;
	//		break;

	//	default:
	//		break;
	//	}

	//}





		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < BOSS_MAX; i++, boss++)
		{
			if (boss->use == true)			// 使用している状態なら描画する
			{
				//if (boss->drawflug = false)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, boss->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS, boss->vertexWk_boss, sizeof(VERTEX_2D));
				//}
			}


		}

	}


//}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexBoss( no );

	// rhwの設定
	boss->vertexWk_boss[0].rhw =
	boss->vertexWk_boss[1].rhw =
	boss->vertexWk_boss[2].rhw =
	boss->vertexWk_boss[3].rhw = 1.0f;

	// 反射光の設定
	boss->vertexWk_boss[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss->vertexWk_boss[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk_boss[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 0.0f);
	boss->vertexWk_boss[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);
	boss->vertexWk_boss[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS);


	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss( int no,int cntPattern )
{
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS;
	
	boss->vertexWk_boss[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss->vertexWk_boss[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss->vertexWk_boss[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss->vertexWk_boss[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss( int no )
{
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	boss->vertexWk_boss[0].vtx.x = boss->pos.x - cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[0].vtx.y = boss->pos.y - sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[0].vtx.z = 0.0f;
	
	boss->vertexWk_boss[1].vtx.x = boss->pos.x + cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[1].vtx.y = boss->pos.y - sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[1].vtx.z = 0.0f;
	
	boss->vertexWk_boss[2].vtx.x = boss->pos.x - cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[2].vtx.y = boss->pos.y + sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[2].vtx.z = 0.0f;
	
	boss->vertexWk_boss[3].vtx.x = boss->pos.x + cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[3].vtx.y = boss->pos.y + sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
BOSS *GetBoss(int no)
{

	
	return(&bossWk[no]);



}


