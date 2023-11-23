#include "receiver.h"
#include <vector>
// #include "part1_functions.cpp"
// #include "part2_functions.cpp"
// #include "part3_functions.cpp"

std::vector<std::string> all_lines; // The actual lines(for outputting purposes)

bool CompareShare(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) { return a.first < b.first; }

struct line
{
    std::vector<std::pair<std::string, std::string>> shares;
    std::string price_b; // first is price and second is b/s(don't worry, it is going to be b)
    line(std::vector<std::pair<std::string, std::string>> shares, std::string price_b) : shares(shares), price_b(price_b) {}
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
    for (int i = 0; i < st.size(); i++)
    {
        if (st[i].s == stock)
        {
            found = true;
            index = i;
            break;
        }
    }
    if (found)
    {
        if (token[token.size() - 1] == 's')
        {
            if (st[index].bests_nt != "N" && price >= stoi(st[index].bests_nt))
            {
                std::cout << "No Trade\n";
                return;
            }
            else
            {
                st[index].bests_nt = str_price;
                // std::cout<<"yo boizz";
            }
            if (st[index].bests_nt == st[index].bestb_nt)
            {
                std::cout << "No Trade\n";
                st[index].bestb_nt = "N";
                st[index].bests_nt = "N";
                return;
            }
            if (price < st[index].price_l)
            {
                std::cout << switch_it(token) << "\n";
                st[index].price_l = price;
                st[index].bests_nt = "N";
            }
            else
            {
                std::cout << "No Trade\n";
            }
        }
        else
        {
            if (st[index].bestb_nt != "N" && price <= stoi(st[index].bestb_nt))
            {
                std::cout << "No Trade\n";
                return;
            }
            else
            {
                st[index].bestb_nt = str_price;
            }
            if (st[index].bestb_nt == st[index].bests_nt)
            {
                std::cout << "No Trade\n";
                st[index].bestb_nt = "N";
                st[index].bests_nt = "N";
                return;
            }
            if (price > st[index].price_l)
            {
                std::cout << switch_it(token) << "\n";
                st[index].price_l = price;
                st[index].bestb_nt = "N";
            }
            else
            {
                std::cout << "No Trade\n";
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

line pre_process(std::string temp)
{
    // std::cerr<<"I reached here safely"<<std::endl;
    int u = temp.length() - 1;
    // std::cerr<<u<<std::endl;
    int p1, p2;
    std::vector<std::pair<std::string, std::string>> r1; // This will be shares
    std::string r2;                                      // This will be price_b
    bool swi_tch = true;                                 // modification of count (as in your code)
    u = u - 2;
    p1 = u;
    while (temp[u] != ' ')
    {
        u--;
    }
    p2 = u;
    u--;
    // std::cerr<<"I reached here safely"<<std::endl;
    // std::cerr<<"p1 and p2 are "<<p1<<" "<<p2<<std::endl;
    r2 = temp.substr(p2 + 1, p1 - p2);
    // std::cerr<<"price is "<<r2<<std::endl;
    std::string t_string;
    std::string t_string1;
    std::pair<std::string, std::string> temp_pair;
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
            // std::cerr<<"p1 , p2 ,u are "<<p1<<" "<<p2<<" "<<u<<std::endl;
            t_string = temp.substr(p2 + 1, p1 - p2);
            // std::cerr<<t_string<<std::endl;
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
            // std::cerr<<"p1 , p2 ,u are "<<p1<<" "<<p2<<" "<<u<<std::endl;
            t_string1 = temp.substr(p2 + 1, p1 - p2);
            temp_pair = std::make_pair(t_string1, t_string);
            // std::cerr<<t_string1<<std::endl;
            r1.push_back(temp_pair);
            swi_tch = true;
        }
    }
    // NEW LINE FOR SORTING THE STOCK PAIRS
    sort(r1.begin(), r1.end(), CompareShare);
    //////////////////////////////////////
    line L(r1, r2);
    // std::cerr<<"I reached here safely"<<std::endl;
    return L;
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

void check_for_arbitrage(std::vector<line> &lines_b)
{
    
    long long int n = lines_b.size() - 1;
    if(n == 0){
        std::cout<<"No Trade"<<std::endl;
        return;
    }
    // std::cerr<<"I reached check for 2nd time safely"<<std::endl;
    // Total number of subsets is 2^n
    long long int totalSubsets = (1 << n);

    int max_profit_index;
    int max_profit = 0;
    std::vector<std::pair<std::string, std::string>> empty_shares;
    std::string empty_price_b = "0";
    line now(empty_shares, empty_price_b);

    // std::cerr<<"I reached check for 2nd time safely"<<std::endl;
    for (int i = 0; i < totalSubsets; ++i)
    {
        // std::cerr<<"I reached check for "<<i<<" time safely"<<std::endl;
        for (int j = 0; j < n; ++j)
        {
            if (i & (1 << j))
            {
                add_line_to_line(now,lines_b[j]);
            }
        }
        add_line_to_line(now,lines_b[n]);
        // std::cerr<<"I reached check for 2nd time safely"<< std::stoi(now.price_b)<<std::endl;
        if (std::stoi(now.price_b) > 0)
        {
            bool flag = true;
            // std::cerr<<"shares size is "<< (now.shares).size()<<std::endl;
            for (int p = 0; p < (now.shares).size(); p++)
            {
                if (std::stoi(now.shares[p].second) != 0)
                    flag = false;
            }
            // std::cerr<<"p is "<< p<<std::endl;

            if (flag && std::stoi(now.price_b) > max_profit)
            {
                max_profit = std::stoi(now.price_b);
                max_profit_index = i;
            }
        }
        (now.shares).clear();
        now.price_b = "0";
    }

    if(max_profit > 0)
    {
        std::cout<<switch_it(all_lines[n])<<std::endl;
        all_lines.erase(all_lines.begin()+n);
        lines_b.erase(lines_b.begin()+n);
        std::cerr<<all_lines.size()<<" "<<n<<std::endl;
        std::cerr<<max_profit<<std::endl;
        std::cerr<<max_profit_index<<std::endl;
        for (int j = n-1; j >=0; j--)
        {
            if (max_profit_index & (1 << j))
            {
                std::cout<<switch_it(all_lines[j])<<std::endl;
                all_lines.erase(all_lines.begin()+j);
                lines_b.erase(lines_b.begin()+j);
            }
        }
        std::cout<<max_profit<<std::endl;
    }
    else
    {
        std::cout<<"No Trade"<<std::endl;
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
        std::vector<line> lines_b; // All lines are going to be stored in the form of buys

        int iter = 0;
        std::string temp = "";
        while (iter < message.length())
        {
            while (message[iter] != '#')
            {
                // std::cerr<<iter<<std::endl;
                temp += message[iter];
                iter++;
            }
            // std::cerr<<temp<<std::endl;
            rectify(message, iter);
            // std::cerr<<iter<<std::endl;
            all_lines.push_back(temp); // Pushed the current line "as it is" in all_lines (for outputting purpose)
            line thisline = pre_process(change_sell_to_buy(temp));
            // std::cerr<<temp<<std::endl;
            temp = "";
            lines_b.push_back(thisline);
            check_for_arbitrage(lines_b);
        }
    }
    else if (argc[1][0] == '3')
    {
        std::cout << "NO";
    }
}
