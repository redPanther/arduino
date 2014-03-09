this is for the Seeeduino Mega Board
====================================

The arduino software didn't support the additional pins from seeed mega board.
This patch will change this.

how to use:
 - locate your direktory of your arduino ide (for me: /usr/share/arduino)
 - cd int 'hardware' folder and open boards.txt
 - add content of my borads.txt to the original file
 - copy seeeduino folder from hardware/arduino/variants to your local hardware/arduino/variants folder
 
After restarting your arduino ide select the board "Seeeduino Mega 2560" and use all the new pins :-)


 