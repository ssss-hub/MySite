<?php
    require_once("../Functions.inc");
    $db_name = 'recipe_db';
    if ($_POST['register'] != NULL) {
        try {
            $dbh = setDB($db_name);
            // トランザクション開始
            $dbh->beginTransaction();
        
            insertData($db_name);
        
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
        header('Location: ../index.php');
    }
    
    function insertData($db_name) {
        $sql ='';
        // レシピIDの最大値の次の数字取得
        $sql = <<< SQL
            SELECT
                MAX(RecipeId) AS maxId
            FROM
                RecipeTable
SQL;
        $newId = selectData($db_name, $sql)[0]['maxId'] + 1;

        // RecipeTableにデータ追加
        $sql = <<< SQL
            INSERT INTO RecipeTable (
                RecipeId,
                RecipeName,
                RecipeNameHiragana,
                CompletedPhotoUrl,
                ReferenceUrl
            )
            VALUES (
                :recipeId,
                :recipeName,
                :recipeNameHiragana,
                :completedPhotoUrl,
                :referenceUrl
            )
SQL;
        $array = array(':recipeId' => $newId, ':recipeName' => $_POST['recipeName'], ':recipeNameHiragana' => $_POST['recipeNameHiragana'], ':completedPhotoUrl' => $_POST['completedPhotoUrl'], ':referenceUrl' => $_POST['referenceUrl']);
        operateData($db_name, $sql, $array);

        // MaterialTableにデータ追加
        $sql = <<< SQL
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
        $cnt = 0;
        foreach ($_POST['material'] as $material) {
            if ($material['materialName'] != '') {
                $array = array(':recipeId' => $newId, ':materialId' => $cnt, ':materialName' => $material['materialName'], ':materialNameHiragana' => $material['materialNameHiragana'], ':quantity' => (($material['quantity'] == '') ? NULL : $material['quantity']), ':unit' => $material['unit']);
                operateData($db_name, $sql, $array);
                $cnt = $cnt + 1;
            }
        }

        // ProcessTableにデータ追加
        $sql = <<< SQL
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
        $cnt = 0;
        foreach ($_POST['process'] as $process) {
            if ($process['processContent'] != '') {
                $array = array(':recipeId' => $newId, ':processId' => $cnt, ':processContent' => $process['processContent'], ':processPhotoUrl' => $process['processPhotoUrl']);
                operateData($db_name, $sql, $array);
                $cnt = $cnt + 1;
            }
        }

        // PointTableにデータ追加
        $sql = <<< SQL
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
        $cnt = 0;
        foreach ($_POST['point'] as $point) {
            if ($point['pointContent'] != '') {
                $array = array(':recipeId' => $newId, ':pointId' => $cnt, ':pointContent' => $point['pointContent']);
                operateData($db_name, $sql, $array);
                $cnt = $cnt + 1;
            }
        }
    }
?>