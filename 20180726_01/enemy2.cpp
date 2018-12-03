//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy4.h"
#include "enemy2.h"
#include "input.h"
#include "effect2.h"
#include"boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy2( int no);
void SetTextureEnemy2( int no,int cntPattern );
void SetVertexEnemy2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy2 = NULL;		// �e�N�X�`���ւ̃|���S��


ENEMY2					enemyWk2[ENEMY2_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY2 *enemy2 = enemyWk2;				// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY2,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy2);			// �ǂݍ��ރ������̃|�C���^


	}

		// �G�l�~�[�̏���������
		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{
			enemy2->use = false;										// �g�p
			enemy2->effectflag2 = false;
			enemy2->BBflag = false;
			enemy2->comeback = false;
			enemy2->pos = D3DXVECTOR3(i * 80+100 + 100.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
			enemy2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			enemy2->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
			enemy2->CountAnim = 0;									// �A�j���J�E���g��������
			enemy2->counter = 0;

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY2_SIZE_X, TEXTURE_ENEMY2_SIZE_Y);
			enemy2->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
			enemy2->BaseAngle = atan2f(TEXTURE_ENEMY2_SIZE_Y, TEXTURE_ENEMY2_SIZE_X);	// �G�l�~�[�̊p�x��������

			enemy2->Texture_enemy = g_pD3DTextureEnemy2;					// �e�N�X�`�����
			MakeVertexEnemy2(i);										// ���_���̍쐬
		}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy2(void)
{
	if (g_pD3DTextureEnemy2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy2->Release();
		g_pD3DTextureEnemy2 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy2(void)
{
	ENEMY2 *enemy2 = enemyWk2;				// �G�l�~�[�̃|�C���^�[��������
	ENEMY4 *enemy4 = GetEnemy4(0);				// �G�l�~�[�̃|�C���^�[��������
	EFFECT2*effect2 = GetEffect2(0);
	BOSS*boss = GetBoss(0);
	int i = 0;

	if (GetEnemy2(i)->counter == 16)
	{
		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{

			GetEnemy2(i)->use = true;


		}
	}

	for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
	{


		if (GetEnemy2(i)->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			GetEnemy2(i)->CountAnim++;
			if ((GetEnemy2(i)->CountAnim % TIME_ANIMATION_ENEMY2) == 0)
			{
				// �p�^�[���̐؂�ւ�
				GetEnemy2(i)->PatternAnim = (GetEnemy2(i)->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY2;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemy2(i, GetEnemy2(i)->PatternAnim);

			}


			if (GetEnemy2(i)->counter > 16 && GetEnemy2(i)->counter < 28)
			{
				GetEnemy2(i)->pos.y += 1.0f;
			}

			if (GetEnemy2(i)->counter > 28)/*&& GetEnemy3(i)->counter < )*/
			{
				GetEnemy2(i)->pos.x -= 1.0f;
			}


			GetEnemy2(i)->enemy2pos_x = GetEnemy2(i)->pos.x;
			GetEnemy2(i)->enemy2pos_y = GetEnemy2(i)->pos.y;



			if (GetEnemy2(i)->pos.x < 100)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				GetEnemy2(i)->use = false;
				GetEnemy2(i)->pos.x = 800.0f;
				GetEnemy2(i)->pos.y = 100.0f;
			}


			SetVertexEnemy2(i);	// �ړ���̍��W�Œ��_��ݒ�

		}

		if (GetEnemy2(i)->effectflag2 == true)
		{
			SetEffect2(GetEnemy2(i)->pos, i);

		}

		if (GetEnemy2(i)->BBflag == true)
		{

			boss->Popcounter++;
			GetEnemy2(i)->BBflag = false;

		}

		//if (GetEnemy4(i)->counter > 32)
		//{

		//	GetEnemy2(i)->comeback = true;
		//	if (GetEnemy2(i)->comeback == true)
		//	{

		//		GetEnemy2(i)->use = true;

		//	}

		//}





	}

	

	if (boss->use == true)
	{

		enemy2->use = false;

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY2 *enemy2 = enemyWk2;				// �G�l�~�[�̃|�C���^�[��������


	if (enemy2->counter > 16)
	{


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY2_MAX; i++, enemy2++)
		{
			if (enemy2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemy2->Texture_enemy);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY2, enemy2->vertexWk_enemy, sizeof(VERTEX_2D));
			}
		}

	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy2( int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������


	// ���_���W�̐ݒ�
	SetVertexEnemy2( no );

	// rhw�̐ݒ�
	enemy2->vertexWk_enemy[0].rhw =
	enemy2->vertexWk_enemy[1].rhw =
	enemy2->vertexWk_enemy[2].rhw =
	enemy2->vertexWk_enemy[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy2->vertexWk_enemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy2->vertexWk_enemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy2->vertexWk_enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy2->vertexWk_enemy[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 0.0f);
	enemy2->vertexWk_enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);
	enemy2->vertexWk_enemy[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY2);






	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy2( int no,int cntPattern )
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������


	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY2;
	
	enemy2->vertexWk_enemy[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy2->vertexWk_enemy[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy2->vertexWk_enemy[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy2->vertexWk_enemy[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy2( int no )
{
	ENEMY2 *enemy2 = &enemyWk2[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy2->vertexWk_enemy[0].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[0].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[0].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[1].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[1].vtx.y = enemy2->pos.y - sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[1].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[2].vtx.x = enemy2->pos.x - cosf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[2].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle - enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[2].vtx.z = 0.0f;

	enemy2->vertexWk_enemy[3].vtx.x = enemy2->pos.x + cosf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[3].vtx.y = enemy2->pos.y + sinf(enemy2->BaseAngle + enemy2->rot.z) * enemy2->Radius;
	enemy2->vertexWk_enemy[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY2 *GetEnemy2(int no)
{

	
	return(&enemyWk2[no]);



}


