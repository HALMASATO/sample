//=============================================================================
//
// �G���� [effect4.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect4.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy4.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect4( int no);
void SetTextureEffect4( int no,int cntPattern );
void SetVertexEffect4( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect4 = NULL;		// �e�N�X�`���ւ̃|���S��


EFFECT4					effect4Wk[EFFECT4_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect4(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = effect4Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT4,				// �t�@�C���̖��O
			&g_pD3DTextureEffect4);			// �ǂݍ��ރ������̃|�C���^


	}



	 //�G�l�~�[�̏���������
	for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
	{
		effect4->use = false;										// �g�p
		effect4->pos = D3DXVECTOR3(i*50+effect4->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		effect4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		effect4->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect4->CountAnim = 0;									// �A�j���J�E���g��������
		effect4->effect4counter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT4_SIZE_X, TEXTURE_EFFECT4_SIZE_Y);
		effect4->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect4->BaseAngle = atan2f(TEXTURE_EFFECT4_SIZE_Y, TEXTURE_EFFECT4_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect4->Texture = g_pD3DTextureEffect4;					// �e�N�X�`�����
		MakeVertexEffect4(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect4(void)
{
	if (g_pD3DTextureEffect4 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect4->Release();
		g_pD3DTextureEffect4 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect4(void)
{
	EFFECT4 *effect4 = effect4Wk;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect4->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�A�j���[�V����
				effect4->CountAnim++;
				if ((effect4->CountAnim % TIME_ANIMATION_EFFECT4) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT4 -1> effect4->PatternAnim)
					{
						// �p�^�[���̐؂�ւ�
						effect4->PatternAnim = (effect4->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT4;


					}
					else
					{
						effect4->use = false;
						effect4->PatternAnim = 0;
						GetEnemy4(effect4->i)->effectflag4 = false;
					}

					
					// �e�N�X�`�����W��ݒ�
					SetTextureEffect4(0, effect4->PatternAnim);


					SetVertexEffect4(0);	// �ړ���̍��W�Œ��_��ݒ�


				}

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = effect4Wk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
		//{
			if (effect4->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (effect4->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effect4->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT4, effect4->vertexWk_effect4, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect4( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT4 *effect4 = &effect4Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEffect4( no );

	// rhw�̐ݒ�
	effect4->vertexWk_effect4[0].rhw =
	effect4->vertexWk_effect4[1].rhw =
	effect4->vertexWk_effect4[2].rhw =
	effect4->vertexWk_effect4[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect4->vertexWk_effect4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect4->vertexWk_effect4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect4->vertexWk_effect4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect4->vertexWk_effect4[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT4, 0.0f);
	effect4->vertexWk_effect4[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT4);
	effect4->vertexWk_effect4[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT4, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT4);






	//effect4->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect4->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect4->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect4->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect4( int no,int cntPattern )
{
	EFFECT4 *effect4 = &effect4Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT4;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT4;
	
	effect4->vertexWk_effect4[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect4->vertexWk_effect4[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect4->vertexWk_effect4[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect4->vertexWk_effect4[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect4( int no )
{
	EFFECT4 *effect4 = &effect4Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	effect4->vertexWk_effect4[0].vtx.x = effect4->pos.x - cosf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[0].vtx.y = effect4->pos.y - sinf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[0].vtx.z = 0.0f;

	effect4->vertexWk_effect4[1].vtx.x = effect4->pos.x + cosf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[1].vtx.y = effect4->pos.y - sinf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[1].vtx.z = 0.0f;

	effect4->vertexWk_effect4[2].vtx.x = effect4->pos.x - cosf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[2].vtx.y = effect4->pos.y + sinf(effect4->BaseAngle - effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[2].vtx.z = 0.0f;

	effect4->vertexWk_effect4[3].vtx.x = effect4->pos.x + cosf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[3].vtx.y = effect4->pos.y + sinf(effect4->BaseAngle + effect4->rot.z) * effect4->Radius;
	effect4->vertexWk_effect4[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetEffect4(D3DXVECTOR3 pos, int i)
{
	EFFECT4 *effect4 = &effect4Wk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < EFFECT4_MAX; i++, effect4++)
	//{
		if (effect4->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect4->use = true;				// �g�p��Ԃ֕ύX����
			effect4->pos = pos;				// ���W���Z�b�g
			effect4->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}




//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EFFECT4 *GetEffect4(int no)
{

	
	return(&effect4Wk[no]);



}


