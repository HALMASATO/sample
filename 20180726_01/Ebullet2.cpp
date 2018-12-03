
//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy6.h"
#include "Ebullet2.h"
#include "player.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEBullet2( int no );
void SetTextureEBullet2( int no, int cntPattern );
void SetVertexEBullet2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEBullet2 = NULL;		// �e�N�X�`���ւ̃|���S��

EBULLET2					EbulletWk[EBULLET2_MAX];			// �o���b�g�\����

 //static LPDIRECTSOUNDBUFFER8	g_p1SE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEBullet2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = &EbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EBULLET2,			// �t�@�C���̖��O
			&g_pD3DTextureEBullet2);			// �ǂݍ��ރ������̃|�C���^
		
		//g_p1SE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
	{
		ebullet2->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		ebullet2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		ebullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		ebullet2->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		ebullet2->CountAnim = 0;									// �A�j���J�E���g��������
		ebullet2->counter = 0;
		ebullet2->Bcounter_ORG=0;

		ebullet2->Texture = g_pD3DTextureEBullet2;					// �e�N�X�`�����
		MakeVertexEBullet2(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEBullet2(void)
{
	if (g_pD3DTextureEBullet2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEBullet2->Release();
		g_pD3DTextureEBullet2 = NULL;
	}

	//if (g_p1SE != NULL)
	//{	// �e�N�X�`���̊J��
	//	g_p1SE->Release();
	//	g_p1SE = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEBullet2(void)
{
	EBULLET2 *ebullet2 = GetEBullet2(0);				// �o���b�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);						//�{�X�̃|�C���^�[��������
	PLAYER*player = GetPlayer(0);

	


	for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
	{
		if (ebullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			//// �o���b�g�̈ړ�����
			//GetEBullet2(i)->pos.x -= GetEBullet2(i)->SPPED_X;
			//GetEBullet2(i)->pos.y -= GetEBullet2(i)->SPPED_Y;

			GetEBullet2(i)->pos.x -= 5.0f;


			////�A�j���[�V����
			//ebullet2->CountAnim++;
			//if ((ebullet2->CountAnim % TIME_ANIMATION_EBULLET2) == 0)
			//{
			//	// �p�^�[���̐؂�ւ�
			//	ebullet2->PatternAnim = (ebullet2->PatternAnim + 1) % ANIM_PATTERN_NUM_EBULLET2;
			//	// �e�N�X�`�����W��ݒ�
			//	SetTextureEBullet2(i, ebullet2->PatternAnim);
			//}

			// ��ʊO�܂Ői�񂾁H
			if (GetEBullet2(i)->pos.x < TEXTURE_EBULLET2_SIZE_X - SCREEN_WIDTH)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				ebullet2->use = false;
				ebullet2->pos.x = 100.0f;
			}

			SetVertexEBullet2(i);				// �ړ���̍��W�Œ��_��ݒ�

			if (boss->use == true)
			{

				GetEBullet2(i)->use = false;

			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEBullet2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = EbulletWk;				// �o���b�g�̃|�C���^�[��������
	//BOSS*boss = GetBoss(0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


		for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
		{
			if (ebullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, ebullet2->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EBULLET2, ebullet2->vertexWk, sizeof(VERTEX_2D));
			}
		}
	

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEBullet2( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET2 *ebullet2 = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEBullet2( no );

	// rhw�̐ݒ�
	ebullet2->vertexWk[0].rhw =
	ebullet2->vertexWk[1].rhw =
	ebullet2->vertexWk[2].rhw =
	ebullet2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	ebullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	ebullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ebullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2, 0.0f);
	ebullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2);
	ebullet2->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EBULLET2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EBULLET2);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEBullet2( int no, int cntPattern )
{
	EBULLET2 *ebullet2 = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2;
	
	ebullet2->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ebullet2->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ebullet2->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ebullet2->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEBullet2( int no )
{
	EBULLET2 *ebullet2 = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	ebullet2->vertexWk[0].vtx.x = ebullet2->pos.x - TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[0].vtx.y = ebullet2->pos.y - TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[0].vtx.z = 0.0f;

	ebullet2->vertexWk[1].vtx.x = ebullet2->pos.x + TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[1].vtx.y = ebullet2->pos.y - TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[1].vtx.z = 0.0f;

	ebullet2->vertexWk[2].vtx.x = ebullet2->pos.x - TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[2].vtx.y = ebullet2->pos.y + TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[2].vtx.z = 0.0f;

	ebullet2->vertexWk[3].vtx.x = ebullet2->pos.x + TEXTURE_EBULLET2_SIZE_X;
	ebullet2->vertexWk[3].vtx.y = ebullet2->pos.y + TEXTURE_EBULLET2_SIZE_Y;
	ebullet2->vertexWk[3].vtx.z = 0.0f;
}

////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureEBullet2(int no,int cntPattern)
//{
//	EBULLET2 *ebullet2 = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������
//
//
//	// �e�N�X�`�����W�̐ݒ�
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET2;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET2;
//
//	ebullet2->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	ebullet2->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	ebullet2->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	ebullet2->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//
//
//}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEBullet2(D3DXVECTOR3 pos)
{
		EBULLET2 *ebullet2 = GetEBullet2(0);			// �o���b�g�̃|�C���^�[��������
		PLAYER*player = GetPlayer(0);

		float	SPEED = 0;

			// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
			for (int i = 0; i < EBULLET2_MAX; i++, ebullet2++)
			{
				if (GetEBullet2(i)->use == false)			// ���g�p��Ԃ̃o���b�g��������
				{
					GetEBullet2(i)->use = true;			// �g�p��Ԃ֕ύX����
					GetEBullet2(i)->pos = pos;				// ���W���Z�b�g


					//GetEBullet2(i)->dis = player->pos - pos;
					//bool ZetFlag = false;

					//if (GetEBullet2(i)->dis.y < 0)
					//{
					//	GetEBullet2(i)->dis.y *= (-1);
					//	ZetFlag = true;
					//}

					//if (GetEBullet2(i)->dis.x < GetEBullet2(i)->dis.y)
					//{
					//	SPEED = GetEBullet2(i)->dis.y / EBULLET2_SPEED;
					//}
					//else
					//{
					//	SPEED = GetEBullet2(i)->dis.x / EBULLET2_SPEED;
					//}
					//if (ZetFlag == true)
					//{
					//	GetEBullet2(i)->dis.y *= (-1);
					//	ZetFlag = false;
					//}

					//GetEBullet2(i)->SPPED_Y = GetEBullet2(i)->dis.y / SPEED;
					//GetEBullet2(i)->SPPED_X = GetEBullet2(i)->dis.x / SPEED;





					ebullet2->pos.x -= (TEXTURE_ENEMY6_SIZE_X / 2) + (TEXTURE_EBULLET2_SIZE_X / 2);

					// ���ˉ��Đ�
					//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

					return;							// 1���Z�b�g�����̂ŏI������
				}
			}
}
//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EBULLET2 *GetEBullet2(int no)
{
	return(&EbulletWk[no]);
}

