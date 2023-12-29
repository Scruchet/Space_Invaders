# Space Invaders

Welcome to the game of the year 2023. If you're here, it's to have fun and enjoy your time. Here are some pieces of information you need to get the game up and running.

## Controls, Configuration, and Installation

To play the game, you need to have SDL installed on your computer. To do that you can execute those three commands:

```bash
sudo apt-get upgrade
sudo apt install libsdl1.2-dev
sudo apt install libsdl-ttf2.0-dev
```

### Controls
The controls are very simple. By default, the 'q' key is to move left, the 'd' key is to move right, and the 'm' key is to launch a missile. If these keys don't suit you, you can change them by following the configuration chapter.

### Configuration
You can configure the number of invaders, the speed of mob movement, and many other factors to make the game more enjoyable for you by looking at ```const.h```

### Installation

After configuring the game to your preferences, you'll need to execute the Makefiles.  To do this, go to the root of the project folder. Then execute these commands:
```bash
make
```
If you have modified certain parameters in the const.h file after running the installation commands, then you need to redo the following commands at the root of the project:

```bash
cd src
make clean
make format
make
```
Cela prendra vos modifications en compte et vous permettra de jouer au jeu avec d'autres paramétres.

## Running the Game!

For this, nothing could be simpler. Once you have completed the installation step, to run the game, type the following commands at the root of the project:
```bash
cd src
./main
```
The game should launch. You can exit the game by clicking the close button in the top right or by pressing CTRL + C in the terminal.

# Conctact
Thank you for visiting my project. If you have any comments or questions, please feel free to contact me via email at the following address: cruchetsimon@gmail.com

