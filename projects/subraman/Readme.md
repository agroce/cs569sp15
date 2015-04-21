CS-569 Static Analysis and Model Checking
===========================================
Assignment: Verification Using CBMC
---------------------------------------------
By Nitin Subramanian (ONID:subraman  OSUID:932287331)

Code Specifics:
---------------
[Implementation of Queue using Arrays in C](https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Queue_Implementation.c)
I chose this code since I wanted to see CBMC behaviour with switch statements.
Code was a showcase of simple operations such as Insert,Delete and Display performed on a Queue.
Operation is performed based on choice of the user:

1. Inserting Input value to the Queue.
2. Deleting First in Queue Value.
3. Displaying Current Queue.

The [Good Harness Code](https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Harness_Good.c) that I wrote for the Queue Verification [Verified Successfully](https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Result_Good_WithNoBound.txt) without Bound/Pointer Check Conditions. 
But it threw upper bound violations on front and rear pointer variables when those conditions were included. Thus I had to change the bounds before I could proceed further and CBMC was a lot friendly to me in that debugging task.It finally helped me get [Verified Successfully]((https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Result_Good_WithBound.txt).)

Assertions and Assumptions:
--------------------------
I had to assume the range of choice for Queue operation due to the swith structure and hence I assumed a range for choice variable.
While I tried insertion od non deterministic values to queue it sometimes went into infinite loopings due to egative value assignations hence I had to assume them to be positive integers.

Assertions were mainly focussed on the 2 pointer variables front and rear and their value updations. One main condition I had to assert to avoid Infinite loops and not checking further assertions is that the rear value should never be more that MAX bound specified. Till I asserted that there were a lot of problems with changes in Fron and Rear pointer values.
I had to also assert the Queue Overflow and Underflow conditions to make sure Queue Operations were accurate.

I wanted to check for swapping of values while deletions using assert operations but I could not succeed in finding an appropriate assertion combination for it.
However I did it manually on different ranges and it seemed to be correct to me.

Verification Time Comparison:
----------------------------
For MAX bound value of 15 and unwind value of 25 it took CBMC about 12.001seconds to verify without Bound/Pointer conditions.
Apparantly the time consumed was more when I included the conditions taking about 15.559seconds for it. 
Similarly for MAX 10 and unwind 21 it took 2.7585 seconds and 5.5898seconds respectively.
Also while comparing time I noticed that there were more number of Variables, Clauses and Verification Conditions(VCCs) along with conditions after reduction when we include Bound/Pointer conditions compared to when we do not include them.

Bug Identification:
---------------------------
I tried inserting quite a few bugs in my [Bad Harness Code](https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Harness_Bad.c) and CBMC caught the violations each time.
I could not manage to work through a bug for these simple operations that could complicate things for CBMC to figure out. It gave me [Verification Failed](https://github.com/agroce/cs569sp15/blob/master/projects/subraman/Result_Bad.txt) each time I inserted singe order bugs.
