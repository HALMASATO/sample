
//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "boss.h"
#include "Ebullet.h"
#include "player.h"
//#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEBullet( int no );
void SetTextureEBullet( int no, int cntPattern );
void SetVertexEBullet( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEBullet = NULL;		// テクスチャへのポリゴン

EBULLET					EbulletWk[EBULLET_MAX];			// バレット構造体

///* static*/ LPDIRECTSOUNDBUFFER8	g_p1SE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &EbulletWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EBULLET,			// ファイルの名前
			&g_pD3DTextureEBullet);			// 読み込むメモリのポインタ
		
		//g_p1SE = LoadSound(SE_00);

	}

	// バレットの初期化処理
	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		ebullet->use = false;									// 未使用（発射されていない弾）
		ebullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		ebullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		ebullet->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		ebullet->CountAnim = 0;									// アニメカウントを初期化
		ebullet->counter = 0;
		ebullet->Bcounter_ORG=0;

		ebullet->Texture = g_pD3DTextureEBullet;					// テクスチャ情報
		MakeVertexEBullet(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEBullet(void)
{
	if (g_pD3DTextureEBullet != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEBullet->Release();
		g_pD3DTextureEBullet = NULL;
	}

	//if (g_p1SE != NULL)
	//{	// テクスチャの開放
	//	g_p1SE->Release();
	//	g_p1SE = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEBullet(void)
{
	EBULLET *ebullet = GetEBullet(0);				// バレットのポインターを初期化
	BOSS*boss = GetBoss(0);						//ボスのポインターを初期化
	PLAYER*player = GetPlayer(0);

	


	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		if (ebullet->use == true)			// 使用している状態なら更新する
		{
			// バレットの移動処理
			GetEBullet(i)->pos.x -= GetEBullet(i)->SPPED_X;
			GetEBullet(i)->pos.y -= GetEBullet(i)->SPPED_Y;


			//アニメーション
			ebullet->CountAnim++;
			if ((ebullet->CountAnim % TIME_ANIMATION_EBULLET) == 0)
			{
				// パターンの切り替え
				ebullet->PatternAnim = (ebullet->PatternAnim + 1) % ANIM_PATTERN_NUM_EBULLET;
				// テクスチャ座標を設定
				SetTextureEBullet(i, ebullet->PatternAnim);
			}

			// 画面外まで進んだ？
			if (GetEBullet(i)->pos.x < TEXTURE_EBULLET_SIZE_X - SCREEN_WIDTH)	// 自分の大きさを考慮して画面外か判定している
			{
				ebullet->use = false;
				ebullet->pos.x = 100.0f;
			}

			SetVertexEBullet(i);				// 移動後の座標で頂点を設定

		}
	}
	


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = EbulletWk;				// バレットのポインターを初期化
	BOSS*boss = GetBoss(0);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


		for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
		{
			if (ebullet->use == true)			// 使用している状態なら更新する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, ebullet->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EBULLET, ebullet->vertexWk, sizeof(VERTEX_2D));
			}
		}
	

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEBullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &EbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexEBullet( no );

	// rhwの設定
	ebullet->vertexWk[0].rhw =
	ebullet->vertexWk[1].rhw =
	ebullet->vertexWk[2].rhw =
	ebullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	ebullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	ebullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ebullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET, 0.0f);
	ebullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET);
	ebullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EBULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EBULLET);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEBullet( int no, int cntPattern )
{
	EBULLET *ebullet = &EbulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET;
	
	ebullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ebullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ebullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ebullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEBullet( int no )
{
	EBULLET *ebullet = &EbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	ebullet->vertexWk[0].vtx.x = ebullet->pos.x - TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[0].vtx.y = ebullet->pos.y - TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[0].vtx.z = 0.0f;

	ebullet->vertexWk[1].vtx.x = ebullet->pos.x + TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[1].vtx.y = ebullet->pos.y - TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[1].vtx.z = 0.0f;

	ebullet->vertexWk[2].vtx.x = ebullet->pos.x - TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[2].vtx.y = ebullet->pos.y + TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[2].vtx.z = 0.0f;

	ebullet->vertexWk[3].vtx.x = ebullet->pos.x + TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[3].vtx.y = ebullet->pos.y + TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[3].vtx.z = 0.0f;
}

////=============================================================================
//// テクスチャ座標の設定
////=============================================================================
//void SetTextureEBullet(int no,int cntPattern)
//{
//	EBULLET *ebullet = &EbulletWk[no];			// バレットのポインターを初期化
//
//
//	// テクスチャ座標の設定
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET;
//
//	ebullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	ebullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	ebullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	ebullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//
//
//}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEBullet(D3DXVECTOR3 pos)
{
		EBULLET *ebullet = GetEBullet(0);			// バレットのポインターを初期化
		PLAYER*player = GetPlayer(0);

		float	SPEED = 0;

			// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
			for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
			{
				if (GetEBullet(i)->use == false)			// 未使用状態のバレットを見つける
				{
					GetEBullet(i)->use = true;			// 使用状態へ変更する
					GetEBullet(i)->pos = pos;				// 座標をセット


					GetEBullet(i)->dis = player->pos - pos;
					bool ZetFlag = false;

					if (GetEBullet(i)->dis.y < 0)
					{
						GetEBullet(i)->dis.y *= (-1);
						ZetFlag = true;
					}

					if (GetEBullet(i)->dis.x < GetEBullet(i)->dis.y)
					{
						SPEED = GetEBullet(i)->dis.y / EBULLET_SPEED;
					}
					else
					{
						SPEED = GetEBullet(i)->dis.x / EBULLET_SPEED;
					}
					if (ZetFlag == true)
					{
						GetEBullet(i)->dis.y *= (-1);
						ZetFlag = false;
					}

					GetEBullet(i)->SPPED_Y = GetEBullet(i)->dis.y / SPEED;
					GetEBullet(i)->SPPED_X = GetEBullet(i)->dis.x / SPEED;





					ebullet->pos.x -= (TEXTURE_BOSS_SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

					// 発射音再生
					//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

					return;							// 1発セットしたので終了する
				}
			}
}
//=============================================================================
// エネミー取得関数
//=============================================================================
EBULLET *GetEBullet(int no)
{
	return(&EbulletWk[no]);
}

