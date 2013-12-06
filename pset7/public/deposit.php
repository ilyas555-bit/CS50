<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["deposit"]))
        {
            // apologize if empty submission
            apologize("You must provide a deposit amount.");
        }
        else if (htmlspecialchars($_POST["deposit"]) <= 0)
        {
            // apologize if negative deposit
            apologize("You must deposit a positive amount.");
        }

        // query database for user
        $new = query("UPDATE users SET cash = cash + ? WHERE id = ?",
        htmlspecialchars($_POST["deposit"]), $_SESSION["id"]);
        
        // redirects back to index.php
        header("Location: /");
    }
    else
    {
        // else render form
        render("deposit_form.php", ["title" => "Log In"]);
    }
    
?>
