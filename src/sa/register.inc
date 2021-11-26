<?php
    require_once("../Functions.inc");
    $db_name = 'as_db';
    if (@$_POST['register'] != NULL) {
        try {
            $dbh = setDB($db_name);
            // トランザクション開始
            $dbh->beginTransaction();
        
            insertSiteData($db_name, $_POST['urlList']);
            updateSiteData($db_name);
            insertUrlData($db_name);
        
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

    }
    $data = getSituation($db_name);
    
    function insertSiteData($db_name, $siteList) {
        $urlArray = explode("\n", $siteList);           // 行に分割
        $urlArray = array_map('trim', $urlArray);       // 各行にtrim()をかける
        $urlArray = array_filter($urlArray, 'strlen');  // 文字数が0の行を取り除く
        $urlArray = array_values($urlArray);            // キーを連番に振りなおす

        foreach ($urlArray as $url) {
            if (!isExistSite($db_name, $url)) {
                // ページIDの最大値の次の数字取得
                $sql='';
                $sql = <<< SQL
                    SELECT
                        MAX(PageId) AS maxId
                    FROM
                        PageTable
SQL;
                $newId = selectData($db_name, $sql)[0]['maxId'] + 1;
        
                // PageTableにデータ追加
                $sql = <<< SQL
                    INSERT INTO PageTable (
                        PageId,
                        PageUrl,
                        PageStatus
                    )
                    VALUES (
                        :pageId,
                        :pageUrl,
                        'new'
                    )
SQL;
    
                $array = array(
                    ':pageId' => $newId,
                    ':pageUrl' => $url
                );
                operateData($db_name, $sql, $array);
            }
        }
    }
    
    function updateSiteData($db_name) {
        $sql = <<< SQL
            SELECT
                PageId,
                PageUrl
            FROM
                PageTable
            WHERE
                PageStatus = 'new'
                AND PageTitle IS NULL
SQL;
        $siteList = selectData($db_name, $sql);
        foreach ($siteList as $site) {
            $sql = <<< SQL
                UPDATE
                    PageTable
                SET
                    PageTitle = :pageTitle,
                    PageSource = :pageSource
                WHERE
                    PageId = :pageId
SQL;
            $pageSource = file_get_contents($site['PageUrl']);
            $title = getTitle($pageSource);

            $array = array(
                ':pageId' => $site['PageId'],
                ':pageTitle' => $title,
                ':pageSource' => $pageSource
            );
            operateData($db_name, $sql, $array);
        }
    }

    function insertUrlData($db_name){
        $sql = <<< SQL
            SELECT
                PageId,
                PageUrl
            FROM
                PageTable
            WHERE
                PageStatus = 'new'
SQL;
        $siteList = selectData($db_name, $sql);
        foreach ($siteList as $site) {
            $preg_string = '/< *img[^>]*src *= *["\']?([^"\']*)/i';
            preg_match_all($preg_string, $site['pageSource'], $match);
            $urlId = 0;
            foreach ($match[1] as $url) {
                if (substr($url, 0, 4) != "http") {
                    if (substr($url, 0, 1) != "/") {
                        $url = '/' . $url;
                    }
                    $url = explode('/', $site['PageUrl'])[0] . '//' . explode('/', $site['PageUrl'])[2] . $url;
                }

                if (strpos($url,'-s.') !== false) {
                    if (getFileSize($url) < getFileSize(str_replace('-s.', '.', $url))) {
                        $url = str_replace('-s.', '.', $url);
                    }
                }
                if (!isExistUrl($db_name, $url)) {
                    // UrlTableにデータ追加
                    $sql = <<< SQL
                        INSERT INTO UrlTable (
                            UrlId,
                            PageId,
                            Url,
                            FileName,
                            FileStatus,
                            FileSize,
                            FileHeight,
                            FileWidth,
                            UpdateDate
                        )
                        VALUES (
                            :urlId,
                            :pageId,
                            :url,
                            :fileName,
                            :fileStatus,
                            :fileSize,
                            :fileHeight,
                            :fileWidth,
                            Now()
                        )
SQL;
                    $urlId ++;
                    $file_size = getFileSize($url);
                    $array = array(
                        ':urlId' => $urlId,
                        ':pageId' => $site['PageId'],
                        ':fileName' => $site['PageId'] . '_' . $urlId . '.' . end(explode('.', explode('?', $url)[0])),
                        ':url' => $url,
                        ':fileStatus' => ($file_size > 40000) ? 'new' : 'garbage',
                        ':fileSize' => $file_size,
                        ':fileHeight' => is_null(getimagesize($url)[1]) ? '0' : getimagesize($url)[1],
                        ':fileWidth' => is_null(getimagesize($url)[0]) ? '0' : getimagesize($url)[0]
                    );
                    operateData($db_name, $sql, $array);
                }
            }
            $sql = <<< SQL
                UPDATE
                    PageTable
                SET
                    PageStatus = 'done',
                    pageSource = NULL
                WHERE
                    PageId = :pageId
SQL;
            $array = array(':pageId' => $site['PageId']);
            operateData($db_name, $sql, $array);
        }
        
    }

    function getSituation($db_name){
        $array = array();
        $sql = <<< SQL
            SELECT
                DATE_FORMAT(UpdateDate, '%Y年%m月%d日%H時%i分%s秒') AS UpdateDate
            FROM
                UrlTable
            ORDER BY
                UpdateDate Desc
            LIMIT 3
SQL;
        $array['LastDownloadData'] = selectData($db_name, $sql);

        $sql = <<< SQL
            SELECT
                (
                    SELECT
                        COUNT(*)
                    FROM
                        UrlTable
                    WHERE
                        UpdateDate IS NOT NULL
                ) AS DownloadedCount,
                (
                    SELECT
                        COUNT(*)
                    FROM
                        UrlTable
                    WHERE
                        UpdateDate IS NULL
                ) AS UnDownloadedCount
            FROM
                DUAL;
SQL;
        $array['Total'] = selectData($db_name, $sql)[0];
        return $array;

    }

    function isExistSite($db_name, $url){
        $sql = <<< SQL
            SELECT
                PageId
            FROM
                PageTable
            WHERE
                PageUrl = :pageUrl
SQL;

        $array = array(':pageUrl' => $url);
        $tmp = selectData($db_name, $sql, $array);
        return count($tmp) > 0;
    }

    function isExistUrl($db_name, $url){
        $sql = <<< SQL
            SELECT
                UrlId
            FROM
                UrlTable
            WHERE
                Url = :url
SQL;

        $array = array(':url' => $url);
        $tmp = selectData($db_name, $sql, $array);
        return count($tmp) > 0;
    }

    function getTitle($source){
        //タイトルタグを探すための正規表現
        $pattern  = '/<title>(.*?)<\/title>/i';

        //preg_matchでページ全体からタイトルタグの中身だけを$matchに抽出
        preg_match($pattern, $source, $match);

        //タイトルタグが一つだけの場合$match[1]がタイトルタグの中身
        if (strlen($match[1]) > 0) {
            return $match[1];
        } else {
            return 'タイトル取得失敗';
        }
    }
    function getFileSize($url){
        $header = @get_headers($url);
        if ( $header !== false ) {
            $size = implode( "\n", $header );
            if (preg_match('/Content-Length: (\d+)/', $size, $matches)) {
                $contentLength = (int)$matches[1];
                return $contentLength;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
?>