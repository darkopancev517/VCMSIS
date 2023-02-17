#ifndef HAL_PMU_H
#define HAL_PMU_H

#include <stdint.h>

void hal_pmu_LDO_ctrl_config_vout_sel(uint32_t value);
void hal_pmu_BUCK_ctrl_config_vout_sel(uint32_t value);

#endif
