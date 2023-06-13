# Rock-Paper-Scissors
It's A Rock-Paper-Scissors Game

The game is rock paper scissors, where rock, paper, and scissors are denoted using LEDs on the right side of the board, and your opponent is denoted using mirrored LEDs on the left side of the board. This is traditional Rock-Paper-Scissors where paper covers rocks, rock crushes scissors, and scissors cut paper. You can choose between rock paper and scissors using the left and right buttons on the board to switch the states, and once a selection has been made, the user will touch the nail/touch sensor to signify that they are ready. The randomizing program will begin, and depending upon the outcome, the person will win, lose, or draw, with an accompanied sound and voice memo for each.

Inputs:

Left Button - Move forward; Rock -> Paper -> Scissors

Right Button - Move backward; Scissors -> Paper -> Rock

Switch: Turn the Game on And off

“Touch Sensor” - Initiates the “Lock In” state where the player locks in their response, and the game starts to generate the opponent's response. Raw range is 0 -> 1021, map() makes it 0 - 50

Outputs:

LED0- Opponent Scissors - Light Blue

LED2 - Opponents Paper - Yellow 

LED4 - Opponents Rock - Orange

LED5 - User Rock - Red

LED7 - User Paper - Green

LED9 - User Scissors - White

Tune0 - Sound to indicate a win

Tune1 - Sound to indicate a loss

Tune2 - Sound to indicate a draw

VoiceMemo0 - Voice memo to indicate a win

VoiceMemo1 - Voice memo to indicate a loss

VoiceMemo2 - Voice memo to indicate a draw
