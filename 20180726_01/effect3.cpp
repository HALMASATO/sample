//=============================================================================
//
// �G���� [effect3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect3.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include "enemy3.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect3( int no);
void SetTextureEffect3( int no,int cntPattern );
void SetVertexEffect3( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect3 = NULL;		// �e�N�X�`���ւ̃|���S��


EFFECT3					effect3Wk[EFFECT3_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect3(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = effect3Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT3,				// �t�@�C���̖��O
			&g_pD3DTextureEffect3);			// �ǂݍ��ރ������̃|�C���^
	}



	 //�G�l�~�[�̏���������
	for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
	{
		effect3->use = false;										// �g�p
		effect3->pos = D3DXVECTOR3(i*50+effect3->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		effect3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		effect3->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect3->CountAnim = 0;									// �A�j���J�E���g��������
		effect3->effect3counter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT3_SIZE_X, TEXTURE_EFFECT3_SIZE_Y);
		effect3->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect3->BaseAngle = atan2f(TEXTURE_EFFECT3_SIZE_Y, TEXTURE_EFFECT3_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect3->Texture = g_pD3DTextureEffect3;					// �e�N�X�`�����
		MakeVertexEffect3(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect3(void)
{
	if (g_pD3DTextureEffect3 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect3->Release();
		g_pD3DTextureEffect3 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect3(void)
{
	EFFECT3 *effect3 = effect3Wk;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY3*enemy3 = GetEnemy3(0);




			if (effect3->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�A�j���[�V����
				effect3->CountAnim++;
				if ((effect3->CountAnim % TIME_ANIMATION_EFFECT3) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT3 -1> effect3->PatternAnim)
					{
						// �p�^�[���̐؂�ւ�
						effect3->PatternAnim = (effect3->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT3;


					}
					else
					{
						effect3->use = false;
						effect3->PatternAnim = 0;
						GetEnemy3(effect3->i)->effectflag3 = false;
					}

					
					// �e�N�X�`�����W��ݒ�
					SetTextureEffect3(0, effect3->PatternAnim);


					SetVertexEffect3(0);	// �ړ���̍��W�Œ��_��ݒ�


				}
	}

}



			



//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = effect3Wk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
		//{
			if (effect3->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (effect3->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effect3->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT3, effect3->vertexWk_effect3, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect3( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT3 *effect3 = &effect3Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEffect3( no );

	// rhw�̐ݒ�
	effect3->vertexWk_effect3[0].rhw =
	effect3->vertexWk_effect3[1].rhw =
	effect3->vertexWk_effect3[2].rhw =
	effect3->vertexWk_effect3[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect3->vertexWk_effect3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect3->vertexWk_effect3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect3->vertexWk_effect3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect3->vertexWk_effect3[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT3, 0.0f);
	effect3->vertexWk_effect3[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT3);
	effect3->vertexWk_effect3[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT3, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT3);






	//effect3->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect3->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect3->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect3->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect3( int no,int cntPattern )
{
	EFFECT3 *effect3 = &effect3Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT3;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT3;
	
	effect3->vertexWk_effect3[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect3->vertexWk_effect3[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect3->vertexWk_effect3[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect3->vertexWk_effect3[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect3( int no )
{
	EFFECT3 *effect3 = &effect3Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	effect3->vertexWk_effect3[0].vtx.x = effect3->pos.x - cosf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[0].vtx.y = effect3->pos.y - sinf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[0].vtx.z = 0.0f;

	effect3->vertexWk_effect3[1].vtx.x = effect3->pos.x + cosf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[1].vtx.y = effect3->pos.y - sinf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[1].vtx.z = 0.0f;

	effect3->vertexWk_effect3[2].vtx.x = effect3->pos.x - cosf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[2].vtx.y = effect3->pos.y + sinf(effect3->BaseAngle - effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[2].vtx.z = 0.0f;

	effect3->vertexWk_effect3[3].vtx.x = effect3->pos.x + cosf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[3].vtx.y = effect3->pos.y + sinf(effect3->BaseAngle + effect3->rot.z) * effect3->Radius;
	effect3->vertexWk_effect3[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetEffect3(D3DXVECTOR3 pos, int i)
{
	EFFECT3 *effect3 = &effect3Wk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < EFFECT3_MAX; i++, effect3++)
	//{
		if (effect3->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect3->use = true;				// �g�p��Ԃ֕ύX����
			effect3->pos = pos;				// ���W���Z�b�g
			effect3->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}




//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EFFECT3 *GetEffect3(int no)
{

	
	return(&effect3Wk[no]);



}


