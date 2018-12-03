//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Selectbg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSelBG(void);
void SetVertexSelBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_yakei = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_tuki = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureSelBG_HP = NULL;		// �e�N�X�`���ւ̃|�C���^




VERTEX_2D				g_vertexWkSelBG_yakei[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_vertexWkSelBG_tuki[NUM_VERTEX];		// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkSelBG_HP[NUM_VERTEX];		// ���_���i�[���[�N



D3DXVECTOR2				g_posSelBG;					// �w�i�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSelBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_SelBG00,					// �t�@�C���̖��O
			&g_pD3DTextureSelBG_yakei);			// �ǂݍ��ރ������[

		//D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		//	TEXTURE_GAME_SelBG01_tuki,				// �t�@�C���̖��O
		//	&g_pD3DTextureSelBG_tuki);				// �ǂݍ��ރ������[

		//D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		//	TEXTURE_GAME_SelBG02_heart,			// �t�@�C���̖��O
		//	&g_pD3DTextureSelBG_HP);			// �ǂݍ��ރ������[


	}

	g_posSelBG = D3DXVECTOR2(0.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexSelBG();

	g_posSelBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexSelBG();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelBG(void)
{
	if(g_pD3DTextureSelBG_yakei != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSelBG_yakei->Release();
		g_pD3DTextureSelBG_yakei = NULL;
	}

	//if (g_pD3DTextureSelBG_tuki != NULL)
	//{// �e�N�X�`���̊J��
	//	g_pD3DTextureSelBG_tuki->Release();
	//	g_pD3DTextureSelBG_tuki = NULL;
	//}

	//if (g_pD3DTextureSelBG_HP != NULL)
	//{// �e�N�X�`���̊J��
	//	g_pD3DTextureSelBG_HP->Release();
	//	g_pD3DTextureSelBG_HP = NULL;
	//}



}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelBG(void)
{
	// ���t���[�����s���鏈��

	// �X�N���[������
	g_posSelBG.x = GetPlayer(0)->pos.x / 250.0f;
	//g_posSelBG.y = -GetPlayer(0)->pos.y / 250.0f;


	SetVertexSelBG();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelBG(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/*yakei*/
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureSelBG_yakei);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_yakei, sizeof(VERTEX_2D));


	/*tuki*/

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureSelBG_tuki);

	//// �|���S���̕`��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_tuki, sizeof(VERTEX_2D));


	/*heart*/
//
//// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pD3DTextureSelBG_HP);
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkSelBG_HP, sizeof(VERTEX_2D));
//




}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSelBG(void)
{

	/*ossan*/

	// ���_���W�̐ݒ�
	g_vertexWkSelBG_yakei[0].vtx = D3DXVECTOR3(SelBG00_POS_X, SelBG00_POS_Y, 0.0f);
	g_vertexWkSelBG_yakei[1].vtx = D3DXVECTOR3(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y, 0.0f);
	g_vertexWkSelBG_yakei[2].vtx = D3DXVECTOR3(SelBG00_POS_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f);
	g_vertexWkSelBG_yakei[3].vtx = D3DXVECTOR3(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkSelBG_yakei[0].rhw =
	g_vertexWkSelBG_yakei[1].rhw =
	g_vertexWkSelBG_yakei[2].rhw =
	g_vertexWkSelBG_yakei[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkSelBG_yakei[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_yakei[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkSelBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	/*tuki*/

	// ���_���W�̐ݒ�
	g_vertexWkSelBG_tuki[0].vtx = D3DXVECTOR3(SelBG01_POS_X, SelBG01_POS_Y, 0.0f);
	g_vertexWkSelBG_tuki[1].vtx = D3DXVECTOR3(SelBG01_POS_X + SelBG01_SIZE_X, SelBG01_POS_Y, 0.0f);
	g_vertexWkSelBG_tuki[2].vtx = D3DXVECTOR3(SelBG01_POS_X, SelBG01_POS_Y + SelBG01_SIZE_Y, 0.0f);
	g_vertexWkSelBG_tuki[3].vtx = D3DXVECTOR3(SelBG01_POS_X + SelBG01_SIZE_X, SelBG01_POS_Y + SelBG01_SIZE_Y, 0.0f);
				 
	// rhw�̐ݒ� 
	g_vertexWkSelBG_tuki[0].rhw =
	g_vertexWkSelBG_tuki[1].rhw =
	g_vertexWkSelBG_tuki[2].rhw =
	g_vertexWkSelBG_tuki[3].rhw = 1.0f;
				 
	// ���ˌ��̐ݒ�
	g_vertexWkSelBG_tuki[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkSelBG_tuki[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				 
	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkSelBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	///*ossan*/

	//// ���_���W�̐ݒ�
	//g_vertexWkSelBG_HP[0].vtx = D3DXVECTOR3(SelBG02_POS_X, SelBG02_POS_Y, 0.0f);
	//g_vertexWkSelBG_HP[1].vtx = D3DXVECTOR3(SelBG02_POS_X + SelBG02_SIZE_X, SelBG02_POS_Y, 0.0f);
	//g_vertexWkSelBG_HP[2].vtx = D3DXVECTOR3(SelBG02_POS_X, SelBG02_POS_Y + SelBG02_SIZE_Y, 0.0f);
	//g_vertexWkSelBG_HP[3].vtx = D3DXVECTOR3(SelBG02_POS_X + SelBG02_SIZE_X, SelBG02_POS_Y + SelBG02_SIZE_Y, 0.0f);

	//// rhw�̐ݒ� 
	//g_vertexWkSelBG_HP[0].rhw =
	//g_vertexWkSelBG_HP[1].rhw =
	//g_vertexWkSelBG_HP[2].rhw =
	//g_vertexWkSelBG_HP[3].rhw = 1.0f;

	//// ���ˌ��̐ݒ�
	//g_vertexWkSelBG_HP[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkSelBG_HP[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkSelBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkSelBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkSelBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkSelBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSelBG(void)
{
	//// ���_���W�̐ݒ�
	//g_vertexWkSelBG[0].vtx = D3DXVECTOR2(SelBG00_POS_X, SelBG00_POS_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[1].vtx = D3DXVECTOR2(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[2].vtx = D3DXVECTOR2(SelBG00_POS_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f) + g_posSelBG;
	//g_vertexWkSelBG[3].vtx = D3DXVECTOR2(SelBG00_POS_X + SelBG00_SIZE_X, SelBG00_POS_Y + SelBG00_SIZE_Y, 0.0f) + g_posSelBG;

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkSelBG_yakei[0].tex = D3DXVECTOR2(0.0f, 0.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[1].tex = D3DXVECTOR2(1.0f, 0.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[2].tex = D3DXVECTOR2(0.0f, 1.0f)+g_posSelBG;
	g_vertexWkSelBG_yakei[3].tex = D3DXVECTOR2(1.0f, 1.0f)+g_posSelBG;

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkSelBG_tuki[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkSelBG_tuki[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkSelBG_tuki[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkSelBG_tuki[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkSelBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkSelBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkSelBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkSelBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
//SelBG *GetSelBG(int no)
//{
//	return(&SelBGWk[no]);
//}

