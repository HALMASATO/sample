//=============================================================================
//
// Main処理 [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
#include "enemy6.h"
#include "boss.h"
#include "bgage.h"
#include "effect.h"
#include "effect2.h"
#include "effect3.h"
#include "effect4.h"
#include "effect5.h"
#include "effect6.h"
#include "pgage.h"
#include "egage.h"
#include "bosseffect.h"
#include "bullet.h"
#include "Ebullet.h"
#include "Ebullet2.h"
#include "bg.h"
#include "captionbg.h"
#include "title.h"
#include "tgage.h"
#include "result3.h"
#include "score.h"
#include "target.h"
//#include "sound.h"
#include "bullet2.h"
#include"btgage.h"
#include <time.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// ウインドウのクラス名
#define WINDOW_NAME			_T("Alien species")		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void CheckHit(void);
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

void InitGame(void);

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

//#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// フォントへのポインタ
int						g_nCountFPS;				// FPSカウンタ
int						cnt = 0;							// 敵の数を数える

//#endif

int						g_nStage = 0;				// ステージ番号

//LPDIRECTSOUNDBUFFER8	g_pBGM;						// BGM用バッファ


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	ENEMY2 *enemy2 = GetEnemy2(0);			// エネミー2のポインターを初期化
	ENEMY3 *enemy3 = GetEnemy3(0);			// エネミー3のポインターを初期化
	ENEMY4 *enemy4 = GetEnemy4(0);			// エネミー4のポインターを初期化
	ENEMY5 *enemy5 = GetEnemy5(0);			// エネミー5のポインターを初期化
	ENEMY6 *enemy6 = GetEnemy6(0);			// エネミー6のポインターを初期化


	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	EBULLET*ebullet = GetEBullet(0);		//エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);			//プレイヤーのポインターを初期化
	EFFECT*effect = GetEffect(0);			//エフェクトのポインターを初期化
	BOSS*boss = GetBoss(0);
	LOGO*logo = GetLogo(0);
	TGAGE*tgage = GetTgage(0);				//タイムゲージのポインターを初期化


	
	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				//#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPSを測定
				
				logo->logo_counter++;


				if (g_nStage == STAGE_GAME)
				{


					enemy->counter++;
					//enemy3->counter++;


					for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
					{
						GetEnemy2(i)->counter++;
					}

					for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
					{
						GetEnemy3(i)->counter++;

					}

					for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
					{
						GetEnemy4(i)->counter++;

					}



					for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
					{

						GetEnemy5(i)->counter++;


						if (GetEnemy5(i)->use == true)
						{
							GetEnemy5(i)->Mcounter++;
						}
					}



					for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
					{
						GetEnemy6(i)->counter++;

					}





					if (effect->use == true)
					{
						effect->counter++;
					}

					if (boss->use == true)
					{
						boss->counter++;
						player->Bcounter--;
					}

					if (boss->use == false)
					{

						player->counter--;

					}

					if (player->Hitcounter > 0)
					{
						player->Timecounter++;				//無敵時間をつくりたい
					}

					if (boss->Hitcounter > 0)
					{
						boss->Timecounter++;				//無敵時間をつくりたい
					}


					if (bullet->use == true)
					{
						bullet->counter++;
					}



					if (bullet->BM >= 8)
					{
						bullet->reload++;						//リロード時間の制御
					}

					//if (enemy->counter > 28)
					//{
					//	enemy->comeback = true;
					//}


				}


					//boss->counter++;




	//#endif
					dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
					dwFrameCount = 0;							// カウントをクリア
				}



				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
				{
					dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存


					Update();			// 更新処理
					Draw();				// 描画処理



					dwFrameCount++;		// 処理回数のカウントを加算
				}
			}
		}
	

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定

	if(bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
									D3DDEVTYPE_HAL,								// ディスプレイタイプ
									hWnd,										// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
									&d3dpp,										// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

//#ifdef _DEBUG
																			// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
//#endif
	
	// サウンド初期化
	//InitSound(hWnd);
	// ロードと再生
	//g_pBGM = LoadSound(BGM_00);
	//PlaySound(g_pBGM, E_DS8_FLAG_LOOP);

	// プレイヤーの初期化処理
	InitPlayer(0);

	// プレイヤーの初期化処理
	InitPgage();

	// プレイヤーの初期化処理
	InitEgage();

	// プレイヤーの初期化処理
	InitTgage();

	// プレイヤーの初期化処理
	//InitBgage();

	// エネミーの初期化処理
	InitEnemy(0);

	// エネミーの初期化処理
	InitEnemy2(0);

	// エネミーの初期化処理
	InitEnemy3(0);

	// エネミーの初期化処理
	InitEnemy4(0);

	// エネミーの初期化処理
	InitEnemy5(0);

	// エネミーの初期化処理
	InitEnemy6(0);

	//ボスのエネミーの初期化
	InitBoss(0);

	// バレットの初期化処理
	InitBullet(0);

	// バレットの初期化処理
	InitBullet2(0);

	//エフェクトの初期化処理
	InitEffect(0);

	//エフェクトの初期化処理
	InitEffect2(0);

	//エフェクトの初期化処理
	InitEffect3(0);

	//ボスエフェクトの初期化
	InitBossEffect(0);

	//エフェクトの初期化処理
	InitEffect4(0);

	//エフェクトの初期化処理
	InitEffect5(0);

	//エフェクトの初期化処理
	InitEffect6(0);

	//エネミーバレットの初期化
	InitEBullet(0);

	//エネミーバレットの初期化
	InitEBullet2(0);

	//ターゲットの初期化
	InitTarget(0);

	//ターゲットの初期化
	InitBTgage();

	// BG初期化
	InitBG(0);

	// BG初期化
	InitCaptionBG(0);

	// タイトル初期化
	InitTitle();

	// リザルト初期化
	InitResult3();

	// スコア初期化
	InitScore(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 入力処理の終了処理
	UninitInput();

	// プレイヤーの終了処理
	UninitPlayer();

	// プレイヤーの終了処理
	UninitPgage();

	// プレイヤーの終了処理
	UninitEgage();

	// プレイヤーの終了処理
	UninitTgage();

	// プレイヤーの終了処理
	UninitBTgage();

	// プレイヤーの終了処理
	//UninitBgage();

	// エネミーの終了処理
	UninitEnemy();

	// エネミーの終了処理
	UninitEnemy2();

	// エネミーの終了処理
	UninitEnemy3();

	// エネミーの終了処理
	UninitEnemy4();

	// エネミーの終了処理
	UninitEnemy5();

	// エネミーの終了処理
	UninitEnemy6();

	//エフェクトの終了処理
	UninitEffect();

	//エフェクト2の終了処理
	UninitEffect2();

	//エフェクト2の終了処理
	UninitEffect3();

	//エフェクト2の終了処理
	UninitEffect4();

	//エフェクト2の終了処理
	UninitEffect5();
	
	//エフェクト2の終了処理
	UninitEffect6();

	//エフェクト2の終了処理
	UninitBossEffect();

	//ボスの終了処理
	UninitBoss();

	// バレットの終了処理
	UninitBullet();

	// バレットの終了処理
	UninitBullet2();


	//ターゲットの終了処理
	UninitTarget();

	// エネミーバレットの終了処理
	UninitEBullet();

	// BG終了処理
	UninitBG();
	
	// BG終了処理
	UninitCaptionBG();

	// タイトル終了処理
	UninitTitle();

	// リザルト終了処理
	UninitResult3();
	
	// スコア終了処理
	UninitScore();

	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}

	//// サウンド処理の終了処理
	//if (g_pD3D != NULL)
	//{
	//	g_pBGM->Release();
	//	g_pBGM = NULL;
	//}
	//UninitSound();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{

	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	BOSS*boss = GetBoss(0);
	int i = 1;

	// 入力の更新処理
	UpdateInput();
	
	// 画面遷移
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();
		break;

	case STAGE_CAPTION:
		UpdateCaptionBG();
		break;
	//	// プレイヤーの更新処理
	//	UpdatePlayer();

	//	// エネミーの更新処理
	//	UpdateEnemy();

	//	// エネミーの更新処理
	//	UpdateEnemy2();

	//	// バレットの更新処理
	//	UpdateBullet();

	//	// BGの更新処理
	//	UpdateBG();

	//	// 当たり判定
	//	CheckHit();
	//	break;



	case STAGE_GAME:
		// プレイヤーの更新処理
		UpdatePlayer();

		// プレイヤーの更新処理
		UpdatePgage();

		// プレイヤーの更新処理
		UpdateEgage();

		// プレイヤーの更新処理
		UpdateTgage();

		// プレイヤーの更新処理
		UpdateBTgage();

		// プレイヤーの更新処理
		//UpdateBgage();

		// エネミーの更新処理
		UpdateEnemy();

		// エネミーの更新処理
		UpdateEnemy2();

		// エネミーの更新処理
		UpdateEnemy3();

		// エネミーの更新処理
		UpdateEnemy4();

		// エネミーの更新処理
		UpdateEnemy5();

		// エネミーの更新処理
		UpdateEnemy6();

		//ボスの更新処理
		UpdateBoss();

		// バレットの更新処理
		UpdateBullet();

		// バレットの更新処理
		UpdateBullet2();

		//エフェクトの更新処理
		UpdateEffect();

		//エフェクト2の更新処理
		UpdateEffect2();

		//エフェクト3の更新処理
		UpdateEffect3();

		//エフェクト3の更新処理
		UpdateEffect4();

		//エフェクト3の更新処理
		UpdateBossEffect();

		//エフェクト3の更新処理
		UpdateEffect5();

		//エフェクト3の更新処理
		UpdateEffect6();

		// ターゲットの更新処理
		UpdateTarget();


		// エネミーバレットの更新処理
		UpdateEBullet();

		// エネミーバレットの更新処理
		UpdateEBullet2();

		// BGの更新処理
		UpdateBG();

		// スコアの更新処理
		UpdateScore();
		
		// 当たり判定
		CheckHit();
		break;

	case STAGE_GAME_END:
		// スコアの更新処理
		UpdateScore();

		if (STAGE_GAME)
		{// Enter押したら、ステージを切り替える
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				InitGame();				// ゲームの再初期化処理
				SetStage(STAGE_RESULT);
			}

		}
		if (STAGE_GAME&&GetKeyboardTrigger(DIK_RETURN))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_RESULT);


		}

		else if(IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_RESULT);
		}
		break;
	
	case STAGE_RESULT:
		UpdateResult3();
		break;
	}

	
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{

	//ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	BOSS*boss = GetBoss(0);
	int i = 1;




	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// 画面遷移
		switch (g_nStage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;
		case STAGE_CAPTION:
			DrawCaptionBG();
			break;

		case STAGE_PSELECT:
		//	// BGの描画処理
		//	DrawBG();

		//	// エネミーの描画処理
		//	DrawEnemy();

		//	// エネミーの描画処理
		//	DrawEnemy2();

		//	// プレイヤーの描画処理
		//	DrawPlayer();

		//	// バレットの描画処理
		//	DrawBullet();

		//	break;
		case STAGE_GAME:

			// BGの描画処理
			DrawBG();

			// プレイヤーの描画処理
			DrawTgage();

			// プレイヤーの描画処理
			DrawBTgage();

			// プレイヤーの描画処理
			DrawPgage();

			// プレイヤーの描画処理
			DrawEgage();

			// プレイヤーの描画処理
			//DrawBgage();

			// エネミーの描画処理
			DrawEnemy();

			// エネミーの描画処理
			DrawEnemy2();

			// エネミーの描画処理
			DrawEnemy3();

			// エネミーの描画処理
			DrawEnemy4();

			// エネミーの描画処理
			DrawEnemy5();

			// エネミーの描画処理
			DrawEnemy6();

			// プレイヤーの描画処理
			DrawPlayer();

			//プレイヤーの描画処理
			//DrawHP;

			// バレットの描画処理
			DrawBullet();

			// バレットの描画処理
			DrawBullet2();


			//ボスの描画処理
			DrawBoss();

			// ターゲットの描画処理
			DrawTarget();

			//エフェクトの描画処理
			DrawEffect();

			//エフェクト2の描画処理
			DrawEffect2();

			//エフェクト2の描画処理
			DrawEffect3();

			//エフェクト2の描画処理
			DrawEffect4();

			//エフェクト2の描画処理
			DrawEffect5();

			//エフェクト2の描画処理
			DrawEffect6();

			//ボスエフェクトの描画処理
			DrawBossEffect();

			// エネミーバレットの描画処理
			DrawEBullet();

			// エネミーバレットの描画処理
			DrawEBullet2();

			break;


		case STAGE_GAME_END:
			// BGの描画処理
			DrawBG();

			// プレイヤーの描画処理
			DrawEgage();

			// プレイヤーの描画処理
			DrawPgage();

			// プレイヤーの描画処理
			DrawTgage();

			// プレイヤーの描画処理
			DrawBTgage();

			// プレイヤーの描画処理
			//DrawBgage();

			// エネミーの描画処理
			DrawEnemy();

			// エネミーの描画処理
			DrawEnemy2();

			// エネミーの描画処理
			DrawEnemy3();

			// エネミーの描画処理
			DrawEnemy4();

			// エネミーの描画処理
			DrawEnemy5();

			// エネミーの描画処理
			DrawEnemy6();

			// プレイヤーの描画処理
			DrawPlayer();



			//ボスの描画処理
			DrawBoss();

			//エフェクトの描画処理
			DrawEffect();

			//エフェクト2の描画処理
			DrawEffect2();

			//エフェクト2の描画処理
			DrawEffect3();

			//エフェクト2の描画処理
			DrawEffect4();

			//エフェクト2の描画処理
			DrawEffect5();

			//エフェクト2の描画処理
			DrawEffect6();

			//エフェクト2の描画処理
			DrawBossEffect();

			// バレットの描画処理
			DrawBullet();

			// バレットの描画処理
			DrawBullet2();


			//ターゲットの描画処理
			DrawTarget();

			// エネミーバレットの描画処理
			DrawEBullet();

			// エネミーバレットの描画処理
			DrawEBullet2();

			
			// スコアの描画処理
			DrawScore();
			break;


		case STAGE_RESULT:
			DrawResult3();
			break;
		}


#ifdef _DEBUG
		// デバッグ表示
		DrawDebugFont();
#endif
		
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// デバッグ表示処理
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	PLAYER *player = GetPlayer(0);
	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	EBULLET *ebullet = GetEBullet(0);		// バレットのポインターを初期化

	ENEMY *enemy = GetEnemy(0);				// バレットのポインターを初期化
	ENEMY2 *enemy2 = GetEnemy2(0);				// バレットのポインターを初期化
	ENEMY4 *enemy4 = GetEnemy4(0);				// バレットのポインターを初期化
	ENEMY5 *enemy5 = GetEnemy5(0);				// バレットのポインターを初期化

	EFFECT*effect = GetEffect(0);			//エフェクトのポインターを初期化
	EFFECT2*effect2 = GetEffect2(0);		//エフェクト２のポインターを初期化
	EFFECT3*effect3 = GetEffect3(0);		//エフェクト３のポインターを初期化


	BOSS*boss = GetBoss(0);					//ボスのポインターを初期化


		// テキスト描画
		sprintf(str, _T("FPS:%d"), g_nCountFPS);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		rect.top = 20;
		sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		rect.top = 40;
		sprintf(str, "バレットuse:%d", bullet->use);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		//rect.top = 60;
		//sprintf(str, "Sキーuse:%d", player->Skey);
		//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		//rect.top = 80;
		//sprintf(str, "Aキーuse:%d", player->Akey);
		//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 60;
	//	sprintf(str, "Bcounter:%d", player->Bcounter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 80;
	//	sprintf(str, "Timecounter:%d", player->Timecounter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 100;
	//	sprintf(str, "Ecounter:%d", enemy2->counter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 160;
	//	sprintf(str, "再登場フラグ:%d", enemy->comeback);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 180;
	//	sprintf(str, "エネミー2のフラッグ:%d", GetEnemy(1)->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 200;
	//	sprintf(str, "effectpos_x:%f", effect->pos.x);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 220;
	//	sprintf(str, "effectpos_y:%f", effect->pos.y);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 240;
	//	sprintf(str, "ボスのHP:%d", boss->HP);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 260;
	//	sprintf(str, "エフェクトのuse:%d", effect->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 280;
	//	sprintf(str, "Y軸の絶対値:%f", GetBullet(0)->zet);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 300;
	//	sprintf(str, "Yの距離:%f", GetBullet(0)->dis.y);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	//	rect.top = 320;
	//	sprintf(str, "ヒット:%d", GetBoss(0)->Hitcounter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 340;
	//	sprintf(str, "effect:%d", effect3->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 360;
	//	sprintf(str, "ebullet_pos.x:%f", ebullet->pos.x);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	//	rect.top = 400;
	//	sprintf(str, "boss_counter:%d", boss->Popcounter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 420;
	//	sprintf(str, "counter:%d", boss->counter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 440;
	//	sprintf(str, "bossフラグ:%d", boss->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 460;
	//	sprintf(str, "counter:%d", player->counter);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 380;
	//	sprintf(str, "ebullet:%d", ebullet->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	//	rect.top = 120;
	//	sprintf(str, "enemypos_x:%f", enemy->enemypos_x);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 140;
	//	sprintf(str, "enemypos_y:%f", enemy->enemypos_y);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


}
#endif

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage( int stage )
{
	//if( state < 0 || state >= STATE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	ENEMY *enemy = GetEnemy(0);					// エネミーのポインターを初期化
	ENEMY2 *enemy2 = GetEnemy2(0);				// エネミー2のポインターを初期化
	ENEMY3 *enemy3 = GetEnemy3(0);				// エネミー3のポインターを初期化
	ENEMY4 *enemy4 = GetEnemy4(0);				// エネミー4のポインターを初期化
	ENEMY5 *enemy5 = GetEnemy5(0);				// エネミー4のポインターを初期化
	ENEMY6 *enemy6 = GetEnemy6(0);				// エネミー4のポインターを初期化
	BULLET *bullet = GetBullet(0);				// バレットのポインターを初期化
	EBULLET *ebullet = GetEBullet(0);			// エネミーバレットのポインターを初期化
	EBULLET2 *ebullet2 = GetEBullet2(0);		// エネミーバレット2のポインターを初期化

	BULLET2 *bullet2 = GetBullet2(0);			// バレットのポインターを初期化
	PLAYER *player = GetPlayer(0);
	TARGET *target = GetTarget(0);
	EFFECT *effect = GetEffect(0);
	BOSS*boss = GetBoss(0);

	// エネミー1と操作キャラ(BB)
	for( int E = 0; E < ENEMY_MAX; E++,enemy++)
	{
		if(enemy->use == false )	continue;

		if( CheckHitBB( GetPlayer(0)->pos, enemy->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X,TEXTURE_ENEMY_SIZE_Y)) )
		{

			player->Hitcounter++;

			if (player->Hitcounter ==10)
			{
				// HP減少処理
				player->HP-=10;

			}


			if(player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}


			// 敵キャラクターは倒される
			//enemy->use = false;

		}
	}

	// エネミー2と操作キャラ(BB)
	for (int E1 = 0; E1 < ENEMY2_MAX; E1++, enemy2++)
	{
		if (enemy2->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy2->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// エネミー3と操作キャラ(BB)
	for (int E1 = 0; E1 < ENEMY3_MAX; E1++, enemy3++)
	{
		if (enemy3->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy3->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY3_SIZE_X, TEXTURE_ENEMY3_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// エネミー4と操作キャラ(BB)
	for (int E1 = 0; E1 < ENEMY4_MAX; E1++, enemy4++)
	{
		if (enemy4->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy4->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY4_SIZE_X, TEXTURE_ENEMY4_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// エネミー4と操作キャラ(BB)
	for (int E1 = 0; E1 < ENEMY5_MAX; E1++, enemy5++)
	{
		if (enemy5->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy5->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY5_SIZE_X, TEXTURE_ENEMY5_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// エネミー4と操作キャラ(BB)
	for (int E1 = 0; E1 < ENEMY6_MAX; E1++, enemy6++)
	{
		if (enemy6->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy6->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY6_SIZE_X, TEXTURE_ENEMY6_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// bossと操作キャラ(BB)
	for (int E1 = 0; E1 < BOSS_MAX; E1++, boss++)
	{
		if (boss->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, boss->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP減少処理
				player->HP -= 10;

			}


			if (player->HP <= 0)			// 操作キャラクターは死に
			{
				player->use = false;
			}
			// 敵キャラクターは倒される
			//enemy->use = false;
		}
	}


	// 弾とプレイヤー(BC)
	for (int i = 0; i < EBULLET_MAX; i++,ebullet++)
	{
		if (ebullet->use == false) continue;

		for (int j = 0; j < PLAYER_MAX; j++)
		{
			if (GetPlayer(j)->use == false) continue;

			if (CheckHitBC(GetEBullet(i)->pos, GetPlayer(j)->pos, TEXTURE_EBULLET_SIZE_X, TEXTURE_PLAYER_SIZE_X))
			{

				GetPlayer(j)->Hitcounter++;
				if (GetPlayer(j)->Hitcounter == 1)
				{
					// HP減少処理
					GetPlayer(j)->HP -= 10;

				}




				GetEBullet(i)->use = false;		// 弾の消滅処理を行い
				//GetBullet(i)->BBflag = false;	//再誘導をかける


				if (GetPlayer(j)->HP <= 0)
				{

					GetPlayer(j)->use = false;		// 敵は倒される
					SetStage(STAGE_GAME_END);



				}



				// スコア計算
				AddScore(100);
			}
		}
	}


	// 弾とプレイヤー(BC)
	for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
	{
		if (ebullet2->use == false) continue;

		for (int j = 0; j < PLAYER_MAX; j++)
		{
			if (GetPlayer(j)->use == false) continue;

			if (CheckHitBC(GetEBullet2(i)->pos, GetPlayer(j)->pos, TEXTURE_EBULLET2_SIZE_X, TEXTURE_PLAYER_SIZE_X))
			{

				GetPlayer(j)->Hitcounter++;
				if (GetPlayer(j)->Hitcounter == 1)
				{
					// HP減少処理
					GetPlayer(j)->HP -= 10;

				}




				GetEBullet2(i)->use = false;		// 弾の消滅処理を行い
				//GetBullet(i)->BBflag = false;	//再誘導をかける


				if (GetPlayer(j)->HP <= 0)
				{

					GetPlayer(j)->use = false;		// 敵は倒される
					SetStage(STAGE_GAME_END);


				}



				// スコア計算
				AddScore(100);
			}
		}
	}






	// 弾と敵(BC)
	//enemy = GetEnemy(0);	
	for( int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if( GetBullet(i)->use == false ) continue;

		for( int j = 0; j < ENEMY_MAX; j++,enemy++)
		{
			if(GetEnemy(j)->use == false ) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
			{
				//effect->use = true;
				effect->effectcounter++;

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy(j)->use = false;		// 敵は倒される
				GetEnemy(j)->effectflag = true;	//エフェクトを出したい
				GetEnemy(j)->BBflag = true;
				GetBullet(i)->BBflag = false;	//再誘導をかける


				//GetBoss(i)->Popcounter++;


				// スコア計算
				AddScore(100);
			}
		}
	}

	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	if (bullet->use == false) continue;

	//	for (int j = 0; j < ENEMY_MAX; j++)
	//	{
	//		if (GetEnemy(j)->use == false) continue;

	//		if (CheckHitBC(GetBullet(i)->pos, GetEnemy(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
	//		{
	//			//effect->use = true;
	//			effect->effectcounter++;

	//			GetBullet(i)->use = false;		// 弾の消滅処理を行い
	//			GetEnemy(j)->use = false;		// 敵は倒される
	//			GetEnemy(j)->effectflag = true;	//エフェクトを出したい
	//			GetBullet(i)->BBflag = false;	//再誘導をかける
	//			GetBoss(i)->Popcounter++;

	//			if (GetBoss(i)->Popcounter > 13)
	//			{
	//				GetBoss(i)->use = true;

	//				player->counter = 60;

	//			}
	//			// スコア計算
	//			AddScore(100);
	//		}
	//	}
	//}






	//エネミー２との弾との当たり判定だよ！馬鹿野郎

	//enemy2 = GetEnemy2(0);					// エネミーのポインターを初期化

	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY2_MAX; j++,enemy2++)
		{
			if (GetEnemy2(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy2(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY2_SIZE_X))
			{

				//effect->use = true;
				effect->effectcounter += 2;

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy2(j)->use = false;		// 敵は倒される
				//GetBoss(i)->Popcounter++;
				GetEnemy2(j)->effectflag2 = true;	//エフェクトを出したい
				GetEnemy2(j)->BBflag = true;



				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}


				// スコア計算
				AddScore(100);
			}

		}
	}



	// 弾とエネミー３(BC)
	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY3_MAX; j++,enemy3++)
		{
			if (GetEnemy3(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy3(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY3_SIZE_X))
			{

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy3(j)->use = false;		// 敵は倒される
				GetEnemy3(j)->effectflag3 = true;	//エフェクトを出したい
				GetBullet(i)->BBflag = false;	//再誘導をかける
				GetEnemy3(j)->BBflag = true;
				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}


				// スコア計算
				AddScore(100);
			}
		}
	}


	// 弾とエネミー4(BC)
	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY4_MAX; j++,enemy4++)
		{
			if (GetEnemy4(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy4(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY4_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy4(j)->use = false;		// 敵は倒される
				GetEnemy4(j)->effectflag4 = true;	//エフェクトを出したい
				GetBullet(i)->BBflag = false;	//再誘導をかける
				GetEnemy4(j)->nextflag = true;
				GetEnemy4(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// スコア計算
				AddScore(100);
			}
		}
	}



	// 弾とエネミー5(BC)
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY5_MAX; j++, enemy5++)
		{
			if (GetEnemy5(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy5(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY5_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy5(j)->use = false;		// 敵は倒される
				GetEnemy5(j)->effectflag = true;	//エフェクトを出したい
				GetBullet(i)->BBflag = false;	//再誘導をかける
				//GetEnemy5(j)->nextflag = true;
				GetEnemy5(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// スコア計算
				AddScore(100);
			}
		}
	}

	// 弾とエネミー6(BC)
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY6_MAX; j++, enemy6++)
		{
			if (GetEnemy6(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy6(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY6_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetEnemy6(j)->use = false;		// 敵は倒される
				GetEnemy6(j)->effectflag = true;	//エフェクトを出したい
				GetBullet(i)->BBflag = false;	//再誘導をかける
				//GetEnemy5(j)->nextflag = true;
				GetEnemy6(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// スコア計算
				AddScore(100);
			}
		}
	}




	// 弾とボス(BC)
	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < BOSS_MAX; j++,boss++)
		{
			if (GetBoss(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetBoss(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_BOSS_SIZE_X))
			{

				GetBoss(j)->Hitcounter++;
				if (GetBoss(j)->Hitcounter == 1)
				{
					// HP減少処理
					GetBoss(j)->HP -= 15;

				}




				GetBullet(i)->use = false;		// 弾の消滅処理を行い
				GetBoss(i)->effectflag = true;
				//GetBullet(i)->BBflag = false;	//再誘導をかける


				if (GetBoss(j)->HP<=0)
				{

					GetBoss(j)->use = false;		// 敵は倒される
					SetStage(STAGE_GAME_END);
					


				}



				// スコア計算
				AddScore(100);
			}
		}
	}


	// 弾とプレイヤー(BC)
	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		if (target->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (GetEnemy(j)->use == false) continue;

			if (CheckHitBC(GetTarget(i)->pos, GetEnemy(j)->pos, TEXTURE_TARGET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
			{

				target->rockflug = true;
			}
		}
	}


	// 弾2とエネミー(BC)
//enemy = GetEnemy(0);	
	//for (int i = 0; i < BULLET2_MAX; i++)
	//{
	//	if (bullet2->use == false) continue;

	//	for (int j = 0; j < ENEMY_MAX; j++)
	//	{
	//		if (GetEnemy(j)->use == false) continue;

	//		if (CheckHitBC(GetBullet2(i)->pos, GetEnemy(j)->pos, TEXTURE_BULLET2_SIZE_X, TEXTURE_ENEMY_SIZE_X))
	//		{
	//			//effect->use = true;
	//			effect->effectcounter++;

	//			GetBullet2(i)->use = false;		// 弾の消滅処理を行い
	//			GetEnemy(j)->use = false;		// 敵は倒される
	//			GetBullet2(i)->BBflag = false;	//再誘導をかける
	//			GetEnemy(j)->effectflag = true;	//エフェクトを出したい
	//			GetBoss(i)->Popcounter++;


	//			if (GetBoss(i)->Popcounter >= 13)
	//			{

	//				GetBoss(i)->use = true;

	//			}


	//			// スコア計算
	//			AddScore(100);
	//		}
	//	}
	//}


	//エネミー２との弾との当たり判定だよ！馬鹿野郎

	//for (int i = 0; i < BULLET2_MAX; i++)
	//{
	//	if (GetBullet2(i)->use == false) continue;

	//	for (int j = 0; j < ENEMY2_MAX; j++)
	//	{
	//		if (GetEnemy2(j)->use == false) continue;

	//		if (CheckHitBC(GetBullet2(i)->pos, GetEnemy2(j)->pos, TEXTURE_BULLET2_SIZE_X, TEXTURE_ENEMY2_SIZE_X))
	//		{

	//			effect->use = true;
	//			effect->effectcounter += 2;


	//			GetBullet2(i)->use = false;		// 弾の消滅処理を行い
	//			GetEnemy2(j)->use = false;		// 敵は倒される
	//			GetEnemy2(j)->effectflag2 = true;	//エフェクトを出したい
	//			GetBoss(0)->Popcounter++;

	//			// スコア計算
	//			AddScore(100);
	//		}

	//	}
	//}


	//エネミー２との弾との当たり判定だよ！馬鹿野郎

//enemy2 = GetEnemy2(0);					// エネミーのポインターを初期化

	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	if (GetBullet(i)->use == false) continue;

	//	for (int j = 0; j < BOSS_MAX; j++)
	//	{
	//		if (GetBoss(j)->use == false) continue;

	//		if (CheckHitBC(GetBullet(i)->pos, GetBoss(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_BOSS_SIZE_X))
	//		{

	//			effect->use = true;

	//			boss->HP -= 1;


	//			GetBullet(i)->use = false;		// 弾の消滅処理を行い

	//			if (boss->HP == 0)
	//			{
	//				GetBoss(j)->use = false;		// 敵は倒される
	//			}

	//			// スコア計算
	//			AddScore(100);
	//		}

	//	}
	//}




	//ターゲットをと弾の当たり判定

	//for (int i = 0; i < TARGET_MAX; i++, target++)
	//{
	//	if (target->use == false) continue;

	//	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	//	{
	//		if (GetEnemy(j)->use == false) continue;

	//		if (CheckHitBC(GetTarget(i)->pos, GetEnemy(j)->pos, TEXTURE_TARGET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
	//		{
	//			GetBullet(i)->BBflag = true;	// 弾の消滅処理を行い
	//			//GetEnemy(j)->use = false;		// 敵は倒される


	//			// スコア計算
	//			AddScore(100);
	//		}

	//	}
	//}


	//for (int i = 0; i < TARGET_MAX; i++, target++)
	//{
	//	if (target->use == false) continue;

	//	for (int j = 0; j < BULLET_MAX; j++, bullet++)
	//	{
	//		if (GetBullet(j)->use == false) continue;

	//		if (CheckHitBC(GetTarget(i)->pos, GetBullet(j)->pos, TEXTURE_TARGET_SIZE_X, TEXTURE_BULLET_SIZE_X))
	//		{
	//			GetBullet(i)->BBflag = true;	// 弾の消滅処理を行い
	//			//GetEnemy(j)->use = false;		// 敵は倒される


	//			// スコア計算
	//			AddScore(100);
	//		}

	//	}
	//}





	// ボスと弾(BC)

	// 自分と敵の弾(BC)

	// 敵が全滅したら画面遷移
	enemy = GetEnemy(0);					// エネミーのポインターを初期化
	//for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	//{

	//	if (GetEnemy(i)->use == true)
	//	{
	//		cnt++;
	//	}
	//	
	//}

	 //数えた結果敵が全滅？

	if(boss->use==false && player->counter<=0)
	{
			SetStage(STAGE_GAME_END);
		

	}

	//for (int i = 0; i < BULLET_MAX; i++, bullet++)

	//if (enemy->use == false && GetEnemy2(i)->use == false && GetEnemy3(i)->use == false && GetEnemy4(i)->use == false && GetEnemy5(i)->use == false && GetEnemy6(i)->use == false)
	//{
	//	SetStage(STAGE_GAME_END);


	//}


	if (player->Bcounter <= 0)
	{
		//if (boss->use == true)
		//{
			SetStage(STAGE_GAME_END);
		//}

	}


	//if (player->counter == 30 && boss->use == true)
	//{

	//	SetStage(STAGE_GAME_END);


	//}

	//プレイヤーが消えるとゲームオーバー
	if (player->use == false)
	{
		SetStage(STAGE_GAME_END);
	}



}


//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBB( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2 )
{
	size1 /= 2.0f;	// 半サイズにする
	size2 /= 2.0f;	// 同上

	if( pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y )
	{
		return true;
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBC( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2 )
{
	if( ( size1 + size2 ) * ( size1 + size2 ) >
		( pos1.x - pos2.x ) * ( pos1.x - pos2.x ) + ( pos1.y - pos2.y ) * ( pos1.y - pos2.y ) )
	{
		return true;
	}

	return false;
}


//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);		// プレイヤーの再初期化
	InitEnemy(1);		// エネミーの再初期化
	InitBullet(1);		// バレットの再初期化
	InitScore(1);		// スコアの再初期化
	InitBG(1);			// BGの再初期化
	InitPgage();
	InitEgage();
	InitTgage();
	InitBTgage();
	InitEnemy2(1);
	InitEnemy3(1);
	InitEnemy4(1);
	InitEnemy5(1);
	InitEnemy6(1);
	InitBoss(0);
	InitBullet(1);
	InitBullet2(1);
	InitEffect(0);
	InitEffect2(0);
	InitEffect3(0);
	InitBossEffect(0);
	InitEffect4(0);
	InitEBullet(1);
	InitEBullet2(1);
	InitTarget(0);

}

