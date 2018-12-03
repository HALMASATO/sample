//=============================================================================
//
// 敵処理 [bosseffect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bosseffect.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBossEffect( int no);
void SetTextureBossEffect( int no,int cntPattern );
void SetVertexBossEffect( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBossEffect = NULL;		// テクスチャへのポリゴン


BOSSEFFECT					bosseffectWk[BOSSEFFECT_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBossEffect(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = bosseffectWk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BOSSEFFECT,				// ファイルの名前
			&g_pD3DTextureBossEffect);			// 読み込むメモリのポインタ


	}



	 //エネミーの初期化処理
	for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
	{
		bosseffect->use = false;										// 使用
		bosseffect->pos = D3DXVECTOR3(i*50+bosseffect->InitY,50.0f, 0.0f);		// 座標データを初期化
		bosseffect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		bosseffect->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		bosseffect->CountAnim = 0;									// アニメカウントを初期化
		bosseffect->bosseffectcounter = 0;								//エフェクトカウンター
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSSEFFECT_SIZE_X, TEXTURE_BOSSEFFECT_SIZE_Y);
		bosseffect->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		bosseffect->BaseAngle = atan2f(TEXTURE_BOSSEFFECT_SIZE_Y, TEXTURE_BOSSEFFECT_SIZE_X);	// エネミーの角度を初期化

		bosseffect->Texture = g_pD3DTextureBossEffect;					// テクスチャ情報
		MakeVertexBossEffect(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBossEffect(void)
{
	if (g_pD3DTextureBossEffect != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBossEffect->Release();
		g_pD3DTextureBossEffect = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBossEffect(void)
{
	BOSSEFFECT *bosseffect = bosseffectWk;				// エネミーのポインターを初期化
	BOSS *boss = GetBoss(0);							// ボスのポインターを初期化


	if (bosseffect->use == true)			// 使用している状態なら更新する
	{

		//アニメーション
		bosseffect->CountAnim++;
		if ((bosseffect->CountAnim % TIME_ANIMATION_BOSSEFFECT) == 0)
		{
			if (ANIM_PATTERN_NUM_BOSSEFFECT - 1 > bosseffect->PatternAnim)
			{
				// パターンの切り替え
				bosseffect->PatternAnim = (bosseffect->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSSEFFECT;


			}
			else
			{
				bosseffect->use = false;
				bosseffect->PatternAnim = 0;
				GetBoss(bosseffect->i)->effectflag= false;
			}
			

			// テクスチャ座標を設定
			SetTextureBossEffect(0, bosseffect->PatternAnim);


			SetVertexBossEffect(0);	// 移動後の座標で頂点を設定


		}
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawBossEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = bosseffectWk;				// エネミーのポインターを初期化


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
		//{
			if (bosseffect->use == true)			// 使用している状態なら描画する
			{
				//if (bosseffect->counter > 0)
				//{
					// テクスチャの設定
					pDevice->SetTexture(0, bosseffect->Texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSEFFECT, bosseffect->vertexWk_bosseffect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBossEffect( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// エネミーのポインターを初期化


	// 頂点座標の設定
	SetVertexBossEffect( no );

	// rhwの設定
	bosseffect->vertexWk_bosseffect[0].rhw =
	bosseffect->vertexWk_bosseffect[1].rhw =
	bosseffect->vertexWk_bosseffect[2].rhw =
	bosseffect->vertexWk_bosseffect[3].rhw = 1.0f;

	// 反射光の設定
	bosseffect->vertexWk_bosseffect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bosseffect->vertexWk_bosseffect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bosseffect->vertexWk_bosseffect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT, 0.0f);
	bosseffect->vertexWk_bosseffect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT);
	bosseffect->vertexWk_bosseffect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT);






	//bosseffect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bosseffect->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bosseffect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bosseffect->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBossEffect( int no,int cntPattern )
{
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// エネミーのポインターを初期化


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT;
	
	bosseffect->vertexWk_bosseffect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bosseffect->vertexWk_bosseffect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bosseffect->vertexWk_bosseffect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bosseffect->vertexWk_bosseffect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBossEffect( int no )
{
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	bosseffect->vertexWk_bosseffect[0].vtx.x = bosseffect->pos.x - cosf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[0].vtx.y = bosseffect->pos.y - sinf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[0].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[1].vtx.x = bosseffect->pos.x + cosf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[1].vtx.y = bosseffect->pos.y - sinf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[1].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[2].vtx.x = bosseffect->pos.x - cosf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[2].vtx.y = bosseffect->pos.y + sinf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[2].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[3].vtx.x = bosseffect->pos.x + cosf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[3].vtx.y = bosseffect->pos.y + sinf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[3].vtx.z = 0.0f;
}
//=============================================================================
// エフェクトの発生設定
//=============================================================================
void SetBossEffect(D3DXVECTOR3 pos, int i)
{
	BOSSEFFECT *bosseffect = &bosseffectWk[0];			// バレットのポインターを初期化


		// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	//for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
	//{
		if (bosseffect->use == false)			// 未使用状態のバレットを見つける
		{
			bosseffect->use = true;				// 使用状態へ変更する
			bosseffect->pos = pos;				// 座標をセット
			bosseffect->i = i;


			// 発射音再生
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する


		}


	//}


}




//=============================================================================
// エネミー取得関数
//=============================================================================
BOSSEFFECT *GetBossEffect(int no)
{

	
	return(&bosseffectWk[no]);



}


