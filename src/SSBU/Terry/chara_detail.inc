<?php
    require_once("../../Functions.inc");
    require_once("../common/Parsedown.php");
    $db_name = 'ssbu_db';
    $data = getData($db_name);

    function getData($db_name){
        $sql = <<< SQL
                SELECT
                    CharacterTable.CharacterName,
                    CharacterMemoTable.CharacterMemo
                FROM
                    CharacterMemoTable
                    INNER JOIN CharacterTable
                        ON CharacterTable.CharacterId = CharacterMemoTable.CharacterId
                        AND CharacterTable.CharacterSubId = CharacterMemoTable.CharacterSubId
                WHERE
                    CharacterMemoTable.CharacterId = :character_id
SQL;
        $array = array(':character_id' => $_GET['character_id']);

        $result = selectData($db_name, $sql, $array);
        foreach ($result as &$character) {
            $Parsedown = new Parsedown();
            $character['CharacterMemo'] = $Parsedown->text($character['CharacterMemo']);
        }
        return $result;
    }
?>