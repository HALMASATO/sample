//=============================================================================
//
// �v���C���[���� [player.h]
// Author : 
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_


// �}�N����`
#define	NUM_TARGET		(2)					// �|���S����

#define TEXTURE_GAME_TARGET	_T("data/TEXTURE/target.png")	// �摜
#define TEXTURE_TARGET_SIZE_X	(100/2) // �e�N�X�`���T�C�Y
#define TEXTURE_TARGET_SIZE_Y	(100/2) // ����

#define TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TARGET_MAX					(1) // �v���C���[�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		pos1;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				enemy_x;
	int				enemy_y;
	int				HP;
	int				Timecounter;
	int				Hitcounter;
	int				drawcounter;
	bool			rockflug;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} TARGET;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTarget(int type);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
TARGET *GetTarget(int no);


#endif
