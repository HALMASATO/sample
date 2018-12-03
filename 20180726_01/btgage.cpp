//=============================================================================
//
// �^�C�g����ʏ��� [BTgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "BTgage.h"
#include "player.h"
#include"boss.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBTgage(void);
void SetTextureBTgage(void);
void SetVertexBTgage(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBTgage = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureBTgageLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkBTgage[NUM_VERTEX];			// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkBTgageLogo[NUM_VERTEX];		// ���_���i�[���[�N

BTGAGE					btgageWk[BTGAGE_MAX];			// �v���C���[�\����


//LOGO					logoWk[LOGO_MAX];				// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBTgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BTGAGE *btgage = &btgageWk[0];

	for (int i = 0; i < BTGAGE_MAX; i++, btgage++)
	{
		btgage->use = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BTGAGE,				// �t�@�C���̖��O
								&g_pD3DTextureBTgage);		// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexBTgage();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitBTgage(void)
{
	if(g_pD3DTextureBTgage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBTgage->Release();
		g_pD3DTextureBTgage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBTgage(void)
{
	BOSS*boss = GetBoss(0);
	BTGAGE *btgage = &btgageWk[0];
	PLAYER*player = GetPlayer(0);

	if (boss->use == true)
	{

		btgage->use = true;

	}

	if (btgage->use == true)
	{
		SetTextureBTgage();
		SetVertexBTgage();
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBTgage(void)
{
	BOSS*boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BTGAGE *btgage = &btgageWk[0];

	if (boss->use == true)
	{

		btgage->use = true;
		

	}


	if (btgage->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBTgage);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBTgage, sizeof(VERTEX_2D));
	}
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBTgage(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkBTgage[0].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y, 0.0f);
	g_vertexWkBTgage[1].vtx = D3DXVECTOR3(BTGAGE_POS_X + BTGAGE_SIZE_X, BTGAGE_POS_Y, 0.0f);
	g_vertexWkBTgage[2].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
	g_vertexWkBTgage[3].vtx = D3DXVECTOR3(BTGAGE_POS_X + BTGAGE_SIZE_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkBTgage[0].rhw =
	g_vertexWkBTgage[1].rhw =
	g_vertexWkBTgage[2].rhw =
	g_vertexWkBTgage[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkBTgage[0].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[1].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[2].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);
	g_vertexWkBTgage[3].diffuse = D3DCOLOR_RGBA(255, 100, 100, 100);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBTgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBTgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBTgage(void)
{
	PLAYER *player = GetPlayer(0);
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{
		// �e�N�X�`�����W�̐ݒ�
		g_vertexWkBTgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkBTgage[1].tex = D3DXVECTOR2((float)player->Bcounter / player->MAXBcounter, 0.0f);
		g_vertexWkBTgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkBTgage[3].tex = D3DXVECTOR2((float)player->Bcounter / player->MAXBcounter, 1.0f);
	}

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBTgage(void)
{
	PLAYER *player = GetPlayer(0);
	BOSS*boss = GetBoss(0);

	if (boss->use == true)
	{

		// ���_���W�̐ݒ�
		g_vertexWkBTgage[0].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y, 0.0f);
		g_vertexWkBTgage[1].vtx = D3DXVECTOR3(BTGAGE_POS_X + (float)player->Bcounter, BTGAGE_POS_Y, 0.0f);
		g_vertexWkBTgage[2].vtx = D3DXVECTOR3(BTGAGE_POS_X, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
		g_vertexWkBTgage[3].vtx = D3DXVECTOR3(BTGAGE_POS_X + (float)player->Bcounter, BTGAGE_POS_Y + BTGAGE_SIZE_Y, 0.0f);
	}

}
//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BTGAGE *GetBTgage(int no)
{
	return(&btgageWk[no]);
}