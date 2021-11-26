<?php
require_once("../Functions.inc");
$db_name = 'as_db';

if (@$_POST['register'] != NULL) {
    try {
        $dbh = setDB($db_name);
        // トランザクション開始
        $dbh->beginTransaction();

        updateUrlTable($db_name);

        // コミット
        $dbh->commit();

    } catch (PDOException $e) {
        // ロールバック
        $dbh->rollBack();
        // エラーメッセージ出力
        echo $e->getMessage();
        die();
    }
    // 接続を閉じる
    $dbh = null;
    if ($_POST['sort'] == NULL) {
        header('Location: ./index.php');
    } else {
        header('Location: ./select.php?sort=' . $_POST['sort']);
    }
} else {
    if (@$_GET['okOnly'] != NULL) {
        $data = getPhotoOnly($db_name);
    }
    if (@$_GET['multiple'] != NULL) {
        $data = getPhotoMultiple($db_name);
    }
    if (@$_GET['big_size'] != NULL) {
        $data = getPhotoBigSize($db_name);
    }
    if (@$_GET['newOnly'] != NULL) {
        $data = getPhoto($db_name);
        $title = getTitle($db_name);
    }
}

function getPhotoOnly($db_name)
{
    $sql = <<< SQL
            SELECT
                UrlTable.PageId,
                UrlTable.UrlId,
                UrlTable.FileName,
                PageTable.PageTitle
            FROM
                UrlTable
                LEFT OUTER JOIN PageTable
                    ON PageTable.PageId = UrlTable.PageId
            WHERE
                UrlTable.FileStatus = 'ok'
            ORDER BY
SQL;
    switch ($_GET['sort']) {
        case 'update_asc':
            $sql .= ' UrlTable.UpdateDate ASC';
            break;
        case 'update_desc':
            $sql .= ' UrlTable.UpdateDate DESC';
            break;
        case 'size_asc':
            $sql .= ' UrlTable.FileSize ASC';
            break;
        case 'size_desc':
            $sql .= ' UrlTable.FileSize DESC';
            break;
        case 'random':
            $sql .= ' RAND()';
            break;
    }
    return selectData($db_name, $sql);
}

function getPhotoMultiple($db_name)
{
    $sql = <<< SQL
        SELECT
            UrlTable.PageId,
            UrlTable.UrlId,
            UrlTable.Url,
            -- UrlTable.FileSize,
            PageTable.PageTitle
        FROM
            UrlTable
            LEFT OUTER JOIN PageTable
                ON PageTable.PageId = UrlTable.PageId
            LEFT OUTER JOIN (
                SELECT
                    FileSize,
                    FileHeight,
                    FileWidth,
                    Count(FileSize) AS Count,
                    '1' AS Multiple
                FROM
                    UrlTable
                WHERE
                    FileStatus = 'new'
                    OR FileStatus = 'ok'
                GROUP BY
                    FileSize,
                    FileHeight,
                    FileWidth
                HAVING
                    Count > 1
            ) AS Tmp
                ON Tmp.FileSize = UrlTable.FileSize
                AND Tmp.FileHeight = UrlTable.FileHeight
                AND Tmp.FileWidth = UrlTable.FileWidth
        WHERE
            UrlTable.FileStatus = 'new'
            AND Tmp.Multiple = '1'
        ORDER BY
            UrlTable.FileSize DESC
        LIMIT 100
SQL;
    return selectData($db_name, $sql);
}

function getPhotoBigSize($db_name)
{
    $sql = <<< SQL
        SELECT
            UrlTable.PageId,
            UrlTable.UrlId,
            UrlTable.Url,
            -- UrlTable.FileSize,
            PageTable.PageTitle
        FROM
            UrlTable
            LEFT OUTER JOIN PageTable
                ON PageTable.PageId = UrlTable.PageId
        WHERE
            UrlTable.FileStatus = 'new'
            AND UrlTable.UpdateDate IS NOT NULL
            AND UrlTable.Url LIKE :extensionType1
            AND UrlTable.Url NOT LIKE :extensionType2
        ORDER BY
            UrlTable.FileSize DESC
        LIMIT 100
SQL;
    if (@$_GET['gif'] != NULL) {
        $array = array(
            ':extensionType1' => '%.gif',
            ':extensionType2' => ''
        );
    } else {
        $array = array(
            ':extensionType1' => '%',
            ':extensionType2' => '%.gif'
        );
    }
    return selectData($db_name, $sql, $array);
}

function getPhoto($db_name)
{
    $sql = <<< SQL
        SELECT
            UrlTable.PageId,
            UrlTable.UrlId,
            UrlTable.Url,
            PageTable.PageTitle
        FROM
            UrlTable
            LEFT OUTER JOIN PageTable
                ON PageTable.PageId = UrlTable.PageId
        WHERE
            UrlTable.PageId = :pageId
            AND UrlTable.FileStatus = 'new'
        ORDER BY
            UrlTable.FileSize DESC
        LIMIT 100
SQL;
    $array = array(
        ':pageId' => $_GET['pageId']
    );
    return selectData($db_name, $sql, $array);
}

function getTitle($db_name)
{
    $sql = <<< SQL
            SELECT
                PageTitle
            FROM
                PageTable
            WHERE
                PageId = :pageId
SQL;
    $array = array(
        ':pageId' => $_GET['pageId']
    );
    return selectData($db_name, $sql, $array)[0]['PageTitle'];
}

function updateUrlTable($db_name)
{
    foreach ($_POST['choice'] as $index => $value) {
        $sql = <<< SQL
                SELECT
                    FileStatus
                FROM
                    UrlTable
                WHERE
                    PageId = :pageId
                    AND UrlId = :urlId
SQL;
        $array = array(
            ':pageId' => explode('_', $index)[0],
            ':urlId' => explode('_', $index)[1]
        );
        $status = selectData($db_name, $sql, $array)[0]['FileStatus'];

        $sql = <<< SQL
                UPDATE
                    UrlTable
                SET
                    FileStatus = :fileStatus,
                    UpdateDate = Now()
                WHERE
                    PageId = :pageId
                    AND UrlId = :urlId
SQL;
        if ($value == 'delete') {
            $array = array(
                ':fileStatus' => 'ng',
                ':pageId' => explode('_', $index)[0],
                ':urlId' => explode('_', $index)[1]
            );
            $isExcute = ($status != 'ng'); // ステータスが変わらない場合はアップデートをしない
        } else {
            $array = array(
                ':fileStatus' => 'ok',
                ':pageId' => explode('_', $index)[0],
                ':urlId' => explode('_', $index)[1]
            );
            $isExcute = ($status != 'ok'); // ステータスが変わらない場合はアップデートをしない
        }
        if ($isExcute) {
            operateData($db_name, $sql, $array);
        }
    }
}