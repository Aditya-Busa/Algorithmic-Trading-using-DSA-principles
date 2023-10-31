#include "receiver.h"
#include<vector>


std::string switch_it(std::string it){
    if(it[it.size()-1]=='b'){
        it[it.size()-1]='s';
    }
    else{
        it[it.size()-1]='b';
    }
    return it;
}

void add_to_it(std::vector< std::string > &stocks, std::vector< std::string > &prices, std::string token){
    std::string stock;
    std::string price;
    int iter=0;
    while(token[iter]!=' '){
        stock+=token[iter];
        iter++;
    }
    iter++;
    while(token[iter]!=' '){
        price+=token[iter];
        iter++;
    }
    bool found = false;
    int index = 0;
        for (int i = 0; i < stocks.size() ; i++) {
            if (stocks[i] == stock) {
                found = true;
                index = i;
                break;
            }
        }
    

    if(found){
        if(token[token.size()-1]=='s'){
            if(prices[index]>price){
                std::cout<<switch_it(token)<<std::endl;
                prices[index]=price;
            }
            else{
                std::cout<<"No Trade\n";
            }
        }
        else{
            if(prices[index]<price){
                std::cout<<switch_it(token)<<std::endl;
                prices[index]=price;
            }
            else{
                std::cout<<"No Trade\n";
            }
        }
    }
    else{
        stocks.push_back(stock);
        prices.push_back(price);
        std::cout<<switch_it(token)<<std::endl;
    }

}

int main(int argv,char** argc) {

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
        std::vector<std::string> stocks;
        std::vector<std::string> prices;
    //     // char* charArray = new char[message.size() + 1];  // +1 for null terminator
    //     // std::copy(message.begin(), message.end(), charArray);
    //     // charArray[message.size()] = '\0';  // Null-terminate the array
    //     // std::string tok = strtok(charArray, "#");
        
        int iter=0;
        std::string temp="";
        while (message[iter]!='$')
        {
            while(message[iter]!='#'){
                temp+=message[iter];
                iter++;
                // std::cout<<iter<<"\n";
            }
            iter=iter+2;
             //if(temp[0]=='\n'){
               //  temp.erase(0,1);
             //}
            add_to_it(stocks,prices,temp);
            temp="";
        }
        // std::cout<<message; 
        // rcv.terminate();       
    }
    else if(argc[1][0]=='2'){
        std::cout<<"no";
    }
    return 0;
}

