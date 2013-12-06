<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            // apologize if empty field
            apologize("You must specify a stock to buy.");
            exit; 
        }
        
        // validate submission
        if (empty($_POST["shares"]))
        {
            // apologize if empty field
            apologize("You must specify a number of shares.");
            exit; 
        }
        
        // makes sure that user cannot spend more cash than he has
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            // apologizes if stock costs too much
            apologize("Please enter a positive integer");
            exit;
        }
        
        // check if user can buy
        $s = lookup(htmlspecialchars($_POST["symbol"]));
        
        // query the server for cash
        $currentcash = query("SELECT cash FROM users WHERE id = ?", 
        $_SESSION["id"]);
        
        // converts array to one element
        $currentcash2 = $currentcash[0]["cash"];
        
        // multiplies price and shares
        $buying = $s["price"] * htmlspecialchars($_POST["shares"]);
        
        // checks to see if enough money
        if ($buying > $currentcash2)
        {
            apologize("You do not have enough money!");
        }
        
        // converts symbol to uppercase
        $capitalsymb = strtoupper(htmlspecialchars($_POST["symbol"]));
        
        // add stock to anything
        $newstocks = query("INSERT INTO portfolio (id, symbol, shares) 
        VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + 
        VALUES(shares)", $_SESSION["id"], $capitalsymb, htmlspecialchars($_POST["shares"])); 
        
        // update cash
        $new = query("UPDATE users SET cash = cash - ? WHERE id = ?", 
        $buying, $_SESSION["id"]); 
        
        // insert into history
        $updater = query("INSERT INTO history (ID, Transaction, Symbol, 
        Shares, Price) VALUES(?,?,?,?,?)", $_SESSION["id"],'BUY',  
        $capitalsymb, htmlspecialchars($_POST["shares"]), $s["price"]); 
       
        // redirects to index.php
        header("Location: /");    
    }    
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
?>
