//=============================================================================
//
// �G���� [enemy6.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY6_H_
#define _ENEMY6_H_


// �}�N����`
#define	NUM_ENEMY6				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY6		_T("data/TEXTURE/enemy_green.png")	// �摜
#define TEXTURE_ENEMY6_SIZE_X	(40)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY6_SIZE_Y	(40)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY6	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY6	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY6			(TEXTURE_PATTERN_DIVIDE_X_ENEMY6*TEXTURE_PATTERN_DIVIDE_Y_ENEMY6)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY6			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY6_MAX						(3) // �G�̍ő吔





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
	//float			InitY;						//����Y�l
	int				i;
	int             pattern;
	int				Bcounter;
	int				Bcounter_ORG;
	int				flag;
	bool			effectflag;

	

	float			enemy6pos_x;
	float			enemy6pos_y;
	//int				ENM = ENEMY6_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy6[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY6;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy6(int type);
void UninitEnemy6(void);
void UpdateEnemy6(void);
void DrawEnemy6(void);
ENEMY6 *GetEnemy6(int no);



#endif
