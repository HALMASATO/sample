//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _BGAGE_H_
#define _BGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BGAGE		_T("data/TEXTURE/rifle.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BGAGE_POS_X			(40)								// �^�C�g���̕\���ʒu
#define	BGAGE_POS_Y			(400)								// �^�C�g���̕\���ʒu
#define	BGAGE_SIZE_X		(100)								// �^�C�g���̕�
#define	BGAGE_SIZE_Y		(50)								// �^�C�g���̍���
#define BGAGE_MAX			(1)

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p

} BGAGE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBgage(void);
void UninitBgage(void);
void UpdateBgage(void);
void DrawBgage(void);
//LOGO*GetBgage(int no);

#endif
