using System;
using System.Threading;
using System.Console;

class Program
{
    static void Main()
    {
        // Размеры мира
        int width = 30;
        int height = 15;

        // Координаты человека (начинается в центре)
        int playerX = width / 2;
        int playerY = height / 2;

        // Координаты выхода (правый верхний угол)
        int exitX = width - 2;
        int exitY = 1;

        // Координаты огня (пусть движется к человеку)
        int fireX = width / 2;
        int fireY = height / 2 + 3;

        // Главный цикл симуляции (100 кадров)
        for (int step = 0; step < 100; step++)
        {
            // ----- ЛОГИКА ДВИЖЕНИЯ -----
            // Человек идёт к выходу (по диагонали)
            if (playerX < exitX) playerX++;
            if (playerX > exitX) playerX--;
            if (playerY < exitY) playerY++;
            if (playerY > exitY) playerY--;

            // Огонь идёт к человеку
            if (fireX < playerX) fireX++;
            if (fireX > playerX) fireX--;
            if (fireY < playerY) fireY++;
            if (fireY > playerY) fireY--;

            // ----- ОТРИСОВКА -----
            Console.Clear(); // очищаем консоль перед новым кадром

            // Рисуем стены по краям
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    // Стены
                    if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                    {
                        Console.Write("#");
                    }
                    // Выход (зелёный цвет)
                    else if (x == exitX && y == exitY)
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.Write("E");
                        Console.ResetColor();
                    }
                    // Огонь (красный)
                    else if (x == fireX && y == fireY)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.Write("F");
                        Console.ResetColor();
                    }
                    // Человек (синий)
                    else if (x == playerX && y == playerY)
                    {
                        Console.ForegroundColor = ConsoleColor.Cyan;
                        Console.Write("H");
                        Console.ResetColor();
                    }
                    else
                    {
                        Console.Write(".");
                    }
                }
                Console.WriteLine(); // переход на новую строку
            }

            // Проверка: если человек у выхода – победа
            if (playerX == exitX && playerY == exitY)
            {
                Console.WriteLine("Вы спаслись!");
                break;
            }

            // Если огонь добрался до человека – проигрыш
            if (playerX == fireX && playerY == fireY)
            {
                Console.WriteLine("Вы сгорели!");
                break;
            }

            // Задержка, чтобы анимация была видна
            Thread.Sleep(200);
        }
    }
}