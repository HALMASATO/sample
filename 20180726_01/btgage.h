//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _BTGAGE_H_
#define _BTGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BTGAGE		_T("data/TEXTURE/runa.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BTGAGE_POS_X			(550)								// �^�C�g���̕\���ʒu
#define	BTGAGE_POS_Y			(-60)								// �^�C�g���̕\���ʒu
#define	BTGAGE_SIZE_X		(200)							// �^�C�g���̕�
#define	BTGAGE_SIZE_Y		(200)							// �^�C�g���̍���
#define BTGAGE_MAX			(1)

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p

} BTGAGE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBTgage(void);
void UninitBTgage(void);
void UpdateBTgage(void);
void DrawBTgage(void);
BTGAGE *GetBTgage(int no);
#endif