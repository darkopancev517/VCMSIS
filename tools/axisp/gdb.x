
#target remote 192.168.43.245:3333
#target remote 10.75.105.188:3333
#target remote :3333

set history save on
set history size 100
set history expansion on

#set args -p1 ping
#set args -p1 isp ../../../out/magpie.bin
#set args -p1 ww 30001000 ffffcccc
#set args -p1 ww 30001000 ffffcccc
#set args -p1 ww 30001000 abcd6789 a1b2c3d4 e2f2a2b2
#set args -p1 isp ./rom.bin 30000000
#set args mkimg ./magpie.bin ./dsp_image_map.txt firmware.bin
#set args mkimg magpie.bin magpie_bbp_sec_map.txt dsp_version.bin firmware.bin
set args -p1 -x2 ping
#set args -p1 -x1 setup 0 900000
#set args -p1 -x1 isp rom.bin 30000000
#set args -p1 -x1 isp magpie.bin
#set args -p1 -x1 ww 30001000 abcd6789
#set args -p1 -x1 ww 30001000 abcd6789 a1b2c3d4
#set args -p1 -x1 ww 30001000 abcd6789 a1b2c3d4 e2f2a2b2
#set args -p1 -x1 ww 30001000 a1b1c1d1 e2f2a2b2 c3d3e3f3 a4b4c4d4 e5f5a5b5 c6d6e6f6 a7b7c7d
#set args -p1 -x1 dw 54000020 40
#set args probe base
#set args probe base 20000000
#set args probe dw 0 20000000
#set args probe dw 0 20000000 10
#set args probe idw 0 0 10
#set args probe ww 30000000 a1b1c1d1
#set args probe ww 30000000 a1b1c1d1 e2f2a2b2 c3d3e3f3
#set args probe iww 0 a1b1c1d1
#set args probe iww 0 a1b1c1d1 e2f2a2b2 c3d3e3f3

file ./out/axisp

b main
#b vtspisp::do_ping
#b vtspisp::do_remap_get
#b vtspisp::do_setup
#b vtspisp::do_word_read
#b vtspisp::do_word_write
#b vtspisp_packet::send_out
b vtiicisp::do_ping
b vtiicisp::do_isp
b vtiicisp::do_raw_isp
b vtiicisp::prog_iram
b vtiicisp::do_eflash_isp
b vtiicisp::prog_eflash
#b axisp_do_probe
#b vtprobe::do_probe_cmd
#b axisp_dispatch_command
#b vtisp::do_ping
#b vtisp::do_word_write
#b vtisp_packet::send_out
#b vtisp_packet::spi_out
#b axftdi::enum_devices
#b axftdi::~axftdi
#b axftdi::gpio_open
#b axfl_reg_read
#b xmodem_crc
#b isp::do_data_write
#b xmodem16::do_crc
#b isp::do_bist
#b vtisp::do_word_read
#b vtisp::do_isp
#b vtisp::prog_eflash
#b vtisp::do_word_write
#b vtisp::prog_iram
#b mkimg::do_dsp_version
#b mkimg::do_make_image
#b mkimg::do_dsp_parsing
#b mkimg::attach_section

#layout split
#layout regs
#layout asm
#layout src

#focus src
#focus asm
#focus cmd

# command hints:
#
# p/d $d0       ; print d0 in decimal format
# p/x $d0       ; print d0 in hexidecial format
# p/x 0x1e*0x0a ; print value of expression 0x1e*0x0a
# p/x src_expr  ; print result of the source expression
#
# x/4w $r3      ; dump memory data (word x 4) addressed by r3 (using dex/hex format of previous p command)
# x/8b $r3      ; dump memory data (byte x 8) addressed by r3 (using dex/hex format of previous p command)
#
# x/4xw data    ; dump memory data (word x 4) addressed by *data (using hex format)
# x/4xb data    ; dump memory data (byte x 4) addressed by *data (using hex format)
#
# s             ; step a line of source (step into the function if any)
# n             ; trace a line of source
# si            ; step one asm instruction (step into the function if any)
# ni            ; trace one asm instruction
# u #line       ; continue until reaching source line #number
# j #line       ; resume execution at specified line #number
# j *addr       ; resume execution at specified address
# set var=expr  ; set variable value
#

#disp/x $d4
#disp/x $d2
#disp/x $d0
#disp/x $r2

r


