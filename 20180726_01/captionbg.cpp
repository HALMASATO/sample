//=============================================================================
//
// �w�i���� [captionbg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "captionbg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCaptionBG(void);
void SetVertexCaptionBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCaptionBG = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureCaptionBG_tuki = NULL;		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureBG_HP = NULL;		// �e�N�X�`���ւ̃|�C���^




VERTEX_2D				g_vertexWkCaptionBG[NUM_VERTEX];	// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkBG_tuki[NUM_VERTEX];		// ���_���i�[���[�N
//VERTEX_2D				g_vertexWkBG_HP[NUM_VERTEX];		// ���_���i�[���[�N



static D3DXVECTOR2				g_posBG;					// �w�i�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCaptionBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_CAPTIONBG00,					// �t�@�C���̖��O
			&g_pD3DTextureCaptionBG);			// �ǂݍ��ރ������[

		//D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		//	TEXTURE_GAME_BG01_tuki,				// �t�@�C���̖��O
		//	&g_pD3DTextureBG_tuki);				// �ǂݍ��ރ������[

		//D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		//	TEXTURE_GAME_BG02_heart,			// �t�@�C���̖��O
		//	&g_pD3DTextureBG_HP);			// �ǂݍ��ރ������[


	}

	g_posBG = D3DXVECTOR2(0.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexCaptionBG();

	//g_posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexCaptionBG();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCaptionBG(void)
{
	if(g_pD3DTextureCaptionBG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCaptionBG->Release();
		g_pD3DTextureCaptionBG = NULL;
	}

	//if (g_pD3DTextureBG_tuki != NULL)
	//{// �e�N�X�`���̊J��
	//	g_pD3DTextureBG_tuki->Release();
	//	g_pD3DTextureBG_tuki = NULL;
	//}

	//if (g_pD3DTextureBG_HP != NULL)
	//{// �e�N�X�`���̊J��
	//	g_pD3DTextureBG_HP->Release();
	//	g_pD3DTextureBG_HP = NULL;
	//}



}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCaptionBG(void)
{
	// ���t���[�����s���鏈��

	// �X�N���[������
	//g_posBG.x = GetPlayer(0)->pos.x / 250.0f;
	//g_posBG.y = -GetPlayer(0)->pos.y / 250.0f;


	SetVertexCaptionBG();


	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_GAME);
	}
	// �Q�[���p�b�h�łňړ�����
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		SetStage(STAGE_GAME);
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_GAME);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCaptionBG(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/*yakei*/
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureCaptionBG);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkCaptionBG, sizeof(VERTEX_2D));


	/*tuki*/

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureBG_tuki);

	//// �|���S���̕`��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG_tuki, sizeof(VERTEX_2D));


	/*heart*/
//
//// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pD3DTextureBG_HP);
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG_HP, sizeof(VERTEX_2D));
//




}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCaptionBG(void)
{

	/*ossan*/

	// ���_���W�̐ݒ�
	g_vertexWkCaptionBG[0].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X, CAPTIONBG00_POS_Y, 0.0f);
	g_vertexWkCaptionBG[1].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X + CAPTIONBG00_SIZE_X, CAPTIONBG00_POS_Y, 0.0f);
	g_vertexWkCaptionBG[2].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X, CAPTIONBG00_POS_Y + CAPTIONBG00_SIZE_Y, 0.0f);
	g_vertexWkCaptionBG[3].vtx = D3DXVECTOR3(CAPTIONBG00_POS_X + CAPTIONBG00_SIZE_X, CAPTIONBG00_POS_Y + CAPTIONBG00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkCaptionBG[0].rhw =
	g_vertexWkCaptionBG[1].rhw =
	g_vertexWkCaptionBG[2].rhw =
	g_vertexWkCaptionBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkCaptionBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkCaptionBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	/*tuki*/

	//// ���_���W�̐ݒ�
	//g_vertexWkCaptionBG[0].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X, CAPTIONBG01_POS_Y, 0.0f);
	//g_vertexWkCaptionBG[1].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X +CAPTIONBG01_SIZE_X, CAPTIONBG01_POS_Y, 0.0f);
	//g_vertexWkCaptionBG[2].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X, CAPTIONBG01_POS_Y + CAPTIONBG01_SIZE_Y, 0.0f);
	//g_vertexWkCaptionBG[3].vtx = D3DXVECTOR3(CAPTIONBG01_POS_X +CAPTIONBG01_SIZE_X, CAPTIONBG01_POS_Y + CAPTIONBG01_SIZE_Y, 0.0f);
	//			 
	//// rhw�̐ݒ� 
	//g_vertexWkCaptionBG[0].rhw =
	//g_vertexWkCaptionBG[1].rhw =
	//g_vertexWkCaptionBG[2].rhw =
	//g_vertexWkCaptionBG[3].rhw = 1.0f;
	//			 
	//// ���ˌ��̐ݒ�
	//g_vertexWkCaptionBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkCaptionBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//			 
	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	///*ossan*/

	//// ���_���W�̐ݒ�
	//g_vertexWkBG_HP[0].vtx = D3DXVECTOR3(BG02_POS_X, BG02_POS_Y, 0.0f);
	//g_vertexWkBG_HP[1].vtx = D3DXVECTOR3(BG02_POS_X + BG02_SIZE_X, BG02_POS_Y, 0.0f);
	//g_vertexWkBG_HP[2].vtx = D3DXVECTOR3(BG02_POS_X, BG02_POS_Y + BG02_SIZE_Y, 0.0f);
	//g_vertexWkBG_HP[3].vtx = D3DXVECTOR3(BG02_POS_X + BG02_SIZE_X, BG02_POS_Y + BG02_SIZE_Y, 0.0f);

	//// rhw�̐ݒ� 
	//g_vertexWkBG_HP[0].rhw =
	//g_vertexWkBG_HP[1].rhw =
	//g_vertexWkBG_HP[2].rhw =
	//g_vertexWkBG_HP[3].rhw = 1.0f;

	//// ���ˌ��̐ݒ�
	//g_vertexWkBG_HP[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkBG_HP[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexCaptionBG(void)
{
	//// ���_���W�̐ݒ�
	//g_vertexWkBG[0].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[1].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[2].vtx = D3DXVECTOR2(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;
	//g_vertexWkBG[3].vtx = D3DXVECTOR2(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f)+g_posBG;
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f)+g_posBG;
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f)+g_posBG;
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f)+g_posBG;

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkCaptionBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkCaptionBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkCaptionBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkCaptionBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// �e�N�X�`�����W�̐ݒ�
	//g_vertexWkBG_HP[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkBG_HP[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkBG_HP[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkBG_HP[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
//BG *GetBG(int no)
//{
//	return(&BGWk[no]);
//}

