<?php
require_once("../Functions.inc");
$db_name = 'as_db';

$sql = GetSql($_GET['pattern']);

$data_list = selectData($db_name, $sql);

function GetSql($pattern){
    switch ($pattern) {
        case '1':
            $sql = <<< SQL
                SELECT
                    PageTable.*,
                    Tmp.UrlCount
                FROM
                    PageTable
                    LEFT OUTER JOIN (
                        SELECT
                            PageId,
                            COUNT(*) AS UrlCount
                        FROM
                            UrlTable
                        GROUP BY
                            PageId
                    ) AS Tmp
                        ON Tmp.PageId = PageTable.PageId
                WHERE
                    PageStatus = 'new'
                ORDER BY
                    PageId ASC
SQL;
            break;
        case '2':
            $sql = <<< SQL
                SELECT
                    PageTable.*,
                    Tmp.UrlCount
                FROM
                    PageTable
                    LEFT OUTER JOIN (
                        SELECT
                            PageId,
                            COUNT(*) AS UrlCount
                        FROM
                            UrlTable
                        GROUP BY
                            PageId
                    ) AS Tmp
                        ON Tmp.PageId = PageTable.PageId
                ORDER BY
                    PageId ASC
SQL;
            break;
        case '3':
            $sql = <<< SQL
                SELECT
                    UrlTable.*,
                    PageTable.*
                FROM
                    UrlTable
                    LEFT OUTER JOIN PageTable
                        ON PageTable.PageId = UrlTable.PageId
                WHERE
                    UrlTable.FileStatus = 'new'
                ORDER BY
                    UrlId ASC
SQL;
            break;
        case '4':
            $sql = <<< SQL
                SELECT
                    UrlTable.*,
                    PageTable.*
                FROM
                    UrlTable
                    LEFT OUTER JOIN PageTable
                        ON PageTable.PageId = UrlTable.PageId
                WHERE
                    UpdateDate IS NULL
                    AND FileStatus = 'garbage'
                ORDER BY
                    UrlTable.FileSize DESC,
                    UrlTable.UrlId ASC
SQL;
            break;
        default:
            break;
    }

    return $sql;
}
?>