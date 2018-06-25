# TakeStick
  There are n sticks lined up on a shelf.You are requied to take all the n sticks off.in each step,you can take a stick off the shelf or you can place the stick in the corresponding position on the shelf,but,only when the first k-2 sticks are all off and the (k-1)th stick is on,you can place the kth stick on the shelf.note that the first stick can be taken off or taken on in each step.
  For a given n,what's the minimum number of steps?
  


----------
## Input ##
  Each line contains a number n,the last line is 0. (n<1e10)
  


----------
## Output ##
  For each line,output a number s represent the minimum number of steps,for the answer maybe large,output s mod 201829.


----------
## Sample Input ##
1
2
3
4
201829
0


----------
## Sample Output ##
1
2
5
10
1
