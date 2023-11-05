# Algorithmic-Trading-using-DSA-principles

**Details of Implementation for Phase 1 : Part 1**

Few small notes before starting :
  1. Any order which is TRADED doesn't go into Best_buy or Best_sell
  2. All stocks are treated independently


- First order of a new stock is executed
- Every trade which arrived undergoes a three stage check before finalising

 
    i. If it is a " .... s" then compare it with the Best_sell, IF IT IS NOT A BETTER SELL, I.E. WE ARE BUYING SO, **"... s" PRICE >= Best_sell** then you will give out a "No trade" EVEN IF IT IS GOOD TRADE ACCORDING TO VALUE, if it is a better one then you cancel or remove the existing/previous best_sell order.
  
    ii. Now if it survived the above test then you compare with Best_buy and ONLY in the case it is equal, we cancel both(i.e. we give a No Trade in current and you empty the Best_buy)

    iii. Now at last you compare with Value and if Good then you output, if not then you place it in Best_buy or Best_sell wherever it belongs to(Note that we arrived here after checking whether it is a better buy or sell, and we came to this step only after verifying that it is a better buy/sell)

__An Example to take care between ii and iii__ : If B 60 b & B 30 s are surviving orders, then if B 30 b comes, then it gets cancelled by B 60 b, not by B 30 s


**Details of Implementation for Phase 1 : Part 2**

Structs to create : 
  1. **Stock** (This should contain "name_stock" and "quantity_stock") 
  2. **Line** (In this we process a line and store them as "Stock"s), so this should contain a vector of "**Stock**"s and a **pair** which contains "b" or "s" as pair.second and the price for this pair.first,IT SHOULD ALSO CONTAIN A VECTOR WHICH INDICATES WHAT ARE THER LINES USED IN MAKING THIS LINE,THIS WAS NOT TAKEN CARE OF, IN OUR DISCUSSION PREVIOUSLY)
  3. 


Functions to create :
  1. add_line_to_line()(this should contain a _"for loop of add_stock_to_line"_,these are two separate functions just for modularity,DONT FORGET TO ADD QUANTITY ALSO)
  2. add_stock_to_line()
  
**Algorithm**
  1. The first line arrived , we process it and make it into a **Line**, then we push_back it into Structures
  2. Now process the second line, we clone the Structures (i.e. create a **vector<Line>temp_structures=Structures**), Now iterate through **temp_structures**, for every **Line** in **temp_structures**,use **add_line_to_line** to add the current line to existing lines in temp_structures, 













  
