//=============================================================================
//
// �G���� [BOSS2.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS2_H_
#define _BOSS2_H_


// �}�N����`
#define	NUM_BOSS2				(2)			// �|���S����

#define TEXTURE_GAME_BOSS2		_T("data/TEXTURE/boss3.png")	// �摜
#define TEXTURE_BOSS2_SIZE_X	(200)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSS2_SIZE_Y	(200)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSS2	(6)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSS2			(TEXTURE_PATTERN_DIVIDE_X_BOSS2*TEXTURE_PATTERN_DIVIDE_Y_BOSS2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSS2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSS2_MAX						(1) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			effectflag;
	bool			drawflug;
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				i;
	int				counter;
	int				Bcounter;
	int				Bcounter_ORG;
	int				Hitcounter;
	int				Timecounter;
	int				Popcounter;
	int				HP;
	int				MAXHP;


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_boss2[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} BOSS2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss2(int type);
void UninitBoss2(void);
void UpdateBoss2(void);
void DrawBoss2(void);
BOSS2 *GetBoss2(int no);


#endif
