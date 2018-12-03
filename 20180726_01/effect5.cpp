//=============================================================================
//
// �G���� [effect5.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect5.h"
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
HRESULT MakeVertexEffect5( int no);
void SetTextureEffect5( int no,int cntPattern );
void SetVertexEffect5( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect5 = NULL;		// �e�N�X�`���ւ̃|���S��


EFFECT5					effect5Wk[EFFECT5_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect5(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = effect5Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT5,				// �t�@�C���̖��O
			&g_pD3DTextureEffect5);			// �ǂݍ��ރ������̃|�C���^


	}



	 //�G�l�~�[�̏���������
	for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
	{
		effect5->use = false;										// �g�p
		effect5->pos = D3DXVECTOR3(i*50+effect5->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		effect5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		effect5->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect5->CountAnim = 0;									// �A�j���J�E���g��������
		effect5->effectcounter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT5_SIZE_X, TEXTURE_EFFECT5_SIZE_Y);
		effect5->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect5->BaseAngle = atan2f(TEXTURE_EFFECT5_SIZE_Y, TEXTURE_EFFECT5_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect5->Texture = g_pD3DTextureEffect5;					// �e�N�X�`�����
		MakeVertexEffect5(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect5(void)
{
	if (g_pD3DTextureEffect5 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect5->Release();
		g_pD3DTextureEffect5 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect5(void)
{
	EFFECT5 *effect5 = effect5Wk;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect5->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�A�j���[�V����
				effect5->CountAnim++;
				if ((effect5->CountAnim % TIME_ANIMATION_EFFECT5) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT5 -1> effect5->PatternAnim)
					{
						// �p�^�[���̐؂�ւ�
						effect5->PatternAnim = (effect5->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT5;


					}
					else
					{
						effect5->use = false;
						effect5->PatternAnim = 0;
						GetEnemy4(effect5->i)->effectflag4 = false;
					}

					
					// �e�N�X�`�����W��ݒ�
					SetTextureEffect5(0, effect5->PatternAnim);


					SetVertexEffect5(0);	// �ړ���̍��W�Œ��_��ݒ�


				}

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = effect5Wk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
		//{
			if (effect5->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (effect5->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effect5->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT5, effect5->vertexWk_effect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect5( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT5 *effect5 = &effect5Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEffect5( no );

	// rhw�̐ݒ�
	effect5->vertexWk_effect[0].rhw =
	effect5->vertexWk_effect[1].rhw =
	effect5->vertexWk_effect[2].rhw =
	effect5->vertexWk_effect[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect5->vertexWk_effect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect5->vertexWk_effect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect5->vertexWk_effect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect5->vertexWk_effect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT5, 0.0f);
	effect5->vertexWk_effect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT5);
	effect5->vertexWk_effect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT5, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT5);






	//effect5->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect5->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect5->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect5->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect5( int no,int cntPattern )
{
	EFFECT5 *effect5 = &effect5Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT5;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT5;
	
	effect5->vertexWk_effect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect5->vertexWk_effect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect5->vertexWk_effect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect5->vertexWk_effect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect5( int no )
{
	EFFECT5 *effect5 = &effect5Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	effect5->vertexWk_effect[0].vtx.x = effect5->pos.x - cosf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[0].vtx.y = effect5->pos.y - sinf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[0].vtx.z = 0.0f;

	effect5->vertexWk_effect[1].vtx.x = effect5->pos.x + cosf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[1].vtx.y = effect5->pos.y - sinf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[1].vtx.z = 0.0f;

	effect5->vertexWk_effect[2].vtx.x = effect5->pos.x - cosf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[2].vtx.y = effect5->pos.y + sinf(effect5->BaseAngle - effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[2].vtx.z = 0.0f;

	effect5->vertexWk_effect[3].vtx.x = effect5->pos.x + cosf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[3].vtx.y = effect5->pos.y + sinf(effect5->BaseAngle + effect5->rot.z) * effect5->Radius;
	effect5->vertexWk_effect[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetEffect5(D3DXVECTOR3 pos, int i)
{
	EFFECT5 *effect5 = &effect5Wk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < EFFECT5_MAX; i++, effect5++)
	//{
		if (effect5->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect5->use = true;				// �g�p��Ԃ֕ύX����
			effect5->pos = pos;				// ���W���Z�b�g
			effect5->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}




//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EFFECT5 *GetEffect5(int no)
{

	
	return(&effect5Wk[no]);



}


