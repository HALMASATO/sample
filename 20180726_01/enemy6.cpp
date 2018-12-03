//=============================================================================
//
// �G���� [enemy6.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy6.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet2.h"
#include "input.h"
#include"effect.h"
#include "boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy6( int no);
void SetTextureEnemy6( int no,int cntPattern );
void SetVertexEnemy6( int no );
void SetEnemy6(D3DXVECTOR3 pos);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy6 = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY6					enemy6Wk[ENEMY6_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy6(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = enemy6Wk;				// �G�l�~�[�̃|�C���^�[��������
	int j = 0;
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY6,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy6);			// �ǂݍ��ރ������̃|�C���^


	}

	j = rand() % (10);


	//enemy6->pos = D3DXVECTOR3(i * 50 + enemy6->InitY, i*50.0f, 0.0f);		// ���W�f�[�^��������


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
	{
		enemy6->use = false;										// �g�p
		//enemy6->InitY = 700.0f;
		enemy6->pos = D3DXVECTOR3(900+10.0f,50+i*160.0f, 0.0f);		// ���W�f�[�^��������
		enemy6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy6->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy6->CountAnim = 0;									// �A�j���J�E���g��������
		enemy6->Bcounter = 0;										//�G�l�~�[�̏o�����Ԃ��Ǘ�
		enemy6->counter = 0;
		enemy6->Bcounter_ORG=rand()%(60*4);
		enemy6->deadflag = false;
		enemy6->effectflag = false;
		enemy6->BBflag = false;
		enemy6->comeback = false;
		//enemy6->Bcounter = 0;
		//enemy6->Bcounter_ORG = rand() % (60 * 3);


		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY6_SIZE_X, TEXTURE_ENEMY6_SIZE_Y);
		enemy6->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy6->BaseAngle = atan2f(TEXTURE_ENEMY6_SIZE_Y, TEXTURE_ENEMY6_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy6->Texture = g_pD3DTextureEnemy6;					// �e�N�X�`�����
		MakeVertexEnemy6(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy6(void)
{
	if (g_pD3DTextureEnemy6 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy6->Release();
		g_pD3DTextureEnemy6 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy6(void)
{

	ENEMY6 *enemy6 = GetEnemy6(0);				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̃|�C���^�[��������
	EBULLET2 *Ebullet2 = GetEBullet2(0);	// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);


	if (enemy6->counter == 42)
	{
		//�G�l�~�[MAX���\������
		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{
			GetEnemy6(i)->use = true;
		}
	}


		//�G�l�~�[MAX���\������
		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{

			//GetEnemy6(i)->use = true;

			if (GetEnemy6(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				if (GetEnemy6(i)->counter > 50)
				{
					//�G�l�~�[�̒e����
					GetEnemy6(i)->Bcounter++;
					if (GetEnemy6(i)->Bcounter >= GetEnemy6(i)->Bcounter_ORG)
					{
						GetEnemy6(i)->Bcounter = 0;

						D3DXVECTOR3 pos = GetEnemy6(i)->pos;
						SetEBullet2(pos);

					}
				}


				if (GetEnemy6(i)->counter > 48 && GetEnemy6(i)->counter < 58)
				{
					GetEnemy6(i)->pos.x -= 1.0f;
				}




				//�A�j���[�V����
				enemy6->CountAnim++;
				if ((enemy6->CountAnim % TIME_ANIMATION_ENEMY6) == 0)
				{
					// �p�^�[���̐؂�ւ�
					enemy6->PatternAnim = (enemy6->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY6;
					// �e�N�X�`�����W��ݒ�
					SetTextureEnemy6(i, enemy6->PatternAnim);
				}

				// ��ʊO�܂Ői�񂾁H
				if (GetEnemy6(i)->pos.x < 0 - TEXTURE_ENEMY6_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					GetEnemy6(i)->use = false;
					//GetEnemy6(i)->pos.x = 800.0f;
				}

				//GetEnemy6(i)->enemy6pos_x = GetEnemy6(i)->pos.x;
				//GetEnemy6(i)->enemy6pos_y = GetEnemy6(i)->pos.y;


				SetVertexEnemy6(i);	// �ړ���̍��W�Œ��_��ݒ�

			}

			if (GetEnemy6(i)->effectflag == true)
			{
				SetEffect(GetEnemy6(i)->pos, i);
			}

			if (GetEnemy6(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy6(i)->BBflag = false;
			}

			//if (GetEnemy6(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy6(i)->pos;

			//	SetEnemy6(pos);
			//	GetEnemy6(0)->use = true;
			//	GetEnemy6(i)->comeback = false;
			//	GetEnemy6(0)->counter = 14;


			//}


			if (GetEnemy6(i)->use == false)
			{
				GetEnemy6(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy6(i)->use = false;

			}




		}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = GetEnemy6(0);				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
		{

			if (GetEnemy6(i)->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, GetEnemy6(i)->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY6, GetEnemy6(i)->vertexWk_enemy6, sizeof(VERTEX_2D));
			}



		}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy6( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY6 *enemy6 = &enemy6Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy6( no );

	// rhw�̐ݒ�
	enemy6->vertexWk_enemy6[0].rhw =
	enemy6->vertexWk_enemy6[1].rhw =
	enemy6->vertexWk_enemy6[2].rhw =
	enemy6->vertexWk_enemy6[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy6->vertexWk_enemy6[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy6->vertexWk_enemy6[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy6->vertexWk_enemy6[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy6->vertexWk_enemy6[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY6, 0.0f);
	enemy6->vertexWk_enemy6[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY6);
	enemy6->vertexWk_enemy6[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY6, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY6);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy6( int no,int cntPattern )
{
	ENEMY6 *enemy6 = &enemy6Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY6;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY6;
	
	enemy6->vertexWk_enemy6[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy6->vertexWk_enemy6[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy6->vertexWk_enemy6[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy6->vertexWk_enemy6[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy6( int no )
{
	ENEMY6 *enemy6 = &enemy6Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy6->vertexWk_enemy6[0].vtx.x = enemy6->pos.x - cosf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[0].vtx.y = enemy6->pos.y - sinf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[0].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[1].vtx.x = enemy6->pos.x + cosf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[1].vtx.y = enemy6->pos.y - sinf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[1].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[2].vtx.x = enemy6->pos.x - cosf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[2].vtx.y = enemy6->pos.y + sinf(enemy6->BaseAngle - enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[2].vtx.z = 0.0f;

	enemy6->vertexWk_enemy6[3].vtx.x = enemy6->pos.x + cosf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[3].vtx.y = enemy6->pos.y + sinf(enemy6->BaseAngle + enemy6->rot.z) * enemy6->Radius;
	enemy6->vertexWk_enemy6[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemy6(D3DXVECTOR3 pos)
{
	ENEMY6 *enemy6 = &enemy6Wk[0];			// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMY6_MAX; i++, enemy6++)
	{
		if (enemy6->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			enemy6->use = true;			// �g�p��Ԃ֕ύX����
			enemy6->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// ���W���Z�b�g

			//for (int j = 0; j < ENEMY64_MAX; j++)
			//{
			//	if (GetEnemy64(j)->use == false) continue;
			//	{
			//		GetEnemy64(i)->nextflag = false;
			//	}
			//}


			//enemy6->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// ���ˉ��Đ�
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY6 *GetEnemy6(int no)
{

	
	return(&enemy6Wk[no]);



}


