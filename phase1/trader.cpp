#include "receiver.h"
#include<vector>

struct  stocks{
    std:: string s;
    std:: string bests_nt;//Non traded best price for sell
    std:: string bestb_nt;//Non traded best price for buy
    int price_l;//last traded price
    stocks(std::string s, std:: string bests_nt, std:: string bestb_nt, int price_l) : s(s), bests_nt(bests_nt), bestb_nt(bestb_nt), price_l(price_l){}
};

void rectify(std:: string message,int &iter){
    while(!isalpha(message[iter])){
        iter++;
    }
}

std::string switch_it(std:: string it){
    if(it[it.size() - 1]=='b'){
        it[it.size()-1] = 's';
    }
    else{
        it[it.size()-1]='b';
    }
    return it;
}

void add_to_it(std::vector<stocks> &st, std::string token){
    std::string stock;
    std::string str_price;
    int price;
    int iter = 0;
    while(token[iter] != ' '){
        stock += token[iter];
        iter++;
    }
    iter++;
    while(token[iter]!= ' '){
        str_price += token[iter];
        iter++;
    }
    price=stoi(str_price);
    bool found = false;
    int index;
    for(int i =0; i < st.size(); i++){
        if(st[i].s == stock){
            found = true;
            index =i;
            break;
        }
    }
    if(found){
        if(token[token.size() - 1] == 's'){
            if(st[index].bests_nt!="N" && price >= stoi(st[index].bests_nt)){
                    std::cout<<"No Trade\n";
                    return;
            }
            else{
                st[index].bests_nt=str_price;
                // std::cout<<"yo boizz";
            }
            if(st[index].bests_nt == st[index].bestb_nt){
                std::cout<<"No Trade\n";
                st[index].bestb_nt="N";
                st[index].bests_nt="N";
                return;
            }
            if(price < st[index].price_l){
                std::cout<<switch_it(token)<<"\n";
                st[index].price_l= price;
                st[index].bests_nt="N";
            }
            else{
                std::cout<<"No Trade\n";
            }
        }
        else{
            if(st[index].bestb_nt!="N" && price <= stoi(st[index].bestb_nt)){
                    std::cout<<"No Trade\n";
                    return;
            }
            else{
                st[index].bestb_nt=str_price;
            }
            if(st[index].bestb_nt == st[index].bests_nt){
                std::cout<<"No Trade\n";
                st[index].bestb_nt="N";
                st[index].bests_nt="N";
                return;
            }
            if(price > st[index].price_l){
                std::cout<<switch_it(token)<<"\n";
                st[index].price_l= price;
                st[index].bestb_nt="N";
            }
            else{
                std::cout<<"No Trade\n";
            }
        }
    }
    else{
        stocks S(stock, "N", "N", price);
        st.push_back(S);
        std::cout<<switch_it(token)<<std::endl;
    }
}


int main(int argv, char** argc){
    Receiver rcv;
    //sleep(5);
    bool found_dollar = false;
    std::string message = rcv.readIML();
    while(!found_dollar){
        std::string message1 = rcv.readIML();
        message.append(message1);
        if(message.find('$') != std::string::npos){
            //std::message1 = rcv.readIML();
            found_dollar= true;
        }
    }
    rcv.terminate();
    
    if(argc[1][0]=='1'){
        std::vector<stocks> st_vec;
        int iter = 0;
        std::string temp = "";
        while(iter<message.length()){
            while(message[iter]!='#'){
                temp += message[iter];
                iter++;
            }
            rectify(message,iter);
            add_to_it(st_vec,temp);
            temp = "";
        }
    }
    else if(argc[1][0]=='2'){
        // std::cout<<"NO";
        
    }
    else if(argc[1][0]=='3'){
        std::cout<<"NO";
    }
}


