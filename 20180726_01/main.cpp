//=============================================================================
//
// Main���� [main.cpp]
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("Alien species")		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

//#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;				// FPS�J�E���^
int						cnt = 0;							// �G�̐��𐔂���

//#endif

int						g_nStage = 0;				// �X�e�[�W�ԍ�

//LPDIRECTSOUNDBUFFER8	g_pBGM;						// BGM�p�o�b�t�@


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	ENEMY2 *enemy2 = GetEnemy2(0);			// �G�l�~�[2�̃|�C���^�[��������
	ENEMY3 *enemy3 = GetEnemy3(0);			// �G�l�~�[3�̃|�C���^�[��������
	ENEMY4 *enemy4 = GetEnemy4(0);			// �G�l�~�[4�̃|�C���^�[��������
	ENEMY5 *enemy5 = GetEnemy5(0);			// �G�l�~�[5�̃|�C���^�[��������
	ENEMY6 *enemy6 = GetEnemy6(0);			// �G�l�~�[6�̃|�C���^�[��������


	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	EBULLET*ebullet = GetEBullet(0);		//�G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);			//�v���C���[�̃|�C���^�[��������
	EFFECT*effect = GetEffect(0);			//�G�t�F�N�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);
	LOGO*logo = GetLogo(0);
	TGAGE*tgage = GetTgage(0);				//�^�C���Q�[�W�̃|�C���^�[��������


	
	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
				//#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPS�𑪒�
				
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
						player->Timecounter++;				//���G���Ԃ����肽��
					}

					if (boss->Hitcounter > 0)
					{
						boss->Timecounter++;				//���G���Ԃ����肽��
					}


					if (bullet->use == true)
					{
						bullet->counter++;
					}



					if (bullet->BM >= 8)
					{
						bullet->reload++;						//�����[�h���Ԃ̐���
					}

					//if (enemy->counter > 28)
					//{
					//	enemy->comeback = true;
					//}


				}


					//boss->counter++;




	//#endif
					dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
					dwFrameCount = 0;							// �J�E���g���N���A
				}



				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
				{
					dwExecLastTime = dwCurrentTime;	// ��������������ۑ�


					Update();			// �X�V����
					Draw();				// �`�揈��



					dwFrameCount++;		// �����񐔂̃J�E���g�����Z
				}
			}
		}
	

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
									hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&g_pD3DDevice)))							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

//#ifdef _DEBUG
																			// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
