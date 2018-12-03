//=============================================================================
//
// �G���� [enemy3.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy3.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"boss.h"
#include"effect3.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy3( int no);
void SetTextureEnemy3( int no,int cntPattern );
void SetVertexEnemy3( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy3 = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY3					enemy3Wk[ENEMY3_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy3(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = enemy3Wk;				// �G�l�~�[�̃|�C���^�[��������
	int j = 0;
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY3,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy3);			// �ǂݍ��ރ������̃|�C���^


	}

	j = rand() % (9);


	//enemy3->pos = D3DXVECTOR3(i * 50 + enemy3->InitY, i*50.0f, 0.0f);		// ���W�f�[�^��������


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
	{
		enemy3->use = false;										// �g�p
		enemy3->pos = D3DXVECTOR3(i*80+245.0f,500.0f, 0.0f);		// ���W�f�[�^��������
		enemy3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy3->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy3->CountAnim = 0;									// �A�j���J�E���g��������
		enemy3->counter = 0;										//�G�l�~�[�̏o�����Ԃ��Ǘ�
		enemy3->deadflag = false;
		enemy3->effectflag3 = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY3_SIZE_X, TEXTURE_ENEMY3_SIZE_Y);
		enemy3->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy3->BaseAngle = atan2f(TEXTURE_ENEMY3_SIZE_Y, TEXTURE_ENEMY3_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy3->Texture = g_pD3DTextureEnemy3;					// �e�N�X�`�����
		MakeVertexEnemy3(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy3(void)
{
	if (g_pD3DTextureEnemy3 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy3->Release();
		g_pD3DTextureEnemy3 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy3(void)
{


	ENEMY3 *enemy3 = GetEnemy3(0);				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̃|�C���^�[��������
	EBULLET *Ebullet = GetEBullet(0);	// �o���b�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);
	int i = 0;


	if (GetEnemy3(i)->counter == 16)
	{
		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{

			GetEnemy3(i)->use = true;


		}
	}

		//�G�l�~�[MAX���\������
		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{


			if (GetEnemy3(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				//�A�j���[�V����
				enemy3->CountAnim++;
				if ((enemy3->CountAnim % TIME_ANIMATION_ENEMY3) == 0)
				{
					// �p�^�[���̐؂�ւ�
					enemy3->PatternAnim = (enemy3->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY3;

					// �e�N�X�`�����W��ݒ�
					SetTextureEnemy3(i, enemy3->PatternAnim);

				}

				if (GetEnemy3(i)->counter > 16 && GetEnemy3(i)->counter < 32)
				{
					GetEnemy3(i)->pos.y -= 1.0f;
				}

				if (GetEnemy3(i)->counter > 32)/*&& GetEnemy3(i)->counter < )*/
				{
					GetEnemy3(i)->pos.x -= 1.0f;
				}





				//if (enemy3Wk->counter < 10)
				//{


				//	if (GetPlayer(0)->pos.x <= GetEnemy3(i)->pos.x)
				//	{
				//		GetEnemy3(i)->pos.x -= 1.0f;
				//	}
				//	else if (GetPlayer(0)->pos.x >= GetEnemy3(i)->pos.x)
				//	{

				//		GetEnemy3(i)->pos.x += 1.0f;

				//	}
				//	if (GetPlayer(0)->pos.y <= GetEnemy3(i)->pos.y)
				//	{

				//		GetEnemy3(i)->pos.y -= 1.0f;
				//	}
				//	else if (GetPlayer(0)->pos.y >= GetEnemy3(i)->pos.y)
				//	{
				//		GetEnemy3(i)->pos.y += 1.0f;
				//	}




					//�G�l�~�[�̒e����
					//D3DXVECTOR3 pos = enemy3->pos;
					//enemy3->pos.y -= TEXTURE_ENEMY3_SIZE_Y;
					//SetEBullet(pos);









				// ��ʊO�܂Ői�񂾁H
				if (enemy3->pos.x < 0-TEXTURE_ENEMY3_SIZE_X/* - SCREEN_WIDTH*/)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					enemy3->use = false;
					enemy3->pos.x = 800.0f;
				}

				GetEnemy3(i)->enemy3pos_x = GetEnemy3(i)->pos.x;
				GetEnemy3(i)->enemy3pos_y = GetEnemy3(i)->pos.y;


				SetVertexEnemy3(i);	// �ړ���̍��W�Œ��_��ݒ�
			}


			if (GetEnemy3(i)->effectflag3 == true)
			{
				SetEffect3(GetEnemy3(i)->pos, i);

			}

			if (GetEnemy3(i)->BBflag == true)
			{

				boss->Popcounter++;
				GetEnemy3(i)->BBflag = false;

			}


			if (boss->use == true)
			{

				GetEnemy3(i)->use = false;

			}


		}

}






//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = enemy3Wk;				// �G�l�~�[�̃|�C���^�[��������


	if (enemy3->counter > 16)
	{


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY3_MAX; i++, enemy3++)
		{
			if (enemy3->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemy3->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY3, enemy3->vertexWk_enemy3, sizeof(VERTEX_2D));
			}
		}

	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy3( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY3 *enemy3 = &enemy3Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy3( no );

	// rhw�̐ݒ�
	enemy3->vertexWk_enemy3[0].rhw =
	enemy3->vertexWk_enemy3[1].rhw =
	enemy3->vertexWk_enemy3[2].rhw =
	enemy3->vertexWk_enemy3[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy3->vertexWk_enemy3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy3->vertexWk_enemy3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy3->vertexWk_enemy3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy3->vertexWk_enemy3[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY3, 0.0f);
	enemy3->vertexWk_enemy3[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY3);
	enemy3->vertexWk_enemy3[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY3, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY3);






	//enemy3->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy3->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy3->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy3->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy3( int no,int cntPattern )
{
	ENEMY3 *enemy3 = &enemy3Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY3;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY3;
	
	enemy3->vertexWk_enemy3[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy3->vertexWk_enemy3[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy3->vertexWk_enemy3[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy3->vertexWk_enemy3[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy3( int no )
{
	ENEMY3 *enemy3 = &enemy3Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy3->vertexWk_enemy3[0].vtx.x = enemy3->pos.x - cosf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[0].vtx.y = enemy3->pos.y - sinf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[0].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[1].vtx.x = enemy3->pos.x + cosf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[1].vtx.y = enemy3->pos.y - sinf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[1].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[2].vtx.x = enemy3->pos.x - cosf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[2].vtx.y = enemy3->pos.y + sinf(enemy3->BaseAngle - enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[2].vtx.z = 0.0f;

	enemy3->vertexWk_enemy3[3].vtx.x = enemy3->pos.x + cosf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[3].vtx.y = enemy3->pos.y + sinf(enemy3->BaseAngle + enemy3->rot.z) * enemy3->Radius;
	enemy3->vertexWk_enemy3[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY3 *GetEnemy3(int no)
{

	
	return(&enemy3Wk[no]);



}


