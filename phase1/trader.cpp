#include "receiver.h"
#include <vector>
#include "part2_functions.cpp"

std::vector< std::pair<std::string,int> > all_lines; // The actual lines(for outputting purposes)

// ALL_LINES[I] NEED NOT BE I OR I+1 TH LINE
// CHECK ALL_LINES.SECOND

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

void check_for_arbitrage(std::vector<line> &Structures_b)
{
    int for_max_profit_index = -1;
    int the_max_profit = 0;
    int j;
    for (int i = 0; i < Structures_b.size(); i++)
    {
        bool to_continue = true;
        for (j = 0; j < Structures_b[i].shares.size(); j++)
        {
            if ((Structures_b[i].shares[j]).second != "0")
            {
                to_continue = false;
                break;
            }
        }
        if (to_continue && std::stoi(Structures_b[i].price_b_s.first) > the_max_profit)
        {
            the_max_profit = std::stoi(Structures_b[i].price_b_s.first);
            for_max_profit_index = j;
        }
    }
    
    if (for_max_profit_index != -1) // It means arbitrage is detected with >0 profit
    {
        // for (int i = (Structures_b[j].indices_of_lines_in_input).size()-1 ; i >= 0 ; i--)
        // {
        //     ////////////////////////////////////
        //    std::cout<< switch_it(all_lines[i].first) << std::endl ;  
        //    //////////////////////////////////////
        // } SINGLE LOOP PLSS

        std::cout << the_max_profit << std::endl ;
        for(int i = 0 ; i < Structures_b[j].indices_of_lines_in_input.size() ; i++)
        {

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
        std::vector<line> Structures_b;     // All lines are going to be stored in the form of buys

        int iter = 0;
        int index_of_line = 0;
        std::string temp = "";
        while (iter < message.length())
        {
            while (message[iter] != '#')
            {
                temp += message[iter];
                iter++;
            }
            rectify(message, iter);
            temp = "";
            all_lines.push_back(std::make_pair(temp,index_of_line)); //Pushed the current line as it is in all_lines (for outputting purpose)
            line thisline = pre_process(change_sell_to_buy(temp), index_of_line);
            index_of_line++;
        }
    }
    else if (argc[1][0] == '3')
    {
        std::cout << "NO";
    }
}

