# Computers Can Play Tetris
## With a program what I wrote
### In sub-standard C++

Yeah, I'm not good at C++. Deal with it. Actually don't deal with it, yell at me until I fix my problems. Anyway, Tetris, because theaigames is doing it.

So the obviously optimal way, performance-wise, to have a Tetris bot would be to have just a gamestate-to-action table that we made after looking all the way to the end of the game (or until we hit a closed loop of actions, or surpass the number of moves possible within the lifetime of the universe, which is the best kind of the end of the game). But, like, there's 2<sup>200</sup>*7 gamestates (containing the configuration of blocks and the next piece), and I don't got no hope of htat much time for the processing or that the client computer'll have that much space, so, like that's not such a great idea. I was totally thinking that we might kinda have a smaller lookup table for likely gamestates and if that doesn't work, then we can go into the calculate-y bits and hell, theaigames already gave us like a half-second in our timebank for every basically-no-time lookup. Klingt das wie ein gut Gedanke, mein Computerfreund?
