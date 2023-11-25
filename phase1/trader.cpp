#include "receiver.h"
#include <vector>
// #include "part1_functions.cpp"
// #include "part2_functions.cpp"
// #include "part3_functions.cpp"

// IMPLEMENT BINARY SEARCH FOR CHECKING FOR SHARE AS IT IS ALREADY SORTED

// int nth_call = 0;
std::vector<std::string> all_lines; // The actual lines(for outputting purposes)
std::vector<std::string> quantities;
bool CompareShare(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) { return a.first < b.first; }

struct line
{
    std::vector<std::pair<std::string, std::string>> shares;
    std::string price_b; // first is price and second is b/s(don't worry, it is going to be b)
    line(std::vector<std::pair<std::string, std::string>> shares, std::string price_b) : shares(shares), price_b(price_b) {}
};

std::string part3_change_sell_to_buy(std::string it, bool &is_it_s)
{
    if (it[it.size() - 1] == 's')
    {
        is_it_s = true;
        it[it.size() - 1] = 'b';
        int iter = it.size() - 3;
        std::string minus = "-";
        while (it[iter] != ' ')
        {
            iter--;
        }
        iter--;
        while (it[iter] != ' ')
        {
            iter--;
        }
        iter++;
        if (it[iter] == '-')
        {
            it.erase(iter, 1);
        }
        else
        {
            it.insert(iter, minus);
        }
    }
    return it;
}

std::string change_sell_to_buy(std::string it, bool &is_it_s)
{
    if (it[it.size() - 1] == 's')
    {
        is_it_s = true;
        it[it.size() - 1] = 'b';
        int iter = it.size() - 3;
        std::string minus = "-";
        while (it[iter] != ' ')
        {
            iter--;
        }
        iter++;
        if (it[iter] == '-')
        {
            it.erase(iter, 1);
        }
        else
        {
            it.insert(iter, minus);
        }
    }
    return it;
}

struct stocks
{
    std::string s;
    std::string bests_nt; // Non traded best price for sell
    std::string bestb_nt; // Non traded best price for buy
    int price_l;          // last traded price
    stocks(std::string s, std::string bests_nt, std::string bestb_nt, int price_l) : s(s), bests_nt(bests_nt), bestb_nt(bestb_nt), price_l(price_l) {}
};

void rectify(std::string message, int &iter)
{
    while (!isalpha(message[iter]))
    {
        iter++;
    }
}

std::string switch_it(std::string it)
{
    if (it[it.size() - 1] == 'b')
    {
        it[it.size() - 1] = 's';
    }
    else
    {
        it[it.size() - 1] = 'b';
    }
    return it;
}

std::string part3_switch_it(std::string it, int &i, std::vector<int> &currenttuple)
{
    if (it[it.size() - 1] == 'b')
    {
        it[it.size() - 1] = 's';
    }
    else
    {
        it[it.size() - 1] = 'b';
    }
    int iter = it.size() - 3;
    int p2 = iter;
    while (it[iter] != ' ')
    {
        iter--;
    }
    it.erase(iter + 1, p2 - iter);
    it.insert(iter + 1, std::to_string(currenttuple[currenttuple.size() - 1 - i]));
    return it;
}

void add_to_it(std::vector<stocks> &st, std::string token)
{
    std::string stock;
    std::string str_price;
    int price;
    int iter = 0;
    while (token[iter] != ' ')
    {
        stock += token[iter];
        iter++;
    }
    iter++;
    while (token[iter] != ' ')
    {
        str_price += token[iter];
        iter++;
    }
    price = stoi(str_price);
    bool found = false;
    int index;
    for (index = 0; index < st.size(); index++)
    {
        if (st[index].s == stock)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        if (token[token.size() - 1] == 's')
        {
            if (st[index].bests_nt != "N" && price >= stoi(st[index].bests_nt))
            {
                std::cout << "No Trade" << std::endl;
                return;
            }
            else
            {
                st[index].bests_nt = str_price;
                // std::cout<<"yo boizz";
            }
            if (st[index].bests_nt == st[index].bestb_nt)
            {
                std::cout << "No Trade" << std::endl;
                st[index].bestb_nt = "N";
                st[index].bests_nt = "N";
                return;
            }
            if (price < st[index].price_l)
            {
                std::cout << switch_it(token) << std::endl;
                st[index].price_l = price;
                st[index].bests_nt = "N";
            }
            else
            {
                std::cout << "No Trade" << std::endl;
            }
        }
        else
        {
            if (st[index].bestb_nt != "N" && price <= stoi(st[index].bestb_nt))
            {
                std::cout << "No Trade" << std::endl;
                return;
            }
            else
            {
                st[index].bestb_nt = str_price;
            }
            if (st[index].bestb_nt == st[index].bests_nt)
            {
                std::cout << "No Trade" << std::endl;
                st[index].bestb_nt = "N";
                st[index].bests_nt = "N";
                return;
            }
            if (price > st[index].price_l)
            {
                std::cout << switch_it(token) << std::endl;
                st[index].price_l = price;
                st[index].bestb_nt = "N";
            }
            else
            {
                std::cout << "No Trade" << std::endl;
            }
        }
    }
    else
    {
        stocks S(stock, "N", "N", price);
        st.push_back(S);
        std::cout << switch_it(token) << std::endl;
    }
}

