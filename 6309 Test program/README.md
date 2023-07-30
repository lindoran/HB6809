This program assembles at $1000
Run in assist09 by loading with 'L' and typing:

G 1000

6809 detection program for the Asist09 asembly language monitor
z flag will be set if 6809 and clear if 6309, then will soft start 
the monitor. You can then check the status of the CC register with 'R'.

CC Flag determines which cpu 
  D9  --  6809  
  F8  --  6309
