//=============================================================================
//
// �G���� [enemy3.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY3_H_
#define _ENEMY3_H_


// �}�N����`
#define	NUM_ENEMY3				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY3		_T("data/TEXTURE/tama1.png")	// �摜
#define TEXTURE_ENEMY3_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY3_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY3	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY3	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY3			(TEXTURE_PATTERN_DIVIDE_X_ENEMY3*TEXTURE_PATTERN_DIVIDE_Y_ENEMY3)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY3			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY3_MAX						(6) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			deadflag;					//true:���S�@false:����
	bool			BBflag;
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			InitY=500.0f;				//����Y�l
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	bool			effectflag3;

	

	float			enemy3pos_x;
	float			enemy3pos_y;
	//int				ENM = ENEMY3_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy3[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY3;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy3(int type);
void UninitEnemy3(void);
void UpdateEnemy3(void);
void DrawEnemy3(void);
ENEMY3 *GetEnemy3(int no);



#endif
