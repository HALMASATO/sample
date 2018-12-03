
//=============================================================================
//
// バレット処理 [bullet2.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bullet2.h"
#include "target.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet2( int no );
void SetTextureBullet2( int no, int cntPattern );
void SetVertexBullet2( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet2 = NULL;		// テクスチャへのポリゴン

BULLET2					bullet2Wk[BULLET2_MAX];			// バレット構造体

//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = &bullet2Wk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BULLET2,			// ファイルの名前
			&g_pD3DTextureBullet2);			// 読み込むメモリのポインタ
		
		//g_pSE = LoadSound(SE_00);

	}


	// バレットの初期化処理
	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		bullet2->use = false;									// 未使用（発射されていない弾）
		bullet2->BBflag = false;									//ターゲットに当たるとtrue
		bullet2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		bullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		bullet2->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		bullet2->CountAnim = 0;									// アニメカウントを初期化
		bullet2->HP = 2;


		bullet2->Texture = g_pD3DTextureBullet2;					// テクスチャ情報
		MakeVertexBullet2(i);									// 頂点情報の作成
		bullet2->BaseAngle = atan2f(TEXTURE_BULLET2_SIZE_Y, TEXTURE_BULLET2_SIZE_X);	// エネミーの角度を初期化

	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet2(void)
{
	if (g_pD3DTextureBullet2 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBullet2->Release();
		g_pD3DTextureBullet2 = NULL;
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
void UpdateBullet2(void)
{
	BULLET2 *bullet2 = bullet2Wk;				// バレットのポインターを初期化
	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	TARGET*target = GetTarget(0);
	PLAYER*player = GetPlayer(0);

	float i = 0;

	
	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		if (bullet2->use == true)			// 使用している状態なら更新する
		{

				bullet2->pos.x += 3;

			// 画面外まで進んだ？
			if (GetBullet2(i)->pos.x > SCREEN_WIDTH -TEXTURE_BULLET2_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
			{
				bullet2->use = false;
				bullet2->pos.x = -100.0f;
			}

			SetVertexBullet2(i);				// 移動後の座標で頂点を設定
		}

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = bullet2Wk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		if (bullet2->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bullet2->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET2, bullet2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet2( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = &bullet2Wk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexBullet2( no );

	// rhwの設定
	bullet2->vertexWk[0].rhw =
	bullet2->vertexWk[1].rhw =
	bullet2->vertexWk[2].rhw =
	bullet2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET2, 0.0f);
	bullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET2);
	bullet2->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BULLET2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET2);

	//bullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet2( int no, int cntPattern )
{
	BULLET2 *bullet2 = &bullet2Wk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET2;
	
	bullet2->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet2->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet2->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet2->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet2( int no )
{
	BULLET2 *bullet2 = &bullet2Wk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	bullet2->vertexWk[0].vtx.x = bullet2->pos.x - TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[0].vtx.y = bullet2->pos.y - TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[0].vtx.z = 0.0f;

	bullet2->vertexWk[1].vtx.x = bullet2->pos.x + TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[1].vtx.y = bullet2->pos.y - TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[1].vtx.z = 0.0f;

	bullet2->vertexWk[2].vtx.x = bullet2->pos.x - TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[2].vtx.y = bullet2->pos.y + TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[2].vtx.z = 0.0f;

	bullet2->vertexWk[3].vtx.x = bullet2->pos.x + TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[3].vtx.y = bullet2->pos.y + TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[3].vtx.z = 0.0f;


		// 頂点座標の設定
	//bullet2->vertexWk[0].vtx.x = bullet2->pos.x - cosf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[0].vtx.y = bullet2->pos.y - sinf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[0].vtx.z = 0.0f;

	//bullet2->vertexWk[1].vtx.x = bullet2->pos.x + cosf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[1].vtx.y = bullet2->pos.y - sinf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[1].vtx.z = 0.0f;

	//bullet2->vertexWk[2].vtx.x = bullet2->pos.x - cosf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[2].vtx.y = bullet2->pos.y + sinf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[2].vtx.z = 0.0f;

	//bullet2->vertexWk[3].vtx.x = bullet2->pos.x + cosf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[3].vtx.y = bullet2->pos.y + sinf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[3].vtx.z = 0.0f;



}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet2(D3DXVECTOR3 pos)
{
		BULLET2 *bullet2 = &bullet2Wk[0];			// バレットのポインターを初期化

			// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
			for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
			{
				if (bullet2->use == false)			// 未使用状態のバレットを見つける
				{
					bullet2->use = true;				// 使用状態へ変更する
					bullet2->pos = pos;				// 座標をセット

					// 発射音再生
					//PlaySound(g_pSE, E_DS8_FLAG_NONE);

					return;							// 1発セットしたので終了する
				}
			}
}



//=============================================================================
// エネミー取得関数
//=============================================================================
BULLET2 *GetBullet2(int no)
{
	return(&bullet2Wk[no]);
}

