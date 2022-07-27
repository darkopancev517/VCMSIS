/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef RFMBX_H
#define RFMBX_H

#include <stdint.h>
#include "rf_host.h"

#ifdef __cplusplus
extern "C" {
#endif

void rfmbx_init();
void rfmbx_clear();
//int rfmbx_put(RF_EVENT_T *px); //m0 side
int rfmbx_get(RF_EVENT_T *px);
void rfmbx_dump();

#ifdef __cplusplus
}
#endif

#endif // RFMBX_H

