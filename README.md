# RubiksSolver  

This program outputs the moves to the user that are required to solve a Rubiks Cube (More in-depth below). This is not meant to be the fastest or most efficient way to solve a rubiks cube, but rather, I turned the most basic method into code. This project was created entirely from scratch by me.  

## How To Use:
1. Open program and select whether you would like to load a cube layout from a config file  
  a. This step was most useful for the debugging/testing process as I could save my starting layout to test new methods  
  b. The config file must be in the same file as the program and named "cube_config.txt"  
  c. The format of the config file is the capitol letter abbr. of the piece colors  
    c.1. The order of the pieces goes row by row, left to right, along a given face  
    c.2. The face order goes: Top (White), Bottom (Yellow), Front (Red), Back (Orange), Left (Green), Right (Blue)  
2. If you choose to not use a config file (Most likely the case), you will be asked to input each piece color  
  a. The console will give the prompt "FACE COLOR" ["ROW"]["COLUMN"]  
  b. The program expects either the full color name or the first letter with case not mattering (Ex. "White" or "w")  
  c. After the manual layout is taken, the program will ask if you want to save this to a config file. Refer to step 1 for more info.  
3. The program will then attempt to solve the cube!  
4. Hold your cube with Red as the front face and White as the up face when following the output moves.  
5. If there are any errors when solving, please create an issue and send your cube config along with it. Thanks :)  

## How To Read Output:  
The output will consist of capitol letters that may have an "'" following them.  
The letters represent the side of the cube that will be moved. Below are all of them listed:  

U - Up (White)  
D - Down (Yellow)  
F - Front (Red)  
B - Back (Orange)  
L - Left (Green)  
R - Right (Blue)  

If you see an "'" after a letter, it means that the move is "prime".  
What this means is that instead of moving the indicated face CLOCKWISE, you will move it COUNTER-CLOCKWISE.  
If you are having trouble, flip the cube until you have the indicated face pointed towards you, and then do the CLOCKWISE or COUNTER-CLOCKWISE move.  
Alternatively, you can use this program along side any basic Rubiks Cube solving video as it follows most of the moves that will be performed in the video.  

## Future Ideas:  
- Make some optimizations (Remove moves that cancel each other out)  
- Add OpenCV  
