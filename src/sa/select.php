<?php require_once("./select.inc"); ?>
<!doctype html>
<html lang="ja">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
<script type="text/javascript">
    $(document).keydown(
        function(e) {
            if (e.keyCode == 70) { // 70・・・「f」
                document.getElementById('link0').click();
            }
        }
    );
</script>

<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../common.css">
    <title>吟味</title>
</head>

<body>
    <div class="container">
        <h1>サイト一覧</h1>
        <?php foreach (@$data as $index => $site) { ?>
            <li>
                <a href= "select_detail.php?pageId=<?php echo $site['PageId']; ?>&sort=<?php echo $_GET['sort']; ?>&newOnly=1" id="link<?php echo $index; ?>">
                    <?php echo '(' . $site['COUNT'] . '枚)' . $site['PageTitle']; ?>
                </a>
            </li>
            <br />
        <?php } ?>
        <br />
        <form name="select" action="select.php" method="POST">
            <input type="submit" name="repairTitle" value="サイトタイトル自動修正" class="btn btn-success" />
            <!-- <input type="submit" name="repairUrl" value="URL自動修正" class="btn btn-success offset-1" /> -->
            <!-- <input type="submit" name="repairGarbage" value="UpdateDate無しgarbage削除" class="btn btn-success offset-1" /> -->
            <input type="submit" name="repairPageId" value="PageId修正" class="btn btn-success offset-1" />
            <input type="submit" name="DownloadDelete" value="ダウンロード&削除" class="btn btn-success offset-1" />
            <input type="button" onclick="location.href='index.php'" value="戻る" class="btn btn-primary offset-1">
        </form>
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>