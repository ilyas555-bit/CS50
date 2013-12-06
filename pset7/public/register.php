<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // checks for valid submission
        if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            // apologizes for empty submission
            apologize("Please enter a password or a confirmation"); 
            exit; 
        }
        
        // checks if confirmation matches password
        if (htmlspecialchars($_POST["password"]) != htmlspecialchars($_POST["confirmation"]))
        {
            // apologizes for incorrect match
            apologize("Passwords do not match!"); 
            exit; 
        }
        
        // checks if empty username
        if (empty($_POST["username"]))
        {
            // apologizes for empty submissionn
            apologize("Please enter a username!"); 
            exit; 
        }     
        
        // insert user into table   
        $result = query("INSERT INTO users (username, hash, cash) 
        VALUES (?, ?, 10000.0000)",
        htmlspecialchars($_POST["username"]), 
        crypt(htmlspecialchars($_POST["password"]))); 
        
        // checks for valid username       
        if ($result === false)
        {
            // apologize if username is already taken
            apologize("That username is already taken!"); 
            exit; 
        }
        
        // query server
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        
        // converts array to one element
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id; 
        
        // redirects user to index.php
        header("Location: /index.php");
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
