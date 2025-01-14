using System;
using System.Collections.Generic;
using static System.Console;

/*
 *  Идеи для кода:
2) Чтото покупать за монетки - Пример: (выбросить бота из окна для победы) || (Предугадать след. действие бота)
3) Сделать анимации для Win, Faile, Draw + Окно выхода и проигрыша

    Выполенное:
*) Сделать пропуск по деньгам (если не хватает - то экран закрывается в 'q') [SELECT]
*) ПРАВИЛА ИГРЫ [SELECT]
 */

namespace RandomGame_2
{
    internal class Program
    {
        public static int MoneyCount = 45;
        public static string PlayerSelect; public static string SessionSelect;

        static void Main(string[] args)
        {
            while (true)
            {
                if (SysResults.PointCount == 0)
                {
                    WriteLine("\n --- Игра в 'Камень-Ножницы-Бумага' ---\n[Изначально вам дано 45 монет]\n");
                    _SelectMain();

                    if (SessionSelect == "1")
                    {
                        _OutputConsoleGameForMain();
                    }
                }

                if (SysResults.PointCount > 0)
                {
                    WriteLine($"\n --- Сессия номер: '{SysResults.PointCount + 1}' ---\n");
                    _SelectMain();

                    if (SessionSelect == "1")
                    {
                        _OutputConsoleGameForMain();
                    }
                }
            }
        }
        private static void _OutputConsoleGameForMain()
        {
            _returnButtonContinueStr();
            Clear();
            if (PlayerSelect == "1" || PlayerSelect == "2" || PlayerSelect == "3")
            {
                WriteLine("\n --- Результат игры !\n|");
                SysResults SR = new SysResults();
                _returnButtonContinueStr();
                Clear();
            }
        }
        private static void _SelectMain() // выбор предмета игроком.
        {
            if (MoneyCount >= 15)
            {
                Write("\nНачать игру: '1'.\n-\nПосмотреть очки: '2'.\n-\nПосмотреть историю ходов, результатов: '3'.\n-\nПравила игры: '4'.\n-\nЗАКОНЧИТЬ СЕССИЮ: 'q'.\n\n|\n -> ");
                SessionSelect = ReadLine();

                PlayerSelect = "";

                Clear();
                _operationSelect();
            }
            else
            {
                Clear();
                WriteLine("\nНа вашем счету не осталось Денег. Вы проиграли !!!\n");
                _outputSessionEndStr();
            }
        }
        private static void _operationSelect()
        {
            switch (SessionSelect) // Просмотр очков - характеристик
            {
                case "1":
                    {
                        Write("\nВыберите [Ножницы  - '1' || Камень - '2' || Бумага - '3']\n|\n -> ");

                        PlayerSelect = ReadLine();

                        if (PlayerSelect == "1" || PlayerSelect == "2" || PlayerSelect == "3") // вывод выбранного select player's
                        {
                            switch (PlayerSelect)
                            {
                                case "1":
                                    WriteLine($"Вами выбрано: Ножницы");
                                    break;
                                case "2":
                                    WriteLine($"Вами выбрано: Камень");
                                    break;
                                case "3":
                                    WriteLine($"Вами выбрано: Бумага");
                                    break;
                                default: WriteLine("Ошибка."); break;
                            }
                        }
                        else
                        {
                            WriteLine("Ошибка! Введено неверное число");
                            break;
                        }
                        break;
                    }

                case "2":
                    WriteLine($"Кол-во очков: {SysResults.PointCount}\nКол-во монет в кошельке: {MoneyCount}"); SessionSelect = "";
                    _returnButtonContinueStr();
                    Clear();
                    break;

                case "3":
                    WriteLine($"\n[W - Победа, F - Проигрыш, D - Ничья]\nСписок результата сессий: {string.Join(", ", SysResults.ResultCountStrList)}");
                    _returnButtonContinueStr();
                    Clear();
                    break;

                case "4":
                    _outputGameRulesStr();
                    Clear();
                    break;

                case "q": // exit from game
                    _outputSessionEndStr();
                    break;

                default: break;
            }
        }

