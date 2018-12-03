//=============================================================================
//
// �G���� [enemy5.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy5.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"effect5.h"
#include "boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy5( int no);
void SetTextureEnemy5( int no,int cntPattern );
void SetVertexEnemy5( int no );
void SetEnemy5(D3DXVECTOR3 pos);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy5 = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY5					enemy5Wk[ENEMY5_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy5(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = enemy5Wk;				// �G�l�~�[�̃|�C���^�[��������
	int j = 0;
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY5,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy5);			// �ǂݍ��ރ������̃|�C���^


	}

	j = rand() % (10);


	//enemy5->pos = D3DXVECTOR3(i * 50 + enemy5->InitY, i*50.0f, 0.0f);		// ���W�f�[�^��������


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
	{
		enemy5->use = false;										// �g�p
		//enemy5->InitY = 700.0f;
		enemy5->pos = D3DXVECTOR3(900+10.0f,i*50.0f, 0.0f);		// ���W�f�[�^��������
		enemy5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy5->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy5->CountAnim = 0;									// �A�j���J�E���g��������
		enemy5->Bcounter = 0;										//�G�l�~�[�̏o�����Ԃ��Ǘ�
		enemy5->counter = 0;
		enemy5->Mcounter = 0;
		enemy5->Bcounter_ORG=rand()%(60*3);
		enemy5->deadflag = false;
		enemy5->effectflag = false;
		enemy5->BBflag = false;
		enemy5->comeback = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY5_SIZE_X, TEXTURE_ENEMY5_SIZE_Y);
		enemy5->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy5->BaseAngle = atan2f(TEXTURE_ENEMY5_SIZE_Y, TEXTURE_ENEMY5_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy5->Texture = g_pD3DTextureEnemy5;					// �e�N�X�`�����
		MakeVertexEnemy5(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy5(void)
{
	if (g_pD3DTextureEnemy5 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy5->Release();
		g_pD3DTextureEnemy5 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy5(void)
{

	ENEMY5 *enemy5 = GetEnemy5(0);				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̃|�C���^�[��������
	EBULLET *Ebullet = GetEBullet(0);	// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);
	//int i = 0;
	

	if (enemy5->counter == 32)
	{
		for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
		{
			GetEnemy5(i)->use = true;
		}
	}

		////�G�l�~�[MAX���\������
		for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
		{

		//	GetEnemy5(i)->use = true;

			if (GetEnemy5(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�G�l�~�[�̒e����
				//GetEnemy5(i)->Bcounter++;
				//if (GetEnemy5(i)->Bcounter >= GetEnemy5(i)->Bcounter_ORG)
				//{
				//	GetEnemy5(i)->Bcounter = 0;

				//	D3DXVECTOR3 pos = GetEnemy5(i)->pos;
				//	SetEBullet(pos);

				//}

				if (GetEnemy5(i)->Mcounter < 14)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 15&& GetEnemy5(i)->Mcounter<=19)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y += 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 19 && GetEnemy5(i)->Mcounter <= 23)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y -= 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 23 && GetEnemy5(i)->Mcounter <= 27)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y += 1.0f;
				}

				if (GetEnemy5(i)->Mcounter > 27 /*&& GetEnemy5(i)->Mcounter <= 23*/)
				{
					GetEnemy5(i)->pos.x -= 1.0f;
					GetEnemy5(i)->pos.y -= 1.0f;
				}

				//�A�j���[�V����
				enemy5->CountAnim++;
				if ((enemy5->CountAnim % TIME_ANIMATION_ENEMY5) == 0)
				{
					// �p�^�[���̐؂�ւ�
					enemy5->PatternAnim = (enemy5->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY5;
					// �e�N�X�`�����W��ݒ�
					SetTextureEnemy5(i, enemy5->PatternAnim);
				}

				// ��ʊO�܂Ői�񂾁H
				if (GetEnemy5(i)->pos.x < 0 - TEXTURE_ENEMY5_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					GetEnemy5(i)->use = false;
					//GetEnemy5(i)->pos.x = 800.0f;
				}

				GetEnemy5(i)->enemy5pos_x = GetEnemy5(i)->pos.x;
				GetEnemy5(i)->enemy5pos_y = GetEnemy5(i)->pos.y;
				SetVertexEnemy5(i);	// �ړ���̍��W�Œ��_��ݒ�
			}


			if (GetEnemy5(i)->effectflag == true)
			{
				SetEffect5(GetEnemy5(i)->pos, i);
				GetEnemy5(i)->effectflag = false;
			}
			if (GetEnemy5(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy5(i)->BBflag = false;
			}

			//if (GetEnemy5(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy5(i)->pos;

			//	SetEnemy5(pos);
			//	GetEnemy5(0)->use = true;
			//	GetEnemy5(i)->comeback = false;
			//	GetEnemy5(0)->counter = 14;


			//}


			if (GetEnemy5(i)->use == false)
			{
				GetEnemy5(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy5(i)->use = false;

			}




		}

}

//}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = GetEnemy5(0);				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

			for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
			{

				if (GetEnemy5(i)->use == true)			// �g�p���Ă����ԂȂ�`�悷��
				{

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, GetEnemy5(i)->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY5, GetEnemy5(i)->vertexWk_enemy5, sizeof(VERTEX_2D));
			}
		}

	

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy5( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY5 *enemy5 = &enemy5Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy5( no );

	// rhw�̐ݒ�
	enemy5->vertexWk_enemy5[0].rhw =
	enemy5->vertexWk_enemy5[1].rhw =
	enemy5->vertexWk_enemy5[2].rhw =
	enemy5->vertexWk_enemy5[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy5->vertexWk_enemy5[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy5->vertexWk_enemy5[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy5->vertexWk_enemy5[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy5->vertexWk_enemy5[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY5, 0.0f);
	enemy5->vertexWk_enemy5[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY5);
	enemy5->vertexWk_enemy5[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY5, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY5);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy5( int no,int cntPattern )
{
	ENEMY5 *enemy5 = &enemy5Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY5;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY5;
	
	enemy5->vertexWk_enemy5[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy5->vertexWk_enemy5[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy5->vertexWk_enemy5[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy5->vertexWk_enemy5[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy5( int no )
{
	ENEMY5 *enemy5 = &enemy5Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy5->vertexWk_enemy5[0].vtx.x = enemy5->pos.x - cosf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[0].vtx.y = enemy5->pos.y - sinf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[0].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[1].vtx.x = enemy5->pos.x + cosf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[1].vtx.y = enemy5->pos.y - sinf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[1].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[2].vtx.x = enemy5->pos.x - cosf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[2].vtx.y = enemy5->pos.y + sinf(enemy5->BaseAngle - enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[2].vtx.z = 0.0f;

	enemy5->vertexWk_enemy5[3].vtx.x = enemy5->pos.x + cosf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[3].vtx.y = enemy5->pos.y + sinf(enemy5->BaseAngle + enemy5->rot.z) * enemy5->Radius;
	enemy5->vertexWk_enemy5[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemy5(D3DXVECTOR3 pos)
{
	ENEMY5 *enemy5 = &enemy5Wk[0];			// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMY5_MAX; i++, enemy5++)
	{
		if (enemy5->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			enemy5->use = true;			// �g�p��Ԃ֕ύX����
			enemy5->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// ���W���Z�b�g

			//for (int j = 0; j < ENEMY54_MAX; j++)
			//{
			//	if (GetEnemy54(j)->use == false) continue;
			//	{
			//		GetEnemy54(i)->nextflag = false;
			//	}
			//}


			//enemy5->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// ���ˉ��Đ�
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY5 *GetEnemy5(int no)
{

	
	return(&enemy5Wk[no]);



}


