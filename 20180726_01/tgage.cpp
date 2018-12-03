//=============================================================================
//
// �^�C�g����ʏ��� [Tgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Tgage.h"
#include "boss.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTgage(void);
void SetTextureTgage(void);
void SetVertexTgage(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTgage = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureTgageLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTgage[NUM_VERTEX];			// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkTgageLogo[NUM_VERTEX];		// ���_���i�[���[�N

TGAGE					tgageWk[TGAGE_MAX];			// �v���C���[�\����


//LOGO					logoWk[LOGO_MAX];				// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TGAGE *tgage = &tgageWk[0];

	for (int i = 0; i < TGAGE_MAX; i++, tgage++)
	{
		tgage->use = true;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TGAGE,				// �t�@�C���̖��O
								&g_pD3DTextureTgage);		// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexTgage();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitTgage(void)
{
	if(g_pD3DTextureTgage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTgage->Release();
		g_pD3DTextureTgage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTgage(void)
{
	TGAGE *tgage = &tgageWk[0];
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{
		tgage->use = false;

	}

	if (tgage->use == true)
	{
		SetTextureTgage();
		SetVertexTgage();
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TGAGE *tgage = &tgageWk[0];

	if (tgage->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureTgage);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTgage, sizeof(VERTEX_2D));
	}
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTgage(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkTgage[0].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[1].vtx = D3DXVECTOR3(TGAGE_POS_X + TGAGE_SIZE_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[2].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
	g_vertexWkTgage[3].vtx = D3DXVECTOR3(TGAGE_POS_X + TGAGE_SIZE_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTgage[0].rhw =
	g_vertexWkTgage[1].rhw =
	g_vertexWkTgage[2].rhw =
	g_vertexWkTgage[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTgage(void)
{
	PLAYER *player = GetPlayer(0);


	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTgage[1].tex = D3DXVECTOR2((float)player->counter/player->MAXcounter, 0.0f);
	g_vertexWkTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTgage[3].tex = D3DXVECTOR2((float)player->counter / player->MAXcounter, 1.0f);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTgage(void)
{
	PLAYER *player = GetPlayer(0);

	// ���_���W�̐ݒ�
	g_vertexWkTgage[0].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[1].vtx = D3DXVECTOR3(TGAGE_POS_X + (float)player->counter, TGAGE_POS_Y, 0.0f);
	g_vertexWkTgage[2].vtx = D3DXVECTOR3(TGAGE_POS_X, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
	g_vertexWkTgage[3].vtx = D3DXVECTOR3(TGAGE_POS_X + (float)player->counter, TGAGE_POS_Y + TGAGE_SIZE_Y, 0.0f);
}
//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
TGAGE *GetTgage(int no)
{
	return(&tgageWk[no]);
}