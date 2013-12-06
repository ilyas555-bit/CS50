<?php

    // queries the server for symbol
    $stocks = query("SELECT symbol FROM portfolio WHERE id = ?", 
    $_SESSION["id"]); 
    
?>

<form action="sell.php" method="post">
    <fieldset>
        <div class = "form-group">
            <select name = "stock">
            <option value = ""></option>
            
            <?php foreach($stocks as $stock): ?>
                <option value = "<?= $stock["symbol"] ?>"><?=
                $stock["symbol"] ?></option>
            <? endforeach ?>
            
            </select>
       </div>
       <div class = "form-group">
            <button type = "submit" class = "btn btn-default">Sell!</button>
       </div>
   </fieldset>
</form>


