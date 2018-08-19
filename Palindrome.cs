using System;
using System.Collections.Generic;
using System.IO;
class Solution {
    static void Main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution */
        string word = Console.ReadLine();
        int n;
        if(word == "" || word == null){
            n = 0;
        }else{
            n = word.Length;
        }
        char[] wordA = new char[n];
        for (int i=0; i<n; i++){
            wordA[i] = word[i];
        }
        bool firstChar = true;
        bool result = pal1(wordA, firstChar, 0, n-1);
        Console.WriteLine(result);
    }
    static bool pal1(char[] word, bool isFirst, int first, int size){
        if(size < 0){
            return false;
        }
        if (first == size){//for odd length strings
            return true;
        }else if(first == size-1){//for even length strings
            if(word[first] == word[size]){
                return true;
            }else if(isFirst){
                return true;
            }else{
                return false;
            }
        }
        if(word[first] == word[size]){
            return pal1(word, isFirst, first+1, size-1);
        }else if(isFirst){
            return pal1(word, false, first, size-1);
        }else{
            return false;
        }
        
    }
}