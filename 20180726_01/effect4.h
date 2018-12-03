//=============================================================================
//
// �G���� [effect4.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT4_H_
#define _EFFECT4_H_


// �}�N����`
#define	NUM_EFFECT4				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT4		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_EFFECT4_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT4_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT4	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT4	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT4			(TEXTURE_PATTERN_DIVIDE_X_EFFECT4*TEXTURE_PATTERN_DIVIDE_Y_EFFECT4)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT4			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT4_MAX						(1) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			nextflag;					//
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			InitY=700.0f;				//����Y�l
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effect4counter;				//�G�t�F�N�g�Ǘ�
	


	float			effect4pos_x;
	float			effect4pos_y;
	//int				ENM = EFFECT4_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_effect4[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} EFFECT4;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect4(int type);
void UninitEffect4(void);
void UpdateEffect4(void);
void DrawEffect4(void);
EFFECT4 *GetEffect4(int no);
void SetEffect4(D3DXVECTOR3 pos, int i);



#endif
