
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MKPRINT 0
#define MEMORY_START_ADDRESS 0x00000
#define MAX_MEMORY_SIZE 0x11a000
#define BBP_PARTITION_SIZE 0x5a000
#define STRING_SIZE 512

typedef enum {
	MKIMG_READ_R,
	MKIMG_READ_R_PLUS,
	MKIMG_READ_A
} mkimg_read_type;

typedef enum {
	MKIMG_WRITE_W,
	MKIMG_WRITE_W_PLUS,
	MKIMG_WRITE_A
} mkimg_write_type;

typedef enum {
	bbp_null,
	bbp_o_data_0,
	bbp_z_data_0,
	bbp_o_data_1,
	bbp_z_data_1,	
	bbp_o_iram,
	bbp_z_iram,
	bbp_data_0,
	bbp_iram,
} bbp_sec_map_region_type;

typedef struct bbp_sec_map_struct {
	char image_name[255];
	bbp_sec_map_region_type regionType;
	unsigned long offset;
	unsigned long size;
} bbp_sec_map_struct;

typedef struct mkimg_soc_data {
	unsigned char data[MAX_MEMORY_SIZE];
	unsigned long data_len;
} mkimg_soc_data;

typedef struct mkimg_fwver_data {
	unsigned char data[MAX_MEMORY_SIZE];
	unsigned long data_len;
} mkimg_fwver_data;

typedef struct mkimg_iram_data {
	unsigned char data[MAX_MEMORY_SIZE];
	unsigned long data_len;
} mkimg_iram_data;

typedef struct mkimg_data1_data {
	unsigned char data[MAX_MEMORY_SIZE];
	unsigned long data_len;
} mkimg_data1_data;

unsigned char mData[MAX_MEMORY_SIZE];

unsigned long g_soc_len=0;
mkimg_soc_data g_soc;

unsigned long g_fwver_len=0;
mkimg_fwver_data g_fwver;

unsigned long g_iram_len=0;
mkimg_iram_data g_iram;

unsigned long g_data1_len=0;
mkimg_data1_data g_data1;

bbp_sec_map_struct bbpMap[20]={0};

unsigned long bbp_ver_len=16;

unsigned char g_bbp_ver_data[16]={0};

#define MAX_SOC_BIN_SIZE 0xc0000
#define BBP_IRAM_SIZE		 0x38000
#define BBP_DATA1_SIZE   0x0D000
#define	NVRAM_SIZE			 0x1000
#define BBP_VER_SIZE     0x10

#define bbp_iram_start 	 MAX_SOC_BIN_SIZE
#define bbp_iram_end		 (bbp_iram_start + BBP_IRAM_SIZE)
#define bbp_data1_start  bbp_iram_end
#define bbp_data1_end 	 (bbp_data1_start + BBP_DATA1_SIZE)

#define bbp_ver_start 	 bbp_data1_end
#define bbp_ver_end		   (bbp_ver_start + BBP_VER_SIZE)

int dump_mem(char*str, unsigned char *data, int len)
{
	printf("%s:%u Byte\r\n",str, len);

	for (int i = 0; i < len; i++)
  {
		printf("%08X : ", i);
		printf("%02X%02X ", data[i], data[i+1]);
		printf("%02X%02X ", data[i+2], data[i+3]);
		printf("%02X%02X ", data[i+4], data[i+5]);
		printf("%02X%02X ", data[i+6], data[i+7]);
		printf("%02X%02X ", data[i+8], data[i+9]);
		printf("%02X%02X ", data[i+10], data[i+11]);
		printf("%02X%02X ", data[i+12], data[i+13]);
		printf("%02X%02X\r\n", data[i+14], data[i+15]);		
		i+=15;		
	}

	printf("\r\n");
  return 0;
}

FILE* mkimg_Read_File(char *name, mkimg_read_type type)
{
	FILE *file_ptr;

	switch (type)
  {
		case MKIMG_READ_R:
    {
			file_ptr = fopen(name, "r");break;
		}

		case MKIMG_READ_R_PLUS:
    {
			file_ptr = fopen(name, "r+");break;
		}

		case MKIMG_READ_A:
    {
			file_ptr = fopen(name, "a");break;
		}

		default:
			break;
	}	

	if (file_ptr == NULL)
  {
		printf("file %s open error in ReadFile()\r\n", name);
		exit(EXIT_FAILURE);
	}

	return file_ptr;
}

FILE* mkimg_Write_File(char *name, mkimg_write_type type)
{
	FILE *file_ptr;

	switch (type)
  {
		case MKIMG_WRITE_W:
    {
			file_ptr = fopen(name,"w");break;
		}

		case MKIMG_WRITE_W_PLUS:
    {
			file_ptr = fopen(name,"w+");break;
		}

		case MKIMG_WRITE_A:
    {
			file_ptr = fopen(name,"a");break;
		}

		default:
			break;
	}

	if (file_ptr == NULL )
	{
		printf("file %s open error in WriteFile()\r\n", name);
		exit(EXIT_FAILURE);
	}

	return file_ptr;
}

