//=============================================================================
//
// �w�i���� [captionbg.h]
// Author : 
//
//=============================================================================
#ifndef _CAPTIONBG_H_
#define _CAPTIONBG_H_

// �}�N����`
#define TEXTURE_GAME_CAPTIONBG00		_T("data/TEXTURE/ps4kon_ver1.jpg")	// �T���v���p�摜
//#define TEXTURE_GAME_CAPTIONBG01_tuki		_T("data/TEXTURE/tuki.png")	// �T���v���p�摜
//#define TEXTURE_GAME_CAPTIONBG02_heart		_T("data/TEXTURE/heart.png")	// �T���v���p�摜

#define CAPTIONBG00_SIZE_X			(800)							// �e�N�X�`���T�C�Y
#define CAPTIONBG00_SIZE_Y			(450)							// ����
#define CAPTIONBG00_POS_X			(0)								// �|���S���̏����ʒuX(����)
#define CAPTIONBG00_POS_Y			(0)								// ����

//#define	CAPTIONBG01_POS_X			(400)							// �^�C�g�����S�̕\���ʒu
//#define	CAPTIONBG01_POS_Y			(-50)							// �^�C�g�����S�̕\���ʒu
//#define	CAPTIONBG01_SIZE_X			(350)							// �^�C�g�����S�̕�
//#define	CAPTIONBG01_SIZE_Y			(310)							// �^�C�g�����S�̍���
//
//#define	CAPTIONBG02_POS_X			(30)							// �^�C�g�����S�̕\���ʒu
//#define	CAPTIONBG02_POS_Y			(430)							// �^�C�g�����S�̕\���ʒu
//#define	CAPTIONBG02_SIZE_X			(50)							// �^�C�g�����S�̕�
//#define	CAPTIONBG02_SIZE_Y			(50)							// �^�C�g�����S�̍���
//

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCaptionBG(int type);
void UninitCaptionBG(void);
void UpdateCaptionBG(void);
void DrawCaptionBG(void);
//CAPTIONBG *GetCAPTIONBG(int no);

#endif
