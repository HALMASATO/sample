//=============================================================================
//
// �w�i���� [bg.h]
// Author : 
//
//=============================================================================
#ifndef _SelBG_H_
#define _SelBG_H_

// �}�N����`
#define TEXTURE_GAME_SelBG00		_T("data/TEXTURE/yakei2.png")	// �T���v���p�摜
//#define TEXTURE_GAME_SelBG01_tuki		_T("data/TEXTURE/tuki.png")	// �T���v���p�摜
//#define TEXTURE_GAME_SelBG02_heart		_T("data/TEXTURE/heart.png")	// �T���v���p�摜

#define SelBG00_SIZE_X			(1000)							// �e�N�X�`���T�C�Y
#define SelBG00_SIZE_Y			(500)							// ����
#define SelBG00_POS_X			(0)								// �|���S���̏����ʒuX(����)
#define SelBG00_POS_Y			(0)								// ����

#define	SelBG01_POS_X			(400)							// �^�C�g�����S�̕\���ʒu
#define	SelBG01_POS_Y			(-50)							// �^�C�g�����S�̕\���ʒu
#define	SelBG01_SIZE_X			(350)							// �^�C�g�����S�̕�
#define	SelBG01_SIZE_Y			(310)							// �^�C�g�����S�̍���

//#define	SelBG02_POS_X			(30)							// �^�C�g�����S�̕\���ʒu
//#define	SelBG02_POS_Y			(430)							// �^�C�g�����S�̕\���ʒu
//#define	SelBG02_SIZE_X			(50)							// �^�C�g�����S�̕�
//#define	SelBG02_SIZE_Y			(50)							// �^�C�g�����S�̍���
//

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSelBG(int type);
void UninitSelBG(void);
void UpdateSelBG(void);
void DrawSelBG(void);
//SelBG *GetSelBG(int no);

#endif