//#endif
	
	// �T�E���h������
	//InitSound(hWnd);
	// ���[�h�ƍĐ�
	//g_pBGM = LoadSound(BGM_00);
	//PlaySound(g_pBGM, E_DS8_FLAG_LOOP);

	// �v���C���[�̏���������
	InitPlayer(0);

	// �v���C���[�̏���������
	InitPgage();

	// �v���C���[�̏���������
	InitEgage();

	// �v���C���[�̏���������
	InitTgage();

	// �v���C���[�̏���������
	//InitBgage();

	// �G�l�~�[�̏���������
	InitEnemy(0);

	// �G�l�~�[�̏���������
	InitEnemy2(0);

	// �G�l�~�[�̏���������
	InitEnemy3(0);

	// �G�l�~�[�̏���������
	InitEnemy4(0);

	// �G�l�~�[�̏���������
	InitEnemy5(0);

	// �G�l�~�[�̏���������
	InitEnemy6(0);

	//�{�X�̃G�l�~�[�̏�����
	InitBoss(0);

	// �o���b�g�̏���������
	InitBullet(0);

	// �o���b�g�̏���������
	InitBullet2(0);

	//�G�t�F�N�g�̏���������
	InitEffect(0);

	//�G�t�F�N�g�̏���������
	InitEffect2(0);

	//�G�t�F�N�g�̏���������
	InitEffect3(0);

	//�{�X�G�t�F�N�g�̏�����
	InitBossEffect(0);

	//�G�t�F�N�g�̏���������
	InitEffect4(0);

	//�G�t�F�N�g�̏���������
	InitEffect5(0);

	//�G�t�F�N�g�̏���������
	InitEffect6(0);

	//�G�l�~�[�o���b�g�̏�����
	InitEBullet(0);

	//�G�l�~�[�o���b�g�̏�����
	InitEBullet2(0);

	//�^�[�Q�b�g�̏�����
	InitTarget(0);

	//�^�[�Q�b�g�̏�����
	InitBTgage();

	// BG������
	InitBG(0);

	// BG������
	InitCaptionBG(0);

	// �^�C�g��������
	InitTitle();

	// ���U���g������
	InitResult3();

	// �X�R�A������
	InitScore(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// ���͏����̏I������
	UninitInput();

	// �v���C���[�̏I������
	UninitPlayer();

	// �v���C���[�̏I������
	UninitPgage();

	// �v���C���[�̏I������
	UninitEgage();

	// �v���C���[�̏I������
	UninitTgage();

	// �v���C���[�̏I������
	UninitBTgage();

	// �v���C���[�̏I������
	//UninitBgage();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �G�l�~�[�̏I������
	UninitEnemy2();

	// �G�l�~�[�̏I������
	UninitEnemy3();

	// �G�l�~�[�̏I������
	UninitEnemy4();

	// �G�l�~�[�̏I������
	UninitEnemy5();

	// �G�l�~�[�̏I������
	UninitEnemy6();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�G�t�F�N�g2�̏I������
	UninitEffect2();

	//�G�t�F�N�g2�̏I������
	UninitEffect3();

	//�G�t�F�N�g2�̏I������
	UninitEffect4();

	//�G�t�F�N�g2�̏I������
	UninitEffect5();
	
	//�G�t�F�N�g2�̏I������
	UninitEffect6();

	//�G�t�F�N�g2�̏I������
	UninitBossEffect();

	//�{�X�̏I������
	UninitBoss();

	// �o���b�g�̏I������
	UninitBullet();

	// �o���b�g�̏I������
	UninitBullet2();


	//�^�[�Q�b�g�̏I������
	UninitTarget();

	// �G�l�~�[�o���b�g�̏I������
	UninitEBullet();

	// BG�I������
	UninitBG();
	
	// BG�I������
	UninitCaptionBG();

	// �^�C�g���I������
	UninitTitle();

	// ���U���g�I������
	UninitResult3();
	
	// �X�R�A�I������
	UninitScore();

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
	}

	//// �T�E���h�����̏I������
	//if (g_pD3D != NULL)
	//{
	//	g_pBGM->Release();
	//	g_pBGM = NULL;
	//}
	//UninitSound();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{

	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);
	int i = 1;

	// ���͂̍X�V����
	UpdateInput();
	
	// ��ʑJ��
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();
		break;

	case STAGE_CAPTION:
		UpdateCaptionBG();
		break;
	//	// �v���C���[�̍X�V����
	//	UpdatePlayer();

	//	// �G�l�~�[�̍X�V����
	//	UpdateEnemy();

	//	// �G�l�~�[�̍X�V����
	//	UpdateEnemy2();

	//	// �o���b�g�̍X�V����
	//	UpdateBullet();

	//	// BG�̍X�V����
	//	UpdateBG();

	//	// �����蔻��
	//	CheckHit();
	//	break;



	case STAGE_GAME:
		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �v���C���[�̍X�V����
		UpdatePgage();

		// �v���C���[�̍X�V����
		UpdateEgage();

		// �v���C���[�̍X�V����
		UpdateTgage();

		// �v���C���[�̍X�V����
		UpdateBTgage();

		// �v���C���[�̍X�V����
		//UpdateBgage();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();

		// �G�l�~�[�̍X�V����
		UpdateEnemy2();

		// �G�l�~�[�̍X�V����
		UpdateEnemy3();

		// �G�l�~�[�̍X�V����
		UpdateEnemy4();

		// �G�l�~�[�̍X�V����
		UpdateEnemy5();

		// �G�l�~�[�̍X�V����
		UpdateEnemy6();

		//�{�X�̍X�V����
		UpdateBoss();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// �o���b�g�̍X�V����
		UpdateBullet2();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�G�t�F�N�g2�̍X�V����
		UpdateEffect2();

		//�G�t�F�N�g3�̍X�V����
		UpdateEffect3();

		//�G�t�F�N�g3�̍X�V����
		UpdateEffect4();

		//�G�t�F�N�g3�̍X�V����
		UpdateBossEffect();

		//�G�t�F�N�g3�̍X�V����
		UpdateEffect5();

		//�G�t�F�N�g3�̍X�V����
		UpdateEffect6();

		// �^�[�Q�b�g�̍X�V����
		UpdateTarget();


		// �G�l�~�[�o���b�g�̍X�V����
		UpdateEBullet();

		// �G�l�~�[�o���b�g�̍X�V����
		UpdateEBullet2();

		// BG�̍X�V����
		UpdateBG();

		// �X�R�A�̍X�V����
		UpdateScore();
		
		// �����蔻��
		CheckHit();
		break;

	case STAGE_GAME_END:
		// �X�R�A�̍X�V����
		UpdateScore();

		if (STAGE_GAME)
		{// Enter��������A�X�e�[�W��؂�ւ���
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				InitGame();				// �Q�[���̍ď���������
				SetStage(STAGE_RESULT);
			}

		}
		if (STAGE_GAME&&GetKeyboardTrigger(DIK_RETURN))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_RESULT);


		}

		else if(IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// �Q�[���̍ď���������
			SetStage(STAGE_RESULT);
		}
		break;
	
	case STAGE_RESULT:
		UpdateResult3();
		break;
	}

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{

	//ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);
	int i = 1;




	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ��ʑJ��
		switch (g_nStage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;
		case STAGE_CAPTION:
			DrawCaptionBG();
			break;

		case STAGE_PSELECT:
		//	// BG�̕`�揈��
		//	DrawBG();

		//	// �G�l�~�[�̕`�揈��
		//	DrawEnemy();

		//	// �G�l�~�[�̕`�揈��
		//	DrawEnemy2();

		//	// �v���C���[�̕`�揈��
		//	DrawPlayer();

		//	// �o���b�g�̕`�揈��
		//	DrawBullet();

		//	break;
		case STAGE_GAME:

			// BG�̕`�揈��
			DrawBG();

			// �v���C���[�̕`�揈��
			DrawTgage();

			// �v���C���[�̕`�揈��
			DrawBTgage();

			// �v���C���[�̕`�揈��
			DrawPgage();

			// �v���C���[�̕`�揈��
			DrawEgage();

			// �v���C���[�̕`�揈��
			//DrawBgage();

			// �G�l�~�[�̕`�揈��
			DrawEnemy();

			// �G�l�~�[�̕`�揈��
			DrawEnemy2();

			// �G�l�~�[�̕`�揈��
			DrawEnemy3();

			// �G�l�~�[�̕`�揈��
			DrawEnemy4();

			// �G�l�~�[�̕`�揈��
			DrawEnemy5();

			// �G�l�~�[�̕`�揈��
			DrawEnemy6();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			//�v���C���[�̕`�揈��
			//DrawHP;

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �o���b�g�̕`�揈��
			DrawBullet2();


			//�{�X�̕`�揈��
			DrawBoss();

			// �^�[�Q�b�g�̕`�揈��
			DrawTarget();

			//�G�t�F�N�g�̕`�揈��
			DrawEffect();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect2();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect3();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect4();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect5();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect6();

			//�{�X�G�t�F�N�g�̕`�揈��
			DrawBossEffect();

			// �G�l�~�[�o���b�g�̕`�揈��
			DrawEBullet();

			// �G�l�~�[�o���b�g�̕`�揈��
			DrawEBullet2();

			break;


		case STAGE_GAME_END:
			// BG�̕`�揈��
			DrawBG();

			// �v���C���[�̕`�揈��
			DrawEgage();

			// �v���C���[�̕`�揈��
			DrawPgage();

			// �v���C���[�̕`�揈��
			DrawTgage();

			// �v���C���[�̕`�揈��
			DrawBTgage();

			// �v���C���[�̕`�揈��
			//DrawBgage();

			// �G�l�~�[�̕`�揈��
			DrawEnemy();

			// �G�l�~�[�̕`�揈��
			DrawEnemy2();

			// �G�l�~�[�̕`�揈��
			DrawEnemy3();

			// �G�l�~�[�̕`�揈��
			DrawEnemy4();

			// �G�l�~�[�̕`�揈��
			DrawEnemy5();

			// �G�l�~�[�̕`�揈��
			DrawEnemy6();

			// �v���C���[�̕`�揈��
			DrawPlayer();



			//�{�X�̕`�揈��
			DrawBoss();

			//�G�t�F�N�g�̕`�揈��
			DrawEffect();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect2();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect3();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect4();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect5();

			//�G�t�F�N�g2�̕`�揈��
			DrawEffect6();

			//�G�t�F�N�g2�̕`�揈��
			DrawBossEffect();

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �o���b�g�̕`�揈��
			DrawBullet2();


			//�^�[�Q�b�g�̕`�揈��
			DrawTarget();

			// �G�l�~�[�o���b�g�̕`�揈��
			DrawEBullet();

			// �G�l�~�[�o���b�g�̕`�揈��
			DrawEBullet2();

			
			// �X�R�A�̕`�揈��
			DrawScore();
			break;


		case STAGE_RESULT:
			DrawResult3();
			break;
		}


#ifdef _DEBUG
		// �f�o�b�O�\��
		DrawDebugFont();
#endif
		
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�\������
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	PLAYER *player = GetPlayer(0);
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	EBULLET *ebullet = GetEBullet(0);		// �o���b�g�̃|�C���^�[��������

	ENEMY *enemy = GetEnemy(0);				// �o���b�g�̃|�C���^�[��������
	ENEMY2 *enemy2 = GetEnemy2(0);				// �o���b�g�̃|�C���^�[��������
	ENEMY4 *enemy4 = GetEnemy4(0);				// �o���b�g�̃|�C���^�[��������
	ENEMY5 *enemy5 = GetEnemy5(0);				// �o���b�g�̃|�C���^�[��������

	EFFECT*effect = GetEffect(0);			//�G�t�F�N�g�̃|�C���^�[��������
	EFFECT2*effect2 = GetEffect2(0);		//�G�t�F�N�g�Q�̃|�C���^�[��������
	EFFECT3*effect3 = GetEffect3(0);		//�G�t�F�N�g�R�̃|�C���^�[��������


	BOSS*boss = GetBoss(0);					//�{�X�̃|�C���^�[��������


		// �e�L�X�g�`��
		sprintf(str, _T("FPS:%d"), g_nCountFPS);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		rect.top = 20;
		sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		rect.top = 40;
		sprintf(str, "�o���b�guse:%d", bullet->use);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		//rect.top = 60;
		//sprintf(str, "S�L�[use:%d", player->Skey);
		//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


		//rect.top = 80;
		//sprintf(str, "A�L�[use:%d", player->Akey);
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
	//	sprintf(str, "�ēo��t���O:%d", enemy->comeback);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 180;
	//	sprintf(str, "�G�l�~�[2�̃t���b�O:%d", GetEnemy(1)->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 200;
	//	sprintf(str, "effectpos_x:%f", effect->pos.x);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 220;
	//	sprintf(str, "effectpos_y:%f", effect->pos.y);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 240;
	//	sprintf(str, "�{�X��HP:%d", boss->HP);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 260;
	//	sprintf(str, "�G�t�F�N�g��use:%d", effect->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 280;
	//	sprintf(str, "Y���̐�Βl:%f", GetBullet(0)->zet);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//	rect.top = 300;
	//	sprintf(str, "Y�̋���:%f", GetBullet(0)->dis.y);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	//	rect.top = 320;
	//	sprintf(str, "�q�b�g:%d", GetBoss(0)->Hitcounter);
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
	//	sprintf(str, "boss�t���O:%d", boss->use);
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
// ��ʑJ��
//=============================================================================
void SetStage( int stage )
{
	//if( state < 0 || state >= STATE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	ENEMY *enemy = GetEnemy(0);					// �G�l�~�[�̃|�C���^�[��������
	ENEMY2 *enemy2 = GetEnemy2(0);				// �G�l�~�[2�̃|�C���^�[��������
	ENEMY3 *enemy3 = GetEnemy3(0);				// �G�l�~�[3�̃|�C���^�[��������
	ENEMY4 *enemy4 = GetEnemy4(0);				// �G�l�~�[4�̃|�C���^�[��������
	ENEMY5 *enemy5 = GetEnemy5(0);				// �G�l�~�[4�̃|�C���^�[��������
	ENEMY6 *enemy6 = GetEnemy6(0);				// �G�l�~�[4�̃|�C���^�[��������
	BULLET *bullet = GetBullet(0);				// �o���b�g�̃|�C���^�[��������
	EBULLET *ebullet = GetEBullet(0);			// �G�l�~�[�o���b�g�̃|�C���^�[��������
	EBULLET2 *ebullet2 = GetEBullet2(0);		// �G�l�~�[�o���b�g2�̃|�C���^�[��������

	BULLET2 *bullet2 = GetBullet2(0);			// �o���b�g�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	TARGET *target = GetTarget(0);
	EFFECT *effect = GetEffect(0);
	BOSS*boss = GetBoss(0);

	// �G�l�~�[1�Ƒ���L����(BB)
	for( int E = 0; E < ENEMY_MAX; E++,enemy++)
	{
		if(enemy->use == false )	continue;

		if( CheckHitBB( GetPlayer(0)->pos, enemy->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X,TEXTURE_ENEMY_SIZE_Y)) )
		{

			player->Hitcounter++;

			if (player->Hitcounter ==10)
			{
				// HP��������
				player->HP-=10;

			}


			if(player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}


			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;

		}
	}

	// �G�l�~�[2�Ƒ���L����(BB)
	for (int E1 = 0; E1 < ENEMY2_MAX; E1++, enemy2++)
	{
		if (enemy2->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy2->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// �G�l�~�[3�Ƒ���L����(BB)
	for (int E1 = 0; E1 < ENEMY3_MAX; E1++, enemy3++)
	{
		if (enemy3->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy3->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY3_SIZE_X, TEXTURE_ENEMY3_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// �G�l�~�[4�Ƒ���L����(BB)
	for (int E1 = 0; E1 < ENEMY4_MAX; E1++, enemy4++)
	{
		if (enemy4->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy4->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY4_SIZE_X, TEXTURE_ENEMY4_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// �G�l�~�[4�Ƒ���L����(BB)
	for (int E1 = 0; E1 < ENEMY5_MAX; E1++, enemy5++)
	{
		if (enemy5->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy5->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY5_SIZE_X, TEXTURE_ENEMY5_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// �G�l�~�[4�Ƒ���L����(BB)
	for (int E1 = 0; E1 < ENEMY6_MAX; E1++, enemy6++)
	{
		if (enemy6->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, enemy6->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY6_SIZE_X, TEXTURE_ENEMY6_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// boss�Ƒ���L����(BB)
	for (int E1 = 0; E1 < BOSS_MAX; E1++, boss++)
	{
		if (boss->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, boss->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y)))
		{

			player->Hitcounter++;

			if (player->Hitcounter == 10)
			{
				// HP��������
				player->HP -= 10;

			}


			if (player->HP <= 0)			// ����L�����N�^�[�͎���
			{
				player->use = false;
			}
			// �G�L�����N�^�[�͓|�����
			//enemy->use = false;
		}
	}


	// �e�ƃv���C���[(BC)
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
					// HP��������
					GetPlayer(j)->HP -= 10;

				}




				GetEBullet(i)->use = false;		// �e�̏��ŏ������s��
				//GetBullet(i)->BBflag = false;	//�ėU����������


				if (GetPlayer(j)->HP <= 0)
				{

					GetPlayer(j)->use = false;		// �G�͓|�����
					SetStage(STAGE_GAME_END);



				}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}


	// �e�ƃv���C���[(BC)
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
					// HP��������
					GetPlayer(j)->HP -= 10;

				}




				GetEBullet2(i)->use = false;		// �e�̏��ŏ������s��
				//GetBullet(i)->BBflag = false;	//�ėU����������


				if (GetPlayer(j)->HP <= 0)
				{

					GetPlayer(j)->use = false;		// �G�͓|�����
					SetStage(STAGE_GAME_END);


				}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}






	// �e�ƓG(BC)
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

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy(j)->use = false;		// �G�͓|�����
				GetEnemy(j)->effectflag = true;	//�G�t�F�N�g���o������
				GetEnemy(j)->BBflag = true;
				GetBullet(i)->BBflag = false;	//�ėU����������


				//GetBoss(i)->Popcounter++;


				// �X�R�A�v�Z
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

	//			GetBullet(i)->use = false;		// �e�̏��ŏ������s��
	//			GetEnemy(j)->use = false;		// �G�͓|�����
	//			GetEnemy(j)->effectflag = true;	//�G�t�F�N�g���o������
	//			GetBullet(i)->BBflag = false;	//�ėU����������
	//			GetBoss(i)->Popcounter++;

	//			if (GetBoss(i)->Popcounter > 13)
	//			{
	//				GetBoss(i)->use = true;

	//				player->counter = 60;

	//			}
	//			// �X�R�A�v�Z
	//			AddScore(100);
	//		}
	//	}
	//}






	//�G�l�~�[�Q�Ƃ̒e�Ƃ̓����蔻�肾��I�n����Y

	//enemy2 = GetEnemy2(0);					// �G�l�~�[�̃|�C���^�[��������

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

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy2(j)->use = false;		// �G�͓|�����
				//GetBoss(i)->Popcounter++;
				GetEnemy2(j)->effectflag2 = true;	//�G�t�F�N�g���o������
				GetEnemy2(j)->BBflag = true;



				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}


				// �X�R�A�v�Z
				AddScore(100);
			}

		}
	}



	// �e�ƃG�l�~�[�R(BC)
	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY3_MAX; j++,enemy3++)
		{
			if (GetEnemy3(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy3(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY3_SIZE_X))
			{

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy3(j)->use = false;		// �G�͓|�����
				GetEnemy3(j)->effectflag3 = true;	//�G�t�F�N�g���o������
				GetBullet(i)->BBflag = false;	//�ėU����������
				GetEnemy3(j)->BBflag = true;
				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}


				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}


	// �e�ƃG�l�~�[4(BC)
	for (int i = 0; i < BULLET_MAX; i++,bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY4_MAX; j++,enemy4++)
		{
			if (GetEnemy4(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy4(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY4_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy4(j)->use = false;		// �G�͓|�����
				GetEnemy4(j)->effectflag4 = true;	//�G�t�F�N�g���o������
				GetBullet(i)->BBflag = false;	//�ėU����������
				GetEnemy4(j)->nextflag = true;
				GetEnemy4(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}



	// �e�ƃG�l�~�[5(BC)
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY5_MAX; j++, enemy5++)
		{
			if (GetEnemy5(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy5(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY5_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy5(j)->use = false;		// �G�͓|�����
				GetEnemy5(j)->effectflag = true;	//�G�t�F�N�g���o������
				GetBullet(i)->BBflag = false;	//�ėU����������
				//GetEnemy5(j)->nextflag = true;
				GetEnemy5(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}

	// �e�ƃG�l�~�[6(BC)
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (GetBullet(i)->use == false) continue;

		for (int j = 0; j < ENEMY6_MAX; j++, enemy6++)
		{
			if (GetEnemy6(j)->use == false) continue;

			if (CheckHitBC(GetBullet(i)->pos, GetEnemy6(j)->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY6_SIZE_X))
			{
				//effect->use = true;

				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetEnemy6(j)->use = false;		// �G�͓|�����
				GetEnemy6(j)->effectflag = true;	//�G�t�F�N�g���o������
				GetBullet(i)->BBflag = false;	//�ėU����������
				//GetEnemy5(j)->nextflag = true;
				GetEnemy6(j)->BBflag = true;

				//GetBoss(i)->Popcounter++;


				//if (GetBoss(i)->Popcounter > 13)
				//{

				//	GetBoss(i)->use = true;

				//}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}




	// �e�ƃ{�X(BC)
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
					// HP��������
					GetBoss(j)->HP -= 15;

				}




				GetBullet(i)->use = false;		// �e�̏��ŏ������s��
				GetBoss(i)->effectflag = true;
				//GetBullet(i)->BBflag = false;	//�ėU����������


				if (GetBoss(j)->HP<=0)
				{

					GetBoss(j)->use = false;		// �G�͓|�����
					SetStage(STAGE_GAME_END);
					


				}



				// �X�R�A�v�Z
				AddScore(100);
			}
		}
	}


	// �e�ƃv���C���[(BC)
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


	// �e2�ƃG�l�~�[(BC)
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

	//			GetBullet2(i)->use = false;		// �e�̏��ŏ������s��
	//			GetEnemy(j)->use = false;		// �G�͓|�����
	//			GetBullet2(i)->BBflag = false;	//�ėU����������
	//			GetEnemy(j)->effectflag = true;	//�G�t�F�N�g���o������
	//			GetBoss(i)->Popcounter++;


	//			if (GetBoss(i)->Popcounter >= 13)
	//			{

	//				GetBoss(i)->use = true;

	//			}


	//			// �X�R�A�v�Z
	//			AddScore(100);
	//		}
	//	}
	//}


	//�G�l�~�[�Q�Ƃ̒e�Ƃ̓����蔻�肾��I�n����Y

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


	//			GetBullet2(i)->use = false;		// �e�̏��ŏ������s��
	//			GetEnemy2(j)->use = false;		// �G�͓|�����
	//			GetEnemy2(j)->effectflag2 = true;	//�G�t�F�N�g���o������
	//			GetBoss(0)->Popcounter++;

	//			// �X�R�A�v�Z
	//			AddScore(100);
	//		}

	//	}
	//}


	//�G�l�~�[�Q�Ƃ̒e�Ƃ̓����蔻�肾��I�n����Y

//enemy2 = GetEnemy2(0);					// �G�l�~�[�̃|�C���^�[��������

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


	//			GetBullet(i)->use = false;		// �e�̏��ŏ������s��

	//			if (boss->HP == 0)
	//			{
	//				GetBoss(j)->use = false;		// �G�͓|�����
	//			}

	//			// �X�R�A�v�Z
	//			AddScore(100);
	//		}

	//	}
	//}




	//�^�[�Q�b�g���ƒe�̓����蔻��

	//for (int i = 0; i < TARGET_MAX; i++, target++)
	//{
	//	if (target->use == false) continue;

	//	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	//	{
	//		if (GetEnemy(j)->use == false) continue;

	//		if (CheckHitBC(GetTarget(i)->pos, GetEnemy(j)->pos, TEXTURE_TARGET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
	//		{
	//			GetBullet(i)->BBflag = true;	// �e�̏��ŏ������s��
	//			//GetEnemy(j)->use = false;		// �G�͓|�����


	//			// �X�R�A�v�Z
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
	//			GetBullet(i)->BBflag = true;	// �e�̏��ŏ������s��
	//			//GetEnemy(j)->use = false;		// �G�͓|�����


	//			// �X�R�A�v�Z
	//			AddScore(100);
	//		}

	//	}
	//}





	// �{�X�ƒe(BC)

	// �����ƓG�̒e(BC)

	// �G���S�ł������ʑJ��
	enemy = GetEnemy(0);					// �G�l�~�[�̃|�C���^�[��������
	//for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	//{

	//	if (GetEnemy(i)->use == true)
	//	{
	//		cnt++;
	//	}
	//	
	//}

	 //���������ʓG���S�ŁH

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

	//�v���C���[��������ƃQ�[���I�[�o�[
	if (player->use == false)
	{
		SetStage(STAGE_GAME_END);
	}



}


//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2 )
{
	size1 /= 2.0f;	// ���T�C�Y�ɂ���
	size2 /= 2.0f;	// ����

	if( pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y )
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
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
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);		// �v���C���[�̍ď�����
	InitEnemy(1);		// �G�l�~�[�̍ď�����
	InitBullet(1);		// �o���b�g�̍ď�����
	InitScore(1);		// �X�R�A�̍ď�����
	InitBG(1);			// BG�̍ď�����
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

