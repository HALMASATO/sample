//=============================================================================
//
// �G���� [effect2.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT2_H_
#define _EFFECT2_H_


// �}�N����`
#define	NUM_EFFECT2				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT2		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_EFFECT2_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT2_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT2	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT2	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT2			(TEXTURE_PATTERN_DIVIDE_X_EFFECT2*TEXTURE_PATTERN_DIVIDE_Y_EFFECT2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT2			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT2_MAX						(1) // �G�̍ő吔





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
	float			InitY=500.0f;				//����Y�l
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effect2counter;				//�G�t�F�N�g�Ǘ�
	


	float			effect2pos_x;
	float			effect2pos_y;
	//int				ENM = EFFECT2_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_effect2[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} EFFECT2;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect2(int type);
void UninitEffect2(void);
void UpdateEffect2(void);
void DrawEffect2(void);
EFFECT2 *GetEffect2(int no);
void SetEffect2(D3DXVECTOR3 pos, int i);



#endif
