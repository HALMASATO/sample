//=============================================================================
//
// �v���C���[���� [player2.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player2.h"
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
HRESULT MakeVertexPlayer2( int no );
void SetTexturePlayer2( int no, int cntPattern );
void SetVertexPlayer2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer2 = NULL;		// �e�N�X�`���ւ̃|���S��

PLAYER2					player2Wk[PLAYER2_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER2 *player2 = &player2Wk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYER2,				// �t�@�C���̖��O
			&g_pD3DTexturePlayer2);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER2_MAX; i++, player2++)
	{
		player2->use = true;									// �g�p
		player2->pos = D3DXVECTOR3(i*50.0f+100.0f, 300.0f, 0.0f);	// ���W�f�[�^��������
		player2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		player2->PatternAnim = rand() % ANIM_PATTERN_NUM_PLAYER2;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		player2->CountAnim = 0;								// �A�j���J�E���g��������
		player2->HP = 80;
		player2->MAXHP = player2->HP;
		player2->counter = 80;
		player2->Bcounter = 50;
		player2->MAXBcounter = player2->Bcounter;
		player2->MAXcounter = player2->counter;
		player2->drawflug = false;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER2_SIZE_X, TEXTURE_PLAYER2_SIZE_Y);
		player2->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		player2->BaseAngle = atan2f(TEXTURE_PLAYER2_SIZE_Y, TEXTURE_PLAYER2_SIZE_X);	// �v���C���[�̊p�x��������

		player2->Texture = g_pD3DTexturePlayer2;				// �e�N�X�`�����
		MakeVertexPlayer2(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer2(void)
{
	if (g_pD3DTexturePlayer2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer2->Release();
		g_pD3DTexturePlayer2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer2(void)
{
	PLAYER2 *player2 = &player2Wk[0];
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	TARGET *target = GetTarget(0);



	if (player2->Timecounter > 6)
	{
		player2->Hitcounter=0;
		player2->Timecounter = 0;

	}




	for (int i = 0; i < PLAYER2_MAX; i++, player2++)
	{
		if (GetPlayer2(i)->use == true)
		{
			// �A�j���[�V����
			GetPlayer2(i)->CountAnim++;
			if ((GetPlayer2(i)->CountAnim % TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				GetPlayer2(i)->PatternAnim = (GetPlayer2(i)->PatternAnim + 1) % ANIM_PATTERN_NUM_PLAYER2;

				// �e�N�X�`�����W��ݒ�
				SetTexturePlayer2(i, GetPlayer2(i)->PatternAnim);
			}


			// �L�[�{�[�h���͂ňړ�(�ЂƂ܂��S�v���C���[�𓯂��L�[�œ��������Ⴄ)
			if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
			{
				player2->pos.y += 3.0f;



			}
			else if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP))
			{
				player2->pos.y -= 3.0f;



			}

			if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
			{
				player2->pos.x += 3.0f;



			}
			else if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))
			{
				player2->pos.x -= 3.0f;

			}


			if (player2->pos.x < 25)
			{

				player2->pos.x = 25;


			}

			if (player2->pos.x > 777)
			{

				player2->pos.x = 777;


			}

			if (player2->pos.y < 45)
			{

				player2->pos.y = 45;


			}

			if (player2->pos.y > 408)
			{

				player2->pos.y = 408;


			}



			// ��]
			if (GetKeyboardPress(DIK_R))
			{
				player2->rot.z += 0.1f;
			}

			// �g��k��
			if (GetKeyboardPress(DIK_F))
			{
				player2->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player2->Radius += 1.0f;
			}







			// �e����
			else if (GetKeyboardTrigger(DIK_SPACE) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Y) && bullet->reload == 0 || IsButtonTriggered(0, BUTTON_Z) || IsButtonTriggered(0, BUTTON_L) || IsButtonTriggered(0, BUTTON_R))
			{

				if (target->rockflug == true)
				{
					D3DXVECTOR3 pos = player2->pos;
					pos.x += TEXTURE_PLAYER2_SIZE_X;
					//pos.y += TEXTURE_PLAYER2_SIZE_Y;
					SetBullet(pos);
					bullet->BM += 1;
				}

			}

			//// �e����
			//else if (IsButtonPressed(0, BUTTON_B) && bullet->reload == 0)
			//{

			//	if (target->rockflug == true)
			//	{
			//		D3DXVECTOR3 pos = player2->pos;
			//		pos.x += TEXTURE_PLAYER2_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER2_SIZE_Y;
			//		SetBullet(pos);
			//		bullet->BM += 1;
			//	}

			//}



			//if (GetKeyboardTrigger(DIK_Z))
			//{

			//	//if (target->rockflug == true)
			//	//{
			//		D3DXVECTOR3 pos = player2->pos;
			//		pos.x += TEXTURE_PLAYER2_SIZE_X;
			//		//pos.y += TEXTURE_PLAYER2_SIZE_Y;
			//		SetBullet2(pos);
			//	//}

			//}


			//else if (IsButtonTriggered(0, BUTTON_B))
			//{
			//	D3DXVECTOR3 pos = player2->pos;
			//	pos.y -= TEXTURE_PLAYER2_SIZE_Y;
			//	SetBullet(pos);
			//}
			//�����[�h�^�C���̒���

			if (bullet->reload == 5)
			{
				bullet->BM = 0;
				bullet->reload = 0;

			}






			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer2(i);
		}
		
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER2 *player2 = &player2Wk[0];


	for (int i = 0; i < player2->Timecounter; i++)
	{
		switch (player2->Timecounter)
		{
		case 1:
			player2->drawflug = true;
			break;

		case 2:
			player2->drawflug = false;
			break;

		case 3:
			player2->drawflug = true;
			break;

		case 4:
			player2->drawflug = false;
			break;

		case 5:
			player2->drawflug = true;
			break;

		case 6:
			player2->drawflug = false;
			break;

		default:
			break;
		}
	}


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER2_MAX; i++, player2++)
	{
		if (player2->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			if (player2->drawflug == false)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, player2->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER2, player2->vertexWk, sizeof(VERTEX_2D));

			}

		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer2(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER2 *player2 = &player2Wk[no];

	// ���_���W�̐ݒ�
	SetVertexPlayer2(no);

	// rhw�̐ݒ�
	player2->vertexWk[0].rhw =
	player2->vertexWk[1].rhw =
	player2->vertexWk[2].rhw =
	player2->vertexWk[3].rhw = 1.0f;
	

	// ���ˌ��̐ݒ�
	player2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player2->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player2->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PLAYER2, 0.0f );
	player2->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PLAYER2);
	player2->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PLAYER2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PLAYER2 );

	//player2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//player2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//player2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//player2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
