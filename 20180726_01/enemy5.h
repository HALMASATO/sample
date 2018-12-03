//=============================================================================
//
// �G���� [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY5_H_
#define _ENEMY5_H_


// �}�N����`
#define	NUM_ENEMY5				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY5		_T("data/TEXTURE/tama.png")	// �摜
#define TEXTURE_ENEMY5_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY5_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY5	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY5	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY5			(TEXTURE_PATTERN_DIVIDE_X_ENEMY5*TEXTURE_PATTERN_DIVIDE_Y_ENEMY5)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY5			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY5_MAX						(6) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			deadflag;					//true:���S�@false:����
	bool			BBflag;						//�o���b�g�Ɠ���������true
	bool			comeback;					//�ēo���flag
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				counter;
	int				Mcounter;					//�����Ă���Ƃ��̃J�E���g
	//float			InitY;						//����Y�l
	int				i;
	int             pattern;
	int				Bcounter;
	int				Bcounter_ORG;
	int				flag;
	bool			effectflag;

	

	float			enemy5pos_x;
	float			enemy5pos_y;
	//int				ENM = ENEMY5_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy5[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY5;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy5(int type);
void UninitEnemy5(void);
void UpdateEnemy5(void);
void DrawEnemy5(void);
ENEMY5 *GetEnemy5(int no);



#endif
