//=============================================================================
//
// �G���� [effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


// �}�N����`
#define	NUM_EFFECT				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_EFFECT_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT_MAX						(1) // �G�̍ő吔





//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			InitY=500.0f;				//����Y�l
	int				i;
	int             pattern=0;
	int				counter = 0;
	int				flag = 0;
	int				effectcounter;				//�G�t�F�N�g�Ǘ�
	


	float			effectpos_x;
	float			effectpos_y;
	//int				ENM = EFFECT_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_effect[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} EFFECT;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(int no);
void SetEffect(D3DXVECTOR3 pos, int i);



#endif
