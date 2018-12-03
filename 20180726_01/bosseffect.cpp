//=============================================================================
//
// �G���� [bosseffect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bosseffect.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBossEffect( int no);
void SetTextureBossEffect( int no,int cntPattern );
void SetVertexBossEffect( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBossEffect = NULL;		// �e�N�X�`���ւ̃|���S��


BOSSEFFECT					bosseffectWk[BOSSEFFECT_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBossEffect(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = bosseffectWk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSSEFFECT,				// �t�@�C���̖��O
			&g_pD3DTextureBossEffect);			// �ǂݍ��ރ������̃|�C���^


	}



	 //�G�l�~�[�̏���������
	for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
	{
		bosseffect->use = false;										// �g�p
		bosseffect->pos = D3DXVECTOR3(i*50+bosseffect->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		bosseffect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		bosseffect->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		bosseffect->CountAnim = 0;									// �A�j���J�E���g��������
		bosseffect->bosseffectcounter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSSEFFECT_SIZE_X, TEXTURE_BOSSEFFECT_SIZE_Y);
		bosseffect->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		bosseffect->BaseAngle = atan2f(TEXTURE_BOSSEFFECT_SIZE_Y, TEXTURE_BOSSEFFECT_SIZE_X);	// �G�l�~�[�̊p�x��������

		bosseffect->Texture = g_pD3DTextureBossEffect;					// �e�N�X�`�����
		MakeVertexBossEffect(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBossEffect(void)
{
	if (g_pD3DTextureBossEffect != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBossEffect->Release();
		g_pD3DTextureBossEffect = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBossEffect(void)
{
	BOSSEFFECT *bosseffect = bosseffectWk;				// �G�l�~�[�̃|�C���^�[��������
	BOSS *boss = GetBoss(0);							// �{�X�̃|�C���^�[��������


	if (bosseffect->use == true)			// �g�p���Ă����ԂȂ�X�V����
	{

		//�A�j���[�V����
		bosseffect->CountAnim++;
		if ((bosseffect->CountAnim % TIME_ANIMATION_BOSSEFFECT) == 0)
		{
			if (ANIM_PATTERN_NUM_BOSSEFFECT - 1 > bosseffect->PatternAnim)
			{
				// �p�^�[���̐؂�ւ�
				bosseffect->PatternAnim = (bosseffect->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSSEFFECT;


			}
			else
			{
				bosseffect->use = false;
				bosseffect->PatternAnim = 0;
				GetBoss(bosseffect->i)->effectflag= false;
			}
			

			// �e�N�X�`�����W��ݒ�
			SetTextureBossEffect(0, bosseffect->PatternAnim);


			SetVertexBossEffect(0);	// �ړ���̍��W�Œ��_��ݒ�


		}
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawBossEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = bosseffectWk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
		//{
			if (bosseffect->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (bosseffect->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, bosseffect->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSEFFECT, bosseffect->vertexWk_bosseffect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBossEffect( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexBossEffect( no );

	// rhw�̐ݒ�
	bosseffect->vertexWk_bosseffect[0].rhw =
	bosseffect->vertexWk_bosseffect[1].rhw =
	bosseffect->vertexWk_bosseffect[2].rhw =
	bosseffect->vertexWk_bosseffect[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bosseffect->vertexWk_bosseffect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosseffect->vertexWk_bosseffect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bosseffect->vertexWk_bosseffect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bosseffect->vertexWk_bosseffect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT, 0.0f);
	bosseffect->vertexWk_bosseffect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT);
	bosseffect->vertexWk_bosseffect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT);






	//bosseffect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bosseffect->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bosseffect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bosseffect->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBossEffect( int no,int cntPattern )
{
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT;
	
	bosseffect->vertexWk_bosseffect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bosseffect->vertexWk_bosseffect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bosseffect->vertexWk_bosseffect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bosseffect->vertexWk_bosseffect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBossEffect( int no )
{
	BOSSEFFECT *bosseffect = &bosseffectWk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	bosseffect->vertexWk_bosseffect[0].vtx.x = bosseffect->pos.x - cosf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[0].vtx.y = bosseffect->pos.y - sinf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[0].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[1].vtx.x = bosseffect->pos.x + cosf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[1].vtx.y = bosseffect->pos.y - sinf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[1].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[2].vtx.x = bosseffect->pos.x - cosf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[2].vtx.y = bosseffect->pos.y + sinf(bosseffect->BaseAngle - bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[2].vtx.z = 0.0f;

	bosseffect->vertexWk_bosseffect[3].vtx.x = bosseffect->pos.x + cosf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[3].vtx.y = bosseffect->pos.y + sinf(bosseffect->BaseAngle + bosseffect->rot.z) * bosseffect->Radius;
	bosseffect->vertexWk_bosseffect[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetBossEffect(D3DXVECTOR3 pos, int i)
{
	BOSSEFFECT *bosseffect = &bosseffectWk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < BOSSEFFECT_MAX; i++, bosseffect++)
	//{
		if (bosseffect->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bosseffect->use = true;				// �g�p��Ԃ֕ύX����
			bosseffect->pos = pos;				// ���W���Z�b�g
			bosseffect->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}




//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSSEFFECT *GetBossEffect(int no)
{

	
	return(&bosseffectWk[no]);



}


