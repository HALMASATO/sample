
//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "boss.h"
#include "Ebullet.h"
#include "player.h"
//#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEBullet( int no );
void SetTextureEBullet( int no, int cntPattern );
void SetVertexEBullet( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEBullet = NULL;		// �e�N�X�`���ւ̃|���S��

EBULLET					EbulletWk[EBULLET_MAX];			// �o���b�g�\����

///* static*/ LPDIRECTSOUNDBUFFER8	g_p1SE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &EbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EBULLET,			// �t�@�C���̖��O
			&g_pD3DTextureEBullet);			// �ǂݍ��ރ������̃|�C���^
		
		//g_p1SE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		ebullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		ebullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		ebullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		ebullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		ebullet->CountAnim = 0;									// �A�j���J�E���g��������
		ebullet->counter = 0;
		ebullet->Bcounter_ORG=0;

		ebullet->Texture = g_pD3DTextureEBullet;					// �e�N�X�`�����
		MakeVertexEBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEBullet(void)
{
	if (g_pD3DTextureEBullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEBullet->Release();
		g_pD3DTextureEBullet = NULL;
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
void UpdateEBullet(void)
{
	EBULLET *ebullet = GetEBullet(0);				// �o���b�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);						//�{�X�̃|�C���^�[��������
	PLAYER*player = GetPlayer(0);

	


	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		if (ebullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			GetEBullet(i)->pos.x -= GetEBullet(i)->SPPED_X;
			GetEBullet(i)->pos.y -= GetEBullet(i)->SPPED_Y;


			//�A�j���[�V����
			ebullet->CountAnim++;
			if ((ebullet->CountAnim % TIME_ANIMATION_EBULLET) == 0)
			{
				// �p�^�[���̐؂�ւ�
				ebullet->PatternAnim = (ebullet->PatternAnim + 1) % ANIM_PATTERN_NUM_EBULLET;
				// �e�N�X�`�����W��ݒ�
				SetTextureEBullet(i, ebullet->PatternAnim);
			}

			// ��ʊO�܂Ői�񂾁H
			if (GetEBullet(i)->pos.x < TEXTURE_EBULLET_SIZE_X - SCREEN_WIDTH)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				ebullet->use = false;
				ebullet->pos.x = 100.0f;
			}

			SetVertexEBullet(i);				// �ړ���̍��W�Œ��_��ݒ�

		}
	}
	


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = EbulletWk;				// �o���b�g�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


		for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
		{
			if (ebullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, ebullet->Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EBULLET, ebullet->vertexWk, sizeof(VERTEX_2D));
			}
		}
	

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEBullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEBullet( no );

	// rhw�̐ݒ�
	ebullet->vertexWk[0].rhw =
	ebullet->vertexWk[1].rhw =
	ebullet->vertexWk[2].rhw =
	ebullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	ebullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	ebullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ebullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET, 0.0f);
	ebullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET);
	ebullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_EBULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EBULLET);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEBullet( int no, int cntPattern )
{
	EBULLET *ebullet = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET;
	
	ebullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	ebullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	ebullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	ebullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEBullet( int no )
{
	EBULLET *ebullet = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	ebullet->vertexWk[0].vtx.x = ebullet->pos.x - TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[0].vtx.y = ebullet->pos.y - TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[0].vtx.z = 0.0f;

	ebullet->vertexWk[1].vtx.x = ebullet->pos.x + TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[1].vtx.y = ebullet->pos.y - TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[1].vtx.z = 0.0f;

	ebullet->vertexWk[2].vtx.x = ebullet->pos.x - TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[2].vtx.y = ebullet->pos.y + TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[2].vtx.z = 0.0f;

	ebullet->vertexWk[3].vtx.x = ebullet->pos.x + TEXTURE_EBULLET_SIZE_X;
	ebullet->vertexWk[3].vtx.y = ebullet->pos.y + TEXTURE_EBULLET_SIZE_Y;
	ebullet->vertexWk[3].vtx.z = 0.0f;
}

////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureEBullet(int no,int cntPattern)
//{
//	EBULLET *ebullet = &EbulletWk[no];			// �o���b�g�̃|�C���^�[��������
//
//
//	// �e�N�X�`�����W�̐ݒ�
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET;
//
//	ebullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	ebullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	ebullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	ebullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//
//
//}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEBullet(D3DXVECTOR3 pos)
{
		EBULLET *ebullet = GetEBullet(0);			// �o���b�g�̃|�C���^�[��������
		PLAYER*player = GetPlayer(0);

		float	SPEED = 0;

			// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
			for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
			{
				if (GetEBullet(i)->use == false)			// ���g�p��Ԃ̃o���b�g��������
				{
					GetEBullet(i)->use = true;			// �g�p��Ԃ֕ύX����
					GetEBullet(i)->pos = pos;				// ���W���Z�b�g


					GetEBullet(i)->dis = player->pos - pos;
					bool ZetFlag = false;

					if (GetEBullet(i)->dis.y < 0)
					{
						GetEBullet(i)->dis.y *= (-1);
						ZetFlag = true;
					}

					if (GetEBullet(i)->dis.x < GetEBullet(i)->dis.y)
					{
						SPEED = GetEBullet(i)->dis.y / EBULLET_SPEED;
					}
					else
					{
						SPEED = GetEBullet(i)->dis.x / EBULLET_SPEED;
					}
					if (ZetFlag == true)
					{
						GetEBullet(i)->dis.y *= (-1);
						ZetFlag = false;
					}

					GetEBullet(i)->SPPED_Y = GetEBullet(i)->dis.y / SPEED;
					GetEBullet(i)->SPPED_X = GetEBullet(i)->dis.x / SPEED;





					ebullet->pos.x -= (TEXTURE_BOSS_SIZE_X / 2) + (TEXTURE_EBULLET_SIZE_X / 2);

					// ���ˉ��Đ�
					//PlaySound(g_p1SE, E_DS8_FLAG_NONE);

					return;							// 1���Z�b�g�����̂ŏI������
				}
			}
}
//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
EBULLET *GetEBullet(int no)
{
	return(&EbulletWk[no]);
}