std::pair<line, line> pre_process(std::string temp, bool &is_it_s)
{
    // std::cerr << "I reached here safely" << std::endl;
    int u = temp.length() - 1;
    // std::cerr << u << std::endl;
    int p1, p2;
    std::vector<std::pair<std::string, std::string>> r1;     // This will be shares
    std::vector<std::pair<std::string, std::string>> act_r1; // This will be shares
    std::string r2;                                          // This will be price_b
    std::string act_r2;
    bool swi_tch = true; // modification of count (as in your code)
    u = u - 2;
    p1 = u;
    while (temp[u] != ' ')
    {
        u--;
    }
    p2 = u;
    u--;
    // std::cerr << "I reached here safely" << std::endl;
    // std::cerr << "p1 and p2 are " << p1 << " " << p2 << std::endl;
    r2 = temp.substr(p2 + 1, p1 - p2);
    act_r2 = r2;
    if (is_it_s)
    {
        if (act_r2[0] == '-')
        {
            act_r2.erase(0, 1);
        }
        else
        {
            act_r2.insert(0, "-");
        }
    }

    // std::cerr << "modified price is " << r2 << std::endl;
    // std::cerr << "actual price is " << act_r2 << std::endl;

    std::string t_string;
    std::string t_string1;
    std::pair<std::string, std::string> temp_pair;
    std::string act_t_string;
    std::pair<std::string, std::string> act_temp_pair;
    while (u >= 0)
    {
        if (swi_tch)
        {
            p1 = u;
            while (temp[u] != ' ')
            {
                u--;
            }
            p2 = u;
            u--;
            // std::cerr << "p1 , p2 ,u are " << p1 << " " << p2 << " " << u << std::endl;
            t_string = temp.substr(p2 + 1, p1 - p2);
            act_t_string = t_string;
            if (is_it_s)
            {
                if (t_string[0] == '-')
                {
                    t_string.erase(0, 1);
                }
                else
                {
                    t_string.insert(0, "-");
                }
            }
            // std::cerr << t_string << std::endl;
            swi_tch = false;
        }
        else
        {
            p1 = u;
            while (temp[u] != ' ')
            {
                u--;
                if (u == 0 || u == -1)
                    break;
            }
            p2 = u;
            if (p2 == 0)
            {
                p2--;
            } // for accounting the corner case
            u--;
            // std::cerr << "p1 , p2 ,u are " << p1 << " " << p2 << " " << u << std::endl;
            t_string1 = temp.substr(p2 + 1, p1 - p2);
            temp_pair = std::make_pair(t_string1, t_string);
            act_temp_pair = std::make_pair(t_string1, act_t_string);
            // std::cerr << t_string1 << std::endl;
            r1.push_back(temp_pair);
            act_r1.push_back(act_temp_pair);
            swi_tch = true;
        }
    }
    // NEW LINE FOR SORTING THE STOCK PAIRS
    sort(r1.begin(), r1.end(), CompareShare);
    sort(act_r1.begin(), act_r1.end(), CompareShare);
    // std::cerr << "the following is modified_lines_b's shares ";
    // for (int i = 0; i < r1.size(); i++)
    // {
    //     std::cerr << r1[i].first << " " << r1[i].second << " ";
    // }
    // std::cerr << std::endl;
    // std::cerr << "the following is actual_lines_b's shares ";
    // for (int i = 0; i < r1.size(); i++)
    // {
    //     std::cerr << act_r1[i].first << " " << act_r1[i].second << " ";
    // }
    // std::cerr << std::endl;
    // std::cerr << "the modified price is ";
    //////////////////////////////////////
    line L1(r1, r2);
    line L2(act_r1, r2);
    // std::cerr << "I reached here safely" << std::endl;
    return std::make_pair(L1, L2);
}

