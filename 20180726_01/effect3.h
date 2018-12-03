//=============================================================================
//
// �G���� [effect3.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT3_H_
#define _EFFECT3_H_


// �}�N����`
#define	NUM_EFFECT3				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT3		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_EFFECT3_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT3_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT3	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT3	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT3			(TEXTURE_PATTERN_DIVIDE_X_EFFECT3*TEXTURE_PATTERN_DIVIDE_Y_EFFECT3)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT3			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT3_MAX						(1) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	//bool			effectflag2;
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			InitY=700.0f;				//����Y�l
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effect3counter;				//�G�t�F�N�g�Ǘ�
	


	float			effect3pos_x;
	float			effect3pos_y;
	//int				ENM = EFFECT3_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_effect3[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} EFFECT3;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect3(int type);
void UninitEffect3(void);
void UpdateEffect3(void);
void DrawEffect3(void);
EFFECT3 *GetEffect3(int no);
void SetEffect3(D3DXVECTOR3 pos, int i);



#endif
