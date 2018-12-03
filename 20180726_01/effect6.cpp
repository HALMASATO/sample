//=============================================================================
//
// �G���� [effect6.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect6.h"
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
HRESULT MakeVertexEffect6( int no);
void SetTextureEffect6( int no,int cntPattern );
void SetVertexEffect6( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect6 = NULL;		// �e�N�X�`���ւ̃|���S��


EFFECT6					effect6Wk[EFFECT6_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect6(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = effect6Wk;				// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT6,				// �t�@�C���̖��O
			&g_pD3DTextureEffect6);			// �ǂݍ��ރ������̃|�C���^


	}
	 //�G�l�~�[�̏���������
	for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
	{
		effect6->use = false;										// �g�p
		effect6->pos = D3DXVECTOR3(i*50+effect6->InitY,50.0f, 0.0f);		// ���W�f�[�^��������
		effect6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		effect6->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect6->CountAnim = 0;									// �A�j���J�E���g��������
		effect6->effectcounter = 0;								//�G�t�F�N�g�J�E���^�[
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT6_SIZE_X, TEXTURE_EFFECT6_SIZE_Y);
		effect6->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect6->BaseAngle = atan2f(TEXTURE_EFFECT6_SIZE_Y, TEXTURE_EFFECT6_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect6->Texture = g_pD3DTextureEffect6;					// �e�N�X�`�����
		MakeVertexEffect6(i);										// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect6(void)
{
	if (g_pD3DTextureEffect6 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect6->Release();
		g_pD3DTextureEffect6 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect6(void)
{
	EFFECT6 *effect6 = effect6Wk;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

			if (effect6->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�A�j���[�V����
				effect6->CountAnim++;
				if ((effect6->CountAnim % TIME_ANIMATION_EFFECT6) == 0)
				{
					if (ANIM_PATTERN_NUM_EFFECT6 -1> effect6->PatternAnim)
					{
						// �p�^�[���̐؂�ւ�
						effect6->PatternAnim = (effect6->PatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT6;


					}
					else
					{
						effect6->use = false;
						effect6->PatternAnim = 0;
						GetEnemy4(effect6->i)->effectflag4 = false;
					}

					
					// �e�N�X�`�����W��ݒ�
					SetTextureEffect6(0, effect6->PatternAnim);


					SetVertexEffect6(0);	// �ړ���̍��W�Œ��_��ݒ�


				}

			}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = effect6Wk;				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	
		//for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
		//{
			if (effect6->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (effect6->counter > 0)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, effect6->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT6, effect6->vertexWk_effect, sizeof(VERTEX_2D));
				//}
			}

		//}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect6( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT6 *effect6 = &effect6Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEffect6( no );

	// rhw�̐ݒ�
	effect6->vertexWk_effect[0].rhw =
	effect6->vertexWk_effect[1].rhw =
	effect6->vertexWk_effect[2].rhw =
	effect6->vertexWk_effect[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect6->vertexWk_effect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect6->vertexWk_effect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect6->vertexWk_effect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect6->vertexWk_effect[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT6, 0.0f);
	effect6->vertexWk_effect[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT6);
	effect6->vertexWk_effect[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EFFECT6, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT6);






	//effect6->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//effect6->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//effect6->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//effect6->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect6( int no,int cntPattern )
{
	EFFECT6 *effect6 = &effect6Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT6;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT6;
	
	effect6->vertexWk_effect[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect6->vertexWk_effect[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect6->vertexWk_effect[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect6->vertexWk_effect[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect6( int no )
{
	EFFECT6 *effect6 = &effect6Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	effect6->vertexWk_effect[0].vtx.x = effect6->pos.x - cosf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[0].vtx.y = effect6->pos.y - sinf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[0].vtx.z = 0.0f;

	effect6->vertexWk_effect[1].vtx.x = effect6->pos.x + cosf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[1].vtx.y = effect6->pos.y - sinf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[1].vtx.z = 0.0f;

	effect6->vertexWk_effect[2].vtx.x = effect6->pos.x - cosf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[2].vtx.y = effect6->pos.y + sinf(effect6->BaseAngle - effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[2].vtx.z = 0.0f;

	effect6->vertexWk_effect[3].vtx.x = effect6->pos.x + cosf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[3].vtx.y = effect6->pos.y + sinf(effect6->BaseAngle + effect6->rot.z) * effect6->Radius;
	effect6->vertexWk_effect[3].vtx.z = 0.0f;
}
//=============================================================================
// �G�t�F�N�g�̔����ݒ�
//=============================================================================
void SetEffect6(D3DXVECTOR3 pos, int i)
{
	EFFECT6 *effect6 = &effect6Wk[0];			// �o���b�g�̃|�C���^�[��������


		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	//for (int i = 0; i < EFFECT6_MAX; i++, effect6++)
	//{
		if (effect6->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect6->use = true;				// �g�p��Ԃ֕ύX����
			effect6->pos = pos;				// ���W���Z�b�g
			effect6->i = i;


			// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������


		}


	//}


}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EFFECT6 *GetEffect6(int no)
{

	
	return(&effect6Wk[no]);



}