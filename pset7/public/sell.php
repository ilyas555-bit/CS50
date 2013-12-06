<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["stock"]))
        {
            // apologize if empty field
            apologize("You must select a stock to sell!");
            exit; 
        }   

        // look up current price of stock
        $s = lookup(htmlspecialchars($_POST["stock"]));
        
        // query server for shares
        $shares = query("SELECT shares FROM portfolio WHERE id = ? 
        AND symbol = ?", $_SESSION["id"], htmlspecialchars($_POST["stock"]));
        
        // converts array to one element
        $share = $shares[0]["shares"];
        
        // multiplies price with shares
        $sold = $s["price"] * $share; 
        
        // updates cash
        $new = query("UPDATE users SET cash = cash + ? WHERE id = ?", 
        $sold, $_SESSION["id"]); 
        
        // deletes the stock
        $delete = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", 
        $_SESSION["id"], htmlspecialchars($_POST["stock"])); 
        
        // updates history
        $updater = query("INSERT INTO history (ID, Transaction, Symbol, 
        Shares, Price) VALUES(?,?,?,?,?)", $_SESSION["id"],'SELL', 
        htmlspecialchars($_POST["stock"]), $share, $s["price"]); 
       
        // redirects user back to index.php
        header("Location: /");
    }
    else
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

?>
