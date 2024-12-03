using System;
using static System.Console;

namespace РазработкаC_02._12._24
{
    internal class Program
    {
        static void Main(string[] args)
        {
            double radius, h, a, b, c, d;
            const double Pi = 3.14;

            Write("Введите радиус: ");
            radius = Convert.ToDouble(ReadLine().Replace('.', ','));
            Write("Введите высоту: ");
            h = Convert.ToDouble(ReadLine().Replace('.', ','));
            Write("Введите сторону a: ");
            a = Convert.ToDouble(ReadLine().Replace('.', ','));
            Write("Введите сторону b: ");
            b = Convert.ToDouble(ReadLine().Replace('.', ','));
            Write("Введите сторону c: ");
            c = Convert.ToDouble(ReadLine().Replace('.', ','));
            Write("Введите сторону d: ");
            d = Convert.ToDouble(ReadLine().Replace('.', ','));


            WriteLine("Выбирите фигуру, S и P будут вычитаться: ");

            WriteLine($"\nПлощадь Треугольника [S]: {ResultS(a, h) * 0.5}. Используя формулу: [1 / 2 * H * A]"); // /\
            WriteLine($"Периметр треугольника [P]: {ResultP(a, b, c)}. Используя формулу: [A + B + C]");

            WriteLine($"\nПлощадь Круга [S]: {ResultS(radius) * Pi}. Используя формулу: [Pi * (Radius * Radius)]"); // 0
            WriteLine($"Периметр окружности [P]: {ResultP(radius) * Pi}. Используя формулу: [Pi * 2 * Radius]");

            WriteLine($"\nПлощадь Параллелограмма [S]: {ResultS(a, h)}. Используя формулу: [A * H]"); // /_/
            WriteLine($"Периметр параллелограмма [P]: {ResultP(a, b)}. Используя формулу: [2 * (A + B)]");

            WriteLine($"\nПериметр прямоугольника [P]: {ResultP(a, b)}. Используя формулу: [2 * (A + B)]"); // |_|

            if (h == a || h == b)
            {
                WriteLine($"Площадь Прямоугольника [S]: {ResultS(a, h)}. Используя формулу: [A * B]");
            }
            else
            {
                WriteLine("\nУ мрямоугольника неккороектные данные: h != a && h != b [h - высота. a - 1ая сторона. b - 2ая высота.]");
            }
        }
        public static double ResultS(double a, double h)
        {
            return h * a;
        }
        public static double ResultP(double a, double b, double c)
        {
            return a + b + c;
        }
        public static double ResultP(double a, double b)
        {
            return 2 * (a + b);
        }
        public static double ResultS(double radius) // + pi
        {
            return radius * radius;
        }
        public static double ResultP(double radius) // + pi
        {
            return 2 * radius;
        }
    }
}