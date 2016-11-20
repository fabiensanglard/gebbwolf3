typedef struct mmblockstruct
{
	unsigned	start,length;
	unsigned	attributes;
	memptr		*useptr;
	struct mmblockstruct far *next;
} mmblocktype;