        // Упрощение вывода информации в консоль:
        private static void _returnButtonContinueStr()
        {
            WriteLine("\n !Нажмите (любую клавишу) чтобы продолжить: "); ReadKey();
        }
        private static void _outputSessionEndStr() 
        {
            WriteLine($"\nСессия закончена с след. результатами:\nКол-во очков (игр): {SysResults.PointCount}\nКол-во монет в кошельке: {MoneyCount}\n");
            WriteLine($"\n[W - Победа, F - Проигрыш, D - Ничья]\nСписок истории сессий: {string.Join(", ", SysResults.ResultCountStrList)}\n");
            WriteLine($"\nИстория выбора-ов игрока за сессии: {string.Join(", ", SysResults.PlayerSelectList)}\n");
            Environment.Exit(0);
        }
        private static void _outputGameRulesStr()
        {
            WriteLine("\n                 --Правила Игры--\n");
            WriteLine("\n(1) 1 Сессия стоит '15' монет.\n|\n(2) Логика вычисления монет:\n\n " +
                "- За победу игроку начисляется '+15' монет. || При ничье вычитается '-5' монет. || При проигрыше вычитается '-15' монет -\n\n" +
                "(3) За каждую игру игроку начисляется '1' очко опыта.\n|\n(4) За выход || проигрыш игра сбрасывается.");
            _returnButtonContinueStr();
        }
    }

    public class SysOperations // Команды бота (Операции конкретные - бота) (рандом хода)
    {
        Random rand = new Random();

        public static int BotOperationSelect;

        public SysOperations()
        {
            BotOperationSelect = rand.Next(1, 4);
        }
    }

    public class SysResults // Результат игры
    {
        SysOperations SO = new SysOperations();
        Program P = new Program();

        public static int PointCount;  public static string ResultCountStr;
        public static string PlayersTranslateResultStr; public static string BotTranslateResultStr;

        public static List<string> ResultCountStrList = new List<string>();
        public static List<string> PlayerSelectList = new List<string>();

        public SysResults() // вывод
        {
            TransResult();
            WriteLine($"\nИгрок: {PlayersTranslateResultStr} --- ПРОТИВ --- Бот: {BotTranslateResultStr}\n");
            SearchResultCountStr();
            TransResultCount();
        }
        private void SearchResultCountStr() // это для истории списка игр.
        {
            if ((SysOperations.BotOperationSelect == 3 && Program.PlayerSelect == "1") ||
            (SysOperations.BotOperationSelect == 1 && Program.PlayerSelect == "2") ||
            (SysOperations.BotOperationSelect == 2 && Program.PlayerSelect == "3"))
            {
                Console.WriteLine("-> Победил Игрок !");
                ResultCountStr = "W";
            }
            else if ((SysOperations.BotOperationSelect == 2 && Program.PlayerSelect == "1") ||
                     (SysOperations.BotOperationSelect == 3 && Program.PlayerSelect == "2") ||
                     (SysOperations.BotOperationSelect == 1 && Program.PlayerSelect == "3"))
            {
                Console.WriteLine("-> Проиграл Игрок");
                ResultCountStr = "F";
            }
            else if ((SysOperations.BotOperationSelect == 1 && Program.PlayerSelect == "1") ||
                     (SysOperations.BotOperationSelect == 2 && Program.PlayerSelect == "2") ||
                     (SysOperations.BotOperationSelect == 3 && Program.PlayerSelect == "3"))
            {
                Console.WriteLine("-> Ничья");
                ResultCountStr = "D";
            }
        }
        public void TransResult()
        {
            switch (Program.PlayerSelect)
            {
                case "1":
                    PlayersTranslateResultStr = "Ножницы";
                    PlayerSelectList.Add("Нож. ");
                    break;

                case "2":
                    PlayersTranslateResultStr = "Камень";
                    PlayerSelectList.Add("Кам. ");
                    break;

                case "3":
                    PlayersTranslateResultStr = "Бумага";
                    PlayerSelectList.Add("Бум. ");
                    break;
            }
            switch (SysOperations.BotOperationSelect)
            {
                case 1:
                    BotTranslateResultStr = "Ножницы";
                    break;

                case 2:
                    BotTranslateResultStr = "Камень";
                    break;

                case 3:
                    BotTranslateResultStr = "Бумага";
                    break;
            }
        }
        public void TransResultCount()
        {
            switch (ResultCountStr)
            {
                case "W": // Win
                    PointCount++; Program.MoneyCount += 15;
                    ResultCountStrList.Add("W ");
                    WriteLine($"\n Обновлено:\n'Очки +1. Монеты +15'");
                    break;

                case "F": // Faile
                    PointCount++; Program.MoneyCount -= 15;
                    ResultCountStrList.Add("F ");
                    WriteLine($"\n Обновлено:\n'Очки +1. Монеты -15'");
                    break;

                case "D": // Draw
                    PointCount++; Program.MoneyCount -= 5;
                    ResultCountStrList.Add("D ");
                    WriteLine($"\n Обновлено:\n'Очки +1. Монеты -5'");
                    break;
            }
        }
    }
}
