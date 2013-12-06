<?php

    // configuration
    require("../includes/config.php"); 
    
    // query the server
    $rows = query("SELECT Transaction, time, Symbol, Shares, 
    Price FROM history WHERE id = ?", $_SESSION["id"]);
   
    // render portfolio
    render("history_form.php", ["title" => "Portfolio", "rows" => $rows]);

?>
