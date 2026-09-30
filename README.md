# Twixt (C)

A two-player, terminal-based implementation of the classic **Twixt** board game, written in C. Players take turns placing pegs on a 25×25 board; pegs of the same colour a knight's move apart are linked automatically, and the first player to build an unbroken chain across the board wins.

## Rules

- **Red** connects the **top row to the bottom row**; **Black** connects the **left column to the right column**.
- Pegs are placed at `(row, col)` with both indices in `0–24`. The four corners are unusable.
- Red cannot place pegs in the left/right edge columns, and Black cannot place pegs in the top/bottom edge rows.
- When you place a peg, a link is created to every friendly peg a chess-knight's move away, **unless** the new link would cross an existing link (yours or your opponent's).
- A player wins when their linked pegs form a continuous path between their two edges.

## Build and run

Requires `gcc` and `make`.

```bash
make        # build
make run    # build and start the game
make clean  # remove build artifacts
```

## Commands

| Command | Action |
| --- | --- |
| `place <row> <col>` | Place a peg for the current player |
| `view board` | Print the board |
| `view links` | List all Red and Black links |
| `view guide` | Show rules and commands |
| `reset` | Clear the board and restart (Red starts) |
| `exit` | Quit |

## How it works

| File | Responsibility |
| --- | --- |
| `src/main.c` | Command loop, input parsing, turn handling |
| `src/board.c` | Board state, peg placement, automatic link creation, board printing |
| `src/game.c` | Knight-move link validation, segment-intersection test (orientation method), win detection via depth-first search over links |
| `include/*.h` | Shared types (`Board`, `Link`, `Linkdata`, `Player`) and prototypes |

- **Crossing detection:** two links cross if the endpoints of each lie on opposite sides of the other (orientation / cross-product test). Links that share an endpoint are allowed.
- **Win detection:** a DFS starts from every peg on the player's starting edge and follows only existing links; the player wins if it reaches a peg on the opposite edge.

## Possible improvements

- Add a swap rule / pie rule and an AI opponent.
- Render the links on the board rather than listing them.
- Replace fixed-size link arrays with dynamic allocation.
