//=============================================================================
//
// 敵処理 [enemy4.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"effect4.h"
#include"boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy4( int no);
void SetTextureEnemy4( int no,int cntPattern );
void SetVertexEnemy4( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy4 = NULL;		// テクスチャへのポリゴン


ENEMY4					enemy4Wk[ENEMY4_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy4(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = enemy4Wk;				// エネミーのポインターを初期化
	int j = 0;
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY4,			// ファイルの名前
			&g_pD3DTextureEnemy4);			// 読み込むメモリのポインタ


	}

	j = rand() % (9);


	//enemy4->pos = D3DXVECTOR3(i * 50 + enemy4->InitY, i*50.0f, 0.0f);		// 座標データを初期化


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
	{
		enemy4->use = true;										// 使用
		enemy4->pos = D3DXVECTOR3(-50,i*100.0f, 0.0f);		// 座標データを初期化
		enemy4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy4->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy4->CountAnim = 0;									// アニメカウントを初期化
		enemy4->counter = 0;										//エネミーの出現時間を管理
		enemy4->nextflag = false;
		enemy4->effectflag4 = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY4_SIZE_X, TEXTURE_ENEMY4_SIZE_Y);
		enemy4->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy4->BaseAngle = atan2f(TEXTURE_ENEMY4_SIZE_Y, TEXTURE_ENEMY4_SIZE_X);	// エネミーの角度を初期化

		enemy4->Texture = g_pD3DTextureEnemy4;					// テクスチャ情報
		MakeVertexEnemy4(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy4(void)
{
	if (g_pD3DTextureEnemy4 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy4->Release();
		g_pD3DTextureEnemy4 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy4(void)
{


	ENEMY4 *enemy4 = GetEnemy4(0);				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーのポインターを初期化
	EBULLET *Ebullet = GetEBullet(0);	// バレットのポインターを初期化
	BOSS*boss = GetBoss(0);
	int i = 0;

	if (GetEnemy4(i)->counter == 28)
	{
		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{

			GetEnemy4(i)->use = true;


		}
	}

		//エネミーMAX分表示する
		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{

			if (enemy4->use == true)			// 使用している状態なら更新する
			{
				//アニメーション
				enemy4->CountAnim++;
				if ((enemy4->CountAnim % TIME_ANIMATION_ENEMY4) == 0)
				{
					// パターンの切り替え
					enemy4->PatternAnim = (enemy4->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY4;

					// テクスチャ座標を設定
					SetTextureEnemy4(i, enemy4->PatternAnim);

				}


				if (GetEnemy4(i)->counter > 28 && GetEnemy4(i)->counter < 48)
				{
					GetEnemy4(i)->pos.x += 1.0f;
				}

				if (GetEnemy4(i)->counter>48/* && GetEnemy4(i)->counter < 48*/)
				{
					GetEnemy4(i)->pos.x -= 1.0f;
				}






				//if (GetPlayer(0)->pos.x <= GetEnemy4(i)->pos.x)
				//{
				//	GetEnemy4(i)->pos.x -= 1.0f;
				//}
				//else if (GetPlayer(0)->pos.x >= GetEnemy4(i)->pos.x)
				//{

				//	GetEnemy4(i)->pos.x += 1.0f;

				//}
				//if (GetPlayer(0)->pos.y <= GetEnemy4(i)->pos.y)
				//{

				//	GetEnemy4(i)->pos.y -= 1.0f;

				//}
				//else if (GetPlayer(0)->pos.y >= GetEnemy4(i)->pos.y)
				//{
				//	GetEnemy4(i)->pos.y += 1.0f;
				//}



				//// 画面外まで進んだ？
				//if (enemy4->pos.x < 0-TEXTURE_ENEMY4_SIZE_X/* - SCREEN_WIDTH*/)	// 自分の大きさを考慮して画面外か判定している
				//{
				//	enemy4->use = false;
				//	enemy4->pos.x = 700.0f;
				//}

				GetEnemy4(i)->enemy4pos_x = GetEnemy4(i)->pos.x;
				GetEnemy4(i)->enemy4pos_y = GetEnemy4(i)->pos.y;


				SetVertexEnemy4(i);	// 移動後の座標で頂点を設定
			}


			if (GetEnemy4(i)->effectflag4 == true)
			{
				SetEffect4(GetEnemy4(i)->pos, i);
			}
			if (GetEnemy4(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy4(i)->BBflag = false;
			}
			if (boss->use == true)
			{
				GetEnemy4(i)->use = false;
			}

		}



}





//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = enemy4Wk;				// エネミーのポインターを初期化

	if (enemy4->counter > 28)
	{


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{
			if (enemy4->use == true)			// 使用している状態なら描画する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, enemy4->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY4, enemy4->vertexWk_enemy4, sizeof(VERTEX_2D));
			}
		}

	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy4( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = &enemy4Wk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy4( no );

	// rhwの設定
	enemy4->vertexWk_enemy4[0].rhw =
	enemy4->vertexWk_enemy4[1].rhw =
	enemy4->vertexWk_enemy4[2].rhw =
	enemy4->vertexWk_enemy4[3].rhw = 1.0f;

	// 反射光の設定
	enemy4->vertexWk_enemy4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy4->vertexWk_enemy4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy4->vertexWk_enemy4[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY4, 0.0f);
	enemy4->vertexWk_enemy4[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY4);
	enemy4->vertexWk_enemy4[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY4, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY4);






	//enemy4->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy4->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy4->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy4->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy4( int no,int cntPattern )
{
	ENEMY4 *enemy4 = &enemy4Wk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY4;
	
	enemy4->vertexWk_enemy4[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy4->vertexWk_enemy4[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy4->vertexWk_enemy4[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy4->vertexWk_enemy4[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy4( int no )
{
	ENEMY4 *enemy4 = &enemy4Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy4->vertexWk_enemy4[0].vtx.x = enemy4->pos.x - cosf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[0].vtx.y = enemy4->pos.y - sinf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[0].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[1].vtx.x = enemy4->pos.x + cosf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[1].vtx.y = enemy4->pos.y - sinf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[1].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[2].vtx.x = enemy4->pos.x - cosf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[2].vtx.y = enemy4->pos.y + sinf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[2].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[3].vtx.x = enemy4->pos.x + cosf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[3].vtx.y = enemy4->pos.y + sinf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY4 *GetEnemy4(int no)
{

	
	return(&enemy4Wk[no]);



}