std::pair<line, line> part3_pre_process(std::string temp, bool &is_it_s)
{
    // std::cerr << "I reached part3_preprocess line 352 safely" << std::endl;
    int u = temp.length() - 1;
    // std::cerr << "u is "<<u << std::endl;
    int p1, p2;
    std::vector<std::pair<std::string, std::string>> r1;     // This will be shares
    std::vector<std::pair<std::string, std::string>> act_r1; // This will be shares
    std::string r2;                                          // This will be price_b
    std::string act_r2;
    bool swi_tch = true; // modification of count (as in your code)
    u = u - 2;
    p1 = u;
    while (temp[u] != ' ')
    {
        u--;
    }
    p2 = u;
    u--;
    // std::cerr << "I reached here safely" << std::endl;
    // std::cerr << "p1 and p2 are " << p1 << " " << p2 << std::endl;
    quantities.push_back(temp.substr(p2 + 1, p1 - p2));
    p1 = u;
    while (temp[u] != ' ')
    {
        u--;
    }
    p2 = u;
    u--;
    r2 = temp.substr(p2 + 1, p1 - p2);
    // std::cerr << "modified price is " << r2 << std::endl;
    // std::cerr << "actual price is " << act_r2 << std::endl;

    std::string t_string;
    std::string t_string1;
    std::pair<std::string, std::string> temp_pair;
    std::string act_t_string;
    std::pair<std::string, std::string> act_temp_pair;
    while (u >= 0)
    {
        if (swi_tch)
        {
            p1 = u;
            while (temp[u] != ' ')
            {
                u--;
            }
            p2 = u;
            u--;
            // std::cerr << "p1 , p2 ,u are " << p1 << " " << p2 << " " << u << std::endl;
            t_string = temp.substr(p2 + 1, p1 - p2);
            act_t_string = t_string;
            if (is_it_s)
            {
                if (t_string[0] == '-')
                {
                    t_string.erase(0, 1);
                }
                else
                {
                    t_string.insert(0, "-");
                }
            }
            // std::cerr << t_string << std::endl;
            swi_tch = false;
        }
        else
        {
            p1 = u;
            while (temp[u] != ' ')
            {
                u--;
                if (u == 0 || u == -1)
                    break;
            }
            p2 = u;
            if (p2 == 0)
            {
                p2--;
            } // for accounting the corner case
            u--;
            // std::cerr << "p1 , p2 ,u are " << p1 << " " << p2 << " " << u << std::endl;
            t_string1 = temp.substr(p2 + 1, p1 - p2);
            temp_pair = std::make_pair(t_string1, t_string);
            act_temp_pair = std::make_pair(t_string1, act_t_string);
            // std::cerr << t_string1 << std::endl;
            r1.push_back(temp_pair);
            act_r1.push_back(act_temp_pair);
            swi_tch = true;
        }
    }
    // NEW LINE FOR SORTING THE STOCK PAIRS
    sort(r1.begin(), r1.end(), CompareShare);
    sort(act_r1.begin(), act_r1.end(), CompareShare);
    line L1(r1, r2);
    line L2(act_r1, r2);
    // std::cerr << "I reached here safely" << std::endl;
    return std::make_pair(L1, L2);
}

int find_share(std::string share, std::vector<std::pair<std::string, std::string>> shares)
{
    for (int i = 0; i < shares.size(); i++)
    {
        if (shares[i].first == share)
        {
            return i;
        }
    }
    return -1;
}

void add_share_to_line(std::pair<std::string, std::string> share, line &that)
{
    int i = find_share(share.first, that.shares);
    if (i == -1)
    {
        (that.shares).push_back(share);
    }
    else
    {
        (that.shares[i]).second = std::to_string(std::stoi((that.shares[i]).second) + std::stoi(share.second));
    }
}

void add_line_to_line(line &that, line this_one) // we_are_adding_this_one_to_that
{
    for (int i = 0; i < (this_one.shares).size(); i++)
    {
        add_share_to_line((this_one.shares)[i], that);
    }
    that.price_b = std::to_string(std::stoi(this_one.price_b) + std::stoi((that.price_b)));
}

