<?php
    require_once("../../Functions.inc");
    $db_name = 'ssbu_db';
    $data = getData($db_name);

    function getData($db_name){
        $sql = <<< SQL
            SELECT
                CharacterTable.CharacterId,
                CharacterTable.CharacterSubId,
                CharacterTable.CharacterName,
                (
                    CASE CharacterTable.CharacterSubId
                        WHEN 0 THEN 1
                        ELSE 0
                    END
                ) AS IsDetail,
                (
                    CASE
                        WHEN (CharacterTable.CharacterSubId = 0) AND (Tmp.Count > 1) THEN 0
                        ELSE 1
                    END
                ) AS IsModify
            FROM
                CharacterTable
                LEFT OUTER JOIN (
                    SELECT
                        CharacterId,
                        COUNT(CharacterId) AS Count
                    FROM
                        CharacterTable
                    GROUP BY
                        CharacterId
                ) AS Tmp
                    ON Tmp.CharacterId = CharacterTable.CharacterId
            WHERE
                1 = 1 
SQL;
        switch (true) {
            case @$_POST['searchWord'] != '':
                $sql .= <<< SQL
                    AND (
                        CharacterTable.CharacterName LIKE :characterName
                        OR CharacterTable.CharacterNameHiragana LIKE :characterNameHiragana
                    )
SQL;
                $ary = array(':characterName' => '%' . $_POST['searchWord'] . '%', ':characterNameHiragana' => '%' . $_POST['searchWord'] . '%');
                break;
            default:
                $ary = NULL;
                break;
        }
    
        return selectData($db_name, $sql, $ary);
    }
?>