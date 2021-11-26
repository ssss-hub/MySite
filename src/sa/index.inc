<?php
    require_once("../Functions.inc");
    $db_name = 'as_db';
    $data = getCount($db_name);
    
    function getCount($db_name){
        $sql = <<< SQL
            SELECT
                (
                    SELECT
                        COUNT(DISTINCT(PageId))
                    FROM
                        UrlTable
                    WHERE
                        FileStatus = 'new'
                ) AS SELECT_SITE_COUNT,
                (
                    SELECT
                        COUNT(*)
                    FROM
                        UrlTable
                    WHERE
                        FileStatus = 'new'
                ) AS SELECT_URL_COUNT,
                (
                    SELECT
                        COUNT(*)
                    FROM
                        UrlTable
                    WHERE
                        FileStatus = 'ok'
                ) AS OK_COUNT
            FROM
                DUAL
SQL;
        return selectData($db_name, $sql)[0];
    }
