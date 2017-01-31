#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	unsigned char *buf;
	unsigned int *buf32;
	unsigned int total_entries, pos;
	size_t readsize, bufsize=0xD5DE8;
	FILE *f;

	if(argc<2)
	{
		printf("playhistory_parser by yellows8\n");
		printf("Parse 3DS PTM playhistory.\n");
		printf("Usage:\nplayhistory_parser <infile>\n");

		return 0;
	}

	buf = malloc(bufsize);
	if(buf==NULL)return 1;
	memset(buf, 0, bufsize);
	buf32 = (unsigned int*)buf;

	f = fopen(argv[1], "rb");
	if(f==NULL)
	{
		free(buf);
		return 2;
	}

	readsize = fread(buf, 1, bufsize, f);

	if(readsize < 0xc)
	{
		free(buf);
		return 3;
	}

	/*if(readsize < bufsize)
	{
		total_entries = readsize / 0xc;
	}
	else*/
	{
		total_entries = buf32[1];
		if(total_entries > 0x11D28)total_entries = 0x11D28;
	}

	printf("offset 0x0: 0x%x\n", buf32[0]);
	printf("total_entries: 0x%x\n", total_entries);

	for(pos=0; pos<total_entries; pos++)
	{
		printf("entry 0x%x offset 0x%x: ID=0x%08x%08x u32=0x%08x\n", pos, 8+(pos*0xc), buf32[2+(pos*3)], buf32[2+(pos*3)+1], buf32[2+(pos*3)+2]);
	}

	free(buf);

	return 0;
}

