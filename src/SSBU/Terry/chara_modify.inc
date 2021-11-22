<?php
    require_once("../../Functions.inc");
    $db_name = 'ssbu_db';
    switch (true) {
        case $_POST['modify'] !='':
            try {
                $dbh = setDB($db_name);
                // トランザクション開始
                $dbh->beginTransaction();
            
                updateData($db_name);
            
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
            header('Location: ./chara_search.php');
            break;
        default:
            $data = getData($db_name);
            break;
    }

    function getData($db_name){
        $sql = <<< SQL
                SELECT
                    CharacterTable.CharacterName,
                    CharacterMemoTable.CharacterId,
                    CharacterMemoTable.CharacterSubId,
                    CharacterMemoTable.CharacterMemo
                FROM
                    CharacterMemoTable
                    INNER JOIN CharacterTable
                        ON CharacterTable.CharacterId = CharacterMemoTable.CharacterId
                        AND CharacterTable.CharacterSubId = CharacterMemoTable.CharacterSubId
                WHERE
                    CharacterMemoTable.CharacterId = :character_id
                    AND CharacterMemoTable.CharacterSubId = :character_sub_id
SQL;
        $array = array(':character_id' => $_GET['character_id'], ':character_sub_id' => $_GET['character_sub_id']);

        return selectData($db_name, $sql, $array)[0];
    }

    function updateData($db_name){
        $sql = <<< SQL
            UPDATE
                CharacterMemoTable
            SET
                CharacterMemo = :character_memo
            WHERE
                CharacterId = :character_id
                AND CharacterSubId = :character_sub_id
SQL;    
        $array = array(':character_memo' => $_POST['character_memo'], ':character_id' => $_POST['character_id'], ':character_sub_id' => $_POST['character_sub_id']);
        operateData($db_name, $sql, $array);
    }
?>