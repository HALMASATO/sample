//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _PGAGE_H_
#define _PGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PGAGE		_T("data/TEXTURE/gezi1.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_PGAGE_LOGO	_T("data/TEXTURE/start.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PGAGE_POS_X			(30)								// �^�C�g���̕\���ʒu
#define	PGAGE_POS_Y			(30)								// �^�C�g���̕\���ʒu
#define	PGAGE_SIZE_X		(120)							// �^�C�g���̕�
#define	PGAGE_SIZE_Y		(16)							// �^�C�g���̍���
//#define	PGAGELOGO_POS_X		(160)							// �^�C�g�����S�̕\���ʒu
//#define	PGAGELOGO_POS_Y		(300)							// �^�C�g�����S�̕\���ʒu
//#define	PGAGELOGO_SIZE_X	(380)							// �^�C�g�����S�̕�
//#define	PGAGELOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���
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
HRESULT InitPgage(void);
void UninitPgage(void);
void UpdatePgage(void);
void DrawPgage(void);
//LOGO*GetPgage(int no);

#endif
