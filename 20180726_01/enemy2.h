//=============================================================================
//
// �G���� [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_


// �}�N����`
#define	NUM_ENEMY2				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY2		_T("data/TEXTURE/tama1.png")	// �摜
#define TEXTURE_ENEMY2_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY2_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY2	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY2			(TEXTURE_PATTERN_DIVIDE_X_ENEMY2*TEXTURE_PATTERN_DIVIDE_Y_ENEMY2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY2_MAX						(6) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			effectflag2;
	bool			BBflag;
	bool			comeback;
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				i;
	int				counter;					//���Ԃ𐧌䂷��ϐ�
	float			enemy2pos_x;
	float			enemy2pos_y;
	

	LPDIRECT3DTEXTURE9	Texture_enemy;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy2(int type);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
ENEMY2 *GetEnemy2(int no);


#endif
