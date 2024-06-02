# BigTrak
BigTrak logic core for hobby robots

*not for military use*

This is an atmega328 based system that mostly emulates a Bigtrak programmable robot.
If you want to use it you will probably need to do some adjustments.

functions.h has all the actual functions in it that do things, like turn the motors on and off.

The program is configured to use a DV-HT111 IR ermote for programming.
I do have a verion that accepts the programming via serial that can come from an esp8266 srving a
webpage with a PNG that is based on the actual Bigtrak control panel.

All the operation is done via a LUT based state machine. Modifying that state machine is a whole otehr project

(I'm willing to share if you really think you want me to)

----


keys:

forward     move the robot forward(units 0-99 (robot length))

reverse     move the robot reverse(units 0-99)

left        turn the robot left (units 0-99 (3 degrees))

right       turn the robot right (units 0-99)

pause       delay for (units 0- 99 (1/10 second))

acc         active the robot accesory device (your choice)

party       play a music tune

repeat      repeat the last command (times)


clearMem    clear the program memory

delCmd      delete the last command

check       execute the last command entered into program memory

go          run the program

0           valid numbers to enter...        
1        
2        
3        
4        
5        
6        
7        
8        
9        
         

The beeper will give you feedback. It does a different beep for "command ok", "digit ok", and "error".

This system is slightly more capable than the origional bigtrak was.

have fun!

I wrote this a while ago now... 2022, I might have to dig a bit if you ask questions.


Rue 

