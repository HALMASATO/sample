//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/title1.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/start.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(450)							// �^�C�g���̍���
#define	TITLELOGO_POS_X		(160)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(300)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(380)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���
#define	LOGO_MAX			(1)
////

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	int				logo_counter;

} LOGO;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
LOGO*GetLogo(int no);

#endif
