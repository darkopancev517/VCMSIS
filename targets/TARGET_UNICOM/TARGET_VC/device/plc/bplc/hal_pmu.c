#include "hal_pmu.h"

#define VCREG_BASE_PMU 0x40048000

void hal_pmu_LDO_ctrl_config_vout_sel(uint32_t value)
{
	volatile unsigned *pmuLDOCtrlCfgVoutSel = (volatile unsigned *)(VCREG_BASE_PMU + 0x104);
	*(pmuLDOCtrlCfgVoutSel) &= 0xFFFFFFF8;
	*(pmuLDOCtrlCfgVoutSel) |= value;
}

void hal_pmu_BUCK_ctrl_config_vout_sel(uint32_t value)
{
	volatile unsigned *pmuBUCKCtrlCfgVoutSel = (volatile unsigned *)(VCREG_BASE_PMU + 0x108);
	*(pmuBUCKCtrlCfgVoutSel) &= 0xFFFFFFF8;
	*(pmuBUCKCtrlCfgVoutSel) |= value;
}
