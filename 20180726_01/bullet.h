//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// �}�N����`
#define	NUM_BULLET				(2)			// �|���S����

#define TEXTURE_GAME_BULLET		_T("data/TEXTURE/redtama.png")	// �摜
#define TEXTURE_BULLET_SIZE_X	(50/4)		// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(50/8)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET_MAX						(8) // �o���b�g�̍ő吔

#define BULLET_SPEED			(6.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			BBflag;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		dis;

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				BM;						//bullet�̒e�����Ă����ϐ�
	int				reload;
	int				counter;				//�e��ł��Ă���̕b���𐔂���
	int				MAXreload;				//
	float			SPPED_Y;
	float			SPPED_X;
	float			zet;						//��Βl


	float			posx1;
	float			posx2;
	float			posy1;
	float			posy2;


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x


} BULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
BULLET *GetBullet(int no);


#endif
