using System;
using System.Collections.Generic;
using static System.Console;

namespace ЧисленныеМетодыСимпсонГомер
{
    internal class Program // 6 вариант
    {
        static void Main(string[] args)
        {
            // I1 (Fxi)
            Simpson simpson = new Simpson();
            simpson.Output_XS(); // Вычисление x-ов в промежутке интеграла
            simpson.ListFor_Fxi();
            simpson.FXDX();

            WriteLine("Для ПЕРВОЙ I n-ой");
            WriteLine($"\nh = {simpson.Output_H()} [это b-a / n]");
            WriteLine($"\nВсе значения xi: [Всего x-ов i: {simpson.IPrototypeList.Count + 1}]");

            foreach (var value in simpson.IPrototypeList)
                WriteLine(value);

            WriteLine($"X2n = {simpson.MaxLimit}");
            WriteLine("\nВсе значения f(xi) для :");

            foreach (var value in simpson.IEquationList)
                WriteLine(value);

            // I2 (Fxi)
            WriteLine("\n\nДля ВТОРОЙ I n-ой");
            simpson.OutputXS_I2();
            simpson.ListFor_Fxi_I2();
            simpson.FXDX_I2();

            WriteLine($"\nh = {simpson.OutputH_I2()} [это b-a / n]");
            WriteLine($"\nВсе значения xi 2-ой I: [Всего x-ов i: {simpson.IPrototypeList2.Count + 1}]");

            foreach (var value in simpson.IPrototypeList2)
                WriteLine(value);

            WriteLine($"X2n = {simpson.MaxLimit}");
            WriteLine("\nВсе значения f(xi) для 2-ой I:");

            foreach (var value in simpson.IEquationList2)
                WriteLine(value);

            // ответ
            WriteLine($"\n f(x)dx, при {simpson.N}, для {simpson.E}: {simpson.FxDx}");
            WriteLine($"\n f2(x)dx, при {simpson.N2}, для {simpson.E}: {simpson.FxDx2}");

            double result = Math.Abs(simpson.FxDx - simpson.FxDx2)/15;

            if (result > simpson.E)
                WriteLine($"Все еще нужно искать. Точность = {result}");
            else
                WriteLine($"Найдена подходящая для {simpson.E}!! Точность = {result}");
        }
    }

    class Simpson
    {
        public double MinLimit; // интеграл мин
        public double MaxLimit; // интеграл макс
        public double E = 0.00001;

        public double N;
        public double FxDx;

        private double _NLimpromeshytok; // (b-a) / n

        public List<double> IPrototypeList; // Список xi
        public List<double> IEquationList; // Список f(xi)
        public List<double> IFXDX;

        // 2 
        public double FxDx2;
        public double N2;

        private double _NLimpromeshytok2;

        public List<double> IPrototypeList2;
        public List<double> IEquationList2;
        public List<double> IFXDX2;

        public Simpson()
        {
            WriteLine("\n[Max - Min -> Интеграла]");
            WriteLine("Введите MaxLimit (x2n) I1: ");
            this.MaxLimit = Convert.ToDouble(Console.ReadLine());
            WriteLine("Введите MinLimit (x0) I1: ");
            this.MinLimit = Convert.ToDouble(Console.ReadLine());
            WriteLine("Введите n1: ");
            this.N = Convert.ToDouble(Console.ReadLine());

            this._NLimpromeshytok = (MaxLimit - MinLimit) / N; // h нахождение
            IPrototypeList = new List<double>(); // Инициализация списков
            IEquationList = new List<double>();
            IFXDX = new List<double>();

            // ------------ 2 I(Fxi)
            WriteLine("Введите n2: ");
            this.N2 = Convert.ToDouble(Console.ReadLine());
            this._NLimpromeshytok2 = (MaxLimit - MinLimit) / N2; // h нахождение

            IPrototypeList2 = new List<double>();
            IEquationList2 = new List<double>();
            IFXDX2 = new List<double>();
        }

        // ------------ 1 I(Fxi)
        public double Output_H() // h вывод
        {
            return _NLimpromeshytok;
        }
        public void Output_XS()
        {
            for (double i = 0; i < MaxLimit; i += _NLimpromeshytok)
                IPrototypeList.Add(i); // Сохранение xi в список
        }
        public void ListFor_Fxi()
        {
            double equation; int count;
            foreach (double i in IPrototypeList)
            {
                equation = (7 * (i * i)) - 3 * Math.Sqrt(i); // уравнение f(xi)
                IEquationList.Add(equation); // список f(xi)
            }
            equation = (7 * (MaxLimit * MaxLimit)) - 3 * Math.Sqrt(MaxLimit); // уравнение f(xi)
            IEquationList.Add(equation); // список f(xi)
        }
        public void FXDX()
        {
            double _chetni = 0; double _ne_chetni = 0;
            for (int i = 0; i < IEquationList.Count; i++)
            {
                if (i % 2 == 0)
                    _chetni += IEquationList[i];
                else
                    _ne_chetni += IEquationList[i];
            }
            FxDx = ((_NLimpromeshytok / 3)*((MinLimit + MaxLimit) + 4*_ne_chetni + 2*_chetni));
        }

        // ------------ 2 I(fxi)
        public double OutputH_I2() // h вывод
        {
            return _NLimpromeshytok2;
        }
        public void OutputXS_I2()
        {
            for (double i = 0; i < MaxLimit; i += _NLimpromeshytok2)
                IPrototypeList2.Add(i); // Сохранение xi в список
        }
        public void ListFor_Fxi_I2()
        {
            double equation; int count;
            foreach (double i in IPrototypeList2)
            {
                equation = (7 * (i * i)) - 3 * Math.Sqrt(i); // уравнение f(xi)
                IEquationList2.Add(equation); // список f(xi)
            }
            equation = (7 * (MaxLimit * MaxLimit)) - 3 * Math.Sqrt(MaxLimit); // уравнение данное в домашке f(xi)
            IEquationList2.Add(equation); // список f(xi)
        }
        public void FXDX_I2()
        {
            double _chetni2 = 0; double _ne_chetni2 = 0;
            for (int i = 0; i < IEquationList2.Count; i++)
            {
                if (i % 2 == 0)
                    _chetni2 += IEquationList2[i];
                else
                    _ne_chetni2 += IEquationList2[i];
            }
            FxDx2 = ((_NLimpromeshytok2 / 3) * ((MinLimit + MaxLimit) + 4 * _ne_chetni2 + 2 * _chetni2));
        }
    }
}
