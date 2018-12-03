//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET2_H_
#define _BULLET2_H_


// �}�N����`
#define	NUM_BULLET2				(2)			// �|���S����

#define TEXTURE_GAME_BULLET2		_T("data/TEXTURE/rifle.png")	// �摜
#define TEXTURE_BULLET2_SIZE_X	(50/4)		// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET2_SIZE_Y	(50/8)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLET2			(TEXTURE_PATTERN_DIVIDE_X_BULLET2*TEXTURE_PATTERN_DIVIDE_Y_BULLET2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLET2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET2_MAX						(3) // �o���b�g�̍ő吔

#define BULLET2_SPEED			(-6.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			BBflag;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				BM =0;						//bullet�̒e�����Ă����ϐ�
	int				reload=0;
	int				counter = 0;				//�e��ł��Ă���̕b���𐔂���
	int				HP;
	float			posx1;
	float			posx2;
	float			posy1;
	float			posy2;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x


} BULLET2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet2(int type);
void UninitBullet2(void);
void UpdateBullet2(void);
void DrawBullet2(void);
void SetBullet2(D3DXVECTOR3 pos);
BULLET2 *GetBullet2(int no);


#endif
