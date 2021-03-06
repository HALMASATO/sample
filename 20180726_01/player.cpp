//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include "bullet.h"
#include "target.h"
#include "bullet2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );
HRESULT InitMakeVertexPlayer(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// テクスチャへのポリゴン

PLAYER					playerWk[PLAYER_MAX];			// プレイヤー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_PLAYER,				// ファイルの名前
			&g_pD3DTexturePlayer);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;	
		player->yoko = false;
		player->tate = false;
		player->pos = D3DXVECTOR3(i*50.0f+100.0f, 300.0f, 0.0f);	// 座標データを初期化
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
		player->PatternAnim = rand() % ANIM_PATTERN_NUM_PLAYER;	// アニメパターン番号をランダムで初期化
		player->CountAnim = 0;								// アニメカウントを初期化
		player->HP = 80;
		player->i = 2;
		player->MAXHP = player->HP;
		player->counter = 80;
		player->Bcounter = 50;
		player->MAXBcounter = player->Bcounter;
		player->MAXcounter = player->counter;
		player->drawflug = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		player->Radius = D3DXVec2Length(&temp);				// プレイヤーの半径を初期化
		player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// プレイヤーの角度を初期化



		player->Texture = g_pD3DTexturePlayer;				// テクスチャ情報
		MakeVertexPlayer(i);								// 頂点情報の作成
		//InitMakeVertexPlayer(i);


	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

	if (g_pD3DTexturePlayer != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	TARGET *target = GetTarget(0);



	if (player->Timecounter > 6)
	{
		player->Hitcounter=0;
		player->Timecounter = 0;

	}




	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (GetPlayer(i)->use == true)
		{
			// アニメーション
			GetPlayer(i)->CountAnim++;
			if ((GetPlayer(i)->CountAnim % TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				GetPlayer(i)->PatternAnim = (GetPlayer(i)->PatternAnim + 1) % ANIM_PATTERN_NUM_PLAYER;

				// テクスチャ座標を設定
				SetTexturePlayer(i, GetPlayer(i)->PatternAnim);
			}


			// キーボード入力で移動(ひとまず全プレイヤーを同じキーで動かしちゃう)
			//下移動
			if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
			{
				player->pos.y += PLAYER_SPEED;
				player->tate = true;
				player->yoko = false;
				player->i = 3;


			}

			//左移動
			else if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))
			{
				player->pos.x -= PLAYER_SPEED;

				player->i = 3;
				player->Xmuki = true;
				player->yoko = true;
				player->tate = false;

			}

			//上移動
			if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP))
			{

				player->pos.y -= PLAYER_SPEED;
				player->tate = true;
				player->yoko = false;
				player->i = 2;

			}

			//右移動
			if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->pos.x += PLAYER_SPEED;
				player->i = 2;
				player->yoko = true;
				player->tate = false;
				player->Xmuki = false;


			}


			//右向いてるとき
			if (player->Xmuki == false)
			{


				//移動
				if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y -= PLAYER_SPEED;
					player->i = 2;

				}

				if (GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y += PLAYER_SPEED;
					player->i = 2;

				}

			}


			//左向いてるとき
			if (player->Xmuki == true)
			{
				//移動
				if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y -= PLAYER_SPEED;
					player->i = 3;

				}

				if (GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y += PLAYER_SPEED;
					player->i = 2;

				}


				

			}



			//if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
			//{

			//	player->pos.y -= 3.0f;e
			//	player->i = 2;

			//}








			//画面外に出ない処理
			if (player->pos.x < 25)
			{

				player->pos.x = 25;

			}

			if (player->pos.x > 777)
			{

				player->pos.x = 777;

			}

			if (player->pos.y < 45)
			{

				player->pos.y = 45;

			}

			if (player->pos.y > 408)
			{

				player->pos.y = 408;

			}




			//// 回転
			//if (GetKeyboardPress(DIK_RIGHT))
			//{
			//	player->rot.z += 0.1f;
			//}

			//if (GetKeyboardPress(DIK_LEFT))
			//{
			//	player->rot.z -= 0.1f;
			//}



			// 拡大縮小
			if (GetKeyboardPress(DIK_F))
			{
				player->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player->Radius += 1.0f;
			}







			// 弾発射
			else if (GetKeyboardTrigger(DIK_SPACE) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Y) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Z) || IsButtonTriggered(0, BUTTON_L) || IsButtonTriggered(0, BUTTON_R))
			{

				D3DXVECTOR3 pos = player->pos;


				if (player->yoko == true)
				{
					pos.x += TEXTURE_PLAYER_SIZE_X;

				}

				if (player->tate == true)
				{

					pos.y -= TEXTURE_PLAYER_SIZE_Y;

				}

					SetBullet(pos);
					bullet->BM += 1;

			}

			//// 弾発射
			//else if (IsButtonPressed(0, BUTTON_B) && bullet->reload == 0)
			//{

			//	if (target->rockflug == true)
			//	{
			//		D3DXVECTOR3 pos = player->pos;
			//		pos.x += TEXTURE_PLAYER_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER_SIZE_Y;
			//		SetBullet(pos);
			//		bullet->BM += 1;
			//	}

			//}



			//if (GetKeyboardTrigger(DIK_Z))
			//{

			//	//if (target->rockflug == true)
			//	//{
			//		D3DXVECTOR3 pos = player->pos;
			//		pos.x += TEXTURE_PLAYER_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER_SIZE_Y;
			//		SetBullet2(pos);
			//	//}

			//}


			//else if (IsButtonTriggered(0, BUTTON_B))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}
			//リロードタイムの調整

			if (bullet->reload == 5)
			{
				bullet->BM = 0;
				bullet->reload = 0;

			}



			// 移動後の座標で頂点を設定
			SetVertexPlayer(i);
			//MakeVertexPlayer(i);								// 頂点情報の作成


		}
		
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];


	for (int i = 0; i < player->Timecounter; i++)
	{
		switch (player->Timecounter)
		{
		case 1:
			player->drawflug = true;
			break;

		case 2:
			player->drawflug = false;
			break;

		case 3:
			player->drawflug = true;
			break;

		case 4:
			player->drawflug = false;
			break;

		case 5:
			player->drawflug = true;
			break;

		case 6:
			player->drawflug = false;
			break;

		default:
			break;
		}
	}


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// 使用している状態なら描画する
		{
			if (player->drawflug == false)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, player->Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));

			}

		}
	}

}


//=============================================================================
// 初期状態の頂点の作成
//=============================================================================
HRESULT InitMakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);

	return S_OK;


}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// 頂点座標の設定
	SetVertexPlayer(no);

	// rhwの設定
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;
	

	// 反射光の設定
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// テクスチャ座標の設定
	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);


	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];
	
	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER;

	switch (player->i)
	{
	case 1:
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;
		
	case 2:

			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	case 3:
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	case 4:
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	}


}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// 頂点座標の設定
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// プレイヤー取得関数
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

