
//=============================================================================
//
// �o���b�g���� [bullet2.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bullet2.h"
#include "target.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet2( int no );
void SetTextureBullet2( int no, int cntPattern );
void SetVertexBullet2( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet2 = NULL;		// �e�N�X�`���ւ̃|���S��

BULLET2					bullet2Wk[BULLET2_MAX];			// �o���b�g�\����

//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet2(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = &bullet2Wk[0];		// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BULLET2,			// �t�@�C���̖��O
			&g_pD3DTextureBullet2);			// �ǂݍ��ރ������̃|�C���^
		
		//g_pSE = LoadSound(SE_00);

	}


	// �o���b�g�̏���������
	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		bullet2->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bullet2->BBflag = false;									//�^�[�Q�b�g�ɓ������true
		bullet2->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bullet2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bullet2->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bullet2->CountAnim = 0;									// �A�j���J�E���g��������
		bullet2->HP = 2;


		bullet2->Texture = g_pD3DTextureBullet2;					// �e�N�X�`�����
		MakeVertexBullet2(i);									// ���_���̍쐬
		bullet2->BaseAngle = atan2f(TEXTURE_BULLET2_SIZE_Y, TEXTURE_BULLET2_SIZE_X);	// �G�l�~�[�̊p�x��������

	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet2(void)
{
	if (g_pD3DTextureBullet2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBullet2->Release();
		g_pD3DTextureBullet2 = NULL;
	}

	//if (g_pSE != NULL)
	//{	// �e�N�X�`���̊J��
	//	g_pSE->Release();
	//	g_pSE = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet2(void)
{
	BULLET2 *bullet2 = bullet2Wk;				// �o���b�g�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	TARGET*target = GetTarget(0);
	PLAYER*player = GetPlayer(0);

	float i = 0;

	
	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		if (bullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

				bullet2->pos.x += 3;

			// ��ʊO�܂Ői�񂾁H
			if (GetBullet2(i)->pos.x > SCREEN_WIDTH -TEXTURE_BULLET2_SIZE_X)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bullet2->use = false;
				bullet2->pos.x = -100.0f;
			}

			SetVertexBullet2(i);				// �ړ���̍��W�Œ��_��ݒ�
		}

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = bullet2Wk;				// �o���b�g�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
	{
		if (bullet2->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bullet2->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET2, bullet2->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet2( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET2 *bullet2 = &bullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexBullet2( no );

	// rhw�̐ݒ�
	bullet2->vertexWk[0].rhw =
	bullet2->vertexWk[1].rhw =
	bullet2->vertexWk[2].rhw =
	bullet2->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bullet2->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet2->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET2, 0.0f);
	bullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET2);
	bullet2->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BULLET2, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET2);

	//bullet2->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet2->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet2( int no, int cntPattern )
{
	BULLET2 *bullet2 = &bullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET2;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET2;
	
	bullet2->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet2->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet2->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet2->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet2( int no )
{
	BULLET2 *bullet2 = &bullet2Wk[no];			// �o���b�g�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	bullet2->vertexWk[0].vtx.x = bullet2->pos.x - TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[0].vtx.y = bullet2->pos.y - TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[0].vtx.z = 0.0f;

	bullet2->vertexWk[1].vtx.x = bullet2->pos.x + TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[1].vtx.y = bullet2->pos.y - TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[1].vtx.z = 0.0f;

	bullet2->vertexWk[2].vtx.x = bullet2->pos.x - TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[2].vtx.y = bullet2->pos.y + TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[2].vtx.z = 0.0f;

	bullet2->vertexWk[3].vtx.x = bullet2->pos.x + TEXTURE_BULLET2_SIZE_X;
	bullet2->vertexWk[3].vtx.y = bullet2->pos.y + TEXTURE_BULLET2_SIZE_Y;
	bullet2->vertexWk[3].vtx.z = 0.0f;


		// ���_���W�̐ݒ�
	//bullet2->vertexWk[0].vtx.x = bullet2->pos.x - cosf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[0].vtx.y = bullet2->pos.y - sinf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[0].vtx.z = 0.0f;

	//bullet2->vertexWk[1].vtx.x = bullet2->pos.x + cosf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[1].vtx.y = bullet2->pos.y - sinf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[1].vtx.z = 0.0f;

	//bullet2->vertexWk[2].vtx.x = bullet2->pos.x - cosf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[2].vtx.y = bullet2->pos.y + sinf(bullet2->BaseAngle - bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[2].vtx.z = 0.0f;

	//bullet2->vertexWk[3].vtx.x = bullet2->pos.x + cosf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[3].vtx.y = bullet2->pos.y + sinf(bullet2->BaseAngle + bullet2->rot.z) * bullet2->Radius;
	//bullet2->vertexWk[3].vtx.z = 0.0f;



}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet2(D3DXVECTOR3 pos)
{
		BULLET2 *bullet2 = &bullet2Wk[0];			// �o���b�g�̃|�C���^�[��������

			// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
			for (int i = 0; i < BULLET2_MAX; i++, bullet2++)
			{
				if (bullet2->use == false)			// ���g�p��Ԃ̃o���b�g��������
				{
					bullet2->use = true;				// �g�p��Ԃ֕ύX����
					bullet2->pos = pos;				// ���W���Z�b�g

					// ���ˉ��Đ�
					//PlaySound(g_pSE, E_DS8_FLAG_NONE);

					return;							// 1���Z�b�g�����̂ŏI������
				}
			}
}



//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BULLET2 *GetBullet2(int no)
{
	return(&bullet2Wk[no]);
}

