//=============================================================================
//
// �o���b�g���� [Ebullet2.h]
// Author : 
//
//=============================================================================
#ifndef _EBULLET2_H_
#define _EBULLET2_H_


// �}�N����`
#define	NUM_EBULLET2				(2)			// �|���S����

#define TEXTURE_GAME_EBULLET2		_T("data/TEXTURE/purple.png")	// �摜
#define TEXTURE_EBULLET2_SIZE_X	(50/4)		// �e�N�X�`���T�C�Y
#define TEXTURE_EBULLET2_SIZE_Y	(50/8)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EBULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EBULLET2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EBULLET2			(TEXTURE_PATTERN_DIVIDE_X_EBULLET2*TEXTURE_PATTERN_DIVIDE_Y_EBULLET2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EBULLET2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define EBULLET2_MAX						(6) // �o���b�g�̍ő吔

#define EBULLET2_SPEED			(-1.0f)		// �o���b�g�̈ړ��X�s�[�h


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

} EBULLET2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEBullet2(int type);
void UninitEBullet2(void);
void UpdateEBullet2(void);
void DrawEBullet2(void);
void SetEBullet2(D3DXVECTOR3 pos);
EBULLET2 *GetEBullet2(int no);


#endif
