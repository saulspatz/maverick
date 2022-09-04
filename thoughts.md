                                                               Thoughts on Maverick Poker



There are some 477 trillion possible 25-card deals.  Symmetries reduce this to some 19.9 trillion deals.  There are 102 different hand distributions, from 13-12 to 7-6-6-6.  I classify the deals into 10 different "schemes", where a scheme is like a rhyme scheme.  ABCD indicates four suits of different (decreasing) lengths, and AABC indicates that Spades and Hearts have the same lengths, and Diamonds and Clubs have two different lengths.  We would have 

Spades $\ge$ Hearts > Diamonds > Clubs.

My experience with the problem indicates that we need to use heuristics, where applicable, before resorting to exhaustive search.  The most valuable heuristic is that, when each suit has at least five cards, one should try to remove just enough cards from each suit to leave a flush, and use the five cards removed to make a pat hand.  This heuristic applies to fully fifty percent of all hands.  I think that this heuristic needs to be tailored to specific distributions.  For certain distributions, like 7-6-6-6, we should first try to make the fifth hand a full house.  This is easy to check and has a very high probability of success.    I think there are also a lot of cases where there is only one suit of less that 5 cards that would benefit from a heuristic.  I need to do more research on this.

I have a Maverick solitaire game that I've been playing in order to get an idea about the heuristics.  I should make a clone that allows me to set the suit distribution so that I can try to develop heuristics for specific distributions.

Some distributions occur so rarely that it wouldn't be worthwhile to develop a heuristic; we'd go straight to exhaustive search.  In the past, I've tried two different exhaustive search method.  One was Knuth's dancing links.  The other was to count for each card, the number of pat hands in which it occurs.  Then I sorted the deal in increasing order of this number, and tried to find five pat hands that would over the deal.  I experimented with adjusting the counts and resorting the after each choice of a hand.  I think this turned out to be slower, but I was using quick sort.  Timsort might give much better results.  

Both these methods require generating all possible pat hand that can be made from the deal, and if there is no solution, there's no way to avoid this.  But, of course, around 98% of the deals have a solution, so we should look for a less expensive way of looking for a pat hand if the heuristic fails.  For example, suppose I haven't been able to find a good heuristic for the 9-8-6-2 distribution.  Does it make sense to generate all the pat hands immediately?  Say that the 2 Clubs can't occur in the same straight.   Would it be better to construct all the pat hands that contain one of the clubs and check if any two containing both Clubs also comprise 4 Spades, 3 Hearts and a Diamond?

I'm using C.  There will be a distinct program for each of the 102 distributions.  Program will have a hard-coded array of function pointers.  It will have a parallel array of booleans, indicating which tasks
have been completed.  To allow for stopping and restarting, the program will read the list of completed tasks from a file at startup.  The main program will fork four children, with two-ways pipes to all of them.  The parent will assign the next uncompleted task to each worker in turn, and the worker will call the appropriate progrm.  When the worker completes the task, it will write the results to the pipe.  The parent will periodically read the pipes.  If a task has been completed, the parent will record the results and send the worker a new task.  If all tasks have been assigned, the aprent will signal the worker to stop.  When all tasks have been completed, the program will exit.

To allow for interruption, the workers will periodically log their progress.  The log will have a name that encodes the distribution.  When a worker is assigned a task, it will check if a log file with that name exists.  If so, it will will read it to dtermine how to resume the calculation.

The sleep interval for the parent should be a variable.  Early in the process, when the long taks are running, it will be fine if the parent wakes up once every few hours.  Later on, when smaller tasks are running, the interval should be much shorter.

The big data strcutures, namely the suit distributions and the facilities for exhaustive search can be in global memory, since the children get their own copies.  

Is it really necessary to have all these suits?  Can I make do with just the bitsets?  If so, all the suits for a particular distribution will easily fit in L1 D-cache which is 64 KiB on my laptop.  There would be a slowdown in the setup for exhaustive search, but the hope is to avoid this for the majority of deals.  If this turns out to be feasible, and more efficient, what about using pointers instead of array indices.  I couldn't use easily pointers when the suits were distinct, because determinig if the Hearts were better than the Diamonds say, when both suits had the same length would have been too expensive, but if they were the same suit, it would just be a pointer comparison.  It seems like switching to pointers is a no brainer. It certainly won't be slower, and it won't complicate the code much.


 
