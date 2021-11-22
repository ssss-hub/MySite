<?php
    require_once("../Functions.inc");
    $db_name = 'recipe_db';
    $recipeId = $_GET['recipe_id'];
    switch (true) {
        case @$_POST['modify'] !='':
            $recipeId = $_POST['recipe_id'];
            try {
                $dbh = setDB($db_name);
                // トランザクション開始
                $dbh->beginTransaction();
            
                updateData($db_name, $recipeId);
            
                // コミット
                $dbh->commit();
            
            } catch(PDOException $e) {
                // ロールバック
                $dbh->rollBack();
                // エラーメッセージ出力
                echo $e->getMessage();
                die();
            }
            // 接続を閉じる
            $dbh = null;
            header('Location: ./search.php');
            break;
        case @$_POST['delete'] !='':
            $recipeId = $_POST['recipe_id'];
            try {
                $dbh = setDB($db_name);
                // トランザクション開始
                $dbh->beginTransaction();
            
                deleteRecipe($db_name, $recipeId);
            
                // コミット
                $dbh->commit();
            
            } catch(PDOException $e) {
                // ロールバック
                $dbh->rollBack();
                // エラーメッセージ出力
                echo $e->getMessage();
                die();
            }
            // 接続を閉じる
            $dbh = null;
            header('Location: ./search.php');
            break;
    }
    $recipe = setData($db_name, $recipeId);

    function setData($db_name, $recipeId) {
        // レシピテーブルから取得
        $sql = <<< SQL
                SELECT
                    RecipeName,
                    RecipeNameHiragana,
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
                    MaterialId,
                    MaterialName,
                    MaterialNameHiragana,
                    Quantity,
                    Unit
                FROM
                    MaterialTable
                WHERE
                    RecipeId = :recipeId
                ORDER BY
                    MaterialId
SQL;

        $array = array(':recipeId' => $recipeId);

        $recipe['material'] = selectData($db_name, $sql, $array);
        
        // 調理工程テーブルから取得
        $sql = <<< SQL
                SELECT
                    ProcessId,
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
                    PointId,
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

        return $recipe;
    }
    
    function updateData($db_name, $recipeId) {
        // レシピテーブル編集
        $sql = <<< SQL
            UPDATE
                RecipeTable
            SET
                RecipeName = :recipeName,
                RecipeNameHiragana = :recipeNameHiragana,
                CompletedPhotoUrl = :completedPhotoUrl,
                ReferenceUrl = :referenceUrl
            WHERE
                RecipeId = :recipeId
SQL;
        
        $array = array(':recipeName' => $_POST['recipeName'], ':recipeNameHiragana' => $_POST['recipeNameHiragana'], ':completedPhotoUrl' => $_POST['completedPhotoUrl'], ':referenceUrl' => $_POST['referenceUrl'], ':recipeId' => $recipeId);
        operateData($db_name, $sql, $array);
        
        // 材料テーブル編集
        $sqlUpdate = <<< SQL
        UPDATE
            MaterialTable
        SET
            MaterialName = :materialName,
            MaterialNameHiragana = :materialNameHiragana,
            Quantity = :quantity,
            Unit = :unit
        WHERE
            RecipeId = :recipeId
            AND MaterialId = :materialId
SQL;

        $sqlDelete = <<< SQL
            DELETE
            FROM
                MaterialTable
            WHERE
                RecipeId = :recipeId
                AND MaterialId = :materialId
SQL;

        $sqlInsert = <<< SQL
            INSERT INTO MaterialTable (
                RecipeId,
                MaterialId,
                MaterialName,
                MaterialNameHiragana,
                Quantity,
                Unit
            )
            VALUES (
                :recipeId,
                :materialId,
                :materialName,
                :materialNameHiragana,
                :quantity,
                :unit
            )
SQL;
        
        foreach ($_POST['material'] as $material) {
            if ($material['materialName'] == '') {
                $array = array(':recipeId' => $recipeId, ':materialId' => $material['materialId']);
                operateData($db_name, $sqlDelete, $array);
            } else {
                $array = array(':materialName' => $material['materialName'], ':materialNameHiragana' => $material['materialNameHiragana'], ':quantity' => (($material['quantity'] == '') ? NULL : $material['quantity']), ':unit' => $material['unit'], ':recipeId' => $recipeId, ':materialId' => $material['materialId']);
                operateData($db_name, $sqlUpdate, $array);
            }
        }
        
        foreach ($_POST['materialAdd'] as $material) {
            if ($material['materialName'] != '') {
                $array = array(':recipeId' => $recipeId, ':materialId' => $material['materialId'], ':materialName' => $material['materialName'], ':materialNameHiragana' => $material['materialNameHiragana'], ':quantity' => (($material['quantity'] == '') ? NULL : $material['quantity']), ':unit' => $material['unit']);
                operateData($db_name, $sqlInsert, $array);
            }
        }
        
        // 行程テーブル編集
        $sqlUpdate = <<< SQL
        UPDATE
            ProcessTable
        SET
            ProcessContent = :processContent,
            ProcessPhotoUrl = :processPhotoUrl
        WHERE
            RecipeId = :recipeId
            AND ProcessId = :processId
SQL;

        $sqlDelete = <<< SQL
            DELETE
            FROM
                ProcessTable
            WHERE
                RecipeId = :recipeId
                AND ProcessId = :processId
SQL;

        $sqlInsert = <<< SQL
            INSERT INTO ProcessTable (
                RecipeId,
                ProcessId,
                ProcessContent,
                ProcessPhotoUrl
            )
            VALUES (
                :recipeId,
                :processId,
                :processContent,
                :processPhotoUrl
            )
SQL;
        
        foreach ($_POST['process'] as $process) {
            if ($process['processContent'] == '') {
                $array = array(':recipeId' => $recipeId, ':processId' => $process['processId']);
                operateData($db_name, $sqlDelete, $array);
            } else {
                $array = array(':processContent' => $process['processContent'], ':processPhotoUrl' => $process['processPhotoUrl'], ':recipeId' => $recipeId, ':processId' => $process['processId']);
                operateData($db_name, $sqlUpdate, $array);
            }
        }
        
        foreach ($_POST['processAdd'] as $process) {
            if ($process['processContent'] != '') {
                echo $process['processId'];
                $array = array(':recipeId' => $recipeId, ':processId' => $process['processId'], ':processContent' => $process['processContent'], ':processPhotoUrl' => $process['processPhotoUrl']);
                operateData($db_name, $sqlInsert, $array);
            }
        }
        
        // ポイントテーブル編集
        $sqlUpdate = <<< SQL
        UPDATE
            PointTable
        SET
            PointContent = :pointContent
        WHERE
            RecipeId = :recipeId
            AND PointId = :pointId
SQL;

        $sqlDelete = <<< SQL
            DELETE
            FROM
                PointTable
            WHERE
                RecipeId = :recipeId
                AND PointId = :pointId
SQL;

        $sqlInsert = <<< SQL
            INSERT INTO PointTable (
                RecipeId,
                PointId,
                PointContent
            )
            VALUES (
                :recipeId,
                :pointId,
                :pointContent
            )
SQL;
        
        foreach ($_POST['point'] as $point) {
            if ($point['pointContent'] == '') {
                $array = array(':recipeId' => $recipeId, ':pointId' => $point['pointId']);
                operateData($db_name, $sqlDelete, $array);
            } else {
                $array = array(':pointContent' => $point['pointContent'], ':recipeId' => $recipeId, ':pointId' => $point['pointId']);
                operateData($db_name, $sqlUpdate, $array);
            }
        }
        
        foreach ($_POST['pointAdd'] as $point) {
            if ($point['pointContent'] != '') {
                $array = array(':recipeId' => $recipeId, ':pointId' => $point['pointId'], ':pointContent' => $point['pointContent']);
                operateData($db_name, $sqlInsert, $array);
            }
        }
    }

    function deleteRecipe($db_name, $recipeId) {
        $array = array(':recipeId' => $recipeId);
        $sql = <<< SQL
            DELETE
            FROM
                RecipeTable
            WHERE
                RecipeId = :recipeId
SQL;
        operateData($db_name, $sql, $array);
        $sql = <<< SQL
            DELETE
            FROM
                MaterialTable
            WHERE
                RecipeId = :recipeId
SQL;
        operateData($db_name, $sql, $array);
        $sql = <<< SQL
            DELETE
            FROM
                ProcessTable
            WHERE
                RecipeId = :recipeId
SQL;
        operateData($db_name, $sql, $array);
        $sql = <<< SQL
            DELETE
            FROM
                PointTable
            WHERE
                RecipeId = :recipeId
SQL;
        operateData($db_name, $sql, $array);
    }
?>