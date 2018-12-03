//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include"boss2.h"
#include"Ebullet.h"
#include "input.h"
#include "bosseffect.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss2( int no);
void SetTextureBoss2( int no,int cntPattern );
void SetVertexBoss2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS2 = NULL;		// �e�N�X�`���ւ̃|���S��


BOSS2					boss2Wk[BOSS2_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS2 *boss2 = boss2Wk;				// �G�l�~�[�̃|�C���^�[��������


	srand((unsigned)time(NULL));
	int j = 0;


	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS2,				// �t�@�C���̖��O
			&g_pD3DTextureBOSS2);			// �ǂݍ��ރ������̃|�C���^


	}

		// �G�l�~�[�̏���������
		for (int i = 0; i < BOSS2_MAX; i++, boss2++)
		{
			boss2->use = false;										// �g�p
			boss2->effectflag = false;
			boss2->drawflug = false;
			boss2->pos = D3DXVECTOR3(i * 50 + 500.0f, 220.0f, 0.0f);	// ���W�f�[�^��������
			boss2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			boss2->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
			boss2->CountAnim = 0;									// �A�j���J�E���g��������
			boss2->counter = 0;
			boss2->Popcounter = 0;
			boss2->Bcounter = 0;
			boss2->Bcounter_ORG = rand() % (60 * 3);
			boss2->Hitcounter = 0;
			boss2 ->Timecounter = 0;
			boss2->HP = 200;
			boss2->MAXHP = boss2->HP;


			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS2_SIZE_X, TEXTURE_BOSS2_SIZE_Y);
			boss2->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
			boss2->BaseAngle = atan2f(TEXTURE_BOSS2_SIZE_Y, TEXTURE_BOSS2_SIZE_X);	// �G�l�~�[�̊p�x��������

			boss2->Texture = g_pD3DTextureBOSS2;					// �e�N�X�`�����
			MakeVertexBoss2(i);										// ���_���̍쐬
		}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss2(void)
{
	if (g_pD3DTextureBOSS2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBOSS2->Release();
		g_pD3DTextureBOSS2 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss2(void)
{
	BOSS2 *boss2 = GetBoss2(0);				// �G�l�~�[�̃|�C���^�[��������


	if (boss2->Timecounter > 6)
	{
		boss2->Hitcounter = 0;
		boss2->Timecounter = 0;
		//player->Hitcounter = 0;

	}


	if (boss2->Popcounter > 13)
	{
		for (int i = 0; i < BOSS2_MAX; i++)
		{
			if (GetBoss2(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{



					GetBoss2(i)->Bcounter++;
					if (GetBoss2(i)->Bcounter >= GetBoss2(i)->Bcounter_ORG)
					{
						GetBoss2(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetBoss2(i)->pos;
						SetEBullet(pos);


					}
					if (boss2->counter <= 3)
					{
						boss2->pos.y -= 1.0f;
					}
					if (boss2->counter >=3&&boss2->counter<=6 )
					{
						boss2->pos.y += 1.0f;
					}

					if (boss2->counter == 7)
					{

						boss2->counter = 0;

					}


					//�A�j���[�V����
					boss2->CountAnim++;
					if ((boss2->CountAnim % TIME_ANIMATION_BOSS2) == 0)
					{
						// �p�^�[���̐؂�ւ�
						boss2->PatternAnim = (boss2->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS2;

						// �e�N�X�`�����W��ݒ�
						SetTextureBoss2(i, boss2->PatternAnim);

					}

				}

			if (GetBoss2(i)->effectflag == true)
			{
				SetBossEffect(GetBoss2(i)->pos, i);

			}


				// ��ʊO�܂Ői�񂾁H
				if (boss2->pos.y < -TEXTURE_BOSS2_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					boss2->use = false;
					boss2->pos.x = -100.0f;
				}


				SetVertexBoss2(i);	// �ړ���̍��W�Œ��_��ݒ�
			}
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BOSS2 *boss2 = boss2Wk;				// �G�l�~�[�̃|�C���^�[��������

	//if (boss2->Popcounter > 13)
	//{
	//for (int i = 0; i < boss2->Timecounter; i++)
	//{

	//	switch (boss2->Timecounter)
	//	{
	//	case 1:
	//		boss2->drawflug = true;
	//		break;

	//	case 2:
	//		boss2->drawflug = false;
	//		break;

	//	case 3:
	//		boss2->drawflug = true;
	//		break;

	//	case 4:
	//		boss2->drawflug = false;
	//		break;

	//	case 5:
	//		boss2->drawflug = true;
	//		break;

	//	case 6:
	//		boss2->drawflug = false;
	//		break;

	//	default:
	//		break;
	//	}

	//}





		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < BOSS2_MAX; i++, boss2++)
		{
			if (boss2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (boss2->drawflug = false)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, boss2->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS2, boss2->vertexWk_boss2, sizeof(VERTEX_2D));
				//}
			}


		}

	}


//}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss2( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS2 *boss2 = &boss2Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexBoss2( no );

	// rhw�̐ݒ�
	boss2->vertexWk_boss2[0].rhw =
	boss2->vertexWk_boss2[1].rhw =
	boss2->vertexWk_boss2[2].rhw =
	boss2->vertexWk_boss2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss2->vertexWk_boss2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss2->vertexWk_boss2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss2->vertexWk_boss2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss2->vertexWk_boss2[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS2, 0.0f);
	boss2->vertexWk_boss2[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS2);
	boss2->vertexWk_boss2[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS2);


	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss2( int no,int cntPattern )
{
	BOSS2 *boss2 = &boss2Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS2;
	
	boss2->vertexWk_boss2[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss2->vertexWk_boss2[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss2->vertexWk_boss2[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss2->vertexWk_boss2[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss2( int no )
{
	BOSS2 *boss2 = &boss2Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	boss2->vertexWk_boss2[0].vtx.x = boss2->pos.x - cosf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[0].vtx.y = boss2->pos.y - sinf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[0].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[1].vtx.x = boss2->pos.x + cosf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[1].vtx.y = boss2->pos.y - sinf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[1].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[2].vtx.x = boss2->pos.x - cosf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[2].vtx.y = boss2->pos.y + sinf(boss2->BaseAngle - boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[2].vtx.z = 0.0f;
	
	boss2->vertexWk_boss2[3].vtx.x = boss2->pos.x + cosf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[3].vtx.y = boss2->pos.y + sinf(boss2->BaseAngle + boss2->rot.z) * boss2->Radius;
	boss2->vertexWk_boss2[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSS2 *GetBoss2(int no)
{

	
	return(&boss2Wk[no]);



}


