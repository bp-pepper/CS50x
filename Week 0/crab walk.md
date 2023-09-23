# Crab Walk

- crab
- jump over obstacles (cages) moving from right to left
- scoring:
  - ~~time of run OR~~
  - obstacles jumped
- obstacle detection
- display score
- jump (.3 of height)

## Psuedocode

```text
start program
    crab on left 1/4 of screen

    func jump
        move crab vertically up and down
    func move_cage
        move cage incrementally across screen
        ?? increase speed based on score?
    func create_cage
        use cloning in scratch
        base frequency of clones on score

    variables
        int score
        bool gameOver

    loop
      create cage
      move cage from right side of screen to left
      detect collision between crab and cage
      IF collision
        THEN gameOver set to True
      ELSE
        continue moving cage until collision or reaches left side of screen


```

## Objectives

1. Your project must use at least two sprites, at least one of which must not be a cat.

    - Crab
    - Cage

2. Your project must have at least three scripts total (i.e., not necessarily three per sprite).

    - [x]

3. Your project must use at least one conditional, at least one loop, and at least one variable.

    - [x] Cond
    - [x] Loop
    - [x] Var

4. Your project must use at least one custom block that you have made yourself (via Make a Block), which must take at least one input.

    - Block: Move Cage (input is difficulty level to calculate speed)
