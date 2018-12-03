//=============================================================================
//
// �^�C�g����ʏ��� [pgage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "pgage.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPgage(void);
void SetTexturePgage(void);
void SetVertexPgage(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePgage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePgageLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkPgage[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkPgageLogo[NUM_VERTEX];		// ���_���i�[���[�N



//LOGO					logoWk[LOGO_MAX];				// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PGAGE,				// �t�@�C���̖��O
								&g_pD3DTexturePgage);		// �ǂݍ��ރ������[

	//D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
	//							TEXTURE_PGAGE_LOGO,			// �t�@�C���̖��O
	//							&g_pD3DTexturePgageLogo);	// �ǂݍ��ރ������[
	//logo->use = false;

	// ���_���̍쐬
	MakeVertexPgage();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPgage(void)
{
	if(g_pD3DTexturePgage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePgage->Release();
		g_pD3DTexturePgage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePgage(void)
{

	SetTexturePgage();
	SetVertexPgage();



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexturePgage);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkPgage, sizeof(VERTEX_2D));

}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPgage(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkPgage[0].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[1].vtx = D3DXVECTOR3(PGAGE_POS_X + PGAGE_SIZE_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[2].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);
	g_vertexWkPgage[3].vtx = D3DXVECTOR3(PGAGE_POS_X + PGAGE_SIZE_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkPgage[0].rhw =
	g_vertexWkPgage[1].rhw =
	g_vertexWkPgage[2].rhw =
	g_vertexWkPgage[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkPgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkPgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkPgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePgage(void)
{
	PLAYER *player = GetPlayer(0);


	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkPgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPgage[1].tex = D3DXVECTOR2((float)player->HP/player->MAXHP, 0.0f);
	g_vertexWkPgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPgage[3].tex = D3DXVECTOR2((float)player->HP / player->MAXHP, 1.0f);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPgage(void)
{
	PLAYER *player = GetPlayer(0);


	// ���_���W�̐ݒ�
	g_vertexWkPgage[0].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[1].vtx = D3DXVECTOR3(PGAGE_POS_X + (float)player->HP, PGAGE_POS_Y, 0.0f);
	g_vertexWkPgage[2].vtx = D3DXVECTOR3(PGAGE_POS_X, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);
	g_vertexWkPgage[3].vtx = D3DXVECTOR3(PGAGE_POS_X + (float)player->HP, PGAGE_POS_Y + PGAGE_SIZE_Y, 0.0f);


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
