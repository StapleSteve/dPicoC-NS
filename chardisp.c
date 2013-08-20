#include <os.h>

#define CHAR_WIDTH	8
#define CHAR_HEIGHT	12
extern unsigned char charMap_ascii[][12];
/*
inline void setpixel(int x, int y, int color) {
  unsigned char* p = (unsigned char*)(SCREEN_BASE_ADDRESS + ((x >> 1) + (y << 7) + (y << 5)));
  *p = (x & 1) ? ((*p & 0xF0) | color) : ((*p & 0x0F) | (color << 4));
}

inline int getpixel(int x, int y) {
  unsigned char* p = (unsigned char*)(SCREEN_BASE_ADDRESS + ((x >> 1) + (y << 7) + (y << 5)));
  return ((x & 1) ? (*p & 0x0F) : (*p >> 4));
}*/

void write_graph(int x,int y,int width,int height,unsigned char * pimage,int cl_fg,int cl_bg)
{
	int i,j,k,pixel,rx=0,ry=0;
	unsigned char p;
    int iwidth = width/8 + (width % 8 ? 1:0);
	for (i=0;i<height;++i,pimage+=iwidth)
	{
		ry = y+i;
		if (ry>=240) return;
		else if (ry<0) continue;
		for (j=0;j<iwidth;++j)
		{
			p = pimage[j];
			for (k=0;k<8;++k)
			{
				rx = x+(8-k)+8*j;
				pixel = p % 2;
				p>>=1;
				if (pixel)	setPixel(rx,ry,cl_fg);
				else		setPixel(rx,ry,cl_bg);
			}
		}
	}
}

