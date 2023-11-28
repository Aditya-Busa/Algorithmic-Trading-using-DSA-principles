#include "market.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// bool is_positive_integer(std::string &s)
// {
//     for (int i = 0; i < s.length(); i++)
//     {
//         if (s[i] > 57 || s[i] < 48)
//             return false;
//     }
//     return true;
// }

// bool isInteger(std::string &s)
// {
//     int i = 0;
//     if (s[0] == '-')
//         for (i = 1; i < s.length(); i++)
//         {
//             if (s[i] > 57 || s[i] < 48)
//                 return false;
//         }
//     return true;
// }

// bool areAllAlphabets(const std::string &input)
// {
//     for (char ch : input)
//     {
//         // Check if the character is an uppercase or lowercase alphabet
//         if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')))
//         {
//             // If the character is not an alphabet, return false
//             return false;
//         }
//     }

//     // All characters are alphabet
//     return true;
// }
bool CompareShare(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b)
{
    return a.first < b.first;
}

market::market(int argc, char **argv)
{
}

void market::start()
{
    std::string message;
    std::ifstream inputFile("samples/output2.txt");
    std::string line;
    std::string str = "*";
    // Read the first line and discard it
    std::getline(inputFile, line);

    // Read lines until encountering "!@"
    while (std::getline(inputFile, line) && line.substr(0, 2) != "!@")
    {
        message.append(line);
        message.append("\n");
    }
    message.append("%");

    //  Print the collected lines
    // for (const auto &msg : message)
    // {
    //     std::cout << msg;
    // }
    std::vector<std::string> name_shares;
    std::vector<std::vector<std::pair<std::string, std::string>>> sorted_shares;
    std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>>>> i_prices;
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> all_statements;
    int iter = 0;
    int c = 0;
    while (message[iter] != '%')
    {
        int a = 0;
        std::string start;
        std::string during;
        std::string broker;
        std::string s_or_b;
        std::string share;
        std::string price;
        std::string quantity;
        while (message[iter] != '\n')
        {
            if (message[iter] == ' ')
            {
                a++;
                if (a == 1)
                {
                    start = message.substr(c, iter - c);
                    c = iter + 1;
                    // std::cout << start << std::endl;
                }
                else if (a == 2)
                {
                    broker = message.substr(c, iter - c);
                    c = iter + 1;
                    // std::cout << broker << std::endl;
                }
                else if (a == 3)
                {
                    s_or_b = message.substr(c, iter - c);
                    c = iter + 1;
                    // std::cout << s_or_b << std::endl;
                }
            }
            else if (message[iter] == '$')
            {
                share = message.substr(c, iter - c - 1);
                c = iter + 1;
                // std::cout<<share<<std::endl;
            }
            else if (message[iter] == '#')
            {
                price = message.substr(c, iter - c - 1);
                c = iter + 1;
                // std::cout << price << std::endl;
                int iter_1 = iter;
                while (message[iter_1] != ' ')
                {
                    iter_1++;
                }
                quantity = message.substr(c, iter_1 - c);
                // std::cout << quantity << std::endl;
                c = iter_1 + 1;
            }
            else if (message[iter + 1] == '\n')
            {
                during = message.substr(c, iter - c + 1);
                c = iter + 2;
                //  std::cout << during << std::endl;
            }
            iter++;
        }
        iter++;
        bool check_share = true;
        int iter_2 = 0;
        int n_space = 0;
        int e = 0;
        int f = 0;
        std::string temp_string;
        std::string temp_string_1;
        std::vector<std::pair<std::string, std::string>> t_sort_str;
        std::pair<std::string, std::string> sort_pair;
        while (iter_2 < share.size())
        {
            if (share[iter_2] == ' ')
            {
                n_space++;

                if (n_space % 2 == 1)
                {
                    e = iter_2 + 1;
                }
                else if (n_space % 2 == 0)
                {
                    temp_string_1 = share.substr(e, iter_2 - e);
                    temp_string = share.substr(f, e - f - 1);
                    sort_pair.first = temp_string;
                    sort_pair.second = temp_string_1;
                    t_sort_str.push_back(sort_pair);
                    f = iter_2 + 1;
                }
            }
            if (iter_2 + 1 == share.size() && n_space != 0)
            {
                temp_string_1 = share.substr(e, iter_2 - e + 1);
                temp_string = share.substr(f, e - f - 1);
                sort_pair.first = temp_string;
                sort_pair.second = temp_string_1;
                t_sort_str.push_back(sort_pair);
            }
            iter_2++;
        }
        if (n_space == 0)
        {
            temp_string = share;
            temp_string_1 = "0";
            sort_pair.first = temp_string;
            sort_pair.second = temp_string_1;
            t_sort_str.push_back(sort_pair);
        }
        std::sort(t_sort_str.begin(), t_sort_str.end(), CompareShare);

        int end = std::stoi(start) + std::stoi(during);
        // std::cout << share << std::endl;
        std::string end_1 = std::to_string(end);
        std::pair<std::string, std::string> price_1 = std::make_pair(start, end_1);
        std::pair<std::string, std::string> price_2 = std::make_pair(s_or_b, quantity);
        std::pair<std::string, std::string> price_3 = std::make_pair(broker, price);
        std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> price_4 = std::make_pair(price_1, price_3);
        std::pair<std::pair<std::string, std::string>, std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> price_5 = std::make_pair(price_2, price_4);
        auto it = std::find(name_shares.begin(), name_shares.end(), share);
        auto it_1 = std::find(sorted_shares.begin(), sorted_shares.end(), t_sort_str);
        if (it_1 != sorted_shares.end())
        {
            int ind_1 = std::distance(sorted_shares.begin(), it_1);
            i_prices[ind_1].push_back(price_5);
        }
        else
        {
            std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>>> temp_prices;
            name_shares.push_back(share);
            sorted_shares.push_back(t_sort_str);
            temp_prices.push_back(price_5);
            i_prices.push_back(temp_prices);
        }
        // if (it != name_shares.end())
        // {
        //     int ind = std::distance(name_shares.begin(), it);
        //     i_prices[ind].push_back(price_5);
        // }
        // else
        // {
        //     std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>>> temp_prices;
        //     name_shares.push_back(share);
        //     temp_prices.push_back(price_5);
        //     i_prices.push_back(temp_prices);
        // }
        bool p1 = false;
        for (auto &person : all_statements)
        {
            if (person.first.first == broker)
            {
                p1 = true;
            }
        }
        if (!p1)
        {
            std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> temp_statement;
            temp_statement.first.first = broker;
            temp_statement.first.second = "0";
            temp_statement.second.first = "0";
            temp_statement.second.second = "0";
            all_statements.push_back(temp_statement);
        }
    }
    // for (int i = 0; i < name_shares.size(); i++)
    // {
    //     for (int j = 0; j < i_prices[i].size(); j++)
    //     {
    //         std::cout << name_shares[i] << " " << i_prices[i][j].first.first << " " << i_prices[i][j].first.second << " " << i_prices[i][j].second.first.first << " " << i_prices[i][j].second.first.second << " " << i_prices[i][j].second.second.first << " " << i_prices[i][j].second.second.second << std::endl;
    //     }
    // }
    // for (int i = 0; i < name_shares.size(); i++)
    // {
    //     std::cout << name_shares[i] << std::endl;
    // }
    // for (const auto &msg : message)
    // {
    //     std::cout << msg;
    // }

    int money_transfer = 0;
    int complete_trade = 0;
    int shares_trade = 0;
    std::vector<std::string> statements;

    /*
    we have a vector that is name_shares which contains the names of the shares which we are storing
    share -- name_shares[i]
    and now for the corresponding indices we will store it in this
    SELL OR BUY -- i_prices[i][j].first.first
    QUANTITY -- i_prices[i][j].first.second
    START -- i_prices[i][j].second.first.first
    END -- i_prices[i][j].second.first.second
    BROKER -- i_prices[i][j].second.second.first
    PRICE -- i_prices[i][j].second.second.second
    */
    for (int i1 = 0; i1 < name_shares.size(); i1++)
    {
        for (int i2 = 0; i2 < i_prices[i1].size(); i2++)
        {
            int i3 = 0;
            // std::string s = i_prices[i1][i2].second.first.first;
            // while (i3 < i_prices[i1].size() && std::stoi(i_prices[i1][i3].second.first.first) == std::stoi(s))
            // {
            //     i3++;
            // }
            // i3--;
            int i_3 = i3;
            int pappu = 0;
            int j1 = i2;
            std::string comp = i_prices[i1][i2].first.first;
            std::string stat;
            std::string s1;
            std::string s2;
            int share_f;
            int max_p = std::stoi(i_prices[i1][i2].second.second.second);
            if (comp == "SELL")
            {
                do
                {
                    j1 = i2;
                    pappu = 0;
                    max_p = std::stoi(i_prices[i1][i2].second.second.second);
                    while (i3 < i2)
                    {
                        if ((std::stoi(i_prices[i1][i3].second.first.first) > std::stoi(i_prices[i1][i3].second.first.second) || (std::stoi(i_prices[i1][i3].second.first.second) >= std::stoi(i_prices[i1][i2].second.first.first))) && (std::stoi(i_prices[i1][i2].second.first.second) >= std::stoi(i_prices[i1][i3].second.first.first) || std::stoi(i_prices[i1][i2].second.first.second) < std::stoi(i_prices[i1][i2].second.first.first)) && (comp != i_prices[i1][i3].first.first)) //&& (std::stoi(i_prices[i1][i3].second.first.first) < std::stoi(i_prices[i1][i2].second.first.first)))
                        {
                            if (std::stoi(i_prices[i1][i3].second.second.second) > max_p && std::stoi(i_prices[i1][i3].first.second) != 0)
                            {
                                max_p = std::stoi(i_prices[i1][i3].second.second.second);
                                j1 = i3;
                            }
                            else if (std::stoi(i_prices[i1][i3].second.second.second) == max_p && std::stoi(i_prices[i1][i3].first.second) != 0)
                            {
                                if (max_p == std::stoi(i_prices[i1][i2].second.second.second))
                                {
                                    if (pappu == 0)
                                    {
                                        j1 = i3;
                                    }
                                    pappu++;
                                }

                                if (j1 != i2 && std::stoi(i_prices[i1][i3].second.first.first) == std::stoi(i_prices[i1][j1].second.first.first))
                                {
                                    if (i_prices[i1][j1].second.second.first > i_prices[i1][i3].second.second.first)
                                    {
                                        j1 = i3;
                                    }
                                }
                            }
                        }
                        i3++;
                    }
                    if (j1 != i2 && std::stoi(i_prices[i1][j1].first.second) != 0 && std::stoi(i_prices[i1][i2].first.second) != 0)
                    {
                        if (std::stoi(i_prices[i1][j1].first.second) >= std::stoi(i_prices[i1][i2].first.second))
                        {
                            int size_q;
                            size_q = 0;
                            int size_q1;
                            share_f = std::stoi(i_prices[i1][i2].first.second);
                            s1 = i_prices[i1][i2].first.second;
                            size_q1 = std::stoi(i_prices[i1][j1].first.second) - std::stoi(i_prices[i1][i2].first.second);
                            i_prices[i1][j1].first.second = std::to_string(size_q1);
                            i_prices[i1][i2].first.second = std::to_string(size_q);
                            // std::cout << i_prices[i1][j1].first.second << " " << i_prices[i1][i2].first.second << std::endl;
                            //  if (j1 > i2)
                            //  {
                            //      s2 = i_prices[i1][i2].second.second.second;
                            //  }
                            //  else
                            //  {
                            s2 = i_prices[i1][j1].second.second.second;
                            // }
                        }
                        else
                        {
                            int size_q1 = 0;
                            int size_q;
                            share_f = std::stoi(i_prices[i1][j1].first.second);
                            s1 = i_prices[i1][j1].first.second;
                            size_q = std::stoi(i_prices[i1][i2].first.second) - std::stoi(i_prices[i1][j1].first.second);
                            i_prices[i1][i2].first.second = std::to_string(size_q);
                            i_prices[i1][j1].first.second = std::to_string(size_q1);
                            // std::cout << i_prices[i1][j1].first.second << " " << i_prices[i1][i2].first.second << std::endl;
                            //  if (j1 > i2)
                            //  {
                            //      s2 = i_prices[i1][i2].second.second.second;
                            //  }
                            //  else
                            //  {
                            s2 = i_prices[i1][j1].second.second.second;
                            // }
                        }
                        complete_trade = complete_trade + 1;
                        shares_trade = shares_trade + share_f;
                        stat = i_prices[i1][j1].second.second.first + " purchased " + s1 + " shares of " + name_shares[i1] + " from " + i_prices[i1][i2].second.second.first + " for $" + s2 + "/share";
                        // std::cout << i_prices[i1][j1].second.first.first << " " << i_prices[i1][i2].second.first.first << std::endl;
                        // std::cout << stat << std::endl;
                        statements.push_back(stat);
                        money_transfer = money_transfer + (std::stoi(s1) * std::stoi(s2));
                        /*
                        all_statements.first.first = name
                        all_statements.first.second = amount transfer that happened
                        all_statements.second.first = number of orders bought
                        all_statements.second.second = number of orders sold.
                        */
                        for (auto &person : all_statements)
                        {
                            if (person.first.first == i_prices[i1][j1].second.second.first)
                            {
                                int bought;
                                int transfer;
                                // std::cout << s1 << " " << s2;
                                bought = std::stoi(s1) + std::stoi(person.second.first);
                                transfer = std::stoi(person.first.second) - (std::stoi(s1) * std::stoi(s2));
                                person.second.first = std::to_string(bought);
                                // std::cout << " " << person.second.first << std::endl;
                                person.first.second = std::to_string(transfer);
                                // std::cout << person.first.first << " bought " << person.second.first << " and sold " << person.second.second << " for a net transfer of $" << person.first.second << std::endl;
                            }

                            if (person.first.first == i_prices[i1][i2].second.second.first)
                            {

                                int sold;
                                int transfer_1;
                                //  std::cout << s1 << " " << s2 << " " << person.second.second << std::endl;
                                sold = std::stoi(s1) + std::stoi(person.second.second);
                                transfer_1 = std::stoi(person.first.second) + (std::stoi(s1) * std::stoi(s2));
                                person.second.second = std::to_string(sold);
                                person.first.second = std::to_string(transfer_1);
                                // std::cout << person.first.first << " bought " << person.second.first << " and sold " << person.second.second << " for a net transfer of $" << person.first.second << std::endl;
                            }
                        }

                        // for (int k1 = 0; k1 < all_statements)
                    }
                    i3 = 0;
                    // std::cout << i_3 << std::endl;

                } while (j1 != i2 && std::stoi(i_prices[i1][i2].first.second) != 0);
            }
            else
            {
                do
                {
                    j1 = i2;
                    pappu = 0;
                    max_p = std::stoi(i_prices[i1][i2].second.second.second);
                    while (i3 < i2)
                    {
                        if ((std::stoi(i_prices[i1][i3].second.first.first) > std::stoi(i_prices[i1][i3].second.first.second) || (std::stoi(i_prices[i1][i3].second.first.second) >= std::stoi(i_prices[i1][i2].second.first.first))) && (std::stoi(i_prices[i1][i2].second.first.second) >= std::stoi(i_prices[i1][i3].second.first.first) || std::stoi(i_prices[i1][i2].second.first.second) < std::stoi(i_prices[i1][i2].second.first.first)) && (comp != i_prices[i1][i3].first.first)) // && (std::stoi(i_prices[i1][i3].second.first.first) < std::stoi(i_prices[i1][i2].second.first.first)))
                        {
                            if (std::stoi(i_prices[i1][i3].second.second.second) < max_p && std::stoi(i_prices[i1][i3].first.second) != 0)
                            {
                                max_p = std::stoi(i_prices[i1][i3].second.second.second);
                                j1 = i3;
                            }
                            if (std::stoi(i_prices[i1][i3].second.second.second) == max_p && std::stoi(i_prices[i1][i3].first.second) != 0)
                            {
                                if (max_p == std::stoi(i_prices[i1][i2].second.second.second))
                                {
                                    if (pappu == 0)
                                    {
                                        j1 = i3;
                                    }
                                    pappu++;
                                }
                                if (j1 != i2 && std::stoi(i_prices[i1][i3].second.first.first) == std::stoi(i_prices[i1][j1].second.first.first))
                                {
                                    if (i_prices[i1][j1].second.second.first > i_prices[i1][i3].second.second.first)
                                    {
                                        j1 = i3;
                                    }
                                }
                            }
                        }
                        i3++;
                    }
                    if (j1 != i2 && std::stoi(i_prices[i1][j1].first.second) != 0 && std::stoi(i_prices[i1][i2].first.second) != 0)
                    {
                        if (std::stoi(i_prices[i1][j1].first.second) > std::stoi(i_prices[i1][i2].first.second))
                        {
                            int size_q;
                            size_q = 0;
                            int size_q1;
                            share_f = std::stoi(i_prices[i1][i2].first.second);
                            s1 = i_prices[i1][i2].first.second;
                            size_q1 = std::stoi(i_prices[i1][j1].first.second) - std::stoi(i_prices[i1][i2].first.second);
                            i_prices[i1][j1].first.second = std::to_string(size_q1);
                            i_prices[i1][i2].first.second = std::to_string(size_q);
                            // std::cout << i_prices[i1][j1].first.second << " " << i_prices[i1][i2].first.second << std::endl;
                            // if (j1 > i2)
                            // {
                            //     s2 = i_prices[i1][i2].second.second.second;
                            // }
                            // else
                            // {
                            s2 = i_prices[i1][j1].second.second.second;
                            // }
                        }
                        else
                        {
                            int size_q1 = 0;
                            int size_q;
                            share_f = std::stoi(i_prices[i1][j1].first.second);
                            s1 = i_prices[i1][j1].first.second;
                            size_q = std::stoi(i_prices[i1][i2].first.second) - std::stoi(i_prices[i1][j1].first.second);
                            // std::cout << size_q << std::endl;
                            i_prices[i1][i2].first.second = std::to_string(size_q);
                            i_prices[i1][j1].first.second = std::to_string(size_q1);
                            // std::cout << i_prices[i1][j1].first.second << " " << i_prices[i1][i2].first.second << std::endl;
                            // if (j1 > i2)
                            // {
                            //     s2 = i_prices[i1][i2].second.second.second;
                            // }
                            // else
                            // {
                            s2 = i_prices[i1][j1].second.second.second;
                            // }
                        }
                        complete_trade = complete_trade + 1;
                        shares_trade = shares_trade + share_f;
                        stat = i_prices[i1][i2].second.second.first + " purchased " + s1 + " shares of " + name_shares[i1] + " from " + i_prices[i1][j1].second.second.first + " for $" + s2 + "/share";
                        // std::cout << i_prices[i1][j1].second.first.first << " " << i_prices[i1][i2].second.first.first << std::endl;
                        // std::cout << stat << std::endl;
                        statements.push_back(stat);
                        money_transfer = money_transfer + (std::stoi(s1) * std::stoi(s2));
                        /*
                        all_statements.first.first = name
                        all_statements.first.second = amount transfer that happened
                        all_statements.second.first = number of orders bought
                        all_statements.second.second = number of orders sold.
                        */
                        for (auto &person : all_statements)
                        {
                            if (person.first.first == i_prices[i1][i2].second.second.first)
                            {
                                int bought;
                                int transfer;
                                // std::cout << s1 << " " << s2 << " " << person.second.first << std::endl;
                                bought = std::stoi(s1) + std::stoi(person.second.first);
                                transfer = std::stoi(person.first.second) - (std::stoi(s1) * std::stoi(s2));
                                person.second.first = std::to_string(bought);
                                person.first.second = std::to_string(transfer);
                                // std::cout << person.first.first << " bought " << person.second.first << " and sold " << person.second.second << " for a net transfer of $" << person.first.second << std::endl;
                            }
                            if (person.first.first == i_prices[i1][j1].second.second.first)
                            {
                                int sold;
                                int transfer_1;
                                // std::cout << s1 << " " << s2 << " " << person.second.first << std::endl;
                                sold = std::stoi(s1) + std::stoi(person.second.second);
                                transfer_1 = std::stoi(person.first.second) + (std::stoi(s1) * std::stoi(s2));
                                person.second.second = std::to_string(sold);
                                person.first.second = std::to_string(transfer_1);
                                // std::cout << person.first.first << " bought " << person.second.first << " and sold " << person.second.second << " for a net transfer of $" << person.first.second << std::endl;
                            }
                        }

                        /*
                        all_statements.first.first = name
                        all_statements.first.second = amount transfer that happened
                        all_statements.second.first = number of orders bought
                        all_statements.second.second = number of orders sold.
                        */
                    }
                    i3 = i_3;
                    // std::cout << i_prices[i1][i2].first.second << std::endl;
                } while (j1 != i2 && std::stoi(i_prices[i1][i2].first.second) != 0);
            }
        }
    }
    for (auto st : statements)
    {
        std::cout << st << std::endl;
    }
    std::cout << "---END OF THE DAY---" << std::endl;
    std::cout << "Total Amount of Money Transferred: $" << money_transfer << std::endl;
    std::cout << "Number of Completed Trades: " << complete_trade << std::endl;
    std::cout << "Number of Shares Traded: " << shares_trade << std::endl;
    // if ()
    for (auto person : all_statements)
    {
        std::cout << person.first.first << " bought " << person.second.first << " and sold " << person.second.second << " for a net transfer of $" << person.first.second << std::endl;
    }
}
