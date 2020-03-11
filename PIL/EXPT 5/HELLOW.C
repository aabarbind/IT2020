#include <stdio.h>
#include <dos.h>

void main()
{       union REGS inregs,outregs;
	struct SREGS sregs;
	char ch,infile[20],outfile[20],str1[]="ABCD";
	int infilehandle,outfilehandle;
	/*printf("\tEnter input file name : ");
	scanf("%s",infile);*/
	printf("\n\tEnter output file name : ");
	scanf("%s",outfile);

	outfile[9]=0;

	inregs.h.ah=0x3c; /* create file */
	inregs.x.cx=0x00;
	inregs.x.dx=FP_OFF(outfile);
	sregs.ds=FP_SEG(outfile);
	int86x(0x21,&inregs,&outregs,&sregs);


	inregs.h.ah=0x3d; /* open file */
	inregs.h.al=0x01;
	inregs.x.dx=FP_OFF(outfile);
	sregs.ds=FP_SEG(outfile);
	int86x(0x21,&inregs,&outregs,&sregs);
	outfilehandle=outregs.x.ax;
	if(! outregs.x.cflag)
	   printf("\n\tFile opened sucessfully!!!");
	else
	   printf("\n\tError opening file!!!!");

	inregs.h.ah=0x40; /* read file */
	inregs.x.bx=outfilehandle;
	inregs.x.cx=0x04;
	inregs.x.dx=FP_OFF(str1);
	sregs.ds=FP_SEG(str1);
	int86x(0x21,&inregs,&outregs,&sregs);



	inregs.h.ah=0x40; /* close file */
	inregs.x.bx=outfilehandle;
	int86x(0x21,&inregs,&outregs,&sregs);



	/*printf("\tGot character: %c",ch);*/
	getch();
}