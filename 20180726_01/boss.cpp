//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include"boss.h"
#include"Ebullet.h"
#include "input.h"
#include "bosseffect.h"
#include "btgage.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss( int no);
void SetTextureBoss( int no,int cntPattern );
void SetVertexBoss( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS = NULL;		// �e�N�X�`���ւ̃|���S��


BOSS					bossWk[BOSS_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = bossWk;				// �G�l�~�[�̃|�C���^�[��������


	srand((unsigned)time(NULL));
	int j = 0;


	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS,				// �t�@�C���̖��O
			&g_pD3DTextureBOSS);			// �ǂݍ��ރ������̃|�C���^


	}

		// �G�l�~�[�̏���������
		for (int i = 0; i < BOSS_MAX; i++, boss++)
		{
			boss->use = false;										// �g�p
			boss->effectflag = false;
			boss->drawflug = false;
			boss->endflug = false;
			boss->pos = D3DXVECTOR3(i * 50 + 700.0f, 220.0f, 0.0f);	// ���W�f�[�^��������
			boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			boss->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
			boss->CountAnim = 0;									// �A�j���J�E���g��������
			boss->counter = 0;
			boss->Popcounter = 0;
			boss->Bcounter = 0;
			boss->Bcounter_ORG = rand() % (60 * 3);
			boss->Hitcounter = 0;
			boss ->Timecounter = 0;
			boss->HP = 100;
			boss->MAXHP = boss->HP;


			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y);
			boss->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
			boss->BaseAngle = atan2f(TEXTURE_BOSS_SIZE_Y, TEXTURE_BOSS_SIZE_X);	// �G�l�~�[�̊p�x��������

			boss->Texture = g_pD3DTextureBOSS;					// �e�N�X�`�����
			MakeVertexBoss(i);										// ���_���̍쐬
		}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	if (g_pD3DTextureBOSS != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBOSS->Release();
		g_pD3DTextureBOSS = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	BOSS *boss = GetBoss(0);				// �G�l�~�[�̃|�C���^�[��������

	if (GetBoss(0)->Popcounter > 13)
	{
		GetBoss(0)->use = true;

	}


	if (boss->Timecounter > 6)
	{
		boss->Hitcounter = 0;
		boss->Timecounter = 0;

	}


	if (boss->Popcounter > 13)
	{


		for (int i = 0; i < BOSS_MAX; i++)
		{
			if (GetBoss(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{



					GetBoss(i)->Bcounter++;
					if (GetBoss(i)->Bcounter >= GetBoss(i)->Bcounter_ORG)
					{
						GetBoss(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetBoss(i)->pos;
						SetEBullet(pos);


					}
					if (boss->counter <= 3)
					{
						boss->pos.y -= 1.0f;
					}
					if (boss->counter >=3&&boss->counter<=6 )
					{
						boss->pos.y += 1.0f;
					}

					if (boss->counter == 7)
					{

						boss->counter = 0;

					}


					//�A�j���[�V����
					boss->CountAnim++;
					if ((boss->CountAnim % TIME_ANIMATION_BOSS) == 0)
					{
						// �p�^�[���̐؂�ւ�
						boss->PatternAnim = (boss->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS;

						// �e�N�X�`�����W��ݒ�
						SetTextureBoss(i, boss->PatternAnim);

					}

			}

			if (GetBoss(i)->effectflag == true)
			{
				SetBossEffect(GetBoss(i)->pos, i);

			}


				// ��ʊO�܂Ői�񂾁H
				if (boss->pos.y < -TEXTURE_BOSS_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					boss->use = false;
					boss->pos.x = -100.0f;
				}

				if (boss->HP <= 0)
				{
					boss->endflug = true;
				}

				SetVertexBoss(i);	// �ړ���̍��W�Œ��_��ݒ�
			}
		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BOSS *boss = bossWk;				// �G�l�~�[�̃|�C���^�[��������

	//if (boss->Popcounter > 13)
	//{
	//for (int i = 0; i < boss->Timecounter; i++)
	//{

	//	switch (boss->Timecounter)
	//	{
	//	case 1:
	//		boss->drawflug = true;
	//		break;

	//	case 2:
	//		boss->drawflug = false;
	//		break;

	//	case 3:
	//		boss->drawflug = true;
	//		break;

	//	case 4:
	//		boss->drawflug = false;
	//		break;

	//	case 5:
	//		boss->drawflug = true;
	//		break;

	//	case 6:
	//		boss->drawflug = false;
	//		break;

	//	default:
	//		break;
	//	}

	//}





		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < BOSS_MAX; i++, boss++)
		{
			if (boss->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				//if (boss->drawflug = false)
				//{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, boss->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS, boss->vertexWk_boss, sizeof(VERTEX_2D));
				//}
			}


		}

	}


//}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexBoss( no );

	// rhw�̐ݒ�
	boss->vertexWk_boss[0].rhw =
	boss->vertexWk_boss[1].rhw =
	boss->vertexWk_boss[2].rhw =
	boss->vertexWk_boss[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss->vertexWk_boss[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk_boss[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss->vertexWk_boss[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk_boss[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 0.0f);
	boss->vertexWk_boss[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);
	boss->vertexWk_boss[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS);


	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss( int no,int cntPattern )
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS;
	
	boss->vertexWk_boss[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss->vertexWk_boss[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss->vertexWk_boss[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss->vertexWk_boss[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss( int no )
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	boss->vertexWk_boss[0].vtx.x = boss->pos.x - cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[0].vtx.y = boss->pos.y - sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[0].vtx.z = 0.0f;
	
	boss->vertexWk_boss[1].vtx.x = boss->pos.x + cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[1].vtx.y = boss->pos.y - sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[1].vtx.z = 0.0f;
	
	boss->vertexWk_boss[2].vtx.x = boss->pos.x - cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[2].vtx.y = boss->pos.y + sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[2].vtx.z = 0.0f;
	
	boss->vertexWk_boss[3].vtx.x = boss->pos.x + cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[3].vtx.y = boss->pos.y + sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk_boss[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSS *GetBoss(int no)
{

	
	return(&bossWk[no]);



}


