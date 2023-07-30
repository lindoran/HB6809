; 6809 detection program for the Asist09 asembly language monitor
; z flag will be set if 6809 and clear if 6309, then will soft start 
; the monitor. You can then check the status of the CC register with 
; 'R'.
    
    org $1000
    
    
    fdb    $1043           ;6309 COMD instruction (COMA on 6809)
    cmpb   1,S             ;not equal if 6309
    swi
    fcb    8               ; system call to ASSIST09
