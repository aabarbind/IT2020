/* Program to copy contents of a file into another file */
#include <stdio.h>
#include <dos.h>

void main()
       {
	union REGS inregs,outregs;
	struct SREGS sregs;
	char ch,infile[20],outfile[20],buffer[10]="Sanjivani.";
	int infilehandle,outfilehandle,c=1;

	printf("\n\tEnter input file name : ");
	scanf("%s",infile);
	printf("\n\tEnter output file name : ");
	scanf("%s",outfile);


	inregs.h.ah=0x3c; /* Create a new file */
	inregs.x.cx=0x00;
	inregs.x.dx=FP_OFF(outfile);
	sregs.ds=FP_SEG(outfile);
	int86x(0x21,&inregs,&outregs,&sregs);
	if(! outregs.x.cflag)
	   printf("\n\tNew file created sucessfully!!!");
	else
	   {
	    printf("\n\tError creating new file!!!!");
	    c=0;
	    }


	inregs.h.ah=0x3d; /* Open output file for writing*/
	inregs.h.al=0x01;
	inregs.x.dx=FP_OFF(outfile);
	sregs.ds=FP_SEG(outfile);
	int86x(0x21,&inregs,&outregs,&sregs);
	outfilehandle=outregs.x.ax;
	if(! outregs.x.cflag)
	   printf("\n\tOutput file opened sucessfully!!!");
	else
	   {
	    printf("\n\tError opening output file!!!!");
	    c=0;
	    }

	inregs.h.ah=0x3d; /* Open input file for reading*/
	inregs.h.al=0x00;
	inregs.x.dx=FP_OFF(infile);
	sregs.ds=FP_SEG(infile);
	int86x(0x21,&inregs,&outregs,&sregs);
	infilehandle=outregs.x.ax;
	if(! outregs.x.cflag)
	   printf("\n\tInput file opened sucessfully!!!");
	else
	   {
	    printf("\n\tError opening input file!!!!");
	    c=0;
	    }
	while(c>0)
	       {
		inregs.h.ah=0x3f; /* Read a character from input file */
		inregs.x.bx=infilehandle;
		inregs.x.cx=0x01;
		inregs.x.dx=FP_OFF(buffer);
		sregs.ds=FP_SEG(buffer);
		int86x(0x21,&inregs,&outregs,&sregs);
		c=outregs.x.ax;
		if(outregs.x.cflag)
		 {
			printf("\n\tError reading input file!!!!");
			break;
		 }

		inregs.h.ah=0x40; /* Write charater read to output file */
		inregs.x.bx=outfilehandle;
		inregs.x.cx=0x01;
		inregs.x.dx=FP_OFF(buffer);
		sregs.ds=FP_SEG(buffer);
		int86x(0x21,&inregs,&outregs,&sregs);
		if(outregs.x.cflag)
		 {
			printf("\n\tError writing output file!!!!");
			break;
		 }

	       }

	inregs.h.ah=0x3e; /* Close output file */
	inregs.x.bx=outfilehandle;
	int86x(0x21,&inregs,&outregs,&sregs);
	if(! outregs.x.cflag)
	   printf("\n\tOutput file closed sucessfully!!!");
	else
	    printf("\n\tError closing output file!!!!");

	inregs.h.ah=0x3e; /* Close input file */
	inregs.x.bx=infilehandle;
	int86x(0x21,&inregs,&outregs,&sregs);
	if(! outregs.x.cflag)
	   printf("\n\tInput file closed sucessfully!!!");
	else
	    printf("\n\tError closing input file!!!!");

	getch();
}