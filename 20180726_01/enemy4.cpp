//=============================================================================
//
// �G���� [enemy4.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy4.h"
#include "player.h"
#include "Ebullet.h"
#include "input.h"
#include"effect4.h"
#include"boss.h"
#include <stdio.h>
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy4( int no);
void SetTextureEnemy4( int no,int cntPattern );
void SetVertexEnemy4( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy4 = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY4					enemy4Wk[ENEMY4_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy4(int type)
{

	srand((unsigned)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = enemy4Wk;				// �G�l�~�[�̃|�C���^�[��������
	int j = 0;
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY4,			// �t�@�C���̖��O
			&g_pD3DTextureEnemy4);			// �ǂݍ��ރ������̃|�C���^


	}

	j = rand() % (9);


	//enemy4->pos = D3DXVECTOR3(i * 50 + enemy4->InitY, i*50.0f, 0.0f);		// ���W�f�[�^��������


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
	{
		enemy4->use = true;										// �g�p
		enemy4->pos = D3DXVECTOR3(-50,i*100.0f, 0.0f);		// ���W�f�[�^��������
		enemy4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy4->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy4->CountAnim = 0;									// �A�j���J�E���g��������
		enemy4->counter = 0;										//�G�l�~�[�̏o�����Ԃ��Ǘ�
		enemy4->nextflag = false;
		enemy4->effectflag4 = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY4_SIZE_X, TEXTURE_ENEMY4_SIZE_Y);
		enemy4->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy4->BaseAngle = atan2f(TEXTURE_ENEMY4_SIZE_Y, TEXTURE_ENEMY4_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy4->Texture = g_pD3DTextureEnemy4;					// �e�N�X�`�����
		MakeVertexEnemy4(i);										// ���_���̍쐬
	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy4(void)
{
	if (g_pD3DTextureEnemy4 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy4->Release();
		g_pD3DTextureEnemy4 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy4(void)
{


	ENEMY4 *enemy4 = GetEnemy4(0);				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);		//�v���C���[�̃|�C���^�[��������
	EBULLET *Ebullet = GetEBullet(0);	// �o���b�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);
	int i = 0;

	if (GetEnemy4(i)->counter == 28)
	{
		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{

			GetEnemy4(i)->use = true;


		}
	}

		//�G�l�~�[MAX���\������
		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{

			if (enemy4->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				//�A�j���[�V����
				enemy4->CountAnim++;
				if ((enemy4->CountAnim % TIME_ANIMATION_ENEMY4) == 0)
				{
					// �p�^�[���̐؂�ւ�
					enemy4->PatternAnim = (enemy4->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY4;

					// �e�N�X�`�����W��ݒ�
					SetTextureEnemy4(i, enemy4->PatternAnim);

				}


				if (GetEnemy4(i)->counter > 28 && GetEnemy4(i)->counter < 48)
				{
					GetEnemy4(i)->pos.x += 1.0f;
				}

				if (GetEnemy4(i)->counter>48/* && GetEnemy4(i)->counter < 48*/)
				{
					GetEnemy4(i)->pos.x -= 1.0f;
				}






				//if (GetPlayer(0)->pos.x <= GetEnemy4(i)->pos.x)
				//{
				//	GetEnemy4(i)->pos.x -= 1.0f;
				//}
				//else if (GetPlayer(0)->pos.x >= GetEnemy4(i)->pos.x)
				//{

				//	GetEnemy4(i)->pos.x += 1.0f;

				//}
				//if (GetPlayer(0)->pos.y <= GetEnemy4(i)->pos.y)
				//{

				//	GetEnemy4(i)->pos.y -= 1.0f;

				//}
				//else if (GetPlayer(0)->pos.y >= GetEnemy4(i)->pos.y)
				//{
				//	GetEnemy4(i)->pos.y += 1.0f;
				//}



				//// ��ʊO�܂Ői�񂾁H
				//if (enemy4->pos.x < 0-TEXTURE_ENEMY4_SIZE_X/* - SCREEN_WIDTH*/)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				//{
				//	enemy4->use = false;
				//	enemy4->pos.x = 700.0f;
				//}

				GetEnemy4(i)->enemy4pos_x = GetEnemy4(i)->pos.x;
				GetEnemy4(i)->enemy4pos_y = GetEnemy4(i)->pos.y;


				SetVertexEnemy4(i);	// �ړ���̍��W�Œ��_��ݒ�
			}


			if (GetEnemy4(i)->effectflag4 == true)
			{
				SetEffect4(GetEnemy4(i)->pos, i);
			}
			if (GetEnemy4(i)->BBflag == true)
			{
				boss->Popcounter++;
				GetEnemy4(i)->BBflag = false;
			}
			if (boss->use == true)
			{
				GetEnemy4(i)->use = false;
			}

		}



}





//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = enemy4Wk;				// �G�l�~�[�̃|�C���^�[��������

	if (enemy4->counter > 28)
	{


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY4_MAX; i++, enemy4++)
		{
			if (enemy4->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemy4->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY4, enemy4->vertexWk_enemy4, sizeof(VERTEX_2D));
			}
		}

	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy4( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY4 *enemy4 = &enemy4Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy4( no );

	// rhw�̐ݒ�
	enemy4->vertexWk_enemy4[0].rhw =
	enemy4->vertexWk_enemy4[1].rhw =
	enemy4->vertexWk_enemy4[2].rhw =
	enemy4->vertexWk_enemy4[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy4->vertexWk_enemy4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy4->vertexWk_enemy4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy4->vertexWk_enemy4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy4->vertexWk_enemy4[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY4, 0.0f);
	enemy4->vertexWk_enemy4[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY4);
	enemy4->vertexWk_enemy4[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY4, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY4);






	//enemy4->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy4->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy4->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy4->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy4( int no,int cntPattern )
{
	ENEMY4 *enemy4 = &enemy4Wk[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY4;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY4;
	
	enemy4->vertexWk_enemy4[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy4->vertexWk_enemy4[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy4->vertexWk_enemy4[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy4->vertexWk_enemy4[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy4( int no )
{
	ENEMY4 *enemy4 = &enemy4Wk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy4->vertexWk_enemy4[0].vtx.x = enemy4->pos.x - cosf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[0].vtx.y = enemy4->pos.y - sinf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[0].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[1].vtx.x = enemy4->pos.x + cosf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[1].vtx.y = enemy4->pos.y - sinf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[1].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[2].vtx.x = enemy4->pos.x - cosf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[2].vtx.y = enemy4->pos.y + sinf(enemy4->BaseAngle - enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[2].vtx.z = 0.0f;

	enemy4->vertexWk_enemy4[3].vtx.x = enemy4->pos.x + cosf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[3].vtx.y = enemy4->pos.y + sinf(enemy4->BaseAngle + enemy4->rot.z) * enemy4->Radius;
	enemy4->vertexWk_enemy4[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY4 *GetEnemy4(int no)
{

	
	return(&enemy4Wk[no]);



}


