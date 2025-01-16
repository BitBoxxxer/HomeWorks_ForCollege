using System;
using static System.Console;

namespace _14._01._25_4_s_lesson_CS // Тема: Интерфейс (класс может наследовать несколько интерфейсов и более)
{
    internal class Program
    {
        public static string AnimalSelect;

        public static string Name;
        static void Main(string[] args)
        {
            Animal A = new Animal();
            
            Write("Имя питомца: "); string Name = ReadLine();
            Write("\nЖивотное [Рыба'1' или Птица'2' или Сухопутное'3'] ? [выбирите цифру вида животного]: ");
            AnimalSelect = ReadLine();

            WriteLine("\nПозиция 'a': "); int a = Convert.ToInt32(ReadLine());
            WriteLine("\nПозиция 'b': "); int b = Convert.ToInt32(ReadLine());

            if (AnimalSelect == "1" || AnimalSelect == "2")
            {
                WriteLine("\nПозиция 'c': "); int c = Convert.ToInt32(ReadLine());
                WriteLine($"\nХарактеристики животного:");
                switch (AnimalSelect)
                {
                    case "1":
                        WriteLine($"Тип: {Fish.AnimalFishType}");
                        break;

                    case "2":
                        WriteLine($"Тип: {Bird.AnimalBirdType}");
                        break;
                }
                WriteLine($"\nName");
                A.Name(Name);
                WriteLine("\nПозиции на координтах: ");
                A.NewMove(a, b, c);
            }
            else {
                WriteLine($"Тип: {Land.AnimalLandType}");
                WriteLine($"\nName");
                A.Name(Name);
                A.Move(a, b);
            } // select = 3

            // 15.01.25 (3-е задание)
            WriteLine("\nЗадание 3: [CompareTo]\nВведите значение для сравнения с позицией 'X'");
            int o = Convert.ToInt32(ReadLine());
            int comprareResult = A.CompareTo(new Animal {PositionX = o});
            if (comprareResult == 0)
                WriteLine($"Результат: Правильно.");
            else WriteLine("Результат: Ошибка.");

            // clone

            WriteLine("\n[Clone]\n");
            Animal cloneResult = (Animal)A.Clone();

            if (AnimalSelect == "1" || AnimalSelect == "2")
            {
                WriteLine("Какую позицию нужно скопировать ? '1' - X, '2' - Y, '3' - Z");
                string selectforclone = ReadLine();
                switch (selectforclone)
                {
                    case "1":
                        WriteLine($"Пример скопированной позиции X: {cloneResult.PositionX}");
                        break;
                    case "2":
                        WriteLine($"Пример скопированной позиции Y: {cloneResult.PositionY}");
                        break;
                    case "3":
                        WriteLine($"Пример скопированной позиции Z: {cloneResult.PositionZ}");
                        break;
                    default: break;
                }
            }
            else
            {
                WriteLine("Какую позицию нужно скопировать ? '1' - X, '2' - Y ?");
                string selectforclone = ReadLine();
                switch (selectforclone)
                {
                    case "1":
                        WriteLine($"Пример скопированной позиции оси X: {cloneResult.PositionX}");
                        break;
                    case "2":
                        WriteLine($"Пример скопированной позиции оси Y: {cloneResult.PositionY}");
                        break;
                    default: break;
                }
            }
        }
    }

    interface INamed
    {
        string GetName { get; set; }

        void Name(string a);
    }

    interface IMovable
    {
        int PositionX { get; set; }
        int PositionY { get; set; }
        int PositionZ { get; set; }

        void Move(int a, int b);
        void NewMove(int a, int b, int c);
    }

    public class Animal : IMovable, INamed, IComparable, ICloneable // Сделать ответвления от класса для типов животных. IClonable - клонирование объектов
    {
        public int PositionX { get; set; }
        public int PositionY { get; set; }
        public int PositionZ { get; set; }


        public void Move(int a, int b)
        {
            PositionX += a; WriteLine($"[Новая позиция X: {PositionX}]");
            PositionY += b; WriteLine($"[Новая позиция Y: {PositionY}]");
        }
        public void NewMove(int a, int b, int c)
        {
            Move(a, b);
            PositionZ += c; WriteLine($"[Новая позиция Z: {PositionZ}]");
        }

        // 2 задание

        public string GetName { get; set; }
        public void Name(string a)
        {
            GetName = a; WriteLine($"[Новое имя: {GetName}]");
        }

        // 3 задание

        public int CompareTo(object o)
        {
            if (o is Animal A) return PositionX.CompareTo(A.PositionX);
            else throw new ArgumentException("Error");
        }

        public object Clone()
        {
            return MemberwiseClone();
        }

    }
    public class Land : Animal // Land - сухопутное, классика
    {
        public static string AnimalLandType = "Land - Сухопутное";
    }
    public class Fish : Animal
    {
        public static string AnimalFishType = "Fish - Рыба";
    }
    public class Bird : Animal
    {
        public static string AnimalBirdType = "Bird - Птица";
    }
}
