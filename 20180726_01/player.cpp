//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include "bullet.h"
#include "target.h"
#include "bullet2.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );
HRESULT InitMakeVertexPlayer(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

PLAYER					playerWk[PLAYER_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYER,				// �t�@�C���̖��O
			&g_pD3DTexturePlayer);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;	
		player->yoko = false;
		player->tate = false;
		player->pos = D3DXVECTOR3(i*50.0f+100.0f, 300.0f, 0.0f);	// ���W�f�[�^��������
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		player->PatternAnim = rand() % ANIM_PATTERN_NUM_PLAYER;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		player->CountAnim = 0;								// �A�j���J�E���g��������
		player->HP = 80;
		player->i = 2;
		player->MAXHP = player->HP;
		player->counter = 80;
		player->Bcounter = 50;
		player->MAXBcounter = player->Bcounter;
		player->MAXcounter = player->counter;
		player->drawflug = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		player->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������



		player->Texture = g_pD3DTexturePlayer;				// �e�N�X�`�����
		MakeVertexPlayer(i);								// ���_���̍쐬
		//InitMakeVertexPlayer(i);


	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

	if (g_pD3DTexturePlayer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	TARGET *target = GetTarget(0);



	if (player->Timecounter > 6)
	{
		player->Hitcounter=0;
		player->Timecounter = 0;

	}




	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (GetPlayer(i)->use == true)
		{
			// �A�j���[�V����
			GetPlayer(i)->CountAnim++;
			if ((GetPlayer(i)->CountAnim % TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				GetPlayer(i)->PatternAnim = (GetPlayer(i)->PatternAnim + 1) % ANIM_PATTERN_NUM_PLAYER;

				// �e�N�X�`�����W��ݒ�
				SetTexturePlayer(i, GetPlayer(i)->PatternAnim);
			}


			// �L�[�{�[�h���͂ňړ�(�ЂƂ܂��S�v���C���[�𓯂��L�[�œ��������Ⴄ)
			//���ړ�
			if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
			{
				player->pos.y += PLAYER_SPEED;
				player->tate = true;
				player->yoko = false;
				player->i = 3;


			}

			//���ړ�
			else if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))
			{
				player->pos.x -= PLAYER_SPEED;

				player->i = 3;
				player->Xmuki = true;
				player->yoko = true;
				player->tate = false;

			}

			//��ړ�
			if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP))
			{

				player->pos.y -= PLAYER_SPEED;
				player->tate = true;
				player->yoko = false;
				player->i = 2;

			}

			//�E�ړ�
			if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->pos.x += PLAYER_SPEED;
				player->i = 2;
				player->yoko = true;
				player->tate = false;
				player->Xmuki = false;


			}


			//�E�����Ă�Ƃ�
			if (player->Xmuki == false)
			{


				//�ړ�
				if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y -= PLAYER_SPEED;
					player->i = 2;

				}

				if (GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y += PLAYER_SPEED;
					player->i = 2;

				}

			}


			//�������Ă�Ƃ�
			if (player->Xmuki == true)
			{
				//�ړ�
				if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y -= PLAYER_SPEED;
					player->i = 3;

				}

				if (GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_LSHIFT))
				{

					player->pos.y += PLAYER_SPEED;
					player->i = 2;

				}


				

			}



			//if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
			//{

			//	player->pos.y -= 3.0f;e
			//	player->i = 2;

			//}








			//��ʊO�ɏo�Ȃ�����
			if (player->pos.x < 25)
			{

				player->pos.x = 25;

			}

			if (player->pos.x > 777)
			{

				player->pos.x = 777;

			}

			if (player->pos.y < 45)
			{

				player->pos.y = 45;

			}

			if (player->pos.y > 408)
			{

				player->pos.y = 408;

			}




			//// ��]
			//if (GetKeyboardPress(DIK_RIGHT))
			//{
			//	player->rot.z += 0.1f;
			//}

			//if (GetKeyboardPress(DIK_LEFT))
			//{
			//	player->rot.z -= 0.1f;
			//}



			// �g��k��
			if (GetKeyboardPress(DIK_F))
			{
				player->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player->Radius += 1.0f;
			}







			// �e����
			else if (GetKeyboardTrigger(DIK_SPACE) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Y) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Z) || IsButtonTriggered(0, BUTTON_L) || IsButtonTriggered(0, BUTTON_R))
			{

				D3DXVECTOR3 pos = player->pos;


				if (player->yoko == true)
				{
					pos.x += TEXTURE_PLAYER_SIZE_X;

				}

				if (player->tate == true)
				{

					pos.y -= TEXTURE_PLAYER_SIZE_Y;

				}

					SetBullet(pos);
					bullet->BM += 1;

			}

			//// �e����
			//else if (IsButtonPressed(0, BUTTON_B) && bullet->reload == 0)
			//{

			//	if (target->rockflug == true)
			//	{
			//		D3DXVECTOR3 pos = player->pos;
			//		pos.x += TEXTURE_PLAYER_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER_SIZE_Y;
			//		SetBullet(pos);
			//		bullet->BM += 1;
			//	}

			//}



			//if (GetKeyboardTrigger(DIK_Z))
			//{

			//	//if (target->rockflug == true)
			//	//{
			//		D3DXVECTOR3 pos = player->pos;
			//		pos.x += TEXTURE_PLAYER_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER_SIZE_Y;
			//		SetBullet2(pos);
			//	//}

			//}


			//else if (IsButtonTriggered(0, BUTTON_B))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}
			//�����[�h�^�C���̒���

			if (bullet->reload == 5)
			{
				bullet->BM = 0;
				bullet->reload = 0;

			}



			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer(i);
			//MakeVertexPlayer(i);								// ���_���̍쐬


		}
		
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];


	for (int i = 0; i < player->Timecounter; i++)
	{
		switch (player->Timecounter)
		{
		case 1:
			player->drawflug = true;
			break;

		case 2:
			player->drawflug = false;
			break;

		case 3:
			player->drawflug = true;
			break;

		case 4:
			player->drawflug = false;
			break;

		case 5:
			player->drawflug = true;
			break;

		case 6:
			player->drawflug = false;
			break;

		default:
			break;
		}
	}


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			if (player->drawflug == false)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, player->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));

			}

		}
	}

}


//=============================================================================
// ������Ԃ̒��_�̍쐬
//=============================================================================
HRESULT InitMakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);

	return S_OK;


}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// ���_���W�̐ݒ�
	SetVertexPlayer(no);

	// rhw�̐ݒ�
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;
	

	// ���ˌ��̐ݒ�
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// �e�N�X�`�����W�̐ݒ�
	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER);


	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];
	
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER;

	switch (player->i)
	{
	case 1:
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;
		
	case 2:

			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	case 3:
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	case 4:
			player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			break;

	}


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// ���_���W�̐ݒ�
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

