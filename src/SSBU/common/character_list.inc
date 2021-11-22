<?php
require_once("../../Functions.inc");
$db_name = 'ssbu_db';

$data = getCharacter($db_name);

function getCharacter($db_name)
{
    $sql = <<< SQL
            SELECT
                CharacterTable.*
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
                CharacterTable.CharacterSubId != 0
                OR Tmp.Count = 1
            ORDER BY
                CharacterId
SQL;
    return selectData($db_name, $sql);
}