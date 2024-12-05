using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using static System.Console;

namespace Метод_Прямоугольника_04._12._24
{
    internal class Program
    {
        static void Main(string[] args)
        {
            double E = 0.00001;
            MethodRectangle methodRectangle = new MethodRectangle();

            Console.WriteLine($"Промежуток между точками на графике = {methodRectangle.integralStep}");
            Console.WriteLine($"IIntegral_Xs: {methodRectangle}");
        }
    }

    class MethodRectangle // Счетчик шагов - доп. задание.
    {

        public double integralMax; public double integralMin;
        public double integralStep; public double integralStep2;
        private double n; private double n2;

        private bool _permission = false; // чтобы жизнь малиной не казалась.

        public List<double> IIntegral_XS_Numbers;


        public MethodRectangle() // Для Правила Рунге нужно ввести вторую I
        {
            WriteLine("Введите данные для интеграла: [min] -> [max]");
            WriteLine("[max]:");
            integralMax = Convert.ToDouble(ReadLine().Replace('.', ','));
            WriteLine("[min]:");
            integralMin = Convert.ToDouble(ReadLine().Replace('.', ','));

            Console.WriteLine("Введите колличество ЦЕЛЫХ 'n':");
            n = Convert.ToDouble(ReadLine());

            Console.WriteLine("Введите колличество ЦЕЛЫХ 'n2' (для второй I2):");
            n2 = Convert.ToDouble(ReadLine().Replace('.', ','));

            /*if (n <= 0 || n2 <= 0) // я люблю хардкодить.
                Console.WriteLine("Ошибка, колличество точек должно быть положительным [>0] заданным числом.");
            else
                _permission = true;*/

            integralStep = ((integralMax - integralMin)) / n;

            integralStep2 = ((integralMax - integralMin)) / n2;

            IIntegral_XS_Numbers = new List<double>();

        }

        // I1

        public void Integral_XS()
        {

            for (double i = 0; i < integralMax; i += integralStep)
            {
                IIntegral_XS_Numbers.Add(i);
            }

        }

        public void LeftRectangle()
        {

            foreach (double i in IIntegral_XS_Numbers)
            {

            }

        }

    }
}
