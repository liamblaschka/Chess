# Chess

## Description
A chess game made in C++ using SFML. The code includes concepts such as object-oriented programming and recursive functions.
The game functionality includes rules such as check, checkmate, draw by stalemate, draw by insufficient material, castling, en passant and pawn promotion, as well as the general rules for moving each of the pieces.

### Skills
- C++
- Object-Oriented Programming
- SFML

## Instructions
### To use:
- When running the game, it will open with the board set up with it being white's turn first.
- To make a move, click the piece you want to move to select it, the squares of the possible moves for that piece will be highlighted. To then make the move, click any of the available moves with the piece selected.
- Pawn promotion is handling in terminal, when a pawn is moved to the end of the board, the player is prompted to enter the piece they wish to promote to. 
- Checks, wins and draws are outputted into the terminal.

### To build:
- Make a build directory and within it run 'cmake ..' , then when it is finished, run 'make'.
- Navigate to the bin directory within build.
- Run the 'chess' executable.




To make a move click on a piece and the squares of the available moves will be highlighted, clicking any of these squares will then make the move, after which it is the opposite colour's turn to make a move.

## Preview images
<div align="center">
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Chess/start.png?raw=true">
  <p>The board is set up in starting position when running the game. It is starts as white's turn.</p>
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Chess/select_piece.png?raw=true">
  <p>
    It is whites turn, clicking a white piece highlights the available moves,<br>
    clicking a highlighted square will then make the move.
  </p>
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Chess/check.png?raw=true">
  <p>
    Black's king is in check from the white queen demonstrated by the orange box around the king and the output in terminal.<br>
    The black queen is selected showing its available moves, where its only option is to block the check.
  </p>
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Chess/checkmate.png?raw=true">
  <p>
    White's king is checkmated and black wins, demonstrated by the orange box and the message in terminal.<br>
    No more moves can now be made as the game is over.
  </p>
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Chess/stalemate.png?raw=true">
  <p>
    The game ends in stalemate as it is black's turn, black's king is not in check, and black cannot make any moves<br>
    as their only piece, their king, is trapped by white's queen.
  </p>
</div>


