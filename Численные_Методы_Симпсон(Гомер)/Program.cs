using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Security.Cryptography.X509Certificates;

namespace ЧисленныеМетодыСимпсонГомер
{
    internal class Program // 6 вариант
    {
        static void Main(string[] args)
        {


            //1 I
            // Создание объекта Simpson с параметрами
            Console.WriteLine("Для первой I n-ой");
            Simpson1 simpson = new Simpson1();
            simpson.Cal(); // Вычисление x-ов в промежутке интеграла
            simpson.Matem();
            simpson.FXDX();

            Console.WriteLine($"\nh = {simpson.test()} [это b-a / n]");

            // Вывод всех значений IPrototype
            Console.WriteLine($"\nВсе значения xi: [Всего x-ов i: {simpson.IPrototypeList.Count + 1}]");
            foreach (var value in simpson.IPrototypeList)
            {
                Console.WriteLine(value);
            }
            Console.WriteLine($"X2n = {simpson.MaxLimit}");

            Console.WriteLine("\nВсе значения f(xi) для :");
            foreach (var value in simpson.IEquationList)
            {
                Console.WriteLine(value);
            }

            //2 I
            Console.WriteLine("\n\nДля второй I n-ой");
            Simpson2 simpson2 = new Simpson2(simpson);
            simpson2.Cal2();
            simpson2.Matem2();
            simpson2.FXDX2();

            Console.WriteLine($"\nh = {simpson2.test12()} [это b-a / n]");

            // Вывод всех значений IPrototype
            Console.WriteLine($"\nВсе значения xi 2-ой I: [Всего x-ов i: {simpson2.IPrototypeList2.Count + 1}]");
            foreach (var value in simpson2.IPrototypeList2)
            {
                Console.WriteLine(value);
            }
            Console.WriteLine($"X2n = {simpson.MaxLimit}");

            Console.WriteLine("\nВсе значения f(xi) для 2-ой I:");
            foreach (var value in simpson2.IEquationList2)
            {
                Console.WriteLine(value);
            }

            // ответ

            Console.WriteLine($"\n f(x)dx, при {simpson.E}: {simpson.dx}");
            Console.WriteLine($"\n f2(x)dx, при {simpson.E}: {simpson2.dx2}");

            double result = Math.Abs(simpson.dx - simpson2.dx2)/15; // 1 - 2 /15

            if (result > simpson.E)
            {
                Console.WriteLine($"Все еще нужно искать. Точность = {result}");
            }
            else
            {
                Console.WriteLine($"Точность = {result}");
            }

        }
    }

    class Simpson1
    {
        public double MinLimit; // интеграл мин
        public double MaxLimit; // интеграл макс
        public double N; public double E = 0.00001;
        public double dx;

        private double NLimpromeshytok; // (b-a) / n

        public List<double> IPrototypeList; // Список xi
        public List<double> IEquationList; // Список f(xi)
        public List<double> IFXDX;

        private List<double> CHETNI;
        private List<double> Ne_CHETNI;

        public Simpson1()
        {
            Console.WriteLine("Введите MaxLimit (x2n) I1: ");
            this.MaxLimit = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Введите MinLimit (x0) I1: ");
            this.MinLimit = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Введите n1: "); // нужно 
            this.N = Convert.ToDouble(Console.ReadLine());

            this.NLimpromeshytok = (MaxLimit - MinLimit) / N; // h нахождение

            IPrototypeList = new List<double>(); // Инициализация списков
            IEquationList = new List<double>();
            IFXDX = new List<double>();

            CHETNI = new List<double>();
            Ne_CHETNI = new List<double>();
        }

        public double test() // h вывод
        {
            return NLimpromeshytok;
        }

        public void Cal()
        {
            for (double i = 0; i < MaxLimit; i += NLimpromeshytok)
            {
                IPrototypeList.Add(i); // Сохранение xi в список
            }
        }

        public double test2() // ось x-ов
        {
            return IPrototypeList.Count > 0 ? IPrototypeList[IPrototypeList.Count - 1] : 0;
        }

        public void Matem()
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

        public double test3() // ось f(xi)
        {
            return IEquationList.Count > 0 ? IEquationList[IEquationList.Count - 1] : 0;
        }

        public void FXDX()
        {
            double _chetni = 0; double _ne_chetni = 0;
            for (int i = 0; i < IEquationList.Count; i++)
            {
                if (i % 2 == 0)
                {
                    _chetni += IEquationList[i];
                }
                else
                {
                    _ne_chetni += IEquationList[i];
                }
            }
            dx = ((NLimpromeshytok / 3)*((MinLimit + MaxLimit) + 4*_ne_chetni + 2*_chetni));
        }


        public double test4()
        {
            return dx;
        }

    }

    class Simpson2 // для второй I
    {
        public double N2;
        public double dx2;

        readonly Simpson1 simpson1;

        private double NLimpromeshytok; // (b-a) / n

        public List<double> IPrototypeList2; // Список xi
        public List<double> IEquationList2; // Список f(xi)
        public List<double> IFXDX2;

        private List<double> CHETNI;
        private List<double> Ne_CHETNI;

        public Simpson2(Simpson1 _simpson1)
        {
            Console.WriteLine("Введите n2: "); // нужно 
            this.N2 = Convert.ToDouble(Console.ReadLine());
            this.simpson1 = _simpson1;
            this.NLimpromeshytok = (simpson1.MaxLimit - simpson1.MinLimit) / N2; // h нахождение

            IPrototypeList2 = new List<double>(); // Инициализация списков
            IEquationList2 = new List<double>();
            IFXDX2 = new List<double>();

            CHETNI = new List<double>();
            Ne_CHETNI = new List<double>();
        }

        public double test12() // h вывод
        {
            return NLimpromeshytok;
        }

        public void Cal2()
        {
            for (double i = 0; i < simpson1.MaxLimit; i += NLimpromeshytok)
            {
                IPrototypeList2.Add(i); // Сохранение xi в список
            }
        }

        public double test22() // ось x-ов
        {
            return IPrototypeList2.Count > 0 ? IPrototypeList2[IPrototypeList2.Count - 1] : 0;
        }

        public void Matem2()
        {
            double equation; int count;
            foreach (double i in IPrototypeList2)
            {
                equation = (7 * (i * i)) - 3 * Math.Sqrt(i); // уравнение f(xi)
                IEquationList2.Add(equation); // список f(xi)
            }
            equation = (7 * (simpson1.MaxLimit * simpson1.MaxLimit)) - 3 * Math.Sqrt(simpson1.MaxLimit); // уравнение f(xi)
            IEquationList2.Add(equation); // список f(xi)
        }

        public double test32() // ось f(xi)
        {
            return IEquationList2.Count > 0 ? IEquationList2[IEquationList2.Count - 1] : 0;
        }

        public void FXDX2()
        {
            double _chetni = 0; double _ne_chetni = 0;
            for (int i = 0; i < IEquationList2.Count; i++)
            {
                if (i % 2 == 0)
                {
                    _chetni += IEquationList2[i];
                }
                else
                {
                    _ne_chetni += IEquationList2[i];
                }
            }
            dx2 = ((NLimpromeshytok / 3) * ((simpson1.MinLimit + simpson1.MaxLimit) + 4 * _ne_chetni + 2 * _chetni));
        }
        public double test42()
        {
            return dx2;
        }
    }
}
