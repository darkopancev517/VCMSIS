/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __RF_HWSET_H
#define __RF_HWSET_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//TODO: move HWSET to correct flash location

typedef struct {
    /*FLASH_HWSET(rx):ORIGIN = 0x001ff000, LENGTH = 0x1000*/
    uint32_t mSeriesNumber;       //0x001ff000
    uint32_t mDate;               //0x001ff004
    uint32_t mFrequency;          //0x001ff008
    uint32_t mXtalOffset;         //0x001ff00c
    uint32_t mPaSel;              //0x001ff010
    int32_t  mTxPower;            //0x001ff014
    int32_t  mTxPowerCalibOffset; //0x001ff018
    int32_t  mRssiOffset;         //0x001ff01c
    uint16_t mFec;                //0x001ff01d
    uint16_t mLfxoCsel;           //0x001ff01e
    uint16_t mRfTestMode;         //0x001ff01f
    uint16_t space;
    int32_t mTempOffset;
    int32_t  mELNARssiOffset;
    uint32_t mFrontEndStateBits;  // Bit: [0: ELNA state, 1: EPA state, 2: ANT diversity, ...]
    uint8_t mMacAddr[8];
    int32_t mCcaThreshold;
    uint32_t mChipId;             //0x001ff040
    uint32_t mBoardId;            //0x001ff044
    uint32_t mCal[16];            //0x001ff048
} rf_hwset_t;

extern rf_hwset_t rf_hwset;

#ifdef __cplusplus
}
#endif

#endif /* __RF_HWSET_H */
