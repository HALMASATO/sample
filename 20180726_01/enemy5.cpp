//=============================================================================
//
// 敵処理 [enemy5.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy5.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"effect5.h"
#include "boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy5( int no);
void SetTextureEnemy5( int no,int cntPattern );
void SetVertexEnemy5( int no );
void SetEnemy5(D3DXVECTOR3 pos);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy5 = NULL;		// テクスチャへのポリゴン


ENEMY5					enemy5Wk[ENEMY5_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy5(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = enemy5Wk;				// エネミーのポインターを初期化
	int j = 0;
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY5,				// ファイルの名前
			&g_pD3DTextureEnemy5);			// 読み込むメモリのポインタ


	}

	j = rand() % (10);


	//enemy5->pos = D3DXVECTOR3(i * 50 + enemy5->InitY, i*50.0f, 0.0f);		// 座標データを初期化


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
	{
		enemy5->use = false;										// 使用
		//enemy5->InitY = 700.0f;
		enemy5->pos = D3DXVECTOR3(900+10.0f,i*50.0f, 0.0f);		// 座標データを初期化
		enemy5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy5->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy5->CountAnim = 0;									// アニメカウントを初期化
		enemy5->Bcounter = 0;										//エネミーの出現時間を管理
		enemy5->counter = 0;
		enemy5->Mcounter = 0;
		enemy5->Bcounter_ORG=rand()%(60*3);
		enemy5->deadflag = false;
		enemy5->effectflag = false;
		enemy5->BBflag = false;
		enemy5->comeback = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY5_SIZE_X, TEXTURE_ENEMY5_SIZE_Y);
		enemy5->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy5->BaseAngle = atan2f(TEXTURE_ENEMY5_SIZE_Y, TEXTURE_ENEMY5_SIZE_X);	// エネミーの角度を初期化

		enemy5->Texture = g_pD3DTextureEnemy5;					// テクスチャ情報
		MakeVertexEnemy5(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy5(void)
{
	if (g_pD3DTextureEnemy5 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy5->Release();
		g_pD3DTextureEnemy5 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy5(void)
{

	ENEMY5 *enemy5 = GetEnemy5(0);				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	EBULLET *Ebullet = GetEBullet(0);	// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);
	//int i = 0;
	

	if (enemy5->counter == 32)
	{
		for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
		{
			GetEnemy5(i)->use = true;
		}
	}

		////エネミーMAX分表示する
		for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
		{

		//	GetEnemy5(i)->use = true;

			if (GetEnemy5(i)->use == true)			// 使用している状態なら更新する
			{

				//エネミーの弾発射
				//GetEnemy5(i)->Bcounter++;
				//if (GetEnemy5(i)->Bcounter >= GetEnemy5(i)->Bcounter_ORG)
				//{
				//	GetEnemy5(i)->Bcounter = 0;

				//	D3DXVECTOR3 pos = GetEnemy5(i)->pos;
				//	SetEBullet(pos);

				//}

				if (GetEnemy5(i)->Mcounter < 14)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 15&& GetEnemy5(i)->Mcounter<=19)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y += 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 19 && GetEnemy5(i)->Mcounter <= 23)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y -= 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 23 && GetEnemy5(i)->Mcounter <= 27)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y += 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 27 /*&& GetEnemy5(i)->Mcounter <= 23*/)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y -= 1.0f;
				}

				//アニメーション
				enemy5->CountAnim++;
				if ((enemy5->CountAnim % TIME_ANIMATION_ENEMY5) == 0)
				{
					// パターンの切り替え
					enemy5->PatternAnim = (enemy5->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY5;
					// テクスチャ座標を設定
					SetTextureEnemy5(i, enemy5->PatternAnim);
				}

				// 画面外まで進んだ？
				if (GetEnemy5(i)->pos.x < 0 - TEXTURE_ENEMY5_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
				{
					GetEnemy5(i)->use = false;
					//GetEnemy5(i)->pos.x = 800.0f;
				}

				GetEnemy5(i)->enemy5pos_x = GetEnemy5(i)->pos.x;
				GetEnemy5(i)->enemy5pos_y = GetEnemy5(i)->pos.y;
				SetVertexEnemy5(i);	// 移動後の座標で頂点を設定
			}


			if (GetEnemy5(i)->effectflag == true)
			{
				SetEffect5(GetEnemy5(i)->pos, i);
				GetEnemy5(i)->effectflag = false;
			}
			if (GetEnemy5(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy5(i)->BBflag = false;
			}

			//if (GetEnemy5(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy5(i)->pos;

			//	SetEnemy5(pos);
			//	GetEnemy5(0)->use = true;
			//	GetEnemy5(i)->comeback = false;
			//	GetEnemy5(0)->counter = 14;


			//}


			if (GetEnemy5(i)->use == false)
			{
				GetEnemy5(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy5(i)->use = false;

			}




		}

}

//}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = GetEnemy5(0);				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

			for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
			{

				if (GetEnemy5(i)->use == true)			// 使用している状態なら描画する
				{

				// テクスチャの設定
				pDevice->SetTexture(0, GetEnemy5(i)->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY5, GetEnemy5(i)->vertexWk_enemy5, sizeof(VERTEX_2D));
			}
		}

	

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy5( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = &enemy5Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy5( no );

	// rhwの設定
	enemy5->vertexWk_enemy5[0].rhw =
	enemy5->vertexWk_enemy5[1].rhw =
	enemy5->vertexWk_enemy5[2].rhw =
	enemy5->vertexWk_enemy5[3].rhw = 1.0f;

	// 反射光の設定
	enemy5->vertexWk_enemy5[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy5->vertexWk_enemy5[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy5->vertexWk_enemy5[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY5, 0.0f);
	enemy5->vertexWk_enemy5[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY5);
	enemy5->vertexWk_enemy5[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY5, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY5);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy5( int no,int cntPattern )
{
	ENEMY5 *enemy5 = &enemy5Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY5;
	
	enemy5->vertexWk_enemy5[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy5->vertexWk_enemy5[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy5->vertexWk_enemy5[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy5->vertexWk_enemy5[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy5( int no )
{
	ENEMY5 *enemy5 = &enemy5Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy5->vertexWk_enemy5[0].vtx.x = enemy5->pos.x - cosf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[0].vtx.y = enemy5->pos.y - sinf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[0].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[1].vtx.x = enemy5->pos.x + cosf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[1].vtx.y = enemy5->pos.y - sinf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[1].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[2].vtx.x = enemy5->pos.x - cosf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[2].vtx.y = enemy5->pos.y + sinf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[2].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[3].vtx.x = enemy5->pos.x + cosf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[3].vtx.y = enemy5->pos.y + sinf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEnemy5(D3DXVECTOR3 pos)
{
	ENEMY5 *enemy5 = &enemy5Wk[0];			// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
	{
		if (enemy5->use == false)			// 未使用状態のバレットを見つける
		{
			enemy5->use = true;			// 使用状態へ変更する
			enemy5->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// 座標をセット

			//for (int j = 0; j < ENEMY54_MAX; j++)
			//{
			//	if (GetEnemy54(j)->use == false) continue;
			//	{
			//		GetEnemy54(i)->nextflag = false;
			//	}
			//}


			//enemy5->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// 発射音再生
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する
		}
	}
}


//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY5 *GetEnemy5(int no)
{

	
	return(&enemy5Wk[no]);



}


