/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
 * woody.yang@vertexcom.com
*/

#include "totctl.h"

static uint32_t m_totctl_debug = 0;

void totctl_debug_set(uint32_t msk)
{
    m_totctl_debug = msk;
}

uint32_t totctl_debug_get(void)
{
    return m_totctl_debug;
}
