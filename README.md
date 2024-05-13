# Chess

## Description
A chess game made in C++ using SFML. The code includes concepts such as object-oriented programming and recursive functions.
The game functionality includes rules such as check, checkmate, draw by stalemate, draw by insufficient material, castling, en passant and pawn promoting, as well as the general rules for moving each of the pieces.

## Instructions
To play the game run the chess executable, the game will start with the board set up and it will be white's turn first.
To make a move click on a piece and the squares of the available moves will be highlighted, clicking any of these squares will then make the move, after which it is the opposite colour's turn to make a move.

## Preview images
<div align="center">
  <img src="https://github.com/liamblaschka/chess/blob/images/start.png?raw=true" width="526" height="550">
  <p>The board is set up in starting position when running the game. It is starts as white's turn.</p>
  <img src="https://github.com/liamblaschka/chess/blob/images/select_piece.png?raw=true" width="526" height="550">
  <p>
    It is whites turn, clicking a white piece highlights the available moves,<br>
    clicking a highlighted square will then make the move.
  </p>
  <img src="https://github.com/liamblaschka/chess/blob/images/check.png?raw=true" width="856" height="550">
  <p>
    Black's king is in check from the white queen demonstrated by the orange box around the king and the output in terminal.<br>
    The black queen is selected showing its available moves, where its only option is to block the check.
  </p>
  <img src="https://github.com/liamblaschka/chess/blob/images/checkmate.png?raw=true" width="857" height="550">
  <p>
    White's king is checkmated and black wins, demonstrated by the orange box and the message in terminal.<br>
    No more moves can now be made as the game is over.
  </p>
  <img src="https://github.com/liamblaschka/chess/blob/images/stalemate.png?raw=true" width="858" height="550">
  <p>
    The game ends in stalemate as it is black's turn, black's king is not in check, and black cannot make any moves<br>
    as their only piece, their king, is trapped by white's queen.
  </p>
</div>