void part3_add_share_to_line(std::pair<std::string, std::string> share, line &that, int j)
{
    int i = find_share(share.first, that.shares);
    if (i == -1)
    {
        share.second = std::to_string((std::stoi(share.second)) * (j));
        (that.shares).push_back(share);
    }
    else
    {
        // std::cerr<<"checking if that.share[i] and share.first are same "<<share.first<<" "<<(that.shares[i]).first<<std::endl;
        (that.shares[i]).second = std::to_string(std::stoi((that.shares[i]).second) + ((std::stoi(share.second)) * (j)));
    }
}

void part3_add_line_line(line &that, line this_one, int j)
{
    if (j == 0)
        return;
    // std::cerr<<"j is "<<j<<std::endl;
    for (int i = 0; i < (this_one.shares).size(); i++)
    {
        part3_add_share_to_line((this_one.shares)[i], that, j);
    }
    that.price_b = std::to_string(std::stoi(that.price_b) + (j * std::stoi((this_one.price_b))));
}

void check_for_arbitrage(std::vector<line> &modified_lines_b, std::vector<line> &actual_lines_b, int &total_profit, std::vector<bool> are_it_is)
{

    int n = modified_lines_b.size() - 1;
    if (n == 0)
    {
        std::cout << "No Trade" << std::endl;
        return;
    }
    // std::cerr << "I reached check for 2nd time safely" << std::endl;
    // Total number of subsets is 2^n
    long long int totalSubsets = (1 << n);

    int max_profit_index;
    int max_profit = 0;
    std::vector<std::pair<std::string, std::string>> empty_shares;
    std::string empty_price_b = "0";
    line now(empty_shares, empty_price_b);

    // std::cerr << "I reached check for 2nd time safely" << std::endl;
    for (int i = 0; i < totalSubsets; ++i)
    {
        // std::cerr << "I reached check for " << i << " time safely" << std::endl;
        for (int j = 0; j < n; ++j)
        {
            if (i & (1 << j))
            {
                add_line_to_line(now, modified_lines_b[j]);
            }
        }
        // Z -1 Y 1 0 s#
        add_line_to_line(now, modified_lines_b[n]);
        // std::cerr << "I reached check for 2nd time safely" << std::stoi(now.price_b) << std::endl;
        if (std::stoi(now.price_b) > 0)
        {
            bool flag = true;
            // std::cerr << "shares size is " << (now.shares).size() << std::endl;
            for (int p = 0; p < (now.shares).size(); p++)
            {
                if (std::stoi(now.shares[p].second) != 0)
                    flag = false;
            }

            if (flag && std::stoi(now.price_b) > max_profit)
            {
                max_profit = std::stoi(now.price_b);
                max_profit_index = i;
            }
        }
        (now.shares).clear();
        now.price_b = "0";
    }

    if (max_profit > 0)
    {
        std::cout << switch_it(all_lines[n]) << std::endl;
        all_lines.erase(all_lines.begin() + n);
        modified_lines_b.erase(modified_lines_b.begin() + n);
        actual_lines_b.erase(actual_lines_b.begin() + n);
        are_it_is.erase(are_it_is.begin() + n);

        // std::cerr << all_lines.size() << " " << n << std::endl;
        // std::cerr << max_profit << std::endl;
        // std::cerr << max_profit_index << std::endl;
        for (int j = n - 1; j >= 0; j--)
        {
            if (max_profit_index & (1 << j))
            {
                std::cout << switch_it(all_lines[j]) << std::endl;
                all_lines.erase(all_lines.begin() + j);
                modified_lines_b.erase(modified_lines_b.begin() + j);
                actual_lines_b.erase(actual_lines_b.begin() + j);
                are_it_is.erase(are_it_is.begin() + j);
            }
        }
        total_profit += max_profit;
    }
    else
    {
        std::cout << "No Trade" << std::endl;
    }
}

