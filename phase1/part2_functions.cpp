#include <iostream>
#include <string>
#include <vector>


// Later change the preprocess because we are sending only "buy" lines into structure, so no need to check for that

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

struct line
{
    std::vector<std::pair<std::string, std::string>> shares;
    std::pair<std::string, std::string> price_b_s; // first is price and second is b/s(don't worry, it is going to be b)
    std::vector<int> indices_of_lines_in_input;
    line(std::vector<std::pair<std::string, std::string>> shares, std::pair<std::string, std::string> price_b_s, std::vector<int> indices_of_lines_in_input) : shares(shares), price_b_s(price_b_s), indices_of_lines_in_input(indices_of_lines_in_input) {}
};

std::string change_sell_to_buy(std::string it)
{
    if (it[it.size() - 1] == 's')
    {
        it[it.size() - 1] = 'b';
        int iter = it.size() - 3;
        std::string minus = "-";
        while (it[iter] != ' ')
        {
            iter--;
        }
        iter++;
        it.insert(iter, minus);
    }
    return it;
}

line pre_process(std::string temp, int index_of_line)
{
    int u = temp.length() - 1;
    int p1, p2;
    std::vector<std::pair<std::string, std::string>> r1; // This will be shares
    std::pair<std::string, std::string> r2;              // This will be price_b_s
    bool swi_tch = true;                                 // modification of count (as in your code)
    r2.second = temp[u];
    u = u - 2;
    p1 = u;
    while (temp[u] != ' ')
    {
        u--;
    }
    p2 = u;
    r2.first = temp.substr(p2 + 1, p1 - p2);
    std::string t_string;
    std::string t_string1;
    std::pair<std::string, std::string> temp_pair;
    // Now i is at the end of quantity of last stock
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
            t_string = temp.substr(p2 + 1, p1 - p2);
            swi_tch = false;
        }
        else
        {
            p1 = u;
            while (temp[u] != ' ')
            {
                u--;
                if (u == 0)
                    break;
            }
            p2 = u;
            if (!p2)
            {
                p2--;
            } // for accounting the corner case
            u--;
            t_string1 = temp.substr(p2 + 1, p1 - p2);
            temp_pair = std::make_pair(t_string1, t_string);
            r1.push_back(temp_pair);
            swi_tch = true;
        }
    }
    std::vector<int> only_now;
    only_now.push_back(index_of_line);
    line L(r1, r2, only_now);
    return L;
}

void add_line_to_structures(line thisline, std::vector<line> &Structures_b)
{
    std::vector<line> temp_strctr = Structures_b;
    for (int i = 0; i < temp_strctr.size(); i++)
    {
        add_line_to_line(temp_strctr[i], thisline);
    }
    Structures_b.insert(std::end(Structures_b), std::begin(temp_strctr), std::end(temp_strctr));
    Structures_b.push_back(thisline);
    check_for_arbitrage(Structures_b);
}


void add_line_to_line(line &that, line this_one) // we_are_adding_this_one_to_that
{
    for (int i = 0; i < (this_one.shares).size(); i++)
    {
        add_share_to_line((this_one.shares)[i], that);
    }
    (that.price_b_s).first = std::to_string(std::stoi(this_one.price_b_s.first) + std::stoi((that.price_b_s).first));
    that.indices_of_lines_in_input.insert(that.indices_of_lines_in_input.end(), (this_one.indices_of_lines_in_input).begin(), this_one.indices_of_lines_in_input.end());
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