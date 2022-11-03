#!/bin/sh

# ========================================
# Split Tensilica Fusion F1 DSP DAT File
# ========================================
STRIP=arm-none-eabi-strip
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy
COMPRESS=xz

# Memory map settings
DRAM0_START_ADDR=0x60000000
DRAM0_MAX_SIZE=0x14000
DRAM0_MAX_SIZE_BYTES=81920

DRAM1_START_ADDR=0x60020000
DRAM1_MAX_SIZE=0x14000
DRAM1_MAX_SIZE_BYTES=81920

IRAM_START_ADDR=0x60040000
IRAM_MAX_SIZE=0x40000
IRAM_MAX_SIZE_BYTES=262144

CNT_DRAM0=0
CNT_DRAM1=0
CNT_IRAM=0
###############################################################################

if [ $# -ne 1 ]
then
    echo "Usage: split_img <image>"
fi

rm -Rf infom/
rm -Rf output/
rm -f magpie_bbp_sec_header
rm -f *.txt
rm -f *.bin_padding
rm -f *.bin 

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
    -v dram0_max_size=$DRAM0_MAX_SIZE \
    -v dram1_start_addr=$DRAM1_START_ADDR \
    -v dram1_max_size=$DRAM1_MAX_SIZE \
    -v iram_start_addr=$IRAM_START_ADDR \
    -v iram_max_size=$IRAM_MAX_SIZE \
    -v cnt_dram0=$CNT_DRAM0 \
    -v cnt_dram1=$CNT_DRAM1 \
    -v cnt_iram=$CNT_IRAM \
'
BEGIN {
  FS = " "
  str1="image"
  str2="region"
  str3="offset"
  str4="size"
  str5="offset+size"
  str6="front padding"
  str7="File offset"
  str8="-----------------------"
  printf("%-24s %-15s %-15s %-15s %-15s %-15s %-15s \n", str1, str2, str3, str4, str5, str6, str7)
  printf("%-24.21s %-15.8s %-15.8s %-15.8s %-15.8s %-15.13s %-15.11s \n", str8, str8, str8, str8, str8, str8, str8)
}
$2 ~ /(\.*.\.text$|.*\.literal$)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  err_flag = 0
  cnt_iram = cnt_iram+1
  FileOffset  = ("0x" $6) + 0
  if (LMA < dram0_start_addr) {
    loc = "data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    loc = "data0"
    offset = LMA - dram0_start_addr
  } else if (LMA >= iram_start_addr && LMA < iram_start_addr+iram_max_size){
    loc = "iram"
    offset = LMA - iram_start_addr
  } else {
     err_flag = 1
  }
  if (err_flag == 0) {
    if (cnt_iram==1) {
      tmp = offset + Size
      padding = 0
    } else {
      if (offset - tmp != 0) {
        padding = offset -tmp
      } else {
        padding = 0
      }
      tmp = offset + Size
    }
    bin_file = "magpie_sec_idx" $1 ".bin"
    printf("%-24s %-15s %-15x %-15x %-15x %-15x %-15x\n", bin_file, loc, offset, Size, offset+Size, padding, FileOffset)
    cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
    #print cmd
    system(cmd)
    
    if (padding != 0) {
      padding_file = "magpie_sec_idx" $1 ".bin" "_padding" 
      paddingcmd = sprintf("dd if=/dev/zero of=%s bs=1 count=%s", padding_file, padding)
      #print paddingcmd
      system(paddingcmd)
    }
  }
}
$2 ~ /(\.data$|\.rodata$|^\.text$)/ {
  #split($2, Name_fields, ".")
  Size = ("0x" $3) + 0
  LMA  = ("0x" $5) + 0
  err_flag = 0
  cnt_dram0 = cnt_dram0+1
  FileOffset  = ("0x" $6) + 0
  if (LMA < dram0_start_addr) {
    loc = "data1"
    offset = LMA - dram1_start_addr
  } else if (LMA < iram_start_addr) {
    loc = "data0"
    offset = LMA - dram0_start_addr
  } else if (LMA >= iram_start_addr && LMA < iram_start_addr+iram_max_size){
    loc = "iram"
    offset = LMA - iram_start_addr
  }else {
    err_flag = 1
  }
  if (err_flag == 0) {
    if (cnt_dram0==1) {
      tmp = offset + Size
      padding = 0
    } else {
      if (offset - tmp != 0) {
        padding = offset -tmp
      } else {
        padding = 0
      }
      tmp = offset + Size
    }
    bin_file = "magpie_sec_idx" $1 ".bin"
    printf("%-24s %-15s %-15x %-15x %-15x %-15x %-15x\n", bin_file, loc, offset, Size, offset+Size, padding, FileOffset)
    cmd = sprintf("%s -I elf32-little -O binary -j %-28s %s %s", objcopy, $2, img_file, bin_file)
    #print cmd
    system(cmd)

    if (padding != 0) {
      padding_file = "magpie_sec_idx" $1 ".bin" "_padding" 
      paddingcmd = sprintf("dd if=/dev/zero of=%s bs=1 count=%s", padding_file, padding)
      #print paddingcmd
      system(paddingcmd)
    }
  }
}
' magpie_bbp_sec_header > magpie_bbp_sec_map.txt