void part3_generateTuples(std::vector<std::string> &sets, std::vector<int> &my_tuple, int index, std::vector<line> &modified_lines_b, std::vector<line> &actual_lines_b, line now, int &max_profit, int &max_profit_index, int &nth_call)
{
    // See how to remove last element zero case
    if (index == sets.size())
    {
        // std::cerr << "NTH CALL is " << nth_call << std::endl;
        if (nth_call == 0)
        {
            nth_call++;
            return;
        }
        nth_call++;
        // std::cerr << "printing my_tuple ";
        for (int i = 0; i < my_tuple.size(); i++)
        {
            // std::cerr << my_tuple[i] << " ";
            part3_add_line_line(now, modified_lines_b[i], my_tuple[i]);
        }
        // std::cerr << std::endl;
        if (std::stoi(now.price_b) > 0)
        {
            bool flag = true;
            // std::cerr << "shares size is " << (now.shares).size() << std::endl;
            // std::cerr << "printing price_b " << now.price_b << " and now ";
            for (int p = 0; p < (now.shares).size(); p++)
            {
                // std::cerr << now.shares[p].first << " " << now.shares[p].second << " ";
                if (std::stoi((now.shares[p]).second) != 0)
                    flag = false;
            }
            // std::cerr << "flag is " << flag << std::endl;

            if (flag && std::stoi(now.price_b) > max_profit)
            {
                max_profit = std::stoi(now.price_b);
                max_profit_index = nth_call - 1;
            }
        }
        now.price_b = "0";
        now.shares.clear();
        return;
    }
    for (int i = 0; i <= std::stoi(sets[index]); i++)
    {
        my_tuple[index] = i;
        part3_generateTuples(sets, my_tuple, index + 1, modified_lines_b, actual_lines_b, now, max_profit, max_profit_index, nth_call);
    }
}

std::vector<int> get_n(int nth_call)
{
    // std::cerr << "INITIATED GET_N " << std::endl;
    std::vector<int> currentTuple;
    for (int i = quantities.size() - 1; i >= 0; i--)
    {
        // std::cerr<<"the current quantity is "<<quantities[i]<<std::endl;
        currentTuple.push_back(nth_call % (std::stoi(quantities[i]) + 1));
        nth_call = nth_call / (std::stoi(quantities[i]) + 1);
    }
    // reverse(currentTuple.begin(),currentTuple.end());
    return currentTuple;
}

void part3_check_for_arbitrage(std::vector<line> &modified_lines_b, std::vector<line> &actual_lines_b, int &total_profit, std::vector<bool> are_it_is)
{
    int n = modified_lines_b.size() - 1;
    // std::cerr << "n is " << n << std::endl;
    if (n == 0)
    {
        std::cout << "No Trade" << std::endl;
        return;
    }
    // std::cerr << "I reached check for 2nd time safely" << std::endl;
    // Total number of subsets is 2^n

    int max_profit_index = -1;
    int max_profit = 0;
    std::vector<std::pair<std::string, std::string>> empty_shares;
    std::string empty_price_b = "0";
    line now(empty_shares, empty_price_b);

    int nth_call = 0;

    // std::cerr << "Printing quantities ";
    // for (int i = 0; i < quantities.size(); i++)
    // {
    //     std::cerr << quantities[i] << " ";
    // }
    // std::cerr << std::endl;

//     std::cerr << "Printing modified_lines_b and quantities " << std::endl;
//     for (int i = 0; i < modified_lines_b.size(); i++)
//     {
//         std::cerr << "the shares are ";
//         for (int j = 0; j < (modified_lines_b[i].shares).size(); j++)
//         {
//             std::cerr << (modified_lines_b[i].shares)[j].first << " " << (modified_lines_b[i].shares)[j].second << " ";
//         }
//         std::cerr << "the price is " << modified_lines_b[i].price_b << " quantity is " << quantities[i] << std::endl;
//     }

//     std::cerr << "all_lines " << std::endl;
//     for (int i = 0; i < all_lines.size(); i++)
//     {
//         std::cerr << all_lines[i] << std::endl;
//     }

    // std::cerr << "Printing actual_lines_b " << std::endl;
    // for (int i = 0; i < actual_lines_b.size(); i++)
    // {
    //     std::cerr << "the shares are ";
    //     for (int j = 0; j < (actual_lines_b[i].shares).size(); j++)
    //     {
    //         std::cerr << (actual_lines_b[i].shares)[j].first << " " << (actual_lines_b[i].shares)[j].second << " ";
    //     }
    //     std::cerr << "the price is " << actual_lines_b[i].price_b << std::endl;
    // }
    // std::cerr<<std::endl;

    // std::cerr << "Printing all_lines " << std::endl;
    // for (int i = 0; i < all_lines.size(); i++)
    // {
    //     std::cerr << all_lines[i] << std::endl;
    // }
    // std::cerr << std::endl;
    std::vector<int> my_tuple(quantities.size(), 0);
    part3_generateTuples(quantities, my_tuple, 0, modified_lines_b, actual_lines_b, now, max_profit, max_profit_index, nth_call);

    if (max_profit > 0)
    {
        // std::cerr << "I reached check for 2nd time safely and max_profit_index is " << max_profit_index << std::endl;
        std::vector<int> currenttuple = get_n(max_profit_index);

        // std::cerr << "Printing currenttuple "<<currenttuple.size()<<" ";
        // for (int i = 0; i < currenttuple.size(); i++)
        // {
        //     std::cerr << currenttuple[i] << " ";
        // }
        // std::cerr << std::endl;
        // std::cerr << "printing quantities "<<quantities.size();
        for (int i = quantities.size() - 1; i >= 0; i--)
        {
            // std::cerr << quantities[i] << " ";
            quantities[i] = std::to_string(std::stoi(quantities[i]) - currenttuple[quantities.size()-1-i]);
        }
        // std::cerr << std::endl;

        for (int i = currenttuple.size() - 1; i >= 0; i--)
        {
            
            // std::cerr << "the value of quantity of " << i << "th line is " << quantities[i]<<" "<<currenttuple[currenttuple.size()-1-i] << std::endl;
            if (currenttuple[currenttuple.size()-1-i] != 0)
            {
                std::cout << part3_switch_it(all_lines[i], i, currenttuple) << std::endl;
                // std::cerr << part3_switch_it(all_lines[i], i, currenttuple) << std::endl;
            }
            if (quantities[i] == "0")
            {
                modified_lines_b.erase(modified_lines_b.begin() + i);
                actual_lines_b.erase(actual_lines_b.begin() + i);
                are_it_is.erase(are_it_is.begin() + i);
                // std::cerr << "line " << i << " is erased" << std::endl;
                all_lines.erase(all_lines.begin() + i);
                quantities.erase(quantities.begin() + i);
            }
        }
        total_profit += max_profit;
    }
    else
    {
        std::cout << "No Trade" << std::endl;
    }
}

