//=============================================================================
//
// �w�i���� [bg.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// �}�N����`
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/yakei2.png")	// �T���v���p�摜
//#define TEXTURE_GAME_BG01_tuki		_T("data/TEXTURE/tuki.png")	// �T���v���p�摜
//#define TEXTURE_GAME_BG02_heart		_T("data/TEXTURE/heart.png")	// �T���v���p�摜

#define BG00_SIZE_X			(1000)							// �e�N�X�`���T�C�Y
#define BG00_SIZE_Y			(500)							// ����
#define BG00_POS_X			(0)								// �|���S���̏����ʒuX(����)
#define BG00_POS_Y			(0)								// ����

#define	BG01_POS_X			(400)							// �^�C�g�����S�̕\���ʒu
#define	BG01_POS_Y			(-50)							// �^�C�g�����S�̕\���ʒu
#define	BG01_SIZE_X			(350)							// �^�C�g�����S�̕�
#define	BG01_SIZE_Y			(310)							// �^�C�g�����S�̍���

//#define	BG02_POS_X			(30)							// �^�C�g�����S�̕\���ʒu
//#define	BG02_POS_Y			(430)							// �^�C�g�����S�̕\���ʒu
//#define	BG02_SIZE_X			(50)							// �^�C�g�����S�̕�
//#define	BG02_SIZE_Y			(50)							// �^�C�g�����S�̍���
//

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
//BG *GetBG(int no);

#endif
