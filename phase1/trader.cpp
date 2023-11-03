#include "receiver.h"
#include<vector>

struct  stocks{
    std:: string s;
    std:: string bests_nt;//Non traded best price for sell
    std:: string bestb_nt;//Non traded best price for buy
    std:: string price_l;//last traded price
    //std:: string price;//present price
    // char v;
    //  TreeNode(int key, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : key(key), left(leftChild), right(rightChild), parent(parent) {
    stocks(std::string s, std:: string bests_nt, std:: string bestb_nt, std:: string price_l) : s(s), bests_nt(bests_nt), bestb_nt(bestb_nt), price_l(price_l){}
};

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
    std::string price;
    int iter = 0;
    while(token[iter] != ' '){
        stock += token[iter];
        iter++;
    }
    iter++;
    while(token[iter]!= ' '){
        price += token[iter];
        iter++;
    }

    bool found = false;
    int index;
    int x=0;
    int y=0;
    for(int i =0; i < st.size(); i++){
        if(st[i].s == stock){
            found = true;
            index =i;
            break;
        }
    }

    if(found){
        // std::cout<<"print for me"<<st[0].bests_nt<<" "<<st[0].bestb_nt<<std::endl;
        if(token[token.size() - 1] == 's'){
            if(st[index].bests_nt=="N"){
                x=1;
            }
            else{
                if(price >= st[index].bests_nt){
                    std::cout<<"No Trade\n";
                    return;
                }
                else{
                    x=1;
                }
            }
            if(st[index].bestb_nt != "N"){
                if(price == st[index].bestb_nt){
                    std::cout<<"No Trade\n"; 
                    st[index].bestb_nt="N";
                    return ; 
                }
                else{

                }
            }

            if(price < st[index].price_l){
                std::cout<<switch_it(token)<<"\n";
                st[index].price_l= price;
            }
            else{
                std::cout<<"No Trade\n";
                if(x){
                st[index].bests_nt=price;}
                return;
            }

        }
        else{
            if(st[index].bestb_nt== "N"){
                y=1;
            }
            else{
                if(price <= st[index].bestb_nt){
                    std::cout<<"No Trade\n";
                    return;
                }
                else{
                    y=1;
                }
            }
            if(st[index].bests_nt == "N"){

            }
            else{
                if(price == st[index].bests_nt){
                    std::cout<<"No Trade\n";
                    st[index].bests_nt = "N";
                    return;
                }
                else{

                }
            }
            if(price > st[index].price_l){
                std::cout<<switch_it(token)<<std::endl;
                st[index].price_l = price;
                return;
            }
            else{
                std::cout<<"No Trade\n";
                if(y){
                st[index].bestb_nt = price;}
                return;
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
    // std::cout<<message<<std::endl<<std::endl;

    if(argc[1][0]=='1'){
        std::vector<stocks> st_vec;
        int iter = 0;
        std::string temp = "";
        while(iter<message.length()){
            while(message[iter]!='#'){
                temp += message[iter];
                iter++;
            }
            iter = iter + 2;
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


