<?php require_once("./register.inc"); ?>
<!doctype html>
<html lang="ja">

<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../common.css">
    <title>登録</title>
</head>

<body>
    <div class="container">
        <h1>データ</h1>
        <h2>直近ダウンロード</h2>
        <?php foreach ($data['LastDownloadData'] as $value) { ?>
            <li>
                <?php echo $value['UpdateDate']; ?>
            </li>
        <?php } ?>
        <h2>件数</h2>
        <h3>ダウンロード済み</h3>
        <?php echo number_format($data['Total']['DownloadedCount']); ?>件
        <h3>未ダウンロード</h3>
        <?php echo number_format($data['Total']['UnDownloadedCount']); ?>件
        <h1>登録URL</h1>
        <form name="register" action="register.php" method="POST">
            <textarea name="urlList" class="form-control" rows="30"></textarea>
            <br />
            <input type="submit" name="register" value="登録" class="btn btn-success" />
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