int put_data_into_memory(int startAddrs, int endAddrs, unsigned char *pData, int size)
{
	unsigned long addrsCount=0;	
	
	addrsCount = startAddrs;

	printf("start) 0x%06x end) 0x%06x size) 0x%x (%d byte)\r\n", startAddrs, endAddrs, size, size);

	for(int i = 0; i < size; i++)
  {
		//printf("%02X ",pData[i]);
		mData[addrsCount]=pData[i];
		addrsCount++;
	}

	//printf("\r\n");
  return 0;
}

void char_subst( char* target_string, char target_char, char  wanted_char)
{
  for (int index = 0; index < strlen(target_string); index++)
  {
    if (target_string[index] == target_char)
    {
      target_string[index] = wanted_char;
    }
  }

  return;
}

char* get_val_from_string(char *str, long *int_cnt, long int_val[], short* val2_len)
{
	char val_str[4][STRING_SIZE] = {0};
	char temp_str[STRING_SIZE] = {0};
	unsigned long	value[3] = {0};

	strcpy(temp_str,str);	
	sscanf(temp_str, "%s %s %s %s", val_str[0], val_str[1], val_str[2],val_str[3]);	

	int_val[0] = (long)val_str[0];
	int_val[1] = (long)val_str[1];
	int_val[2] = (int)strtol(val_str[2], NULL, 16);
	int_val[3] = (int)strtol(val_str[3], NULL, 16);

	return str;
}

int transferRegionType(long regionType)
{
	bbp_sec_map_region_type type = 0;
	//printf("transferRegionType:%s\r\n",regionType);	

	if (strstr("o_data0", (char *)regionType) != NULL)
  {		
		type =  bbp_o_data_0;
	}

	if (strstr("z_data0", (char *)regionType) != NULL)
  {
		type =  bbp_z_data_0;
	}

	if (strstr("o_data1", (char *)regionType) != NULL)
  {
		type =  bbp_o_data_1;
	}

	if (strstr("z_data1", (char *)regionType) != NULL)
  {
		type =  bbp_z_data_1;
	}

	if (strstr("o_iram", (char *)regionType) != NULL)
  {
		type =  bbp_o_iram;
	}

	if (strstr("z_iram", (char *)regionType) != NULL)
  {
		type =  bbp_z_iram;
	}

	if (strstr("data0", (char *)regionType) != NULL)
  {
		type =  bbp_data_0;
	}

	if (strstr("iram", (char *)regionType) != NULL)
  {
		type = bbp_iram;
	}

	return type;
}

int process_soc_bin_file(char *fileName)
{
	FILE *rFile;
	unsigned char ch; 
  int count = 0;
	int address=0x000000;
	
	rFile = mkimg_Read_File(fileName,MKIMG_READ_R);

	while (!feof(rFile))
  {
		fread(&ch, sizeof(char), 1, rFile);
		g_soc.data[address]=ch;
		g_soc_len++;
		address++;
	}

	return 0;
}

int process_bbp_iram()
{
	FILE *rFile;
	unsigned char ch;
	char fileName[255]={0};
  int count = 0;
	int address=0x000000;

	memset(g_iram.data, 0x0, MAX_MEMORY_SIZE);

	for (int i = 0; i < 20; i++)
  {
		if (bbpMap[i].regionType == bbp_iram ||(bbpMap[i].regionType == bbp_o_iram))
    {
			//printf("iram: %s off=%x , len=%x\r\n",bbpMap[i].image_name, bbpMap[i].offset, bbpMap[i].size);
			sprintf(fileName,"../bbp/%s", bbpMap[i].image_name);
			rFile = mkimg_Read_File(fileName,MKIMG_READ_R);
			address=0;

			while (!feof(rFile))
      {
				fread(&ch, sizeof(char), 1, rFile);				
				g_iram.data[bbpMap[i].offset+(address++)]=ch;	
			}

			g_iram_len=bbpMap[i].offset+address-1;
		}
	}

	
#if(MKPRINT)
	dump_mem("iramData:", &g_iram.data[0], g_iram_len);
#endif
  return 0;
}

int process_bbp_data1()
{
	FILE *rFile;
	unsigned char ch;
	char fileName[255]={0};
  int count = 0;
	int address=0x000000;
	int i;

	for (i = 0; i < 20; i++)
  {
		if (bbpMap[i].regionType == bbp_o_data_1)
    {
			sprintf(fileName,"../bbp/%s",bbpMap[i].image_name);
			//printf("data1: %s off=%x , len=%x\r\n",bbpMap[i].image_name, bbpMap[i].offset, bbpMap[i].size);
			
			rFile = mkimg_Read_File(fileName,MKIMG_READ_R);
			address=0;

			while (!feof(rFile))
      {
				fread(&ch, sizeof(char), 1, rFile);				
				g_data1.data[bbpMap[i].offset+(address++)]=ch;	
			}

			g_data1_len=bbpMap[i].offset+address-1;	
		}
	}

#if(MKPRINT)
	dump_mem("data1Data:", &g_data1.data[0], g_data1_len);
#endif	
  return 0;
}

