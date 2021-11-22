<?php
    require_once("../Functions.inc");
    $db_name = 'as_db';
    if ($_POST['register'] != NULL) {
        try {
            $dbh = setDB($db_name);
            // トランザクション開始
            $dbh->beginTransaction();
        
            insertSiteData($db_name, $_POST['urlList']);
            insertUrlData($db_name);
            DownloadPhoto($db_name);
        
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
        // header('Location: ./index.php');
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
                        PageTitle,
                        PageStatus
                    )
                    VALUES (
                        :pageId,
                        :pageUrl,
                        :pageTitle,
                        'new'
                    )
SQL;
                $title = getTitle($url);
    
                $array = array(
                    ':pageId' => $newId,
                    ':pageUrl' => $url,
                    ':pageTitle' => $title
                );
                operateData($db_name, $sql, $array);
                sleep(1);
            }
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
            $rssImage = '';
            $site_source = file_get_contents($site['PageUrl']);
            $preg_string = '/< *img[^>]*src *= *["\']?([^"\']*)/i';
            preg_match_all($preg_string, $site_source, $match);
            foreach ($match[1] as $url) {
                if (!isExistUrl($db_name, $url)) {
                    $sql ='';
                    // UrlIDの最大値の次の数字取得
                    $sql = <<< SQL
                        SELECT
                            MAX(UrlId) AS maxId
                        FROM
                            UrlTable
SQL;
                    $newId = selectData($db_name, $sql)[0]['maxId'] + 1;
            
                    // UrlTableにデータ追加
                    $sql = <<< SQL
                        INSERT INTO UrlTable (
                            UrlId,
                            PageId,
                            Url,
                            FileName,
                            FileStatus
                        )
                        VALUES (
                            :urlId,
                            :pageId,
                            :url,
                            :fileName,
                            'new'
                        )
SQL;
        
                    $array = array(
                        ':urlId' => $newId,
                        ':pageId' => $site['PageId'],
                        ':fileName' => $newId . '.' . end(explode('.', $url)),
                        ':url' => $url
                    );
                    operateData($db_name, $sql, $array);
                }
            }
            $sql = <<< SQL
                UPDATE
                    PageTable
                SET
                    PageStatus = 'done'
                WHERE
                    PageUrl = :pageUrl
SQL;
            $array = array(':pageUrl' => $site['PageUrl']);
            operateData($db_name, $sql, $array);
        }
        
    }

    function DownloadPhoto($db_name){
        $sql = <<< SQL
            SELECT
                UrlTable.UrlId,
                UrlTable.Url,
                UrlTable.FileName,
                PageTable.PageTitle
            FROM
                UrlTable
                INNER JOIN PageTable ON
                    PageTable.PageId = UrlTable.PageId
            WHERE
                UpdateDate IS NULL
SQL;

            $photoList = selectData($db_name, $sql);
            foreach ($photoList as $photo) {
                $dir = './Download';
                $file_name = $dir . '/' . $photo['FileName'];
                mkdir($dir, '0777', true);
                chmod($dir, '0755');
                $data = file_get_contents($photo['Url']);
                file_put_contents($file_name, $data); //ファイルの保存先

                $sql = <<< SQL
                    UPDATE
                        UrlTable
                    SET
                        FileSize = :fileSize,
                        UpdateDate = Now()
                    WHERE
                        UrlId = :urlId
SQL;
                $array = array(
                    ':urlId' => $photo['UrlId'],
                    ':fileSize' => filesize($file_name)
                );
                
                operateData($db_name, $sql, $array);
                if (filesize($file_name) < 20000) { // 20kb以下は削除する
                    unlink($file_name);
                    $sql = <<< SQL
                        UPDATE
                            UrlTable
                        SET
                            FileStatus = 'garbage'
                        WHERE
                            UrlId = :urlId
SQL;
                    $array = array(
                        ':urlId' => $photo['UrlId']
                    );

                    operateData($db_name, $sql, $array);
                }
                sleep(2);
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

    function getTitle($url){
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
?>