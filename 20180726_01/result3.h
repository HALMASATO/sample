//=============================================================================
//
//// ���U���g��ʏ��� [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT3_H_
#define _RESULT3_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT3		_T("data/TEXTURE/over.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_RESULT3_LOGO	_T("data/TEXTURE/result_logo.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT3_POS_X			(0)							// �^�C�g���̕\���ʒu
#define	RESULT3_POS_Y			(0)							// �^�C�g���̕\���ʒu
#define	RESULT3_SIZE_X			(800)						// �^�C�g���̕�
#define	RESULT3_SIZE_Y			(450)						// �^�C�g���̍���
#define	RESULT3LOGO_POS_X		(160)						// �^�C�g�����S�̕\���ʒu
#define	RESULT3LOGO_POS_Y		(200)						// �^�C�g�����S�̕\���ʒu
#define	RESULT3LOGO_SIZE_X		(480)						// �^�C�g�����S�̕�
#define	RESULT3LOGO_SIZE_Y		(80)						// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult3(void);
void UninitResult3(void);
void UpdateResult3(void);
void DrawResult3(void);

#endif
