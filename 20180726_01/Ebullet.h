//=============================================================================
//
// �o���b�g���� [Ebullet.h]
// Author : 
//
//=============================================================================
#ifndef _EBULLET_H_
#define _EBULLET_H_


// �}�N����`
#define	NUM_EBULLET				(2)			// �|���S����

#define TEXTURE_GAME_EBULLET		_T("data/TEXTURE/tama.png")	// �摜
#define TEXTURE_EBULLET_SIZE_X	(50/4)		// �e�N�X�`���T�C�Y
#define TEXTURE_EBULLET_SIZE_Y	(50/8)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EBULLET	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EBULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EBULLET			(TEXTURE_PATTERN_DIVIDE_X_EBULLET*TEXTURE_PATTERN_DIVIDE_Y_EBULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EBULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define EBULLET_MAX						(4) // �o���b�g�̍ő吔

#define EBULLET_SPEED			(-1.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		dis;

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				counter;					//�o���b�g�̐���
	int				Bcounter_ORG;				//
	float			SPPED_Y;
	float			SPPED_X;

	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} EBULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEBullet(int type);
void UninitEBullet(void);
void UpdateEBullet(void);
void DrawEBullet(void);
void SetEBullet(D3DXVECTOR3 pos);
EBULLET *GetEBullet(int no);


#endif
