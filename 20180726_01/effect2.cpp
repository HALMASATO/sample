//=============================================================================
//
// �G���� [effect2.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect2.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy2.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect2( int no);
void SetTextureEffect2( int no,int cntPattern );
void SetVertexEffect2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect2 = NULL;		// �e�N�X�`���ւ̃|���S��


EFFECT2					effect2Wk[EFFECT2_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT2 *effect2 = effect2Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT2,				// �t�@�C���̖��O
			&g_pD3DTextureEffect2);			// �ǂݍ��ރ������̃|�C���^


	}



	 //�G�l�~�[�̏���������
	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{
		effect2->use = false;										// �g�p
		effect2->pos = D3DXVECTOR3(i*50+effect2->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		effect2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		effect2->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect2->CountAnim = 0;									// �A�j���J�E���g��������
		effect2->effect2counter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT2_SIZE_X, TEXTURE_EFFECT2_SIZE_Y);
		effect2->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect2->BaseAngle = atan2f(TEXTURE_EFFECT2_SIZE_Y, TEXTURE_EFFECT2_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect2->Texture = g_pD3DTextureEffect2;					// �e�N�X�`�����
		MakeVertexEffect2(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect2(void)
{
	if (g_pD3DTextureEffect2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect2->Release();
		g_pD3DTextureEffect2 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect2(void)
{
	EFFECT2 *effect2 = effect2Wk;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY2*enemy2 = GetEnemy2(0);


			if (effect2->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�A�j���[�V����
				effect2->CountAnim++;
				if ((effect2->CountAnim % TIME_ANIMATION_EFFECT2) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT2 -1> effect2->PatternAnim)
					{
						// �p�^�[���̐؂�ւ�
						effect2->PatternAnim = (effect2->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT2;


					}
					else
					{
						effect2->use = false;
						effect2->PatternAnim = 0;
						GetEnemy2(effect2->i)->effectflag2 = false;
					}

					
					// �e�N�X�`�����W��ݒ�
					SetTextureEffect2(0, effect2->PatternAnim);


					SetVertexEffect2(0);	// �ړ���̍��W�Œ��_��ݒ�


				}


	}

}



			



//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT2 *effect2 = effect2Wk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
		//{
			if (effect2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (effect2->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effect2->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT2, effect2->vertexWk_effect2, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect2( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT2 *effect2 = &effect2Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEffect2( no );

	// rhw�̐ݒ�
	effect2->vertexWk_effect2[0].rhw =
	effect2->vertexWk_effect2[1].rhw =
	effect2->vertexWk_effect2[2].rhw =
	effect2->vertexWk_effect2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect2->vertexWk_effect2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk_effect2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk_effect2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect2->vertexWk_effect2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect2->vertexWk_effect2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect2->vertexWk_effect2[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 0.0f);
	effect2->vertexWk_effect2[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);
	effect2->vertexWk_effect2[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT2);






	//effect2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect2( int no,int cntPattern )
{
	EFFECT2 *effect2 = &effect2Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT2;
	
	effect2->vertexWk_effect2[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect2->vertexWk_effect2[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect2->vertexWk_effect2[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect2->vertexWk_effect2[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect2( int no )
{
	EFFECT2 *effect2 = &effect2Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	effect2->vertexWk_effect2[0].vtx.x = effect2->pos.x - cosf(effect2->BaseAngle + effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[0].vtx.y = effect2->pos.y - sinf(effect2->BaseAngle + effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[0].vtx.z = 0.0f;

	effect2->vertexWk_effect2[1].vtx.x = effect2->pos.x + cosf(effect2->BaseAngle - effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[1].vtx.y = effect2->pos.y - sinf(effect2->BaseAngle - effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[1].vtx.z = 0.0f;

	effect2->vertexWk_effect2[2].vtx.x = effect2->pos.x - cosf(effect2->BaseAngle - effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[2].vtx.y = effect2->pos.y + sinf(effect2->BaseAngle - effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[2].vtx.z = 0.0f;

	effect2->vertexWk_effect2[3].vtx.x = effect2->pos.x + cosf(effect2->BaseAngle + effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[3].vtx.y = effect2->pos.y + sinf(effect2->BaseAngle + effect2->rot.z) * effect2->Radius;
	effect2->vertexWk_effect2[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetEffect2(D3DXVECTOR3 pos, int i)
{
	EFFECT2 *effect2 = &effect2Wk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	//{
		if (effect2->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect2->use = true;				// �g�p��Ԃ֕ύX����
			effect2->pos = pos;				// ���W���Z�b�g
			effect2->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}




//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EFFECT2 *GetEffect2(int no)
{

	
	return(&effect2Wk[no]);



}


