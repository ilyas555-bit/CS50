    
    <div class=navbartable>
    <table class="table table-striped">  
        
        <thead>  
            <tr>  
                <th>Symbol</th>  
                <th>Name</th>  
                <th>Shares</th>  
                <th>Price</th>  
                <th>Total</th>
            </tr>  
        </thead> 
    <tbody>      
      
    <?php
        
        // query for cash
        $cashs = query("SELECT cash FROM users WHERE id = ?", 
        $_SESSION["id"]);
        
        // converts array to one element
        $cash = $cashs[0]["cash"];
        
        // adds two numbers after decimal
        $cash = number_format($cash, 2);  
        
        foreach ($positions as $position)   
        {
            // multiplies to find current value
            $currentvalue = $position["price"] * $position["shares"];
         
            // adds two numbers after decimal
            $position["price"] = number_format($position["price"], 2); 
            $currentvalue = number_format($currentvalue, 2); 
            
            // prints values in table
            print("<tr>");
            print("<td>{$position["symbol"]}</td>");            
            print("<td>{$position["name"]}</td>");
            print("<td>{$position["shares"]}</td>");
            print("<td>$ {$position["price"]}</td>");
            print("<td>$ {$currentvalue}</td>");                        
            print("</tr>");       
        } 
        print("<tr>"); 
        
    ?>
    
    <td colspan="4">CASH</td> 
            
    <?php
        
        // prints total  cash in separate line
        print("<td>$ {$cash}</td>"); 
        print("</tr>");  
         
    ?>
      
    </tbody>  
    
    </table> 
     
    </div>
    
<a href="logout.php">Log Out</a>


