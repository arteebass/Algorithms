using System;
using System.Collections.Generic;
using System.IO;
class Solution {
    static void Main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution */
        int a = Convert.ToInt32(Console.ReadLine());
        int b = Convert.ToInt32(Console.ReadLine());
        int c = Convert.ToInt32(Console.ReadLine());
        int d = Convert.ToInt32(Console.ReadLine());
        long f = fib(d, a, b, c);
        Console.WriteLine(f);
    }
    static long fib(int n, int a, int b, int c){
        long f0 = a;
        long f1 = b;
        long f2 = c;
        if (n<=2){
            return 1;
        }
        int i = 3;
        long currentF = 0;
        while(i <= n){
            currentF = 3*f0 + 2*f1 + f2;
            f0 = f1;
            f1 = f2;
            f2 = currentF;
            i++;
        }
        return currentF;
    }
}