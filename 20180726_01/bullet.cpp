
//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bullet.h"
#include "target.h"
//#include "sound.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet( int no );
void SetTextureBullet( int no, int cntPattern );
void SetVertexBullet( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet = NULL;		// テクスチャへのポリゴン

BULLET					bulletWk[BULLET_MAX];			// バレット構造体

//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BULLET,			// ファイルの名前
			&g_pD3DTextureBullet);			// 読み込むメモリのポインタ
		
		//g_pSE = LoadSound(SE_00);

	}


	// バレットの初期化処理
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->use = false;									// 未使用（発射されていない弾）
		bullet->BBflag = false;									//ターゲットに当たるとtrue
		bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->dis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		bullet->CountAnim = 0;									// アニメカウントを初期化
		bullet->BM = 0;
		bullet->counter = 0;
		bullet->reload = 0;
		bullet->MAXreload = bullet->reload;

		bullet->Texture = g_pD3DTextureBullet;					// テクスチャ情報
		MakeVertexBullet(i);									// 頂点情報の作成
		bullet->BaseAngle = atan2f(TEXTURE_BULLET_SIZE_Y, TEXTURE_BULLET_SIZE_X);	// エネミーの角度を初期化

	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	if (g_pD3DTextureBullet != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBullet->Release();
		g_pD3DTextureBullet = NULL;
	}



	//if (g_pSE != NULL)
	//{	// テクスチャの開放
	//	g_pSE->Release();
	//	g_pSE = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	BULLET *bullet = bulletWk;				// バレットのポインターを初期化
	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	TARGET*target = GetTarget(0);
	PLAYER*player = GetPlayer(0);

	float i = 0;

	//GetBullet(0)->pos.x = i;
	//i++;
	
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// 使用している状態なら更新する
		{

			bullet->pos.x += bullet->SPPED_X;
			bullet->pos.y += bullet->SPPED_Y;

			
			// 画面外まで進んだ？
			if (GetBullet(i)->pos.x > SCREEN_WIDTH -TEXTURE_BULLET_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
			{
				bullet->use = false;
				bullet->pos.x = -100.0f;
			}

			if (GetBullet(i)->pos.x < 0 - TEXTURE_BULLET_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
			{
				GetBullet(i)->use = false;
				bullet->pos.x = -100.0f;
			}


			SetVertexBullet(i);				// 移動後の座標で頂点を設定
		}

		if (bullet->use == false)
		{

			bullet->BBflag = false;

		}
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = bulletWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bullet->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexBullet( no );

	// rhwの設定
	bullet->vertexWk[0].rhw =
	bullet->vertexWk[1].rhw =
	bullet->vertexWk[2].rhw =
	bullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET, 0.0f);
	bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET);
	bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet( int no, int cntPattern )
{
	BULLET *bullet = &bulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET;
	
	bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet( int no )
{
	BULLET *bullet = &bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	bullet->vertexWk[0].vtx.x = bullet->pos.x - TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[0].vtx.y = bullet->pos.y - TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[0].vtx.z = 0.0f;

	bullet->vertexWk[1].vtx.x = bullet->pos.x + TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[1].vtx.y = bullet->pos.y - TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[1].vtx.z = 0.0f;

	bullet->vertexWk[2].vtx.x = bullet->pos.x - TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[2].vtx.y = bullet->pos.y + TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[2].vtx.z = 0.0f;

	bullet->vertexWk[3].vtx.x = bullet->pos.x + TEXTURE_BULLET_SIZE_X;
	bullet->vertexWk[3].vtx.y = bullet->pos.y + TEXTURE_BULLET_SIZE_Y;
	bullet->vertexWk[3].vtx.z = 0.0f;


		// 頂点座標の設定
	//bullet->vertexWk[0].vtx.x = bullet->pos.x - cosf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[0].vtx.y = bullet->pos.y - sinf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[0].vtx.z = 0.0f;

	//bullet->vertexWk[1].vtx.x = bullet->pos.x + cosf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[1].vtx.y = bullet->pos.y - sinf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[1].vtx.z = 0.0f;

	//bullet->vertexWk[2].vtx.x = bullet->pos.x - cosf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[2].vtx.y = bullet->pos.y + sinf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[2].vtx.z = 0.0f;

	//bullet->vertexWk[3].vtx.x = bullet->pos.x + cosf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[3].vtx.y = bullet->pos.y + sinf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	//bullet->vertexWk[3].vtx.z = 0.0f;



}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos)
{
		BULLET *bullet = &bulletWk[0];			// バレットのポインターを初期化
		PLAYER*player = GetPlayer(0);
		TARGET*target = GetTarget(0);

		float	SPEED=0;

			// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
			for (int i = 0; i < BULLET_MAX; i++, bullet++)
			{
				if (bullet->use == false)			// 未使用状態のバレットを見つける
				{
					bullet->use = true;				// 使用状態へ変更する
					bullet->pos = pos;				// 座標をセット

					bullet->dis = target->pos - pos;
					bool ZetFlag_Y = false;
					bool ZetFlag_X = false;


					if (bullet->dis.y < 0)
					{
						bullet->dis.y *= (-1);
						ZetFlag_Y = true;
					}

					if (bullet->dis.x < 0)
					{
						bullet->dis.x *= (-1);
						ZetFlag_X = true;
					}

					if (bullet->dis.x < bullet->dis.y)
					{
						SPEED = bullet->dis.y / BULLET_SPEED;
					}
					else
					{
						SPEED = bullet->dis.x / BULLET_SPEED;
					}

					if (ZetFlag_Y == true)
					{
						bullet->dis.y *= (-1);
						ZetFlag_Y = false;
					}

					if (ZetFlag_X == true)
					{
						bullet->dis.x *= (-1);
						ZetFlag_X = false;
					}

					GetBullet(i)->SPPED_Y = bullet->dis.y / SPEED;
					GetBullet(i)->SPPED_X = bullet->dis.x / SPEED;



					//}


						//GetBullet(i)->SPPED_X = (target->pos.x - pos.x) / GetBullet(i)->SPPED_X;
					

		
					// 発射音再生
					//PlaySound(g_pSE, E_DS8_FLAG_NONE);

					return;							// 1発セットしたので終了する


				}


			}
		
	
}



//=============================================================================
// エネミー取得関数
//=============================================================================
BULLET *GetBullet(int no)
{
	return(&bulletWk[no]);
}

