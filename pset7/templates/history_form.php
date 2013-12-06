<div class = "navbartable"> 
<table class="table table-striped">  
    <thead>  
        <tr>  
            <th>Transaction</th>  
            <th>Date/Time</th>  
            <th>Symbol</th>  
            <th>Shares</th>  
            <th>Price</th>
        </tr>  
    </thead>  
    <tbody>  
    <?php
    
        foreach ($rows as $row)
        {
            // makes two numbers after decimal
            $row["Price"] = number_format($row["Price"], 2);  
            
            // prints table with values
            print("<tr>");
            print("<td>{$row["Transaction"]}</td>");            
            print("<td>{$row["time"]}</td>");
            print("<td>{$row["Symbol"]}</td>");
            print("<td>{$row["Shares"]}</td>");
            print("<td>$ {$row["Price"]}</td>");
            print("</tr>");
        }
        
   ?>
   </tbody>  
</table>  
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>


