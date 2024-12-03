using System;
using System.Threading;
using static System.Console;

namespace _03._12._24.Архитектура_Аппаратных_Средств_Триггеры
{
    internal class Program
    {
        static void Main(string[] args)
        {

            /*// 7 задание

            int[] signals = { 1, 0, 1, 1, 0, 1 };

            int T1 = 0, T2 = 0, T3 = 0;

            Console.WriteLine("Input | T1 | T2 | T3");
            WriteLine("owo uwu owo uwu owo");

            foreach (int i in signals)
            {
                int T11 = T1; int T22 = T2; int T33 = T3;

                if (i == 1)
                {
                    T1 = T11 == 0 ? 1 : 0;
                }

                if (T11 != T22 && i == 1)
                {
                    T3 = T33 == 0 ? 1 : 0;
                }

                if (T11 == 1 && i == 0)
                {
                    T2 = T22 == 0 ? 1 : 0;
                }
                


                //WriteLine(Convert.ToString(i) + " T1 =" + T1 + " T2 = " + T2 + " T3 = " + T3);
                WriteLine($"{i}     | {T1}  | {T2}  | {T3}");

            }*/


            // 9-ое задание

            Console.WriteLine("Input | T1 | T2 | T3 | T4 | T5");
            WriteLine("\nowo uwu owo uwu owo uwu owo");

            int[] signals = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1 };

            int T1 = 0; int T2 = 0; int T3 = 0; int T4 = 0; int T5 = 0;
            int count1 = 0; int count2 = 0; int count3 = 0; int count4 = 0; int count5 = 0;

            foreach (int X in signals)
            {
                
                int T11 = T1; int T22 = T2; int T33 = T3; int T44 = T4; int T55 = T5;

                if (X == 1 || T55 == 1) // T1
                {
                    T1 = T11 == 0 ? 1 : 0; 
                    count1 ++;
                }

                if ((T11 == 1 && X == 0) || (T33 == 1 && T44 == 0)) // T2
                {
                    T2 = T22 == 0 ? 1 : 0;
                    count2 ++;
                }

                if ((T11 != T22 && X == 1) || (T55 == 0)) // T3
                {
                    T3 = T33 == 0 ? 1 : 0;
                    count3 ++;
                }

                if ((T33 == 1 && X == 1) || (T11 == 1 && T55 == 1)) // T4
                {
                    T4 = T44 == 0 ? 1 : 0;
                    count4 ++;
                }

                if ((T44 == 1 && X == 0) || (T22 == 1 && X == 1)) // T5
                {
                    T5 = T55 == 0 ? 1 : 0;
                    count5 ++;
                }

                WriteLine($"{X}     | {T1}  | {T2}  | {T3}  | {T4}  | {T5}");
            }
            WriteLine($"\nСчетчик: {count1}, {count2}, {count3}, {count4}, {count5}");
        }
    }
}
