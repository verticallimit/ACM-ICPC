# CountStick
  There are n sticks lined up on a shelf.Each stick has a length,note that maybe two or more sticks have the same length.There are Q query,for each given query,you need to find the sum of the lengths of sticks which have different length between two given number l,r.Stick numbering starts from 1.
  


----------
## Input ##
  First line contains an integer T (T<=10),indecating the number of testcases.
  next line contains an integer n.(n<=20000)
  next line contains n integers,indecating n sticks' length.(0 <= length <= 1e8)
  next line contains an integer Q,indecating the number of query.(Q<=100000)
  next Q line,each line contains two integers l,r.(1 <= i <= j <=n)
  


----------
## Output ##
  output the sum for each query.
  


----------
## Sample Input ##
1
5
2 2 8 3 5
2
1 2
2 4


----------
## Sample Output ##
2
13
