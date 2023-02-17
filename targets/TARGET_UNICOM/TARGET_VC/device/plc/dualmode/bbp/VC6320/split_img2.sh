#!/bin/sh

STRIP=arm-none-eabi-strip
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy
COMPRESS=xz

# Memory map settings
DRAM0_START_ADDR=0x60040000
DRAM1_START_ADDR=0x60020000
IRAM_START_ADDR=0x60080000
###############################################################################

if [ $# -ne 1 ]
then
    echo "Usage: split_img <image>"
fi

#img_file=G3_PLC.dat
#$STRIP -I elf32-little -g -S -d -o $img_file $1

img_file=$1

$OBJDUMP -h $img_file > magpie_bbp_sec_header

# Format of magpie_bbp_sec_header
#   1:Idx 2:Name 3:Size 4:VMA 5:LMA 6:File off 7:Algn
# Expetected output format
#   1:bbp_substr(Name).bin 2:data0|data1|iram 3:offset 4:size

awk --non-decimal-data \
    -v img_file=$img_file \
    -v objcopy=$OBJCOPY \
    -v compress=$COMPRESS\
    -v dram0_start_addr=$DRAM0_START_ADDR \
    -v dram1_start_addr=$DRAM1_START_ADDR \
    -v iram_start_addr=$IRAM_START_ADDR \
'
BEGIN {
  FS = " "
  print "# image                   region  offset    size"
  print "# ------------------      ------  --------  --------"
}
$2 ~ /(\.*.\.text$|.*\.literal$|.*\.MagpieBbpFwVer)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  if (LMA < dram0_start_addr) {
    loc = "data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    loc = "data0"
    offset = LMA - dram0_start_addr
  } else {
    loc = "iram"
    offset = LMA - iram_start_addr
  }
  bin_file = "magpie_sec_idx" $1 ".bin"
  printf("%-24s  %-6s  %08x  %08x\n", bin_file, loc, offset, Size)
  cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
  #print cmd
  system(cmd)
}

$2 ~ /(\.data$|\.rodata$|^\.text$)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  if (LMA < dram0_start_addr) {
    zip_loc = "z_data1"
    unzip_loc = "o_data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    zip_loc = "z_data0"
    unzip_loc = "o_data0"
    offset = LMA - dram0_start_addr
  } else {
    zip_loc = "z_iram"
    unzip_loc = "o_iram"
    offset = LMA - iram_start_addr
  }

  bin_file = "magpie_sec_idx" $1 ".bin"
  zip_file = bin_file ".xz"
  printf("%-24s  %-6s  %08x  %08x\n", bin_file, unzip_loc, offset, Size)
  printf("%-24s  %-6s  %08x  REPLACE_%-08s\n", zip_file, zip_loc, offset, zip_loc)
  cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
  #print cmd
  system(cmd)
  cmd = sprintf("%s -z -k -f --lzma2=dict=4K --check=none %s", compress, bin_file)
  #print cmd
  system(cmd)
  cmd = sprintf("printf \"%%08x\" `stat -c \"%%s\" %s.xz` > compressed_size_%s", bin_file, zip_loc)
  #print cmd
  system(cmd)
}
$2 ~ /\.MagpieBbpFwVer$/ {
  cmd = objcopy " -I elf32-little -O binary -j .MagpieBbpFwVer " img_file " magpie_bbp_fw_ver.bin"
  #print cmd
  system(cmd)
}


' magpie_bbp_sec_header > magpie_bbp_sec_map.txt


awk --non-decimal-data \
    -v img_file=$img_file \
    -v objcopy=$OBJCOPY \
    -v compress=$COMPRESS\
    -v dram0_start_addr=$DRAM0_START_ADDR \
    -v dram1_start_addr=$DRAM1_START_ADDR \
    -v iram_start_addr=$IRAM_START_ADDR \
'
BEGIN {
 
  print "set *0x400111c0=0x0"
  print "\n "
}
$2 ~ /(\.*.\.text$|.*\.literal$|.*\.MagpieBbpFwVer)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  if (LMA < dram0_start_addr) {
    loc = "data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    loc = "data0"
    offset = LMA - dram0_start_addr
  } else {
    loc = "iram"
    offset = LMA - iram_start_addr
  }
  bin_file = "magpie_sec_idx" $1 ".bin"
  printf("restore ~/SHARE/Trx/Magpie2/vtec/bbp/%-24s binary 0x%08x\n", bin_file, LMA-0x40000000)
  #cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
  #print cmd
  #system(cmd)
}



$2 ~ /(\.data$|\.rodata$|^\.text$)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  if (LMA < dram0_start_addr) {
    zip_loc = "z_data1"
    unzip_loc = "o_data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    zip_loc = "z_data0"
    unzip_loc = "o_data0"
    offset = LMA - dram0_start_addr
  } else {
    zip_loc = "z_iram"
    unzip_loc = "o_iram"
    offset = LMA - iram_start_addr
  }

  bin_file = "magpie_sec_idx" $1 ".bin"
  zip_file = bin_file ".xz"
  if(unzip_loc == "o_data1") {
    printf("restore ~/SHARE/Trx/Magpie2/vtec/bbp/%-24s binary 0x%08x\n", bin_file, LMA-0x40000000+0xC0000)
    } else if (unzip_loc = "o_iram"){
        printf("restore ~/SHARE/Trx/Magpie2/vtec/bbp/%-24s binary 0x%08x\n", bin_file, LMA-0x40000000)
    }
    else {
            printf("restore ~/SHARE/Trx/Magpie2/vtec/bbp/%-24s binary 0x%08x\n", bin_file, LMA-0x40000000)
    } 

 # printf("restore ~/SHARE/Trx/Magpie2/vtec/bbp/%-24s binary 0x200E0000+0x%08x\n", bin_file, offset)
  #printf("%-24s  %-6s  %08x  REPLACE_%-08s\n", zip_file, zip_loc, offset, zip_loc)
  #cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
  #print cmd
  #system(cmd)
  #cmd = sprintf("%s -z -k -f --lzma2=dict=4K --check=none %s", compress, bin_file)
  #print cmd
  #system(cmd)
  #cmd = sprintf("printf \"%%08x\" `stat -c \"%%s\" %s.xz` > compressed_size_%s", bin_file, zip_loc)
  #print cmd
  #system(cmd)




}



' magpie_bbp_sec_header > auto

COMPRESS_SIZE=`cat compressed_size_z_data1`
sed -i "s/REPLACE_z_data1/$COMPRESS_SIZE/g" magpie_bbp_sec_map.txt
COMPRESS_SIZE=`cat compressed_size_z_data0`
sed -i "s/REPLACE_z_data0/$COMPRESS_SIZE/g" magpie_bbp_sec_map.txt
COMPRESS_SIZE=`cat compressed_size_z_iram`
sed -i "s/REPLACE_z_iram/$COMPRESS_SIZE/g" magpie_bbp_sec_map.txt
