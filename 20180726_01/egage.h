//=============================================================================
//
// �^�C�g����ʏ��� [egage.h]
// Author : 
//
//=============================================================================
#ifndef _EGAGE_H_
#define _EGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EGAGE		_T("data/TEXTURE/gazi2.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_EGAGE_LOGO	_T("data/TEXTURE/start.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	EGAGE_POS_X			(430)								// �^�C�g���̕\���ʒu
#define	EGAGE_POS_Y			(30)								// �^�C�g���̕\���ʒu
#define	EGAGE_SIZE_X		(120)							// �^�C�g���̕�
#define	EGAGE_SIZE_Y		(16)							// �^�C�g���̍���
//#define	EGAGELOGO_POS_X		(160)							// �^�C�g�����S�̕\���ʒu
//#define	EGAGELOGO_POS_Y		(300)							// �^�C�g�����S�̕\���ʒu
//#define	EGAGELOGO_SIZE_X	(380)							// �^�C�g�����S�̕�
//#define	EGAGELOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���
//#define	LOGO_MAX			(1)
//

//typedef struct	// �G�l�~�[�\����
//{
//	bool			use;						// true:�g�p  false:���g�p
//	int				logo_counter;
//
//} LOGO;
//

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEgage(void);
void UninitEgage(void);
void UpdateEgage(void);
void DrawEgage(void);
//LOGO*GetEgage(int no);

#endif
