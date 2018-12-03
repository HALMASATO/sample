//=============================================================================
//
// �G���� [enemy4.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY4_H_
#define _ENEMY4_H_


// �}�N����`
#define	NUM_ENEMY4				(2)			// �|���S����

#define TEXTURE_GAME_ENEMY4		_T("data/TEXTURE/tama1.png")	// �摜
#define TEXTURE_ENEMY4_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY4_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY4	(9)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY4	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY4			(TEXTURE_PATTERN_DIVIDE_X_ENEMY4*TEXTURE_PATTERN_DIVIDE_Y_ENEMY4)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY4			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY4_MAX						(6) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			nextflag;					//true:���S�@false:����
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
	bool			effectflag4;

	

	float			enemy4pos_x;
	float			enemy4pos_y;
	//int				ENM = ENEMY4_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_enemy4[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ENEMY4;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy4(int type);
void UninitEnemy4(void);
void UpdateEnemy4(void);
void DrawEnemy4(void);
ENEMY4 *GetEnemy4(int no);



#endif
