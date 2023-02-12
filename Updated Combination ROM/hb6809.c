#include <cmoc.h>
#pragma limit 0x7EAA  		// start ASSIST09 reserved memory starts here
//#pragma limit 0x7E3A		// start TRACE reserved mem starts here
//#pragma limit 0x7E2A		// start DISSASEMBLER reserved mem starts here
//#pragma limit 0x7FFF		// end of memory 32k 


// 0x7FFF can potentially overwrite the monitor which we are useing bootstrap 
// memory, and load the code TRACE / DISSASEMBLER are reloaded from soft start 
// so safe to overwrite. (unless you want to use them to debug.)
//

// the HB6809 custom combo rom moves the reserved space to the very end of memory
// removing the 4k gap in the tranter rom.  this leaves a contiguious 32049 bytes
// of RAM for programs! (slightly less if you need the debugger to remain memory
// resident -- see break points above) 

// Extended Basic uses this space, future use if we can get CMOC to load the 
// floating point routines from ROM this will be needed. otherwise org can be 0.

#pragma org 0x179 

//  Load this program at the ASSIST09 prompt using 'L'
//  NOTE: Minimal ACIA card needs a line delay of 200 ms & a 10 ms char delay
//  start this program as 'G 179'
//  potentally loading code over a saved space will cause issues. 

// ASSIST09 SYSTEM CALLS USED
#define OUTCH	1		// sends a character to the terminal
#define MONITR	8		// soft start ASSIST09

// lets redirect printf... assist09 has a built in character output
void newOutputRoutine(void) {
	char ch;
	asm {
		pshs 	x,b	// save registers swi handler uses them 
		swi
		fcb 	OUTCH	// system call to ASSIST09
		puls	b,x    	// put them back
	}
}

// call the monitor to softstart...
void softStart(void) {
	asm {
		swi
		fcb	MONITR	// system call to ASSIST09
	}
}




// we are trying to use the standard lib to output to acia
int main() {
	// console redirect --- this is copy paste from CMOC Manual
    setConsoleOutHook(newOutputRoutine);
    
	// If this printf is overwriting at the newline, use --flex --srec at
	// compile time.  CMOC defaluts its target to CoCo/Dragon which
	// only sees <CR> and passes it as CR/LF instead. (as i understand it)

	
    
	printf("Hello, World \n");

	
	softStart();

	return(0);
}

