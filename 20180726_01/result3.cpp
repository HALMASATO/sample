//=============================================================================
//
// ���U���g��ʏ��� [result3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "result3.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult3(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult3 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResult3Logo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkResult3[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkResult3Logo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT3,				// �t�@�C���̖��O
								&g_pD3DTextureResult3);		// �ǂݍ��ރ������[

	//D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
	//							TEXTURE_RESULT3_LOGO,		// �t�@�C���̖��O
	//							&g_pD3DTextureResult3Logo);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexResult3();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult3(void)
{
	if(g_pD3DTextureResult3 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResult3->Release();
		g_pD3DTextureResult3 = NULL;
	}

	if(g_pD3DTextureResult3Logo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResult3Logo->Release();
		g_pD3DTextureResult3Logo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult3(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResult3);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult3, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureResult3Logo);

	//// �|���S���̕`��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult3Logo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult3(void)
{	
	// ���_���W�̐ݒ�
	g_vertexWkResult3[0].vtx = D3DXVECTOR3(RESULT3_POS_X, RESULT3_POS_Y, 0.0f);
	g_vertexWkResult3[1].vtx = D3DXVECTOR3(RESULT3_POS_X + RESULT3_SIZE_X, RESULT3_POS_Y, 0.0f);
	g_vertexWkResult3[2].vtx = D3DXVECTOR3(RESULT3_POS_X, RESULT3_POS_Y + RESULT3_SIZE_Y, 0.0f);
	g_vertexWkResult3[3].vtx = D3DXVECTOR3(RESULT3_POS_X + RESULT3_SIZE_X, RESULT3_POS_Y + RESULT3_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult3[0].rhw =
	g_vertexWkResult3[1].rhw =
	g_vertexWkResult3[2].rhw =
	g_vertexWkResult3[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult3[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult3[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult3[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkResult3Logo[0].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X, RESULT3LOGO_POS_Y, 0.0f);
	g_vertexWkResult3Logo[1].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X + RESULT3LOGO_SIZE_X, RESULT3LOGO_POS_Y, 0.0f);
	g_vertexWkResult3Logo[2].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X, RESULT3LOGO_POS_Y + RESULT3LOGO_SIZE_Y, 0.0f);
	g_vertexWkResult3Logo[3].vtx = D3DXVECTOR3(RESULT3LOGO_POS_X + RESULT3LOGO_SIZE_X, RESULT3LOGO_POS_Y + RESULT3LOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult3Logo[0].rhw =
	g_vertexWkResult3Logo[1].rhw =
	g_vertexWkResult3Logo[2].rhw =
	g_vertexWkResult3Logo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult3Logo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult3Logo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult3Logo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult3Logo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult3Logo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult3Logo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

