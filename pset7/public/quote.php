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
            apologize("You must provide a symbol!");
            exit; 
        }
        
        // use lookup in functions.php
        $s = lookup($_POST["symbol"]);  
        
        // validate submission
        if ($s === false)
        {
            // apologize if invalid field
            apologize("That symbol is invalid!");
            exit; 
        } 
        
        //require("../templates/quote.php"); 
        render("quote.php", ["title" => "Quote", "price" => $s["price"], 
        "name" => $s["name"], "symbol" => $s["symbol"]]);   
    }  
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