void dg_put_str (int x,int y,char * s,int cl_fg,int cl_bg)
{
	int i;

	for(i=0;*s;++i,++s,x+=CHAR_WIDTH)
	{
		write_graph(x,y,
					CHAR_WIDTH,CHAR_HEIGHT,
					charMap_ascii[*s],
					cl_bg,cl_fg);
	}
}
int get_string (int x,int y,char * s,int width,int max,BOOL only_num,int clf,int clb)
{
	unsigned	ch;
	BOOL		refresh = TRUE;
	int			len = strlen(s);

	while(1)
	{
		if (refresh)
		{
			int i;
			
			for(i=0;i<width;++i)
				dg_put_str(x+i*CHAR_WIDTH,y," ",clf,clb);
			
			dg_put_str(x,y,(len>width-1?(s+len-width+1):s),clf,clb);
			
			dg_put_str(len>width-1?x+(width-1)*CHAR_WIDTH:x+len*CHAR_WIDTH,y,'|',clf,clb);
			
			refresh = FALSE;
		}
		
		wait_key_pressed();
		ch = nio_getch();
		
		if ((ch>='a' && ch<='z' && !only_num)
			|| (ch>='0' && ch<='9')
			|| (ch==' ')
			&& len<max) // get char
		{
			s[len++]	= ch;
			s[len]		= '\0';
			refresh		= TRUE;
		}
		else if (ch==8 && len>0)
		{
			s[--len]	= '\0';
			refresh		= TRUE;
		}
		else if (ch=='\n')
		{
			return 1;
		}
		else if (ch==0)
		{
			return 0;
		}
	}
	return 0;
}
unsigned char charMap_ascii[128][12]={
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 0 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 1 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 2 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 3 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 4 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 5 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 6 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 7 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 8 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 9 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 10 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 11 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 12 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 13 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 14 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 15 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 16 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 17 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 18 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 19 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 20 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 21 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 22 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 23 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 24 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 25 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 26 */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 27 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 28 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 29 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 30 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/* 31 */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},				/*   */
{0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x10,0x0,0x0},		/* ! */
{0x0,0x28,0x28,0x28,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},			/* " */
{0x0,0x14,0x14,0x7e,0x28,0x28,0x28,0xfc,0x50,0x50,0x0,0x0},		/* # */
{0x0,0x10,0x38,0x44,0x40,0x38,0x4,0x44,0x38,0x10,0x0,0x0},		/* $ */
{0x0,0x40,0xa2,0x44,0x8,0x10,0x20,0x44,0x8a,0x4,0x0,0x0},		/* % */
{0x0,0x30,0x40,0x40,0x20,0x60,0x92,0x94,0x88,0x76,0x0,0x0},		/* & */
{0x0,0x10,0x10,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},			/* ' */
{0x0,0x8,0x10,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x8},		/* ( */
{0x0,0x20,0x10,0x10,0x8,0x8,0x8,0x8,0x8,0x10,0x10,0x20},		/* ) */
{0x0,0x0,0x0,0x6c,0x38,0xfe,0x38,0x6c,0x0,0x0,0x0,0x0},			/* * */
{0x0,0x0,0x0,0x10,0x10,0x10,0xfe,0x10,0x10,0x10,0x0,0x0},		/* + */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x20,0x0},			/* , */
{0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x0,0x0,0x0,0x0,0x0},				/* - */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x0,0x0},				/* . */
{0x0,0x0,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x0,0x0,0x0},			/* / */
{0x0,0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x0,0x0},		/* 0 */
{0x0,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},		/* 1 */
{0x0,0x38,0x44,0x4,0x4,0x8,0x10,0x20,0x40,0x7c,0x0,0x0},		/* 2 */
{0x0,0x38,0x44,0x4,0x4,0x18,0x4,0x4,0x44,0x38,0x0,0x0},			/* 3 */
{0x0,0x8,0x18,0x18,0x28,0x28,0x48,0x7c,0x8,0x1c,0x0,0x0},		/* 4 */
{0x0,0x7c,0x40,0x40,0x40,0x78,0x4,0x4,0x44,0x38,0x0,0x0},		/* 5 */
{0x0,0x18,0x20,0x40,0x40,0x78,0x44,0x44,0x44,0x38,0x0,0x0},		/* 6 */
{0x0,0x7c,0x44,0x4,0x8,0x8,0x10,0x10,0x20,0x20,0x0,0x0},		/* 7 */
{0x0,0x38,0x44,0x44,0x44,0x38,0x44,0x44,0x44,0x38,0x0,0x0},		/* 8 */
{0x0,0x38,0x44,0x44,0x44,0x3c,0x4,0x4,0x8,0x30,0x0,0x0},		/* 9 */
{0x0,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x10,0x0,0x0},			/* : */
{0x0,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x10,0x20,0x0},			/* ; */
{0x0,0x0,0x0,0x8,0x10,0x20,0x40,0x20,0x10,0x8,0x0,0x0},			/* < */
{0x0,0x0,0x0,0x0,0x7c,0x0,0x7c,0x0,0x0,0x0,0x0,0x0},			/* = */
{0x0,0x0,0x0,0x20,0x10,0x8,0x4,0x8,0x10,0x20,0x0,0x0},			/* > */
{0x0,0x38,0x44,0x4,0x4,0x8,0x10,0x10,0x0,0x10,0x0,0x0},			/* ? */
{0x0,0x3c,0x42,0x9a,0xaa,0xaa,0xaa,0x9c,0x40,0x38,0x0,0x0},		/* @ */
{0x0,0x30,0x10,0x10,0x28,0x28,0x44,0x7c,0x44,0xee,0x0,0x0},		/* A */
{0x0,0xfc,0x42,0x42,0x42,0x7c,0x42,0x42,0x42,0xfc,0x0,0x0},		/* B */
{0x0,0x3c,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x3c,0x0,0x0},		/* C */
{0x0,0xf8,0x44,0x42,0x42,0x42,0x42,0x42,0x44,0xf8,0x0,0x0},		/* D */
{0x0,0xfe,0x42,0x40,0x48,0x78,0x48,0x40,0x42,0xfe,0x0,0x0},		/* E */
{0x0,0xfe,0x42,0x40,0x48,0x78,0x48,0x40,0x40,0xf0,0x0,0x0},		/* F */
{0x0,0x3c,0x42,0x80,0x80,0x80,0x8e,0x82,0x42,0x3c,0x0,0x0},		/* G */
{0x0,0xee,0x44,0x44,0x44,0x7c,0x44,0x44,0x44,0xee,0x0,0x0},		/* H */
{0x0,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},		/* I */
{0x0,0x3c,0x8,0x8,0x8,0x8,0x8,0x88,0x88,0x70,0x0,0x0},			/* J */
{0x0,0xe6,0x44,0x48,0x48,0x50,0x70,0x48,0x44,0xe6,0x0,0x0},		/* K */
{0x0,0xf8,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0xfe,0x0,0x0},		/* L */
{0x0,0xc6,0x44,0x6c,0x6c,0x54,0x54,0x44,0x44,0xee,0x0,0x0},		/* M */
{0x0,0xce,0x44,0x64,0x64,0x54,0x4c,0x4c,0x44,0xe4,0x0,0x0},		/* N */
{0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},		/* O */
{0x0,0xfc,0x42,0x42,0x42,0x7c,0x40,0x40,0x40,0xf0,0x0,0x0},		/* P */
{0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x36,0x0},	/* Q */
{0x0,0xfc,0x42,0x42,0x42,0x7c,0x48,0x48,0x44,0xe6,0x0,0x0},		/* R */
{0x0,0x7c,0x82,0x80,0x80,0x7c,0x2,0x2,0x82,0x7c,0x0,0x0},		/* S */
{0x0,0xfe,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x0,0x0},		/* T */
{0x0,0xee,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x0,0x0},		/* U */
{0x0,0xee,0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x0,0x0},		/* V */
{0x0,0xee,0x44,0x44,0x44,0x54,0x54,0x54,0x28,0x28,0x0,0x0},		/* W */
{0x0,0xee,0x44,0x28,0x28,0x10,0x28,0x28,0x44,0xee,0x0,0x0},		/* X */
{0x0,0xee,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x38,0x0,0x0},		/* Y */
{0x0,0xfe,0x84,0x8,0x8,0x10,0x20,0x20,0x42,0xfe,0x0,0x0},		/* Z */
{0x0,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38},	/* [ */
{0x0,0x0,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x0,0x0,0x0},			/* \ */
{0x0,0x38,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x38},			/* ] */
{0x10,0x28,0x44,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},			/* ^ */
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe},				/* _ */
{0x0,0x20,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},			/* ` */
{0x0,0x0,0x0,0x0,0x78,0x4,0x7c,0x84,0x84,0x7a,0x0,0x0},			/* a */
{0x0,0xc0,0x40,0x40,0x7c,0x42,0x42,0x42,0x42,0xfc,0x0,0x0},		/* b */
{0x0,0x0,0x0,0x0,0x7c,0x82,0x80,0x80,0x82,0x7c,0x0,0x0},		/* c */
{0x0,0xc,0x4,0x4,0x7c,0x84,0x84,0x84,0x84,0x7e,0x0,0x0},		/* d */
{0x0,0x0,0x0,0x0,0x7c,0x82,0xfe,0x80,0x82,0x7c,0x0,0x0},		/* e */
{0x0,0x18,0x20,0x20,0x78,0x20,0x20,0x20,0x20,0x78,0x0,0x0},		/* f */
{0x0,0x0,0x0,0x0,0x7e,0x84,0x84,0x84,0x7c,0x4,0x4,0x78},		/* g */
{0x0,0xc0,0x40,0x40,0x58,0x64,0x44,0x44,0x44,0xee,0x0,0x0},		/* h */
{0x0,0x10,0x0,0x0,0x70,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},		/* i */
{0x0,0x8,0x0,0x0,0x78,0x8,0x8,0x8,0x8,0x8,0x8,0x70},			/* j */
{0x0,0xc0,0x40,0x40,0x4c,0x48,0x50,0x70,0x48,0xc6,0x0,0x0},		/* k */
{0x0,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},		/* l */
{0x0,0x0,0x0,0x0,0xe8,0x54,0x54,0x54,0x54,0xd6,0x0,0x0},		/* m */
{0x0,0x0,0x0,0x0,0xd8,0x64,0x44,0x44,0x44,0xee,0x0,0x0},		/* n */
{0x0,0x0,0x0,0x0,0x7c,0x82,0x82,0x82,0x82,0x7c,0x0,0x0},		/* o */
{0x0,0x0,0x0,0x0,0xfc,0x42,0x42,0x42,0x42,0x7c,0x40,0xe0},		/* p */
{0x0,0x0,0x0,0x0,0x7e,0x84,0x84,0x84,0x84,0x7c,0x4,0xe},		/* q */
{0x0,0x0,0x0,0x0,0xec,0x32,0x20,0x20,0x20,0xf8,0x0,0x0},		/* r */
{0x0,0x0,0x0,0x0,0x7c,0x82,0x70,0xc,0x82,0x7c,0x0,0x0},			/* s */
{0x0,0x0,0x20,0x20,0x78,0x20,0x20,0x20,0x24,0x18,0x0,0x0},		/* t */
{0x0,0x0,0x0,0x0,0xcc,0x44,0x44,0x44,0x4c,0x36,0x0,0x0},		/* u */
{0x0,0x0,0x0,0x0,0xee,0x44,0x44,0x28,0x28,0x10,0x0,0x0},		/* v */
{0x0,0x0,0x0,0x0,0xee,0x44,0x54,0x54,0x28,0x28,0x0,0x0},		/* w */
{0x0,0x0,0x0,0x0,0xee,0x44,0x38,0x38,0x44,0xee,0x0,0x0},		/* x */
{0x0,0x0,0x0,0x0,0xee,0x44,0x44,0x28,0x28,0x10,0x10,0x60},		/* y */
{0x0,0x0,0x0,0x0,0xfc,0x88,0x10,0x20,0x44,0xfc,0x0,0x0},		/* z */
{0x0,0xc,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0xc},		/* { */
{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},	/* | */
{0x0,0x60,0x10,0x10,0x10,0x10,0xc,0x10,0x10,0x10,0x10,0x60},	/* } */
{0x0,0x0,0x62,0x92,0x8c,0x0,0x0,0x0,0x0,0x0,0x0,0x0},			/* ~ */
{0x0,0x0,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x0},		/* 127 */
};