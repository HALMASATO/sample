//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
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
HRESULT MakeVertexEnemy( int no);
void SetTextureEnemy( int no,int cntPattern );
void SetVertexEnemy( int no );
void SetEnemy(D3DXVECTOR3 pos);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// �G�l�~�[�̃|�C���^�[��������
	int j = 0;
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy);			// �ǂݍ��ރ������̃|�C���^


	}

	j = rand() % (10);


	//enemy->pos = D3DXVECTOR3(i * 50 + enemy->InitY, i*50.0f, 0.0f);		// ���W�f�[�^��������


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// �g�p
		//enemy->InitY = 700.0f;
		enemy->pos = D3DXVECTOR3(900+10.0f,i*100.0f, 0.0f);		// ���W�f�[�^��������
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy->CountAnim = 0;									// �A�j���J�E���g��������
		enemy->Bcounter = 0;										//�G�l�~�[�̏o�����Ԃ��Ǘ�
		enemy->counter = 0;
		enemy->Bcounter_ORG=rand()%(60*3);
		enemy->deadflag = false;
		enemy->effectflag = false;
		enemy->BBflag = false;
		enemy->comeback = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy->Texture = g_pD3DTextureEnemy;					// �e�N�X�`�����
		MakeVertexEnemy(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{

	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̃|�C���^�[��������
	EBULLET *Ebullet = GetEBullet(0);	// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);
	BOSS*boss = GetBoss(0);
	//int i = 0;

	int j = rand() % (10);
	
			//if (GetEnemy(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			//{

		//�G�l�~�[MAX���\������
		for (int i=0; i < ENEMY_MAX; i++, enemy++)
		{

			if (GetEnemy(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{

				//�G�l�~�[�̒e����
				//GetEnemy(i)->Bcounter++;
				//if (GetEnemy(i)->Bcounter >= GetEnemy(i)->Bcounter_ORG)
				//{
				//	GetEnemy(i)->Bcounter = 0;

				//	D3DXVECTOR3 pos = GetEnemy(i)->pos;
				//	SetEBullet(pos);

				//}

				GetEnemy(i)->pos.x -= 1.0f;


				 //�A�j���[�V����
				enemy->CountAnim++;
				if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
				{
					// �p�^�[���̐؂�ւ�
					enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;
					// �e�N�X�`�����W��ݒ�
					SetTextureEnemy(i, enemy->PatternAnim);
				}

				// ��ʊO�܂Ői�񂾁H
				if (GetEnemy(i)->pos.x < 0-TEXTURE_ENEMY_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					GetEnemy(i)->use = false;
					//GetEnemy(i)->pos.x = 800.0f;
				}

				GetEnemy(i)->enemypos_x = GetEnemy(i)->pos.x;
				GetEnemy(i)->enemypos_y = GetEnemy(i)->pos.y;


				SetVertexEnemy(i);	// �ړ���̍��W�Œ��_��ݒ�

			}

			if (GetEnemy(i)->effectflag == true)
			{
				SetEffect(GetEnemy(i)->pos, i);
			}

			if (GetEnemy(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy(i)->BBflag = false;
			}

			//if (GetEnemy(i)->comeback == true)
			//{
			//	D3DXVECTOR3 pos = GetEnemy(i)->pos;

			//	SetEnemy(pos);
			//	GetEnemy(0)->use = true;
			//	GetEnemy(i)->comeback = false;
			//	GetEnemy(0)->counter = 14;


			//}


			if (GetEnemy(i)->use == false)
			{
				GetEnemy(i)->pos.x = 900.0f;

			}

			if (boss->use == true)
			{

				GetEnemy(i)->use = false;

			}




		}


}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

			for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			{

				if (GetEnemy(i)->use == true)			// �g�p���Ă����ԂȂ�`�悷��
				{

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, GetEnemy(i)->Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, GetEnemy(i)->vertexWk_enemy, sizeof(VERTEX_2D));
				}


			}
		

	

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy( no );

	// rhw�̐ݒ�
	enemy->vertexWk_enemy[0].rhw =
	enemy->vertexWk_enemy[1].rhw =
	enemy->vertexWk_enemy[2].rhw =
	enemy->vertexWk_enemy[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vertexWk_enemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk_enemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vertexWk_enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk_enemy[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk_enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk_enemy[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy( int no,int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk_enemy[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk_enemy[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk_enemy[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk_enemy[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy->vertexWk_enemy[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[0].vtx.z = 0.0f;

	enemy->vertexWk_enemy[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[1].vtx.z = 0.0f;

	enemy->vertexWk_enemy[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[2].vtx.z = 0.0f;

	enemy->vertexWk_enemy[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk_enemy[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	ENEMY *enemy = &enemyWk[0];			// �o���b�g�̃|�C���^�[��������
	ENEMY4*enemy4 = GetEnemy4(0);

		// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			enemy->use = true;			// �g�p��Ԃ֕ύX����
			enemy->pos =  D3DXVECTOR3(900 + 10.0f, i*100.0f, 0.0f);				// ���W���Z�b�g

			//for (int j = 0; j < ENEMY4_MAX; j++)
			//{
			//	if (GetEnemy4(j)->use == false) continue;
			//	{
			//		GetEnemy4(i)->nextflag = false;
			//	}
			//}


			//enemy->pos.x -= (TEXTURE__SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

			// ���ˉ��Đ�
			//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{

	
	return(&enemyWk[no]);



}