// actual_lines_b[n].price_b == actual_lines_b[i].price_b

void check_for_cancellation(std::vector<line> &actual_lines_b, std::vector<bool> &are_it_s, std::vector<line> &modified_lines_b)
{
    int n = actual_lines_b.size() - 1;
    int first = -1;
    int second = -1;
    for (int i = 0; i < n; i++)
    {
        if (actual_lines_b[n].shares == actual_lines_b[i].shares)
        {
            if (first == -1)
            {
                first = i;
            }
            else
            {
                second = i;
                break;
            }
        }
    }
    // std::cerr << "first is " << first << "second is " << second << std::endl;
    if (first == -1 && second == -1)
    {
        return;
    }
    else if (second == -1)
    {
        if (are_it_s[first] == are_it_s[n])
        {
            if (std::stoi(actual_lines_b[n].price_b) <= std::stoi(actual_lines_b[first].price_b))
            {
                all_lines.erase(all_lines.begin() + n);
                actual_lines_b.erase(actual_lines_b.begin() + n);
                modified_lines_b.erase(modified_lines_b.begin() + n);
                are_it_s.erase(are_it_s.begin() + n);
                return;
            }
            else
            {
                all_lines.erase(all_lines.begin() + first);
                actual_lines_b.erase(actual_lines_b.begin() + first);
                modified_lines_b.erase(modified_lines_b.begin() + first);
                are_it_s.erase(are_it_s.begin() + first);
                return;
            }
        }
        else
        {
            if (std::stoi(actual_lines_b[n].price_b) + std::stoi(actual_lines_b[first].price_b) == 0)
            {
                all_lines.erase(all_lines.begin() + n);
                actual_lines_b.erase(actual_lines_b.begin() + n);
                modified_lines_b.erase(modified_lines_b.begin() + n);
                are_it_s.erase(are_it_s.begin() + n);
                all_lines.erase(all_lines.begin() + first);
                actual_lines_b.erase(actual_lines_b.begin() + first);
                modified_lines_b.erase(modified_lines_b.begin() + first);
                are_it_s.erase(are_it_s.begin() + first);
                return;
            }
        }
    }
    else
    {
        int same;
        int diff;
        if (are_it_s[first] == are_it_s[n])
        {
            same = first;
            diff = second;
        }
        else
        {
            same = second;
            diff = first;
        }

        if (std::stoi(actual_lines_b[n].price_b) <= std::stoi(actual_lines_b[same].price_b))
        {
            all_lines.erase(all_lines.begin() + n);
            actual_lines_b.erase(actual_lines_b.begin() + n);
            modified_lines_b.erase(modified_lines_b.begin() + n);
            are_it_s.erase(are_it_s.begin() + n);
            return;
        }
        else
        {
            all_lines.erase(all_lines.begin() + same);
            actual_lines_b.erase(actual_lines_b.begin() + same);
            modified_lines_b.erase(modified_lines_b.begin() + same);
            are_it_s.erase(are_it_s.begin() + same);
            if (same < diff)
            {
                diff--;
            }
            n--;
        }

        if (std::stoi(actual_lines_b[n].price_b) + std::stoi(actual_lines_b[diff].price_b) == 0)
        {
            all_lines.erase(all_lines.begin() + n);
            actual_lines_b.erase(actual_lines_b.begin() + n);
            modified_lines_b.erase(modified_lines_b.begin() + n);
            are_it_s.erase(are_it_s.begin() + n);
            all_lines.erase(all_lines.begin() + diff);
            actual_lines_b.erase(actual_lines_b.begin() + diff);
            modified_lines_b.erase(modified_lines_b.begin() + diff);
            are_it_s.erase(are_it_s.begin() + diff);
            return;
        }
    }
}

