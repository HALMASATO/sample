//=============================================================================
//
// �G���� [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// �}�N����`
#define	NUM_ENEMY				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY		_T("data/TEXTURE/tama.png")	// �摜
#define TEXTURE_ENEMY_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY			(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY_MAX						(6) // �G�̍ő吔





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

	

	float			enemypos_x;
	float			enemypos_y;
	//int				ENM = ENEMY_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int no);



#endif