awk 'BEGIN {
  data0_bin_file = "sonata_dsp_dram0_tmp.bin"
  catcmd = sprintf("touch %s",data0_bin_file)
  system(catcmd)
  iram_bin_file = "sonata_dsp_iram_tmp.bin"
  catcmd = sprintf("touch %s",iram_bin_file)
  system(catcmd)
}
{
  bin_file = $1
  loc = $2
  padding = $6
  padding_file = bin_file "_padding"
  if (loc == "data0") {
    if (padding != 0) {
    printf("cat %s > %s\n",padding_file,data0_bin_file)
    catcmd = sprintf("cat %s >> %s",padding_file,data0_bin_file)
    system(catcmd) 
    }
    printf("cat %s > %s\n",bin_file,data0_bin_file)
    catcmd = sprintf("cat %s >> %s",bin_file,data0_bin_file)
    system(catcmd) 
     
  } else if (loc == "iram") {
    if (padding != 0) {
    printf("cat %s > %s\n",padding_file,iram_bin_file)
    catcmd = sprintf("cat %s >> %s",padding_file,iram_bin_file)
    system(catcmd) 
    }
    printf("cat %s > %s\n",bin_file,iram_bin_file)
    catcmd = sprintf("cat %s >> %s",bin_file,iram_bin_file)
    system(catcmd)
  } 
}' magpie_bbp_sec_map.txt >cat_sec_map.txt


DRAM0FILENAME=sonata_dsp_dram0_tmp.bin
DRAM0FILEPADDINGNAME=sonata_dsp_dram0_tmp.bin_padding
DRAM0FILELASTNAME=sonata_dsp_dram0.bin
DRAM0FILESIZE=$(stat -c%s "$DRAM0FILENAME")
DRAM0PADDINGBYTES=$((${DRAM0_MAX_SIZE_BYTES}-${DRAM0FILESIZE}))
dd if=/dev/zero of=$DRAM0FILEPADDINGNAME bs=1 count=$DRAM0PADDINGBYTES
#cat %s %s > %s,$DRAM0FILENAME,$DRAM0FILEPADDINGNAME,$DRAM0FILELASTNAME
cat $DRAM0FILENAME $DRAM0FILEPADDINGNAME > $DRAM0FILELASTNAME

IRAMFILENAME=sonata_dsp_iram_tmp.bin
IRAMFILEPADDINGNAME=sonata_dsp_iram_tmp.bin_padding
IRAMFILELASTNAME=sonata_dsp_iram.bin
IRAMFILESIZE=$(stat -c%s "$IRAMFILENAME")
IRAMPADDINGBYTES=$((${IRAM_MAX_SIZE_BYTES}-${IRAMFILESIZE}))
dd if=/dev/zero of=$IRAMFILEPADDINGNAME bs=1 count=$IRAMPADDINGBYTES
cat $IRAMFILENAME $IRAMFILEPADDINGNAME > $IRAMFILELASTNAME

mkdir -p infom
mv *.bin infom/
mv *.bin_padding infom/
mv *.txt infom/
mv magpie_bbp_sec_header infom/

mkdir -p output
mv infom/sonata_dsp_dram0.bin output/
mv infom/sonata_dsp_iram.bin output/