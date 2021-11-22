<?php
    require_once("../Functions.inc");
    $db_name = 'recipe_db';
    
    $sql = '';
    switch (true) {
        case @$_POST['searchWord'] != '':
            $sql = <<< SQL
                SELECT
                    RecipeTable.RecipeId,
                    RecipeTable.RecipeName
                FROM
                    RecipeTable
                    LEFT OUTER JOIN (
                        SELECT
                            RecipeId,
                            GROUP_CONCAT(MaterialName) AS MaterialName,
                            GROUP_CONCAT(MaterialNameHiragana) AS MaterialNameHiragana
                        FROM
                            MaterialTable
                        GROUP BY
                            RecipeId
                    ) AS MaterialTable
                        ON MaterialTable.RecipeId = RecipeTable.RecipeId
                WHERE
                    RecipeTable.RecipeName LIKE :recipeName
                    OR RecipeTable.RecipeNameHiragana LIKE :recipeNameHiragana
SQL;
            if (@$_POST['includeMaterial'] == '1') {
                $sql .= <<< SQL
                    OR MaterialTable.MaterialName LIKE :materialName
                    OR MaterialTable.MaterialNameHiragana LIKE :materialNameHiragana
SQL;
            }
            if (@$_POST['includeMaterial'] == '1') {
                $recipe = array(':recipeName' => '%' . $_POST['searchWord'] . '%', ':recipeNameHiragana' => '%' . $_POST['searchWord'] . '%', ':materialName' => '%' . $_POST['searchWord'] . '%', ':materialNameHiragana' => '%' . $_POST['searchWord'] . '%');
            } else {
                $recipe = array(':recipeName' => '%' . $_POST['searchWord'] . '%', ':recipeNameHiragana' => '%' . $_POST['searchWord'] . '%');
            }
            break;
        default:
            $sql = <<< SQL
                    SELECT
                        RecipeId,
                        RecipeName
                    FROM
                        RecipeTable
SQL;
            $recipe = NULL;
            break;
    }

    $recipeList = selectData($db_name, $sql, $recipe);
?>