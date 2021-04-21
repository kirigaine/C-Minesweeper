# C-Minesweeper

## Description

C-Minesweeper is a text-based version of Minesweeper. Use guesses and logic to reveal the board without hitting a mine!

## Installation

You will need the gcc compiler in order to compile and run this program.
```bash
gcc -std=c99 minesweeper.c
```

## Usage

1. Run the executable with desired settings as parameters
   - ```./a.out numberOfRows[2-100] numberOfColumns[2-100] difficulty[1-10]```
2. Input coordinates of a guess that *shouldn't* be a mine, then hit enter (e.g. ```2 5```)
   - Note: You can input coordinates one at a time, should you desire (i.e. your keyboard input could be ```2 ENTER 5 ENTER```)

## Known Issues

1. Non-numeric input causes the program to get stuck in an infinite loop. I may fix this in the future, but I recommend avoiding it just incase.

## Contributing

No contributions are wanted for this project.

## Authors and acknowledgment

Kirigaine - Developer

## License

[MIT](https://choosealicense.com/licenses/mit/)

## Project Status

***This is an upload of an old project (10/31/18)***. It is no longer being developed or maintained.
