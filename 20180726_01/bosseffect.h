//=============================================================================
//
// �G���� [bosseffect.h]
// Author : 
//
//=============================================================================
#ifndef _BOSSEFFECT_H_
#define _BOSSEFFECT_H_


// �}�N����`
#define	NUM_BOSSEFFECT				(2)			// �|���S����

#define TEXTURE_GAME_BOSSEFFECT		_T("data/TEXTURE/bomb2.png")	// �摜
#define TEXTURE_BOSSEFFECT_SIZE_X	(100)		// �e�N�X�`���T�C�Y
#define TEXTURE_BOSSEFFECT_SIZE_Y	(100)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BOSSEFFECT			(TEXTURE_PATTERN_DIVIDE_X_BOSSEFFECT*TEXTURE_PATTERN_DIVIDE_Y_BOSSEFFECT)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BOSSEFFECT			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define BOSSEFFECT_MAX						(1) // �G�̍ő吔





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
	int				bosseffectcounter;				//�G�t�F�N�g�Ǘ�
	


	float			bosseffectpos_x;
	float			bosseffectpos_y;
	//int				ENM = BOSSEFFECT_MAX;
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk_bosseffect[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} BOSSEFFECT;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBossEffect(int type);
void UninitBossEffect(void);
void UpdateBossEffect(void);
void DrawBossEffect(void);
BOSSEFFECT *GetBossEffect(int no);
void SetBossEffect(D3DXVECTOR3 pos, int i);



#endif