void part3_check_for_cancellation(std::vector<line> &actual_lines_b, std::vector<bool> &are_it_s, std::vector<line> &modified_lines_b)
{
    int n = actual_lines_b.size() - 1;
    int first = 0;
    for (first = 0; first < n; first++)
    {
        if ((actual_lines_b[n].price_b == actual_lines_b[first].price_b && are_it_s[first] == are_it_s[n]) || ((std::stoi(actual_lines_b[n].price_b) + std::stoi(actual_lines_b[first].price_b) == 0) && are_it_s[first] != are_it_s[n]))
        {
            if (actual_lines_b[n].shares == actual_lines_b[first].shares)
            {
                break;
            }
        }
    }
    // std::cerr << "first is " << first << "second is " << second << std::endl;x
    if (first == n)
    {
        return;
    }
    else
    {
        if (are_it_s[first] == are_it_s[n])
        {
            quantities[n] = std::to_string(std::stoi(quantities[n]) + std::stoi(quantities[first]));
            all_lines.erase(all_lines.begin() + first);
            quantities.erase(quantities.begin() + first);
            actual_lines_b.erase(actual_lines_b.begin() + first);
            modified_lines_b.erase(modified_lines_b.begin() + first);
            are_it_s.erase(are_it_s.begin() + first);
            return;
        }
        else
        {
            if (std::stoi(quantities[n]) == std::stoi(quantities[first]))
            {
                all_lines.erase(all_lines.begin() + n);
                actual_lines_b.erase(actual_lines_b.begin() + n);
                modified_lines_b.erase(modified_lines_b.begin() + n);
                are_it_s.erase(are_it_s.begin() + n);
                quantities.erase(quantities.begin() + n);
                all_lines.erase(all_lines.begin() + first);
                actual_lines_b.erase(actual_lines_b.begin() + first);
                modified_lines_b.erase(modified_lines_b.begin() + first);
                are_it_s.erase(are_it_s.begin() + first);
                quantities.erase(quantities.begin() + first);
                return;
            }
            else if (std::stoi(quantities[n]) > std::stoi(quantities[first]))
            {
                quantities[n] = std::to_string(std::stoi(quantities[n]) - std::stoi(quantities[first]));
                all_lines.erase(all_lines.begin() + first);
                quantities.erase(quantities.begin() + first);
                actual_lines_b.erase(actual_lines_b.begin() + first);
                modified_lines_b.erase(modified_lines_b.begin() + first);
                are_it_s.erase(are_it_s.begin() + first);
                return;
            }
            else
            {
                quantities[first] = std::to_string(std::stoi(quantities[first]) - std::stoi(quantities[n]));
                all_lines.erase(all_lines.begin() + n);
                actual_lines_b.erase(actual_lines_b.begin() + n);
                modified_lines_b.erase(modified_lines_b.begin() + n);
                are_it_s.erase(are_it_s.begin() + n);
                quantities.erase(quantities.begin() + n);
                return;
            }
        }
    }
}