int process_bbp_sec_map(char *fileName)
{
  char line_buffer[255]={0};    	
	FILE *rFile;
	int bbpMapIdx=0;
  int i;    	
	rFile = mkimg_Read_File(fileName,MKIMG_READ_R);

	while (fgets(line_buffer, 255, rFile) != NULL )
  {
		if (strstr(line_buffer,"#") != NULL)
    {
			/* skip comment*/
		}
    else
    {
			short val2_len = 0;	
			long int_cnt = 0;
			long int_val[4] = {0};			
			get_val_from_string(line_buffer, &int_cnt, int_val, &val2_len);						
			strcpy(bbpMap[bbpMapIdx].image_name, (char *)int_val[0]);
			bbpMap[bbpMapIdx].regionType = transferRegionType(int_val[1]);
			bbpMap[bbpMapIdx].offset = int_val[2];
			bbpMap[bbpMapIdx].size=int_val[3];
			bbpMapIdx++;
		}
	}

	if (rFile != NULL)
  {
		process_bbp_iram();
		process_bbp_data1();
	}

	return 0;
}

int process_bbp_fw_ver(char *fileName)
{
	FILE *rFile;
	//unsigned char bbp_ver_data[16]={0};
	int address=0x0;
	unsigned char ch;
	int i;

	rFile = mkimg_Read_File(fileName,MKIMG_READ_R);

	while (!feof(rFile))
  {
		fread(&ch, sizeof(char), 1, rFile);
		g_bbp_ver_data[address]=ch;
		address++;
	}
	
	return 0;
}

int process_info_block()
{
	mData[0x0C]=0x01;/*__bbp_reloc__*/	
  return 0;
}

int process_image_bin_output(char *fileName)
{
	FILE *wFile;

	put_data_into_memory(MEMORY_START_ADDRESS,MAX_SOC_BIN_SIZE, g_soc.data, g_soc_len);
	put_data_into_memory(bbp_iram_start, bbp_iram_end, g_iram.data, g_iram_len);
	put_data_into_memory(bbp_data1_start, bbp_data1_end, g_data1.data, g_data1_len);
	put_data_into_memory(bbp_ver_start, bbp_ver_end, g_bbp_ver_data,  bbp_ver_len);

	wFile = mkimg_Write_File(fileName, MKIMG_WRITE_W);

	for (int i = 0x0; i < MAX_MEMORY_SIZE; i++)
  {
		fwrite(&mData[i],1,sizeof(char),wFile);
	}

	fclose(wFile);

  return 0;
}

int process_image_bbp_bin_output(char *filename)
{
  FILE *wfile;

  int new_bbp_iram_end = bbp_iram_end - MAX_SOC_BIN_SIZE;
  int new_bbp_data1_start = bbp_data1_start - MAX_SOC_BIN_SIZE;
  int new_bbp_data1_end = bbp_data1_end - MAX_SOC_BIN_SIZE;
  int new_bbp_ver_start = bbp_ver_start - MAX_SOC_BIN_SIZE;
  int new_bbp_ver_end = bbp_ver_end - MAX_SOC_BIN_SIZE;

  memset(mData, 0, MAX_MEMORY_SIZE);

  put_data_into_memory(0, new_bbp_iram_end, g_iram.data, g_iram_len);
  put_data_into_memory(new_bbp_data1_start, new_bbp_data1_end, g_data1.data, g_data1_len);
  put_data_into_memory(new_bbp_ver_start, new_bbp_ver_end, g_bbp_ver_data, bbp_ver_len);

  wfile = mkimg_Write_File(filename, MKIMG_WRITE_W);

  for (int i = 0; i < BBP_PARTITION_SIZE; i++)
  {
    fwrite(&mData[i], 1, sizeof(char), wfile);
  }

  fclose(wfile);

  return 0;
}

int main(int argc, char* argv[])
{	
  printf("mkimg->argc:%d\r\n",argc);    	

  for(int i=0; i < argc; i++)
  {
    printf("%d->%s\r\n", i, argv[i]);
  }

	printf("\n");
	
  process_soc_bin_file(argv[1]);    	
	process_bbp_sec_map(argv[2]);
	process_bbp_fw_ver(argv[3]);
	process_info_block();

	process_image_bin_output(argv[4]);      /* SOC + BBP image */
  process_image_bbp_bin_output(argv[5]);  /* BBP only image */

	printf("\n");

	return 0;
}
