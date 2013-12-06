<?php

    // configuration
    require("../includes/config.php"); 
    
    // quiery the server for symbol
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", 
    $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        // looks up stock
        $stock = lookup($row["symbol"]);
        
        // combines names and prices from lookup with shares and symbols
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
         }
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => 
    $positions]);

?>