int main(int argv, char **argc)
{
    Receiver rcv;
    // sleep(5);
    bool found_dollar = false;
    std::string message = rcv.readIML();
    while (!found_dollar)
    {
        std::string message1 = rcv.readIML();
        message.append(message1);
        if (message.find('$') != std::string::npos)
        {
            // std::message1 = rcv.readIML();
            found_dollar = true;
        }
    }
    rcv.terminate();

    if (argc[1][0] == '1')
    {
        // for (int i = 0; i < message.size(); i++)
        // {
        //     std::cout << message[i];
        // }

        // return 0;
        std::vector<stocks> st_vec;
        int iter = 0;
        std::string temp = "";
        while (iter < message.length())
        {
            while (message[iter] != '#')
            {
                temp += message[iter];
                iter++;
            }
            rectify(message, iter);
            add_to_it(st_vec, temp);
            temp = "";
        }
    }
    else if (argc[1][0] == '2')
    {
        std::vector<line> modified_lines_b; // All lines are going to be stored in the form of buys
        std::vector<line> actual_lines_b;
        std::vector<bool> are_it_s;
        int iter = 0;
        std::string temp = "";
        int total_profit = 0;
        while (iter < message.length())
        {
            while (message[iter] != '#')
            {
                // std::cerr << iter << std::endl;
                temp += message[iter];
                iter++;
            }
            // std::cerr << temp << std::endl;
            rectify(message, iter);
            // std::cerr << iter << std::endl;
            all_lines.push_back(temp); // Pushed the current line "as it is" in all_lines (for outputting purpose)
            bool is_it_s = false;
            std::vector<std::pair<std::string, std::string>> empty_shares;
            std::string empty_price_b = "0";
            line modi(empty_shares, empty_price_b);
            line actu(empty_shares, empty_price_b);
            std::pair<line, line> hi = std::make_pair(modi, actu);
            hi = pre_process(change_sell_to_buy(temp, is_it_s), is_it_s);
            modified_lines_b.push_back(hi.first);
            actual_lines_b.push_back(hi.second);
            are_it_s.push_back(is_it_s);
            // std::cerr << temp << std::endl;
            temp = "";

            check_for_cancellation(actual_lines_b, are_it_s, modified_lines_b);
            check_for_arbitrage(modified_lines_b, actual_lines_b, total_profit, are_it_s);
        }
        std::cout << total_profit;
    }
    else if (argc[1][0] == '3')
    {
        std::vector<line> modified_lines_b; // All lines are going to be stored in the form of buys
        std::vector<line> actual_lines_b;
        std::vector<bool> are_it_s;
        int iter = 0;
        std::string temp = "";
        int total_profit = 0;
        while (iter < message.length())
        {
            while (message[iter] != '#')
            {
                // std::cerr << iter << std::endl;
                temp += message[iter];
                iter++;
            }
            // std::cerr << temp << std::endl;
            rectify(message, iter);
            // std::cerr << iter << std::endl;
            all_lines.push_back(temp); // Pushed the current line "as it is" in all_lines (for outputting purpose)
            bool is_it_s = false;
            std::vector<std::pair<std::string, std::string>> empty_shares;
            std::string empty_price_b = "0";
            line modi(empty_shares, empty_price_b);
            line actu(empty_shares, empty_price_b);
            std::pair<line, line> hi = std::make_pair(modi, actu);
            hi = part3_pre_process(part3_change_sell_to_buy(temp, is_it_s), is_it_s);
            modified_lines_b.push_back(hi.first);
            actual_lines_b.push_back(hi.second);
            are_it_s.push_back(is_it_s);
            // std::cerr << temp << std::endl;
            temp = "";

            // std::cerr << "Printing modified_lines_b "<<std::endl;
            // for (int i = 0; i < modified_lines_b.size(); i++)
            // {
            //     std::cerr<<"the shares are ";
            //     for (int j = 0; j < (modified_lines_b[i].shares).size(); j++)
            //     {
            //         std::cerr<<(modified_lines_b[i].shares)[j].first<<" "<<(modified_lines_b[i].shares)[j].second<<" ";
            //     }
            //     std::cerr<<"the price is "<<modified_lines_b[i].price_b<<std::endl;
            // }

            // std::cerr << "Printing actual_lines_b "<<std::endl;
            // for (int i = 0; i < actual_lines_b.size(); i++)
            // {
            //     std::cerr<<"the shares are ";
            //     for (int j = 0; j < (actual_lines_b[i].shares).size(); j++)
            //     {
            //         std::cerr<<(actual_lines_b[i].shares)[j].first<<" "<<(actual_lines_b[i].shares)[j].second<<" ";
            //     }
            //     std::cerr<<"the price is "<<actual_lines_b[i].price_b<<std::endl;
            // }

            // std::cerr << "Printing are_it_is vector ";
            // for (int i = 0; i < are_it_s.size(); i++)
            // {
            //     std::cerr << are_it_s[i] << " ";
            // }
            // std::cerr << std::endl;

            part3_check_for_cancellation(actual_lines_b, are_it_s, modified_lines_b);
            part3_check_for_arbitrage(modified_lines_b, actual_lines_b, total_profit, are_it_s);
        }
        std::cout << total_profit;
    }
}
