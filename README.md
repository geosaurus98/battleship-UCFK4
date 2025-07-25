# Battleship on UC Funkit 4
## Setup:

    Connect Devices:
        Use two UC Funkit 4 devices, one for each player.
        Ensure both devices have IR sensors aligned for communication.
    Game Initialization:
        Load the Battleship program on both devices.
        Each player places three ships (2x1, 3x1, 4x1) on their 5x7 LED matrix during the setup phase by selecting coordinates.

## Game Rules:

    Objective: Sink your opponent’s ship by guessing its position on their board.
    Ship Size: Each player has 3 ships hidden on their board. Ships cannot overlap.
    Turns: Players take turns firing shots at coordinates on the opponent's board.
    Winning: The first player to hit all of the opponent’s ships wins.

## How to Play:
### 1. Placing the Ship:

    Use joystick to navigate across the 5x7 matrix and position your ships.
    Press the joystick button to rotate placement.
    Confirm placement with button click.

### 2. Firing a Shot:

    Take turns selecting coordinates on your opponent’s matrix.
    Use the joystick to move a target on the grid.
    Press the joystick button to fire a shot at the selected position.

### 3. Processing the Shot:

    If your shot hits the ship, your screen shows “H”.
    If you miss, it shows “M”.
    The opponent’s board updates the shot as:
        Hit: LED blinks.
        Miss: LED lights up steadily.

### 4. Game End:

    Winner: If first to sink all opponents ships, your screen shows “WINNER”.
    Loser: The other player sees “LOSER”.
    IR communication will notify the loser automatically.

### Thank you
    Thank you for playing,
    Created by;
    George Johnson and Daniel Cayford
