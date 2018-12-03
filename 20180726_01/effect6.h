//=============================================================================
//
// �G���� [effect4.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT6_H_
#define _EFFECT6_H_


// �}�N����`
#define	NUM_EFFECT6				(2)			// �|���S����

#define TEXTURE_GAME_EFFECT6		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_EFFECT6_SIZE_X	(25)		// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT6_SIZE_Y	(25)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_EFFECT6	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT6	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_EFFECT6			(TEXTURE_PATTERN_DIVIDE_X_EFFECT6*TEXTURE_PATTERN_DIVIDE_Y_EFFECT6)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT6			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT6_MAX						(1) // �G�̍ő吔





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
	int				effectcounter;				//�G�t�F�N�g�Ǘ�
	


	float			effect4pos_x;
	float			effect4pos_y;
	//int				ENM = EFFECT6_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_effect[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} EFFECT6;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect6(int type);
void UninitEffect6(void);
void UpdateEffect6(void);
void DrawEffect6(void);
EFFECT6 *GetEffect6(int no);
void SetEffect6(D3DXVECTOR3 pos, int i);



#endif