//void SetRGBPlayer2(int no, int cntPattern)
//{
//
//	PLAYER2 *player2 = &player2Wk[no];
//
//	// ���ˌ��̐ݒ�
//	player2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//	player2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer2( int no, int cntPattern )
{
	PLAYER2 *player2 = &player2Wk[no];
	
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PLAYER2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PLAYER2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYER2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYER2;
	
	player2->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	player2->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	player2->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	player2->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer2(int no)
{
	PLAYER2 *player2 = &player2Wk[no];
	
	// ���_���W�̐ݒ�
	player2->vertexWk[0].vtx.x = player2->pos.x - cosf(player2->BaseAngle + player2->rot.z) * player2->Radius;
	player2->vertexWk[0].vtx.y = player2->pos.y - sinf(player2->BaseAngle + player2->rot.z) * player2->Radius;
	player2->vertexWk[0].vtx.z = 0.0f;

	player2->vertexWk[1].vtx.x = player2->pos.x + cosf(player2->BaseAngle - player2->rot.z) * player2->Radius;
	player2->vertexWk[1].vtx.y = player2->pos.y - sinf(player2->BaseAngle - player2->rot.z) * player2->Radius;
	player2->vertexWk[1].vtx.z = 0.0f;

	player2->vertexWk[2].vtx.x = player2->pos.x - cosf(player2->BaseAngle - player2->rot.z) * player2->Radius;
	player2->vertexWk[2].vtx.y = player2->pos.y + sinf(player2->BaseAngle - player2->rot.z) * player2->Radius;
	player2->vertexWk[2].vtx.z = 0.0f;

	player2->vertexWk[3].vtx.x = player2->pos.x + cosf(player2->BaseAngle + player2->rot.z) * player2->Radius;
	player2->vertexWk[3].vtx.y = player2->pos.y + sinf(player2->BaseAngle + player2->rot.z) * player2->Radius;
	player2->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER2 *GetPlayer2(int no)
{
	return(&player2Wk[no]);
}

