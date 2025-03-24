#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

int random_invest_tabl(int range)
{
    return rand() % range;
}

void generate_random_assets(int comp, vector<string>& names, vector<double>& returns, vector<double>& risks,
    vector<double>& prices)
{
    for (int i = 0; i < comp; i++) {
        names.push_back("Компания " + to_string(i + 1));
        returns.push_back(random_invest_tabl(20) + 1);
        risks.push_back(random_invest_tabl(5) + 1);
        prices.push_back(random_invest_tabl(100) + 1);
    }
}

pair<vector<int>, double> optimize_portfolio(const vector<string>& names, const vector<double>& returns,
    const vector<double>& risks, const vector<double>& prices, double total_money, double max_risk)
{
    int n = names.size();
    vector<vector<double>> dp(max_risk + 1, vector<double>(total_money + 1, 0));
    vector<vector<vector<int>>> asset_selection(max_risk + 1, vector<vector<int>>(total_money + 1));

    for (int i = 0; i < n; i++)
        for (int r = max_risk; r >= risks[i]; r--)
            for (int m = total_money; m >= prices[i]; m--)
            {
                double new_return = dp[r - risks[i]][m - prices[i]] + returns[i];
                if (new_return > dp[r][m]) {
                    dp[r][m] = new_return;
                    asset_selection[r][m] = asset_selection[r - risks[i]][m - prices[i]];
                    asset_selection[r][m].push_back(i);
                }
            }

    double max_return = 0;
    vector<int> best_combination;

    for (int r = 0; r <= max_risk; r++)
        for (int m = 0; m <= total_money; m++)
            if (dp[r][m] > max_return) {
                max_return = dp[r][m];
                best_combination = asset_selection[r][m];
            }

    return { best_combination, max_return };
}

void sum_best_asset(vector<pair<int, double>> best_companies, vector<string> names, vector<double> returns,
    vector<double> risks, vector<double> prices, double& user_money)
{
    vector<int> vectorFor_CC_akcii(names.size(), 0);
    int total_stocks = 0;

    cout << "Покупка акций лучших компаний:\n";
    for (const auto& company : best_companies)
    {
        int index = company.first;
        cout << names[index] << ": Стоимость = " << prices[index]
            << " (доход: " << returns[index]
            << ", Риск: " << risks[index] << ")\n";

        int count_akcii = 0;

        while (user_money >= prices[index])
        {
            user_money -= prices[index];
            count_akcii++;
        }

        vectorFor_CC_akcii[index] = count_akcii;
        total_stocks += count_akcii;

        if (count_akcii > 0)
        {
            cout << names[index] << ": Кол-во акций: " << count_akcii << "\n";
        }
    }

    cout << "\nОстаточные деньги: " << user_money << endl;

    cout << "Докупка акций лучших компаний на остаточные деньги:\n";
    while (true)
    {
        bool bought_something = false;
        for (const auto& company : best_companies)
        {
            int index = company.first;
            if (user_money >= prices[index])
            {
                user_money -= prices[index];
                vectorFor_CC_akcii[index]++;
                total_stocks++;
                cout << names[index] << ": Куплена еще одна акция.\n";
                bought_something = true;
            }
        }

        if (!bought_something)
        {
            break;
        }
    }

    cout << "\nИтоговые купленные акции лучших компаний:\n";
    for (const auto& company : best_companies)
    {
        int index = company.first;
        if (vectorFor_CC_akcii[index] > 0)
        {
            cout << names[index] << ": Кол-во акций: " << vectorFor_CC_akcii[index] << "\n";
        }
    }

    cout << "\nОстаточные деньги: " << user_money << endl;
    cout << "\nОбщее количество купленных акций: " << total_stocks << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int companies = 3;
    double user_money = 500;
    double max_risk = 10;

    vector<string> names;
    vector<double> returns, risks, prices;

    generate_random_assets(companies, names, returns, risks, prices);
    cout << "Деньги пользователя: " << user_money << "\nСгенерированные компании:\n";
    for (int i = 0; i < companies; ++i)
        cout << names[i] << ": доход = " << returns[i]
            << ", Риск = " << risks[i] << ", Стоимость = " << prices[i] << endl;

    auto [optimal_indices, maximum_return] = optimize_portfolio(names, returns, risks, prices, user_money, max_risk);

    cout << "\nЛучший вариант компаний: [смотри сверху - вниз.--- \nЛишние комании отпадают, если акция совсем ужасная]\n" << endl;
    vector<pair<int, double>> best_companies;

    for (int index : optimal_indices)
    {
        double difference = returns[index] - prices[index];
        best_companies.emplace_back(index, difference);
    }
    sort(best_companies.begin(), best_companies.end(), [&](const pair<int, double>& a, const pair<int, double>& b) {
        if (a.second != b.second)
            return a.second > b.second; //по разнице

        });

    sum_best_asset(best_companies, names, returns, risks, prices, user_money);
}
