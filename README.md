TODOs:
- Heuristics may need additional parameter (roughness is probably needed)
    (can be copied from daniel_devel branch  class: HeuristicsExplorer mehod: updateTempMoveboardHeights )

- The bombs functions need a revision, one function inside the TetrisGame is double for loops, and inside another functions from Tetromino required another double for loops
(Due to the bomb's rotational capabilities, it is imperative to determine the specific cell it occupies. This is essential for ensuring that the ensuing explosion appropriately impacts the game board. Consequently, the algorithm iterates through the board's cells to facilitate this process.)
(feel free to rvise it however you see fit)

- Amir stated that free floating blocks may need to fall after an explosion, may require an elaboration.

- consider using static arrays for boardHeights and boardHoles
(board width is already known see:(1) no need to use vectors unless you want to modify them during runtime)
(1 C++ 2024A - MTA - Exercises -- Exercise 1 ).

- consider updating gameOverLogic to fit project requirements
(The current version of gameOverLogic fails to differentiate between games that conclude simultaneously, a crucial issue given the existence of a scoring system. This oversight may lead to point deductions. Consider updating the logic to match the capabilities of previous versions or, alternatively, contemplate the removal of the scoring system altogether to address this challenge.)

- uestimateBestMove revision may be needed
(The current implementation of estimateBestMove relies on assignTransform to simulate drops from every x position. However, it overlooks the  step of verifying if the position is reachable. Consequently, the algorithm may calculate scores for moves that cannot be played on the board. For instance, attempting to simulate a drop of a piece from the coordinates (y=0, x=1) when there's an occupied cell at (y=0, x=3) may lead to erroneous results. It is advisable to enhance the implementation by incorporating a check for the accessibility of the target position to ensure accurate scoring and prevent calculations for unreachable moves.)
