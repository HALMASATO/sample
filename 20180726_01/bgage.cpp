//=============================================================================
//
// �^�C�g����ʏ��� [Bgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Bgage.h"
#include "bullet.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBgage(void);
void SetTextureBgage(void);
void SetVertexBgage(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBgage = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureBgageLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkBgage[NUM_VERTEX];			// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkBgageLogo[NUM_VERTEX];		// ���_���i�[���[�N


BGAGE					bgageWk[BGAGE_MAX];			// �v���C���[�\����

//LOGO					logoWk[LOGO_MAX];				// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BGAGE *bgage = &bgageWk[0];


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BGAGE,				// �t�@�C���̖��O
								&g_pD3DTextureBgage);		// �ǂݍ��ރ������[

	for (int i = 0; i < BGAGE_MAX; i++, bgage++)
	{
		bgage->use = false;
	}

	//D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
	//							TEXTURE_BGAGE_LOGO,			// �t�@�C���̖��O
	//							&g_pD3DTextureBgageLogo);	// �ǂݍ��ރ������[
	//logo->use = false;

	// ���_���̍쐬
	MakeVertexBgage();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBgage(void)
{
	if(g_pD3DTextureBgage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBgage->Release();
		g_pD3DTextureBgage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBgage(void)
{

	SetTextureBgage();
	SetVertexBgage();



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BGAGE *bgage = &bgageWk[0];

	if (bgage->use == false)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBgage);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBgage, sizeof(VERTEX_2D));
	}

}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBgage(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkBgage[0].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[1].vtx = D3DXVECTOR3(BGAGE_POS_X + BGAGE_SIZE_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[2].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);
	g_vertexWkBgage[3].vtx = D3DXVECTOR3(BGAGE_POS_X + BGAGE_SIZE_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkBgage[0].rhw =
	g_vertexWkBgage[1].rhw =
	g_vertexWkBgage[2].rhw =
	g_vertexWkBgage[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkBgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBgage(void)
{
	BULLET *bullet = GetBullet(0);


	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBgage[1].tex = D3DXVECTOR2((float)bullet->reload/bullet->MAXreload, 0.0f);
	g_vertexWkBgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBgage[3].tex = D3DXVECTOR2((float)bullet->reload / bullet->MAXreload, 1.0f);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBgage(void)
{
	BULLET *bullet = GetBullet(0);


	// ���_���W�̐ݒ�
	g_vertexWkBgage[0].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[1].vtx = D3DXVECTOR3(BGAGE_POS_X + (float)bullet->counter, BGAGE_POS_Y, 0.0f);
	g_vertexWkBgage[2].vtx = D3DXVECTOR3(BGAGE_POS_X, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);
	g_vertexWkBgage[3].vtx = D3DXVECTOR3(BGAGE_POS_X + (float)bullet->counter, BGAGE_POS_Y + BGAGE_SIZE_Y, 0.0f);


}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
//LOGO *GetLogo(int no)
//{
//
//
//	return(&logoWk[no]);
//
//
//
//}
