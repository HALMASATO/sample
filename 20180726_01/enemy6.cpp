//=============================================================================
//
// 敵処理 [enemy6.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy6.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet2.h"
#include "input.h"
#include"effect.h"
#include "boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy6( int no);
void SetTextureEnemy6( int no,int cntPattern );
void SetVertexEnemy6( int no );
void SetEnemy6(D3DXVECTOR3 pos);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy6 = NULL;		// テクスチャへのポリゴン


ENEMY6					enemy6Wk[ENEMY6_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy6(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = enemy6Wk;				// エネミーのポインターを初期化
	int j = 0;
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY6,				// ファイルの名前
			&g_pD3DTextureEnemy6);			// 読み込むメモリのポインタ


	}

	j = rand() % (10);


	//enemy6->pos = D3DXVECTOR3(i * 50 + enemy6->InitY, i*50.0f, 0.0f);		// 座標データを初期化


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
	{
		enemy6->use = false;										// 使用
		//enemy6->InitY = 700.0f;
		enemy6->pos = D3DXVECTOR3(900+10.0f,50+i*160.0f, 0.0f);		// 座標データを初期化
		enemy6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy6->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy6->CountAnim = 0;									// アニメカウントを初期化
		enemy6->Bcounter = 0;										//エネミーの出現時間を管理
		enemy6->counter = 0;
		enemy6->Bcounter_ORG=rand()%(60*4);
		enemy6->deadflag = false;
		enemy6->effectflag = false;
		enemy6->BBflag = false;
		enemy6->comeback = false;
		//enemy6->Bcounter = 0;
		//enemy6->Bcounter_ORG = rand() % (60 * 3);


		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY6_SIZE_X, TEXTURE_ENEMY6_SIZE_Y);
		enemy6->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy6->BaseAngle = atan2f(TEXTURE_ENEMY6_SIZE_Y, TEXTURE_ENEMY6_SIZE_X);	// エネミーの角度を初期化

		enemy6->Texture = g_pD3DTextureEnemy6;					// テクスチャ情報
		MakeVertexEnemy6(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy6(void)
{
	if (g_pD3DTextureEnemy6 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy6->Release();
		g_pD3DTextureEnemy6 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy6(void)
{

	ENEMY6 *enemy6 = GetEnemy6(0);				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	EBULLET2 *Ebullet2 = GetEBullet2(0);	// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);


	if (enemy6->counter == 42)
	{
		//エネミーMAX分表示する
		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{
			GetEnemy6(i)->use = true;
		}
	}


		//エネミーMAX分表示する
		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{

			//GetEnemy6(i)->use = true;

			if (GetEnemy6(i)->use == true)			// 使用している状態なら更新する
			{

				if (GetEnemy6(i)->counter > 50)
				{
					//エネミーの弾発射
					GetEnemy6(i)->Bcounter++;
					if (GetEnemy6(i)->Bcounter >= GetEnemy6(i)->Bcounter_ORG)
					{
						GetEnemy6(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetEnemy6(i)->pos;
						SetEBullet2(pos);

					}
				}


				if (GetEnemy6(i)->counter > 48 && GetEnemy6(i)->counter < 58)
				{
					GetEnemy6(i)->pos.x -= 1.0f;
				}




				//アニメーション
				enemy6->CountAnim++;
				if ((enemy6->CountAnim % TIME_ANIMATION_ENEMY6) == 0)
				{
					// パターンの切り替え
					enemy6->PatternAnim = (enemy6->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY6;
					// テクスチャ座標を設定
					SetTextureEnemy6(i, enemy6->PatternAnim);
				}

				// 画面外まで進んだ？
				if (GetEnemy6(i)->pos.x < 0 - TEXTURE_ENEMY6_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
				{
					GetEnemy6(i)->use = false;
					//GetEnemy6(i)->pos.x = 800.0f;
				}

				//GetEnemy6(i)->enemy6pos_x = GetEnemy6(i)->pos.x;
				//GetEnemy6(i)->enemy6pos_y = GetEnemy6(i)->pos.y;


				SetVertexEnemy6(i);	// 移動後の座標で頂点を設定

			}

			if (GetEnemy6(i)->effectflag == true)
			{
				SetEffect(GetEnemy6(i)->pos, i);
			}

			if (GetEnemy6(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy6(i)->BBflag = false;
			}

			//if (GetEnemy6(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy6(i)->pos;

			//	SetEnemy6(pos);
			//	GetEnemy6(0)->use = true;
			//	GetEnemy6(i)->comeback = false;
			//	GetEnemy6(0)->counter = 14;


			//}


			if (GetEnemy6(i)->use == false)
			{
				GetEnemy6(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy6(i)->use = false;

			}




		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = GetEnemy6(0);				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{

			if (GetEnemy6(i)->use == true)			// 使用している状態なら描画する
			{

				// テクスチャの設定
				pDevice->SetTexture(0, GetEnemy6(i)->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY6, GetEnemy6(i)->vertexWk_enemy6, sizeof(VERTEX_2D));
			}



		}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy6( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = &enemy6Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy6( no );

	// rhwの設定
	enemy6->vertexWk_enemy6[0].rhw =
	enemy6->vertexWk_enemy6[1].rhw =
	enemy6->vertexWk_enemy6[2].rhw =
	enemy6->vertexWk_enemy6[3].rhw = 1.0f;

	// 反射光の設定
	enemy6->vertexWk_enemy6[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy6->vertexWk_enemy6[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy6->vertexWk_enemy6[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY6, 0.0f);
	enemy6->vertexWk_enemy6[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY6);
	enemy6->vertexWk_enemy6[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY6, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY6);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy6( int no,int cntPattern )
{
	ENEMY6 *enemy6 = &enemy6Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY6;
	
	enemy6->vertexWk_enemy6[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy6->vertexWk_enemy6[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy6->vertexWk_enemy6[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy6->vertexWk_enemy6[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy6( int no )
{
	ENEMY6 *enemy6 = &enemy6Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy6->vertexWk_enemy6[0].vtx.x = enemy6->pos.x - cosf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[0].vtx.y = enemy6->pos.y - sinf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[0].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[1].vtx.x = enemy6->pos.x + cosf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[1].vtx.y = enemy6->pos.y - sinf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[1].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[2].vtx.x = enemy6->pos.x - cosf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[2].vtx.y = enemy6->pos.y + sinf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[2].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[3].vtx.x = enemy6->pos.x + cosf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[3].vtx.y = enemy6->pos.y + sinf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEnemy6(D3DXVECTOR3 pos)
{
	ENEMY6 *enemy6 = &enemy6Wk[0];			// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
	{
		if (enemy6->use == false)			// 未使用状態のバレットを見つける
		{
			enemy6->use = true;			// 使用状態へ変更する
			enemy6->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// 座標をセット

			//for (int j = 0; j < ENEMY64_MAX; j++)
			//{
			//	if (GetEnemy64(j)->use == false) continue;
			//	{
			//		GetEnemy64(i)->nextflag = false;
			//	}
			//}


			//enemy6->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// 発射音再生
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する
		}
	}
}


//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY6 *GetEnemy6(int no)
{

	
	return(&enemy6Wk[no]);



}


