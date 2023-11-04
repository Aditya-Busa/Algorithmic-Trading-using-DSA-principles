# Algorithmic-Trading-using-DSA-principles

Details of Implementation for Phase 1 : Part 1

Few small notes before starting :
  1. Any order which is TRADED doesn't go into Best_buy or Best_sell
  2. All stocks are treated independently


- First order of a new stock is executed
- Every trade which arrived undergoes a three stage check before finalising

 
    i. If it is a " .... s" then compare it with the Best_sell, IF IT IS NOT A BETTER SELL, I.E. WE ARE BUYING SO, **"... s" PRICE >= Best_sell** then you will give out a "No trade" EVEN IF IT IS GOOD TRADE ACCORDING TO VALUE, if it is a better one then you cancel or remove the existing/previous best_sell order.
  
    ii. Now if it survived the above test then you compare with Best_buy and ONLY in the case it is equal, we cancel both(i.e. we give a No Trade in current and you empty the Best_buy)

    iii. Now at last you compare with Value and if Good then you output, if not then you place it in Best_buy or Best_sell wherever it belongs to(Note that we arrived here after checking whether it is a better buy or sell, and we came to this step only after verifying that it is a better buy/sell)

__An Example to take care between ii and iii__ : If B 60 b & B 30 s are surviving orders, then if B 30 b comes, then it gets cancelled by B 60 b, not by B 30 s
