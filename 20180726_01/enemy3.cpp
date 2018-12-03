//=============================================================================
//
// 敵処理 [enemy3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy3.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"boss.h"
#include"effect3.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy3( int no);
void SetTextureEnemy3( int no,int cntPattern );
void SetVertexEnemy3( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy3 = NULL;		// テクスチャへのポリゴン


ENEMY3					enemy3Wk[ENEMY3_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy3(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = enemy3Wk;				// エネミーのポインターを初期化
	int j = 0;
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY3,				// ファイルの名前
			&g_pD3DTextureEnemy3);			// 読み込むメモリのポインタ


	}

	j = rand() % (9);


	//enemy3->pos = D3DXVECTOR3(i * 50 + enemy3->InitY, i*50.0f, 0.0f);		// 座標データを初期化


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
	{
		enemy3->use = false;										// 使用
		enemy3->pos = D3DXVECTOR3(i*80+245.0f,500.0f, 0.0f);		// 座標データを初期化
		enemy3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy3->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy3->CountAnim = 0;									// アニメカウントを初期化
		enemy3->counter = 0;										//エネミーの出現時間を管理
		enemy3->deadflag = false;
		enemy3->effectflag3 = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY3_SIZE_X, TEXTURE_ENEMY3_SIZE_Y);
		enemy3->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy3->BaseAngle = atan2f(TEXTURE_ENEMY3_SIZE_Y, TEXTURE_ENEMY3_SIZE_X);	// エネミーの角度を初期化

		enemy3->Texture = g_pD3DTextureEnemy3;					// テクスチャ情報
		MakeVertexEnemy3(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy3(void)
{
	if (g_pD3DTextureEnemy3 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy3->Release();
		g_pD3DTextureEnemy3 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy3(void)
{


	ENEMY3 *enemy3 = GetEnemy3(0);				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	EBULLET *Ebullet = GetEBullet(0);	// バレットのポインターを初期化
	BOSS*boss = GetBoss(0);
	int i = 0;


	if (GetEnemy3(i)->counter == 16)
	{
		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{

			GetEnemy3(i)->use = true;


		}
	}

		//エネミーMAX分表示する
		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{


			if (GetEnemy3(i)->use == true)			// 使用している状態なら更新する
			{
				//アニメーション
				enemy3->CountAnim++;
				if ((enemy3->CountAnim % TIME_ANIMATION_ENEMY3) == 0)
				{
					// パターンの切り替え
					enemy3->PatternAnim = (enemy3->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY3;

					// テクスチャ座標を設定
					SetTextureEnemy3(i, enemy3->PatternAnim);

				}

				if (GetEnemy3(i)->counter > 16 && GetEnemy3(i)->counter < 32)
				{
					GetEnemy3(i)->pos.y -= 1.0f;
				}

				if (GetEnemy3(i)->counter > 32)/*&& GetEnemy3(i)->counter < )*/
				{
					GetEnemy3(i)->pos.x -= 1.0f;
				}





				//if (enemy3Wk->counter < 10)
				//{


				//	if (GetPlayer(0)->pos.x <= GetEnemy3(i)->pos.x)
				//	{
				//		GetEnemy3(i)->pos.x -= 1.0f;
				//	}
				//	else if (GetPlayer(0)->pos.x >= GetEnemy3(i)->pos.x)
				//	{

				//		GetEnemy3(i)->pos.x += 1.0f;

				//	}
				//	if (GetPlayer(0)->pos.y <= GetEnemy3(i)->pos.y)
				//	{

				//		GetEnemy3(i)->pos.y -= 1.0f;
				//	}
				//	else if (GetPlayer(0)->pos.y >= GetEnemy3(i)->pos.y)
				//	{
				//		GetEnemy3(i)->pos.y += 1.0f;
				//	}




					//エネミーの弾発射
					//D3DXVECTOR3 pos = enemy3->pos;
					//enemy3->pos.y -= TEXTURE_ENEMY3_SIZE_Y;
					//SetEBullet(pos);









				// 画面外まで進んだ？
				if (enemy3->pos.x < 0-TEXTURE_ENEMY3_SIZE_X/* - SCREEN_WIDTH*/)	// 自分の大きさを考慮して画面外か判定している
				{
					enemy3->use = false;
					enemy3->pos.x = 800.0f;
				}

				GetEnemy3(i)->enemy3pos_x = GetEnemy3(i)->pos.x;
				GetEnemy3(i)->enemy3pos_y = GetEnemy3(i)->pos.y;


				SetVertexEnemy3(i);	// 移動後の座標で頂点を設定
			}


			if (GetEnemy3(i)->effectflag3 == true)
			{
				SetEffect3(GetEnemy3(i)->pos, i);

			}

			if (GetEnemy3(i)->BBflag == true)
			{

				boss->Popcounter++;
				GetEnemy3(i)->BBflag = false;

			}


			if (boss->use == true)
			{

				GetEnemy3(i)->use = false;

			}


		}

}






//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = enemy3Wk;				// エネミーのポインターを初期化


	if (enemy3->counter > 16)
	{


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{
			if (enemy3->use == true)			// 使用している状態なら描画する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, enemy3->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY3, enemy3->vertexWk_enemy3, sizeof(VERTEX_2D));
			}
		}

	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy3( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = &enemy3Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy3( no );

	// rhwの設定
	enemy3->vertexWk_enemy3[0].rhw =
	enemy3->vertexWk_enemy3[1].rhw =
	enemy3->vertexWk_enemy3[2].rhw =
	enemy3->vertexWk_enemy3[3].rhw = 1.0f;

	// 反射光の設定
	enemy3->vertexWk_enemy3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy3->vertexWk_enemy3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy3->vertexWk_enemy3[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY3, 0.0f);
	enemy3->vertexWk_enemy3[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY3);
	enemy3->vertexWk_enemy3[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY3, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY3);






	//enemy3->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy3->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy3->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy3->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy3( int no,int cntPattern )
{
	ENEMY3 *enemy3 = &enemy3Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY3;
	
	enemy3->vertexWk_enemy3[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy3->vertexWk_enemy3[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy3->vertexWk_enemy3[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy3->vertexWk_enemy3[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy3( int no )
{
	ENEMY3 *enemy3 = &enemy3Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy3->vertexWk_enemy3[0].vtx.x = enemy3->pos.x - cosf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[0].vtx.y = enemy3->pos.y - sinf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[0].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[1].vtx.x = enemy3->pos.x + cosf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[1].vtx.y = enemy3->pos.y - sinf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[1].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[2].vtx.x = enemy3->pos.x - cosf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[2].vtx.y = enemy3->pos.y + sinf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[2].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[3].vtx.x = enemy3->pos.x + cosf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[3].vtx.y = enemy3->pos.y + sinf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY3 *GetEnemy3(int no)
{

	
	return(&enemy3Wk[no]);



}


