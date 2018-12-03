//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
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
HRESULT MakeVertexEnemy( int no);
void SetTextureEnemy( int no,int cntPattern );
void SetVertexEnemy( int no );
void SetEnemy(D3DXVECTOR3 pos);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy = NULL;		// テクスチャへのポリゴン


ENEMY					enemyWk[ENEMY_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化
	int j = 0;
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY,				// ファイルの名前
			&g_pD3DTextureEnemy);			// 読み込むメモリのポインタ


	}

	j = rand() % (10);


	//enemy->pos = D3DXVECTOR3(i * 50 + enemy->InitY, i*50.0f, 0.0f);		// 座標データを初期化


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// 使用
		//enemy->InitY = 700.0f;
		enemy->pos = D3DXVECTOR3(900+10.0f,i*100.0f, 0.0f);		// 座標データを初期化
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy->CountAnim = 0;									// アニメカウントを初期化
		enemy->Bcounter = 0;										//エネミーの出現時間を管理
		enemy->counter = 0;
		enemy->Bcounter_ORG=rand()%(60*3);
		enemy->deadflag = false;
		enemy->effectflag = false;
		enemy->BBflag = false;
		enemy->comeback = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// エネミーの角度を初期化

		enemy->Texture = g_pD3DTextureEnemy;					// テクスチャ情報
		MakeVertexEnemy(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{

	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	EBULLET *Ebullet = GetEBullet(0);	// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);
	//int i = 0;

	int j = rand() % (10);
	
			//if (GetEnemy(i)->use == true)			// 使用している状態なら更新する
			//{

		//エネミーMAX分表示する
		for (int i=0; i < ENEMY_MAX; i++, enemy++)
		{

			if (GetEnemy(i)->use == true)			// 使用している状態なら更新する
			{

				//エネミーの弾発射
				//GetEnemy(i)->Bcounter++;
				//if (GetEnemy(i)->Bcounter >= GetEnemy(i)->Bcounter_ORG)
				//{
				//	GetEnemy(i)->Bcounter = 0;

				//	D3DXVECTOR3 pos = GetEnemy(i)->pos;
				//	SetEBullet(pos);

				//}

				GetEnemy(i)->pos.x -= 1.0f;


				 //アニメーション
				enemy->CountAnim++;
				if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
				{
					// パターンの切り替え
					enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;
					// テクスチャ座標を設定
					SetTextureEnemy(i, enemy->PatternAnim);
				}

				// 画面外まで進んだ？
				if (GetEnemy(i)->pos.x < 0-TEXTURE_ENEMY_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
				{
					GetEnemy(i)->use = false;
					//GetEnemy(i)->pos.x = 800.0f;
				}

				GetEnemy(i)->enemypos_x = GetEnemy(i)->pos.x;
				GetEnemy(i)->enemypos_y = GetEnemy(i)->pos.y;


				SetVertexEnemy(i);	// 移動後の座標で頂点を設定

			}

			if (GetEnemy(i)->effectflag == true)
			{
				SetEffect(GetEnemy(i)->pos, i);
			}

			if (GetEnemy(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy(i)->BBflag = false;
			}

			//if (GetEnemy(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy(i)->pos;

			//	SetEnemy(pos);
			//	GetEnemy(0)->use = true;
			//	GetEnemy(i)->comeback = false;
			//	GetEnemy(0)->counter = 14;


			//}


			if (GetEnemy(i)->use == false)
			{
				GetEnemy(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy(i)->use = false;

			}




		}


}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

			for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			{

				if (GetEnemy(i)->use == true)			// 使用している状態なら描画する
				{

					// テクスチャの設定
					pDevice->SetTexture(0, GetEnemy(i)->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, GetEnemy(i)->vertexWk_enemy, sizeof(VERTEX_2D));
				}


			}
		

	

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy( no );

	// rhwの設定
	enemy->vertexWk_enemy[0].rhw =
	enemy->vertexWk_enemy[1].rhw =
	enemy->vertexWk_enemy[2].rhw =
	enemy->vertexWk_enemy[3].rhw = 1.0f;

	// 反射光の設定
	enemy->vertexWk_enemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy->vertexWk_enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk_enemy[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk_enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk_enemy[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy( int no,int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk_enemy[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk_enemy[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk_enemy[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk_enemy[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy->vertexWk_enemy[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[0].vtx.z = 0.0f;

	enemy->vertexWk_enemy[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[1].vtx.z = 0.0f;

	enemy->vertexWk_enemy[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[2].vtx.z = 0.0f;

	enemy->vertexWk_enemy[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	ENEMY *enemy = &enemyWk[0];			// バレットのポインターを初期化
	ENEMY4*enemy4 = GetEnemy4(0);

		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == false)			// 未使用状態のバレットを見つける
		{
			enemy->use = true;			// 使用状態へ変更する
			enemy->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// 座標をセット

			//for (int j = 0; j < ENEMY4_MAX; j++)
			//{
			//	if (GetEnemy4(j)->use == false) continue;
			//	{
			//		GetEnemy4(i)->nextflag = false;
			//	}
			//}


			//enemy->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// 発射音再生
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する
		}
	}
}


//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY *GetEnemy(int no)
{

	
	return(&enemyWk[no]);



}


