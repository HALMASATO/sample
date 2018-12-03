//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy4.h"
#include "enemy2.h"
#include "input.h"
#include "effect2.h"
#include"boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy2( int no);
void SetTextureEnemy2( int no,int cntPattern );
void SetVertexEnemy2( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy2 = NULL;		// テクスチャへのポリゴン


ENEMY2					enemyWk2[ENEMY2_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY2 *enemy2 = enemyWk2;				// エネミーのポインターを初期化


	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY2,				// ファイルの名前
			&g_pD3DTextureEnemy2);			// 読み込むメモリのポインタ


	}

		// エネミーの初期化処理
		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{
			enemy2->use = false;										// 使用
			enemy2->effectflag2 = false;
			enemy2->BBflag = false;
			enemy2->comeback = false;
			enemy2->pos = D3DXVECTOR3(i * 80+100 + 100.0f, 0.0f, 0.0f);	// 座標データを初期化
			enemy2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			enemy2->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
			enemy2->CountAnim = 0;									// アニメカウントを初期化
			enemy2->counter = 0;

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y);
			enemy2->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
			enemy2->BaseAngle = atan2f(TEXTURE_ENEMY2_SIZE_Y, TEXTURE_ENEMY2_SIZE_X);	// エネミーの角度を初期化

			enemy2->Texture_enemy = g_pD3DTextureEnemy2;					// テクスチャ情報
			MakeVertexEnemy2(i);										// 頂点情報の作成
		}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy2(void)
{
	if (g_pD3DTextureEnemy2 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy2->Release();
		g_pD3DTextureEnemy2 = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;				// エネミーのポインターを初期化
	ENEMY4 *enemy4 = GetEnemy4(0);				// エネミーのポインターを初期化
	EFFECT2*effect2 = GetEffect2(0);
	BOSS*boss = GetBoss(0);
	int i = 0;

	if (GetEnemy2(i)->counter == 16)
	{
		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{

			GetEnemy2(i)->use = true;


		}
	}

	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{


		if (GetEnemy2(i)->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			GetEnemy2(i)->CountAnim++;
			if ((GetEnemy2(i)->CountAnim % TIME_ANIMATION_ENEMY2) == 0)
			{
				// パターンの切り替え
				GetEnemy2(i)->PatternAnim = (GetEnemy2(i)->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY2;

				// テクスチャ座標を設定
				SetTextureEnemy2(i, GetEnemy2(i)->PatternAnim);

			}


			if (GetEnemy2(i)->counter > 16 && GetEnemy2(i)->counter < 28)
			{
				GetEnemy2(i)->pos.y += 1.0f;
			}

			if (GetEnemy2(i)->counter > 28)/*&& GetEnemy3(i)->counter < )*/
			{
				GetEnemy2(i)->pos.x -= 1.0f;
			}


			GetEnemy2(i)->enemy2pos_x = GetEnemy2(i)->pos.x;
			GetEnemy2(i)->enemy2pos_y = GetEnemy2(i)->pos.y;



			if (GetEnemy2(i)->pos.x < 100)	// 自分の大きさを考慮して画面外か判定している
			{
				GetEnemy2(i)->use = false;
				GetEnemy2(i)->pos.x = 800.0f;
				GetEnemy2(i)->pos.y = 100.0f;
			}


			SetVertexEnemy2(i);	// 移動後の座標で頂点を設定

		}

		if (GetEnemy2(i)->effectflag2 == true)
		{
			SetEffect2(GetEnemy2(i)->pos, i);

		}

		if (GetEnemy2(i)->BBflag == true)
		{

			boss->Popcounter++;
			GetEnemy2(i)->BBflag = false;

		}

		//if (GetEnemy4(i)->counter > 32)
		//{

		//	GetEnemy2(i)->comeback = true;
		//	if (GetEnemy2(i)->comeback == true)
		//	{

		//		GetEnemy2(i)->use = true;

		//	}

		//}





	}

	

	if (boss->use == true)
	{

		enemy2->use = false;

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY2 *enemy2 = enemyWk2;				// エネミーのポインターを初期化


	if (enemy2->counter > 16)
	{


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{
			if (enemy2->use == true)			// 使用している状態なら描画する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, enemy2->Texture_enemy);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY2, enemy2->vertexWk_enemy, sizeof(VERTEX_2D));
			}
		}

	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy2( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexEnemy2( no );

	// rhwの設定
	enemy2->vertexWk_enemy[0].rhw =
	enemy2->vertexWk_enemy[1].rhw =
	enemy2->vertexWk_enemy[2].rhw =
	enemy2->vertexWk_enemy[3].rhw = 1.0f;

	// 反射光の設定
	enemy2->vertexWk_enemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy2->vertexWk_enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk_enemy[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 0.0f);
	enemy2->vertexWk_enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);
	enemy2->vertexWk_enemy[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);






	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy2( int no,int cntPattern )
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2;
	
	enemy2->vertexWk_enemy[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy2->vertexWk_enemy[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy2->vertexWk_enemy[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy2->vertexWk_enemy[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy2( int no )
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy2->vertexWk_enemy[0].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[0].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[0].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[1].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[1].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[1].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[2].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[2].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[2].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[3].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[3].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY2 *GetEnemy2(int no)
{

	
	return(&enemyWk2[no]);



}


