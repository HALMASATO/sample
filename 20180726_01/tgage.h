//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _TGAGE_H_
#define _TGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TGAGE		_T("data/TEXTURE/runa.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TGAGE_POS_X			(550)								// �^�C�g���̕\���ʒu
#define	TGAGE_POS_Y			(-60)								// �^�C�g���̕\���ʒu
#define	TGAGE_SIZE_X		(200)							// �^�C�g���̕�
#define	TGAGE_SIZE_Y		(200)							// �^�C�g���̍���
#define TGAGE_MAX			(1)

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p

} TGAGE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTgage(void);
void UninitTgage(void);
void UpdateTgage(void);
void DrawTgage(void);
TGAGE *GetTgage(int no);
#endif