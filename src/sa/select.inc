<?php
require_once("../Functions.inc");
$db_name = 'as_db';

if (@$_POST['repairTitle'] != NULL) {
    RepairUntitledSite($db_name);
}
// if (@$_POST['repairUrl'] != NULL) {
//     RepairUrl($db_name);
// }
// if (@$_POST['repairGarbage'] != NULL) {
//     UpdateGarbage($db_name);
// }
if (@$_POST['repairPageId'] != NULL) {
    UpdatePageTableUpdateTable($db_name);
}
if (@$_POST['DownloadDelete'] != NULL) {
    DownloadAndDeletePhoto($db_name);
}
$data = getSite($db_name);

function RepairUntitledSite($db_name)
{
    $sql = <<< SQL
            SELECT
                PageId,
                PageUrl
            FROM
                PageTable
            WHERE
                PageTitle = 'タイトル取得失敗'
SQL;
    $siteList = selectData($db_name, $sql);

    foreach ($siteList as $site) {
        $sql = <<< SQL
                UPDATE
                    PageTable
                SET
                    PageTitle = :pageTitle
                WHERE
                    PageId = :pageId
SQL;
        $array = array(
            ':pageTitle' => getTitle($site['PageUrl']),
            ':pageId' => $site['PageId']
        );

        operateData($db_name, $sql, $array);
    }
}

function DownloadAndDeletePhoto($db_name){
    $sql = <<< SQL
        SELECT
            Url,
            FileName
        FROM
            UrlTable
        WHERE
            FileStatus = 'ok'
SQL;
    $photoList = selectData($db_name, $sql);

    $dir = './Download';

    foreach ($photoList as $photo) {
        $file_name = $dir . '/' . $photo['FileName'];
        if (!file_exists($file_name)) {
            $data = file_get_contents($photo['Url']);
            file_put_contents($file_name, $data); //ファイルの保存先
        }
    }
    
    foreach (glob($dir . '/*.*') as $file) {
        $file_name = end(explode('/', $file));
        $deleteFlag = true;
        foreach ($photoList as $photo) {
            if ($photo['FileName'] == $file_name) {
                $deleteFlag = false;
                break;
            }
        }
        if ($deleteFlag) {
            unlink($file);
        }

    }


    // foreach(glob('dir/*') as $file){
    //     if(is_file($file)){
    //         echo htmlspecialchars($file);
    //     }
    // }
}

// function DeleteNgPhoto($db_name)
// {
//     // foreach ($_POST['choice'] as $index => $value) {
//     $sql = <<< SQL
//                 SELECT
//                     FileName
//                 FROM
//                     UrlTable
//                 WHERE
//                     FileStatus = 'ng'
//                     -- UrlId = :urlId
//                 ORDER BY
//                     UpdateDate DESC
//                 LIMIT
//                     1000
// SQL;
//     // $array = array(
//     //     ':urlId' => $index
//     // );
//     // }
//     // $photolist = selectData($db_name, $sql, $array);
//     $photolist = selectData($db_name, $sql);

//     foreach ($photolist as $photo) {
//         $file_path = './Download/' . $photo['FileName'];
//         if ($file_path) {
//             unlink($file_path);
//         }
//     }
// }


// function RepairUrl($db_name)
// {
//     $sql = <<< SQL
//             UPDATE
//                 UrlTable,
//                 PageTable
//             SET
//                 UrlTable.Url = CONCAT(
//                     SUBSTRING_INDEX(PageTable.PageUrl, '/', 3),
//                     UrlTable.Url
//                 ),
//                 UrlTable.FileStatus = 'new',
//                 UrlTable.FileSize = NULL,
//                 UrlTable.UpdateDate = NULL
//             WHERE
//                 UrlTable.PageId = PageTable.PageId
//                 AND UrlTable.FileSize = 0
//                 AND NOT(UrlTable.Url LIKE 'http%')
// SQL;
//     operateData($db_name, $sql);
// }

// function UpdateGarbage($db_name)
// {
//     $sql = <<< SQL
//             UPDATE
//                 UrlTable
//             SET
//                 UpdateDate = NOW()
//             WHERE
//                 UpdateDate IS NULL
//                 AND FileStatus = 'garbage'
// SQL;
//     operateData($db_name, $sql);
// }

function UpdatePageTableUpdateTable($db_name)
{
    // UrlTableにデータがないPageTableを削除
    $sql = <<< SQL
        DELETE
            PageTable
        FROM
            PageTable
            LEFT OUTER JOIN (
                SELECT
                    PageId,
                    '1' AS IsExistUrl
                FROM
                    UrlTable
                GROUP BY
                    PageId
            ) AS UrlTable2 ON UrlTable2.PageId = PageTable.PageId
        WHERE
            UrlTable2.IsExistUrl IS NULL
            AND PageStatus = 'done'
SQL;
    operateData($db_name, $sql);

    $sql = <<< SQL
        SELECT
            ROW_NUMBER() OVER (
                ORDER BY
                    PageId
            ) AS RowNumber,
            PageId
        FROM
            PageTable
        ORDER BY
            PageId ASC
SQL;
    $pageData = selectData($db_name, $sql);
    foreach ($pageData as $page) {
        # code...
    }
}

function getTitle($url)
{
    //file_get_contentsでソース全部読み込む
    $contents = file_get_contents($url);

    //タイトルタグを探すための正規表現
    $pattern  = '/<title>(.*?)<\/title>/i';

    //preg_matchでページ全体からタイトルタグの中身だけを$matchに抽出
    preg_match($pattern, $contents, $match);

    //タイトルタグが一つだけの場合$match[1]がタイトルタグの中身
    if (strlen($match[1]) > 0) {
        return $match[1];
    } else {
        return 'タイトル取得失敗';
    }
}

function getSite($db_name)
{
    $sql = <<< SQL
            SELECT
                COUNT(UrlTable.PageId) AS COUNT,
                PageTable.PageId,
                PageTable.PageTitle
            FROM
                UrlTable
                INNER JOIN PageTable
                    ON PageTable.PageId = UrlTable.PageId
                LEFT OUTER JOIN (
                    SELECT
                        DISTINCT PageId,
                        '1' AS IsExistUpdateDateNull
                    FROM
                        UrlTable
                    WHERE
                        UpdateDate IS NULL
                ) AS A
                    ON A.PageId = PageTable.PageId
                LEFT OUTER JOIN (
                    SELECT
                        Count(*) AS OK_NG_NEW_Count,
                        PageId
                    FROM
                        UrlTable
                    WHERE
                        FileStatus = 'ok'
                        OR FileStatus = 'ng'
                        OR FileStatus = 'new'
                    GROUP BY
                        PageId
                ) AS NG_UrlTable
                    ON NG_UrlTable.PageId = UrlTable.PageId
            WHERE
                UrlTable.FileStatus = 'new'
                AND A.IsExistUpdateDateNull IS NULL
            GROUP BY
                UrlTable.PageId
            ORDER BY
SQL;
    switch (@$_GET['sort']) {
        case 'count_asc':
            $sql .= ' OK_NG_NEW_Count ASC';
            break;
        case 'count_desc':
            $sql .= ' OK_NG_NEW_Count DESC';
            break;
        case 'page_id_asc':
            $sql .= ' PageTable.PageId ASC';
            break;
        case 'page_id_desc':
            $sql .= ' PageTable.PageId DESC';
            break;
        case 'page_title_asc':
            $sql .= ' PageTable.PageTitle ASC';
            break;
        case 'page_title_desc':
            $sql .= ' PageTable.PageTitle DESC';
            break;
    }
    return selectData($db_name, $sql);
}
