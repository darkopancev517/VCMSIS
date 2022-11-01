#i/bin/bash
gcc main.c -o mkimg;
./mkimg magpie_e_soc.bin magpie_e_soc_nvram.bin bbp/magpie_bbp_sec_map.txt bbp/magpie_bbp_fw_ver.bin
