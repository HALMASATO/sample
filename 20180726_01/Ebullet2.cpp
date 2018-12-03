
//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy6.h"
#include "Ebullet2.h"
#include "player.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEBullet2( int no );
void SetTextureEBullet2( int no, int cntPattern );
void SetVertexEBullet2( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEBullet2 = NULL;		// テクスチャへのポリゴン

EBULLET2					EbulletWk[EBULLET2_MAX];			// バレット構造体

 //static LPDIRECTSOUNDBUFFER8	g_p1SE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEBullet2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = &EbulletWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_EBULLET2,			// ファイルの名前
			&g_pD3DTextureEBullet2);			// 読み込むメモリのポインタ
		
		//g_p1SE = LoadSound(SE_00);

	}

	// バレットの初期化処理
	for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
	{
		ebullet2->use = false;									// 未使用（発射されていない弾）
		ebullet2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		ebullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		ebullet2->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		ebullet2->CountAnim = 0;									// アニメカウントを初期化
		ebullet2->counter = 0;
		ebullet2->Bcounter_ORG=0;

		ebullet2->Texture = g_pD3DTextureEBullet2;					// テクスチャ情報
		MakeVertexEBullet2(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEBullet2(void)
{
	if (g_pD3DTextureEBullet2 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEBullet2->Release();
		g_pD3DTextureEBullet2 = NULL;
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
void UpdateEBullet2(void)
{
	EBULLET2 *ebullet2 = GetEBullet2(0);				// バレットのポインターを初期化
	BOSS*boss = GetBoss(0);						//ボスのポインターを初期化
	PLAYER*player = GetPlayer(0);

	


	for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
	{
		if (ebullet2->use == true)			// 使用している状態なら更新する
		{
			//// バレットの移動処理
			//GetEBullet2(i)->pos.x -= GetEBullet2(i)->SPPED_X;
			//GetEBullet2(i)->pos.y -= GetEBullet2(i)->SPPED_Y;

			GetEBullet2(i)->pos.x -= 5.0f;


			////アニメーション
			//ebullet2->CountAnim++;
			//if ((ebullet2->CountAnim % TIME_ANIMATION_EBULLET2) == 0)
			//{
			//	// パターンの切り替え
			//	ebullet2->PatternAnim = (ebullet2->PatternAnim + 1) % ANIM_PATTERN_NUM_EBULLET2;
			//	// テクスチャ座標を設定
			//	SetTextureEBullet2(i, ebullet2->PatternAnim);
			//}

			// 画面外まで進んだ？
			if (GetEBullet2(i)->pos.x < TEXTURE_EBULLET2_SIZE_X - SCREEN_WIDTH)	// 自分の大きさを考慮して画面外か判定している
			{
				ebullet2->use = false;
				ebullet2->pos.x = 100.0f;
			}

			SetVertexEBullet2(i);				// 移動後の座標で頂点を設定

			if (boss->use == true)
			{

				GetEBullet2(i)->use = false;

			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEBullet2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = EbulletWk;				// バレットのポインターを初期化
	//BOSS*boss = GetBoss(0);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


		for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
		{
			if (ebullet2->use == true)			// 使用している状態なら更新する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, ebullet2->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EBULLET2, ebullet2->vertexWk, sizeof(VERTEX_2D));
			}
		}
	

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEBullet2( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = &EbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexEBullet2( no );

	// rhwの設定
	ebullet2->vertexWk[0].rhw =
	ebullet2->vertexWk[1].rhw =
	ebullet2->vertexWk[2].rhw =
	ebullet2->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	ebullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	ebullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ebullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2, 0.0f);
	ebullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2);
	ebullet2->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EBULLET2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EBULLET2);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEBullet2( int no, int cntPattern )
{
	EBULLET2 *ebullet2 = &EbulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2;
	
	ebullet2->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ebullet2->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ebullet2->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ebullet2->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEBullet2( int no )
{
	EBULLET2 *ebullet2 = &EbulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	ebullet2->vertexWk[0].vtx.x = ebullet2->pos.x - TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[0].vtx.y = ebullet2->pos.y - TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[0].vtx.z = 0.0f;

	ebullet2->vertexWk[1].vtx.x = ebullet2->pos.x + TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[1].vtx.y = ebullet2->pos.y - TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[1].vtx.z = 0.0f;

	ebullet2->vertexWk[2].vtx.x = ebullet2->pos.x - TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[2].vtx.y = ebullet2->pos.y + TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[2].vtx.z = 0.0f;

	ebullet2->vertexWk[3].vtx.x = ebullet2->pos.x + TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[3].vtx.y = ebullet2->pos.y + TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[3].vtx.z = 0.0f;
}

////=============================================================================
//// テクスチャ座標の設定
////=============================================================================
//void SetTextureEBullet2(int no,int cntPattern)
//{
//	EBULLET2 *ebullet2 = &EbulletWk[no];			// バレットのポインターを初期化
//
//
//	// テクスチャ座標の設定
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2;
//
//	ebullet2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	ebullet2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	ebullet2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	ebullet2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//
//
//}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetEBullet2(D3DXVECTOR3 pos)
{
		EBULLET2 *ebullet2 = GetEBullet2(0);			// バレットのポインターを初期化
		PLAYER*player = GetPlayer(0);

		float	SPEED = 0;

			// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
			for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
			{
				if (GetEBullet2(i)->use == false)			// 未使用状態のバレットを見つける
				{
					GetEBullet2(i)->use = true;			// 使用状態へ変更する
					GetEBullet2(i)->pos = pos;				// 座標をセット


					//GetEBullet2(i)->dis = player->pos - pos;
					//bool ZetFlag = false;

					//if (GetEBullet2(i)->dis.y < 0)
					//{
					//	GetEBullet2(i)->dis.y *= (-1);
					//	ZetFlag = true;
					//}

					//if (GetEBullet2(i)->dis.x < GetEBullet2(i)->dis.y)
					//{
					//	SPEED = GetEBullet2(i)->dis.y / EBULLET2_SPEED;
					//}
					//else
					//{
					//	SPEED = GetEBullet2(i)->dis.x / EBULLET2_SPEED;
					//}
					//if (ZetFlag == true)
					//{
					//	GetEBullet2(i)->dis.y *= (-1);
					//	ZetFlag = false;
					//}

					//GetEBullet2(i)->SPPED_Y = GetEBullet2(i)->dis.y / SPEED;
					//GetEBullet2(i)->SPPED_X = GetEBullet2(i)->dis.x / SPEED;





					ebullet2->pos.x -= (TEXTURE_ENEMY6_SIZE_X / 2) + (TEXTURE_EBULLET2_SIZE_X / 2);

					// 発射音再生
					//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

					return;							// 1発セットしたので終了する
				}
			}
}
//=============================================================================
// エネミー取得関数
//=============================================================================
EBULLET2 *GetEBullet2(int no)
{
	return(&EbulletWk[no]);
}

