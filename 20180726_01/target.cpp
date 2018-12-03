//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "input.h"
#include "bullet.h"
#include "target.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTarget( int no );
void SetTextureTarget( int no, int cntPattern );
void SetVertexTarget( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTarget = NULL;		// �e�N�X�`���ւ̃|���S��

TARGET					targetWk[TARGET_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitTarget(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TARGET,				// �t�@�C���̖��O
			&g_pD3DTextureTarget);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏���������
	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		target->use = true;									// �g�p
		target->pos = D3DXVECTOR3(i*200.0f+200.0f, 300.0f, 0.0f);	// ���W�f�[�^��������
		target->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		target->PatternAnim = rand() % ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		target->CountAnim = 0;								// �A�j���J�E���g��������
		target->HP = 5;
		target->rockflug = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		target->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		target->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������

		target->Texture = g_pD3DTextureTarget;				// �e�N�X�`�����
		MakeVertexTarget(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTarget(void)
{
	if (g_pD3DTextureTarget != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureTarget->Release();
		g_pD3DTextureTarget = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTarget(void)
{
	TARGET *target = &targetWk[0];
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	ENEMY	*enemy = GetEnemy(0);
	ENEMY2	*enemy2 = GetEnemy2(0);
	PLAYER *player = GetPlayer(0);


	for (int i = 0; i < TARGET_MAX; i++, target++)
	{



	//	if (target->rockflug == false)
	//	{
	//		switch (player->i)
	//		{
	//		case 1:

	//			target->pos.x = player->pos.x;
	//			target->pos.y = player->pos.y - 100.0f;
	//			break;

	//		case 2:

	//			target->pos.x = player->pos.x + 300.0f;
	//			target->pos.y = player->pos.y;

	//			if (GetKeyboardPress(DIK_UP) || IsButtonPressed(0, BUTTON_X))
	//			{
	//				target->pos.y -= 4.0f;
	//			}

	//			if (GetKeyboardPress(DIK_DOWN) || IsButtonPressed(0, BUTTON_B))
	//			{
	//				target->pos.y += 4.0f;
	//			}


	//			break;

	//		case 3:

	//			target->pos.x = player->pos.x - 300.0f;
	//			target->pos.y = player->pos.y;

	//			break;

	//		case 4:

	//			target->pos.x = player->pos.x;
	//			target->pos.y = player->pos.y + 100.0f;
	//			break;


	//		}

	//	}



		//if (target->rockflug == true)
		//{

		//	target->pos


		//}

		if (GetKeyboardPress(DIK_RIGHT)|| IsButtonPressed(0, BUTTON_C))
		{
			target->pos.x += 4.0f;
		}

		if (GetKeyboardPress(DIK_LEFT)|| IsButtonPressed(0, BUTTON_A))
		{
			target->pos.x -= 4.0f;
		}

		if (GetKeyboardPress(DIK_UP)|| IsButtonPressed(0, BUTTON_X))


		{
			target->pos.y -= 4.0f;
		}

		if (GetKeyboardPress(DIK_DOWN) || IsButtonPressed(0, BUTTON_B))
		{
			target->pos.y += 4.0f;
		}



		if (target->pos.x < 25)
		{

			target->pos.x = 25;


		}

		if (target->pos.x > 777)
		{

			target->pos.x = 777;


		}

		if (target->pos.y < 45)
		{

			target->pos.y = 45;


		}

		if (target->pos.y > 408)
		{

			target->pos.y = 408;


		}


		//if (GetKeyboardPress(DIK_RETURN))
		//{

		//	target->pos.x=GetEnemy(i)->enemypos_x;
		//	target->pos.y=GetEnemy(i)->enemypos_y;
			//target->rockflug = true;
		//}



		//if (GetKeyboardPress(DIK_LSHIFT))
		//{


			//target->pos1.x = enemy2->pos.x;
			//target->pos1.y = enemy2->pos.y;

		//	target->drawflug = true;



		//}





		//if (GetKeyboardPress(DIK_RSHIFT))
		//{
		//	target->drawflug = false;
		//}




	//if (player->Timecounter > 6)
	//{
	//	player->Hitcounter=0;
	//	player->Timecounter = 0;
	//	//player->Hitcounter = 0;

	//}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexTarget(i);
		
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[0];
	ENEMY*enemy = GetEnemy(0);


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		if (target->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			//if (target->drawflug == true)
			//{
					//if (enemy->use == true)
					//{
						// �e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, target->Texture);

						// �|���S���̕`��
						pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, target->vertexWk, sizeof(VERTEX_2D));
					//}
			//}

		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTarget(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[no];

	// ���_���W�̐ݒ�
	SetVertexTarget(no);

	// rhw�̐ݒ�
	target->vertexWk[0].rhw =
	target->vertexWk[1].rhw =
	target->vertexWk[2].rhw =
	target->vertexWk[3].rhw = 1.0f;
	

	// ���ˌ��̐ݒ�
	target->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	target->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	target->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	target->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	target->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	target->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	target->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	target->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );

	//player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//player->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//player->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
//void SetRGBPlayer(int no, int cntPattern)
//{
//
//	PLAYER *player = &playerWk[no];
//
//	// ���ˌ��̐ݒ�
//	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTarget( int no, int cntPattern )
{
	TARGET *target = &targetWk[0];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	
	target->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	target->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	target->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	target->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTarget(int no)
{
	TARGET *target = &targetWk[0];

	// ���_���W�̐ݒ�
	target->vertexWk[0].vtx.x = target->pos.x - cosf(target->BaseAngle + target->rot.z) * target->Radius;
	target->vertexWk[0].vtx.y = target->pos.y - sinf(target->BaseAngle + target->rot.z) * target->Radius;
	target->vertexWk[0].vtx.z = 0.0f;

	target->vertexWk[1].vtx.x = target->pos.x + cosf(target->BaseAngle - target->rot.z) * target->Radius;
	target->vertexWk[1].vtx.y = target->pos.y - sinf(target->BaseAngle - target->rot.z) * target->Radius;
	target->vertexWk[1].vtx.z = 0.0f;

	target->vertexWk[2].vtx.y = target->pos.y + sinf(target->BaseAngle - target->rot.z) * target->Radius;
	target->vertexWk[2].vtx.x = target->pos.x - cosf(target->BaseAngle - target->rot.z) * target->Radius;
	target->vertexWk[2].vtx.z = 0.0f;
	
	target->vertexWk[3].vtx.x = target->pos.x + cosf(target->BaseAngle + target->rot.z) * target->Radius;
	target->vertexWk[3].vtx.y = target->pos.y + sinf(target->BaseAngle + target->rot.z) * target->Radius;
	target->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
TARGET *GetTarget(int no)
{
	return(&targetWk[no]);
}

