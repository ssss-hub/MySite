<?php
    require_once("../Functions.inc");
    $db_name = 'recipe_db';
    if (@$_POST['fraction'] == '') {
        $recipeId = $_GET['recipe_id'];
        $fraction1 = 1;
        $fraction2 = 1;
    } else {
        $recipeId  = $_POST['recipe_id'];
        $fraction1 = $_POST['fraction1'];
        $fraction2 = $_POST['fraction2'];
    }
    
    // レシピテーブルから取得
    $sql = <<< SQL
            SELECT
                RecipeName,
                CompletedPhotoUrl,
                ReferenceUrl
            FROM
                RecipeTable
            WHERE
                RecipeId = :recipeId
SQL;

    $array = array(':recipeId' => $recipeId);

    $recipe = selectData($db_name, $sql, $array)[0];
    
    // 材料テーブルから取得
    $sql = <<< SQL
            SELECT
                MaterialName,
                Quantity * :fraction1 / :fraction2 AS Quantity,
                Unit
            FROM
                MaterialTable
            WHERE
                RecipeId = :recipeId
            ORDER BY
                MaterialId
SQL;

    $array = array(':fraction1' => $fraction1, ':fraction2' => $fraction2, ':recipeId' => $recipeId);

    $recipe['material'] = selectData($db_name, $sql, $array);
    
    // 調理工程テーブルから取得
    $sql = <<< SQL
            SELECT
                ProcessContent,
                ProcessPhotoUrl
            FROM
                ProcessTable
            WHERE
                RecipeId = :recipeId
            ORDER BY
                ProcessId
SQL;

    $array = array(':recipeId' => $recipeId);

    $recipe['process'] = selectData($db_name, $sql, $array);


    
    // ポイントテーブルから取得
    $sql = <<< SQL
            SELECT
                PointContent
            FROM
                PointTable
            WHERE
                RecipeId = :recipeId
            ORDER BY
                PointId
SQL;

    $array = array(':recipeId' => $recipeId);

    $recipe['point'] = selectData($db_name, $sql, $array);
?>