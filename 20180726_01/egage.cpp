//=============================================================================
//
// �^�C�g����ʏ��� [eage.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "egage.h"
#include "input.h"
#include "boss.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEgage(void);
void SetTextureEgage(void);
void SetVertexEgage(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEgage = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkEgage[NUM_VERTEX];			// ���_���i�[���[�N



//LOGO					logoWk[LOGO_MAX];				// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EGAGE,				// �t�@�C���̖��O
								&g_pD3DTextureEgage);		// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexEgage();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEgage(void)
{
	if(g_pD3DTextureEgage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEgage->Release();
		g_pD3DTextureEgage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEgage(void)
{

	SetTextureEgage();
	SetVertexEgage();



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEgage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = GetBoss(0);

	if (boss->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEgage);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkEgage, sizeof(VERTEX_2D));
	}

}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEgage(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkEgage[0].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[1].vtx = D3DXVECTOR3(EGAGE_POS_X + EGAGE_SIZE_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[2].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);
	g_vertexWkEgage[3].vtx = D3DXVECTOR3(EGAGE_POS_X + EGAGE_SIZE_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkEgage[0].rhw =
	g_vertexWkEgage[1].rhw =
	g_vertexWkEgage[2].rhw =
	g_vertexWkEgage[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkEgage[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkEgage[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkEgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkEgage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkEgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkEgage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEgage(void)
{
	BOSS *boss = GetBoss(0);


	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkEgage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkEgage[1].tex = D3DXVECTOR2((float)boss->HP/boss->MAXHP, 0.0f);
	g_vertexWkEgage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkEgage[3].tex = D3DXVECTOR2((float)boss->HP / boss->MAXHP, 1.0f);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEgage(void)
{
	BOSS *boss = GetBoss(0);


	// ���_���W�̐ݒ�
	g_vertexWkEgage[0].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[1].vtx = D3DXVECTOR3(EGAGE_POS_X + (float)boss->HP, EGAGE_POS_Y, 0.0f);
	g_vertexWkEgage[2].vtx = D3DXVECTOR3(EGAGE_POS_X, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);
	g_vertexWkEgage[3].vtx = D3DXVECTOR3(EGAGE_POS_X + (float)boss->HP, EGAGE_POS_Y + EGAGE_SIZE_Y, 0.0f);


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
