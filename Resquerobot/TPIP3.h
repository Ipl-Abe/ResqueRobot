/**
* @file TPIP3.h
* @brief TPIP3�p���C�u����
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
* @version 1.01 2013/03/21 katayama
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* ���̃t�@�C���̒��쌠�́ATPIP���[�U�[�R�~���j�e�B�̋K��ɏ]���g�p���������܂��B
*/


#ifndef __TPIP3_H__
#define __TPIP3_H__

#define QVGA       (0)       //!< @brief QVGA�𑜓x
#define VGA        (1)       //!< @brief VGA�𑜓x

#define PWM_MAX    ( 1000)   //!< @brief PWM�ւ̏o�͍ő�l
#define PWM_MIN    (-1000)   //!< @brief PWM�ւ̏o�͍ŏ��l

#define AI_MAX     (0xFFFF)  //!< @brief �A�i���O���͂̍ő�l
#define AI_MIN     (0x00)    //!< @brief �A�i���O���͂̍ŏ��l

#define PI_MAX     (0xFFFF)  //!< @brief �p���X���͂̍ő�l
#define PI_MIN     (0x00)    //!< @brief �p���X���͂̍ŏ��l

#define AI_CH      (8)      //!< @brief �A�i���O���͂̃`�����l����
#define PI_CH      (4)       //!< @brief �p���X���͂̃`�����l����
#define DI_CH      (4)       //!< @brief �f�W�^���o�͂̃`�����l����
#define DO_CH      (4)       //!< @brief �f�W�^�����͂̃`�����l����
#define PWM_CH     (4)      //!< @brief PWM�o�͂̃`�����l����

#define AXIS_MAX   (32767)   //!< @brief �Q�[���R���g���[���̃A�i���O�p�b�h�̍ő�l
#define AXIS_MIN   (-32768)  //!< @brief �Q�[���R���g���[���̃A�i���O�p�b�h�̍ŏ��l

#define BTN_RU     (0x001)   //!< @brief �Q�[���R���g���[���̉E�A��̒l
#define BTN_RR     (0x002)   //!< @brief �Q�[���R���g���[���̉E�A�E�̒l
#define BTN_RD     (0x004)   //!< @brief �Q�[���R���g���[���̉E�A���̒l
#define BTN_RL     (0x008)   //!< @brief �Q�[���R���g���[���̉E�A���̒l
#define BTN_L2     (0x010)   //!< @brief �Q�[���R���g���[����L2�̒l
#define BTN_R2     (0x020)   //!< @brief �Q�[���R���g���[����R2�̒l
#define BTN_L1     (0x040)   //!< @brief �Q�[���R���g���[����L1�̒l
#define BTN_R1     (0x080)   //!< @brief �Q�[���R���g���[����R1�̒l
#define BTN_ST     (0x100)   //!< @brief �Q�[���R���g���[����START�̒l
#define BTN_SE     (0x200)   //!< @brief �Q�[���R���g���[����SELECT�̒l
#define BTN_L3     (0x400)   //!< @brief �Q�[���R���g���[����L3�̒l
#define BTN_R3     (0x800)   //!< @brief �Q�[���R���g���[����R3�̒l

#define TPJT_COM_JPEG (0x01) //!< @brief �ʐM���[�h(JPEG)
#define TPJT_COM_CTRL (0x02) //!< @brief �ʐM���[�h(����)

#include "../tpip3/include/TPGC_11dll.h"      // �Q�[���p�b�h����
#include "../tpip3/include/TPGM_12dll.h"      // ��ʕ`��
#include "../tpip3/include/TPJT3.h"           // ����`��
#include "../tpip3/include/TPUD_13dll.h"      // UDP�ʐM


#pragma comment(lib, "../tpip3/lib/TPGC_11.lib")
#pragma comment(lib, "../tpip3/lib/TPGM_12.lib")
#pragma comment(lib, "../tpip3/lib/TPJT3.lib")
#pragma comment(lib, "../tpip3/lib/TPUD_13.lib")

#endif