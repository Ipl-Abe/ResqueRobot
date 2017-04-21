/**
* @file TPIP3.h
* @brief TPIP3用ライブラリ
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
* @version 1.01 2013/03/21 katayama
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* このファイルの著作権は、TPIPユーザーコミュニティの規約に従い使用許諾をします。
*/


#ifndef __TPIP3_H__
#define __TPIP3_H__

#define QVGA       (0)       //!< @brief QVGA解像度
#define VGA        (1)       //!< @brief VGA解像度

#define PWM_MAX    ( 1000)   //!< @brief PWMへの出力最大値
#define PWM_MIN    (-1000)   //!< @brief PWMへの出力最小値

#define AI_MAX     (0xFFFF)  //!< @brief アナログ入力の最大値
#define AI_MIN     (0x00)    //!< @brief アナログ入力の最小値

#define PI_MAX     (0xFFFF)  //!< @brief パルス入力の最大値
#define PI_MIN     (0x00)    //!< @brief パルス入力の最小値

#define AI_CH      (8)      //!< @brief アナログ入力のチャンネル数
#define PI_CH      (4)       //!< @brief パルス入力のチャンネル数
#define DI_CH      (4)       //!< @brief デジタル出力のチャンネル数
#define DO_CH      (4)       //!< @brief デジタル入力のチャンネル数
#define PWM_CH     (4)      //!< @brief PWM出力のチャンネル数

#define AXIS_MAX   (32767)   //!< @brief ゲームコントローラのアナログパッドの最大値
#define AXIS_MIN   (-32768)  //!< @brief ゲームコントローラのアナログパッドの最小値

#define BTN_RU     (0x001)   //!< @brief ゲームコントローラの右、上の値
#define BTN_RR     (0x002)   //!< @brief ゲームコントローラの右、右の値
#define BTN_RD     (0x004)   //!< @brief ゲームコントローラの右、下の値
#define BTN_RL     (0x008)   //!< @brief ゲームコントローラの右、左の値
#define BTN_L2     (0x010)   //!< @brief ゲームコントローラのL2の値
#define BTN_R2     (0x020)   //!< @brief ゲームコントローラのR2の値
#define BTN_L1     (0x040)   //!< @brief ゲームコントローラのL1の値
#define BTN_R1     (0x080)   //!< @brief ゲームコントローラのR1の値
#define BTN_ST     (0x100)   //!< @brief ゲームコントローラのSTARTの値
#define BTN_SE     (0x200)   //!< @brief ゲームコントローラのSELECTの値
#define BTN_L3     (0x400)   //!< @brief ゲームコントローラのL3の値
#define BTN_R3     (0x800)   //!< @brief ゲームコントローラのR3の値

#define TPJT_COM_JPEG (0x01) //!< @brief 通信モード(JPEG)
#define TPJT_COM_CTRL (0x02) //!< @brief 通信モード(制御)

#include "../tpip3/include/TPGC_11dll.h"      // ゲームパッド入力
#include "../tpip3/include/TPGM_12dll.h"      // 画面描画
#include "../tpip3/include/TPJT3.h"           // 動画伝送
#include "../tpip3/include/TPUD_13dll.h"      // UDP通信


#pragma comment(lib, "../tpip3/lib/TPGC_11.lib")
#pragma comment(lib, "../tpip3/lib/TPGM_12.lib")
#pragma comment(lib, "../tpip3/lib/TPJT3.lib")
#pragma comment(lib, "../tpip3/lib/TPUD_13.lib")

#endif