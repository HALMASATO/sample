//=============================================================================
//
// �v���C���[���� [player2.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_


// �}�N����`
#define	NUM_PLAYER2		(2)					// �|���S����

#define TEXTURE_GAME_PLAYER2	_T("data/TEXTURE/player2.png")	// �摜
#define TEXTURE_PLAYER2_SIZE_X	(40) // �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER2_SIZE_Y	(40) // ����

#define TEXTURE_PATTERN_DIVIDE_X_PLAYER2	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYER2	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PLAYER2			(TEXTURE_PATTERN_DIVIDE_X_PLAYER2*TEXTURE_PATTERN_DIVIDE_Y_PLAYER2)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER2_MAX					(1) // �v���C���[�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				counter;
	int				HP;
	int				Bcounter;
	int				MAXHP;
	int				MAXcounter;					//
	int				MAXBcounter;
	int				Timecounter;
	int				Hitcounter;
	int				drawcounter;
	bool			drawflug;


	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} PLAYER2;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer2(int type);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
PLAYER2 *GetPlayer2(int no);


#endif
